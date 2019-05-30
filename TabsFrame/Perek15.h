#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"


// CPerek15 view

class CPerek15 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek15)

protected:
	CPerek15();           // protected constructor used by dynamic creation
	virtual ~CPerek15();

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
	afx_msg void OnSetFocus(CWnd* pOldWnd);
protected:
	void InitOnSubHeadButton(void);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};


