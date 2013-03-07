// DisplayWaveSource.cpp: implementation of the CDisplayWaveSource class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpectrumAnalysis.h"
#include "DisplayWaveSource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDisplayWaveSource::CDisplayWaveSource()
{
	m_pWaveSource = NULL;
}

CDisplayWaveSource::CDisplayWaveSource(CWave* in_pWave)
{
	AttachSource(in_pWave);
	InitSource();
}

CDisplayWaveSource::~CDisplayWaveSource()
{

}

//////////////////////////////////////////////////////////////////////////
// this function calculate the max/min value of time and sample value
INT CDisplayWaveSource::InitSource()
{
	if(m_pWaveSource == NULL) return SPA_ERR_INVALID_DPSOURCE;

	DOUBLE lTotalTime = m_pWaveSource->GetTotalTime();
	SetXName(SPA_AXIS_UNIT_MS);
	SetXMax(lTotalTime);
	SetXMin(0);
	SetXUnitVal(m_pWaveSource->GetSampleCycle());
	
	SetFXName(SPA_AXIS_UNIT_PERCENT);
	SetFXMax(100);
	SetFXMin(-100);
	SetFXUnitVal(1);
	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
INT CDisplayWaveSource::AttachSource(CWave *in_pWave)
{
	m_pWaveSource = in_pWave;
	m_spMax = m_pWaveSource->GetMaxSample(); 
	m_spMin = m_pWaveSource->GetMinSample();
	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
DOUBLE CDisplayWaveSource::SampleToPercent(SAMPLE in_spSam)
{
	DOUBLE ret = 0;

	if(in_spSam >= 0)
	{		
		ret =  ((DOUBLE)in_spSam / SHRT_MAX);
	}
	else //if(in_spSam < 0)
	{
		ret = ((DOUBLE) in_spSam / SHRT_MAX);
	}

	ret = ret * 100;
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// return the sample value at specified time
// x: time (ms)
// Fx: %Sample (%)
DOUBLE CDisplayWaveSource::Fx(DOUBLE x)
{
	if(x<0) return 0;

	DOUBLE dTcycle = m_pWaveSource->GetSampleCycle();
	LONG lSamplePos = (LONG)(x / dTcycle);
	SAMPLE spSam = m_pWaveSource->GetSampleAt(lSamplePos);

	return SampleToPercent(spSam);
}
