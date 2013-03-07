// DisplayPanel.h: interface for the CDisplayPanel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPLAYPANEL_H__3CB83ED0_7A87_4023_9237_B316113474BC__INCLUDED_)
#define AFX_DISPLAYPANEL_H__3CB83ED0_7A87_4023_9237_B316113474BC__INCLUDED_

#include "Axis.h"	// Added by ClassView
#include "DisplayWaveSource.h"	// Added by ClassView
#include "DisplaySpectrumSource.h"
#include "common.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDisplayPanel  
{
public:
	DOUBLE GetFXval(LONG in_FXpos);
	DOUBLE GetXval(LONG in_Xpos);
	BOOL isPowerON();
	VOID TurnOff();
	VOID TurnOn();
	VOID DrawOffScreen();
	POINT GetOriginalPoint();
	INT Display();
	INT AttachSource(CSignal* in_pSpectrum);
	INT AttachSource(CWave* in_pWave);

	INT DrawDisplayPanel();
	INT DrawSelectMask(const CPoint in_ptFisrt, const CPoint in_ptSecond);
	RECT GetSelectedRect(const POINT in_ptFirst, const POINT in_ptSecond);
	INT DrawConsole(const POINT in_Pos);
	BOOL IsOnPanel(const POINT in_Pos);
	INT DrawGrid();
	INT AttachAxis(CAxis in_oAxis);
	CRect GetClientRect();
	
	//--------------------------------------------	
	//contructor/~destructor
	CDisplayPanel();
	CDisplayPanel(CDC* pDC);

	virtual ~CDisplayPanel();


	VOID SetSignalPen(LOGPEN in_lgPen);
	LOGPEN GetSignalPen();
	VOID SetGridPen(LOGPEN in_lgPen);
	LOGPEN GetGridPen();
	VOID SetConsolePen(LOGPEN in_lgPen);
	LOGPEN GetConsolePen();
	VOID SetDisplayFrame(CRect in_Frame){m_rcFrame = in_Frame;}
	
	COLORREF GetBackColor(){ return m_crBackground;}

	CDC* m_pDC;
	CAxis		m_oHorizontalAxis;	//Horizontal axis
	CAxis		m_oVerticalAxis;	//Vertical axis
private:
	BOOL m_isPowerOn;
	CDisplaySource* m_pDS;
	INT attachTopAxis(const CAxis in_Axis);
	INT attachBottomAxis(const CAxis in_Axis);
	INT attachLeftAxis(const CAxis in_Axis);
	INT attachRightAxis(const CAxis in_Axis);
	
	VOID initValue();
		
	CRect		m_rcFrame;			//general frame 
	COLORREF	m_crBackground;		//display background
	LOGPEN		m_lgpSignal;		//pen to draw signal lines
	LOGPEN		m_lgpGrid;			//pen to draw grid
	LOGPEN		m_lgpConsole;		//pen to draw console lines

protected:
	CPoint offsetFromOrg(CSize in_szSize);
	CPoint getPointFromValue(DOUBLE in_dX, DOUBLE in_dFX);
	INT displaySpectrum();
	INT displayWaveform();
	INT m_iSourceType;
	INT drawBoundary();
	INT drawAxis();
	VOID drawVerticalLines();
	VOID drawHorizontalLines();
};

#endif // !defined(AFX_DISPLAYPANEL_H__3CB83ED0_7A87_4023_9237_B316113474BC__INCLUDED_)
