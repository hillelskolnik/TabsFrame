// BookPage.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "BookPage.h"

enum
{
	move_prior = -3
	,move_next = -4
};

// CBookPage

IMPLEMENT_DYNCREATE(CBookPage, CView)

CBookPage::CBookPage()
: m_nPos(0)
, m_nCurentPage(-1)
, m_idx(-1)
, m_nHLidx(-1)
, m_bHandCursor(false)
, m_nHeadLine(-1)
{

}

CBookPage::~CBookPage()
{
}


BEGIN_MESSAGE_MAP(CBookPage, CView)
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEWHEEL()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// CBookPage message handlers



void CBookPage::OnDraw(CDC* pDC)
{
	DrawPage(pDC);
}

void CBookPage::LoadPage(int idx, int nHLidx)
{
	if(idx == -1 || m_bHandCursor)
		return;

	if(idx != -2)
		m_idx = idx;
	m_nHLidx = nHLidx;

	CChapPage cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_idx];
	int nPage = cp.page;
	if(idx == -2 && m_nHLidx > -1)
	{
		CParagraphInstant &pi = cp.paragraphs[m_nHLidx];
		nPage += pi.pageFromStart;
	}
	else if(idx == -2 && nHLidx == move_prior)
	{
		nPage = cp.page;
	}
	else if(idx == -2 && nHLidx == move_next)
	{
		nPage = m_nCurentPage + 1;
	}

	if(nPage == m_nCurentPage)
	{
		SetPageY(cp);
		CClientDC dc(this);
		DrawPage(&dc);
		return;
	}

	m_nCurentPage = nPage;
	if(m_image.IsNull() == false)
	{
		m_image.Destroy();
	}
	CString sPage;
	sPage.Format("Images\\Page%d.JPG",m_nCurentPage);
	m_image.Load(theApp.m_appPath + sPage);

	CRect rc;
	GetClientRect(rc);
	SetScrollBar(rc.Width(), rc.Height());
	SetPageY(cp);
	CClientDC dc(this);
	DrawPage(&dc);
}

void CBookPage::SetPageY(CChapPage& cp)
{
	SCROLLINFO si;
	ZeroMemory(&si, sizeof(SCROLLINFO));
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	GetScrollInfo(SB_VERT,&si);
	CRect rc;
	rc.SetRectEmpty();
	if(m_nHLidx > -1)
	{
		rc = cp.paragraphs[m_nHLidx].hitRect;
	}
	else if (m_nHLidx == move_prior)
	{
		m_nPos = si.nMax - si.nPage;
		SetScrollPos(SB_VERT, m_nPos);
		return;
	}
	else if (m_nHLidx == move_next)
	{
		m_nPos = 50;
		SetScrollPos(SB_VERT, m_nPos);
		return;
	}



	if(rc.IsRectEmpty() == FALSE)
	{
		int top = rc.top;
		if((int)(top  + si.nPage) >= si.nMax)
		{
			m_nPos = si.nMax - (int)si.nPage;
		}
		else
		{
			m_nPos = top - 20;
		}
		SetScrollPos(SB_VERT, m_nPos);
	}
	else if(si.nMax)
	{
		if(cp.startY <= 20 )
		{
			m_nPos = 0;
		}
		else if((int)(cp.startY + si.nPage) >= si.nMax)
		{
			m_nPos = si.nMax - si.nPage;
		}
		else
		{
			m_nPos = cp.startY - 20;
		}
		SetScrollPos(SB_VERT, m_nPos);
	}
}

void CBookPage::DrawPage(CDC* pDC)
{
	if(m_image.IsNull())
		return;
	CRect rc;
	GetClientRect(rc);
	int cx = rc.Width();
	int cy = rc.Height();

	if(cx == 0 || cy == 0)
		return;

	int iWidth = m_image.GetWidth();
	int iHeight = m_image.GetHeight();


	int yExt = (int)((float)cy / (float)cx * (float)iWidth);
	yExt = min(yExt, iHeight);

	pDC->SetStretchBltMode(HALFTONE);
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(iWidth, yExt);
	pDC->SetViewportExt(cx, cy);
	CPoint ptOldOrigin = pDC->SetViewportOrg(0, 0);
	//pDC->PatBlt(0,0,iWidth,iWidth*cy/cx, WHITENESS);

	m_image.Draw(pDC->m_hDC, 0, 0, iWidth, yExt, 0,m_nPos, iWidth, yExt);

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_idx];
	int size = (int)cp.paragraphs.GetCount();
	for(int i = 0; i < size; ++i)
	{
		CParagraphInstant pi = cp.paragraphs[i];
		if((cp.page + pi.pageFromStart) != m_nCurentPage)
			continue;
		PaintRect(pi.hitRect, pi.color);
	}
}

