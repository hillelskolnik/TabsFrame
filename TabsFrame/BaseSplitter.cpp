// BaseSplitter.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "BaseSplitter.h"


// CBaseSplitter

IMPLEMENT_DYNAMIC(CBaseSplitter, CSplitterWnd)

CBaseSplitter::CBaseSplitter()
{

}

CBaseSplitter::~CBaseSplitter()
{
}


BEGIN_MESSAGE_MAP(CBaseSplitter, CSplitterWnd)
END_MESSAGE_MAP()



// CBaseSplitter message handlers



BOOL CBaseSplitter::CreateDlg(int row, int col, CDialog* pWnd, SIZE sizeInit, UINT uId)
{
	ASSERT_VALID(this);
	ASSERT(row >= 0 && row < m_nRows);
	ASSERT(col >= 0 && col < m_nCols);

	if (GetDlgItem(IdFromRowCol(row, col)) != NULL)
	{
		TRACE2("Error: CreateView - pane already exists for row %d, col %d.\n",
			row, col);
		ASSERT(FALSE);
		return FALSE;
	}
	m_pColInfo[col].nIdealSize = sizeInit.cx;
	m_pRowInfo[row].nIdealSize = sizeInit.cy;

	BOOL bSendInitialUpdate = FALSE;
	ASSERT(pWnd->m_hWnd == NULL);       // not yet created

	DWORD dwStyle = AFX_WS_DEFAULT_VIEW;
	//yby if (afxData.bWin4)
		dwStyle &= ~WS_BORDER;

	// Create with the right size (wrong position)
	//CRect rect(CPoint(0,0), sizeInit);
	if (!pWnd->Create(uId, this))
	{
		TRACE0("Warning: couldn't create client pane for splitter.\n");
			// pWnd will be cleaned up by PostNcDestroy
		return FALSE;
	}

	pWnd->ModifyStyle(0, AFX_WS_DEFAULT_VIEW);
	//yby<
	pWnd->ModifyStyle(WS_BORDER|WS_POPUP|WS_CAPTION|WS_SYSMENU, WS_CHILD);
	pWnd->ModifyStyle(WS_THICKFRAME|WS_CLIPSIBLINGS, 0); //Dialog
	pWnd->ModifyStyleEx(WS_EX_WINDOWEDGE|WS_EX_CONTROLPARENT, 0); //Dialog
	pWnd->ModifyStyleEx(WS_EX_NOPARENTNOTIFY, 0); //TabCtrl
	//pWnd->ModifyStyleEx(0, WS_EX_CONTROLPARENT, 0); //Dialog
	//yby>
	//pWnd->SetParent(this);

	pWnd->ShowWindow(SW_SHOW);
	pWnd->SetDlgCtrlID(IdFromRowCol(row,col) );

	ASSERT((int)pWnd->GetDlgCtrlID() == IdFromRowCol(row, col));

	return TRUE;
}
// BaseSplitter.cpp : implementation file
//

// CBasePerekSplit

IMPLEMENT_DYNCREATE(CBasePerekSplit, CBaseSplitter)

CBasePerekSplit::CBasePerekSplit()
: m_bIsSplitCreated(false)
{

}

CBasePerekSplit::~CBasePerekSplit()
{
}

BEGIN_MESSAGE_MAP(CBasePerekSplit, CBaseSplitter)
END_MESSAGE_MAP()


// CBasePerekSplit diagnostics

#ifdef _DEBUG
void CBasePerekSplit::AssertValid() const
{
	CWnd::AssertValid();
}

#ifndef _WIN32_WCE
void CBasePerekSplit::Dump(CDumpContext& dc) const
{
	CWnd::Dump(dc);
}
#endif
#endif //_DEBUG


void CBaseSplitter::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect)
{
	if (pDC == NULL)
	{
		RedrawWindow(rect, NULL, RDW_INVALIDATE|RDW_NOCHILDREN);
		return;
	}
	CRect rc = rect;
	switch (nType)
	{
	case splitBorder:
		pDC->Draw3dRect(rc, RGB(32,0,64), RGB(32,0,64));
		rc.InflateRect(-1, -1);
		pDC->Draw3dRect(rc, RGB(32,0,64), RGB(32,0,64));
		return;

	case splitIntersection:
	case splitBar:
		pDC->FillSolidRect(rc, RGB(64,0,128));
		return;
	}

	CSplitterWnd::OnDrawSplitter(pDC, nType, rect);
}

// CBasePerekSplit message handlers

BOOL CBasePerekSplit::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	CWnd *pWnd = NULL;
	switch(message)
	{
	case WM_SET_WND_SUBTYPE:
		pWnd = GetPane(0,1);
		if(pWnd)
			pWnd->SendMessageA(WM_SET_WND_SUBTYPE, wParam, lParam);
		return TRUE;
	case BASIC_DLL_MSG:
		pWnd = GetPane(0,1);
		if(pWnd)
			pWnd->SendMessageA(message, wParam, lParam);
		return TRUE;
	case WM_GET_WT:
		pWnd = GetPane(0,1);
		if(pWnd)
			*pResult = pWnd->SendMessageA(message, wParam, lParam);
		return TRUE;
	}

	return CBaseSplitter::OnWndMsg(message, wParam, lParam, pResult);
}

BOOL CBasePerekSplit::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	CWnd *pWnd = GetPane(0,1);
	if(pWnd && pWnd->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	return CBaseSplitter::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
