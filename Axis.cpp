// Axis.cpp: implementation of the CAxis class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpectrumAnalysis.h"
#include "Axis.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAxis::CAxis()
{
	initValue(CRect(0,0,0,0), NULL,0,0, SPA_AXIS_DIRECT_NOTSET,
							0, SPA_AXIS_NOTSET, 0, "%d", "");
}

CAxis::CAxis
(
	CRect	in_rcFrame,
	CDC*	pDC,
	LONG	in_dOffsetVal,
	LONG	in_dStartVal,
	INT		in_iDirection,
	INT		in_iMarkInterval,
	INT		in_iPosition,
	INT		in_iUnitSize,
	CString	in_sUnitFormat,
	CString	in_sUnitName
)
{
	initValue(in_rcFrame,pDC,in_dOffsetVal,in_dStartVal,
		in_iDirection,in_iMarkInterval,in_iPosition,in_iUnitSize,
		in_sUnitFormat,in_sUnitName);
}

CAxis::~CAxis()
{

}

VOID CAxis::initValue
(
	CRect	in_rcFrame,
	CDC*	pDC,
	LONG	in_lOffsetVal,
	LONG	in_lStartVal,
	INT		in_iDirection,
	INT		in_iMarkInterval,
	INT		in_iPosition,
	INT		in_iUnitSize,
	CString	in_sUnitFormat,
	CString	in_sUnitName
)
{	
	m_rcFrame = in_rcFrame;
	m_pDC = pDC;
	m_lOffsetVal = in_lOffsetVal; 
	m_lStartVal	= in_lStartVal;
	m_iDirection = in_iDirection;
	m_iMarkInterval = in_iMarkInterval;
	m_iPosition = in_iPosition;
	//m_iTotalLength = 0;
	m_iUnitSize = in_iUnitSize;
	m_sUnitFormat = in_sUnitFormat;
	m_sUnitName = in_sUnitName;	

	//init font
	m_lfFont.lfHeight = SPA_AXIS_FONT_HEIGHT;
	m_lfFont.lfWidth = 0;
	m_lfFont.lfEscapement = 0;
	m_lfFont.lfOrientation = 0;
	m_lfFont.lfWeight = FW_NORMAL;
	m_lfFont.lfItalic = FALSE;
	m_lfFont.lfUnderline = FALSE;
	m_lfFont.lfStrikeOut = FALSE;
	m_lfFont.lfCharSet = ANSI_CHARSET;
	m_lfFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	m_lfFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	m_lfFont.lfQuality = DEFAULT_QUALITY;
	m_lfFont.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;	
	strcpy(m_lfFont.lfFaceName, (LPCTSTR)SPA_AXIS_FONT_NAME);
}

//////////////////////////////////////////////////////////////////////////
INT CAxis::DrawAxis()
{
	//Check the valid axis
	if(!IsValidAxis()||m_rcFrame.IsRectEmpty()) 
		return SPA_ERR_INVALID_AXIS;

	INT ret = SPA_NORMAL;
	CDC* pDC = m_pDC;

	/////////////////////////////////////////////////
	// CDC setup

	//init pen and font
	CFont fnAxisFont;
	fnAxisFont.CreateFontIndirect(&m_lfFont);
	CFont* pOldFont = pDC->SelectObject(&fnAxisFont);

	CPen pnPen(PS_SOLID, 1, RGB(0,0,0));	
	CPen* pOldPen =	pDC->SelectObject(&pnPen);
		

	INT iOldBkMode = pDC->SetBkMode(TRANSPARENT);
	///////////////////////////////////////////	
	//start axis drawing
	switch(m_iPosition) 
	{
	case SPA_AXIS_TOP:
		ret = drawTopAxis();
		break;
	
	case SPA_AXIS_LEFT: 
		ret =  drawLeftAxis();
		break;

	case SPA_AXIS_BOTTOM:
		ret =  drawBottomAxis();
		break;

	case SPA_AXIS_RIGHT:
		ret =  drawRightAxis();
		break;

	default: //SPA_AXIS_NOTSET
		ASSERT("AXIS POS IS NOTSET!");
		return SPA_ERR_INVALID_AXIS;
		break;
	}

	////////////////////////////////////
	//restore old settings	
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);
	pDC->SetBkMode(iOldBkMode);
	
	//pDC->SelectClipRgn(&rgnOrg);

	return ret;
}

