// DisplaySpectrumSource.h: interface for the CDisplaySpectrumSource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPLAYSPECTRUMSOURCE_H__70809A8D_715F_4715_B41D_F968C9348E5A__INCLUDED_)
#define AFX_DISPLAYSPECTRUMSOURCE_H__70809A8D_715F_4715_B41D_F968C9348E5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DisplaySource.h"
#include "Signal.h"

class CDisplaySpectrumSource : public CDisplaySource  
{
public:
	INT AttachSource(CSignal* in_pSignal);
	virtual DOUBLE Fx(DOUBLE x);
	virtual INT InitSource();
	CDisplaySpectrumSource();
	CDisplaySpectrumSource(CSignal* in_pSignal);
	virtual ~CDisplaySpectrumSource();
	CSignal* m_pSpectrum;

private:
	
};

typedef CDisplaySpectrumSource CDSSpectrum;
#endif // !defined(AFX_DISPLAYSPECTRUMSOURCE_H__70809A8D_715F_4715_B41D_F968C9348E5A__INCLUDED_)
