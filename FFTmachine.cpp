// FFTmachine.cpp: implementation of the CFFTmachine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpectrumAnalysis.h"
#include "FFTmachine.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFFTmachine::CFFTmachine()
{
	m_iFFTSize = 0;
	m_iFFTExp = 0;
	m_pComplexSignal = NULL;
}

CFFTmachine::~CFFTmachine()
{
	if(m_pComplexSignal != NULL) 
		delete [] m_pComplexSignal;
	m_pComplexSignal = NULL;
}

//////////////////////////////////////////////////////////////////////////
LONG CFFTmachine::GetFFTSize()
{
	return m_iFFTSize;
}

//////////////////////////////////////////////////////////////////////////
BOOL CFFTmachine::SetFFTSize(LONG in_iSize)
{
	INT nTemp;
	INT nExp;

	nExp = 0;
	nTemp = 1;

	//check if size is power of two
	while (nTemp < in_iSize)
	{
		nTemp = nTemp*2;
		nExp++;
	}

	if(nTemp != in_iSize)
	{
		return FALSE;
	}

	m_iFFTSize = in_iSize;
	m_iFFTExp = nExp;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//this function convert signal from integer to complex format
INT CFFTmachine::SetSignalSource(const CSignal *in_pSignal)
{
	m_pSignalSource = in_pSignal;

	LONG nSignalSize = in_pSignal->GetSignalSize();
	
	if(m_iFFTSize == 0)
	{
		return SPA_ERR_INVALID_FFTSIZE;
	}

	if(nSignalSize == m_iFFTSize)
	{
		INT i;
		if(m_pComplexSignal != NULL) 
		{
			delete [] m_pComplexSignal;
			m_pComplexSignal = NULL;
		}

		m_pComplexSignal = new COMPLEX[m_iFFTSize];
		
		if(m_pComplexSignal == NULL)
		{
			return SPA_ERR_MEMORY;
		}
		
		for (i=0; i< m_iFFTSize; i++)
		{
			SAMPLE stest = (*in_pSignal)[i];

			m_pComplexSignal[i].dReal  = (((DOUBLE)(*in_pSignal)[i])/SHRT_MAX);
			DOUBLE dtest  = m_pComplexSignal[i].dReal;

			m_pComplexSignal[i].dImage = 0;
		}
	}
	else //this case is impossible, 
	{
		TRACE("Size of signal and FFT is not equal");
		ASSERT(FALSE);
		return	SPA_ERR_INVALID_SCHEME;
	}

	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
//this function initialize the 
INT CFFTmachine::InitMachine(const CSignal *in_pSignal, LONG in_iFFTSize)
{
	//set size of FFT transform
	if(!SetFFTSize(in_iFFTSize))
	{
		return SPA_ERR_INVALID_FFTSIZE;
	}
	
	//compatiblize the input signal
	INT retCode = SetSignalSource(in_pSignal);
	
	if (retCode != SPA_NORMAL)
	{
		return retCode;
	}
	
	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
//FFT process function
/*
	input:
		m_iFFTSize: size of FFT transform
		m_iFFTExp:	Exponent of FFT (m_iFFTSize = 2^m_iFFTExp)

	input/output
		m_pComplexSignal: array complex sample
*/	
INT CFFTmachine::RunFFT(INT in_Direct)
{
	if(m_iFFTSize == 0) return SPA_ERR_INVALID_FFTSIZE;
	if(m_pComplexSignal == NULL) return SPA_ERR_FFTINIT_FAIL;

	int i,j,k,n1,n2;
	double c,s,e,a,t1,t2;

	if(m_iFFTSize == 0) return SPA_ERR_INVALID_FFTSIZE;
	if(m_pComplexSignal == NULL) return SPA_ERR_FFTINIT_FAIL;

	/* bit-reverse */
	j = 0; 
	n2 = m_iFFTSize/2;

	for (i=1; i < m_iFFTSize-1; i++)
	{
		n1 = n2;
		while ( j >= n1 )
		{
			j = j - n1;
			n1 = n1/2;
		}
		
		j = j + n1;
		if (i < j)
		{
			t1 = m_pComplexSignal[i].dReal;
			m_pComplexSignal[i].dReal = m_pComplexSignal[j].dReal;
			m_pComplexSignal[j].dReal = t1;

			t1 = m_pComplexSignal[i].dImage;
			m_pComplexSignal[i].dImage = m_pComplexSignal[j].dImage;
			m_pComplexSignal[i].dImage = t1;
		}
	}

	/* FFT */
	n1 = 0; 
	n2 = 1;
	for (i = 0; i < m_iFFTExp; i++)
	{
		n1 = n2;
		n2 = n2 + n2;
		
		e = -(2*SPA_PI)/n2;
		a = 0.0;
		for (j=0; j < n1; j++)
		{
			c = cos(a);
			s = sin(a);
			a = a + e;
			for (k=j; k < m_iFFTSize; k=k+n2)
			{
				t1 = c*m_pComplexSignal[k+n1].dReal - s*m_pComplexSignal[k+n1].dImage;
				t2 = s*m_pComplexSignal[k+n1].dReal + c*m_pComplexSignal[k+n1].dImage;
				m_pComplexSignal[k+n1].dReal = m_pComplexSignal[k].dReal - t1;
				m_pComplexSignal[k+n1].dImage = m_pComplexSignal[k].dImage - t2;
				m_pComplexSignal[k].dReal = m_pComplexSignal[k].dReal + t1;
				m_pComplexSignal[k].dImage = m_pComplexSignal[k].dImage + t2;
			}
		}
	}

	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
INT CFFTmachine::GetFFTExp()
{
	return m_iFFTExp;
}

//////////////////////////////////////////////////////////////////////////
//this function return the spectrum result in signal form
INT CFFTmachine::GetSpectrum(CSignal& out_pSignal)
{
	CSignal oTemp = CSignal(m_iFFTSize);
	oTemp.SetFrequency(m_pSignalSource->GetFrequency());
	INT i;

	for(i=0; i< m_iFFTSize; i++)
	{
	 	DOUBLE s = m_pComplexSignal[i].dReal;
	 	DOUBLE t = fabs(m_pComplexSignal[i].dReal);

	 	DOUBLE specVal = 20 * log10(fabs(m_pComplexSignal[i].dReal));
	 	oTemp[i] = (SAMPLE) specVal;        
	}

	out_pSignal = oTemp;
	
	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
VOID CFFTmachine::ResetMachine()
{
	m_pSignalSource = 0;
	m_iFFTSize = 0;
	m_iFFTExp = 0;
	if(m_pComplexSignal != NULL) 
		delete [] m_pComplexSignal;
	m_pComplexSignal = NULL;
}
