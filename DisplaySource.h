// DisplaySource.h: interface for the CDisplaySource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPLAYSOURCE_H__16BA9C36_E469_453B_A8E1_CD36E4166981__INCLUDED_)
#define AFX_DISPLAYSOURCE_H__16BA9C36_E469_453B_A8E1_CD36E4166981__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common.h"

class CDisplaySource  
{
public:	
	virtual DOUBLE Fx(DOUBLE x)
	{
		ASSERT(FALSE);
		return 0;
	};

	virtual INT InitSource()
	{
		ASSERT(FALSE);
		return SPA_ERR_INVALID_DPSOURCE;
	};

	CString GetXName(){return m_msX.sUnitName; }
	VOID SetXName(CString in_sXName){ m_msX.sUnitName = in_sXName;}

	DOUBLE GetXUnitVal(){return m_msX.lUnitVal; }
	VOID SetXUnitVal(DOUBLE in_lUnitVal){ m_msX.lUnitVal = in_lUnitVal;}
	
	DOUBLE GetXMax(){return m_msX.lMaxVal;}
	VOID SetXMax(DOUBLE in_lMax){m_msX.lMaxVal = in_lMax;}

	DOUBLE GetXMin(){return m_msX.lMinVal;}
	VOID SetXMin(DOUBLE in_lMin){m_msX.lMinVal = in_lMin;}

	CString GetFXName(){return m_msFX.sUnitName; }
	VOID SetFXName(CString in_sFXName){ m_msFX.sUnitName = in_sFXName;}

	DOUBLE GetFXUnitVal(){return m_msFX.lUnitVal; }
	VOID SetFXUnitVal(DOUBLE in_lUnitVal){ m_msFX.lUnitVal = in_lUnitVal;}
	
	DOUBLE GetFXMax(){return m_msFX.lMaxVal;}
	VOID SetFXMax(DOUBLE in_lMax){m_msFX.lMaxVal = in_lMax;}

	DOUBLE GetFXMin(){return m_msFX.lMinVal;}
	VOID SetFXMin(DOUBLE in_lMin){m_msFX.lMinVal = in_lMin;}

	CDisplaySource();
	virtual ~CDisplaySource();

protected:
	MEASUREMENT m_msX;
	MEASUREMENT m_msFX;	

	SAMPLE m_spMin;
	SAMPLE m_spMax;
};


#endif // !defined(AFX_DISPLAYSOURCE_H__16BA9C36_E469_453B_A8E1_CD36E4166981__INCLUDED_)
