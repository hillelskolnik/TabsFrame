// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TabsFrame.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_UPDATE_COMMAND_UI(IDB_BTNDEL, &CMainFrame::OnUpdateButtonDel)
	ON_UPDATE_COMMAND_UI(ID_SHOW_BOOK, &CMainFrame::OnUpdateButtonDel)
	ON_UPDATE_COMMAND_UI(IDC_TAB1, &CMainFrame::OnUpdateTab)
	ON_COMMAND(IDB_BTNDEL, &CMainFrame::OnButtonDel)
	ON_COMMAND(ID_SHOW_BOOK, &CMainFrame::OnButtomShowBook)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndDlgBar.CreateEx(this))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	m_wndDlgBar.InsertWnd(0, WT_BOOK);
	m_wndDlgBar.m_tab.SetCurSel(0);

	CMenu *pMenu = GetMenu();
	if(pMenu)
	{
		static CBrush br(RGB(123,157,234));
		MENUINFO mi;
		memset(&mi,0,sizeof(mi));
		mi.cbSize = sizeof(mi);
		mi.fMask = MIM_BACKGROUND;
		mi.hbrBack = (HBRUSH)br;
		pMenu->SetMenuInfo(&mi);
	}

	SetIcon(theApp.LoadIconA(IDI_ICON_CAPSTION2),FALSE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	CWnd *pWnd = m_wndDlgBar.GetCurWnd();
	if(pWnd)
		pWnd->SetFocus();
//	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	//if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	//	return TRUE;
	CWnd *pWnd = m_wndDlgBar.GetCurWnd();
	if(pWnd && pWnd->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	
	CFrameWnd::OnSize(nType, cx, cy);

}

void CMainFrame::OnUpdateButtonDel(CCmdUI *pCmdUI)
{
	int count = m_wndDlgBar.m_tab.GetItemCount();
	int current = m_wndDlgBar.m_tab.GetCurSel();
	pCmdUI->Enable(count > 0 && current > 0);
}
void CMainFrame::OnUpdateTab(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CMainFrame::OnButtonDel()
{
	m_wndDlgBar.DelWnd();
}

BOOL CMainFrame::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_SHOW_GRAPH:
		{
			int idx = (int)m_wndDlgBar.SendMessage(WM_GET_CHL_IDX);
			m_wndDlgBar.ShowWnd(idx - IDX_PEREK_2 + WT_PEREK_2, (int)wParam);
		}
		return TRUE;
	}

	return CFrameWnd::OnWndMsg(message, wParam, lParam, pResult);
}

void CMainFrame::OnButtomShowBook()
{
	m_wndDlgBar.m_tab.SetCurSel(0);
	m_wndDlgBar.ShowCurWnd();
}

void CMainFrame::OnUpdateFrameMenu(HMENU hMenuAlt)
{
	// TODO: Add your specialized code here and/or call the base class
	CFrameWnd::OnUpdateFrameMenu(hMenuAlt);
}

void CMainFrame::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpD)
{
	if(nIDCtl == IDR_MAINFRAME)
	{
		if(lpD->itemAction & ODA_DRAWENTIRE)
		{
		}
	}

	CFrameWnd::OnDrawItem(nIDCtl, lpD);
}
