// Perek7.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek7.h"


// CPerek7

IMPLEMENT_DYNCREATE(CPerek7, CPerek2DBase)

CPerek7::CPerek7()
:m_rc(ipWidth/8,ipHeight*3/16,ipWidth*7/8,ipHeight*5/8)
, m_pt(ipWidth*5/8, ipHeight*3/16)
, m_pAlef(ipWidth*7/8,ipHeight*6/8)
, m_pBet(ipWidth/8,ipHeight*6/8)
{
	m_rcMouse = m_rc;
	m_rcMouse.DeflateRect(105,0);
	m_rcMouse.bottom -= 100;

	m_IDstart = ID_P7_1;
	m_IDidx = WT_PEREK_7;
}

CPerek7::~CPerek7()
{
}

BEGIN_MESSAGE_MAP(CPerek7, CPerek2DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P7_1, ID_P7_11, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P7_1, ID_P7_11, &CPerek2DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek7 drawing

// CPerek7 diagnostics

#ifdef _DEBUG
void CPerek7::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek7::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek7 message handlers

int CPerek7::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek2DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	m_memDc.CreateCompatibleDC(&dc);
	m_memBm.CreateCompatibleBitmap(&dc, ipWidth, ipHeight);
	m_memDc.SelectObject(&m_memBm);
	m_memDc.SelectObject(&m_font);

	m_wndTool.Create(this, WS_CHILD | WS_VISIBLE | CBRS_RIGHT);
	theApp.CreateToolBm2(IDX_PEREK_7, 16, &dc,m_wndTool,m_IDstart);

	return 0;
}

