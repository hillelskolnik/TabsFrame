#pragma once


// CButtonEx

class CButtonEx : public CButton
{
	DECLARE_DYNAMIC(CButtonEx)

public:
	CButtonEx();
	virtual ~CButtonEx();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	BOOL m_bMouseTracking;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	BOOL m_bChected;
};


