// DisplayPanel.cpp: implementation of the CDisplayPanel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpectrumAnalysis.h"
#include "DisplayPanel.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CDisplayPanel::CDisplayPanel()
{
	initValue();	
}

//////////////////////////////////////////////////////////////////////
CDisplayPanel::CDisplayPanel(CDC* pDC)
{
	initValue();
	m_pDC = pDC;
}

//////////////////////////////////////////////////////////////////////////
CDisplayPanel::~CDisplayPanel()
{
	if(m_pDS != 0) delete m_pDS;
	m_pDS = NULL;
}

//////////////////////////////////////////////////////////////////////////
LOGPEN CDisplayPanel::GetConsolePen()
{
	return m_lgpConsole;
}

//////////////////////////////////////////////////////////////////////////
VOID CDisplayPanel::SetConsolePen(LOGPEN in_lgPen)
{
	m_lgpConsole = in_lgPen;
}

//////////////////////////////////////////////////////////////////////////
LOGPEN CDisplayPanel::GetGridPen()
{
	return m_lgpGrid;
}

//////////////////////////////////////////////////////////////////////////
VOID CDisplayPanel::SetGridPen(LOGPEN in_lgPen)
{
	m_lgpGrid = in_lgPen;
}

//////////////////////////////////////////////////////////////////////////
LOGPEN CDisplayPanel::GetSignalPen()
{
	return m_lgpSignal;
}

//////////////////////////////////////////////////////////////////////////
VOID CDisplayPanel::SetSignalPen(LOGPEN in_lgPen)
{
	m_lgpSignal = in_lgPen;
}

VOID CDisplayPanel::initValue()
{
	m_pDC = NULL;
	m_pDS = NULL;
	m_rcFrame = CRect(0,0,0,0);
	m_crBackground = SPA_DP_BACKGROUND;
	m_iSourceType = SPA_SOURCE_NULL;

	(CPen(SPA_DP_CONSOLE_STYLE,
		  SPA_DP_CONSOLE_WIDTH,
		  SPA_DP_CONSOLE_COLOR)).GetLogPen(&m_lgpConsole);

	(CPen(SPA_DP_GRID_STYLE,
		  SPA_DP_GRID_WIDTH,
		  SPA_DP_GRID_COLOR)).GetLogPen(&m_lgpGrid);

	(CPen(SPA_DP_SIGNAL_STYLE,
		  SPA_DP_SIGNAL_WIDTH,
		  SPA_DP_SIGNAL_COLOR)).GetLogPen(&m_lgpSignal);	
}

//////////////////////////////////////////////////////////////////////////
INT CDisplayPanel::drawAxis()
{
	//check the axis validation
	if(m_pDC == NULL) return SPA_ERR_INVALID_DISPLAY;
	if(!m_oHorizontalAxis.IsValidAxis()) return SPA_ERR_INVALID_AXIS;
	if(!m_oVerticalAxis.IsValidAxis()) return SPA_ERR_INVALID_AXIS;

	INT ret = SPA_NORMAL;
	m_oHorizontalAxis.m_pDC = m_pDC;
	ret = m_oHorizontalAxis.DrawAxis();
	if(ret != SPA_NORMAL) return ret;

	m_oVerticalAxis.m_pDC = m_pDC;
	ret = m_oVerticalAxis.DrawAxis();
	if(ret != SPA_NORMAL) return ret;

	return ret;
}

//////////////////////////////////////////////////////////////////////////
CRect CDisplayPanel::GetClientRect()
{
	return m_rcFrame;
}