void CBookPage::SetScrollBar(int cx, int cy)
{
	if(m_image.IsNull() || cx == 0 || cy ==0)
		return;

	int iWidth = m_image.GetWidth();
	int iHeight = m_image.GetHeight();

	float fImageRelation = 
		(float)iHeight / (float)iWidth;
	float fWndRelation = 
		(float)cy / (float)cx;

	SCROLLINFO si;
	ZeroMemory(&si, sizeof(SCROLLINFO));
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;

	if(fWndRelation < fImageRelation)
	{
		si.nPage = (int)((float)iWidth * fWndRelation);
		si.nMax = iHeight;
		m_nPos = min(m_nPos, (int)(si.nMax - si.nPage));
		si.nPos = m_nPos;
		SetScrollInfo(SB_VERT,&si);
	}
	else 
	{
		si.nPage = (int)((float)iWidth * fWndRelation);
		SetScrollInfo(SB_VERT,&si);
	}
}

void CBookPage::PaintRect(CRect& rc, COLORREF color)
{
	CClientDC dc(this);
	SetLogicDC(&dc);
	CDC tdc;
	tdc.CreateCompatibleDC(&dc);
	CBitmap bm;
	bm.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	tdc.SelectObject(&bm);
	CBrush br(color);

	tdc.FillRect(CRect(0,0,rc.Width(),rc.Height()), &br);
	dc.BitBlt(rc.left,rc.top- m_nPos,
		rc.Width(),rc.Height(),&tdc,0,0, SRCAND);
}

void CBookPage::SetLogicDC(CDC* pDC)
{
	if(m_image.IsNull())
		return;
	CRect rc;
	GetClientRect(rc);
	int cx = rc.Width();
	int cy = rc.Height();

	if(cx == 0 || cy == 0)
		return;

	int iWidth = m_image.GetWidth();
	int iHeight = m_image.GetHeight();


	int yExt = (int)((float)cy / (float)cx * (float)iWidth);
	yExt = min(yExt, iHeight);

	pDC->SetStretchBltMode(HALFTONE);
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(iWidth, yExt);
	pDC->SetViewportExt(cx, cy);
	CPoint ptOldOrigin = pDC->SetViewportOrg(0, 0);
}

int CBookPage::CanNext(void)
{
	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_idx];
	int nPage = (int)cp.page;
	int size = (int)cp.paragraphs.GetCount();
	for(int i = 0; i < size; ++i)
	{
		int pageFromStart = cp.paragraphs[i].pageFromStart;
		if((pageFromStart + nPage) > m_nCurentPage)
		{
			if((size == 1 || i == 0) && pageFromStart)
				return move_next;
			return i;
		}
	}
	return 0;
}

int CBookPage::CanPrior(void)
{
	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_idx];
	int nPage = (int)cp.page;
	int size = (int)cp.paragraphs.GetCount();
	if(/*size == 1*/size > 0 && nPage < m_nCurentPage && cp.paragraphs[0].pageFromStart > 0)
	{
		return move_prior;
	}
	//else if(size > 0 && cp.paragraphs[0].pageFromStart > 0 )
	//{
	//	return move_prior;
	//}

	for(int i = size -1; i > -1; --i)
	{
		int pageFromStart = cp.paragraphs[i].pageFromStart;
		if((pageFromStart + nPage) < m_nCurentPage)
			return i;		
	}
	return -1;
}

