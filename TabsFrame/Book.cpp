// Book.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Book.h"

#include "HeadLineView.h"
#include "BookKeyList.h"
#include "BookPage.h"
#include "MainFrm.h"




// CBook

IMPLEMENT_DYNCREATE(CBook, CSplitterWnd)

CBook::CBook()
: m_pMainFrame(NULL)
, m_bIsSplitCreated(false)
{
}

CBook::~CBook()
{
}


BEGIN_MESSAGE_MAP(CBook, CSplitterWnd)
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CBook message handlers



void CBook::Create(void)
{
	m_pMainFrame = (CMainFrame*)AfxGetMainWnd();

	CreateStatic(m_pMainFrame,1,2);
	m_split2.CreateStatic(this,2,1,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		IdFromRowCol(0,1));

	CRect rc;
	m_pMainFrame->GetClientRect(rc);

	CreateView(0,0,RUNTIME_CLASS(CBookPage), CSize(0, 0), NULL);
	m_split2.CreateView(0,0,RUNTIME_CLASS(CBookKeyList), CSize(0, 0), NULL);
	m_split2.CreateView(1,0,RUNTIME_CLASS(CHeadLineView), CSize(0, 0), NULL);

	m_bIsSplitCreated = true;
	OnSize(0, rc.Width(), rc.Height());

}

void CBook::OnSize(UINT nType, int cx, int cy)
{
	CSplitterWnd::OnSize(nType, cx, cy);

	int fourfifthx = 4 * cx / 5;
	if(GetSafeHwnd() && m_bIsSplitCreated)
	{
		SetColumnInfo(0, fourfifthx, 10);
		SetColumnInfo(1, cx - fourfifthx, 10);
		CRect rc;
		m_split2.GetClientRect(rc);
		m_split2.SetRowInfo(0, rc.Height()/2, rc.Height()/4);
		RecalcLayout();
		m_split2.RecalcLayout();
	}
}

BOOL CBook::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	CWnd *pWnd = NULL;
	switch(message)
	{
	case WM_GET_CHL_IDX:
		pWnd = m_split2.GetPane(0,0);
		*pResult = pWnd->SendMessage(message);
		if(wParam)
		{
			pWnd = m_split2.GetPane(1,0);
			pWnd->SendMessage(message, wParam);
		}
		return TRUE;
		case WM_LOAD_PAGE:
			if((int)lParam == -1)
			{
				m_split2.GetPane(1,0)->PostMessage(WM_FILL_HEADLINES ,wParam);
			}
			GetPane(0,0)->PostMessageA(message, wParam, lParam);
			return TRUE;
		case WM_SET_HEADLINE:
				pWnd = m_split2.GetPane(1,0);
				pWnd->PostMessage(message, wParam);
			return TRUE;
	}

	return CSplitterWnd::OnWndMsg(message, wParam, lParam, pResult);
}