//////////////////////////////////////////////////////////////////////////
//cause time purpose, the m_iDrection is not condidered
// always asume it is 1, it means L-->R direction
INT CAxis::drawTopAxis()
{
	CDC* pDC = m_pDC;
	//////////////////////////////////////////////////
	// Draw axis's line and axis's mark

	//draw axis line (assume L2R direction)
	CPoint ptOrg = CPoint(m_rcFrame.left, m_rcFrame.bottom);
	CPoint ptEnd = m_rcFrame.BottomRight();

	pDC->MoveTo(ptOrg);
	pDC->LineTo(ptEnd);

	//draw axis mark
	INT iAxisLength = m_rcFrame.Width();
	INT iCurLength = 0;
	INT iCurNumOfMark = 0;
	LONG lCurVal = m_lStartVal;
	CPoint ptCurPos = ptOrg;

	while(iCurLength <= iAxisLength)
	{
		CPoint ptEndMark;
		pDC->MoveTo(ptCurPos);
		INT iMarkModulo = iCurNumOfMark % m_iMarkInterval;

		//define the short or long mark
		if(iMarkModulo == 0) 
			ptEndMark = ptCurPos - CSize(0, SPA_AXIS_LONG_MARK);
		else
			ptEndMark = ptCurPos - CSize(0, SPA_AXIS_SHORT_MARK);

		pDC->LineTo(ptEndMark);

		
		//draw mark value
		if((iMarkModulo == 0) && 
			(iCurLength < (iAxisLength -SPA_AXIS_UNITNAME_WITH)))
		{
			CString sMarkStr;
			sMarkStr.Format(m_sUnitFormat, lCurVal);
			pDC->TextOut(ptEndMark.x, ptEndMark.y - SPA_AXIS_MARK_HEIGHT, sMarkStr);

		}
		
		//update loop variables
		lCurVal += m_lOffsetVal;
		iCurNumOfMark++;
		iCurLength = iCurNumOfMark * m_iUnitSize;			
		ptCurPos += CSize(m_iUnitSize,0);//assume L2R direction
	}

	// Draw UnitName
	pDC->TextOut(m_rcFrame.right - SPA_AXIS_UNITNAME_WITH,
				m_rcFrame.bottom - SPA_AXIS_LONG_MARK - SPA_AXIS_MARK_HEIGHT, 
				m_sUnitName);
	return SPA_NORMAL;
}

