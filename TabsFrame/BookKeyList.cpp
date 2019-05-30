// BookKeyList.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "BookKeyList.h"


// CBookKeyList

IMPLEMENT_DYNCREATE(CBookKeyList, CListView)

CBookKeyList::CBookKeyList()
{

}

CBookKeyList::~CBookKeyList()
{
}


BEGIN_MESSAGE_MAP(CBookKeyList, CListView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &CBookKeyList::OnLvnItemchanged)
END_MESSAGE_MAP()



// CBookKeyList message handlers

BOOL CBookKeyList::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= LVS_REPORT | LVS_NOCOLUMNHEADER  | LVS_OWNERDRAWFIXED ;

	return CListView::PreCreateWindow(cs);
}

int CBookKeyList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_imageList.Create(1,48, ILC_COLOR4,1,1);
	m_imageList.Add(AfxGetApp()->LoadIconA(IDI_ICON_LIST_HEIGHT));
	CListCtrl &list = GetListCtrl();
	list.SetImageList(&m_imageList, LVSIL_STATE);
	list.InsertColumn(0, 0, 0, lpCreateStruct->cx - 20);
	CFont *font = list.GetFont();
	LOGFONT lf;
	font->GetLogFont(&lf);
	lf.lfCharSet = HEBREW_CHARSET;
	lf.lfHeight  = -9;
	static CFont m_font;
	m_font.CreateFontIndirectA(&lf);
	list.SetFont(&m_font);

	CChapPageArr &cpa = theApp.m_chaptersParagraphs.m_chapPageArr;
	int size = (int)cpa.GetCount();
	for(int i = 0; i < size; ++i)
	{
		list.InsertItem(i, cpa[i].sChap, 0);
	}

	list.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);

	return 0;
}

void CBookKeyList::DrawItem(LPDRAWITEMSTRUCT lpD)
{
	CListCtrl &list = GetListCtrl();
	LVITEM item;
	memset(&item, 0, sizeof(LVITEM));
	item.mask = LVIF_STATE ;//| LVIF_TEXT;
	item.iItem = lpD->itemID;
	item.stateMask = LVIS_SELECTED ;//| LVIS_FOCUSED;
	list.GetItem(&item);

	CRect rc = lpD->rcItem;
	CDC *pDC = CDC::FromHandle(lpD->hDC);
	COLORREF tc = 0, bc =0;
	pDC->FillSolidRect(rc, RGB(255,255,255));
	rc.DeflateRect(1,1);
	int xd = 0;
	BOOL bSelected = item.state & LVIS_SELECTED;
	if(bSelected)
	{
		//bc = RGB(48,120,200);
		tc = RGB(255,128,255);
		pDC->SetTextColor(tc);//RGB(32,64,128));
		pDC->SetBkColor(bc);
		pDC->DrawEdge(rc,EDGE_SUNKEN, BF_RECT);
		xd = 2;
	
	}
	else
	{
		//bc = RGB(64,147,255);
		tc = RGB(160,255,160);
		pDC->SetTextColor(tc);//RGB(64,147,255));//white);
		pDC->SetBkColor(bc);
		pDC->DrawEdge(rc,EDGE_RAISED, BF_RECT);
	}

	rc.DeflateRect(xd?3:2,2);
	//CBrush br(bc);
	//pDC->FillRect(rc, &br);
	if(bSelected)
	{
		RectPaint(rc,pDC,RGB(92,92,92),0,-90,90);
	}
	else
	{
		RectPaint(rc,pDC,0,RGB(92,92,92),-90,90);
	}
	CString sText  = list.GetItemText(lpD->itemID, 0);
	rc.DeflateRect(xd + 1,1);
	pDC->DrawText(sText, rc, DT_RIGHT | DT_WORDBREAK);
}

void CBookKeyList::OnSize(UINT nType, int cx, int cy)
{
	CListView::OnSize(nType, cx, cy);

	CListCtrl &list = GetListCtrl();
	if(list.GetSafeHwnd())
	{
		list.SetColumnWidth(0, cx - 2);
	}
}

void CBookKeyList::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if(pNMLV->uNewState & LVIS_SELECTED)
	{
		GetParent()->GetParent()->PostMessage(WM_LOAD_PAGE, pNMLV->iItem, -1);
	}
	*pResult = 0;
}

BOOL CBookKeyList::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	CListCtrl &list = GetListCtrl();
	switch(message)
	{
	case WM_GET_CHL_IDX:
		*pResult = list.GetNextItem(-1, LVIS_SELECTED);
		return TRUE;
	}

	return CListView::OnWndMsg(message, wParam, lParam, pResult);
}
