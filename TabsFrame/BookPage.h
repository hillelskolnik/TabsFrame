#pragma once


// CBookPage

class CBookPage : public CView
{
	DECLARE_DYNCREATE(CBookPage)

public:
	CBookPage();
	virtual ~CBookPage();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnDraw(CDC* /*pDC*/);
public:
	void LoadPage(int idx, int nHLidx = -1);
protected:
	CImage m_image;
protected:
	int m_nPos;
	int m_nCurentPage;
	int m_idx;
	int m_nHLidx;
public:
	void SetPageY(CChapPage& cp);
public:
	void DrawPage(CDC* pDC);
public:
	void SetScrollBar(int cx, int cy);
public:
	void PaintRect(CRect& rc, COLORREF color);
public:
	void SetLogicDC(CDC* pDC);
public:
	int CanNext(void);
public:
	int CanPrior(void);
public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
public:
	bool m_bHandCursor;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	int m_nHeadLine;
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


