// Axis.h: interface for the CAxis class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AXIS_H__2C45F602_4495_4D40_9A85_27CC75DE5585__INCLUDED_)
#define AFX_AXIS_H__2C45F602_4495_4D40_9A85_27CC75DE5585__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common.h"

class CAxis  
{
public:
	LONG GetPosValue(const POINT in_ptPos);
	LONG GetMaxValue();
	INT DrawAxis();
	CAxis();

	CAxis(
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
	);

	
	virtual ~CAxis();
	CDC* m_pDC;

	LONG	GetOffsetVal(){ return m_lOffsetVal;}
	VOID	SetOffsetVal(LONG in_lVal){ m_lOffsetVal = in_lVal;}
	 
	LONG	GetStartVal(){ return m_lStartVal;}
	VOID	SetStartVal(LONG in_lVal){ m_lStartVal = in_lVal;}

	INT		GetDirection(){return m_iDirection;}
	VOID	SetDirection(INT in_iDirect){ m_iDirection = in_iDirect;}

	INT		GetMarkInterval(){return m_iMarkInterval;}
	VOID	SetMarkInterval(INT in_iItvl){ m_iMarkInterval = in_iItvl;}

	INT		GetPosition(){return m_iPosition;}
	VOID	SetPosition(INT in_pos){ m_iPosition = in_pos;}

	INT		GetUnitSize(){ return m_iUnitSize;}
	VOID	SetUnitSize(INT in_iSize){ m_iUnitSize = in_iSize;}

	const CRect	GetFrame(){ return m_rcFrame;}
	VOID	SetFrame(CRect in_Rect){ m_rcFrame = in_Rect;}
	
	CString GetUnitFormat(){ return m_sUnitFormat;}
	VOID	SetUnitFormat(CString in_str){ m_sUnitFormat = in_str;}

	CString GetUnitName(){return m_sUnitName;}
	VOID	SetUnitName(CString in_str){m_sUnitName = in_str;}

	BOOL	IsValidAxis();

private:
	
	LOGFONT	m_lfFont;
	CRect	m_rcFrame;			//rectangle that contain the axis
	INT		m_iDirection;		//axis direction 
	INT		m_iPosition;		//edge that axis attach 
	CString m_sUnitFormat;		//format of unit string
	LONG	m_lStartVal;		//start value 
	LONG	m_lOffsetVal;		//value of an unit
	UINT	m_iMarkInterval;	//num of unit between two marked axis line
	//UINT	m_iTotalLength;		//total length size of axis
	UINT	m_iUnitSize;		//length size of an unit
	CString m_sUnitName;		//name of unit

protected:

	INT		drawLeftAxis();
	INT		drawBottomAxis();
	INT		drawRightAxis();
	INT		drawTopAxis();
	VOID	initValue(
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
	);
};

#endif // !defined(AFX_AXIS_H__2C45F602_4495_4D40_9A85_27CC75DE5585__INCLUDED_)
