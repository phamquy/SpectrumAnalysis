// SpectrumAnalysisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpectrumAnalysis.h"
#include "SpectrumAnalysisDlg.h"

#include "Signal.h"
#include "Hanning.h"
#include "Hamming.h"
#include "Rectangle.h"

//test include 
#include "Axis.h"
#include "DisplayPanel.h"
#include "DisplayWaveSource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


VOID SPA_ShowMessage(INT errCode)
{
	//CString str;	
	//AfxMessageBox(str);
}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpectrumAnalysisDlg dialog

CSpectrumAnalysisDlg::CSpectrumAnalysisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpectrumAnalysisDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpectrumAnalysisDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpectrumAnalysisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpectrumAnalysisDlg)
	DDX_Control(pDX, IDC_CMD_ANALYSIS, m_cmdAnalysis);
	DDX_Control(pDX, IDC_CB_WINDOW, m_cbWindow);
	DDX_Control(pDX, IDC_CB_FFTSIZE, m_cbFFTSize);
	DDX_Control(pDX, IDC_FRAME_FFT, m_frmFFT);
	DDX_Control(pDX, IDC_LB_FFTSIZE, m_lblFFTsize);
	DDX_Control(pDX, IDC_LB_WINDOW, m_lblWindow);
	DDX_Control(pDX, IDC_CMD_PLAY, m_cmdPlay);
	DDX_Control(pDX, IDC_LB_BPS, m_lblBps);
	DDX_Control(pDX, IDC_LB_CHANEL, m_lblChannel);
	DDX_Control(pDX, IDC_LB_FREQ, m_lblFreq);
	DDX_Control(pDX, IDC_LB_TIME, m_lblTime);
	DDX_Control(pDX, IDC_FRAME_FINFO, m_frmFileInfo);
	
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSpectrumAnalysisDlg, CDialog)
	//{{AFX_MSG_MAP(CSpectrumAnalysisDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_FILE_ANALYSIS, OnAnalysis)
	ON_COMMAND(ID_FILE_PLAY, OnPlay)
	ON_COMMAND(ID_FILE_EXIT, OnExit)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CMD_ANALYSIS, OnAnalysis)
	ON_BN_CLICKED(IDC_CMD_PLAY, OnPlay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpectrumAnalysisDlg message handlers

BOOL CSpectrumAnalysisDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//init dialog pos
	WINDOWPLACEMENT wndPlacement;
	wndPlacement.length = sizeof(WINDOWPLACEMENT);
	wndPlacement.showCmd = SW_SHOWNORMAL;	
	wndPlacement.rcNormalPosition = CRect(SPA_DLG_X,SPA_DLG_Y,SPA_DLG_WIDTH,SPA_DLG_HEIGHT);
	SetWindowPlacement(&wndPlacement);

	//my init
	initControl();
	initPanel();
	initSource();
	

	m_iStatus = SPA_STATUS_INIT;
	updateControlStatus();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSpectrumAnalysisDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CSpectrumAnalysisDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		display(&dc);
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSpectrumAnalysisDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSpectrumAnalysisDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
}

//////////////////////////////////////////////////////////////////////////
void CSpectrumAnalysisDlg::OnHelpAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg  aboutDg;
	aboutDg.DoModal();
}

