// Perek5.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek5.h"


// CPerek5

IMPLEMENT_DYNCREATE(CPerek5, CPerek2DBase)

CPerek5::CPerek5()
:m_rc(0,0,ipWidth, ipHeight - 300)
, m_degree(100)
, m_pMiddel(0)
, m_nHalfWidth(ipHeight * 3 / 8)
{
	m_pMiddel.SetPoint(m_rc.CenterPoint().x, m_rc.bottom + 20);
	m_IDstart = ID_P5_1;
	m_IDidx = WT_PEREK_5;
}

CPerek5::~CPerek5()
{
}

BEGIN_MESSAGE_MAP(CPerek5, CPerek2DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P5_1, ID_P5_2, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P5_1, ID_P5_2, &CPerek2DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek5 drawing


// CPerek5 diagnostics

#ifdef _DEBUG
void CPerek5::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek5::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek5 message handlers

int CPerek5::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek2DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	m_memDc.CreateCompatibleDC(&dc);
	m_memBm.CreateCompatibleBitmap(&dc, ipWidth, ipHeight);
	m_memDc.SelectObject(&m_memBm);
	m_memDc.SelectObject(&m_font);

	m_wndTool.Create(this, WS_CHILD | WS_VISIBLE | CBRS_RIGHT);
	theApp.CreateToolBm2(IDX_PEREK_5, 16, &dc,m_wndTool,m_IDstart);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);

	return 0;
}

void CPerek5::DoDrawing(CDC* pDC)
{
	m_memDc.PatBlt(0,0,ipWidth,ipHeight,BLACKNESS);

	int n = m_memDc.SaveDC();

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[IDX_PEREK_5];
	CParagraphInstant &pi = cp.paragraphs[m_buttonId];

	COLORREF txtcolor = m_memDc.SetTextColor(pi.color);
	m_memDc.SetBkMode(TRANSPARENT);
	CRect rcTxt(ipWidth - 290, 10, ipWidth - 50, 130);
	CString sTxt = pi.sParagraph;
	if(pi.sArg.IsEmpty() == FALSE)
		sTxt = pi.sArg + (CString)"\r" + sTxt;
	m_memDc.DrawText(sTxt, rcTxt, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);


	COLORREF color0 = cp.paragraphs[0].color;
	COLORREF color1 = cp.paragraphs[1].color;

	CPen pen0 (PS_SOLID, (m_buttonId == 0)?5:2, color0);
	CPen pen1 (PS_SOLID, (m_buttonId == 1)?5:2, color1);

	CPoint p1(m_pMiddel.x - m_nHalfWidth, m_pMiddel.y);
	CPoint p2(m_pMiddel.x + m_nHalfWidth, m_pMiddel.y);
	int nOut = 100;
	CPoint ANGpt = GetAnglePoint(m_nHalfWidth - nOut, m_degree, m_pMiddel); 
	CPoint p3(ANGpt.x - m_nHalfWidth, ANGpt.y);
	CPoint p4(ANGpt.x + m_nHalfWidth, ANGpt.y);
	CPen *oPen = m_memDc.SelectObject(&pen0);

	m_memDc.MoveTo(p1);
	m_memDc.LineTo(p2);
	m_memDc.MoveTo(p3);
	m_memDc.LineTo(p4);
	CPoint ANGpt2 = GetAnglePoint(m_nHalfWidth, m_degree, m_pMiddel);
	CPoint ANGpt3 = GetAnglePoint(nOut, m_degree+180, m_pMiddel);
	CPen pen2(PS_SOLID, 2, RGB(0,255,0));
	m_memDc.SelectObject(&pen2);
	m_memDc.MoveTo(ANGpt2);
	m_memDc.LineTo(ANGpt3);

	m_memDc.SelectObject(&pen1);
	int rcw = 60;
	CPoint p = m_pMiddel;
	CRect rc1(p.x - rcw, p.y - rcw, p.x + rcw, p.y + rcw);
	CRect rc2(ANGpt.x - rcw, ANGpt.y - rcw, ANGpt.x + rcw, ANGpt.y + rcw);
	m_memDc.Arc(rc1, ANGpt2, p1);
	m_memDc.Arc(rc2, ANGpt2, p3);
	m_memDc.SetTextColor(color1);
	m_memDc.TextOutA(p3.x,p3.y,"à");
	m_memDc.TextOutA(p4.x,p4.y,"á");
	m_memDc.TextOutA(p1.x,p1.y,"â");
	m_memDc.TextOutA(p2.x,p2.y,"ã");

	int xplus = (m_degree > 90)? - 20:10;
	m_memDc.TextOutA(ANGpt2.x,ANGpt2.y - 30,"ä");
	m_memDc.TextOutA(ANGpt3.x,ANGpt3.y,"å");
	m_memDc.TextOutA(ANGpt.x + xplus,ANGpt.y,"æ");
	m_memDc.TextOutA(m_pMiddel.x + xplus,m_pMiddel.y,"ç");

	m_memDc.SelectObject(oPen);
	m_memDc.RestoreDC(n);
	pDC->BitBlt(0,0,ipWidth,ipHeight,&m_memDc,0,0,SRCCOPY);
}

void CPerek5::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = m_rc.PtInRect(p);

	if(m_bBntDown && m_bHandCursor)
	{
		m_degree = PointsToAng(m_pMiddel, p);

		CRect rc = m_rc;
		rc.MoveToY(150);
		dc.LPtoDP(rc);
		//CRect rc;
		//GetClientRect(rc);
		//rc.right -= 20;
		InvalidateRect(rc, FALSE);
	}

	CPerek2DBase::OnMouseMove(nFlags, point);
}
