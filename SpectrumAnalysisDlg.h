// SpectrumAnalysisDlg.h : header file
//

#if !defined(AFX_SPECTRUMANALYSISDLG_H__108B74C7_B142_4D47_AEBD_8D5D22DD561A__INCLUDED_)
#define AFX_SPECTRUMANALYSISDLG_H__108B74C7_B142_4D47_AEBD_8D5D22DD561A__INCLUDED_

#include "DisplayPanel.h"	// Added by ClassView
#include "Wave.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FFTmachine.h"
#include "Signal.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CSpectrumAnalysisDlg dialog

class CSpectrumAnalysisDlg : public CDialog
{
// Construction
public:
	CSpectrumAnalysisDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSpectrumAnalysisDlg)
	enum { IDD = IDD_SPECTRUMANALYSIS_DIALOG };
	CButton	m_cmdAnalysis;
	CComboBox	m_cbWindow;
	CComboBox	m_cbFFTSize;
	CButton	m_frmFFT;
	CStatic	m_lblFFTsize;
	CStatic	m_lblWindow;
	CButton	m_cmdPlay;
	CStatic	m_lblBps;
	CStatic	m_lblChannel;
	CStatic	m_lblFreq;
	CStatic	m_lblTime;
	CButton	m_frmFileInfo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpectrumAnalysisDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL updateComboData(BOOL in_bool = TRUE);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSpectrumAnalysisDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnHelpAbout();
	afx_msg void OnFileClose();
	afx_msg void OnFileOpen();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAnalysis();
	afx_msg void OnPlay();
	afx_msg void OnCancel();
	afx_msg void OnExit();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bConsole1;
	BOOL m_bConsole2;
	BOOL m_bSelected;

	INT m_iConsoleStatus;
	CPoint m_ptOldMouseMove;
	CPoint m_ptConsole2;
	CPoint m_ptConsole1;
	RECT getConsoleValidateRect(INT in_Pos);
	VOID display(CDC* pDC);
	BOOL getSpecSource();
	BOOL getWaveSegment();
	BOOL runFFTmachine();
	VOID setWaveConsole(INT in_con1, INT in_con2);
	BOOL loadWaveFile(CString in_sFileName);
	VOID updateControlStatus();
	VOID initSource();
	INT m_iStatus;
	INT m_iWindow;
	INT m_iFFTsize;
	INT m_iConsole2;
	INT m_iConsole1;
	CSignal m_oSpecSource;
	CSignal m_oWaveSegment;
	VOID initPanel();
	VOID initControl();
	CDisplayPanel m_oSpectrumPanel;
	CDisplayPanel m_oWavePanel;
	CWave m_oWave;
	CFFTmachine m_oFFTMachine;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECTRUMANALYSISDLG_H__108B74C7_B142_4D47_AEBD_8D5D22DD561A__INCLUDED_)
