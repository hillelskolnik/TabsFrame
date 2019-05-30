// ButtonEx.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "ButtonEx.h"

#include "ToolExBar.h"


// CButtonEx

IMPLEMENT_DYNAMIC(CButtonEx, CButton)

CButtonEx::CButtonEx()
: m_bMouseTracking(FALSE)
, m_bChected(FALSE)
{

}

CButtonEx::~CButtonEx()
{
}


BEGIN_MESSAGE_MAP(CButtonEx, CButton)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CButtonEx message handlers



BOOL CButtonEx::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	GetClientRect(rc);
	BOOL bRightAllig = (BOOL)((GetParent()->SendMessage(WM_GET_ALIGAIN_RIGHT)) == TRUE);
	if(bRightAllig)
	{
		RectPaint(rc, pDC, 0, RGB(128,128,128), -90,90, FALSE);
	}
	else
		RectPaint(rc,pDC);
	return TRUE;

	return CButton::OnEraseBkgnd(pDC);
}

HBRUSH CButtonEx::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  Change any attributes of the DC here

	static CBrush br(RGB(123,157,234));
	return br;
}

void CButtonEx::DrawItem(LPDRAWITEMSTRUCT lpD)
{

	CRect rc = lpD->rcItem;
	CDC *pDC = CDC::FromHandle(lpD->hDC);
	CBitmap *pBm = CBitmap::FromHandle( GetBitmap());
	BOOL bRightAllig = (BOOL)GetParent()->SendMessage(WM_GET_ALIGAIN_RIGHT) == TRUE;
	if(bRightAllig)
	{
		RectPaint(rc, pDC, 0, RGB(128,128,128), -90,90, FALSE);
	}
	else
		RectPaint(rc,pDC);
	BITMAP bm;
	pBm->GetBitmap(&bm);
	CDC bmDc;
	bmDc.CreateCompatibleDC(pDC);
	CBitmap* oBm = bmDc.SelectObject(pBm);
	int top = (rc.Height() -bm.bmHeight) / 2;
	int left = (rc.Width() -bm.bmWidth) / 2;
	if(lpD->itemState & (ODS_DISABLED /*| ODS_SELECTED*/))
	{
		for(int i=0; i< bm.bmHeight; ++i)
		{
			for(int j=0; j < bm.bmWidth;++j)
			{
				COLORREF col = bmDc.GetPixel(j,i);
				int r = GetRValue(col);
				int g = GetGValue(col);
				int b = GetBValue(col);
				int ev = (r + g + b) / 3;
				col = RGB(ev,ev,ev);
				pDC->SetPixelV(j+left,i+top,col);
			}
		}
	}
	else if(lpD->itemState & ODS_SELECTED)
	{
		for(int i=0; i< bm.bmHeight; ++i)
		{
			for(int j=0; j < bm.bmWidth;++j)
			{
				COLORREF col = bmDc.GetPixel(j,i);
				int r = ((int)GetRValue(col)*27)/30;
				int g = ((int)GetGValue(col)*27)/30;
				int b = ((int)GetBValue(col)*27)/30;
				col = RGB(r,g,b);
				pDC->SetPixelV(j+left,i+top,col);
			}
		}
	}
	else
	{
		pDC->BitBlt(left,top,bm.bmWidth,bm.bmHeight,&bmDc,0,0,SRCCOPY);
	}
	int x = bRightAllig?6:2;
	int y = bRightAllig?1:2;
	rc.DeflateRect(x,y);
	if(bRightAllig)
		rc.top -= 1;
	if(m_bMouseTracking && m_bChected == FALSE)
	{
		CBrush br(RGB(255,255,255));
		pDC->FrameRect(rc, &br);
	}
	else if(m_bChected)
	{
		CBrush br(pBm/*RGB(192,192,192)*/);
		pDC->FrameRect(rc, &br);
	}
	bmDc.SelectObject(oBm);
}

BOOL CButtonEx::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_MOUSELEAVE:
		{
			m_bMouseTracking = FALSE;
			Invalidate();
		}
		break;
	}

	return CButton::OnWndMsg(message, wParam, lParam, pResult);
}

void CButtonEx::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_bMouseTracking == FALSE)
	{
		m_bMouseTracking = CTrackMouseEvent(this).Track();
		Invalidate(FALSE);
	}

	CButton::OnMouseMove(nFlags, point);
}