//////////////////////////////////////////////////////////////////////////
//this function init control indialog
VOID CSpectrumAnalysisDlg::initControl()
{
	CRect rcDlgClient;
	GetClientRect(&rcDlgClient);

	CPoint ptTopLeft;
	CPoint ptBottomRight;
	CRect rcCtlRect;

	ptTopLeft = rcDlgClient.TopLeft();
	ptTopLeft += CSize(SPA_DLG_BORDER + SPA_DLG_DP_WIDTH 
					+ SPA_DLG_DP_CTRL, SPA_DLG_BORDER);

	ptBottomRight.x = rcDlgClient.right - SPA_DLG_BORDER;
	ptBottomRight.y = rcDlgClient.top + SPA_DLG_BORDER 
									 + SPA_DLG_DP_HEIGHT;

	rcCtlRect.SetRect(ptTopLeft, ptBottomRight);

	//File infor frame
	m_frmFileInfo.SetWindowPos
	(
		&wndBottom, 
		ptTopLeft.x, 
		ptTopLeft.y, 
		rcCtlRect.Width(), 
		rcCtlRect.Height(),
		SWP_SHOWWINDOW
	);

	ptTopLeft.x += SPA_DLG_FRM_CX;

	ptTopLeft.y += SPA_DLG_FRM_CY;
	m_lblFreq.SetWindowPos
	(
		&wndTop, 
		ptTopLeft.x, 
		ptTopLeft.y,
		SPA_DLG_CTL_CX, 
		SPA_DLG_CTL_CY,
		SWP_SHOWWINDOW
	);
	
	ptTopLeft.y += SPA_DLG_CTL_CYSPACE;
	m_lblBps.SetWindowPos
	(
		&wndTop, 
		ptTopLeft.x, 
		ptTopLeft.y, 
		SPA_DLG_CTL_CX, 
		SPA_DLG_CTL_CY,
		SWP_SHOWWINDOW
	);
	
	ptTopLeft.y += SPA_DLG_CTL_CYSPACE;
	m_lblChannel.SetWindowPos
	(
		&wndTop, 
		ptTopLeft.x, 
		ptTopLeft.y, 
		SPA_DLG_CTL_CX, 
		SPA_DLG_CTL_CY,
		SWP_SHOWWINDOW
	);

	ptTopLeft.y += SPA_DLG_CTL_CYSPACE;
	m_lblTime.SetWindowPos
	(
		&wndTop, 
		ptTopLeft.x, 
		ptTopLeft.y, 
		SPA_DLG_CTL_CX, 
		SPA_DLG_CTL_CY + 5,
		SWP_SHOWWINDOW
	);

	ptTopLeft.y = rcDlgClient.top + SPA_DLG_PLAY_CYS;
	m_cmdPlay.SetWindowPos
	(
		&wndTop, 
		ptTopLeft.x, 
		ptTopLeft.y, 
		SPA_DLG_BTN_PLAY_CX, 
		SPA_DLG_BTN_PLAY_CY,
		SWP_SHOWWINDOW
	);
	
	//FFT FRame
	ptTopLeft.y = rcDlgClient.top + SPA_DLG_BORDER
					+ SPA_DLG_DP_HEIGHT + SPA_DLG_DP_SPACE;
	ptTopLeft.x -= SPA_DLG_FRM_CX;
	m_frmFFT.SetWindowPos
	(
		&wndBottom, 
		ptTopLeft.x, 
		ptTopLeft.y, 
		rcCtlRect.Width(), 
		rcCtlRect.Height(),
		SWP_SHOWWINDOW
	);

	ptTopLeft.x += SPA_DLG_FRM_CX;

	ptTopLeft.y += SPA_DLG_FRM_CY;
	m_lblFFTsize.SetWindowPos
	(
		&wndTop, 
		ptTopLeft.x, 
		ptTopLeft.y,
		SPA_DLG_CTL_CX, 
		SPA_DLG_CTL_CY,
		SWP_SHOWWINDOW
	);

	ptTopLeft.y += SPA_DLG_CTL_CYSPACE;
	m_cbFFTSize.SetWindowPos
	(
		&wndTop, 
		ptTopLeft.x, 
		ptTopLeft.y-5, 
		SPA_DLG_CTL_CX, 
		SPA_DLG_CTL_CY,
		SWP_SHOWWINDOW
	);
	m_cbFFTSize.SetCurSel(2);

	ptTopLeft.y += SPA_DLG_CTL_CYSPACE;
	m_lblWindow.SetWindowPos
	(
		&wndTop, 
		ptTopLeft.x, 
		ptTopLeft.y, 
		SPA_DLG_CTL_CX, 
		SPA_DLG_CTL_CY,
		SWP_SHOWWINDOW
	);

	ptTopLeft.y += SPA_DLG_CTL_CYSPACE;
	m_cbWindow.SetWindowPos
	(
		&wndTop, 
		ptTopLeft.x, 
		ptTopLeft.y-5, 
		SPA_DLG_CTL_CX, 
		SPA_DLG_CTL_CY+100,
		SWP_SHOWWINDOW
	);
	m_cbWindow.AddString(SPA_WINDOW_HAN);
	m_cbWindow.AddString(SPA_WINDOW_HAM);
	m_cbWindow.AddString(SPA_WINDOW_REC);
	m_cbWindow.SetCurSel(0);
	
	ptTopLeft.y += 75;
	m_cmdAnalysis.SetWindowPos
	(
		&wndTop, 
		ptTopLeft.x, 
		ptTopLeft.y, 
		SPA_DLG_BTN_PLAY_CX, 
		SPA_DLG_BTN_PLAY_CY,
		SWP_SHOWWINDOW
	);

	CMenu* pMnu = GetSystemMenu(FALSE);
}

