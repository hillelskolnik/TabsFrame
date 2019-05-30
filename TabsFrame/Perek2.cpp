// Perek2.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek2.h"



static const double btn4Deg = 80.0;

// CPerek2

IMPLEMENT_DYNCREATE(CPerek2, CPerek2DBase)

CPerek2::CPerek2()
:m_rc(250, 50, 901, 701)
,m_rcMiddel(0,0,7,7)
, m_degree(0)
{
	m_pMiddel = m_rc.CenterPoint();
	m_rcMiddel.MoveToXY(m_pMiddel.x - (m_rcMiddel.Width() / 2), 
		m_pMiddel.y - (m_rcMiddel.Height() / 2));
	m_IDstart = ID_P2_1;
	m_IDidx = WT_PEREK_2;

}

CPerek2::~CPerek2()
{
}

BEGIN_MESSAGE_MAP(CPerek2, CPerek2DBase)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_P2_1, ID_P2_10, &CPerek2DBase::OnSubHeadBtn)
	ON_WM_MOUSEMOVE()
	ON_UPDATE_COMMAND_UI_RANGE(ID_P2_1, ID_P2_10, &CPerek2DBase::OnSubHeadUpdate)
END_MESSAGE_MAP()


// CPerek2 drawing

// CPerek2 diagnostics

#ifdef _DEBUG
void CPerek2::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek2::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek2 message handlers

int CPerek2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek2DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	m_memDc.CreateCompatibleDC(&dc);
	m_memBm.CreateCompatibleBitmap(&dc, ipWidth, ipHeight);
	m_memDc.SelectObject(&m_memBm);

	m_memDc.SelectObject(&m_font);


	m_wndTool.Create(this, WS_CHILD | WS_VISIBLE | CBRS_RIGHT);
//	theApp.CreateToolBm(IDX_PEREK_2, 16, m_toolBm, &dc,m_wndTool,ID_P2_1);
	theApp.CreateToolBm2(IDX_PEREK_2, 16, &dc,m_wndTool,ID_P2_1);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);

	return 0;
}

