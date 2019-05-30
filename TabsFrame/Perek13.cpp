// Perek13.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek13.h"


// CPerek13

IMPLEMENT_DYNCREATE(CPerek13, CPerek3DBase)

CPerek13::CPerek13()
: m_zTurn(0)
{
	m_IDstart = ID_P13_1;
	m_IDidx = WT_PEREK_13;
	m_IDX_PEREK = IDX_PEREK_13;
}

CPerek13::~CPerek13()
{
}

BEGIN_MESSAGE_MAP(CPerek13, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P13_1, ID_P13_3, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P13_1, ID_P13_3, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek13 drawing

// CPerek13 diagnostics

#ifdef _DEBUG
void CPerek13::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek13::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek13 message handlers

const int trsz = 252;
const double cadurXAng = 15;

enum
{
	muzak
	,galgal
	,cadur2
	,cadur
};

int CPerek13::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 45.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];

	CClientDC dc(this);
	COLORREF color0 = cp.paragraphs[0].color;
	COLORREF color1 = cp.paragraphs[1].color;
	COLORREF color2 = cp.paragraphs[2].color;

	int kotTrsz = DiameterSteps(7);
	m_3dscreen.BeginObject(muzak);
	m_3dscreen.CreateSphereObject(7, 
		ColDev(color1, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color1
		,fr_zIntensity , 3.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(0.0,axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(cadur);
	m_3dscreen.CReateCircleLineObject(trsz, 
		RGBT(32,32,255, 0), 1.0, 360.0, 3);
	m_3dscreen.TurnShape(90, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.BeginObject(galgal);
	m_3dscreen.CReateCircleLineObject(trsz, 
		RGB(0,0,255), 2.5);
	int steps2 = DiameterSteps(trsz, 2.5);
	m_3dscreen.FillRect(0,0,steps2, 2, color2
		,fr_yIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	COLORREF col1 = RGBT(0,0,128, 95);
	COLORREF col2 = RGBT(0,0,160, 95);
	m_3dscreen.BeginObject(cadur2);
	m_3dscreen.CreateSphereObject(trsz, 
		RGBT(0,0,96, 95), 360.0,90.0,-45.0,1.5);
	int steps = DiameterSteps(trsz,1.5);
	m_3dscreen.FillRect(0,0,steps/6, steps /3, col1);
	m_3dscreen.FillRect(steps/6,0,steps/6, steps/3, col2);

	m_3dscreen.FillRect(steps/2,0,steps/6, steps /3, col1);
	m_3dscreen.FillRect(steps*4/6,0,steps/6, steps/3, col2);

	m_3dscreen.FillRect(0,0,steps, steps /4, RGB(92,92,255)
		,fr_yIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.TurnShape(90, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.TrigerPaintAlow();

	return 0;
}

void CPerek13::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = TRUE;


	if(m_bBntDown && m_bHandCursor)
	{
		double cx = (p.x - m_pt.x);
		m_zTurn = -cx /2.0;


		//static int tt = 0;
		//if(tt % 5 == 0)
			Do3DPaint();
		//tt++;
		//if(tt == 10000)
		//	tt = 0;
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek13::Do3DPaint(void)
{
	if(m_bSkip)
		return;
	m_bSkip = true;

	m_3dscreen.ClearScreen();


	m_3dscreen.BeginObject(cadur);
	//m_3dscreen.ResetTranslation();
	//m_3dscreen.TurnShape(m_zTurn, axis_Z, false);
	//m_3dscreen.TurnShape(cadurXAng, axis_X);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(m_zTurn, axis_Z);
	m_3dscreen.TurnMatrix(cadurXAng, axis_X);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(muzak);
	if(m_buttonId >= 1)
	{
		m_3dscreen.Translate3Dto2D(FALSE);
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(galgal);
	if(m_buttonId == 2)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(m_zTurn, axis_Z, false);
		m_3dscreen.TurnShape(cadurXAng, axis_X);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}
	
	m_3dscreen.BeginObject(cadur2);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(m_zTurn, axis_Z);
	m_3dscreen.TurnMatrix(cadurXAng, axis_X);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}
