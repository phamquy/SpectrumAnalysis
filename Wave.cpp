// Wave.cpp: implementation of the CWave class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpectrumAnalysis.h"
#include "Wave.h"
#include "Mmsystem.h"
#include "windowsx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWave::CWave()
{
	m_sFileName = "";
	m_chnkDATA.WaveData = NULL;
	m_chnkDATA.ChnkSize = 0;
}

CWave::~CWave()
{
	ResetData();
}

//////////////////////////////////////////////////////////////////////////
VOID CWave::ResetData()
{
	if(m_chnkDATA.WaveData != NULL)
	{
		GlobalFreePtr(m_chnkDATA.WaveData);
		m_chnkDATA.WaveData = NULL;
	}	
	m_chnkDATA.ChnkSize = 0;	
}
//////////////////////////////////////////////////////////////////////////

CString CWave::GetFileName()
{
	return m_sFileName;
}

//////////////////////////////////////////////////////////////////////////

void CWave::SetFileName(CString in_sFileName)
{
	if(in_sFileName.GetLength() > MAX_FILENAME_SIZE)
	{
		//AfxMessageBox(SPA_MSG_LONG_FILENAME);
		return;
	}
	m_sFileName = in_sFileName;
}

//////////////////////////////////////////////////////////////////////////
int CWave::collectParameter()
{	
	HMMIO		hMMIO;		//io handle
	MMCKINFO	mmRiffChnkInfo;
	MMCKINFO	mmFmtChnkInfo;
	MMCKINFO	mmDataChnkInfo;

	int retCode = SPA_NORMAL;
	
	char szFileName[MAX_FILENAME_SIZE];
	strcpy(szFileName, LPCTSTR(m_sFileName));
	
	// Open the given file for reading using buffered I/O.
	if(!(hMMIO = mmioOpen(szFileName, NULL, MMIO_READ | MMIO_ALLOCBUF)))
	{
		//AfxMessageBox(SPA_MSG_WAV_FILENOTFOUND);
		return SPA_ERR_FILENOTFOUND;
	}
	
	//get wave chunk info, ensure wave file format
	mmRiffChnkInfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (mmioDescend(hMMIO, &mmRiffChnkInfo, NULL, MMIO_FINDRIFF) )
	{
		//AfxMessageBox(SPA_MSG_INVALID_FILETYPE);
		mmioClose(hMMIO, 0);
		return SPA_ERR_INVALID_FORMAT;
	}

	// Find the "fmt " chunk. It should be
	//  a subchunk of the 'RIFF' parent chunk.
	mmFmtChnkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (mmioDescend(hMMIO, &mmFmtChnkInfo, &mmRiffChnkInfo,	MMIO_FINDCHUNK)!= MMSYSERR_NOERROR)
	{
		//AfxMessageBox(SPA_MSG_UNKNOWN_FORMAT);
		mmioClose(hMMIO, 0);
		return SPA_ERR_CHUNKLOSE;
	}

	//get size of chunk format 
	DWORD dwFmtSize = mmFmtChnkInfo.cksize;
	HANDLE hFormat  = LocalAlloc(LMEM_MOVEABLE, LOWORD(dwFmtSize));	
	if (!hFormat)
	{
		//AfxMessageBox(SPA_MSG_MEMORY_FULL);
		mmioClose(hMMIO, 0);
		return SPA_ERR_MEMORY;
	}
	
	//locate fmt chunk memory
	WAVEFORMATEX* pFormat;	//contain fmt chunk
	pFormat = (WAVEFORMATEX*)LocalLock(hFormat);
	if (!pFormat)
	{
		//AfxMessageBox(SPA_MSG_MEMORY_DUMP);
		LocalFree(hFormat);
		mmioClose(hMMIO, 0);
		return SPA_ERR_MEMORY;
	}

	// Read the fmt chunk.
	if (mmioRead(hMMIO, (HPSTR) pFormat, dwFmtSize) != (LONG) dwFmtSize)
	{
		//AfxMessageBox(SPA_MSG_FILEHEADER_FAIL);
	    LocalUnlock( hFormat );
		LocalFree( hFormat );
		mmioClose(hMMIO, 0);
		return SPA_ERR_HEADER_FAIL;
	}

	// Make sure it's a PCM file.
	if (pFormat->wFormatTag != WAVE_FORMAT_PCM)
	{
		LocalUnlock( hFormat );
		LocalFree( hFormat );
		mmioClose(hMMIO, 0);
		//AfxMessageBox(SPA_MSG_NOT_PCM);
        return SPA_ERR_HEADER_FAIL;
	}

	//fill to our chunk 
	retCode = fillFMTChunk(pFormat);
	if(retCode != SPA_NORMAL)
	{
		//AfxMessageBox(SPA_MSG_FILEHEADER_FAIL);
		LocalUnlock(hFormat);
		LocalFree(hFormat);
		mmioClose(hMMIO, 0);		
		return retCode; 
	}

	if(!openAndCheckDeviceSupport(pFormat, SPA_FMT_CHECK))
	{
		//AfxMessageBox(SPA_MSG_DEVICE_NOT_SUPPORT);
		LocalUnlock(hFormat);
		LocalFree( hFormat );
		mmioClose(hMMIO, 0);		
		return SPA_ERR_DEVICE_NOT_SUPPORT; 
	}
		
	//chunk up and infect to data chunk
	mmioAscend(hMMIO, &mmDataChnkInfo, 0);
	mmDataChnkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(hMMIO, &mmDataChnkInfo, &mmRiffChnkInfo,MMIO_FINDCHUNK)!= MMSYSERR_NOERROR)
	{
		//AfxMessageBox(SPA_MSG_DATA_CHUNK_FAIL);
		LocalUnlock( hFormat );
		LocalFree( hFormat );
		mmioClose(hMMIO, 0);
		return SPA_ERR_DATA_FAIL;
	}

	DWORD dwDataSize = mmDataChnkInfo.cksize;
	if (dwDataSize == 0L)
	{
		//AfxMessageBox(SPA_MSG_DATA_SIZEUNKNOWN);
		LocalUnlock( hFormat);
		LocalFree( hFormat );
		mmioClose(hMMIO, 0);
		return SPA_ERR_DATA_SIZE_FAIL;
	}

	fillDATAChunk(&mmDataChnkInfo, hMMIO);

	if(!openAndCheckDeviceSupport(pFormat, SPA_DATA_CHECK))
	{
		//AfxMessageBox(SPA_MSG_DEVICE_NOT_SUPPORT);
		LocalUnlock(hFormat);
		LocalFree( hFormat );
		mmioClose(hMMIO, 0);		
		return SPA_ERR_DEVICE_NOT_SUPPORT; 
	}

	// We're done with the format header, free it.
	LocalUnlock( hFormat );
	LocalFree( hFormat );
	mmioClose(hMMIO, 0);
	
	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