void CPerek2::DoDrawing(CDC* pDC)
{
	m_memDc.PatBlt(0,0,ipWidth,ipHeight,BLACKNESS);

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[IDX_PEREK_2];
	CParagraphInstant &pi = cp.paragraphs[m_buttonId];

	COLORREF txtcolor = m_memDc.SetTextColor(pi.color);
	m_memDc.SetBkMode(TRANSPARENT);
	CRect rcTxt(ipWidth - 250, 10, ipWidth - 50, 50);
	m_memDc.DrawText(pi.sParagraph, rcTxt, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);

	switch(m_buttonId)
	{
	case 0:
		{
			CArray<CPoint,CPoint&> arr;
			CPen pen(0, 2, pi.color);
			CPen *oPen = m_memDc.SelectObject(&pen);

			DrawPolyLines(3, 150, CPoint(150, 250),&m_memDc);

			DrawPolyLines(4, 150, CPoint(512, 250),&m_memDc, 45);
			DrawPolyLines(5, 150, CPoint(512, 600),&m_memDc);
			DrawPolyLines(6, 180, CPoint(860, 360),&m_memDc);
			DrawPolyLines(8, 120, CPoint(150, 490),&m_memDc);
			m_memDc.SelectObject(oPen);
		}
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		{
			int idx = (m_buttonId == 1)? 1:2;
			COLORREF penColor = cp.paragraphs[idx].color;
			CPen pen(0, 3, penColor);
			CBrush br;
			if(m_buttonId == 1)
				br.CreateHatchBrush(HS_HORIZONTAL, cp.paragraphs[idx].color);
			else
				br.CreateSolidBrush(0);
			CBrush *oBr = m_memDc.SelectObject(&br);
			CPen *oPen = m_memDc.SelectObject(&pen);
			
			m_memDc.Ellipse(m_rc);
			if(m_buttonId == 5)
			{
				CPen pen4(0, 3, pi.color);
				m_memDc.SelectObject(&pen4);
				DrawPolyLines(2, m_rc.Width() / 2,
					m_pMiddel,&m_memDc, m_degree, 180);
			}
			if(m_buttonId >= 3)
			{
				CPen pen3(0, 1, (COLORREF)0);
				m_memDc.SelectObject(&pen3);
				CBrush br3(cp.paragraphs[3].color);
				oBr = m_memDc.SelectObject(&br3);
				m_memDc.Ellipse(m_rcMiddel);
			}
			if(m_buttonId == 4)
			{
				CPen pen4(0, 3, pi.color);
				m_memDc.SelectObject(&pen4);
				DrawPolyLines(2, m_rc.Width() / 2,
					m_pMiddel,&m_memDc, m_degree, btn4Deg);
			}
			m_memDc.SelectObject(oPen);
			m_memDc.SelectObject(oBr);
		}
		break;
	case 6:
	case 7:
		{
			COLORREF penColor = cp.paragraphs[6].color;
			CPen pen(0, 2, penColor);
			CBrush br((COLORREF)0);
			CBrush *oBr = m_memDc.SelectObject(&br);
			CPen *oPen = m_memDc.SelectObject(&pen);

			if(m_buttonId == 6)
			{
				CRect rcPie(0, 0, 450, 450);
				rcPie.MoveToXY(-210, -100);
				m_memDc.Pie(rcPie, 
					CPoint(rcPie.right,rcPie.bottom - 150), 
					CPoint(rcPie.right,rcPie.top + 150));
				rcPie.DeflateRect(50, 150);
				m_memDc.DrawText(pi.sParagraph, rcPie, 
					DT_RIGHT | DT_SINGLELINE | DT_VCENTER | DT_RTLREADING);
			}

			CRect rc = m_rc;
			rc.InflateRect(40, 40);
			m_memDc.Ellipse(rc);

			CPen pen2(0, 1, cp.paragraphs[7].color);
			m_memDc.SelectObject(&pen2);
			double degree = 0;
			for(int i = 0; i < 180; ++i, degree += 1.0)
			{
				DrawPolyLines(2, rc.Width() / 2,
					m_pMiddel,&m_memDc, degree, 180.0);
			}

			m_memDc.SelectObject(oPen);
			m_memDc.SelectObject(oBr);
		}
		break;
	case 8:
	case 9:
		{
			CPen pen(0, 2, pi.color);
			CBrush br((COLORREF)0);
			CBrush *oBr = m_memDc.SelectObject(&br);
			CPen *oPen = m_memDc.SelectObject(&pen);

			m_memDc.Ellipse(m_rc);

			DrawPolyLines(2, m_rc.Width() / 2,
				m_pMiddel,&m_memDc, 0.0, 180.0);
			if(m_buttonId == 9)
			{
				DrawPolyLines(2, m_rc.Width() / 2,
					m_pMiddel,&m_memDc, 90.0, 180.0);
			}

			CPoint p(m_pMiddel.x + 10, m_pMiddel.y - 10);
			CBrush br2(pi.color);
			m_memDc.SelectObject(&br2);
			m_memDc.FloodFill(p.x,p.y, pi.color);

			m_memDc.SelectObject(oPen);
			m_memDc.SelectObject(oBr);
		}
		break;
	}

	pDC->BitBlt(0,0,ipWidth,ipHeight,&m_memDc,0,0,SRCCOPY);
}

void CPerek2::OnMouseMove(UINT nFlags, CPoint point)
{

	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);
	if(m_buttonId == 4 || m_buttonId == 5)
	{
		m_bHandCursor  = m_rc.PtInRect(p);
	}
	else
		m_bHandCursor = FALSE;

	if(m_bBntDown && m_bHandCursor)
	{
		m_degree = PointsToAng(m_pMiddel, p);
		m_degree -= (m_buttonId == 4)? (btn4Deg / 2.0): 90.0;
		CRect rc = m_rc;
		dc.LPtoDP(rc);
		InvalidateRect(rc, FALSE);
	}

	CPerek2DBase::OnMouseMove(nFlags, point);
}

void CPerek2::SetDgreeStartAng(void)
{
	if(m_buttonId == 4)
	{
		m_degree = 90.0 - btn4Deg / 2.0;
	}
	else
		m_degree = 0;
}
