// ToolExBar.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "ToolExBar.h"

#include "ButtonEx.h"


// CToolExBar

IMPLEMENT_DYNAMIC(CToolExBar, CToolBar)

CToolExBar::CToolExBar()
: m_pButtons(NULL)
, m_btnsCount(0)
, m_bRightAllig(TRUE)
, m_pBitmap(NULL)
{

}

CToolExBar::~CToolExBar()
{
	delete [] m_pButtons;
	delete [] m_pBitmap;
}


BEGIN_MESSAGE_MAP(CToolExBar, CToolBar)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CToolExBar message handlers



BOOL CToolExBar::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	GetClientRect(rc);
	rc.bottom += 20;
	rc.right += 10;

	RectPaint(rc, pDC, 0, RGB(128,128,128), -90,90, FALSE);
	return TRUE;
	return CToolBar::OnEraseBkgnd(pDC);
}

void CToolExBar::OnSize(UINT nType, int cx, int cy)
{
	CToolBar::OnSize(nType, cx, cy);

	if(m_pButtons && m_btnsCount)
	{
		CSize size = GetToolBarCtrl().GetButtonSize();
		for(int i = 0, y = 0; i < m_btnsCount; ++i, y += size.cy)
		{
			m_pButtons[i].MoveWindow(0,y, cx, size.cy);
		}
	}
}

BOOL CToolExBar::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_GET_ALIGAIN_RIGHT:
		*pResult = TRUE;
		return TRUE;
	}

	return CToolBar::OnWndMsg(message, wParam, lParam, pResult);
}
