// DisplaySource.cpp: implementation of the CDisplaySource class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpectrumAnalysis.h"
#include "DisplaySource.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDisplaySource::CDisplaySource()
{
	m_msX.lMaxVal = 0;
	m_msX.lMinVal = 0;
	m_msX.lUnitVal = 0;
	m_msX.sUnitName = "";

	m_msFX.lMaxVal = 0;
	m_msFX.lMinVal = 0;
	m_msFX.lUnitVal = 0;
	m_msFX.sUnitName = "";
}

CDisplaySource::~CDisplaySource()
{

}
