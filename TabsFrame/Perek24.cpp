// Perek24.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek24.h"


// CPerek24

IMPLEMENT_DYNCREATE(CPerek24, CPerek3DBase)


CPerek24::CPerek24()
: trsz(360)
, xStart(5)
, timerElaps(20)
, stepsMagalKohav(DiameterSteps(trsz))
, sShemesh(13)
, lasty(0)
{
	m_IDstart = ID_P24_1;
	m_IDidx = WT_PEREK_24;
	m_IDX_PEREK = IDX_PEREK_24;
}

CPerek24::~CPerek24()
{
}

BEGIN_MESSAGE_MAP(CPerek24, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P24_1, ID_P24_7, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P24_1, ID_P24_7, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


// CPerek24 diagnostics

#ifdef _DEBUG
void CPerek24::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek24::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG

enum
{
	halal
	,galgalMashveHaYom
	,kohav
	,mslulKohav
	,shemesh
	,mesibatShemesh
	,galgalDome
	,galgalDomeSshetach
	,nekuda1
	,nekuda2
	,galgalMazalot
	,kavLekuty
};

int CPerek24::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 30.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();


	int steps = DiameterSteps(trsz);
	m_3dscreen.BeginObject(halal);
	m_3dscreen.CreateSphereObject(trsz, RGBT(48,48,48, 0));
	m_3dscreen.FillRect(0,0,steps, steps/2, RGBT(0,0,0,0)
		,fr_zIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();
	m_3dscreen.ScreenToDC(TRUE);
	m_3dscreen.ClearScreen();
	m_3dscreen.DeleteObject(halal);

	m_3dscreen.BeginObject(galgalMashveHaYom);
	m_3dscreen.CReateCircleLineObject(trsz,color0);
	m_3dscreen.TurnShape(90 + xStart, axis_X, false, true);

	m_3dscreen.BeginObject(mesibatShemesh);
	m_3dscreen.CReateCircleLineObject(trsz,color2);
	m_3dscreen.TurnShape(90, axis_X, false, true);

	int kotTrsz = DiameterSteps(9);
	m_3dscreen.BeginObject(kohav);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color1, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color1
		,fr_zIntensity , 4.5);
	m_3dscreen.ResetTranslation();

	
	m_3dscreen.BeginObject(mslulKohav);
	m_3dscreen.CReateCircleLineObject(trsz,color1);
	m_3dscreen.TurnShape(90, axis_X, false, true);

	int stepsShem = DiameterSteps(sShemesh);
	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(128,0,0, 0));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(255,128,0,0)
		,fr_zIntensity , (double)sShemesh / 2.0 - 0.5);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(galgalDome);
	m_3dscreen.CReateCircleLineObject(trsz,color3);
	m_3dscreen.TurnShape(90, axis_X, false, true);

	int ms = 15;
	m_3dscreen.BeginObject(galgalDomeSshetach);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm1.GetMyPaintDC();
		int n = pdc->SaveDC();
		CPen pen1(PS_SOLID,1,color3);
		CBrush br1(/*HS_VERTICAL,*/color3);
		pdc->SelectObject(&pen1);
		pdc->SelectObject(&br1);
		CRect rc(0,0,trsz,trsz);
		pdc->FillSolidRect(CRect(0,0,trsz, trsz),0);
		pdc->Ellipse(rc);

		rc.DeflateRect(ms,ms);


		CBrush br2(RGB(0,0,0)/*color3*/);
		pdc->SelectObject(&br2);
		pdc->Ellipse(rc);

		m_3dscreen.CreateFlatBmObj(bm1);
		pdc->RestoreDC(n);
	}
	m_3dscreen.TurnShape(90, axis_X, false, true);

	m_3dscreen.BeginObject(galgalMazalot);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,1080,48,0);
		CDC* pdc = bm1.GetMyPaintDC();
		int n = pdc->SaveDC();
		pdc->RestoreDC(n);
		pdc->SetBkColor(0);
		CPen pen1(PS_SOLID,1,color5);
		pdc->SelectObject(&pen1);
		CBrush br(HS_BDIAGONAL,(COLORREF)color5);
		pdc->FillRect(CRect(0,0,1080,48),&br);
		pdc->MoveTo(0,0);
		pdc->LineTo(1079,0);
		pdc->MoveTo(0,47);
		pdc->LineTo(1079,47);
		CPoint topp(0,0);
		CPoint bottomp(0,47);
		CPoint plusp(90,0);
		for(int i = 0; i < 12; ++i, topp += plusp, bottomp += plusp)
		{
			pdc->MoveTo(topp);
			pdc->LineTo(bottomp);
		}

		m_3dscreen.CreateSphereBmObj(trsz-2*ms,bm1,9,-9);
		pdc->RestoreDC(n);
	}


	m_3dscreen.BeginObject(nekuda1);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color4, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color4
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz/2, axis_X, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(nekuda2);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color4, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color4
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2, axis_X, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(kavLekuty);
	m_3dscreen.CReateCircleLineObject(trsz-2*ms, color6, 3);
	m_3dscreen.TurnShape(90, axis_X, false, true);


	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek24::Do3DPaint(void)
{
	if(m_bPastCreate == false || m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();


	m_3dscreen.BeginObject(galgalMashveHaYom);
	if(m_buttonId >= 3)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		static bool bneedPaint = true;
		if(lasty != m_yTurn && bneedPaint == false)
		{
			m_3dscreen.Translate3Dto2D(FALSE);
			bneedPaint = true;
		}
		else
		{
			bneedPaint = false;
			m_3dscreen.ResetTranslation();
			m_3dscreen.ResetShift();
			m_3dscreen.TurnShape(0, axis_Y);
			m_3dscreen.Translate3Dto2D();
		}
	}

	m_3dscreen.BeginObject(kavLekuty);
	if(m_buttonId == 6)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnShape(23.5 + xStart, axis_X, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(galgalDome);
	if(m_buttonId >= 3)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnShape(23.5 + xStart, axis_X, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(galgalMazalot);
	if(m_buttonId >= 5)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnShape(23.5 + xStart, axis_X, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(galgalDomeSshetach);
	if(m_buttonId >= 3)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnShape(23.5 + xStart, axis_X, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekuda1);
	if(m_buttonId >= 4)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekuda2);
	if(m_buttonId >= 4)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(shemesh);
	if(m_buttonId == 2)
	{
//		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		double halfTrsz = trsz/2;
		double sAliya = 
			asin(SinNetyatAliyaYeshara(m_yTurn, 23.5)) *ToD;
		double shiftY = sin(sAliya * D) * halfTrsz;
		double shiftX = cos(sAliya * D) * halfTrsz;
		m_3dscreen.ShiftObjectCenter(shiftX, axis_X);
		m_3dscreen.ShiftObjectCenter(shiftY, axis_Y);
		m_3dscreen.TurnObjectCenter(-m_yTurn * 365.25, axis_Y);
		m_3dscreen.TurnObjectCenter(xStart, axis_X);
		m_3dscreen.TurnShape(0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(mesibatShemesh);
	if(m_buttonId == 2)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		double sAliya = 
			asin(SinNetyatAliyaYeshara(m_yTurn, 23.5)) *ToD;
		//m_3dscreen.FillRect(0,0,stepsMagalKohav, 3, 0
		//	,fr_shrink , cos(sAliya * D));
		double halfTrsz = trsz/2;
		double shiftY = sin(sAliya * D) * halfTrsz;
		m_3dscreen.ShiftObjectCenter(shiftY, axis_Y);
		m_3dscreen.TurnObjectCenter(xStart, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(xStart, axis_X);
		m_3dscreen.TurnMatrix(cos(sAliya * D), axis_S);
		m_3dscreen.Transform();
		//m_3dscreen.TurnShape(xStart, axis_X);
		double step = (double)stepsMagalKohav/360;
		double yt = fmod(m_yTurn * 365.25, 360);
		double steps = step * yt;
		m_3dscreen.Translate3Dto2D(TRUE ,0, (int)steps);
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(kohav);
	if(m_buttonId == 1)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		double halfTrsz = trsz/2;
		double shiftY = sin(-m_xTurn * D) * halfTrsz;
		double shiftX = cos(-m_xTurn * D) * halfTrsz;
		m_3dscreen.ShiftObjectCenter(shiftX, axis_X);
		m_3dscreen.ShiftObjectCenter(shiftY, axis_Y);
		m_3dscreen.TurnObjectCenter(-m_yTurn, axis_Y);
		m_3dscreen.TurnObjectCenter(xStart, axis_X);
		m_3dscreen.TurnShape(0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(mslulKohav);
	if(m_buttonId == 1)
	{
//		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		//m_3dscreen.FillRect(0,0,stepsMagalKohav, 3, 0
		//	,fr_shrink , cos(-m_xTurn * D));
		double halfTrsz = trsz/2;
		double shiftY = sin(-m_xTurn * D) * halfTrsz;
		m_3dscreen.ShiftObjectCenter(shiftY, axis_Y);
		m_3dscreen.TurnObjectCenter(xStart, axis_X);
		//m_3dscreen.TurnShape(xStart, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(xStart, axis_X);
		m_3dscreen.TurnMatrix(cos(-m_xTurn * D), axis_S);
		m_3dscreen.Transform();
		double step = (double)stepsMagalKohav/360;
		double steps = step * m_yTurn;
		m_3dscreen.Translate3Dto2D(TRUE ,0, (int)steps);
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	lasty = m_yTurn;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek24::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = TRUE;


	if(m_bBntDown && m_bHandCursor )
	{
		double cx = (p.x - m_pt.x);
		double cy = (p.y - m_pt.y);

		switch(m_buttonId)
		{
		case 0:
		case 1:
		case 2:
			break;
		default:
			m_xTurn = cy / 3.0;
			m_yTurn = cx / 3.0;
			Do3DPaint();
			break;
		}

	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek24::OnTimer(UINT_PTR nIDEvent)
{
	switch(m_buttonId)
	{
	case 1:
		++m_yTurn;
		if(m_yTurn >= 360)
			m_yTurn -= 360;

		if(m_bNoTimerDraw == false)
			Do3DPaint();
		break;
	case 2:
		m_yTurn += (360/ 365.25)/90;
		if(m_yTurn >= 365.25)
			m_yTurn -= 365.25;

		if(m_bNoTimerDraw == false)
			Do3DPaint();
		break;
	}

	CPerek3DBase::OnTimer(nIDEvent);
}

void CPerek24::InitOnSubHeadButton(void)
{
	
	switch(m_buttonId)
	{
	case 0:
		lasty = m_yTurn;
	case 1:
		m_xTurn = -15;
		m_yTurn = 0;
		SetTimer(1, timerElaps, NULL);
		break;
	case 2:
		m_xTurn = 0;
		m_yTurn = 0;
		SetTimer(1, timerElaps/3, NULL);
		break;
	default:
		lasty = 0;
		KillTimer(1);
		m_yTurn = 0;
		break;
	}
}

void CPerek24::OnKillFocus(CWnd* pNewWnd)
{
	CPerek3DBase::OnKillFocus(pNewWnd);

	KillTimer(1);
}

void CPerek24::OnSetFocus(CWnd* pOldWnd)
{
	CPerek3DBase::OnSetFocus(pOldWnd);

	switch(m_buttonId)
	{
	case 1:
		SetTimer(1, timerElaps, NULL);
		break;
	case 2:
		SetTimer(1, timerElaps/3, NULL);
		break;
	}
}
