#pragma once


// CBookKeyList

class CBookKeyList : public CListView
{
	DECLARE_DYNCREATE(CBookKeyList)

public:
	CBookKeyList();
	virtual ~CBookKeyList();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	CImageList m_imageList;
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};


