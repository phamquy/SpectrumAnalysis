// Hanning.cpp: implementation of the CHanning class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpectrumAnalysis.h"
#include "Hanning.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHanning::CHanning()
{
	m_iType = SPA_FIL_HANNING;
}

CHanning::~CHanning()
{

}


//////////////////////////////////////////////////////////////////////////
// main function
INT CHanning::DoFilter(CSignal &inout_pSignal)
{
	try
	{
		LONG nSignalSize = inout_pSignal.GetSignalSize();
		LONG nN = nSignalSize/2;
		for(LONG i=0;i< nSignalSize; i++ )
		{
			DOUBLE dTemp = 
				inout_pSignal[i] * this->getHanningValue(i,nN);
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
//from the signal  index and total of pulse
DOUBLE CHanning::getHanningValue(LONG in_n, LONG in_N)
{
	//out of window area
	if(in_n < 0 || in_n > 2*in_N )
	{
		return 0;
	}
	//in window area
	else
	{
		DOUBLE temp = ((in_n-in_N)*SPA_PI)/(in_N+1);
		return (0.5*cos(temp)+0.5);
	}
}

