// Perek15.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek15.h"


// CPerek15

IMPLEMENT_DYNCREATE(CPerek15, CPerek3DBase)

CPerek15::CPerek15()
{
	m_xTurn = -15;

	m_IDstart = ID_P15_1;
	m_IDidx = WT_PEREK_15;
	m_IDX_PEREK = IDX_PEREK_15;
}

CPerek15::~CPerek15()
{
}

BEGIN_MESSAGE_MAP(CPerek15, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P15_1, ID_P15_3, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P15_1, ID_P15_3, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


// CPerek15 drawing

// CPerek15 diagnostics

#ifdef _DEBUG
void CPerek15::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek15::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek15 message handlers
const int trsz = 296;
const double earthAng = 5;
const double yTurn = 15;
const int timeElp = 30;
enum
{
	earth
	,sky
	,ole
	,yored
};

int CPerek15::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];

	CClientDC dc(this);
	COLORREF color0 = cp.paragraphs[0].color;
	COLORREF color1 = cp.paragraphs[1].color;
	COLORREF color2 = cp.paragraphs[2].color;

	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 45.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();
	m_3dscreen.NoPaint();

	m_3dscreen.BeginObject(earth);

	m_3dscreen.CreatObjectPixselMap(trsz,trsz);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm1.GetMyPaintDC();
		CPen pen1(PS_SOLID,1,(COLORREF)0);
		CBrush br1(color0);
		pdc->SelectObject(&pen1);
		pdc->SelectObject(&br1);
		CRect rc(0,0,trsz,trsz);
		pdc->FillSolidRect(CRect(0,0,trsz, trsz),0);
		pdc->Ellipse(rc);
		m_3dscreen.BitmapToObject(bm1, RGBT2(0,50));
	}
	m_3dscreen.FillRect(0,0,trsz, trsz, RGBT(0,128,0,50)
		,fr_xyIntensity , (double)trsz / 2.0 - 0.5);
	//m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(90.0 + earthAng, axis_X, false, true);
	m_3dscreen.Translate3Dto2D();

	int steps = DiameterSteps(trsz);
	m_3dscreen.BeginObject(sky);
	m_3dscreen.CreateSphereObject(trsz, RGBT(128,0,192, 95));
	m_3dscreen.FillRect(0,0,steps, steps/4, RGBT(0,128,255,95)
		,fr_yIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.FillRect(0,steps/4,steps, steps/4, RGBT(0,0,1,95)
		,fr_yIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(earthAng, axis_X);
	m_3dscreen.Translate3Dto2D();
	m_3dscreen.ScreenToDC(TRUE);
	m_3dscreen.ClearScreen();
	m_3dscreen.DeleteObject(sky);
	
	int kotTrsz = DiameterSteps(16);

	m_3dscreen.BeginObject(ole);
	m_3dscreen.CreateSphereObject(16, 
		ColDev(color1, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color1
		,fr_zIntensity , 8.0);
	m_3dscreen.ShiftObjectCenter(-(double)trsz / 2.0, axis_Z, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(yored);
	m_3dscreen.CreateSphereObject(16, 
		ColDev(color2, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color2
		,fr_zIntensity , 8.0);
	m_3dscreen.ShiftObjectCenter((double)trsz / 2.0, axis_Z, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.TrigerPaintAlow();
	//if(m_buttonId > 0)
	//{
	//SetTimer(2, 600, NULL);
	//}
	
	return 0;
}

void CPerek15::Do3DPaint(void)
{
	if(m_bPastCreate == false)
		return;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(ole);
	if(m_buttonId == 1)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(yored);
	if(m_buttonId == 2)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	static double lasty = 2222222;
	m_3dscreen.BeginObject(earth);
	if(m_yTurn == lasty)
	{
		m_3dscreen.Translate3Dto2D(FALSE);
	}
	else
	{
		m_3dscreen.BeginObject(earth);
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	lasty = m_yTurn;

	m_3dscreen.ScreenToDC();
}

void CPerek15::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = TRUE;


	if(m_bBntDown && m_bHandCursor)
	{
		double cx = (p.x - m_pt.x);
		m_yTurn = cx / 4.0;


		if(m_buttonId && m_bPastCreate)
			SetTimer(1, timeElp, NULL);
		static int tt = 0;
		if(tt % 3 == 0)
		{
			Do3DPaint();
		}
		tt++;
		if(tt == 10000)
			tt = 0;
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek15::OnSetFocus(CWnd* pOldWnd)
{
	CPerek3DBase::OnSetFocus(pOldWnd);

	if(m_buttonId > 0)
	{
		SetTimer(1, timeElp, NULL);
	}
}

void CPerek15::InitOnSubHeadButton(void)
{
	if(m_buttonId == 0)
	{
		KillTimer(1);
	}
	else
	{
		SetFocus();
		SetTimer(1, timeElp, NULL);
	}
}

void CPerek15::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 1)
	{
		static double cy = 0;
		m_xTurn = -(fmod(cy , 60.0)- 30.0);
		cy += 0.5;
		if(cy > 20000 * 15)
			cy = 0;
		if(m_bNoTimerDraw == false)
			Do3DPaint();
	}

	
	CPerek3DBase::OnTimer(nIDEvent);
}

void CPerek15::OnKillFocus(CWnd* pNewWnd)
{
	CPerek3DBase::OnKillFocus(pNewWnd);

	KillTimer(1);
}

BOOL CPerek15::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_ON_TRIGER_MSG:
		if(wParam == 0)
		{
			SetTimer(1, timeElp, NULL);
			m_bPastCreate = true;
			m_3dscreen.OnPaint();
			CClientDC dc(this);
			OnPrepareDC(&dc);
			CaptionDraw(&dc);
			Do3DPaint();
			return TRUE;
		}
		break;
	}

	return CPerek3DBase::OnWndMsg(message, wParam, lParam, pResult);
}
