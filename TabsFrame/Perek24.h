#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"


// CPerek24 view

class CPerek24 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek24)

protected:
	CPerek24();           // protected constructor used by dynamic creation
	virtual ~CPerek24();

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	virtual void Do3DPaint(void);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	const int trsz;
	const double xStart;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	virtual void InitOnSubHeadButton(void);
	const int timerElaps;
	int stepsMagalKohav;
	const int sShemesh;
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
protected:
	double lasty;
};


