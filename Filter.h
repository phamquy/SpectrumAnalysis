// Filter.h: interface for the CFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILTER_H__31F5D5B4_2591_47AA_9660_0428EE83B31F__INCLUDED_)
#define AFX_FILTER_H__31F5D5B4_2591_47AA_9660_0428EE83B31F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Signal.h"



class CFilter  
{
public:
	virtual INT DoFilter(CSignal& in_pSignal);
	VOID SetFilterType(UINT in_iType);
	UINT GetFilterType() const;
	CFilter();
	virtual ~CFilter();

protected:
	//indicate the filter type
	UINT m_iType;
};

#endif // !defined(AFX_FILTER_H__31F5D5B4_2591_47AA_9660_0428EE83B31F__INCLUDED_)
