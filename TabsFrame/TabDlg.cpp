// TabDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "TabDlg.h"

#include "BookKeyList.h"
#include "BookPage.h"
#include "MainFrm.h"
#include "BaseSplitter.h"

#include "Perek2.h"
#include "Perek3.h"
#include "Perek4.h"
#include "Perek5.h"
#include "Perek6.h"
#include "Perek7.h"
#include "Perek10.h"
#include "Perek11.h"
#include "Perek12.h"
#include "Perek13.h"
#include "Perek14.h"
#include "Perek15.h"
#include "Perek16.h"
#include "Perek17.h"
#include "Perek18.h"
#include "Perek19.h"
#include "Perek20.h"
#include "Perek21.h"
#include "Perek22.h"
#include "Perek23.h"
#include "Perek24.h"
#include "Perek25.h"
#include "Perek26.h"
#include "Perek27.h"
#include "Perek28.h"
#include "Perek29.h"
#include "Perek30.h"
#include "Perek31.h"
#include "Perek32.h"
#include "Perek33.h"
#include "Perek34.h"
#include "Perek35.h"
#include "Perek36.h"
#include "Perek37.h"
#include "Perek38.h"
#include "Perek39.h"
#include "Perek41.h"
#include "Perek42.h"
#include "Perek43.h"
#include "Perek44.h"
#include "Perek45.h"
#include "Perek46.h"
#include "Perek47.h"
#include "Perek48.h"
#include "Perek49.h"
#include "Perek50.h"


const int nOffset = 24;


// CTabDlg dialog

IMPLEMENT_DYNAMIC(CTabDlg, CToolBar)

CTabDlg::CTabDlg(CWnd* pParent /*=NULL*/)
//	: CDialogBar(CTabDlg::IDD, pParent)
: m_pMainFrame(NULL)
, nLastselect(0)
{
	m_bitmap.LoadBitmapA(IDB_BITMAP1);
}

CTabDlg::~CTabDlg()
{
}


BEGIN_MESSAGE_MAP(CTabDlg, CToolBar)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTabDlg::OnTcnSelchangeTab1)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTabDlg message handlers

void CTabDlg::OnSize(UINT nType, int cx, int cy)
{
	CToolBar::OnSize(nType, cx, cy);


	if(m_tab.GetSafeHwnd())
	{
		SetButtonInfo(0, IDC_TAB1,  TBBS_SEPARATOR, cx);
		m_tab.MoveWindow(0,0,cx - nOffset*2 ,cy);
		CRect rcBtn(cx - nOffset*2,0,cx - nOffset,cy);
		m_btnBook.MoveWindow(rcBtn);
		rcBtn.MoveToX(cx - nOffset);
		m_btnDel.MoveWindow(rcBtn);
	}
}

void CTabDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShowCurWnd();
	*pResult = 0;
}

int CTabDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	int cx = lpCreateStruct->cx;
	int cy = lpCreateStruct->cy;
	m_pMainFrame = (CMainFrame *)AfxGetMainWnd();
	CToolBarCtrl &tool = GetToolBarCtrl();
	tool.SetBitmapSize(CSize(1,15));
	SetBitmap(m_bitmap);
	TBBUTTON tb;
	memset(&tb, 0, sizeof(tb));
	tb.fsStyle = TBSTYLE_BUTTON;
	tb.iString = -1;
	tb.idCommand = IDC_TAB1;
	tool.InsertButton(0,&tb);
	tool.InsertButton(1,&tb);
	SetButtonInfo(0, IDC_TAB1,  TBBS_SEPARATOR, cx /*- nOffset*/);



	m_imageList.Create(IDB_BITMAP_TAB, 17, 1,  0);
	m_tab.Create(WS_CHILD | WS_VISIBLE | TCS_OWNERDRAWFIXED, 
		CRect(0,0,cx - nOffset*2,cy), this, IDC_TAB1);
	m_tab.SetImageList(&m_imageList);

	m_btnBook.Create(NULL, WS_CHILD | WS_VISIBLE | BS_BITMAP 
		| BS_OWNERDRAW 
		,CRect(cx - nOffset*2,0,cx - nOffset,cy),this, ID_SHOW_BOOK);
	static CBitmap bm;
	if(bm.GetSafeHandle() == NULL)
		bm.LoadBitmapA(IDB_BITMAP_TAB);
	m_btnBook.SetBitmap(bm);

	m_btnDel.Create(NULL, WS_CHILD | WS_VISIBLE | BS_BITMAP 
		| BS_OWNERDRAW 
		,CRect(cx - nOffset,0,cx,cy),this, IDB_BTNDEL);
	static CBitmap bm2;
	if(bm2.GetSafeHandle() == NULL)
		bm2.LoadBitmapA(IDB_BITMAP_DEL);
	m_btnDel.SetBitmap(bm2);

	tool.HideButton(1);


	return 0;
}