//////////////////////////////////////////////////////////////////////////
// init 2 display panel
VOID CSpectrumAnalysisDlg::initPanel()
{
	CRect rcDlgClient;
	GetClientRect(&rcDlgClient);

	CRect rcDisplayRect;
	CPoint ptTopLeft;
	CPoint ptBottomRight;

	//set wave panel's frame rect
	ptTopLeft = rcDlgClient.TopLeft();
	ptTopLeft += CSize(SPA_DLG_BORDER,SPA_DLG_BORDER);
	ptBottomRight = ptTopLeft + CSize(SPA_DLG_DP_WIDTH, SPA_DLG_DP_HEIGHT);
	rcDisplayRect.SetRect(ptTopLeft, ptBottomRight);
	rcDisplayRect.NormalizeRect();
	m_oWavePanel.SetDisplayFrame(rcDisplayRect);
	m_oWavePanel.TurnOff();
	
	//set spectrum panel's frame rect
	ptTopLeft += CSize(0, SPA_DLG_DP_HEIGHT + SPA_DLG_DP_SPACE);
	ptBottomRight = ptTopLeft + CSize(SPA_DLG_DP_WIDTH, SPA_DLG_DP_HEIGHT);
	rcDisplayRect.SetRect(ptTopLeft, ptBottomRight);
	rcDisplayRect.NormalizeRect();
	m_oSpectrumPanel.SetDisplayFrame(rcDisplayRect);
	m_oSpectrumPanel.TurnOff();
	
}

//////////////////////////////////////////////////////////////////////////
VOID CSpectrumAnalysisDlg::initSource()
{
	m_iConsole1 = 0;
	m_bConsole1 = FALSE;
	
	m_iConsole2 = 0;
	m_bConsole1 = FALSE;
	
	m_bSelected = FALSE;

	m_iConsoleStatus = SPA_NOCONSOLE;

}