int CWave::GetSignal(SLS in_scheme, CSignal& out_oSignal)
{
	INT  i;
	INT offset = 0;
	LONG nStartPos = in_scheme.nStart;	
	INT	 nLastPos = in_scheme.nStart  + 
						(in_scheme.nLength-1)*in_scheme.nStep;

	INT nSignalLastPos = m_chnkDATA.ChnkSize - 1;

	//the last pos of this scheme is greater than 
	//signal last pos ? it must return the invalid 
	//scheme
	if(nLastPos > nSignalLastPos)
	{
		return SPA_ERR_INVALID_SCHEME;
	}
	
	//check if the segment is out of original range
	LONG nNumOfSample = nLastPos - nStartPos;

	//after above code, it's sure that the scheme
	//is valid
	if(nNumOfSample <= 0)
	{
		return SPA_ERR_INVALID_SCHEME;
	}

	CSignal temp(in_scheme.nLength);
	INT nBytePerSample = m_chnkFMT.BitPerSample/8; 
		
	try
	{	
		for(i=0; i<in_scheme.nLength; i++)
		{
			offset = nStartPos + i*in_scheme.nStep*nBytePerSample;
			pSAMPLE pTemp = (pSAMPLE)(m_chnkDATA.WaveData + offset);
			temp[i] = *(pTemp);
		}
	}
	catch (CMemoryException ex)		
	{
		return SPA_ERR_MEMORY;
	}

	temp.SetFrequency(m_chnkFMT.SampleRate / in_scheme.nStep);

	out_oSignal = temp;
	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////

int CWave::Play(LONG in_lStart, LONG in_length)
{
	ASSERT(m_chnkDATA.WaveData != NULL);
	ASSERT(in_lStart < GetNumOfSample());

	LONG lPlayLength;

	if((in_length == 0)||
		((in_length+in_lStart) > GetNumOfSample()))
	{
		lPlayLength = GetNumOfSample() - in_lStart;
	}
	else
	{
		lPlayLength = in_length;
	}

	LONG dataStart = in_lStart * 2;
	ASSERT (dataStart < m_chnkDATA.ChnkSize);

	LONG dataLength = lPlayLength * 2;
	if((dataLength + dataStart) > m_chnkDATA.ChnkSize)
	{
		dataLength = m_chnkDATA.ChnkSize - dataStart;
	}

	LPWAVEHDR lpWaveHeader;
	DWORD	dwResult;
	
	lpWaveHeader = (LPWAVEHDR)GlobalAllocPtr(GMEM_MOVEABLE | GMEM_SHARE,
					(DWORD) sizeof(WAVEHDR));
	if (!lpWaveHeader)
	{
		return  SPA_ERR_MEMORY;
	}

	lpWaveHeader->lpData = m_chnkDATA.WaveData + dataStart;
	lpWaveHeader->dwBufferLength = dataLength;
	lpWaveHeader->dwLoops = 0;
	lpWaveHeader->dwFlags = 0;
	
	dwResult = waveOutPrepareHeader(m_hWaveOut, lpWaveHeader, sizeof(WAVEHDR));
	if(dwResult  != MMSYSERR_NOERROR)
	{
		GlobalFreePtr( lpWaveHeader );			
		return SPA_ERR_FAIL_TO_PLAYWAVE;
	}

	// Then the data block can be sent to the output device.
	
	dwResult = waveOutWrite(m_hWaveOut, lpWaveHeader, sizeof(WAVEHDR));
	if (dwResult != MMSYSERR_NOERROR)
	{
		waveOutUnprepareHeader( m_hWaveOut, lpWaveHeader, sizeof(WAVEHDR));
		GlobalFreePtr( lpWaveHeader );		
		return SPA_ERR_FAIL_TO_PLAYWAVE;
	}
	
	while (TRUE) 
	{
		if((lpWaveHeader->dwFlags & WHDR_DONE) == WHDR_DONE)
		break;
	}

	GlobalFreePtr( lpWaveHeader );
	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////

int CWave::InitInstance()
{
	CFileFind fileFind;
	BOOL bFileExist = fileFind.FindFile(m_sFileName);

	if(!bFileExist)
		return SPA_ERR_FILENOTFOUND;


	return collectParameter();
}

//////////////////////////////////////////////////////////////////////////

int CWave::fillFMTChunk(WAVEFORMATEX *in_pFormat)
{
	CString fmt = "fmt ";
	strcpy((char*)m_chnkFMT.ChunkID, LPCTSTR(fmt));	
	m_chnkFMT.AudioFormat	= SPA_CODE_PCM_FORMAT;
	m_chnkFMT.SampleRate	= in_pFormat->nSamplesPerSec;
	m_chnkFMT.BitPerSample  = in_pFormat->wBitsPerSample;
	m_chnkFMT.BlockAlign	= in_pFormat->nBlockAlign;
	m_chnkFMT.NumOfChannels = in_pFormat->nChannels;
	m_chnkFMT.ByteRate		= (m_chnkFMT.SampleRate * m_chnkFMT.NumOfChannels * m_chnkFMT.BitPerSample)/8;
	m_chnkFMT.ChunkSize		= SPA_PCM_FMT_SIZE;
	
	if(is11025_16MONO()) return SPA_NORMAL;
	else return SPA_ERR_NON_11025_16MONO;
}

BOOL CWave::is11025_16MONO()
{
	if(m_chnkFMT.BitPerSample != SPA_PCM_16BITS_SAMPLE) return FALSE;
	if(m_chnkFMT.SampleRate != SPA_PCM_11025Hz)	return FALSE;
	if(m_chnkFMT.NumOfChannels != SPA_PCM_MONO) return FALSE;

	return TRUE;
}

BOOL CWave::openAndCheckDeviceSupport(WAVEFORMATEX *in_pFormat, int in_CheckMode)
{
	int retCode;
	
	if(in_CheckMode == SPA_FMT_CHECK)
	{
	
		// Make sure a waveform output device supports this format.
		#if (WINVER >= 0x0400)
		retCode = waveOutOpen(&m_hWaveOut, WAVE_MAPPER, in_pFormat, 0, 0L, WAVE_FORMAT_QUERY);
		#else
		retCode = waveOutOpen(&m_hWaveOut, WAVE_MAPPER, (LPWAVEFORMATEX)in_pFormat, 0, 0L, WAVE_FORMAT_QUERY);
		#endif
		if(retCode != MMSYSERR_NOERROR)
			return FALSE;	
	}
	else
	{
		#if (WINVER >= 0x0400)
		retCode = waveOutOpen(&m_hWaveOut, WAVE_MAPPER,in_pFormat, (UINT)AfxGetApp()->m_pMainWnd->m_hWnd, 0L, CALLBACK_WINDOW);
		#else
		retCode = waveOutOpen(&m_hWaveOut, WAVE_MAPPER,(LPWAVEFORMATEX)in_pFormat, (UINT)AfxGetApp()->m_pMainWnd->m_hWnd, 0L, CALLBACK_WINDOW);
		#endif

		if(retCode != MMSYSERR_NOERROR)
			return FALSE;	
	}
	return TRUE;
}



//////////////////////////////////////////////////////////////////////////
int CWave::fillDATAChunk(MMCKINFO* in_DataChunk, HMMIO in_hmmio)
{
	CString str = "data";
	strcpy((char*)m_chnkDATA.ChunkID, LPCTSTR(str));
	m_chnkDATA.ChnkSize = in_DataChunk->cksize;
	// Allocate and lock memory for the waveform data.	
	m_chnkDATA.WaveData = (HPSTR)GlobalAllocPtr( GMEM_MOVEABLE | GMEM_SHARE, m_chnkDATA.ChnkSize);
	
	if (!m_chnkDATA.WaveData)
	{
		//AfxMessageBox(SPA_MSG_UNLOCATE_DATA_MEM);
		mmioClose(in_hmmio, 0);
		return SPA_ERR_MEMORY;
	}

	// Read the waveform data subchunk.
	if(mmioRead(in_hmmio, 
			m_chnkDATA.WaveData, 
			m_chnkDATA.ChnkSize) != (long)m_chnkDATA.ChnkSize)
	{
		//AfxMessageBox(SPA_MSG_CANNOT_READDATA);
		ResetData();
		mmioClose(in_hmmio, 0);
		return SPA_ERR_MEMORY_READ;
	}

	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
LONG CWave::GetNumOfSample() const
{
	ASSERT(m_chnkDATA.WaveData != NULL);

	LONG lNumOfSample;
	INT iBytePerSample = m_chnkFMT.BitPerSample / 8;
	lNumOfSample = m_chnkDATA.ChnkSize / m_chnkFMT.NumOfChannels;
	lNumOfSample = lNumOfSample / iBytePerSample;

	return lNumOfSample;
}

//////////////////////////////////////////////////////////////////////////
// get total time of wave file, in milisecond (ms)
DOUBLE CWave::GetTotalTime() const
{
	DOUBLE	dTotalTime;
	LONG	lNumOfSample = GetNumOfSample();
	DOUBLE	Ts_ms = (DOUBLE)1000/(DOUBLE)m_chnkFMT.SampleRate;

	dTotalTime = lNumOfSample * Ts_ms;

	return dTotalTime;
}

//////////////////////////////////////////////////////////////////////////
SAMPLE CWave::GetMaxSample()
{
	ASSERT(m_chnkFMT.NumOfChannels == 1);
	ASSERT(m_chnkDATA.WaveData != NULL);

	LONG i;
	LONG iNumOfSignal = GetNumOfSample();
	INT iBytePerSample = m_chnkFMT.BitPerSample / 8;
	SAMPLE spMax = 0;
	pSAMPLE pPointer = (pSAMPLE)m_chnkDATA.WaveData;

	for(i = 0; i < iNumOfSignal; i++)
	{
		SAMPLE spTemp = *(pPointer);
		if (spTemp > spMax) 
			spMax = spTemp;
		pPointer ++;
	}

	return spMax;
}

//////////////////////////////////////////////////////////////////////////
SAMPLE CWave::GetMinSample()
{
	ASSERT(m_chnkFMT.NumOfChannels == 1);
	ASSERT(m_chnkDATA.WaveData != NULL);

	LONG i;
	LONG iNumOfSignal = GetNumOfSample();
	INT iBytePerSample = m_chnkFMT.BitPerSample / 8;
	SAMPLE spMin = 0;
	pSAMPLE pPointer = (pSAMPLE)m_chnkDATA.WaveData;

	for(i = 0; i < iNumOfSignal; i++)
	{
		SAMPLE spTemp = *(pPointer);
		if (spTemp < spMin) 
			spMin = spTemp;
		pPointer ++;
	}

	return spMin;
}

//////////////////////////////////////////////////////////////////////////
// return value in:(ms)
DOUBLE CWave::GetSampleCycle()
{
	return (DOUBLE)1000/(DOUBLE)m_chnkFMT.SampleRate;
}

//////////////////////////////////////////////////////////////////////////
SAMPLE CWave::GetSampleAt(LONG in_lPos)
{
	ASSERT(in_lPos < GetNumOfSample());
	pSAMPLE pPointer = (pSAMPLE)m_chnkDATA.WaveData;
	pPointer += in_lPos;

	return *(pPointer);
}

//////////////////////////////////////////////////////////////////////////
DOUBLE CWave::GetTimeAt(LONG in_lPos)
{
	ASSERT(in_lPos < GetNumOfSample());
	DOUBLE	dTime;	
	DOUBLE	Ts_ms = (DOUBLE)1000/(DOUBLE)m_chnkFMT.SampleRate;	
	dTime = in_lPos * Ts_ms;
	return dTime;
}

//////////////////////////////////////////////////////////////////////////
LONG CWave::GetIndexOfTime(DOUBLE in_dTime)
{
	DOUBLE Ts_ms = (DOUBLE)1000/(DOUBLE)m_chnkFMT.SampleRate;
	LONG lPos = in_dTime/Ts_ms;
	return lPos;
}
