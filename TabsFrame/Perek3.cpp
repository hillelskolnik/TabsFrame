// Perek3.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek3.h"


// CPerek3

IMPLEMENT_DYNCREATE(CPerek3, CPerek2DBase)

CPerek3::CPerek3()
: m_degree(0)
,m_rc(0,0,ipWidth, ipHeight - 100)
, m_pMiddel(0)
, bplus(20)
{
	m_pMiddel.SetPoint(m_rc.CenterPoint().x, m_rc.bottom + bplus);
	m_rcHalf.SetRect(m_pMiddel.x + 10,0,m_rc.right,m_rc.bottom);
	m_IDstart = ID_P3_1;
	m_IDidx = WT_PEREK_3;
}

CPerek3::~CPerek3()
{
}

BEGIN_MESSAGE_MAP(CPerek3, CPerek2DBase)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI_RANGE(ID_P3_1, ID_P3_15, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P3_1, ID_P3_15, &CPerek2DBase::OnSubHeadBtn)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek3 drawing


// CPerek3 diagnostics

#ifdef _DEBUG
void CPerek3::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek3::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek3 message handlers

int CPerek3::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek2DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	m_memDc.CreateCompatibleDC(&dc);
	m_memBm.CreateCompatibleBitmap(&dc, ipWidth, ipHeight);
	m_memDc.SelectObject(&m_memBm);
	m_memDc.SelectObject(&m_font);

	m_wndTool.Create(this, WS_CHILD | WS_VISIBLE | CBRS_RIGHT);
//	theApp.CreateToolBm(IDX_PEREK_3, 16, m_toolBm, &dc,m_wndTool, ID_P3_1);
	theApp.CreateToolBm2(IDX_PEREK_3, 16, &dc,m_wndTool,ID_P3_1);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);

	return 0;
}

