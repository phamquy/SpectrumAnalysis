// DisplayWaveSource.h: interface for the CDisplayWaveSource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPLAYWAVESOURCE_H__7E73580F_14EF_406A_9BF5_289B06C7102F__INCLUDED_)
#define AFX_DISPLAYWAVESOURCE_H__7E73580F_14EF_406A_9BF5_289B06C7102F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DisplaySource.h"
#include "Wave.h"
#include "common.h"	// Added by ClassView

class CDisplayWaveSource : public CDisplaySource  
{
public:
	virtual DOUBLE Fx(DOUBLE x);
	
	INT AttachSource(CWave* in_pWave);
	virtual INT InitSource();
	CDisplayWaveSource();
	CDisplayWaveSource(CWave* pWave);
	virtual ~CDisplayWaveSource();
	CWave* m_pWaveSource;
	DOUBLE SampleToPercent(SAMPLE in_spSam);

	
};

typedef CDisplayWaveSource CDSWave;

#endif // !defined(AFX_DISPLAYWAVESOURCE_H__7E73580F_14EF_406A_9BF5_289B06C7102F__INCLUDED_)
