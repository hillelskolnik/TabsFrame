#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"


// CPerek23 view

class CPerek23 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek23)

protected:
	CPerek23();           // protected constructor used by dynamic creation
	virtual ~CPerek23();

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
public:
	virtual void Do3DPaint(void);
protected:
	virtual void InitOnSubHeadButton(void);
	double lasty;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	void PaintResult(void);
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};


