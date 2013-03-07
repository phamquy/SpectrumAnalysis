// SpectrumAnalysis.h : main header file for the SPECTRUMANALYSIS application
//

#if !defined(AFX_SPECTRUMANALYSIS_H__E962F023_A4DE_49FB_A7C1_3438FD11C02B__INCLUDED_)
#define AFX_SPECTRUMANALYSIS_H__E962F023_A4DE_49FB_A7C1_3438FD11C02B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpectrumAnalysisApp:
// See SpectrumAnalysis.cpp for the implementation of this class
//

class CSpectrumAnalysisApp : public CWinApp
{
public:
	CSpectrumAnalysisApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpectrumAnalysisApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSpectrumAnalysisApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECTRUMANALYSIS_H__E962F023_A4DE_49FB_A7C1_3438FD11C02B__INCLUDED_)
