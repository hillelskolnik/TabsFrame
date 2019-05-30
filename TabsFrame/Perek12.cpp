// Perek12.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek12.h"


// CPerek12

IMPLEMENT_DYNCREATE(CPerek12, CPerek3DBase)

CPerek12::CPerek12()
{
	m_IDstart = ID_P12_1;
	m_IDidx = WT_PEREK_12;
	m_IDX_PEREK = IDX_PEREK_12;
}

CPerek12::~CPerek12()
{
}

BEGIN_MESSAGE_MAP(CPerek12, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P12_1, ID_P12_17, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P12_1, ID_P12_17, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek12 drawing

// CPerek12 diagnostics

#ifdef _DEBUG
void CPerek12::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek12::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek12 message handlers

const int trsz = 212;

enum
{
	egulKavit1
	,shetachEgul
	,muzak
	,cadorHzaim
	,alachson
	,kotev1
	,kotev2
	,kotev3
	,kotev4
	,kotev5
	,kotev6
	,egulKavit2
	,keshetEgul1
	,zavitChituch
	,zavitZara
	,zavitMeruvachat
	,kavHitoch1
	,kavHitoch2
	,egulKavit3
};
#define xPosAng  -30.0


int CPerek12::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	COLORREF color8 = cp.paragraphs[8].color;
	COLORREF color9 = cp.paragraphs[9].color;
	COLORREF color10 = cp.paragraphs[10].color;
	COLORREF color11 = cp.paragraphs[11].color;
	COLORREF color12 = cp.paragraphs[12].color;
	COLORREF color13 = cp.paragraphs[13].color;
	COLORREF color14 = cp.paragraphs[14].color;
	COLORREF color15 = cp.paragraphs[15].color;
	COLORREF color16 = cp.paragraphs[16].color;

	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 45.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();

	m_3dscreen.BeginObject(egulKavit1);
	m_3dscreen.CReateCircleLineObject(trsz+3,color0);
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(egulKavit2);
	m_3dscreen.CReateCircleLineObject(trsz+3,color7);
	m_3dscreen.TurnShape(90.0, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(egulKavit3);
	m_3dscreen.CReateCircleLineObject(trsz+3,color16);
	m_3dscreen.TurnShape(90.0, axis_Y, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(shetachEgul);
	m_3dscreen.CreatObjectPixselMap(trsz,trsz);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm1.GetMyPaintDC();
		CPen pen1(PS_SOLID,1,(COLORREF)0);
		CBrush br1(HS_HORIZONTAL ,cp.paragraphs[2].color);
		pdc->SelectObject(&pen1);
		pdc->SelectObject(&br1);
		CRect rc(0,0,trsz,trsz);
		pdc->FillSolidRect(CRect(0,0,trsz, trsz),0);
		pdc->Ellipse(rc);
		m_3dscreen.BitmapToObject(bm1, RGBT2(0,0));
	}
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(keshetEgul1);
	m_3dscreen.CReateCircleLineObject(trsz+3,color9, 2.0, 90.0);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	double shiftAng = 75;
	double dtrsz = (double)trsz;
	double shiftX = sin(shiftAng * D) * dtrsz / 2.0;
	double newtrsz = cos(shiftAng * D) * dtrsz;
	m_3dscreen.BeginObject(zavitChituch);
	m_3dscreen.CReateCircleLineObject((int)(float)newtrsz, 
		RGBT2(color10, 0), 2.5, 90.0);
	m_3dscreen.TurnShape(90.0, axis_z, false, true);
	m_3dscreen.TurnShape(90.0, axis_y, false, true);
	m_3dscreen.ShiftObjectCenter(shiftX, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(zavitZara);
	m_3dscreen.CReateCircleLineObject((int)(float)newtrsz, 
		RGBT2(color13, 0), 2.5, 90.0 + xPosAng);
	m_3dscreen.TurnShape(90.0 - xPosAng, axis_z, false, true);
	m_3dscreen.TurnShape(90.0, axis_y, false, true);
	m_3dscreen.ShiftObjectCenter(shiftX, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(zavitMeruvachat);
	m_3dscreen.CReateCircleLineObject((int)(float)newtrsz, 
		RGBT2(color14, 0), 2.5, 90.0 - xPosAng);
	m_3dscreen.TurnShape(90.0, axis_y, false, true);
	m_3dscreen.ShiftObjectCenter(shiftX, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kavHitoch1);
	m_3dscreen.CreatObjectPixselMap(trsz+2,trsz+2);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz+2,trsz+2,0);
		CDC* pdc = bm1.GetMyPaintDC();
		CPen pen1(PS_SOLID,2,color7);
		CBrush br1(RGB(128,128,255));
		pdc->SelectObject(&pen1);
		pdc->SelectObject(&br1);
		CRect rc(0,0,trsz+2,trsz+2);
		pdc->FillSolidRect(CRect(0,0,trsz+2, trsz+2),0);
		pdc->Ellipse(rc);
		m_3dscreen.BitmapToObject(bm1, RGBT2(0,0));
	}
	m_3dscreen.FillRect(0,0,trsz+2, trsz+2, color7
		,fr_xyIntensity , (double)(trsz+2) / 2.0 - 0.5);
	m_3dscreen.TurnShape(90.0, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kavHitoch2);
	m_3dscreen.CreatObjectPixselMap(trsz+2,trsz+2);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz+2,trsz+2,0);
		CDC* pdc = bm1.GetMyPaintDC();
		CPen pen1(PS_SOLID,2,color0);
		CBrush br1(RGB(192,130, 255));
		pdc->SelectObject(&pen1);
		pdc->SelectObject(&br1);
		CRect rc(0,0,trsz+2,trsz+2);
		pdc->FillSolidRect(CRect(0,0,trsz+2, trsz+2),0);
		pdc->Ellipse(rc);
		m_3dscreen.BitmapToObject(bm1, RGBT2(0,0));
	}
	m_3dscreen.FillRect(0,0,trsz+2, trsz+2, color0
		,fr_xyIntensity , (double)(trsz+2) / 2.0 - 0.5);
	m_3dscreen.TurnShape(xPosAng, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();


	int kotTrsz = DiameterSteps(7);
	m_3dscreen.BeginObject(muzak);
	m_3dscreen.CreateSphereObject(7, 
		ColDev(color1, 2));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, RGB(255,179,217)
		,fr_zIntensity , 3.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(0.0,axis_Y);
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.BeginObject(kotev1);
	m_3dscreen.CreateSphereObject(7, 
		ColDev(color5, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color5
		,fr_zIntensity , 3.5);
	m_3dscreen.ShiftObjectCenter(-((double)trsz / 2.0), axis_Z, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotev2);
	m_3dscreen.CreateSphereObject(7, 
		ColDev(color6, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color6
		,fr_zIntensity , 3.5);
	m_3dscreen.ShiftObjectCenter((double)trsz / 2.0, axis_Z, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotev3);
	m_3dscreen.CreateSphereObject(7, 
		ColDev(color8, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color8
		,fr_zIntensity , 3.5);
	m_3dscreen.ShiftObjectCenter((double)trsz / 2.0, axis_Y, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotev4);
	m_3dscreen.CreateSphereObject(7, 
		ColDev(color8, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color8
		,fr_zIntensity , 3.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz / 2.0, axis_Y, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotev5);
	m_3dscreen.CreateSphereObject(7, 
		ColDev(color16, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color16
		,fr_zIntensity , 3.5);
	m_3dscreen.ShiftObjectCenter((double)trsz / 2.0, axis_Z, true);
	m_3dscreen.TurnObjectCenter(90.0, axis_Y, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotev6);
	m_3dscreen.CreateSphereObject(7, 
		ColDev(color16, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color16
		,fr_zIntensity , 3.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz / 2.0, axis_Z, true);
	m_3dscreen.TurnObjectCenter(90.0, axis_Y, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(cadorHzaim);
	m_3dscreen.CreateSphereObject(trsz, 
		RGBT2(color3, 80), 360.0,90.0,-90.0,2.0);
	int steps = DiameterSteps(trsz,2.0);
	m_3dscreen.FillRect(0,0,steps/2, steps /2, RGBT(0,128,0,80));
	m_3dscreen.FillRect(0,0,steps/2, steps /2, RGB(64,192,64)
		,fr_zIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.FillRect(steps/2,0,steps, steps /2, RGB(128,255,128)
		,fr_zIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(alachson);
	m_3dscreen.CreateCylinderObject(3,3,trsz, 
		RGBT2(color4, 30)
		,360.0);
	m_3dscreen.TurnShape(90.0, axis_Z, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.TrigerPaintAlow();

	return 0;
}


void CPerek12::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = TRUE;


	if(m_bBntDown && m_bHandCursor)
	{
		double cx = (p.x - m_pt.x);
		double cy = p.y - m_pt.y;
		m_yTurn = cx /2.0;
		m_xTurn = cy / 2.0;//distent / 4.0;
		switch(m_buttonId)
		{
		case 3:
		case 6:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
			m_yTurn += 90.0;
			break;
		}


		//static int tt = 0;
		//if(tt % 5 == 0)
			Do3DPaint();
		//tt++;
		//if(tt == 10000)
		//	tt = 0;
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek12::Do3DPaint(void)
{
	if(m_bSkip)
		return;
	m_bSkip = true;

	m_3dscreen.ClearScreen();

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];

	m_3dscreen.BeginObject(muzak);
	if(m_buttonId >= 1)
	{
		m_3dscreen.Translate3Dto2D(FALSE);
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(alachson);
	if(m_buttonId >= 4 && m_buttonId < 7)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();
		//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		//m_3dscreen.TurnShape(m_xTurn, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kotev1);
	if(m_buttonId >= 5)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		if(m_buttonId >= 12 && m_buttonId != 16)
			m_3dscreen.TurnObjectCenter(xPosAng, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnShape(0.0, axis_X);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kotev2);
	if(m_buttonId >= 6)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		if(m_buttonId >= 12 && m_buttonId != 16)
			m_3dscreen.TurnObjectCenter(xPosAng, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnShape(0.0, axis_X);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kotev3);
	if(m_buttonId >= 8)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnShape(0.0, axis_X);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kotev4);
	if(m_buttonId >= 8 )
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnShape(0.0, axis_X);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kotev5);
	if(m_buttonId == 16 )
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnShape(0.0, axis_X);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kotev6);
	if(m_buttonId == 16 )
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnShape(0.0, axis_X);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(shetachEgul);
	if(m_buttonId >= 2 && m_buttonId < 7)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		//m_3dscreen.TurnShape(m_xTurn, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kavHitoch1);
	if(m_buttonId == 15)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		//m_3dscreen.TurnShape(m_xTurn, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kavHitoch2);
	if(m_buttonId == 15)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		//m_3dscreen.TurnShape(m_xTurn, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(egulKavit1);
	if((m_buttonId >= 0 && m_buttonId < 12) || m_buttonId == 16)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		//m_3dscreen.TurnShape(m_xTurn, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId >= 12)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(xPosAng, axis_X, false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		//m_3dscreen.TurnShape(m_xTurn, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(xPosAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(keshetEgul1);
	if(m_buttonId == 9)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		//m_3dscreen.TurnShape(m_xTurn, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(zavitChituch);
	if(m_buttonId >= 10 && m_buttonId < 12)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn+180, axis_Y, false);
		m_3dscreen.TurnShape(m_yTurn+180, axis_Y, false);
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X, false);
		m_3dscreen.TurnShape(m_xTurn, axis_X);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(zavitZara);
	if(m_buttonId >= 13 && m_buttonId < 15)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn+180, axis_Y, false);
		m_3dscreen.TurnShape(m_yTurn+180, axis_Y, false);
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X, false);
		m_3dscreen.TurnShape(m_xTurn, axis_X);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(zavitMeruvachat);
	if(m_buttonId >= 14 && m_buttonId < 15)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn+180, axis_Y, false);
		m_3dscreen.TurnShape(m_yTurn+180, axis_Y, false);
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X, false);
		m_3dscreen.TurnShape(m_xTurn, axis_X);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(egulKavit2);
	if(m_buttonId >= 7)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		//m_3dscreen.TurnShape(m_xTurn, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(egulKavit3);
	if(m_buttonId == 16)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		m_3dscreen.TurnShape(m_xTurn, axis_X);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(cadorHzaim);
	if(m_buttonId >= 3 && m_buttonId < 7)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		//m_3dscreen.TurnShape(m_xTurn, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
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

void CPerek12::InitOnSubHeadButton(void)
{
	switch(m_buttonId)
	{
	case 0:
	case 1:
	case 2:
	case 4:
	case 5:
	case 9:
		m_yTurn = m_xTurn = 0;
		break;
	case 3:
	case 6:
	case 7:
	case 8:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
		m_yTurn = 90;
		m_xTurn = 0;
		break;
	case 15:
	case 16:
		m_yTurn = 90;
		m_xTurn = 7;
		break;
	}

}
