// Hanning.h: interface for the CHanning class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HANNING_H__CC849ADD_D76F_44A6_A1E6_6A7229276569__INCLUDED_)
#define AFX_HANNING_H__CC849ADD_D76F_44A6_A1E6_6A7229276569__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Filter.h"

class CHanning : public CFilter  
{
public:
	CHanning();
	virtual ~CHanning();

	//the filtering function
	virtual INT DoFilter(CSignal& inout_pSignal);

private:
	DOUBLE getHanningValue(LONG n, LONG N);
};

#endif // !defined(AFX_HANNING_H__CC849ADD_D76F_44A6_A1E6_6A7229276569__INCLUDED_)