//////////////////////////////////////////////////////////////////////////
void CSpectrumAnalysisDlg::OnFileClose() 
{
	// TODO: Add your command handler code here
	m_oSpectrumPanel.TurnOff();
	m_oWavePanel.TurnOff();
	m_oWave.ResetData();
	m_oFFTMachine.ResetMachine();

	m_iStatus = SPA_STATUS_INIT;
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
void CSpectrumAnalysisDlg::OnFileOpen() 
{
	// TODO: Add your command handler code here
	INT ret = SPA_NORMAL;
	CFileDialog oFile(TRUE);

	//if user cancel file selection
	if(oFile.DoModal() != IDOK)	return;

	//if the user choose an wave file
	CString sFileName = oFile.GetPathName();
	if(!loadWaveFile(sFileName)) 
	{
		MessageBox("Can not load wave file:\n" + sFileName);
		return;
	}	
	setWaveConsole(0,0);
		
	if(!getWaveSegment()) 
	{
		MessageBox("You select invalid segment!");
		return;
	}

	
	if(!updateComboData())
	{
		MessageBox("Please select again!");
		return;
	}

	if(!getSpecSource()) 
	{
		MessageBox("You select invalid segment!");
		return;
	}
	
	initSource();

	m_oSpectrumPanel.TurnOn();
	m_oWavePanel.TurnOn();
	m_iStatus = SPA_STATUS_LOADED;
	
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
void CSpectrumAnalysisDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_iStatus == SPA_STATUS_INIT) return;

	if(m_oWavePanel.IsOnPanel(point))
	{
		CRect rcFrame = m_oWavePanel.GetClientRect();
		CRect rcValidate;
	INT left;
	INT right;
		switch(m_iConsoleStatus) 
		{
		case SPA_NOCONSOLE:
			m_iConsole1 = point.x - rcFrame.left;
			m_ptConsole1 = point;
			m_bConsole1 = TRUE;

			m_iConsole2 = point.x - rcFrame.left;
			m_ptConsole2 = point;
		
			m_iConsoleStatus = SPA_CONSOLE1;
			rcValidate = getConsoleValidateRect(m_iConsole1);			
			InvalidateRect(&rcValidate);
			break;
		
		case SPA_CONSOLE1:
			m_iConsole2 = point.x - rcFrame.left;
			m_ptConsole2 = point;
			m_bConsole2 = TRUE;
			m_iConsoleStatus = SPA_CONSOLE2;

			left = min(min(m_ptConsole1.x, m_ptConsole2.x), point.x);
			right = max(max(m_ptConsole1.x, m_ptConsole2.x), point.x);
			rcValidate = CRect(left, rcFrame.top, right,rcFrame.bottom);
			rcValidate.InflateRect(1,1);

			InvalidateRect(&rcValidate);
			break;
		
		case SPA_CONSOLE2:			
			left = min(min(m_ptConsole1.x, m_ptConsole2.x), point.x);
			right = max(max(m_ptConsole1.x, m_ptConsole2.x), point.x);
			rcValidate = CRect(left, rcFrame.top, right,rcFrame.bottom);
			rcValidate.InflateRect(1,1);
			m_iConsole1 = point.x - rcFrame.left;
			m_ptConsole1 = point;
			m_bConsole1 = TRUE;

			m_iConsole2 = point.x - rcFrame.left;
			m_ptConsole2 = point;
			
			m_iConsoleStatus = SPA_CONSOLE1;
			InvalidateRect(rcValidate);
			break;
		}
	}
	CDialog::OnLButtonDown(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////
BOOL CSpectrumAnalysisDlg::updateComboData(BOOL in_bool)
{	
	UpdateData(in_bool);
	if(in_bool)
	{
		INT i = m_cbFFTSize.GetCurSel();
		if(i<0) 
		{
			MessageBox("You have to select \ncorrect FFT's Size");
			return FALSE;
		}
		CString str;

		INT n = m_cbFFTSize.GetLBTextLen(i);
		m_cbFFTSize.GetLBText( i, str.GetBuffer(n) );
		str.ReleaseBuffer();
		m_iFFTsize = atoi(str.GetBuffer(0));
		str.ReleaseBuffer();

		i = m_cbWindow.GetCurSel();
		if(i<0) 
		{
			MessageBox("You have to select \ncorrect window");
			return FALSE;
		}

		n = m_cbWindow.GetLBTextLen(i);
		m_cbWindow.GetLBText( i, str.GetBuffer(n) );
		str.ReleaseBuffer();
		
		if(!str.CompareNoCase(SPA_WINDOW_HAM))		
			m_iWindow = SPA_WINDOW_HAM_IDX;
		else if(!str.CompareNoCase(SPA_WINDOW_HAN))
			m_iWindow = SPA_WINDOW_HAN_IDX;
		else
			m_iWindow = SPA_WINDOW_REC_IDX;

	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
VOID CSpectrumAnalysisDlg::updateControlStatus()
{
	CMenu* pMain = GetMenu();
	CMenu* pFileMenu = pMain->GetSubMenu(0);

	switch(m_iStatus) 
	{
	case SPA_STATUS_INIT:		
		m_cmdPlay.EnableWindow(FALSE);
		pFileMenu->EnableMenuItem(SPA_MNU_PLAY, SPA_MNU_DISABLE);		
		m_cmdAnalysis.EnableWindow(FALSE);
		pFileMenu->EnableMenuItem(SPA_MNU_ANALYSIS, SPA_MNU_DISABLE);
		pFileMenu->EnableMenuItem(SPA_MNU_CLOSE, SPA_MNU_DISABLE);
		break;

	case SPA_STATUS_LOADED:
		m_cmdPlay.EnableWindow(TRUE);
		pFileMenu->EnableMenuItem(SPA_MNU_PLAY, SPA_MNU_ENABLE);		
		m_cmdAnalysis.EnableWindow(TRUE);
		pFileMenu->EnableMenuItem(SPA_MNU_ANALYSIS, SPA_MNU_ENABLE);
		pFileMenu->EnableMenuItem(SPA_MNU_CLOSE, SPA_MNU_ENABLE);
		break;

	default:
		ASSERT(0);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
void CSpectrumAnalysisDlg::OnAnalysis() 
{
	// TODO: Add your command handler code here
	if(!updateComboData())
	{
		MessageBox("Please select again!");
		return;
	}

	if(!getWaveSegment()) 
	{
		MessageBox("You select invalid segment!");
		return;
	}

	if(!getSpecSource()) 
	{
		MessageBox("You select invalid segment!");
		return;
	}

	m_oSpectrumPanel.TurnOn();
	InvalidateRect(SPA_DLG_SPEC,TRUE);	
}

//////////////////////////////////////////////////////////////////////////
void CSpectrumAnalysisDlg::OnPlay() 
{
	// TODO: Add your command handler code here	
	if(m_iConsole1 == m_iConsole2)
	{
		if(m_oWave.Play() != SPA_NORMAL)
		{
			MessageBox("Can not play wave file!");
			return;
		}
	}
	else
	{
		LONG maxCons = min(m_iConsole1, m_iConsole2);
		DOUBLE timePos = m_oWavePanel.GetXval(maxCons);
		LONG iWaveStart = m_oWave.GetIndexOfTime(timePos);
		if(!getWaveSegment())
		{
			MessageBox("You select invalid segment!");
			return;
		}
		LONG waveLength = m_oWaveSegment.GetSignalSize();
		if(m_oWave.Play(iWaveStart,waveLength) != SPA_NORMAL)
		{
			MessageBox("Can not play wave file!");
			return;
		}
	}
}

void CSpectrumAnalysisDlg::OnCancel() 
{

}

//////////////////////////////////////////////////////////////////////////
void CSpectrumAnalysisDlg::OnExit() 
{
	// TODO: Add your command handler code here

	OnOK();
}

//////////////////////////////////////////////////////////////////////////
void CSpectrumAnalysisDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default	
	
	OnOK();
	CDialog::OnClose();
}

//////////////////////////////////////////////////////////////////////////
BOOL CSpectrumAnalysisDlg::loadWaveFile(CString in_sFileName)
{
	m_oWave.SetFileName(in_sFileName);
	INT iRetCode = m_oWave.InitInstance();

	if(iRetCode != SPA_NORMAL) 
	{
		SPA_ShowMessage(iRetCode);
		m_oWave.ResetData();
		return FALSE;
	}

	LONG lTotalTime = m_oWave.GetTotalTime();
	CString sNew;
	sNew.Format("%d", lTotalTime);
	sNew = SPA_LBL_TOTALTIME  + sNew + SPA_AXIS_UNIT_MS;
	m_lblTime.SetWindowText((LPCTSTR) sNew);
	m_oWavePanel.AttachSource(&m_oWave);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
VOID CSpectrumAnalysisDlg::setWaveConsole(INT in_con1, INT in_con2)
{
	if(in_con1<0) 
		m_iConsole1 = 0;
	else if(in_con1 > SPA_DLG_DP_WIDTH)
		m_iConsole1 = SPA_DLG_DP_WIDTH;
	else m_iConsole1 = in_con1;

	if(in_con2<0) 
		m_iConsole2 = 0;
	else if(in_con2 > SPA_DLG_DP_WIDTH)
		m_iConsole2 = SPA_DLG_DP_WIDTH;
	else m_iConsole2 = in_con2;
}

//////////////////////////////////////////////////////////////////////////
// input: console1-2, FFTsize, Window, WaveFile, FFTmachine
//	| oSCHEME, oWaveSegment, 
// output: m_oSpecSource, m_oSpecPanel, 
BOOL CSpectrumAnalysisDlg::runFFTmachine()
{
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//input console1-2, m_oWave, m_oWavePanel
//output: segment of wave
BOOL CSpectrumAnalysisDlg::getWaveSegment()
{
	DOUBLE timePos1 = m_oWavePanel.GetXval(m_iConsole1);
	DOUBLE timePos2 = m_oWavePanel.GetXval(m_iConsole2);

	LONG iWaveIdx1 = m_oWave.GetIndexOfTime(timePos1);
	LONG iWaveIdx2 = m_oWave.GetIndexOfTime(timePos2);

	if(iWaveIdx2 >= m_oWave.GetNumOfSample()) iWaveIdx2 = m_oWave.GetNumOfSample();
	if(iWaveIdx2 < 0 ) iWaveIdx2 = 0 ;
	if(iWaveIdx1 >= m_oWave.GetNumOfSample()) iWaveIdx1 = m_oWave.GetNumOfSample();
	if(iWaveIdx1 < 0 ) iWaveIdx1 = 0;

	if (iWaveIdx1 == iWaveIdx2)	
	{
		if(iWaveIdx2 == (m_oWave.GetNumOfSample()-1))
			iWaveIdx1 = 0;	
		
		if(iWaveIdx1 == 0)
			iWaveIdx2 = m_oWave.GetNumOfSample()-1; 
	}

	LONG lTemp = iWaveIdx1;
	iWaveIdx1 = min(iWaveIdx1, iWaveIdx2);
	iWaveIdx2 = max(lTemp, iWaveIdx2);
	LONG iSegmentLength = iWaveIdx2 - iWaveIdx1 + 1;

	SLS schSegment;
	schSegment.nStart = iWaveIdx1;
	schSegment.nLength = iSegmentLength;
	schSegment.nStep = 1;
	
	INT ret = m_oWave.GetSignal(schSegment, m_oWaveSegment);
	if(ret != SPA_NORMAL) 
	{
		SPA_ShowMessage(ret);
		return FALSE;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL CSpectrumAnalysisDlg::getSpecSource()
{
	//check wave segment
	if(m_oWaveSegment.IsEmpty()) return FALSE;
	LONG iSegSize = m_oWaveSegment.GetSignalSize();


	CSignal oSignal(m_iFFTsize, m_oWaveSegment.GetFrequency());
	CFilter* pFilter;
	if(m_iFFTsize > iSegSize)
	{		
		for (INT i=0; i< iSegSize; i++) 
		{
			oSignal[i] = m_oWaveSegment[i];				
		}		
	}
	else //if(m_iFFTsize <= iSegSize)
	{		
		for (INT i=0; i< m_iFFTsize; i++) 
		{
			oSignal[i] = m_oWaveSegment[i];				
		}
	}
	
	switch(m_iWindow) 
	{
	case SPA_WINDOW_HAM_IDX:
		pFilter = new CHamming();
		break;

	case SPA_WINDOW_HAN_IDX:
		pFilter = new CHanning();
		break;

	case SPA_WINDOW_REC_IDX:
		pFilter = new CRectangle();
		break;
	}

	pFilter->DoFilter(oSignal);
	m_oFFTMachine.InitMachine(&oSignal, oSignal.GetSignalSize());
	m_oFFTMachine.RunFFT(SPA_FFT_COMMON);
	m_oFFTMachine.GetSpectrum(m_oSpecSource);
	m_oSpectrumPanel.AttachSource(&m_oSpecSource);

	delete pFilter;
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
VOID CSpectrumAnalysisDlg::display(CDC* pDC)
{

		m_oSpectrumPanel.m_pDC = pDC;
		m_oSpectrumPanel.DrawDisplayPanel();
		m_oSpectrumPanel.Display();
		
		m_oWavePanel.m_pDC = pDC;
		m_oWavePanel.DrawDisplayPanel();
		m_oWavePanel.Display();

		if(m_iStatus == SPA_STATUS_LOADED)
		{
			switch(m_iConsoleStatus) 
			{
			case SPA_NOCONSOLE:
				break;

			case SPA_CONSOLE1:
				m_oWavePanel.DrawConsole(m_ptConsole1);
				break;

			case SPA_CONSOLE2:
				m_oWavePanel.DrawConsole(m_ptConsole1);
				m_oWavePanel.DrawConsole(m_ptConsole2);
				m_oWavePanel.DrawSelectMask(m_ptConsole1 ,m_ptConsole2);
				break;	
			}
		}
		updateControlStatus();
}

//////////////////////////////////////////////////////////////////////////
RECT CSpectrumAnalysisDlg::getConsoleValidateRect(INT in_Pos)
{
	CRect consoleRec;
	consoleRec.left = in_Pos + SPA_DLG_BORDER - 1;
	consoleRec.right = in_Pos + SPA_DLG_BORDER + 1;
	consoleRec.top = m_oWavePanel.GetClientRect().top;
	consoleRec.bottom = m_oWavePanel.GetClientRect().bottom;
	return consoleRec;
}
