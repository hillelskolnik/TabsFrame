#pragma once
#include "afxwin.h"


// CTabExCtrl

class CTabExCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CTabExCtrl)

public:
	CTabExCtrl();
	virtual ~CTabExCtrl();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	CFont m_font;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


