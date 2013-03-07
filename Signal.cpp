// Signal.cpp: implementation of the CSignal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpectrumAnalysis.h"
#include "Signal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSignal::CSignal()
{
	m_lSize = 0;
	m_pSampleConsole = new SAMPLE[m_lSize +1];
	m_pSampleConsole[m_lSize] = SPA_END_OF_SIGNAL;
	m_lSampleFrequence = 0;
}

CSignal::CSignal(LONG in_Size)
{
	if (in_Size > 0)
	{
		m_lSize = in_Size;		
	}
	else
	{
		m_lSize = 0;
	}

	m_pSampleConsole = new SAMPLE[m_lSize + 1];
	// set pointer-based array element
	for ( int i = 0; i < m_lSize; i++ )
	{
		m_pSampleConsole[ i ] = 0; 
	}
	m_pSampleConsole[m_lSize] = SPA_END_OF_SIGNAL;
	m_lSampleFrequence  = 0;
}

CSignal::CSignal(LONG in_Size, LONG in_lFrequency)
{
	if (in_Size > 0)
	{
		m_lSize = in_Size;		
	}
	else
	{
		m_lSize = 0;
	}

	m_pSampleConsole = new SAMPLE[m_lSize + 1];
	// set pointer-based array element
	for ( int i = 0; i < m_lSize; i++ )
	{
		m_pSampleConsole[ i ] = 0; 
	}
	m_pSampleConsole[m_lSize] = SPA_END_OF_SIGNAL;
	m_lSampleFrequence  = in_lFrequency;
}

//////////////////////////////////////////////////////////////////////////
//copy constructor

CSignal::CSignal( const CSignal &in_SignalCopy)
      :m_lSize(in_SignalCopy.m_lSize)
{
	// create space for pointer-based array
	m_pSampleConsole = new SAMPLE[ m_lSize + 1]; 

	for ( int i = 0; i < m_lSize; i++ )
	{
		// copy into object
		m_pSampleConsole[ i ] = 
		in_SignalCopy.m_pSampleConsole[ i ]; 
	}

	m_pSampleConsole[m_lSize] = SPA_END_OF_SIGNAL;
	m_lSampleFrequence = in_SignalCopy.m_lSampleFrequence;
} 

//////////////////////////////////////////////////////////////////////////

CSignal::~CSignal()
{
	delete [] m_pSampleConsole;
}

//////////////////////////////////////////////////////////////////////////

LONG CSignal::GetSignalSize() const
{
	return m_lSize;
}

//////////////////////////////////////////////////////////////////////////

const CSignal& CSignal::operator=( const CSignal &right )
{
	if ( &right != this ) // avoid self-assignment
	{
		// for Arrays of different sizes, deallocate original
		// left-side array, then allocate new left-side array
		if ( m_lSize != right.m_lSize )
		{
			delete [] m_pSampleConsole;					// release space
			m_lSize = right.m_lSize;					// resize this object
			m_pSampleConsole = new SAMPLE[m_lSize + 1];	// create space for array copy
		} 

		for ( int i = 0; i < m_lSize; i++ )
		{
			m_pSampleConsole[ i ] = right.m_pSampleConsole[ i ];				// copy array into object
		}
		m_pSampleConsole[m_lSize] = SPA_END_OF_SIGNAL;	
		m_lSampleFrequence = right.m_lSampleFrequence;	
	}

	return *this; // enables x = y = z, for example
}

//////////////////////////////////////////////////////////////////////////
SAMPLE &CSignal::operator[](LONG subscript )
{
	// check for subscript out-of-range error
	if ( subscript < 0 || subscript >= m_lSize )
	{
		TRACE(SPA_SGN_OUTOFRANGE);
		return m_pSampleConsole[m_lSize];
	}
	return m_pSampleConsole[subscript];
}

//////////////////////////////////////////////////////////////////////////

SAMPLE CSignal::operator[](LONG subscript ) const
{
	// check for subscript out-of-range error
	if ( subscript < 0 || subscript >= m_lSize )
	{
		TRACE(SPA_SGN_OUTOFRANGE);
		return m_pSampleConsole[m_lSize];
	}
	return m_pSampleConsole[subscript];
}

//////////////////////////////////////////////////////////////////////////
CSignal operator*(const CSignal& sgX, const CSignal& sgH)
{
	CSignal snResult(0);

	if(sgX.m_lSize != sgH.m_lSize)
	{
		TRACE(SPA_SGN_INVALID_CONVOLUTION);		
		return snResult;
	}
	
	//if two signal has the same size	
	LONG n	= 0;
	LONG k	= 0;	
	LONG sizeN = sgX.m_lSize;

	//prepare mem to store result
	snResult.LocateMem(sizeN);

	for (n=0; n <sizeN; n++)
	{
		SAMPLE nTemp = 0;
		for(k=0; k< sizeN; k++)
		{	
			nTemp += sgX[k] * sgH[n-k];
		}
		snResult[n] = nTemp;
	}
	
	return  snResult;
}

//////////////////////////////////////////////////////////////////////////
// prepare memory for thi signal
BOOL CSignal::LocateMem(LONG in_size)
{
	if(in_size < 0) 
		return FALSE;
	else
	{
		m_lSize = in_size;
		delete [] m_pSampleConsole;
		m_pSampleConsole = NULL;
		m_pSampleConsole = new SAMPLE[m_lSize+1];		

		

		ASSERT(m_pSampleConsole != NULL);

		// set pointer-based array element
		for ( int i = 0; i < m_lSize; i++ )
		{
			m_pSampleConsole[ i ] = 0; 
		}
		m_pSampleConsole[m_lSize] = SPA_END_OF_SIGNAL;

		return TRUE;
	}
}

//////////////////////////////////////////////////////////////////////////
BOOL CSignal::IsEmpty()
{
	if(m_lSize == 0) return TRUE;
	else return FALSE;
}

//////////////////////////////////////////////////////////////////////////
LONG CSignal::GetFrequency() const
{
	return m_lSampleFrequence;
}

//////////////////////////////////////////////////////////////////////////
VOID CSignal::SetFrequency(LONG in_Freq)
{
	m_lSampleFrequence = in_Freq;
}

//////////////////////////////////////////////////////////////////////////
SAMPLE CSignal::GetMinSample() 
{
	ASSERT(!IsEmpty());
	SAMPLE spMin = SHRT_MAX;
	for (LONG i=0; i<m_lSize; i++)
	{
		SAMPLE spTem = m_pSampleConsole[i];
		spMin = min(spMin, spTem);
	}

	return spMin;
}

//////////////////////////////////////////////////////////////////////////
SAMPLE CSignal::GetMaxSample()
{
	ASSERT(!IsEmpty());
	SAMPLE spMax = SHRT_MIN;
	for (LONG i=0; i<m_lSize; i++)
	{
		SAMPLE spTem = m_pSampleConsole[i];
		spMax = max(spMax, spTem);
	}

	return spMax;
}
//////////////////////////////////////////////////////////////////////////
VOID CSignal::Empty()
{
	
}
