; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSpectrumAnalysisDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SpectrumAnalysis.h"

ClassCount=3
Class1=CSpectrumAnalysisApp
Class2=CSpectrumAnalysisDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_SPA_MENU (English (U.S.))
Resource4=IDD_SPECTRUMANALYSIS_DIALOG
Resource5=IDD_SPECTRUMANALYSIS_DIALOG (English (U.S.))
Resource6=IDD_ABOUTBOX (English (U.S.))
Resource7=IDR_SPA_MENU

[CLS:CSpectrumAnalysisApp]
Type=0
HeaderFile=SpectrumAnalysis.h
ImplementationFile=SpectrumAnalysis.cpp
Filter=N

[CLS:CSpectrumAnalysisDlg]
Type=0
HeaderFile=SpectrumAnalysisDlg.h
ImplementationFile=SpectrumAnalysisDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSpectrumAnalysisDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=SpectrumAnalysisDlg.h
ImplementationFile=SpectrumAnalysisDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SPECTRUMANALYSIS_DIALOG]
Type=1
Class=CSpectrumAnalysisDlg
ControlCount=12
Control1=IDC_FRAME_FINFO,button,1342177287
Control2=IDC_LB_FREQ,static,1342308352
Control3=IDC_LB_BPS,static,1342308352
Control4=IDC_LB_CHANEL,static,1342308352
Control5=IDC_LB_TIME,static,1342308352
Control6=IDC_CMD_PLAY,button,1342242816
Control7=IDC_FRAME_FFT,button,1342177287
Control8=IDC_LB_FFTSIZE,static,1342308352
Control9=IDC_CB_WINDOW,combobox,1344339970
Control10=IDC_LB_WINDOW,static,1342308352
Control11=IDC_CMD_ANALYSIS,button,1342242816
Control12=IDC_CB_FFTSIZE,combobox,1344339970

[MNU:IDR_SPA_MENU]
Type=1
Class=CSpectrumAnalysisDlg
Command1=ID_FILE_OPEN
Command2=ID_FILE_PLAY
Command3=ID_FILE_ANALYSIS
Command4=ID_FILE_CLOSE
Command5=ID_FILE_EXIT
Command6=ID_HELP_ABOUT
CommandCount=6

[MNU:IDR_SPA_MENU (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_PLAY
Command3=ID_FILE_ANALYSIS
Command4=ID_FILE_CLOSE
Command5=ID_FILE_EXIT
Command6=ID_HELP_ABOUT
CommandCount=6

[DLG:IDD_SPECTRUMANALYSIS_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=12
Control1=IDC_FRAME_FINFO,button,1342177287
Control2=IDC_LB_FREQ,static,1342308352
Control3=IDC_LB_BPS,static,1342308352
Control4=IDC_LB_CHANEL,static,1342308352
Control5=IDC_LB_TIME,static,1342308352
Control6=IDC_CMD_PLAY,button,1342242816
Control7=IDC_FRAME_FFT,button,1342177287
Control8=IDC_LB_FFTSIZE,static,1342308352
Control9=IDC_CB_WINDOW,combobox,1344339970
Control10=IDC_LB_WINDOW,static,1342308352
Control11=IDC_CMD_ANALYSIS,button,1342242816
Control12=IDC_CB_FFTSIZE,combobox,1344339970

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

