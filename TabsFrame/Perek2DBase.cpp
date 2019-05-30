// Perek2DBase.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek2DBase.h"


// CPerek2DBase

IMPLEMENT_DYNAMIC(CPerek2DBase, CView)

CPerek2DBase::CPerek2DBase()
: m_buttonId(0)
, m_bBntDown(FALSE)
, m_bHandCursor(FALSE)
, m_IDstart(0)
, m_IDidx(0)
, m_IDX_PEREK(0)
, m_ipWidth(ipWidth)
, m_ipHeight(ipHeight)
, m_bNoTimerDraw(false)
, m_bNoDilay(true)
{
	m_rcGetWnd.SetRectEmpty();
}

CPerek2DBase::~CPerek2DBase()
{
}

BEGIN_MESSAGE_MAP(CPerek2DBase, CView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPerek2DBase drawing

void CPerek2DBase::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	if(m_bNoDilay)
	{
		DoDrawing(pDC);
	}
	else
	{
		SetTimer(53, 25, NULL);
		m_bNoTimerDraw = true;
	}
	//DoDrawing(pDC);
}


// CPerek2DBase diagnostics

#ifdef _DEBUG
void CPerek2DBase::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek2DBase::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek2DBase message handlers

void CPerek2DBase::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
}

BOOL CPerek2DBase::OnEraseBkgnd(CDC* pDC)
{
	CRect rc, rc2;
	GetClientRect(rc);
	if(m_wndTool.GetSafeHwnd())
	{
		m_wndTool.GetClientRect(rc2);
		rc.right -= (rc2.Width() + 1);
	}
	pDC->PatBlt(0,0,rc.Width(), rc.Height(), BLACKNESS); 

	return TRUE;
	return CView::OnEraseBkgnd(pDC);
}

void CPerek2DBase::DoDrawing(CDC* pDC)
{
}

void CPerek2DBase::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	CRect rc;
	GetClientRect(rc);
	int cx = rc.Width();
	int cy = rc.Height();

	if(cx == 0 || cy == 0)
		return;

	if(m_wndTool.GetSafeHwnd())
	{
		m_wndTool.GetClientRect(rc);
		if(rc.Width() < cx)
		{
			cx -= rc.Width() + 10;
		}
	}

	pDC->SetStretchBltMode(HALFTONE);
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(m_ipWidth, m_ipHeight);
	pDC->SetViewportExt(cx, cy);
	CPoint ptOldOrigin = pDC->SetViewportOrg(0, 0);
	CView::OnPrepareDC(pDC, pInfo);
}

void CPerek2DBase::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bBntDown = TRUE;

	CView::OnLButtonDown(nFlags, point);
}

void CPerek2DBase::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bBntDown = FALSE;

	CView::OnLButtonUp(nFlags, point);
}

BOOL CPerek2DBase::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	static HCURSOR hCur = theApp.LoadStandardCursor(MAKEINTRESOURCE(32649));

	if(m_bHandCursor)
	{
		SetCursor(hCur);
		return TRUE;
	}
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

int CPerek2DBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	VERIFY(m_font.CreateFont(
		-24,                     // nHeight
		0,                       // nWidth
		0,                       // nEscapement
		0,                       // nOrientation
		FW_NORMAL,               // nWeight
		FALSE,                   // bItalic
		FALSE,                   // bUnderline
		0,                       // cStrikeOut
		HEBREW_CHARSET,          // nCharSet
		OUT_DEFAULT_PRECIS,      // nOutPrecision
		CLIP_DEFAULT_PRECIS,     // nClipPrecision
		DEFAULT_QUALITY,         // nQuality
		DEFAULT_PITCH | FF_SWISS,// nPitchAndFamily
		"Guttman Stam"));        // lpszFacename

	return 0;
}

void CPerek2DBase::OnSubHeadUpdate(CCmdUI* pCmdUI)
{
	BOOL bChect = pCmdUI->m_nID == (m_buttonId + m_IDstart);
	pCmdUI->SetCheck(bChect);
	int idx = pCmdUI->m_nID - m_IDstart;
	if(idx >= 0)
	{
		if(m_wndTool.m_pButtons[idx].m_bChected != bChect)
		{
			m_wndTool.m_pButtons[idx].m_bChected = bChect;
			m_wndTool.m_pButtons[idx].Invalidate();
		}
	}
}

void CPerek2DBase::SetDgreeStartAng(void)
{
}

void CPerek2DBase::OnSubHeadBtn(UINT Id)
{
	m_buttonId = Id - m_IDstart;
	SetDgreeStartAng();
	CRect rc;
	GetClientRect(rc);
	InvalidateRect(rc, FALSE);
}

BOOL CPerek2DBase::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_SET_WND_SUBTYPE:
		m_buttonId = (UINT)wParam;
		SetDgreeStartAng();
		return TRUE;
	case WM_GET_WND_SUBTYPE:
		*pResult = m_buttonId;
		return TRUE;
	case WM_GET_WT:
		*pResult = m_IDidx;
		return TRUE;
	case WM_GET_IDX_PEREK:
		*pResult = m_IDX_PEREK;
		return TRUE;
	case WM_GET_WND_RC:
		{
			GetClientRect(m_rcGetWnd);
			int cx = m_rcGetWnd.Width();
			if(m_wndTool.GetSafeHwnd())
			{
				CRect rc2;
				m_wndTool.GetClientRect(rc2);
				if((rc2.Width()+ 10) < cx)
				{
					m_rcGetWnd.right -= rc2.Width() + 10;
				}
			}
			*pResult = (LRESULT)&m_rcGetWnd;
		}
		return TRUE;
	}

	return CView::OnWndMsg(message, wParam, lParam, pResult);
}

int CPerek2DBase::DiameterSteps(int diameter, double fine)
{
	double lfpi = atan2(0.0, -1.0);
	double lfcirclePixsel = ((double)diameter * lfpi) / fine;
	lfcirclePixsel = ceil(lfcirclePixsel);
	double mod4 = fmod(lfcirclePixsel, 4.0);
	if(mod4 != 0.0)
		lfcirclePixsel += 4.0 - mod4;
	return (int)(float)lfcirclePixsel;
}

void CPerek2DBase::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 53)
	{
		KillTimer(nIDEvent);
		CClientDC dc(this);
		OnPrepareDC(&dc);
		DoDrawing(&dc);
		m_bNoTimerDraw = false;
	}

	CView::OnTimer(nIDEvent);
}
