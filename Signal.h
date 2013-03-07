// Signal.h: interface for the CSignal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGNAL_H__BD995893_8BB4_49A4_9F4A_5A29AA645306__INCLUDED_)
#define AFX_SIGNAL_H__BD995893_8BB4_49A4_9F4A_5A29AA645306__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common.h"


class CSignal  
{
	//convolution
	friend CSignal operator*(const CSignal&, const CSignal&);

public:
	CSignal();
	CSignal(LONG in_Size);
	CSignal(LONG in_Size, LONG in_lFrequency);
	CSignal( const CSignal &in_SignalCopy);
	virtual ~CSignal();

//property
private:
	LONG		m_lSampleFrequence;
	LONG		m_lSize;		
	pSAMPLE		m_pSampleConsole;

public:
	VOID Empty();
	SAMPLE GetMaxSample();
	SAMPLE GetMinSample();
	VOID SetFrequency(LONG in_Freq);
	LONG GetFrequency() const;
	BOOL IsEmpty();
	BOOL LocateMem(LONG in_size);
	LONG GetSignalSize() const;
	//assignment
	const CSignal& operator=( const CSignal & );
	//get element
	SAMPLE& operator[]( LONG ); 
	SAMPLE  operator[]( LONG ) const;
};

#endif // !defined(AFX_SIGNAL_H__BD995893_8BB4_49A4_9F4A_5A29AA645306__INCLUDED_)
