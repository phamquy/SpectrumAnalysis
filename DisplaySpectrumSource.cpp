// DisplaySpectrumSource.cpp: implementation of the CDisplaySpectrumSource class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpectrumAnalysis.h"
#include "DisplaySpectrumSource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDisplaySpectrumSource::CDisplaySpectrumSource()
{
	m_pSpectrum = NULL;
}

CDisplaySpectrumSource::CDisplaySpectrumSource(CSignal* in_pSignal)
{
	AttachSource(in_pSignal);
	InitSource();
}

CDisplaySpectrumSource::~CDisplaySpectrumSource()
{

}

INT CDisplaySpectrumSource::InitSource()
{
	if(m_pSpectrum == NULL) return SPA_ERR_INVALID_DPSOURCE;
	
	//set FXaxis dB
	SetFXName(SPA_AXIS_UNIT_DB);
	SetFXUnitVal(SPA_DECIBEN_UNIT);
	SetFXMax(m_pSpectrum->GetMaxSample());
	SetFXMin(m_pSpectrum->GetMinSample());

	//set Xaxis Hz
	SetXName(SPA_AXIS_UNIT_HZ);
	SetXUnitVal(SPA_HZ_UNIT);
	SetXMin(0);
	DOUBLE dMax = 0.5 * m_pSpectrum->GetFrequency();
	SetXMax(dMax);
	
	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
// return the spectrum sample value at specified frequence
// x: frequency (Hz)
// Fx: Amplitude (dB)
DOUBLE CDisplaySpectrumSource::Fx(DOUBLE x)
{
	LONG lSignalSize = m_pSpectrum->GetSignalSize() ;
	DOUBLE pos = (x * (DOUBLE)lSignalSize) / (DOUBLE)m_pSpectrum->GetFrequency();
	SAMPLE	retVal = (*m_pSpectrum)[(LONG)pos];
	return retVal;
}

//////////////////////////////////////////////////////////////////////////
INT CDisplaySpectrumSource::AttachSource(CSignal *in_pSignal)
{
	m_pSpectrum = in_pSignal;
	m_spMax = in_pSignal->GetMaxSample();
	m_spMin = in_pSignal->GetMinSample();
	return SPA_NORMAL;
}