void CPerek3::DoDrawing(CDC* pDC)
{
	m_memDc.PatBlt(0,0,ipWidth,ipHeight,BLACKNESS);

	int n = m_memDc.SaveDC();

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[IDX_PEREK_3];
	CParagraphInstant &pi = cp.paragraphs[m_buttonId];

	COLORREF txtcolor = m_memDc.SetTextColor(pi.color);
	m_memDc.SetBkMode(TRANSPARENT);
	CRect rcTxt(ipWidth - 290, 10, ipWidth - 50, 130);
	CString sTxt = pi.sParagraph;
	if(pi.sArg.IsEmpty() == FALSE)
		sTxt = pi.sArg + (CString)"\r" + sTxt;
	m_memDc.DrawText(sTxt, rcTxt, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);

	switch(m_buttonId)
	{
	case 0:
	case 1:
	case 2:
		{
			int rcns = m_buttonId? 3:5;
			COLORREF col0 = cp.paragraphs[0].color;
			COLORREF col1 = cp.paragraphs[1].color;
			COLORREF lineColor = RGB(255, 255, 0);
			CPen pen(PS_SOLID, 2, lineColor);
			CPen* oPen = m_memDc.SelectObject(&pen);
			int offset = 60;
			CPoint pl(m_rc.left + offset, m_rc.bottom + bplus);
			CPoint pr(m_rc.right - offset, m_rc.bottom + bplus);
			m_memDc.MoveTo(pl);
			m_memDc.LineTo(pr);
			DrawLine(500, m_pMiddel, m_degree, &m_memDc, lineColor);
			CPen penArc(PS_SOLID, 2, col1);
			if(m_buttonId)
			{
				int arcs = 60;
				CRect rc(m_pMiddel.x - arcs,
					m_pMiddel.y - arcs, m_pMiddel.x + arcs,
					m_pMiddel.y + arcs);
				CPoint start(m_pMiddel.x + arcs, m_pMiddel.y);
				CPoint ANGpt = GetAnglePoint(45, m_degree, m_pMiddel);             
				m_memDc.SelectObject(&penArc);
				m_memDc.Arc(rc, start, ANGpt);
				CString sAng;
				sAng.Format("%.1f", m_degree);
				m_memDc.TextOutA(m_pMiddel.x, m_pMiddel.y, sAng);
			}
			CPen point(PS_SOLID, 2, col0);
			m_memDc.SelectObject(&point);
			CBrush br(col0);
			CBrush* obr = m_memDc.SelectObject(&br);
			CRect rcEli(m_pMiddel.x - rcns, m_pMiddel.y - rcns,
					m_pMiddel.x + rcns, m_pMiddel.y + rcns);
			m_memDc.Ellipse(rcEli);


			m_memDc.SelectObject(obr);
			m_memDc.SelectObject(oPen);
		}
		break;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		{
			COLORREF color4 = cp.paragraphs[4].color;
			COLORREF color5 = cp.paragraphs[5].color;
			COLORREF color6 = cp.paragraphs[6].color;
			COLORREF color7 = cp.paragraphs[7].color;
			COLORREF color8 = cp.paragraphs[8].color;

			CPen pen5 (PS_SOLID, (m_buttonId == 5)?5:2, color5);
			CPen pen6 (PS_SOLID, (m_buttonId == 6)?5:2, color6);
			CPen pen7 (PS_SOLID, (m_buttonId == 7)?5:2, color7);
			CPen pen8 (PS_SOLID, (m_buttonId == 8)?5:2, color8);

			DrawLine(500, m_pMiddel, m_degree, &m_memDc, color4,
				(m_buttonId == 4)?5:2);
			CPoint pgimel = GetAnglePoint(540, m_degree, m_pMiddel);
			m_memDc.SetTextColor(color4);
			m_memDc.TextOutA(pgimel.x, pgimel.y, "â");
			m_memDc.TextOutA(m_pMiddel.x, m_pMiddel.y, "ã");

			CPen* oPen = m_memDc.SelectObject(&pen5);
			int offset = 60;
			CPoint pl(m_rc.left + offset, m_rc.bottom + bplus);
			CPoint pr(m_rc.right - offset, m_rc.bottom + bplus);
			m_memDc.MoveTo(pl);
			m_memDc.LineTo(pr);
			m_memDc.SetTextColor(color5);
			m_memDc.TextOutA(pl.x - 30, pl.y, "á");
			m_memDc.TextOutA(pr.x + 30, pr.y, "à");

			int rcns = (m_buttonId == 6)? 5:3;
			CBrush br(color6);
			m_memDc.SelectObject(&pen6);
			CBrush* obr = m_memDc.SelectObject(&br);
			CRect rcEli(m_pMiddel.x - rcns, m_pMiddel.y - rcns,
					m_pMiddel.x + rcns, m_pMiddel.y + rcns);
			m_memDc.Ellipse(rcEli);

			m_memDc.SelectObject(&pen7);
			int arcs = 60;
			CRect rc(m_pMiddel.x - arcs,
				m_pMiddel.y - arcs, m_pMiddel.x + arcs,
				m_pMiddel.y + arcs);
			CPoint start(m_pMiddel.x + arcs, m_pMiddel.y);
			CPoint ANGpt = GetAnglePoint(45, m_degree, m_pMiddel);             
			m_memDc.Arc(rc, start, ANGpt);

			m_memDc.SelectObject(&pen8);
			CPoint end(m_pMiddel.x - arcs, m_pMiddel.y);
			m_memDc.Arc(rc, ANGpt, end);

			m_memDc.SelectObject(obr);
			m_memDc.SelectObject(oPen);
		}
		break;
	case 9  :
	case 10 :
	case 11 :
	case 12 :
	case 13 :
	case 14 :
	case 15 :
		{
			COLORREF color10 = cp.paragraphs[10].color;
			COLORREF color11 = cp.paragraphs[11].color;
			COLORREF color12 = cp.paragraphs[12].color;
			COLORREF color13 = cp.paragraphs[13].color;
			COLORREF color14 = cp.paragraphs[14].color;
			COLORREF color15 = cp.paragraphs[15].color;

			CPen pen10 (PS_SOLID, (m_buttonId == 10)?5:2, color10);
			CPen pen11 (PS_SOLID, (m_buttonId == 11)?5:2, color11);
			CPen pen12 (PS_SOLID, (m_buttonId == 12)?5:2, color12);
			CPen pen13 (PS_SOLID, (m_buttonId == 13)?5:2, color13);
			CPen pen14 (PS_SOLID, (m_buttonId == 14)?5:2, color14);

			DrawLine(460, m_pMiddel, m_degree, &m_memDc, color10,
				(m_buttonId == 10)?5:2);
			CPoint pgimel = GetAnglePoint(490, m_degree, m_pMiddel);
			m_memDc.SetTextColor(color10);
			m_memDc.TextOutA(pgimel.x, pgimel.y, "ç");
			m_memDc.TextOutA(m_pMiddel.x, m_pMiddel.y, "å");

			CPen* oPen = m_memDc.SelectObject(&pen11);
			int offset = 60;
			CPoint pl(m_rc.left + offset, m_rc.bottom + bplus);
			CPoint pr(m_rc.right - offset, m_rc.bottom + bplus);
			m_memDc.MoveTo(pl);
			m_memDc.LineTo(pr);
			m_memDc.TextOutA(pl.x - 30, pl.y, "æ");
			m_memDc.TextOutA(pr.x + 30, pr.y, "ä");

			int rcns = (m_buttonId == 6)? 5:3;
			CBrush br(color12);
			m_memDc.SelectObject(&pen12);
			CBrush* obr = m_memDc.SelectObject(&br);
			CRect rcEli(m_pMiddel.x - rcns, m_pMiddel.y - rcns,
					m_pMiddel.x + rcns, m_pMiddel.y + rcns);
			m_memDc.Ellipse(rcEli);

			m_memDc.SelectObject(&pen13);
			int arcs = 60;
			CRect rc(m_pMiddel.x - arcs,
				m_pMiddel.y - arcs, m_pMiddel.x + arcs,
				m_pMiddel.y + arcs);
			CPoint start(m_pMiddel.x + arcs, m_pMiddel.y);
			CPoint ANGpt = GetAnglePoint(45, m_degree, m_pMiddel);             
			m_memDc.Arc(rc, start, ANGpt);

			m_memDc.SelectObject(&pen14);
			CPoint end(m_pMiddel.x - arcs, m_pMiddel.y);
			m_memDc.Arc(rc, ANGpt, end);

			if(m_buttonId == 15)
			{
				m_memDc.SetTextColor(color15);
				CString sAngSum;
				sAngSum.Format("%.1f + %.1f = 180", 180.0 - m_degree,m_degree);
				m_memDc.TextOutA(100,350,sAngSum);
			}

			m_memDc.SelectObject(obr);
			m_memDc.SelectObject(oPen);
		}
		break;
	}

	m_memDc.RestoreDC(n);
	pDC->BitBlt(0,0,ipWidth,ipHeight,&m_memDc,0,0,SRCCOPY);

}

