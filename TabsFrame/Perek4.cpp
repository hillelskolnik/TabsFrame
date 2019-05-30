// Perek4.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek4.h"


// CPerek4

IMPLEMENT_DYNCREATE(CPerek4, CPerek2DBase)

CPerek4::CPerek4()
: m_pMiddel(ipWidth/2,ipHeight/2)
, m_degree(150)
, m_radius(ipHeight *3 / 8)
{
	int cy = 100;
	int cx = 50;
	CPoint p = m_pMiddel;
	m_rc.SetRect(p.x-m_radius, p.y-m_radius,p.x+m_radius, p.y+m_radius);
	p.y -= cy;
	p.x -= cx;
	m_rctl.SetRect(CPoint(0),p);
	p.y += cy*2;
	p.x += cx*2;
	m_rcbr.SetRect(p, CPoint(ipWidth, ipHeight));
	int arcs = 60;
	m_rcArc.SetRect(m_pMiddel.x - arcs,
		m_pMiddel.y - arcs, m_pMiddel.x + arcs,
		m_pMiddel.y + arcs);
	m_IDstart = ID_P4_1;
	m_IDidx = WT_PEREK_4;
}

CPerek4::~CPerek4()
{
}

BEGIN_MESSAGE_MAP(CPerek4, CPerek2DBase)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI_RANGE(ID_P4_1, ID_P4_12, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P4_1, ID_P4_12, &CPerek2DBase::OnSubHeadBtn)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek4 drawing

// CPerek4 diagnostics

#ifdef _DEBUG
void CPerek4::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek4::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek4 message handlers

int CPerek4::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek2DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	m_memDc.CreateCompatibleDC(&dc);
	m_memBm.CreateCompatibleBitmap(&dc, ipWidth, ipHeight);
	m_memDc.SelectObject(&m_memBm);
	m_memDc.SelectObject(&m_font);

	m_wndTool.Create(this, WS_CHILD | WS_VISIBLE | CBRS_RIGHT);
//	theApp.CreateToolBm(IDX_PEREK_4, 16, m_toolBm, &dc,m_wndTool, ID_P4_1);
	theApp.CreateToolBm2(IDX_PEREK_4, 16, &dc,m_wndTool,m_IDstart);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);

	return 0;
}

