// Wave.h: interface for the CWave class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVE_H__F0A9AFE2_E57D_473F_818F_D308E030FA3F__INCLUDED_)
#define AFX_WAVE_H__F0A9AFE2_E57D_473F_818F_D308E030FA3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Signal.h"
#include "Mmsystem.h"
#include "common.h"	// Added by ClassView


//////////////////////////////////////////////////////////////////////////
// get saple scheme 

typedef struct tagSELECT_SAMPLE_SCHEME{
	LONG	nStart;			//start position co collect the signal
	INT		nStep;			//interval step to collect the samples
	LONG	nLength;		//number of sample	 
}SELECT_SAMPLE_SCHEME;

typedef SELECT_SAMPLE_SCHEME SLS, *PSLS;


//////////////////////////////////////////////////////////////////////////
// File chunk define

#define MAX_FILENAME_SIZE	128
#define DesciptID	_T("RIFF")
#define WAVE_FOMART	-T("WAVE")
typedef struct  tagFILE_CHUNK
{
	BYTE ChunkID[4];	//RIFF
	LONG ChunkSize;		//Size
	BYTE ChunkFormat[4];//WAVE
}FILE_CHUNK, *PFILE_CHUNK;

//////////////////////////////////////////////////////////////////////////
// FMT chunk define
#define FMT_ID _T("fmt ");
#define AUDIO_FORMAT_PCM	1
#define AUDIO_MONO			1
#define AUDIO_STEREO		2

#define SAMPLE_RATE_11025	11025
#define SAMPLE_BITS			16

typedef struct tagFMT_CHUNK{	
	BYTE ChunkID[4];		//"fmt "
	LONG ChunkSize;			//fmt size
	WORD AudioFormat;		//format =1 ~ PCM
	WORD NumOfChannels;		//1,2
	LONG SampleRate;		//sample rate 11025Hz
	LONG ByteRate;
	WORD BlockAlign;
	WORD BitPerSample;
}FMT_CHUNK, *PFMT_CHUNK;

//////////////////////////////////////////////////////////////////////////
// DATA chunk define

#define DATA_ID		_T("data")

typedef struct tagDATA_CHUNK{
	BYTE	ChunkID[4];
	LONG	ChnkSize;
	HPSTR	WaveData;
}DATA_CHUNK, *PDATA_CHUNK;


//////////////////////////////////////////////////////////////////////////
// Wave object 
class CWave  
{
//function declaration
public:
	LONG GetIndexOfTime(DOUBLE in_dTime);
	VOID ResetData();
	DOUBLE GetTimeAt(LONG in_lPos);
	SAMPLE GetSampleAt(LONG in_lPos);
	DOUBLE GetSampleCycle();
	SAMPLE GetMaxSample();
	SAMPLE GetMinSample();
	DOUBLE GetTotalTime() const;
	LONG GetNumOfSample() const;
	int Play(LONG in_lStart = 0, LONG in_length = 0);
	int GetSignal(SLS in_scheme, CSignal& out_oSignal);	
	void SetFileName(CString in_sFileName);
	CString GetFileName();
	INT InitInstance();
	CWave();
	virtual ~CWave();

protected:
	int collectParameter();
	int fillFMTChunk(WAVEFORMATEX* in_pFormat);
private:
	int fillDATAChunk(MMCKINFO* in_DataChunk, HMMIO in_hmmio);
	BOOL openAndCheckDeviceSupport(WAVEFORMATEX * in_pFormat, int in_CheckMode);
	BOOL is11025_16MONO();
	CString		m_sFileName;
	DATA_CHUNK	m_chnkDATA;
	FMT_CHUNK	m_chnkFMT;
	FILE_CHUNK	m_chnkFILE;
	HWAVEOUT	m_hWaveOut;
};

#endif // !defined(AFX_WAVE_H__F0A9AFE2_E57D_473F_818F_D308E030FA3F__INCLUDED_)
