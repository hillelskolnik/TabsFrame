#pragma once


// CBook

class CMainFrame;

class CBook : public CSplitterWnd
{
	DECLARE_DYNCREATE(CBook)

public:
	CBook();
	virtual ~CBook();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void Create(void);
protected:
	CMainFrame* m_pMainFrame;
	CSplitterWnd m_split2;

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	bool m_bIsSplitCreated;
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};


