// FFTmachine.h: interface for the CFFTmachine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FFTMACHINE_H__88EA162E_EDA5_4CC1_93CA_F307BBE59157__INCLUDED_)
#define AFX_FFTMACHINE_H__88EA162E_EDA5_4CC1_93CA_F307BBE59157__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common.h"
#include "Signal.h"

class CFFTmachine  
{
public:
	VOID ResetMachine();
	const CSignal* m_pSignalSource;
	INT GetSpectrum(CSignal&  out_pSignal);
	INT GetFFTExp();
	INT RunFFT(INT in_Direct);
	INT InitMachine(const CSignal* in_pSignal, LONG in_iFFTSize);
	INT SetSignalSource(const CSignal *in_pSignal);
	BOOL SetFFTSize(LONG in_iSize);
	LONG GetFFTSize();
	CFFTmachine();
	virtual ~CFFTmachine();

private:
	INT m_iFFTExp;
	LONG m_iFFTSize;				//size of FFT transform
	COMPLEX* m_pComplexSignal;  //the complex form of signal
};

#endif // !defined(AFX_FFTMACHINE_H__88EA162E_EDA5_4CC1_93CA_F307BBE59157__INCLUDED_)
