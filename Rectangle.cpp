// Rectangle.cpp: implementation of the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpectrumAnalysis.h"
#include "Rectangle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectangle::CRectangle()
{
	m_iType = SPA_FIL_RECTANGLE;
}

CRectangle::~CRectangle()
{

}

//////////////////////////////////////////////////////////////////////////
// main function 
DOUBLE CRectangle::getRectangleValue(LONG in_n, LONG in_N)
{
	if(in_n < 0 || in_n > 2*in_N)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

INT CRectangle::DoFilter(CSignal &inout_pSignal)
{
	try
	{
		LONG nSignalSize = inout_pSignal.GetSignalSize();
		LONG nN = nSignalSize/2;
		for(LONG i=0;i< nSignalSize; i++ )
		{
			DOUBLE dTemp = 
				inout_pSignal[i] * this->getRectangleValue(i,nN);
			inout_pSignal[i] = (SAMPLE)dTemp;
		}
	}
	catch(...)
	{
		return SPA_ERR_FILTERFAIL;
	}
	return SPA_NORMAL;
}