void CBookPage::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	const int nLine = 10;
	SCROLLINFO si;
	ZeroMemory(&si, sizeof(SCROLLINFO));
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	GetScrollInfo(SB_VERT,&si);
	switch(nSBCode)
	{
	case SB_THUMBTRACK:
		m_nPos = nPos;
		break;
	case SB_LINEDOWN:
		if((int)(m_nPos + nLine + si.nPage) >= si.nMax)
		{
			int nParIdx = CanNext();
			if(nParIdx)
			{
				LoadPage(-2, nParIdx);
			}
			else
				m_nPos = si.nMax - si.nPage;
		}
		else
			m_nPos += nLine;			
		break;
	case SB_LINEUP:
		if((m_nPos - nLine) <= 0)
		{
			int nParIdx = CanPrior();
			if(nParIdx != -1)
			{
				LoadPage(-2, nParIdx);
			}
			else
				m_nPos = 0;
		}
		else
			m_nPos -= nLine;
		break;
	case SB_PAGEDOWN:
		if((int)(m_nPos + 5 * nLine + si.nPage) <= si.nMax)
			m_nPos += 5 * nLine;
		else
		{
			int nParIdx = CanNext();
			if(nParIdx)
			{
				LoadPage(-2, nParIdx);
			}
		}
		break;
	case SB_PAGEUP:
		if((m_nPos - 5 * nLine) >= 0)
			m_nPos -= 5 * nLine;
		else
		{
			int nParIdx = CanPrior();
			if(nParIdx != -1)
			{
				LoadPage(-2, nParIdx);
			}
			else
				m_nPos = 0;
		}
		break;
	case SB_TOP:
		m_nPos = 0;
		break;
	case SB_BOTTOM:
		m_nPos = si.nMax - si.nPage;
		break;
	}
	SetScrollPos(SB_VERT, m_nPos);

	CRect rc;
	GetClientRect(rc);
	InvalidateRect(rc, FALSE);

	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CBookPage::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	SetScrollBar(cx,cy);
}

void CBookPage::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	m_bHandCursor = false;
	m_nHeadLine = -1;
	switch(nChar)
	{
	case VK_DOWN:
		OnVScroll(SB_LINEDOWN ,0,0);
		break;
	case VK_UP:
		OnVScroll(SB_LINEUP ,0,0);
		break;
	case VK_NEXT:
		OnVScroll(SB_PAGEDOWN ,0,0);
		break;
	case VK_PRIOR:
		OnVScroll(SB_PAGEUP ,0,0);
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CBookPage::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_LOAD_PAGE:
		LoadPage((int)wParam, (int)lParam);
		return TRUE;
	}

	return CView::OnWndMsg(message, wParam, lParam, pResult);
}

void CBookPage::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_idx != -1)
	{
		CClientDC dc(this);
		SetLogicDC(&dc);
		CPoint p = point;
		dc.DPtoLP(&p);
		p.y += m_nPos;
		CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_idx];
		int size = (int)cp.paragraphs.GetCount();
		int i = 0;
		for(; i < size; ++i)
		{
			CParagraphInstant pi = cp.paragraphs[i];
			if((cp.page + pi.pageFromStart) != m_nCurentPage)
				continue;
			if(pi.hitRect.PtInRect(p))
				break;
		}
		m_bHandCursor = (i < size);
		m_nHeadLine = m_bHandCursor? i : -1;
	}

	CView::OnMouseMove(nFlags, point);
}

BOOL CBookPage::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	static HCURSOR hCur = theApp.LoadStandardCursor(MAKEINTRESOURCE(32649));

	if(m_bHandCursor)
	{
		SetCursor(hCur);
		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CBookPage::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_nHeadLine != -1)
	{
		GetParent()->PostMessageA(WM_SET_HEADLINE, m_nHeadLine);
	}

	CView::OnLButtonDown(nFlags, point);
}

void CBookPage::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if(m_nHeadLine != -1)
	{
		AfxGetMainWnd()->PostMessageA(WM_SHOW_GRAPH, m_nHeadLine);
	}

	CView::OnLButtonDblClk(nFlags, point);
}

BOOL CBookPage::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int nSBCode = (zDelta < 0)? SB_PAGEDOWN:SB_PAGEUP;
	OnVScroll(nSBCode, 0, NULL);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CBookPage::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

	m_bHandCursor = false;
}
