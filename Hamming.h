// Hamming.h: interface for the CHamming class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HAMMING_H__E25B3339_CE5F_47D7_83F8_103D6430983C__INCLUDED_)
#define AFX_HAMMING_H__E25B3339_CE5F_47D7_83F8_103D6430983C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Filter.h"

class CHamming : public CFilter  
{
public:
	CHamming(DOUBLE in_a, DOUBLE in_b);
	CHamming();
	virtual ~CHamming();
	virtual INT DoFilter(CSignal& in_pSignal);

private:
	//cac he so cua so
	DOUBLE m_fb;
	DOUBLE m_fa;

	DOUBLE getHammingValue(LONG n, LONG N);
};

#endif // !defined(AFX_HAMMING_H__E25B3339_CE5F_47D7_83F8_103D6430983C__INCLUDED_)
