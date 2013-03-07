/********************************************************************
    Project:    SpectrumAnalysis
	created:	2007/01/22
	created:	22:1:2007   21:09
	file base:	common
	file ext:	h
	author:		
	
	purpose:	file khai bao cac bien thong tin 
				chung cho toan project
*********************************************************************/

#ifndef SPA_COMMON__H_
#define SPA_COMMON__H_

//////////////////////////////////////////////////////////////////////////
// dinh nghia kieu cho tin hieu

//define the structure of complex signal sample 
typedef struct tagCOMPLEX{
	DOUBLE dReal;
	DOUBLE dImage;
} COMPLEX;

typedef struct tagMEASUREMENT
{
	CString	sUnitName;
	DOUBLE	lUnitVal;
	DOUBLE	lMinVal;
	DOUBLE	lMaxVal;
}MEASUREMENT; 

typedef __int16		SAMPLE;		//mau tin hieu
typedef __int16*	pSAMPLE;	//con tro mau tim hieu
typedef __int32		DSAMPLE;
typedef __int32*	pDSAMPLE;


//////////////////////////////////////////////////////////////////////////
// Dialog layout define

//dialog
#define SPA_DLG_X			0
#define SPA_DLG_Y			0
#define SPA_DLG_WIDTH		800
#define SPA_DLG_HEIGHT		570

//client layout
#define SPA_DLG_DP_WIDTH	600
#define SPA_DLG_DP_HEIGHT	200
#define SPA_DLG_DP_SPACE	40

#define SPA_DLG_FRM_CX		5
#define SPA_DLG_FRM_CY		25

#define SPA_DLG_CTL_CYSPACE	20
#define SPA_DLG_CTL_CX		115
#define SPA_DLG_CTL_CY		12

#define SPA_DLG_PLAY_CYS	170
#define SPA_DLG_BTN_PLAY_CY	35
#define SPA_DLG_BTN_PLAY_CX	115

#define	SPA_DLG_DP_CTRL		50
#define SPA_DLG_BORDER		10

#define SPA_DLG_DP_CX		650
#define SPA_DLG_DP_CY		250
#define SPA_DLG_WAVE		&CRect(0,0,650,240)
#define SPA_DLG_SPEC		&CRect(0,240,650,480)



//////////////////////////////////////////////////////////////////////////
// dinh nghia cac message box

#define SPA_SGN_OUTOFRANGE				_T("Out of range!")
#define SPA_SGN_INVALID_SAMPLE			_T("Negative sample!")
#define SPA_SGN_INVALID_CONVOLUTION		_T("Negative sample!")

#define SPA_MSG_WAV_FILENOTFOUND			_T("Error when open wave file!")
#define SPA_MSG_LONG_FILENAME				_T("File name is too long!")
#define SPA_MSG_INVALID_FILETYPE			_T("File is not *.wav type !")
#define SPA_MSG_UNKNOWN_FORMAT				_T("Can't find fmt chunk")
#define SPA_MSG_MEMORY_FULL					_T("Memory error! Its may be full")
#define SPA_MSG_MEMORY_DUMP					_T("Memory dump!")
#define SPA_MSG_FILEHEADER_FAIL				_T("File header read fail!")
#define SPA_MSG_NOT_PCM						_T("File is not PCM waveform !")
#define SPA_MSG_DEVICE_NOT_SUPPORT			_T("Device is not support this format!")
#define	SPA_MSG_DATA_CHUNK_FAIL				_T("Can't load data !")
#define SPA_MSG_DATA_SIZEUNKNOWN			_T("Can't get size of data")
#define SPA_MSG_UNLOCATE_DATA_MEM			_T("Can't locate memory for data block !")
#define SPA_MSG_CANNOT_READDATA				_T("Can't read data Wave file !")


//////////////////////////////////////////////////////////////////////////
//error code define 
#define SPA_NORMAL					0
#define SPA_ERR_FILENOTFOUND		1
#define SPA_ERR_INVALID_FORMAT		2
#define SPA_ERR_CHUNKLOSE			3
#define SPA_ERR_MEMORY				4
#define SPA_ERR_HEADER_FAIL			5
#define SPA_ERR_NON_11025_16MONO	6
#define SPA_ERR_DEVICE_NOT_SUPPORT	7
#define SPA_ERR_DATA_FAIL			8
#define SPA_ERR_DATA_SIZE_FAIL		9
#define SPA_ERR_MEMORY_READ			10
#define SPA_ERR_NOTIMPLEMENT		11
#define SPA_ERR_FILTERFAIL			12
#define SPA_ERR_INVALID_SCHEME		13
#define SPA_ERR_INVALID_FFTSIZE		14
#define SPA_ERR_FFTINIT_FAIL		15
#define SPA_ERR_INVALID_FFT_DIRECT	16
#define SPA_ERR_INVALID_AXIS		17
#define SPA_ERR_INVALID_DISPLAY		18
#define SPA_ERR_INVALID_DPSOURCE	19
#define SPA_ERR_FAIL_TO_PLAYWAVE	20			


//////////////////////////////////////////////////////////////////////////
//wave format constant define

//define code
#define SPA_CODE_PCM_FORMAT			1
#define SPA_PCM_FMT_SIZE			16

//check device mode
#define SPA_FMT_CHECK				0
#define SPA_DATA_CHECK				1