void CPerek3::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	switch(m_buttonId)
	{
	case 0:
	case 1:
	case 2:
		m_bHandCursor  = m_rc.PtInRect(p);
		break;
	case 9  :
	case 10 :
	case 11 :
	case 12 :
	case 13 :
	case 14 :
	case 15 :
		m_bHandCursor  = m_rcHalf.PtInRect(p);
		break;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		m_bHandCursor = FALSE;
		break;
	}

	if(m_bBntDown && m_bHandCursor)
	{
		m_degree = PointsToAng(m_pMiddel, p);

		CRect rc = m_rc;
		rc.InflateRect(25, 25);
		dc.LPtoDP(rc);
		//CRect rc;
		//GetClientRect(rc);
		//rc.right -= 20;
		InvalidateRect(rc, FALSE);
	}

	CPerek2DBase::OnMouseMove(nFlags, point);
}

void CPerek3::SetDgreeStartAng(void)
{
	switch(m_buttonId)
	{
	case 0:
	case 1:
	case 2:
	case 9  :
	case 10 :
	case 11 :
	case 12 :
	case 13 :
	case 14 :
	case 15 :
		if(m_buttonId <= 2)
			m_degree = (m_buttonId == 2)? 20:90;
		else
			m_degree = 30;
		break;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		m_degree = (m_buttonId == 2)? 20:90;
		break;
	}
}
