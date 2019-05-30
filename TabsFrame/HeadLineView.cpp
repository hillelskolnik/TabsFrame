// HeadLineView.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "HeadLineView.h"


// CHeadLineView

IMPLEMENT_DYNCREATE(CHeadLineView, CListView)

CHeadLineView::CHeadLineView()
{

}

CHeadLineView::~CHeadLineView()
{
}

BEGIN_MESSAGE_MAP(CHeadLineView, CListView)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &CHeadLineView::OnLvnItemchanged)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CHeadLineView diagnostics

#ifdef _DEBUG
void CHeadLineView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CHeadLineView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHeadLineView message handlers

void CHeadLineView::DrawItem(LPDRAWITEMSTRUCT lpD)
{
	CListCtrl &list = GetListCtrl();
	LVITEM item;
	memset(&item, 0, sizeof(LVITEM));
	item.mask = LVIF_STATE | LVIF_PARAM;//| LVIF_TEXT;
	item.iItem = lpD->itemID;
	item.stateMask = LVIS_SELECTED ;//| LVIS_FOCUSED;
	list.GetItem(&item);

	CRect rc = lpD->rcItem;
	CDC *pDC = CDC::FromHandle(lpD->hDC);
	COLORREF white = RGB(241,248,255);
	if(item.state & LVIS_SELECTED)
	{
		pDC->SetTextColor((COLORREF)item.lParam);//RGB(32,64,128));
		pDC->SetBkColor(0);//white);
		pDC->FillSolidRect(rc, 0);//);
	}
	else
	{
		pDC->SetTextColor(0);//white);
		pDC->SetBkColor((COLORREF)item.lParam);//RGB(64,147,255));
		pDC->FillSolidRect(rc, (COLORREF)item.lParam);//RGB(64,147,255));
	}
	CBrush br(white);
	pDC->FrameRect(rc, &br);
	rc.DeflateRect(5,1);
	CString sText  = list.GetItemText(lpD->itemID, 0);
	pDC->DrawText(sText, rc, DT_RIGHT | DT_SINGLELINE);
}

BOOL CHeadLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT | LVS_NOCOLUMNHEADER  | LVS_OWNERDRAWFIXED 
		| LVS_SINGLESEL;

	return CListView::PreCreateWindow(cs);
}

BOOL CHeadLineView::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	CListCtrl &list = GetListCtrl();
	switch(message)
	{
	case WM_GET_CHL_IDX:
		if(wParam)
		{
			*((UINT_PTR*)wParam) = list.GetNextItem(-1, LVIS_SELECTED);
		}
		return TRUE;
	case WM_FILL_HEADLINES:
		{
			int idx = (int)wParam;
			CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[idx];
			INT_PTR size = cp.paragraphs.GetCount();
			//if(size == 0)
			//	return TRUE;

			CListCtrl &list = GetListCtrl();
			list.DeleteAllItems();
			
			for(INT_PTR i = 0; i < size; ++i)
			{
				list.InsertItem((int)i, cp.paragraphs[i].sParagraph,0);
				list.SetItemData((int)i, (DWORD_PTR)cp.paragraphs[i].color);
			}
		}
		return TRUE;
	case WM_SET_HEADLINE:
		list.SetItemState((int)wParam, LVIS_SELECTED, LVIS_SELECTED);
		return TRUE;
	}

	return CListView::OnWndMsg(message, wParam, lParam, pResult);
}

void CHeadLineView::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if(pNMLV->uNewState & LVIS_SELECTED)
	{
		GetParent()->GetParent()->PostMessage(WM_LOAD_PAGE, -2, pNMLV->iItem);
	}
	*pResult = 0;
}

int CHeadLineView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CListCtrl &list = GetListCtrl();
	list.InsertColumn(0,"", 0, 100);

	CFont *font = list.GetFont();
	LOGFONT lf;
	font->GetLogFont(&lf);
	lf.lfCharSet = HEBREW_CHARSET;
	lf.lfHeight  = -9;
	static CFont m_font;
	m_font.CreateFontIndirectA(&lf);
	list.SetFont(&m_font);


	return 0;
}

void CHeadLineView::OnSize(UINT nType, int cx, int cy)
{
	CListView::OnSize(nType, cx, cy);

	CListCtrl &list = GetListCtrl();
	CRect rc;
	list.GetClientRect(rc);
	list.SetColumnWidth(0, rc.Width()- 1);
}

void CHeadLineView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CListCtrl &list = GetListCtrl();
	int idx = list.GetNextItem(-1, LVIS_SELECTED);
	if(idx != -1)
	{
		AfxGetMainWnd()->PostMessageA(WM_SHOW_GRAPH, idx);
	}

	CListView::OnLButtonDblClk(nFlags, point);
}
