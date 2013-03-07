// Filter.cpp: implementation of the CFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpectrumAnalysis.h"
#include "Filter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFilter::CFilter()
{

}

CFilter::~CFilter()
{

}


//return the type of filter
UINT CFilter::GetFilterType() const
{
	return m_iType;
}


//set type of the filter
VOID CFilter::SetFilterType(UINT in_iType)
{
	m_iType = in_iType;
}


//virtual function, execute the filter fuction
INT CFilter::DoFilter(CSignal &in_pSignal)
{
	ASSERT("METHOD IS NOT IMPLEMETED!");
	return SPA_ERR_NOTIMPLEMENT;
}


