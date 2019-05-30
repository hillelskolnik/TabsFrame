// Perek10.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek10.h"


// CPerek10

IMPLEMENT_DYNCREATE(CPerek10, CPerek2DBase)

CPerek10::CPerek10()
: m_diameter(((double)ipWidth*5/8) / pi)
, m_top(((double)ipHeight - m_diameter) / 2.0)
, m_ptyNull(m_top + m_diameter / 2.0)
, m_right((double)ipWidth*13/16)
, m_rc(ipWidth*3/16, (int)(float)m_top,(int)(float)m_right,(int)(float)(m_top+m_diameter))
, m_pt((int)(float)m_right,(int)(float)m_ptyNull)
, m_radius(m_diameter / 2.0)
, m_plb(m_rc.left, m_rc.bottom)
, m_step(m_diameter/7.0)
, m_angStep(360.0 / 22.0)
, m_pmt7(m_rc.right - 10, m_rc.top)
, m_plt7(m_rc.right + 10, m_rc.top)
{
	m_IDidx = WT_PEREK_10;
}

CPerek10::~CPerek10()
{
}

BEGIN_MESSAGE_MAP(CPerek10, CPerek2DBase)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek10 drawing

// CPerek10 diagnostics

#ifdef _DEBUG
void CPerek10::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek10::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek10 message handlers

int CPerek10::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek2DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	m_memDc.CreateCompatibleDC(&dc);
	m_memBm.CreateCompatibleBitmap(&dc, ipWidth, ipHeight);
	m_memDc.SelectObject(&m_memBm);
	m_memDc.SelectObject(&m_font);

	return 0;
}

void CPerek10::DoDrawing(CDC* pDC)
{
	m_memDc.PatBlt(0,0,ipWidth,ipHeight,BLACKNESS);

	int n = m_memDc.SaveDC();

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[IDX_PEREK_10];
	CParagraphInstant &pi = cp.paragraphs[m_buttonId];

	COLORREF txtcolor = m_memDc.SetTextColor(pi.color);
	m_memDc.SetBkMode(TRANSPARENT);
	CRect rcTxt(ipWidth - 290, 10, ipWidth - 50, 130);
	CString sTxt = pi.sParagraph;
	if(pi.sArg.IsEmpty() == FALSE)
		sTxt = pi.sArg + (CString)"\r" + sTxt;
	m_memDc.DrawText(sTxt, rcTxt, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);

	CPen pen1(PS_SOLID, 2, pi.color);
	CPen pen(PS_SOLID, 2, 255);
	CPen *oPen = m_memDc.SelectObject(&pen1);

	int rad = (int)(float)m_radius;
	CRect rc(m_pt.x - rad, m_pt.y - rad, m_pt.x + rad, m_pt.y + rad);

	double ang = ((m_right - (double)m_pt.x) / m_radius)*ToD;
//	m_memDc.SelectObject(&pen1);

	CPoint sArc(m_pt.x, rc.bottom);
	m_memDc.MoveTo(m_plb);
	m_memDc.LineTo(sArc);

	int nLeft = m_rc.left;
	double left = (double)nLeft;
	int i = 0;
	for(; i < 22 && nLeft < m_pt.x; ++i, left += m_step, nLeft = (int)(float)left)
	{
		CPoint p1(nLeft,m_rc.bottom - 10);
		m_memDc.MoveTo(p1);
		p1.y += 20;
		m_memDc.LineTo(p1);
	}
	double angTemp = ang - 90.0;
	for(angTemp -= m_angStep;i < 22; ++i, angTemp -= m_angStep)
	{
		C2DPoint dpt = angTemp;
		dpt *= (m_radius - 10);
		m_memDc.MoveTo(dpt.GetScreenPt(m_pt));
		dpt = angTemp;
		dpt *= (m_radius + 10);
		m_memDc.LineTo(dpt.GetScreenPt(m_pt));
	}
	
	m_memDc.SelectObject(&pen);
	C2DPoint t = (ang + 90);
	C2DPoint b = (ang - 90);
	CPoint pt = (t *= m_radius).GetScreenPt(m_pt);
	CPoint pb = (b *= m_radius).GetScreenPt(m_pt);

	m_memDc.MoveTo(pt);
	m_memDc.LineTo(pb);
	InitDPArr();
	C2DPoint turn = ang;
	for(i = 0; i < 12; i += 2)
	{
		Turn(m_dPArr[i],turn);
		Turn(m_dPArr[i+1],turn);
		m_memDc.MoveTo(m_dPArr[i].GetScreenPt(m_pt));
		m_memDc.LineTo(m_dPArr[i+1].GetScreenPt(m_pt));
	}
	m_memDc.MoveTo(m_pmt7);
	m_memDc.LineTo(m_plt7);

	m_memDc.SelectObject(&pen1);
	if(ang > 1)
	{
		m_memDc.Arc(rc,sArc,pb);
	}

	{
		COLORREF color2 = RGB(0,0,255);
		CPen pen2(PS_SOLID, 2, color2);
		int rcns = 5;
		m_memDc.SelectObject(&pen2);
		CBrush br(color2);
		CBrush* obr = m_memDc.SelectObject(&br);
		CRect rcEli(m_pt.x - rcns, m_pt.y - rcns,
				m_pt.x + rcns, m_pt.y + rcns);
		m_memDc.Ellipse(rcEli);
		m_memDc.SelectObject(obr);
	}

	m_memDc.TextOutA(m_rc.left - 20, m_rc.bottom + 5, "22");
	m_memDc.TextOutA(m_rc.right + 5, m_rc.top - 33, "7");


	m_memDc.SelectObject(oPen);
	m_memDc.RestoreDC(n);
	pDC->BitBlt(0,0,ipWidth,ipHeight,&m_memDc,0,0,SRCCOPY);
}

void CPerek10::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);


	m_bHandCursor  = TRUE;

	if(m_bBntDown && m_bHandCursor)
	{
		if(p.x < m_rc.left)
			m_pt.x = m_rc.left;
		else if(p.x > m_rc.right)
			m_pt.x = m_rc.right;
		else
			m_pt.x = p.x;

		CRect rc = m_rc;
		rc.InflateRect(150, 25);
		dc.LPtoDP(rc);
		//GetClientRect(rc);
		
		InvalidateRect(rc, FALSE);
	}

	CPerek2DBase::OnMouseMove(nFlags, point);
}

void CPerek10::InitDPArr(void)
{
	double start = m_step - m_radius;
	double size = 10;
	for(int i = 0; i < 12; i += 2, start += m_step)
	{
		m_dPArr[i].x = -size;
		m_dPArr[i].y = start;
		m_dPArr[i+1].x = size;
		m_dPArr[i+1].y = start;
	}
}
