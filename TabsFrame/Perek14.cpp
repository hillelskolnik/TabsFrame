// Perek14.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek14.h"


// CPerek14

IMPLEMENT_DYNCREATE(CPerek14, CPerek3DBase)

CPerek14::CPerek14()
: m_zTurn(0)
, m_nekudaSteps(0)
,m_sliderHorRc(0, ipHeight - 100, ipWidth, ipHeight)
{
	m_IDstart = ID_P14_1;
	m_IDidx = WT_PEREK_14;
	m_IDX_PEREK = IDX_PEREK_14;
}

CPerek14::~CPerek14()
{
}

BEGIN_MESSAGE_MAP(CPerek14, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P14_1, ID_P14_8, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P14_1, ID_P14_8, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek14 drawing

// CPerek14 diagnostics

#ifdef _DEBUG
void CPerek14::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek14::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek14 message handlers
const int trsz = 252;
const double cadurXAng = 15;

enum
{
	muzak
	,galgal
	,cadur2
	,cadur
	,kotev1
	,kotev2
	,bariach1
	,bariach2
	,nekoda
	,magalNekoda
	,nekoda2
	,magalNekoda2
};

int CPerek14::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];

	CClientDC dc(this);
	COLORREF color0 = cp.paragraphs[0].color;
	COLORREF color1 = cp.paragraphs[1].color;
	COLORREF color2 = cp.paragraphs[2].color;
	COLORREF color3 = cp.paragraphs[3].color;
	COLORREF color4 = cp.paragraphs[4].color;
	COLORREF color5 = cp.paragraphs[5].color;
	COLORREF color6 = cp.paragraphs[6].color;
	COLORREF color7 = cp.paragraphs[7].color;

	m_3dscreen.SetScreenWnd(this);
	m_memDc.CreateCompatibleDC(&dc);
	m_memBm.CreateCompatibleBitmap(&dc, ipWidth,ipHeight);
	m_memDc.SelectObject(&m_memBm);
	m_memDc.SelectObject(&m_font);

	m_3dscreen.SetSceenSize(400,300, 45.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();

	m_3dscreen.BeginObject(galgal);
	m_3dscreen.CReateCircleLineObject(trsz, 
		color0, 2.5);
	int steps2 = DiameterSteps(trsz, 2.5);
	m_3dscreen.FillRect(0,0,steps2, 2, RGB(255,0,0)
		,fr_yIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	int kotTrsz = DiameterSteps(7);

	m_3dscreen.BeginObject(kotev1);
	m_3dscreen.CreateSphereObject(7, 
		ColDev(color1, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color1
		,fr_zIntensity , 3.5);
	m_3dscreen.ShiftObjectCenter(-((double)trsz / 2.0), axis_Z, true);
	m_3dscreen.TurnObjectCenter(cadurXAng, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotev2);
	m_3dscreen.CreateSphereObject(7, 
		ColDev(color1, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color1
		,fr_zIntensity , 3.5);
	m_3dscreen.ShiftObjectCenter((double)trsz / 2.0, axis_Z, true);
	m_3dscreen.TurnObjectCenter(cadurXAng, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	kotTrsz = DiameterSteps(5);

	double shiftZAng = 50;
	double shiftZ = cos(shiftZAng * D) * (double)trsz/2.0;
	double shiftX2 = sin(shiftZAng * D) * (double)trsz/2.0;
	double startAng = 70;
	m_3dscreen.BeginObject(nekoda);
	m_3dscreen.CreateSphereObject(5, 
		ColDev(color5, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color5
		,fr_zIntensity , 2.5);
	m_3dscreen.ShiftObjectCenter(-shiftZ, axis_Z, true);
	m_3dscreen.ShiftObjectCenter(shiftX2, axis_X, true);
	m_3dscreen.TurnObjectCenter(startAng, axis_Z, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(nekoda2);
	m_3dscreen.CreateSphereObject(5, 
		ColDev(color5, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color5
		,fr_zIntensity , 2.5);
	m_3dscreen.ShiftObjectCenter(shiftZ, axis_Z, true);
	m_3dscreen.ShiftObjectCenter(shiftX2, axis_X, true);
	m_3dscreen.TurnObjectCenter(startAng- 30, axis_Z, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	int magalNekudaTrsz = (int)(float)(shiftX2 * 2);
	m_nekudaSteps = DiameterSteps(magalNekudaTrsz, 2);
	m_3dscreen.BeginObject(magalNekoda);
	m_3dscreen.CReateCircleLineObject(magalNekudaTrsz, 
		color7, 2);
	m_3dscreen.FillRect(0,0,m_nekudaSteps, 2, color6
		,fr_yIntensity , (double)magalNekudaTrsz / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(-shiftZ, axis_Z, true);
	m_3dscreen.TurnShape(startAng, axis_Z, false, true);
	m_3dscreen.TurnObjectCenter(cadurXAng, axis_X, true);
	m_3dscreen.TurnShape(cadurXAng, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(magalNekoda2);
	m_3dscreen.CReateCircleLineObject(magalNekudaTrsz, 
		color7, 2);
	m_3dscreen.FillRect(0,0,m_nekudaSteps, 2, color6
		,fr_yIntensity , (double)magalNekudaTrsz / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(shiftZ, axis_Z, true);
	m_3dscreen.TurnShape(startAng - 30, axis_Z, false, true);
	m_3dscreen.TurnObjectCenter(cadurXAng, axis_X, true);
	m_3dscreen.TurnShape(cadurXAng, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.BeginObject(cadur);
	m_3dscreen.CReateCircleLineObject(trsz, 
		RGBT(32,32,255, 0), 1.0, 360.0, 3);
	m_3dscreen.TurnShape(90, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	COLORREF col1 = RGBT(0,0,128, 95);
	COLORREF col2 = RGBT(0,0,160, 95);
	m_3dscreen.BeginObject(cadur2);
	m_3dscreen.CreateSphereObject(trsz, 
		RGBT(0,0,96, 95), 360.0,90.0,-90.0,1.5);
	int steps = DiameterSteps(trsz,1.5);
	m_3dscreen.FillRect(0,0,steps/6, steps /2, col1);
	m_3dscreen.FillRect(steps/6,0,steps/6, steps/2, col2);

	m_3dscreen.FillRect(steps/2,0,steps/6, steps /2, col1);
	m_3dscreen.FillRect(steps*4/6,0,steps/6, steps/2, col2);

	m_3dscreen.FillRect(0,0,steps, steps /2, RGB(32,96,244)
		,fr_yIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.TurnShape(90, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(muzak);
	m_3dscreen.CreateSphereObject(7, 
		RGBT2(color3, 0));
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(bariach1);
	m_3dscreen.CreatObjectPixselMap(trsz,1, color4);
	m_3dscreen.TurnShape(90, axis_X, false, true);
	m_3dscreen.TurnShape(90, axis_Y, false, true);
	m_3dscreen.TurnShape(cadurXAng, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(bariach2);
	m_3dscreen.CreatObjectPixselMap(trsz,1, color4);
	m_3dscreen.TurnShape(90, axis_Y, false, true);
	m_3dscreen.TurnShape(cadurXAng, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek14::Do3DPaint(void)
{
	if(m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(galgal);
	if(m_buttonId >= 0)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(m_zTurn, axis_Z, false);
		m_3dscreen.TurnShape(cadurXAng, axis_X, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(magalNekoda);
	if(m_buttonId >= 6)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);

		double zTurn = m_zTurn;
		while(zTurn > 360)
			zTurn -= 360;
		while(zTurn < 0)
			zTurn += 360;
		int steps = (m_buttonId == 7)?-1:(int)(float)((double)m_nekudaSteps * (zTurn/360));

		m_3dscreen.Translate3Dto2D(TRUE, 0, steps);
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

		m_3dscreen.BeginObject(nekoda);
	if(m_buttonId >= 5 && m_buttonId < 7)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_zTurn, axis_Z);
		m_3dscreen.TurnObjectCenter(cadurXAng, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}


	m_3dscreen.BeginObject(magalNekoda2);
	if(m_buttonId >= 6)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);

		double zTurn = m_zTurn;
		while(zTurn > 360)
			zTurn -= 360;
		while(zTurn < 0)
			zTurn += 360;
		int steps = (m_buttonId == 7)?-1:(int)(float)((double)m_nekudaSteps * (zTurn/360));

		m_3dscreen.Translate3Dto2D(TRUE, 0, steps);
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

		m_3dscreen.BeginObject(nekoda2);
	if(m_buttonId >= 5 && m_buttonId < 7)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_zTurn, axis_Z);
		m_3dscreen.TurnObjectCenter(cadurXAng, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}


	m_3dscreen.BeginObject(bariach1);
	if(m_buttonId >= 4)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}
	m_3dscreen.BeginObject(bariach2);
	if(m_buttonId >= 4)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kotev1);
	if(m_buttonId >= 1)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kotev2);
	if(m_buttonId >= 1)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(muzak);
	if(m_buttonId >= 3)
	{
		m_3dscreen.Translate3Dto2D(FALSE);
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(cadur);
	if(m_buttonId >= 2)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_zTurn, axis_Z);
		m_3dscreen.TurnMatrix(cadurXAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}
	m_3dscreen.BeginObject(cadur2);
	if(m_buttonId >= 2)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_zTurn, axis_Z);
		m_3dscreen.TurnMatrix(cadurXAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}


	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek14::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = TRUE;


	if(m_bBntDown && m_bHandCursor)
	{
		double cx = (p.x - m_pt.x);
		double cy = (p.y - m_pt.y);
		if(m_sliderHorRc.PtInRect(p))
			m_zTurn = -cx;
		else
			m_yTurn = cy /4.0;


		//static int tt = 0;
		//if(tt % 5 == 0)
			Do3DPaint();
		//tt++;
		//if(tt == 10000)
		//	tt = 0;
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek14::PaintSlider(void)
{
	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];
	COLORREF color = cp.paragraphs[m_buttonId].color;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	CRect rc2 = m_sliderHorRc;
	int n = m_memDc.SaveDC();
	m_memDc.FillSolidRect(rc2,0);

	CBrush br(color);


	rc2.DeflateRect(1,1,1,5);
	m_memDc.FrameRect(rc2, &br);


	dc.BitBlt(m_sliderHorRc.left,
		m_sliderHorRc.top,m_sliderHorRc.Width(),m_sliderHorRc.Height(),
		&m_memDc,m_sliderHorRc.left,m_sliderHorRc.top,SRCCOPY);

	m_memDc.RestoreDC(n);
}

BOOL CPerek14::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_EXTRA_DRAW:
		PaintSlider();
		return TRUE;
	}

	return CPerek3DBase::OnWndMsg(message, wParam, lParam, pResult);
}

void CPerek14::InitOnSubHeadButton(void)
{
	PaintSlider();
}