//////////////////////////////////////////////////////////////////////////
INT CDisplayPanel::AttachAxis(CAxis in_oAxis)
{	
	if (m_rcFrame.IsRectEmpty()) return SPA_ERR_INVALID_DISPLAY;

	INT ret = SPA_NORMAL;
	switch(in_oAxis.GetPosition()) 
	{
	case SPA_AXIS_TOP:
		return attachTopAxis(in_oAxis);
		break;

	case SPA_AXIS_BOTTOM:
		return attachBottomAxis(in_oAxis);
		break;

	case SPA_AXIS_LEFT:
		return attachLeftAxis(in_oAxis);
		break;

	case SPA_AXIS_RIGHT:		
		return attachRightAxis(in_oAxis);
		break;

	default:
		return SPA_ERR_INVALID_AXIS;
		break;
	}

	return ret;
}

//////////////////////////////////////////////////////////////////////////
INT CDisplayPanel::attachTopAxis(const CAxis in_Axis)
{
	m_oHorizontalAxis = in_Axis;
	CSize axisSize (m_rcFrame.Width(), 
		SPA_AXIS_LONG_MARK + SPA_AXIS_MARK_HEIGHT);

	CPoint	axisPos = m_rcFrame.TopLeft()  
		- CSize(0,SPA_AXIS_LONG_MARK + SPA_AXIS_MARK_HEIGHT+SPA_DP_BORDER_WITH);

	CRect axisRect(axisPos, axisSize);
	m_oHorizontalAxis.SetFrame(axisRect);
	m_oHorizontalAxis.m_pDC = m_pDC;
	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
INT CDisplayPanel::attachBottomAxis(const CAxis in_Axis)
{
	m_oHorizontalAxis = in_Axis;
	CSize axisSize (m_rcFrame.Width(), 
		SPA_AXIS_LONG_MARK + SPA_AXIS_MARK_HEIGHT);

	CPoint	axisPos(m_rcFrame.left, m_rcFrame.bottom);
	axisPos += CSize(0,SPA_DP_BORDER_WITH);

	CRect axisRect(axisPos, axisSize);
	m_oHorizontalAxis.SetFrame(axisRect);	
	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
INT CDisplayPanel::attachLeftAxis(const CAxis in_Axis)
{
	m_oVerticalAxis = in_Axis;
	CSize axisSize(-(SPA_AXIS_LONG_MARK + SPA_AXIS_MARK_HEIGHT),
		m_rcFrame.Height());

	CPoint	axisPos= m_rcFrame.TopLeft() - CSize(SPA_DP_BORDER_WITH,0);	

	CRect axisRect(axisPos, axisSize);
	axisRect.NormalizeRect();

	m_oVerticalAxis.SetFrame(axisRect);		
	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
INT CDisplayPanel::attachRightAxis(const CAxis in_Axis)
{
	m_oVerticalAxis = in_Axis;
	
	//CPoint	axisPos = m_rcFrame.BottomRight() + CSize(SPA_DP_BORDER_WITH,0);	

	CPoint	axisPos(m_rcFrame.right + SPA_DP_BORDER_WITH, m_rcFrame.top);
	
	CSize axisSize(SPA_AXIS_LONG_MARK + SPA_AXIS_MARK_HEIGHT,
		m_rcFrame.Height());

	CRect axisRect(axisPos, axisSize);
	
	m_oVerticalAxis.SetFrame(axisRect);		
	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
INT CDisplayPanel::DrawGrid()
{
	//check the axis validation
	if(m_pDC == NULL) return SPA_ERR_INVALID_AXIS;
	if(!m_oHorizontalAxis.IsValidAxis()) return SPA_ERR_INVALID_AXIS;
	if(!m_oVerticalAxis.IsValidAxis()) return SPA_ERR_INVALID_AXIS;
	
	//setup for DC
	CPen pnGrid;
	pnGrid.CreatePenIndirect(&m_lgpGrid);
	CPen*  pOldPen = m_pDC->SelectObject(&pnGrid);

	drawHorizontalLines();
	drawVerticalLines();

	//restore DC 
	m_pDC->SelectObject(pOldPen);

	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
VOID CDisplayPanel::drawVerticalLines()
{
	CDC* pDC = m_pDC;
	
	INT iFrameWidth = m_rcFrame.Width();
	INT iMarkDistance = m_oHorizontalAxis.GetMarkInterval() 
						* m_oHorizontalAxis.GetUnitSize();
	INT iCurLength = 0;
	CPoint ptTopPoint = m_rcFrame.TopLeft();
	CPoint ptBottomPoint = ptTopPoint + CSize(0, m_rcFrame.Height());
	CSize szOffset(iMarkDistance,0);

	while(iCurLength < iFrameWidth)
	{
		//draw horizontal line
		pDC->MoveTo(ptTopPoint);
		if(iCurLength != 0) pDC->LineTo(ptBottomPoint);

		//update loop variables
		iCurLength += iMarkDistance;
		ptTopPoint += szOffset;
		ptBottomPoint += szOffset;
	}
}

//////////////////////////////////////////////////////////////////////////
VOID CDisplayPanel::drawHorizontalLines()
{
	CDC* pDC = m_pDC;
	
	INT iFrameHeight = m_rcFrame.Height();
	INT iMarkDistance = m_oVerticalAxis.GetMarkInterval() 
						* m_oVerticalAxis.GetUnitSize();
	INT iCurLength = 0;

	
	CPoint ptRightPoint = m_rcFrame.BottomRight();
	CPoint ptLeftPoint = ptRightPoint - CSize(m_rcFrame.Width(), 0);

	CSize szOffset(0,iMarkDistance);

	while(iCurLength < iFrameHeight)
	{
		//draw horizontal line
		pDC->MoveTo(ptLeftPoint);
		if(iCurLength != 0) pDC->LineTo(ptRightPoint);

		//update loop variables
		iCurLength += iMarkDistance;
		ptLeftPoint -= szOffset;
		ptRightPoint -= szOffset;
	}
}

//////////////////////////////////////////////////////////////////////////
BOOL CDisplayPanel::IsOnPanel(const POINT in_Pos)
{
	ASSERT(!m_rcFrame.IsRectEmpty());
	BOOL bTemp = m_rcFrame.PtInRect(in_Pos);
	return m_rcFrame.PtInRect(in_Pos);
}

//////////////////////////////////////////////////////////////////////////
BOOL CDisplayPanel::DrawConsole(const POINT in_Pos)
{
	ASSERT(m_pDC != NULL);
	ASSERT(!m_rcFrame.IsRectEmpty());

	if(!IsOnPanel(in_Pos)) return FALSE;

	//setup for dc
	CPen pnConsole;
	pnConsole.CreatePenIndirect(&m_lgpConsole);
	CPen* pOldPen = m_pDC->SelectObject(&pnConsole);

	INT iCurLength = 0;
	INT iFrameHeight = m_rcFrame.Height();

	CSize szSpace(0, SPA_DP_CONSOLE_PATERN/2);
	CSize  szPatern(0, SPA_DP_CONSOLE_PATERN);

	CPoint ptTop(in_Pos.x, m_rcFrame.top);
	CPoint ptBottom = ptTop + szSpace;
	
	while((iCurLength+SPA_DP_CONSOLE_PATERN/2) < iFrameHeight)
	{
		m_pDC->MoveTo(ptTop);
		m_pDC->LineTo(ptBottom);

		iCurLength += SPA_DP_CONSOLE_PATERN;
		ptTop += szPatern;
		ptBottom += szPatern;
	}

	if(iCurLength < iFrameHeight) 
	{
		ptTop = CPoint(in_Pos.x, m_rcFrame.top + iCurLength);
		ptBottom = CPoint(in_Pos.x, m_rcFrame.bottom);
		m_pDC->MoveTo(ptTop);
		m_pDC->LineTo(ptBottom);
	}

	//restore
	m_pDC->SelectObject(pOldPen);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
RECT CDisplayPanel::GetSelectedRect(const POINT in_ptFirst, const POINT in_ptSecond)
{
	ASSERT(!m_rcFrame.IsRectEmpty());

	CPoint topLeft(in_ptFirst.x, m_rcFrame.top);
	CPoint bottomRight(in_ptSecond.x, m_rcFrame.bottom);

	CRect rcSelected(topLeft, bottomRight);
	rcSelected.NormalizeRect();

	return rcSelected;
}

//////////////////////////////////////////////////////////////////////////
INT CDisplayPanel::DrawSelectMask(const CPoint in_ptFisrt, const CPoint in_ptSecond)
{
	INT ret = SPA_NORMAL;

	CRect rcMaskRect(GetSelectedRect(in_ptFisrt, in_ptSecond));	

	rcMaskRect.DeflateRect(0,1,0,1);
	
	CDC memDC;
	CBitmap bmpMask;
	CBrush brMask(SPA_DP_SELECT_MASK);

	memDC.CreateCompatibleDC(m_pDC);
	bmpMask.CreateCompatibleBitmap(m_pDC, rcMaskRect.Width(), rcMaskRect.Height());
	memDC.SelectObject(&bmpMask);

	CRect memRect(0,0,rcMaskRect.Width(), rcMaskRect.Height());
	memDC.FillRect(&memRect, &brMask);

	
	if(!m_pDC->BitBlt(rcMaskRect.TopLeft().x,rcMaskRect.TopLeft().y,
					rcMaskRect.Width(),rcMaskRect.Height(),
					&memDC,	0,0,SRCINVERT))
	{
		return SPA_ERR_MEMORY;
	}

	return ret;
}

//////////////////////////////////////////////////////////////////////////
INT CDisplayPanel::DrawDisplayPanel()
{
	INT ret = SPA_NORMAL;


	ret = drawAxis();
	if(ret != SPA_NORMAL) return ret;
	
	m_pDC->FillRect(&m_rcFrame, &(CBrush(m_crBackground)));
	ret = DrawGrid();
	if(ret != SPA_NORMAL) return ret;

	ret = drawBoundary();
	if(ret != SPA_NORMAL) return ret;

	
	return ret;
}

//////////////////////////////////////////////////////////////////////////
INT CDisplayPanel::drawBoundary()
{
	if(m_rcFrame.IsRectEmpty()) return SPA_ERR_INVALID_DISPLAY;

	CRect boundRect= m_rcFrame;
	boundRect.InflateRect(SPA_DP_BORDER_1,SPA_DP_BORDER_1);
	m_pDC->DrawEdge(&boundRect, EDGE_SUNKEN ,BF_RECT );
	boundRect.InflateRect(SPA_DP_BORDER_2,SPA_DP_BORDER_2);
	m_pDC->DrawEdge(&boundRect, EDGE_SUNKEN ,BF_RECT );	

	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
INT CDisplayPanel::AttachSource(CWave *in_pWave)
{
	INT ret = SPA_NORMAL;
		
	m_pDS = new CDisplayWaveSource(in_pWave);
	m_iSourceType = SPA_SOURCE_WAVE;
	
	//set the vertical axis
	CAxis vAxis = CAxis();
	vAxis.SetPosition(SPA_AXIS_RIGHT);
	vAxis.SetDirection(SPA_AXIS_DIRECT_B2T);
	vAxis.SetMarkInterval(SPA_PERCENT_MARK);
	vAxis.SetUnitSize(SPA_PERCENT_USIZE);
	vAxis.SetUnitName(SPA_AXIS_UNIT_PERCENT);
	vAxis.SetOffsetVal(SPA_PERCENT_OFFSET);
	vAxis.SetStartVal(-100);

	if(vAxis.IsValidAxis())
	{
		ret = AttachAxis(vAxis);
		if(ret != SPA_NORMAL) return ret;
	}
	else
	{
		ASSERT(0);
	}
	

	//set the horizontal axis
	CAxis hAxis = CAxis() ;
	hAxis.SetPosition(SPA_AXIS_BOTTOM);
	hAxis.SetDirection(SPA_AXIS_DIRECT_L2R);
	hAxis.SetOffsetVal(SPA_TIME_OFFSET);
	hAxis.SetStartVal(0);
	hAxis.SetUnitName(SPA_AXIS_UNIT_MS);
	
	INT iUnitSize = (SPA_DLG_DP_WIDTH * SPA_TIME_OFFSET)/in_pWave->GetTotalTime();
	hAxis.SetUnitSize((INT)iUnitSize);

	INT iMarkInterval = 0;

	for(INT i=0; i * iUnitSize < SPA_MARK_OFFSET_MIN ; i++)
	{
		iMarkInterval++;
	}
	hAxis.SetMarkInterval(iMarkInterval);

	if(hAxis.IsValidAxis())
	{
		ret = AttachAxis(hAxis);
		if(ret != SPA_NORMAL) return ret;
	}
	else
	{
		ASSERT(0);
	}
	

	return ret;	
}

//////////////////////////////////////////////////////////////////////////
INT CDisplayPanel::AttachSource(CSignal *in_pSpectrum)
{
	INT ret = SPA_NORMAL;
	INT i;
	m_pDS = new CDisplaySpectrumSource(in_pSpectrum);
	m_iSourceType = SPA_SOURCE_SPEC;

	//set vaxis dB
	CAxis vAxis = CAxis();
	vAxis.SetPosition(SPA_AXIS_RIGHT);
	vAxis.SetDirection(SPA_AXIS_DIRECT_T2B);
	vAxis.SetUnitName(SPA_AXIS_UNIT_DB);
	
	vAxis.SetMarkInterval(SPA_DB_MARK);	
	vAxis.SetUnitSize(SPA_DB_USIZE);
	//vAxis.SetOffsetVal(SPA_DB_OFFSET);
	vAxis.SetStartVal(m_pDS->GetFXMax());
	
	SAMPLE spDiff = m_pDS->GetFXMax() - m_pDS->GetFXMin();
	LONG iOffset = (spDiff * SPA_DB_USIZE)/SPA_DLG_DP_HEIGHT;
	iOffset ++;
	vAxis.SetOffsetVal(-iOffset);	

	if(vAxis.IsValidAxis())
	{
		ret = AttachAxis(vAxis);
		if(ret != SPA_NORMAL) return ret;
	}
	else
	{
		ASSERT(0);
	}
	
	//set horizontal axis
	CAxis hAxis = CAxis();
	hAxis.SetPosition(SPA_AXIS_BOTTOM);
	hAxis.SetDirection(SPA_AXIS_DIRECT_L2R);
	hAxis.SetUnitName(SPA_AXIS_UNIT_HZ);
	hAxis.SetStartVal(0);
	hAxis.SetOffsetVal(SPA_HZ_OFFSET);

	CDisplaySpectrumSource* pDSS = (CDisplaySpectrumSource*)m_pDS;
	INT iUnitSize = (SPA_DLG_DP_WIDTH * SPA_HZ_OFFSET)/pDSS->GetXMax();
	hAxis.SetUnitSize((INT)iUnitSize);

	INT iMarkInterval = 0;

	for(i=0; i * iUnitSize < SPA_MARK_OFFSET_MIN ; i++)
	{
		iMarkInterval++;
	}
	hAxis.SetMarkInterval(iMarkInterval);

	if(hAxis.IsValidAxis())
	{
		ret = AttachAxis(hAxis);
		if(ret != SPA_NORMAL) return ret;
	}
	else
	{
		ASSERT(0);
	}
	
	return ret;
}

//////////////////////////////////////////////////////////////////////////
INT CDisplayPanel::Display()
{
	INT ret = SPA_NORMAL;
	ASSERT(m_pDC != NULL);
	
	if(!m_isPowerOn) 
	{
		DrawOffScreen();
		return ret;
	}

	//setup dc
	CPen pnSignalPen;
	pnSignalPen.CreatePenIndirect(&m_lgpSignal);
	CPen* pOldPen = m_pDC->SelectObject(&pnSignalPen);
	
	switch(m_iSourceType)
	{
	case SPA_SOURCE_WAVE:
		displayWaveform();
		break;

	case SPA_SOURCE_SPEC:
		displaySpectrum();
		break;
	
	default:
		ASSERT(0);
	}

	//restore dc settings
	m_pDC->SelectObject(pOldPen);

	return ret;
}

/////////////////////////////////////////////////////////////////////////
INT CDisplayPanel::displayWaveform()
{
	INT ret = SPA_NORMAL;	
	INT i;
	CDC* pDC = m_pDC;

	
	CDisplayWaveSource* pDWS = (CDisplayWaveSource*)m_pDS;
	CWave* pWave = pDWS->m_pWaveSource;

	LONG lSize = pWave->GetNumOfSample();	//so vong lap
	
	SAMPLE spValFX = pWave->GetSampleAt(0);	//mau tai 0
	DOUBLE lX = pWave->GetTimeAt(0);		//X tai 0
	DOUBLE dFx = pDWS->SampleToPercent(spValFX);//FX tai 0

	CPoint ptCurrent = getPointFromValue(lX, dFx);
	pDC->MoveTo(ptCurrent);

	for(i=1; i<lSize; i++)
	{
		spValFX = pWave->GetSampleAt(i);
		dFx =  pDWS->SampleToPercent(spValFX);
		lX = pWave->GetTimeAt(i);
		ptCurrent = getPointFromValue(lX, dFx);
		pDC->LineTo(ptCurrent);
	}
	
	return ret;
}

//////////////////////////////////////////////////////////////////////////
INT CDisplayPanel::displaySpectrum()
{
	
	INT ret = SPA_NORMAL;	

	INT i;
	CDC* pDC = m_pDC;

	
	CDisplaySpectrumSource* pDSS = (CDisplaySpectrumSource*)m_pDS;
	CSignal* pSpectrum = pDSS->m_pSpectrum;

	LONG lSize = pSpectrum->GetSignalSize();//so vong lap
	LONG lFreq = pSpectrum->GetFrequency();

	DOUBLE lX = 0;						//X tai 0 la 0Hz
	SAMPLE dFx = (*pSpectrum)[0];		//FX tai 0

	CPoint ptCurrent = getPointFromValue(lX, dFx);
	pDC->MoveTo(ptCurrent);

	for(i=1; i< lSize; i++)
	{
	
		dFx =  (*pSpectrum)[i];
		lX = ((DOUBLE)i/(DOUBLE)lSize) * lFreq;
		ptCurrent = getPointFromValue(lX, dFx);
		if(ptCurrent.x >= SPA_DLG_DP_WIDTH + SPA_DLG_BORDER) break;
		pDC->LineTo(ptCurrent);
	}

	return ret;
}

//////////////////////////////////////////////////////////////////////////
CPoint CDisplayPanel::getPointFromValue(DOUBLE in_dX, DOUBLE in_dFX)
{
	CSize szSize;

	DOUBLE dXoffset = in_dX - m_oHorizontalAxis.GetStartVal();
	DOUBLE dFXoffset = in_dFX - m_oVerticalAxis.GetStartVal();

	szSize.cx = (dXoffset * m_oHorizontalAxis.GetUnitSize()) 
					/ m_oHorizontalAxis.GetOffsetVal();

	szSize.cy = (dFXoffset * m_oVerticalAxis.GetUnitSize()) 
					/ m_oVerticalAxis.GetOffsetVal();
	
	return offsetFromOrg(szSize);
}

//////////////////////////////////////////////////////////////////////////
POINT CDisplayPanel::GetOriginalPoint()
{
	POINT retPoint;
	INT hPos = m_oHorizontalAxis.GetDirection();
	INT vPos = m_oVerticalAxis.GetDirection();

	switch(hPos){
	case SPA_AXIS_DIRECT_L2R:
		switch(vPos) {
		case SPA_AXIS_DIRECT_T2B:
			retPoint = m_rcFrame.TopLeft();break;

		case SPA_AXIS_DIRECT_B2T:
			retPoint.x = m_rcFrame.left;
			retPoint.y = m_rcFrame.bottom;
			break;

		default:
			ASSERT(0); 
			break;
		}
		break;

	case SPA_AXIS_DIRECT_R2L:
		switch(vPos) {
		case SPA_AXIS_DIRECT_T2B:
			retPoint.x = m_rcFrame.right;
			retPoint.y = m_rcFrame.TopLeft;
			break;

		case SPA_AXIS_DIRECT_B2T:
			retPoint = m_rcFrame.BottomRight();
			break;

		default:
			ASSERT(0); 
			break;
		}
		break;

	default:
		ASSERT(0);
		break;
	}	

	return retPoint;
}

//////////////////////////////////////////////////////////////////////////
CPoint CDisplayPanel::offsetFromOrg(CSize in_szSize)
{
	CPoint retPoint;
	CPoint ptOrg = GetOriginalPoint();

	INT hPos = m_oHorizontalAxis.GetDirection();
	INT vPos = m_oVerticalAxis.GetDirection();
	switch(hPos){
	case SPA_AXIS_DIRECT_L2R:
		switch(vPos) {
		case SPA_AXIS_DIRECT_T2B:
			retPoint = ptOrg + in_szSize;
			break;

		case SPA_AXIS_DIRECT_B2T:
			in_szSize.cy = - in_szSize.cy;
			retPoint = ptOrg + in_szSize;

			break;

		default:
			ASSERT(0); 
			break;
		}
		break;

	case SPA_AXIS_DIRECT_R2L:
		switch(vPos) {
		case SPA_AXIS_DIRECT_T2B:
			in_szSize.cx = - in_szSize.cx;
			retPoint = ptOrg + in_szSize;
			break;

		case SPA_AXIS_DIRECT_B2T:
			retPoint = ptOrg - in_szSize;
			break;

		default:
			ASSERT(0); 
			break;
		}
		break;

	default:
		ASSERT(0);
		break;
	}	

	return retPoint;
}
//////////////////////////////////////////////////////////////////////////
// this function draw "the electric off" screer
VOID CDisplayPanel::DrawOffScreen()
{
	//check empty frame
	ASSERT(!m_rcFrame.IsRectEmpty());
	ASSERT(m_pDC != NULL);
	//ret = drawAxis();
	//if(ret != SPA_NORMAL) return ret;
	
	m_pDC->FillRect(&m_rcFrame, &(CBrush(SPA_DP_OFFSCREEN)));
	//ret = DrawGrid();
	//if(ret != SPA_NORMAL) return ret;
	drawBoundary();
}

//////////////////////////////////////////////////////////////////////////
VOID CDisplayPanel::TurnOn()
{
	m_isPowerOn = TRUE;
}

//////////////////////////////////////////////////////////////////////////
VOID CDisplayPanel::TurnOff()
{
	m_isPowerOn = FALSE;
}

BOOL CDisplayPanel::isPowerON()
{
	return m_isPowerOn;
}

//////////////////////////////////////////////////////////////////////////
DOUBLE CDisplayPanel::GetXval(LONG in_Xpos)
{
	ASSERT(m_oHorizontalAxis.IsValidAxis());
	DOUBLE retVal  = ((DOUBLE)in_Xpos/(DOUBLE)m_oHorizontalAxis.GetUnitSize()) 
			* (DOUBLE)m_oHorizontalAxis.GetOffsetVal();

	return retVal;
}

//////////////////////////////////////////////////////////////////////////
DOUBLE CDisplayPanel::GetFXval(LONG in_FXpos)
{
	ASSERT(!m_oVerticalAxis.IsValidAxis());
	DOUBLE retVal  = ((DOUBLE)in_FXpos/ (DOUBLE)m_oVerticalAxis.GetUnitSize()) 
					* (DOUBLE)m_oVerticalAxis.GetOffsetVal();

	return retVal;
}