//////////////////////////////////////////////////////////////////////////
INT CAxis::drawRightAxis()
{
	CDC* pDC = m_pDC;

	//////////////////////////////////////////////////
	// Draw axis's line and axis's mark

	//draw axis line (assume L2R direction)
	CPoint ptOrg;
	CPoint ptEnd;			

	//xac dinh diem goc va cuoio cua truc
	if(m_iDirection == SPA_AXIS_DIRECT_B2T)
	{
		ptOrg = CPoint(m_rcFrame.left, m_rcFrame.bottom);
		ptEnd = m_rcFrame.TopLeft();
	}
	else 
	{
		ptOrg = m_rcFrame.TopLeft();
		ptEnd = CPoint(m_rcFrame.left, m_rcFrame.bottom);
	}

	
	//ve truc chua co vach
	pDC->MoveTo(ptOrg);
	pDC->LineTo(ptEnd);

	//draw axis mark
	INT iAxisLength = m_rcFrame.Height();
	INT iCurLength = 0;
	INT iCurNumOfMark = 0;
	LONG lCurVal = m_lStartVal;
	CPoint ptCurPos = ptOrg;

	while(iCurLength <= iAxisLength)
	{
		CPoint ptEndMark;
		pDC->MoveTo(ptCurPos);
		INT iMarkModulo = iCurNumOfMark % m_iMarkInterval;

		//define the short or long mark
		if(iMarkModulo == 0) 
			ptEndMark = ptCurPos + CSize(SPA_AXIS_LONG_MARK, 0);
		else
			ptEndMark = ptCurPos + CSize(SPA_AXIS_SHORT_MARK, 0);

		//draw mark
		pDC->LineTo(ptEndMark);

		//draw mark value
		//if((iMarkModulo == 0) && 
		//	(iCurLength < (iAxisLength -SPA_AXIS_FONT_HEIGHT/2)))
		if(iMarkModulo == 0)
		{
			CString sMarkStr;
			sMarkStr.Format(m_sUnitFormat, lCurVal);
			pDC->TextOut(ptEndMark.x + 2, ptEndMark.y - SPA_AXIS_FONT_HEIGHT/2, sMarkStr);
		}

		//update loop variables
		lCurVal += m_lOffsetVal;
		iCurNumOfMark++;
		iCurLength = iCurNumOfMark * m_iUnitSize;		
		if(m_iDirection == SPA_AXIS_DIRECT_B2T)
			ptCurPos -= CSize(0, m_iUnitSize);//assume B2T direction
		else
			ptCurPos += CSize(0, m_iUnitSize);
	}

	
	// Draw Unitname 
//	if (m_sUnitName == SPA_AXIS_UNIT_PERCENT)
//	{
		if(m_iDirection == SPA_AXIS_DIRECT_B2T)
			pDC->TextOut(m_rcFrame.left + SPA_AXIS_LONG_MARK + 15,
				m_rcFrame.top - SPA_AXIS_FONT_HEIGHT/2, m_sUnitName);
		else
			pDC->TextOut(m_rcFrame.left + SPA_AXIS_LONG_MARK + 15,
				m_rcFrame.bottom - SPA_AXIS_FONT_HEIGHT/2, m_sUnitName);		
		
//	}
//	else
//	{
//		if(m_iDirection == SPA_AXIS_DIRECT_B2T)
//			pDC->TextOut(m_rcFrame.left + SPA_AXIS_LONG_MARK,
//					m_rcFrame.top - SPA_AXIS_FONT_HEIGHT/2, m_sUnitName);
//		else
//			pDC->TextOut(m_rcFrame.left + SPA_AXIS_LONG_MARK,
//					m_rcFrame.bottom - SPA_AXIS_FONT_HEIGHT/2, m_sUnitName);
//	}
	

	return SPA_NORMAL;	
}

//////////////////////////////////////////////////////////////////////////
INT CAxis::drawBottomAxis()
{
	CDC* pDC = m_pDC;

	//////////////////////////////////////////////////
	// Draw axis's line and axis's mark

	//draw axis line (assume L2R direction)
	CPoint ptOrg = m_rcFrame.TopLeft();			
	CPoint ptEnd = CPoint(m_rcFrame.right, m_rcFrame.top);

	pDC->MoveTo(ptOrg);
	pDC->LineTo(ptEnd);

	//draw axis mark
	INT iAxisLength = m_rcFrame.Width();
	INT iCurLength = 0;
	INT iCurNumOfMark = 0;
	LONG lCurVal = m_lStartVal;
	CPoint ptCurPos = ptOrg;

	while(iCurLength <= iAxisLength)
	{
		CPoint ptEndMark;
		pDC->MoveTo(ptCurPos);
		INT iMarkModulo = iCurNumOfMark % m_iMarkInterval;

		//define the short or long mark
		if(iMarkModulo == 0) 
			ptEndMark = ptCurPos + CSize(0, SPA_AXIS_LONG_MARK);
		else
			ptEndMark = ptCurPos + CSize(0, SPA_AXIS_SHORT_MARK);

		//draw mark
		pDC->LineTo(ptEndMark);

		//draw mark value
		if((iMarkModulo == 0) && 
			(iCurLength < (iAxisLength -SPA_AXIS_UNITNAME_WITH)))
		{
			CString sMarkStr;
			sMarkStr.Format(m_sUnitFormat, lCurVal);
			pDC->TextOut(ptEndMark.x, ptEndMark.y, sMarkStr);

		}

		//update loop variables
		lCurVal += m_lOffsetVal;
		iCurNumOfMark++;
		iCurLength = iCurNumOfMark * m_iUnitSize;		
		ptCurPos += CSize(m_iUnitSize, 0);//assume L2R direction
	}

	// Draw mark string 
	pDC->TextOut(m_rcFrame.right,
					m_rcFrame.top + SPA_AXIS_LONG_MARK, 
					m_sUnitName);

	return SPA_NORMAL;
}

