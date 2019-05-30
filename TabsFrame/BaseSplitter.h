#pragma once


// CBaseSplitter

class CBaseSplitter : public CSplitterWnd
{
	DECLARE_DYNAMIC(CBaseSplitter)

public:
	CBaseSplitter();
	virtual ~CBaseSplitter();

protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL CreateDlg(int row, int col, CDialog* pWnd, SIZE sizeInit, UINT uId);
public:
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);
};



// CBasePerekSplit view

class CBasePerekSplit : public CBaseSplitter
{
	DECLARE_DYNCREATE(CBasePerekSplit)

protected:
	CBasePerekSplit();           // protected constructor used by dynamic creation
	virtual ~CBasePerekSplit();

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	virtual void Create(UINT nPane){ASSERT(1);};
protected:
	bool m_bIsSplitCreated;
public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
};


