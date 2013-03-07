// Hamming.cpp: implementation of the CHamming class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpectrumAnalysis.h"
#include "Hamming.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHamming::CHamming()
{
	m_iType = SPA_FIL_HAMMING;
	m_fa = SPA_HAMMING_A;
	m_fb = SPA_HAMMING_B;
}

CHamming::CHamming(DOUBLE in_a, DOUBLE in_b)
{
	m_iType = SPA_FIL_HAMMING;
	m_fa = in_a;
	m_fb = in_b;
}

CHamming::~CHamming()
{

}

//abcdefghiklmnopqrstuvwxyz
//////////////////////////////////////////////////////////////////////////
//main function
INT CHamming::DoFilter(CSignal& inout_pSignal)
{
	try 
	{
		LONG nSignalSize = inout_pSignal.GetSignalSize();
		LONG nN = nSignalSize/2;
		for(LONG i=0;i< nSignalSize; i++ )
		{
			DOUBLE dTemp = 
				inout_pSignal[i] * this->getHammingValue(i,nN);
		
			inout_pSignal[i] = (SAMPLE)dTemp;		
		}
	}
	catch(...)
	{
		return SPA_ERR_FILTERFAIL;
	}
	return SPA_NORMAL;
}

//this function used to get Hanning pulse  value
//from the signal  index and total of pulses
DOUBLE CHamming::getHammingValue(LONG in_n, LONG in_N)
{
	//out of window area
	if(in_n < 0 || in_n > 2*in_N )
	{
		return 0;
	}
	//in window area
	else
	{
		DOUBLE temp = ((in_n - in_N)*SPA_PI)/in_N ;
		return (2* m_fa *cos(temp) + m_fb);
	}
}