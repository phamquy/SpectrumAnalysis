// Rectangle.h: interface for the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTANGLE_H__768892A2_F8AB_49BB_908E_BF498C9D0F20__INCLUDED_)
#define AFX_RECTANGLE_H__768892A2_F8AB_49BB_908E_BF498C9D0F20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Filter.h"

class CRectangle : public CFilter  
{
public:
	virtual INT DoFilter(CSignal& inout_pSignal);
	CRectangle();
	virtual ~CRectangle();

private:
	DOUBLE getRectangleValue(LONG n, LONG N);
};

#endif // !defined(AFX_RECTANGLE_H__768892A2_F8AB_49BB_908E_BF498C9D0F20__INCLUDED_)
