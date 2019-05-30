#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"


// CPerek19 view

class CPerek19 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek19)

protected:
	CPerek19();           // protected constructor used by dynamic creation
	virtual ~CPerek19();

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
	virtual void InitOnSubHeadButton(void);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
protected:
	double lasty;
	int m_nMazalotStarsSize;
};


