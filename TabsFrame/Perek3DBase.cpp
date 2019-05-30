// Perek3DBase.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek3DBase.h"


// CPerek3DBase

IMPLEMENT_DYNCREATE(CPerek3DBase, CPerek2DBase)

CPerek3DBase::CPerek3DBase()
: m_bSkip(false)
, m_bPastCreate(false)
, m_pt(ipWidth/2,ipHeight/2)
, m_xTurn(0)
, m_yTurn(0)
, m_nCaptionBottom(160)
{
	m_bNoDilay = false;
}

CPerek3DBase::~CPerek3DBase()
{
	m_scale.Clean();
}

BEGIN_MESSAGE_MAP(CPerek3DBase, CPerek2DBase)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPerek3DBase drawing

//void CPerek3DBase::OnDraw(CDC* pDC)
//{
//	CDocument* pDoc = GetDocument();
//
//	DoDrawing(pDC);
//	m_scale.Paint();
//	m_3dscreen.OnPaint();
//}


// CPerek3DBase diagnostics

#ifdef _DEBUG
void CPerek3DBase::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek3DBase::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek3DBase message handlers

void CPerek3DBase::OnSubHeadBtn(UINT Id)
{
	m_buttonId = Id - m_IDstart;
	CaptionDraw(NULL);
	m_3dscreen.OnPaint();
	InitOnSubHeadButton();
	Do3DPaint();
}

void CPerek3DBase::Do3DPaint(void)
{
}

void CPerek3DBase::SetDgreeStartAng(void)
{
	InitOnSubHeadButton();
	Do3DPaint();
}

void CPerek3DBase::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_scale.OnLButtonDown(point);

	CPerek2DBase::OnLButtonDown(nFlags, point);
}

void CPerek3DBase::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_scale.OnLButtonUp(point);

	CPerek2DBase::OnLButtonUp(nFlags, point);
}

void CPerek3DBase::OnMouseMove(UINT nFlags, CPoint point)
{
	m_scale.OnMouseMove(point);

	CPerek2DBase::OnMouseMove(nFlags, point);
}

int CPerek3DBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek2DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	//m_memDc.CreateCompatibleDC(&dc);
	//m_memBm.CreateCompatibleBitmap(&dc, ipWidth, ipHeight);
	//m_memDc.SelectObject(&m_memBm);
	//m_memDc.SelectObject(&m_font);

	m_wndTool.Create(this, WS_CHILD | WS_VISIBLE | CBRS_RIGHT);
	theApp.CreateToolBm2(m_IDX_PEREK, 16, &dc,m_wndTool,m_IDstart);
	return 0;
}

void CPerek3DBase::DoDrawing(CDC* pDC)
{
	m_scale.Paint();
	CaptionDraw(pDC);
	m_3dscreen.OnPaint();
	SendMessage(WM_EXTRA_DRAW);
}


void CPerek3DBase::CaptionDraw(CDC* pDC)
{
	//m_memDc.PatBlt(0,0,ipWidth,ipHeight,BLACKNESS);
	//int n = m_memDc.SaveDC();

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];
	CParagraphInstant &pi = cp.paragraphs[m_buttonId];

	BITMAP bm;
	m_3dscreen.m_refreshDC.GetBitmap(&bm);
	CDC *pRefreshDC = m_3dscreen.m_refreshDC.operator CDC *();
	CRect rcR(bm.bmWidth - 290, 10, bm.bmWidth, m_nCaptionBottom);
	pRefreshDC->FillSolidRect(rcR,0);

	int n = pRefreshDC->SaveDC();
	COLORREF txtcolor = pRefreshDC->SetTextColor(pi.color);
	pRefreshDC->SetBkMode(TRANSPARENT);
	CString sTxt = pi.sParagraph;
	if(pi.sArg.IsEmpty() == FALSE)
		sTxt = pi.sArg + (CString)"\r" + sTxt;
	CFont* pFont = pRefreshDC->SelectObject(&m_font);
	pRefreshDC->DrawText(sTxt, rcR, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);
	pRefreshDC->SelectObject(pFont);
	pRefreshDC->RestoreDC(n);
	m_3dscreen.CopyRefresh(rcR);
	
}

void CPerek3DBase::InitOnSubHeadButton(void)
{
}

BOOL CPerek3DBase::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_ON_TRIGER_MSG:
		switch(wParam)
		{
		case 0:
			{
			m_bPastCreate = true;
			CaptionDraw(NULL);
			m_3dscreen.OnPaint();
			Do3DPaint();
			SendMessage(WM_EXTRA_DRAW);
			return TRUE;
			}
		case 1:
			m_bSkip = false;
			return TRUE;
		}		
	}

	return CPerek2DBase::OnWndMsg(message, wParam, lParam, pResult);
}

void CPerek3DBase::CreateText(int id, CString text, unsigned long txtColor, unsigned long bkColor, unsigned int txtBmId)
{
	int textSize = text.GetLength();
	BYTE alef = 'à';
	CImageList imageList;
	imageList.Create(txtBmId,9,0,0);
	CMyFBitmap bmOtyut;
	bmOtyut.CreateMyCompatibleBitmap(NULL,textSize*9,14,bkColor);
	CDC *pDC = bmOtyut.GetMyPaintDC();
	int n = pDC->SaveDC();
	CBrush brOt(txtColor);
	CBrush *pOb = pDC->SelectObject(&brOt);
	CPoint p(0,0);

	for(int i = textSize - 1; !(i < 0); --i, p.x += 9)
	{
		imageList.Draw(pDC,(BYTE)text[i]-alef,p, ILD_IMAGE);
	}
	m_3dscreen.BeginObject(id);
	m_3dscreen.CreatObjectPixselMap(textSize*9,14);
	pDC->PatBlt(0,0,textSize*9,14,0X00A000C9);
	m_3dscreen.BitmapToObject(bmOtyut);

	pDC->SelectObject(pOb);
	pDC->RestoreDC(n);
}