/////////////////////////////////////////////////////////////////////////
INT CAxis::drawLeftAxis()
{
	CDC* pDC = m_pDC;

	//////////////////////////////////////////////////
	// Draw axis's line and axis's mark

	//draw axis line (assume L2R direction)
	CPoint ptOrg = m_rcFrame.BottomRight();			
	CPoint ptEnd = CPoint(m_rcFrame.right, m_rcFrame.top);

	pDC->MoveTo(ptOrg);
	pDC->LineTo(ptEnd);

	//draw axis mark
	INT iAxisLength = m_rcFrame.Height();
	INT iCurLength = 0;
	INT iCurNumOfMark = 0;
	CPoint ptCurPos = ptOrg;

	while(iCurLength <= iAxisLength)
	{
		CPoint ptEndMark;
		pDC->MoveTo(ptCurPos);
		INT iMarkModulo = iCurNumOfMark % m_iMarkInterval;

		//define the short or long mark
		if(iMarkModulo == 0) 
			ptEndMark = ptCurPos - CSize(SPA_AXIS_LONG_MARK, 0);
		else
			ptEndMark = ptCurPos - CSize(SPA_AXIS_SHORT_MARK, 0);

		//draw mark
		pDC->LineTo(ptEndMark);

		//update loop variables
		iCurNumOfMark++;
		iCurLength = iCurNumOfMark * m_iUnitSize;		
		ptCurPos -= CSize(0, m_iUnitSize);//assume L2R direction
	}

	///////////////////////////////////////////////////
	// Draw mark string 
	//???????

	return SPA_NORMAL;	
}

//////////////////////////////////////////////////////////////////////////
BOOL CAxis::IsValidAxis()
{
	if(m_lOffsetVal == 0) return FALSE;
	if(m_iDirection == SPA_AXIS_DIRECT_NOTSET) return FALSE;
	if(m_iPosition == SPA_AXIS_NOTSET) return FALSE;
	if(m_iUnitSize == 0) return FALSE;
	//if(m_rcFrame.IsRectEmpty()) return FALSE;
	if(m_sUnitName == "") return FALSE;
	//if(m_pDC == NULL) return FALSE;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
LONG CAxis::GetMaxValue()
{
	ASSERT(IsValidAxis());

	LONG lTotalValOffset;
	LONG lMaxValue;

	switch(m_iPosition) {
	case SPA_AXIS_TOP:
	case SPA_AXIS_BOTTOM:	
		lTotalValOffset = (m_rcFrame.Width() * m_lOffsetVal) / m_iUnitSize; 
		lMaxValue  = m_lStartVal + lTotalValOffset;
		break;

	case SPA_AXIS_LEFT:
	case SPA_AXIS_RIGHT:
		lTotalValOffset = (m_rcFrame.Height() * m_lOffsetVal) / m_iUnitSize; 
		lMaxValue  = m_lStartVal + lTotalValOffset;
		break;
	default:
		break;
	}
	
	return  lMaxValue;
}

//////////////////////////////////////////////////////////////////////////
LONG CAxis::GetPosValue(const POINT in_ptPos)
{
	ASSERT(IsValidAxis());

	INT iPosOffset;

	switch(m_iPosition) {
	case SPA_AXIS_TOP:
	case SPA_AXIS_BOTTOM:	
		iPosOffset = in_ptPos.x - m_rcFrame.left;
		break;

	case SPA_AXIS_LEFT:
	case SPA_AXIS_RIGHT:
		iPosOffset = m_rcFrame.bottom - in_ptPos.y;
		break;

	default:
		break;
	}

	LONG lPosValOffset = (iPosOffset * m_lOffsetVal) / m_iUnitSize;
	LONG lPosVal = m_lStartVal + lPosValOffset;
	return lPosVal;
}
