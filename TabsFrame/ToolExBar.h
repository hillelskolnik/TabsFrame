#pragma once

class CButtonEx;
// CToolExBar

class CToolExBar : public CToolBar
{
	DECLARE_DYNAMIC(CToolExBar)

public:
	CToolExBar();
	virtual ~CToolExBar();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	CButtonEx* m_pButtons;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	int m_btnsCount;
public:
	BOOL m_bRightAllig;
public:
	CBitmap* m_pBitmap;
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};