//current valid wave format
#define SPA_PCM_16BITS_SAMPLE		16
#define SPA_PCM_11025Hz				11025	
#define SPA_PCM_MONO				1

//////////////////////////////////////////////////////////////////////////
// filter constantz

//filter type
#define SPA_FIL_RECTANGLE	0	//cua so chu nhat
#define SPA_FIL_HANNING		1	//cua so Hamminhg
#define SPA_FIL_HAMMING		2	//cua so Hanning
#define SPA_FIL_BARTLETT	3	//cua so tam giac

//Hamming default parameter
#define SPA_HAMMING_A		0.23
#define SPA_HAMMING_B		0.54

//FFT direction
#define SPA_FFT_COMMON	0
#define SPA_FFT_INVERT	1

//////////////////////////////////////////////////////////////////////////
//Display panel default setting values

#define SPA_DP_BORDER_WITH		3
#define SPA_DP_BORDER_1			2
#define SPA_DP_BORDER_2			1

#define SPA_DP_OFFSCREEN		RGB(64,64,64)
#define SPA_DP_BACKGROUND		RGB(0,0,0)
#define SPA_DP_SELECT_MASK		RGB(255,255,255)
#define SPA_DP_CONSOLE_PATERN	6

#define SPA_DP_SIGNAL_STYLE		PS_SOLID
#define SPA_DP_SIGNAL_WIDTH		1
#define SPA_DP_SIGNAL_COLOR		RGB(0,255,0)

#define SPA_DP_GRID_STYLE		PS_SOLID
#define SPA_DP_GRID_WIDTH		1
#define SPA_DP_GRID_COLOR		RGB(80,80,80)

#define SPA_DP_CONSOLE_STYLE	PS_DASH	
#define SPA_DP_CONSOLE_WIDTH	1
#define SPA_DP_CONSOLE_COLOR	RGB(255,255,0)



//////////////////////////////////////////////////////////////////////////
//axis constant define
#define SPA_AXIS_NOTSET		0
#define SPA_AXIS_TOP		1
#define SPA_AXIS_RIGHT		2
#define SPA_AXIS_BOTTOM		3
#define SPA_AXIS_LEFT		4

#define SPA_AXIS_DIRECT_NOTSET	0

#define SPA_AXIS_DIRECT_L2R		1
#define SPA_AXIS_DIRECT_R2L		2

#define SPA_AXIS_DIRECT_T2B		1
#define SPA_AXIS_DIRECT_B2T		2

#define SPA_AXIS_SHORT_MARK		3
#define SPA_AXIS_LONG_MARK		5

#define SPA_AXIS_FONT_NAME		_T("Arial")
#define SPA_AXIS_FONT_HEIGHT	12
		
#define SPA_AXIS_UNIT_MS		_T("(ms)")
#define SPA_AXIS_UNIT_S			_T("(s)")
#define SPA_AXIS_UNIT_PERCENT	_T("(%)")
#define SPA_AXIS_UNIT_DB		_T("(dB)")
#define SPA_AXIS_UNIT_HZ		_T("(Hz)")
#define SPA_AXIS_UNITNAME_WITH	15
#define SPA_AXIS_MARK_HEIGHT	9

//////////////////////////////////////////////////////////////////////////
//general constant

//end of signal
#define SPA_END_OF_SIGNAL	0
#define	SPA_PI				3.141592654L

#define SPA_SOURCE_NULL		0
#define SPA_SOURCE_WAVE		1
#define SPA_SOURCE_SPEC		2

//APP constant
#define SPA_TIME_OFFSET		50
#define SPA_MARK_OFFSET_MIN	40
#define SPA_PERCENT_MARK	5
#define SPA_PERCENT_USIZE	5
#define SPA_PERCENT_OFFSET	5

#define SPA_DECIBEN_UNIT	1
#define SPA_HZ_UNIT			1
#define SPA_HZ_MIN			0
#define SPA_HZ_OFFSET		50

#define SPA_DB_USIZE		4
#define SPA_DB_OFFSET		-2
#define SPA_DB_MARK			5
#define SPA_DB_NUM_OF_MARK	10
#define SPA_DB_MARKOFSET	10


//Combo box value
#define SPA_WINDOW_HAN		_T("Hanning")
#define SPA_WINDOW_HAN_IDX	0
#define SPA_WINDOW_HAM		_T("Hamming")
#define SPA_WINDOW_HAM_IDX	1
#define SPA_WINDOW_REC		_T("Rectangle")
#define SPA_WINDOW_REC_IDX	2

//status
#define SPA_STATUS_INIT		0
#define SPA_STATUS_LOADED	1

#define SPA_NOCONSOLE		0
#define SPA_CONSOLE1		1
#define SPA_CONSOLE2		2

#define SPA_MNU_OPEN		0
#define SPA_MNU_PLAY		1
#define SPA_MNU_ANALYSIS	2
#define SPA_MNU_CLOSE		3
#define SPA_MNU_EXIT		4

#define SPA_MNU_ENABLE		MF_ENABLED | MF_BYPOSITION
#define SPA_MNU_DISABLE		MF_DISABLED | MF_GRAYED |MF_BYPOSITION
#define SPA_LBL_TOTALTIME	_T("Total time: ")
#endif //SPA_COMMON__H_