void CPerek4::DoDrawing(CDC* pDC)
{
	m_memDc.PatBlt(0,0,ipWidth,ipHeight,BLACKNESS);

	int n = m_memDc.SaveDC();

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[IDX_PEREK_4];
	CParagraphInstant &pi = cp.paragraphs[m_buttonId];

	COLORREF txtcolor = m_memDc.SetTextColor(pi.color);
	m_memDc.SetBkMode(TRANSPARENT);
	CRect rcTxt(ipWidth - 290, 10, ipWidth - 50, 130);
	CString sTxt = pi.sParagraph;
	if(pi.sArg.IsEmpty() == FALSE)
		sTxt = pi.sArg + (CString)"\r" + sTxt;
	m_memDc.DrawText(sTxt, rcTxt, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);


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
	COLORREF color11 = cp.paragraphs[11].color;

	CPen pen1 (PS_SOLID, (m_buttonId == 1)?5:2, color1);
	CPen pen2 (PS_SOLID, (m_buttonId == 2)?5:2, color2);
	CPen pen3 (PS_SOLID, (m_buttonId == 3)?5:2, color3);
	CPen pen4 (PS_SOLID, (m_buttonId == 4)?5:2, color4);
	CPen pen5 (PS_SOLID, (m_buttonId == 5)?5:2, color5);
	CPen pen6 (PS_SOLID, (m_buttonId == 6)?5:2, color6);
	CPen pen7 (PS_SOLID, (m_buttonId == 7)?5:2, color7);
	CPen pen8 (PS_SOLID, (m_buttonId == 8)?5:2, color8);
	CPen pen9 (PS_SOLID, (m_buttonId == 9)?5:2, color9);
	CPen pen10 (PS_SOLID, (m_buttonId == 10)?5:2, color10);
	CPen pen11 (PS_SOLID, (m_buttonId == 11)?5:2, color11);

	CPen *oPen = m_memDc.SelectObject(&pen1);
	DrawPolyLines(2, m_rc.Width() / 2,
		m_pMiddel,&m_memDc, 0, 180);

	CPoint pgimel = GetAnglePoint(m_radius + 40, m_degree, m_pMiddel);
	m_memDc.SetTextColor(color1);
	m_memDc.TextOutA(m_pMiddel.x + (m_radius + 40), m_pMiddel.y, "à");
	m_memDc.TextOutA(m_pMiddel.x - (m_radius + 40), m_pMiddel.y, "á");

	m_memDc.SelectObject(&pen2);
	DrawPolyLines(2, m_rc.Width() / 2,
		m_pMiddel,&m_memDc, m_degree, 180);

	m_memDc.SetTextColor(color2);
	m_memDc.TextOutA(pgimel.x, pgimel.y, "â");
	m_memDc.TextOutA(m_pMiddel.x*2-pgimel.x, m_pMiddel.y*2-pgimel.y, "ã");

	int rcns = (m_buttonId == 3)? 5:3;
	m_memDc.SelectObject(&pen3);
	CBrush br(color3);
	CBrush* obr = m_memDc.SelectObject(&br);
	CRect rcEli(m_pMiddel.x - rcns, m_pMiddel.y - rcns,
			m_pMiddel.x + rcns, m_pMiddel.y + rcns);
	m_memDc.Ellipse(rcEli);
	m_memDc.SetTextColor(color3);
	m_memDc.TextOutA(m_pMiddel.x-20, m_pMiddel.y, "ç");
	m_memDc.TextOutA(m_pMiddel.x, m_pMiddel.y-40, "å");
	m_memDc.TextOutA(m_pMiddel.x-85, m_pMiddel.y-35, "ä");
	m_memDc.TextOutA(m_pMiddel.x+65, m_pMiddel.y, "æ");

	m_memDc.SelectObject(&pen4);
	CPoint pl(m_pMiddel.x - m_radius , m_pMiddel.y);
	m_memDc.Arc(m_rcArc, pgimel, pl);
	CPoint pdalet(m_pMiddel.x*2-pgimel.x, m_pMiddel.y*2-pgimel.y);
	CPoint pr(m_pMiddel.x + m_radius , m_pMiddel.y);
	m_memDc.Arc(m_rcArc, pdalet, pr);

	m_memDc.SelectObject(&pen5);
	m_memDc.Arc(m_rcArc, pr, pgimel);
	m_memDc.Arc(m_rcArc, pl, pdalet);

	CRect rc = m_rcArc;
	rc.InflateRect(40,40);
	switch(m_buttonId)
	{
	case 6:
		m_memDc.SelectObject(&pen6);
		m_memDc.Arc(m_rc, pdalet, pgimel);
		break;
	case 7:
		m_memDc.SelectObject(&pen7);
		m_memDc.Arc(m_rc, pr, pl);
		break;
	case 8:
		m_memDc.SelectObject(&pen8);
		m_memDc.Arc(rc, pr, pl);
		break;
	case 9:
		m_memDc.SelectObject(&pen9);
		m_memDc.Arc(rc, pdalet, pgimel);
		break;
	case 10:
		m_memDc.SelectObject(&pen10);
		m_memDc.Arc(rc, pgimel, pl);
		m_memDc.Arc(rc, pdalet, pr);
		break;
	case 11:
		m_memDc.SelectObject(&pen11);
		m_memDc.Arc(rc, pr, pgimel);
		m_memDc.Arc(rc, pl, pdalet);
		break;
	}

	m_memDc.SelectObject(oPen);
	m_memDc.SelectObject(obr);
	m_memDc.RestoreDC(n);
	pDC->BitBlt(0,0,ipWidth,ipHeight,&m_memDc,0,0,SRCCOPY);
}

void CPerek4::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	BOOL bInrctl = m_rctl.PtInRect(p);
	if(bInrctl)
	{
		m_bHandCursor = TRUE;
	}
	else if(m_rcbr.PtInRect(p))
	{
		m_bHandCursor = TRUE;
	}
	else
		m_bHandCursor = FALSE;


	if(m_bBntDown && m_bHandCursor)
	{
		m_degree = PointsToAng(m_pMiddel, p);
		if(bInrctl == FALSE)
			m_degree -= 180;

		CRect rc = m_rc;
		rc.InflateRect(75, 75);
		dc.LPtoDP(rc);
		//CRect rc;
		//GetClientRect(rc);
		//rc.right -= 20;
		InvalidateRect(rc, FALSE);
	}

	CPerek2DBase::OnMouseMove(nFlags, point);
}




void CPerek4::SetDgreeStartAng(void)
{
}
