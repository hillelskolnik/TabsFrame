#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "book.h"
#include "tabexctrl.h"
#include "buttonex.h"


// CTabDlg dialog

enum
{
	TAB_CY = 20
};

class CMainFrame;


class CTabDlg : public CToolBar
{
	DECLARE_DYNAMIC(CTabDlg)

public:
	CBook m_split;
	CTabDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTabDlg();

// Dialog Data
	enum { IDD = IDC_TABS };

protected:

	DECLARE_MESSAGE_MAP()
public:
	//virtual BOOL OnInitDialog();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	// the tab
	CTabExCtrl m_tab;
	CButtonEx m_btnBook;
	CButtonEx m_btnDel;
public:
	// Delete tab and window
//	CButton m_btnDel;
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	bool InsertWnd(int nSel, int nType, int nSubType = 0);
protected:
	CMainFrame* m_pMainFrame;
	CImageList m_imageList;
	CMap<int, int, int, int> m_paneId;
	CBitmap m_bitmap;
public:
	CWnd* GetCurWnd(void);
public:
	void DelWnd(void);
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	void ShowWnd(int ntype, int nSubType);
	int ShowCurWnd(void);
protected:
	int nLastselect;
	void CreateNewView(TCITEMA& item, CString sCaption, CRuntimeClass* pNewViewClass, int nSubType, int nPane, int nSel);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