bool CTabDlg::InsertWnd(int nSel, int nType, int nSubType)
{
	int nPane = AFX_IDW_PANE_FIRST + 1;
	if(nSel)
	{
		while(m_paneId.Lookup(nPane, nPane))
		{
			++nPane;
		}
	}
	TCITEMA item;
	item.mask = TCIF_PARAM | TCIF_TEXT | TCIF_IMAGE;
	switch(nType)
	{
	case WT_BOOK:
		m_split.Create();
		m_split.ShowWindow(SW_SHOW);		
		item.pszText = "תכונת השמים";
		item.cchTextMax = 12;
		item.iImage = 0;
		item.lParam = (LPARAM)&(m_split);
		m_tab.InsertItem(nSel, &item);
		break;
		// TODO Make class factory for the rest
	case WT_PEREK_2:
		CreateNewView(item, "פרק ב", RUNTIME_CLASS(CPerek2), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_3:
		CreateNewView(item, "פרק ג", RUNTIME_CLASS(CPerek3), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_4:
		CreateNewView(item, "פרק ד", RUNTIME_CLASS(CPerek4), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_5:
		CreateNewView(item, "פרק ה", RUNTIME_CLASS(CPerek5), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_6:
		CreateNewView(item, "פרק ו", RUNTIME_CLASS(CPerek6), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_7:
		CreateNewView(item, "פרק ז", RUNTIME_CLASS(CPerek7), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_10:
		CreateNewView(item, "פרק י", RUNTIME_CLASS(CPerek10), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_11:
		CreateNewView(item, "פרק יא", RUNTIME_CLASS(CPerek11), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_12:
		CreateNewView(item, "פרק יב", RUNTIME_CLASS(CPerek12), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_13:
		CreateNewView(item, "פרק יג", RUNTIME_CLASS(CPerek13), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_14:
		CreateNewView(item, "פרק יד", RUNTIME_CLASS(CPerek14), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_15:
		CreateNewView(item, "פרק טו", RUNTIME_CLASS(CPerek15), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_16:
		CreateNewView(item, "פרק טז", RUNTIME_CLASS(CPerek16), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_17:
		CreateNewView(item, "פרק יז", RUNTIME_CLASS(CPerek17), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_18:
		CreateNewView(item, "פרק יח", RUNTIME_CLASS(CPerek18), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_19:
		CreateNewView(item, "פרק יט", RUNTIME_CLASS(CPerek19), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_20:
		CreateNewView(item, "פרק כ", RUNTIME_CLASS(CPerek20), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_21:
		CreateNewView(item, "פרק כא", RUNTIME_CLASS(CPerek21), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_22:
		CreateNewView(item, "פרק כב", RUNTIME_CLASS(CPerek22), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_23:
		CreateNewView(item, "פרק כג", RUNTIME_CLASS(CPerek23), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_24:
		CreateNewView(item, "פרק כד", RUNTIME_CLASS(CPerek24), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_25:
		CreateNewView(item, "פרק כה", RUNTIME_CLASS(CPerek25), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_26:
		CreateNewView(item, "פרק כו", RUNTIME_CLASS(CPerek26), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_27:
		CreateNewView(item, "פרק כז", RUNTIME_CLASS(CPerek27), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_28:
		CreateNewView(item, "פרק כח", RUNTIME_CLASS(CPerek28), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_29:
		CreateNewView(item, "פרק כט", RUNTIME_CLASS(CPerek29), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_30:
		CreateNewView(item, "פרק ל", RUNTIME_CLASS(CPerek30), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_31:
		CreateNewView(item, "פרק לא", RUNTIME_CLASS(CPerek31), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_32:
		CreateNewView(item, "פרק לב", RUNTIME_CLASS(CPerek32), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_33:
		CreateNewView(item, "פרק לג", RUNTIME_CLASS(CPerek33), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_34:
		CreateNewView(item, "פרק לד", RUNTIME_CLASS(CPerek34), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_35:
		CreateNewView(item, "פרק לה", RUNTIME_CLASS(CPerek35), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_36:
		CreateNewView(item, "פרק לו", RUNTIME_CLASS(CPerek36), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_37:
		CreateNewView(item, "פרק לז", RUNTIME_CLASS(CPerek37), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_38:
		CreateNewView(item, "פרק לח", RUNTIME_CLASS(CPerek38), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_39:
		CreateNewView(item, "פרק לט", RUNTIME_CLASS(CPerek39), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_41:
		CreateNewView(item, "פרק מא", RUNTIME_CLASS(CPerek41), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_42:
		CreateNewView(item, "פרק מב", RUNTIME_CLASS(CPerek42), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_43:
		CreateNewView(item, "פרק מג", RUNTIME_CLASS(CPerek43), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_44:
		CreateNewView(item, "פרק מד", RUNTIME_CLASS(CPerek44), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_45:
		CreateNewView(item, "פרק מה", RUNTIME_CLASS(CPerek45), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_46:
		CreateNewView(item, "פרק מו", RUNTIME_CLASS(CPerek46), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_47:
		CreateNewView(item, "פרק מז", RUNTIME_CLASS(CPerek47Split), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_48:
		CreateNewView(item, "פרק מח", RUNTIME_CLASS(CPerek48Split), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_49:
		CreateNewView(item, "פרק מט", RUNTIME_CLASS(CPerek49Split), nSubType,
			nPane, nSel);
		break;
	case WT_PEREK_50:
		CreateNewView(item, "פרק נ", RUNTIME_CLASS(CPerek50Split), nSubType,
			nPane, nSel);
		break;
	default:
		return false;
	}

	return true;
}

CWnd* CTabDlg::GetCurWnd(void)
{
	if(m_tab.GetSafeHwnd() == NULL)
		return NULL;

	int  idx = m_tab.GetCurSel();
	if(idx < 0)
		return NULL;
	TCITEMA item;
	item.mask = TCIF_PARAM;
	m_tab.GetItem(idx, &item);
	CWnd *pWndNew = (CWnd*)item.lParam;
	return pWndNew;
}

void CTabDlg::DelWnd(void)
{
	int  idx = m_tab.GetCurSel();
	if(idx < 0)
		return ;
	TCITEMA item;
	item.mask = TCIF_PARAM;
	m_tab.GetItem(idx, &item);
	CWnd *pWndDel = (CWnd*)item.lParam;
	m_tab.DeleteItem(idx);

	int count = m_tab.GetItemCount();
	if(count == idx)
		--idx;
	m_tab.GetItem(idx, &item);
	CWnd *pWndShow = (CWnd*)item.lParam;
	pWndShow->ShowWindow(SW_SHOW);
	pWndShow->SetDlgCtrlID(AFX_IDW_PANE_FIRST);

	nLastselect = idx;
	m_tab.SetCurSel(idx);

	pWndDel->DestroyWindow();
	
}

BOOL CTabDlg::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_GET_CHL_IDX:
		*pResult = m_split.SendMessage(message, wParam, lParam);
		return TRUE;
	}

	return CToolBar::OnWndMsg(message, wParam, lParam, pResult);
}

void CTabDlg::ShowWnd(int ntype, int nSubType)
{
	int idx = m_tab.GetItemCount();
	for(int i=0; i<idx;++i)
	{
		TCITEMA item;
		item.mask = TCIF_PARAM;
		m_tab.GetItem(i, &item);
		CWnd *pWnd = (CWnd*)item.lParam;
		int nwndType = (int)pWnd->SendMessage(WM_GET_WT);
		if(nwndType == ntype)
		{
			pWnd->PostMessageA(WM_SET_WND_SUBTYPE, nSubType);
			m_tab.SetCurSel(i);
			ShowCurWnd();
			return;
		}
	}
	if(InsertWnd(idx, ntype, nSubType))
	{
		m_tab.SetCurSel(idx);
		ShowCurWnd();
	}
}

int CTabDlg::ShowCurWnd(void)
{
	
	int  idx = m_tab.GetCurSel();
	TCITEMA item;
	item.mask = TCIF_PARAM;
	m_tab.GetItem(idx, &item);
	CWnd *pWndNew = (CWnd*)item.lParam;
	m_tab.GetItem(nLastselect, &item);
	CWnd *pWndOld = (CWnd*)item.lParam;
	pWndNew->ShowWindow(SW_SHOW);
	pWndOld->ShowWindow(SW_HIDE);
	int nNewId = pWndNew->GetDlgCtrlID();
	int nOldId = pWndOld->GetDlgCtrlID();
	pWndNew->SetDlgCtrlID(nOldId);
	pWndOld->SetDlgCtrlID(nNewId);

	CRuntimeClass *pClass = pWndNew->GetRuntimeClass();
	CString sClassName = pClass->m_lpszClassName;
	if(pClass->IsDerivedFrom(RUNTIME_CLASS(CView)))
	{
		m_pMainFrame->SetActiveView((CView*)pWndNew);
	}
	else if(pClass->IsDerivedFrom(RUNTIME_CLASS(CSplitterWnd)))
	{
		CSplitterWnd *pSplit = (CSplitterWnd*)pWndNew;
		if(sClassName == "CBook")
			pWndNew = pSplit->GetPane(0,0);
		else
			pWndNew = pSplit->GetPane(0,1);

		pSplit->RecalcLayout();
		m_pMainFrame->SetActiveView((CView*)pWndNew);
		if(sClassName != "CBook")
			((CSplitterWnd*)(pSplit->GetPane(0,0)))->GetPane(1,0)->SetFocus();
	}
	m_pMainFrame->RecalcLayout();

	nLastselect = idx;

//	m_tab.SetCurFocus(nLastselect);
	SetTimer(1, 10, NULL);
	return 0;
}

void CTabDlg::CreateNewView(TCITEMA& item, 
							CString sCaption, 
							CRuntimeClass* pNewViewClass,
							int nSubType,
							int nPane, int nSel)
{
	CWnd* pWnd = NULL;
	if(pNewViewClass->IsDerivedFrom(RUNTIME_CLASS(CBasePerekSplit)))
	{
		CBasePerekSplit *pBaseSplit = (CBasePerekSplit*)pNewViewClass->CreateObject();
		pBaseSplit->Create(nPane);
		pWnd = pBaseSplit;
	}
	else
	{
		CCreateContext cctxt;
		cctxt.m_pCurrentFrame = m_pMainFrame;
		cctxt.m_pNewViewClass = pNewViewClass;
		pWnd = m_pMainFrame->CreateView(&cctxt, nPane);
	}
	item.iImage = -1;
	item.pszText = sCaption.GetBuffer();
	item.cchTextMax = sCaption.GetLength() + 1;
	item.lParam = (LPARAM)pWnd;
	m_tab.InsertItem(nSel, &item);
	pWnd->SendMessageA(WM_SET_WND_SUBTYPE, nSubType);
	sCaption.ReleaseBuffer();
}

void CTabDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 1)
	{
		Invalidate(FALSE);
		//CRect rc;
		//m_tab.GetClientRect(rc);
		//m_tab.InvalidateRect(rc);
		//int size = m_tab.GetItemCount();
		//for(int i = 0; i < size; ++i)
		//	m_tab.SetCurFocus(i);
		//m_tab.SetCurFocus(nLastselect);
		KillTimer(1);
	}

	CToolBar::OnTimer(nIDEvent);
}
