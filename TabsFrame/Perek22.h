#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"


// CPerek22 view

class CPerek22 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek22)

protected:
	CPerek22();           // protected constructor used by dynamic creation
	virtual ~CPerek22();

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
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	virtual void InitOnSubHeadButton(void);
public:
	virtual void Do3DPaint(void);
protected:
	double lasty;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
protected:
	int m_nMazalotStars2Size;
	int m_nMazalotStarsSize;
};