void CPerek7::DoDrawing(CDC* pDC)
{
	m_memDc.PatBlt(0,0,ipWidth,ipHeight,BLACKNESS);

	int n = m_memDc.SaveDC();

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[IDX_PEREK_7];
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
	COLORREF color2 = cp.paragraphs[2].color;
	COLORREF color3 = cp.paragraphs[3].color;
	COLORREF color4 = cp.paragraphs[4].color;
	COLORREF color5 = cp.paragraphs[5].color;
	COLORREF color6 = cp.paragraphs[6].color;
	COLORREF color7 = cp.paragraphs[7].color;
	COLORREF color8 = cp.paragraphs[8].color;
	COLORREF color9 = cp.paragraphs[9].color;
	COLORREF color10 = cp.paragraphs[10].color;

	CPen pen0 (PS_SOLID, (m_buttonId == 0)?5:2, color0);
	CPen pen1 (PS_SOLID, (m_buttonId == 1)?5:2, color1);
	CPen pen2 (PS_SOLID, (m_buttonId == 2)?5:2, color2);
	CPen pen3 (PS_SOLID, (m_buttonId == 3)?5:2, color3);
	CPen pen4 (PS_SOLID, (m_buttonId == 4)?5:2, color4);
	CPen pen5 (PS_SOLID, (m_buttonId == 5)?5:2, color5);
	CPen pen6 (PS_SOLID, (m_buttonId == 6)?5:2, color6);
	CPen pen7 (PS_SOLID, (m_buttonId == 7)?7:2, color7);
	CPen pen8 (PS_SOLID, (m_buttonId == 8)?5:2, color8);
	CPen pen9 (PS_SOLID, (m_buttonId == 9)?5:2, color9);
	CPen pen10 (PS_SOLID, (m_buttonId == 10)?5:2, color10);

	CPen *oPen = m_memDc.SelectObject(&pen0);
	m_memDc.MoveTo(m_pBet);
	m_memDc.LineTo(m_pt);
	m_memDc.LineTo(m_pAlef);
	if(m_buttonId == 3)
		m_memDc.SelectObject(&pen3);
	m_memDc.LineTo(m_pBet);

	m_memDc.SelectObject(&pen1);
	CPoint pHe(m_rc.left,m_pt.y);
	CPoint pZain(m_rc.right,m_pt.y);
	m_memDc.MoveTo(pHe);
	m_memDc.LineTo(pZain);

	int rcw = 90;
	CPoint p = m_pt;
	CRect rcGimel(p.x - rcw, p.y - rcw, p.x + rcw, p.y + rcw);
	p = m_pAlef;
	static CRect rcAlef(p.x - rcw, p.y - rcw, p.x + rcw, p.y + rcw);
	p = m_pBet;
	static CRect rcBet(p.x - rcw, p.y - rcw, p.x + rcw, p.y + rcw);

	double zavDalet = PointsToAng(m_pBet, m_pt);
	double zavHe = 180 - PointsToAng(m_pAlef, m_pt);
	double zavVav = 180 - (zavDalet + zavHe);
	switch(m_buttonId)
	{
	case 4:
		m_memDc.SelectObject(&pen4);
		m_memDc.Arc(rcGimel, m_pAlef, pZain);
		m_memDc.Arc(rcAlef, m_pt, m_pBet);
		break;
	case 5:
		m_memDc.SelectObject(&pen5);
		m_memDc.Arc(rcGimel, pHe, m_pBet);
		m_memDc.Arc(rcBet, m_pAlef, m_pt);
		break;
	case 7:
		m_memDc.SelectObject(&pen7);
		m_memDc.Arc(rcGimel, pHe, pZain);
	case 6:
		m_memDc.SelectObject(&pen6);
		m_memDc.Arc(rcAlef, m_pt, m_pBet);
		m_memDc.Arc(rcBet, m_pAlef, m_pt);
		m_memDc.Arc(rcGimel, m_pBet, m_pAlef);
		break;
	case 8:
		m_memDc.SelectObject(&pen8);
		m_memDc.Arc(rcGimel, pHe, pZain);
		break;
	case 9:
		m_memDc.SetTextColor(color9);
		m_memDc.SelectObject(&pen9);
		m_memDc.Arc(rcGimel, pHe, pZain);
		sTxt.Format("%.1f + %.1f + %.1f = 180", zavDalet, zavVav, zavHe);
		m_memDc.TextOutA(m_pBet.x + 250,m_pBet.y + 50, sTxt);
		break;
	case 10:
		m_memDc.SetTextColor(color10);
		m_memDc.SelectObject(&pen10);
		m_memDc.Arc(rcAlef, m_pt, m_pBet);
		m_memDc.Arc(rcBet, m_pAlef, m_pt);
		m_memDc.Arc(rcGimel, m_pBet, m_pAlef);
		sTxt.Format("%.1f + %.1f + %.1f = 180", zavDalet, zavVav, zavHe);
		m_memDc.TextOutA(m_pBet.x + 250,m_pBet.y + 50, sTxt);
		break;
	}

	m_memDc.SetTextColor(color0);
	m_memDc.TextOutA(m_pAlef.x,m_pAlef.y,"à");
	m_memDc.TextOutA(m_pBet.x,m_pBet.y,"á");
	m_memDc.TextOutA(m_pt.x,m_pt.y-33,"â");

	m_memDc.SetTextColor(color1);
	m_memDc.TextOutA(pHe.x,pHe.y,"ç");
	m_memDc.TextOutA(pZain.x-5,pZain.y,"æ");

	m_memDc.SetTextColor(RGB(255,0,0));
	m_memDc.TextOutA(m_pt.x-3,m_pt.y+5,"å");
	m_memDc.TextOutA(m_pBet.x+rcw-25,m_pBet.y-35,"ã");
	m_memDc.TextOutA(m_pAlef.x-rcw + 10,m_pAlef.y-35,"ä");
	m_memDc.TextOutA(m_pt.x+rcw + 5,m_pt.y,"è");
	m_memDc.TextOutA(m_pt.x-rcw-13,m_pt.y,"é");

	{
		int rcns = (m_buttonId == 2)? 5:3;
		m_memDc.SelectObject(&pen2);
		CBrush br(color2);
		CBrush* obr = m_memDc.SelectObject(&br);
		CRect rcEli(m_pt.x - rcns, m_pt.y - rcns,
				m_pt.x + rcns, m_pt.y + rcns);
		m_memDc.Ellipse(rcEli);
		m_memDc.SelectObject(obr);
	}


	m_memDc.SelectObject(oPen);
	m_memDc.RestoreDC(n);
	pDC->BitBlt(0,0,ipWidth,ipHeight,&m_memDc,0,0,SRCCOPY);
}

void CPerek7::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);


	m_bHandCursor  = m_rcMouse.PtInRect(p);

	if(m_bBntDown && m_bHandCursor)
	{
		m_pt = p;

		CRect rc = m_rc;
		rc.InflateRect(35, 35);
		rc.bottom += 150;
		dc.LPtoDP(rc);
		//CRect rc;
		//GetClientRect(rc);
		//rc.right -= 20;
		InvalidateRect(rc, FALSE);
	}

	CPerek2DBase::OnMouseMove(nFlags, point);
}
