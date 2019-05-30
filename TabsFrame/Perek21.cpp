// Perek21.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek21.h"


// CPerek21
const int trsz = 346;
const int trszArez = 175;
const double fine = 2.0;
const int plus = 4;

IMPLEMENT_DYNCREATE(CPerek21, CPerek3DBase)

CPerek21::CPerek21()
: m_person(m_3dscreen)
, m_stepsKav(DiameterSteps(trszArez + plus, fine))
, m_stepsRochavMevukash(DiameterSteps(trszArez + plus + 2, fine))
, m_stepsTrszP2(DiameterSteps(trsz + 2, fine))
, m_bLbDown(false)
, m_yTplus(0)
, m_xTplus(0)
{
	m_IDstart = ID_P21_1;
	m_IDidx = WT_PEREK_21;
	m_IDX_PEREK = IDX_PEREK_21;
}

CPerek21::~CPerek21()
{
}

BEGIN_MESSAGE_MAP(CPerek21, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P21_1, ID_P21_19, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P21_1, ID_P21_19, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// CPerek21 drawing

// CPerek21 diagnostics

#ifdef _DEBUG
void CPerek21::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek21::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek21 message handlers
const double xTurnStart = 7.5;
const double yTurnStart = 2.5;

enum
{
	halal
	,cadur
	,egulHakuk
	,raviaCadur
	,kotevEl
	,kotevTch
	,nekudaNochachat
	,egulGadol
	,zavitYeshara
	,rochavMevukash

	,arez
	,kavRohav
	,kotevZ
	,kotevD
	,mekomMedina
	,kavHaShave
	,zavitYeshara2
	,rochavMedina

	,keshetOfanHaziYom
	,kotevOlamZ
	,kotevOlamD
	,nekudatRosh
	,shetachgalgalHaShave
	,galgalHaShave
	,rochavMeNekudatRosh
};


int CPerek21::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CMyFBitmap bm11;
	CString path = theApp.m_appPath + "Images\\Earth.bmp";
	CImage image22;
	image22.Load(path);
	bm11.CreateMyCompatibleBitmap(NULL, image22.GetWidth(),
		image22.GetHeight());
	image22.BitBlt(bm11.operator CDC *()->GetSafeHdc(),
		CPoint(0,0));

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
	COLORREF color17 = cp.paragraphs[17].color;
	COLORREF color18 = cp.paragraphs[18].color;

	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 30.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();
	m_3dscreen.NoPaint();


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

	int stepsArez = DiameterSteps(trszArez);
	m_3dscreen.BeginObject(cadur);
	m_3dscreen.CreateSphereObject(trszArez, RGBT(0,97,193, 0));
	m_3dscreen.FillRect(0,0,stepsArez, stepsArez/2, RGBT(55,155,255,0)
		,fr_yIntensity , (double)trszArez / 2.0 - 0.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(xTurnStart, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(egulHakuk);
	m_3dscreen.CReateCircleLineObject(trszArez+plus, color0, fine);
	m_3dscreen.TurnShape(90 + xTurnStart, axis_X,false ,true);

	m_3dscreen.BeginObject(kavRohav);
	m_3dscreen.CReateCircleLineObject(trszArez+plus, color7, fine);
	m_3dscreen.TurnShape(90 + xTurnStart, axis_X,false ,true);

	m_3dscreen.BeginObject(raviaCadur);
	m_3dscreen.CReateCircleLineObject(trszArez+plus, color1,
		1, 90);

	m_3dscreen.BeginObject(keshetOfanHaziYom);
	m_3dscreen.CReateCircleLineObject(trsz, color14,
		1, 90);

	m_3dscreen.BeginObject(rochavMevukash);
	m_3dscreen.CReateCircleLineObject(trszArez+plus + 2, color6,
		fine, 90);
	m_3dscreen.TurnShape(-90, axis_Y, false, true);

	m_3dscreen.BeginObject(rochavMedina);
	m_3dscreen.CReateCircleLineObject(trszArez+plus + 2, color13,
		fine, 90);
	m_3dscreen.TurnShape(-90, axis_Y, false, true);

	m_3dscreen.BeginObject(rochavMeNekudatRosh);
	m_3dscreen.CReateCircleLineObject(trsz + 2, color18,
		fine, 90);
	m_3dscreen.TurnShape(-90, axis_Y, false, true);

	m_3dscreen.BeginObject(egulGadol);
	m_3dscreen.CReateCircleLineObject(trszArez+2, color4);
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(90 + xTurnStart, axis_X, false);
	m_3dscreen.TurnShape(yTurnStart, axis_Y);
	m_3dscreen.Translate3Dto2D();

	int kotTrsz = DiameterSteps(9);
	m_3dscreen.BeginObject(kotevEl);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color2, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color2
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(((double)trszArez / 2.0), axis_Y, true);
	m_3dscreen.TurnObjectCenter(xTurnStart, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotevTch);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color2, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color2
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-((double)trszArez / 2.0), axis_Y, true);
	m_3dscreen.TurnObjectCenter(xTurnStart, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(nekudaNochachat);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color3, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color3
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-((double)trszArez / 2.0), axis_Z, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(mekomMedina);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color8, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color8
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-((double)trszArez / 2.0), axis_Z, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(nekudatRosh);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color16, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color16
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-((double)trsz / 2.0), axis_Z, true);
	m_3dscreen.ResetTranslation();

	double shiftAng = 75;
	double dtrsz = (double)trszArez + 2.0;
	double shiftZ = sin(shiftAng * D) * dtrsz / 2.0;
	double newtrsz = cos(shiftAng * D) * dtrsz;
	m_3dscreen.BeginObject(zavitYeshara);
	m_3dscreen.CReateCircleLineObject((int)(float)newtrsz, 
		RGBT2(color5, 0), 2.5, 90.0);
	m_3dscreen.TurnShape(90.0, axis_z, false, true);
	m_3dscreen.ShiftObjectCenter(-shiftZ, axis_Z, true);

	m_3dscreen.BeginObject(zavitYeshara2);
	m_3dscreen.CReateCircleLineObject((int)(float)newtrsz, 
		RGBT2(color12, 0), 2.5, 90.0);
	m_3dscreen.TurnShape(90.0, axis_z, false, true);
	m_3dscreen.ShiftObjectCenter(-shiftZ, axis_Z, true);

	m_3dscreen.BeginObject(arez);
	m_3dscreen.CreateSphereObject(trszArez, RGBT2(color2, 95),
		360.0,90.0,-90.0, 1.2);
	m_3dscreen.BitmapToObject(bm11, RGBT2(0,0));
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.BeginObject(kotevZ);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color10, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color10
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(((double)trszArez / 2.0), axis_Y, true);
	m_3dscreen.TurnObjectCenter(xTurnStart, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotevD);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color10, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color10
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-((double)trszArez / 2.0), axis_Y, true);
	m_3dscreen.TurnObjectCenter(xTurnStart, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotevOlamZ);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color15, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color15
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(((double)trsz / 2.0), axis_Y, true);
	m_3dscreen.TurnObjectCenter(xTurnStart, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotevOlamD);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color15, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color15
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-((double)trsz / 2.0), axis_Y, true);
	m_3dscreen.TurnObjectCenter(xTurnStart, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kavHaShave);
	m_3dscreen.CReateCircleLineObject(trszArez+2, color11);
	m_3dscreen.TurnShape(90 + xTurnStart , axis_X, false , true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(shetachgalgalHaShave);
//	m_3dscreen.CreatObjectPixselMap(trsz,trsz);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm1.GetMyPaintDC();
		CPen pen1(PS_SOLID,2,(COLORREF)color17);
		CBrush br1((COLORREF)0);
		pdc->SelectObject(&pen1);
		pdc->SelectObject(&br1);
		CRect rc(0,0,trsz,trsz);
		pdc->FillSolidRect(CRect(0,0,trsz, trsz),0);
		rc.DeflateRect(2,2);
		pdc->Ellipse(rc);

		double degree = 0;
		for(int i = 0; i < 24; ++i, degree += 15.0)
		{
			DrawPolyLines(2, rc.Width() / 2,
				rc.CenterPoint(),bm1, degree, 180.0);
		}

		//m_3dscreen.BitmapToObject(bm1, RGBT2(0,0));
		m_3dscreen.CreateFlatBmObj(bm1);
	}
	m_3dscreen.TurnShape(90, axis_X, false, true);

	m_3dscreen.BeginObject(galgalHaShave);
	m_3dscreen.CReateCircleLineObject(trsz, color17,2.6);
	m_3dscreen.TurnShape(90 + xTurnStart, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_person.Create();

	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek21::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(raviaCadur);
	if(m_buttonId >= 1 && m_buttonId != 7 && m_buttonId != 8)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.InitMatrix();
		if(m_xTurn < 0)
		{
			//m_3dscreen.TurnShape(180, axis_X,false);
			m_3dscreen.TurnMatrix(180, axis_X);
		}
		//m_3dscreen.TurnShape(270 + yTurnStart, axis_Y,false);
		//m_3dscreen.TurnShape(xTurnStart, axis_X, !m_bLbDown);
		m_3dscreen.TurnMatrix(270 + yTurnStart, axis_Y);
		m_3dscreen.TurnMatrix(xTurnStart, axis_X);
		if(m_bLbDown)
		{
			//m_3dscreen.TurnShape(m_yTplus, axis_Y, false);
			//m_3dscreen.TurnShape(m_xTplus, axis_X);
			m_3dscreen.TurnMatrix(m_yTplus, axis_Y);
			m_3dscreen.TurnMatrix(m_xTplus, axis_X);
		}
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(keshetOfanHaziYom);
	if(m_buttonId >= 14 )
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.InitMatrix();
		if(m_xTurn < 0)
		{
			//m_3dscreen.TurnShape(180, axis_X,false);
			m_3dscreen.TurnMatrix(180, axis_X);
		}
		//m_3dscreen.TurnShape(270 + yTurnStart, axis_Y,false);
		//m_3dscreen.TurnShape(xTurnStart, axis_X, !m_bLbDown);
		m_3dscreen.TurnMatrix(270 + yTurnStart, axis_Y);
		m_3dscreen.TurnMatrix(xTurnStart, axis_X);
		if(m_bLbDown)
		{
			//m_3dscreen.TurnShape(m_yTplus, axis_Y, false);
			//m_3dscreen.TurnShape(m_xTplus, axis_X);
			m_3dscreen.TurnMatrix(m_yTplus, axis_Y);
			m_3dscreen.TurnMatrix(m_xTplus, axis_X);
		}
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(cadur);
	if(m_buttonId >= 0 && m_buttonId <= 6)
		m_3dscreen.Translate3Dto2D(FALSE);
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(egulGadol);
	if(m_buttonId >= 4 && m_buttonId <= 6)
		m_3dscreen.Translate3Dto2D(FALSE);
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(egulHakuk);
	if(m_buttonId >= 0 && m_buttonId <= 6)
	{
		double vec = cos(m_xTurn * D);
		double half = (double)trszArez / 2 + 1;
		double shiftY = sin(m_xTurn * D) * half;
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		//m_3dscreen.FillRect(0,0,(int)m_stepsKav + 1, 3, 0
		//	,fr_shrink , vec);
		m_3dscreen.ShiftObjectCenter(shiftY, axis_Y);
		m_3dscreen.TurnObjectCenter(xTurnStart, axis_X);
		//m_3dscreen.TurnShape(yTurnStart, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(yTurnStart, axis_Y);
		m_3dscreen.TurnMatrix(vec, axis_S);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(kotevEl);
	if(m_buttonId >= 2 && m_buttonId <= 6 && m_xTurn >=0)
		m_3dscreen.Translate3Dto2D(FALSE);
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kotevTch);
	if(m_buttonId >= 2 && m_buttonId <= 6 && m_xTurn < 0)
		m_3dscreen.Translate3Dto2D(FALSE);
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekudaNochachat);
	if(m_buttonId >= 3 && m_buttonId <= 6)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(-m_xTurn + xTurnStart, axis_X);
		m_3dscreen.TurnObjectCenter(yTurnStart, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(mekomMedina);
	if(m_buttonId >= 8)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(-m_xTurn + xTurnStart, axis_X);
		m_3dscreen.TurnObjectCenter(yTurnStart, axis_Y);
		if(m_bLbDown)
		{
			m_3dscreen.TurnObjectCenter(m_yTplus, axis_Y);
			m_3dscreen.TurnObjectCenter(m_xTplus, axis_X);
		}
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekudatRosh);
	if(m_buttonId >= 16)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(-m_xTurn + xTurnStart, axis_X);
		m_3dscreen.TurnObjectCenter(yTurnStart, axis_Y);
		if(m_bLbDown)
		{
			m_3dscreen.TurnObjectCenter(m_yTplus, axis_Y);
			m_3dscreen.TurnObjectCenter(m_xTplus, axis_X);
		}
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(zavitYeshara);
	if(m_buttonId >= 5 && m_buttonId <= 6)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.InitMatrix();
		if(m_xTurn < 0)
			m_3dscreen.TurnMatrix(90, axis_Z);
			//m_3dscreen.TurnShape(90, axis_Z, false);
		m_3dscreen.TurnObjectCenter(xTurnStart, axis_X);
		//m_3dscreen.TurnShape(xTurnStart, axis_X, false);
		m_3dscreen.TurnObjectCenter(yTurnStart, axis_Y);
		//m_3dscreen.TurnShape(yTurnStart, axis_Y, !m_bLbDown);
		m_3dscreen.TurnMatrix(xTurnStart, axis_X);
		m_3dscreen.TurnMatrix(yTurnStart, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(rochavMevukash);
	if(m_buttonId == 6)
	{
		double step = m_stepsRochavMevukash / 360;
		int steps = (int)fabs(step * m_xTurn);
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();
		m_3dscreen.InitMatrix();
		if(m_xTurn < 0)
			m_3dscreen.TurnMatrix(180, axis_Z);
		//	m_3dscreen.TurnShape(180, axis_Z, false);
		//m_3dscreen.TurnShape(xTurnStart, axis_X, false);
		//m_3dscreen.TurnShape(yTurnStart, axis_Y, !m_bLbDown);
		m_3dscreen.TurnMatrix(xTurnStart, axis_X);
		m_3dscreen.TurnMatrix(yTurnStart, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D(TRUE, 0 , steps);
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(rochavMedina);
	if(m_buttonId >= 13)
	{
		double step = m_stepsRochavMevukash / 360;
		int steps = (int)fabs(step * m_xTurn);
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();
		m_3dscreen.InitMatrix();
		if(m_xTurn < 0)
			m_3dscreen.TurnMatrix(180, axis_Z);
		//	m_3dscreen.TurnShape(180, axis_Z, false);
		//m_3dscreen.TurnShape(xTurnStart, axis_X, false);
		//m_3dscreen.TurnShape(yTurnStart, axis_Y, !m_bLbDown);
		m_3dscreen.TurnMatrix(xTurnStart, axis_X);
		m_3dscreen.TurnMatrix(yTurnStart, axis_Y);
		if(m_bLbDown)
		{
			//m_3dscreen.TurnShape(m_yTplus, axis_Y, false);
			//m_3dscreen.TurnShape(m_xTplus, axis_X);
			m_3dscreen.TurnMatrix(m_yTplus, axis_Y);
			m_3dscreen.TurnMatrix(m_xTplus, axis_X);
		}
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D(TRUE, 0 , steps);
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(rochavMeNekudatRosh);
	if(m_buttonId == 18)
	{
		double step = m_stepsTrszP2 / 360;
		int steps = (int)fabs(step * m_xTurn);
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();
		m_3dscreen.InitMatrix();
		if(m_xTurn < 0)
			m_3dscreen.TurnMatrix(180, axis_Z);
		//	m_3dscreen.TurnShape(180, axis_Z, false);
		//m_3dscreen.TurnShape(xTurnStart, axis_X, false);
		//m_3dscreen.TurnShape(yTurnStart, axis_Y, !m_bLbDown);
		m_3dscreen.TurnMatrix(xTurnStart, axis_X);
		m_3dscreen.TurnMatrix(yTurnStart, axis_Y);
		if(m_bLbDown)
		{
			//m_3dscreen.TurnShape(m_yTplus, axis_Y, false);
			//m_3dscreen.TurnShape(m_xTplus, axis_X);
			m_3dscreen.TurnMatrix(m_yTplus, axis_Y);
			m_3dscreen.TurnMatrix(m_xTplus, axis_X);
		}
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D(TRUE, 0 , steps);
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}


	m_3dscreen.BeginObject(arez);
	if(m_buttonId > 6)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn + yTurnStart, axis_Y);
		m_3dscreen.TurnMatrix(xTurnStart, axis_X);
		if(m_bLbDown)
		{
			m_3dscreen.TurnMatrix(m_yTplus, axis_Y);
			m_3dscreen.TurnMatrix(m_xTplus, axis_X);
		}
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kavRohav);
	if(m_buttonId > 6)
	{
		double vec = cos(m_xTurn * D);
		double half = (double)trszArez / 2 + 1;
		double shiftY = sin(m_xTurn * D) * half;
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		//m_3dscreen.FillRect(0,0,(int)m_stepsKav + 1, 3, 0
		//	,fr_shrink , vec);
		m_3dscreen.ShiftObjectCenter(shiftY, axis_Y);
		m_3dscreen.TurnObjectCenter(xTurnStart, axis_X);
		m_3dscreen.InitMatrix();
		//m_3dscreen.TurnShape(yTurnStart, axis_Y, !m_bLbDown);
		m_3dscreen.TurnMatrix(yTurnStart, axis_Y);
		if(m_bLbDown)
		{
			m_3dscreen.TurnObjectCenter(m_yTplus, axis_Y);
			m_3dscreen.TurnObjectCenter(m_xTplus, axis_X);
			//m_3dscreen.TurnShape(m_yTplus, axis_Y, false);
			//m_3dscreen.TurnShape(m_xTplus, axis_X);
			m_3dscreen.TurnMatrix(m_yTplus, axis_Y);
			m_3dscreen.TurnMatrix(m_xTplus, axis_X);
		}
		m_3dscreen.TurnMatrix(vec, axis_S);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kotevZ);
	if(m_buttonId >= 10 && m_xTurn >=0)
	{
		if(m_bLbDown)
		{
			//m_3dscreen.ResetTranslation();
			m_3dscreen.ResetShift();
			m_3dscreen.TurnObjectCenter(m_yTplus, axis_Y);
			m_3dscreen.TurnObjectCenter(m_xTplus, axis_X);
			m_3dscreen.TurnShape(0.0, axis_X);
			m_3dscreen.Translate3Dto2D();
		}
		else
			m_3dscreen.Translate3Dto2D(FALSE);
	}
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kotevD);
	if(m_buttonId >= 10 && m_xTurn < 0)
	{
		if(m_bLbDown)
		{
			//m_3dscreen.ResetTranslation();
			m_3dscreen.ResetShift();
			m_3dscreen.TurnObjectCenter(m_yTplus, axis_Y);
			m_3dscreen.TurnObjectCenter(m_xTplus, axis_X);
			m_3dscreen.TurnShape(0.0, axis_X);
			m_3dscreen.Translate3Dto2D();
		}
		else
			m_3dscreen.Translate3Dto2D(FALSE);
	}
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kotevOlamZ);
	if(m_buttonId >= 15 && m_xTurn >=0)
	{
		if(m_bLbDown)
		{
			//m_3dscreen.ResetTranslation();
			m_3dscreen.ResetShift();
			m_3dscreen.TurnObjectCenter(m_yTplus, axis_Y);
			m_3dscreen.TurnObjectCenter(m_xTplus, axis_X);
			m_3dscreen.TurnShape(0.0, axis_X);
			m_3dscreen.Translate3Dto2D();
		}
		else
			m_3dscreen.Translate3Dto2D(FALSE);
	}
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kotevOlamD);
	if(m_buttonId >= 15 && m_xTurn < 0)
	{
		if(m_bLbDown)
		{
			//m_3dscreen.ResetTranslation();
			m_3dscreen.ResetShift();
			m_3dscreen.TurnObjectCenter(m_yTplus, axis_Y);
			m_3dscreen.TurnObjectCenter(m_xTplus, axis_X);
			m_3dscreen.TurnShape(0.0, axis_X);
			m_3dscreen.Translate3Dto2D();
		}
		else
			m_3dscreen.Translate3Dto2D(FALSE);
	}
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kavHaShave);
	if(m_buttonId >= 11)
	{
		if(m_bLbDown)
		{
			//m_3dscreen.ResetTranslation();
			//m_3dscreen.ResetShift();
			//m_3dscreen.TurnShape(m_yTplus, axis_Y, false);
			//m_3dscreen.TurnShape(m_xTplus, axis_X);
			m_3dscreen.InitMatrix();
			m_3dscreen.TurnMatrix(m_yTplus, axis_Y);
			m_3dscreen.TurnMatrix(m_xTplus, axis_X);
			m_3dscreen.Transform();
			m_3dscreen.Translate3Dto2D();
		}
		else
			m_3dscreen.Translate3Dto2D(FALSE);
	}
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(zavitYeshara2);
	if(m_buttonId >= 12)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.InitMatrix();
		if(m_xTurn < 0)
			//m_3dscreen.TurnShape(90, axis_Z, false);
			m_3dscreen.TurnMatrix(90, axis_Z);
		m_3dscreen.TurnObjectCenter(xTurnStart, axis_X);
		//m_3dscreen.TurnShape(xTurnStart, axis_X, false);
		m_3dscreen.TurnMatrix(xTurnStart, axis_X);
		m_3dscreen.TurnObjectCenter(yTurnStart, axis_Y);
		//m_3dscreen.TurnShape(yTurnStart, axis_Y, !m_bLbDown);
		m_3dscreen.TurnMatrix(yTurnStart, axis_Y);
		if(m_bLbDown)
		{
			m_3dscreen.TurnObjectCenter(m_yTplus, axis_Y);
			//m_3dscreen.TurnShape(m_yTplus, axis_Y, false);
			m_3dscreen.TurnMatrix(m_yTplus, axis_Y);
			m_3dscreen.TurnObjectCenter(m_xTplus, axis_X);
			//m_3dscreen.TurnShape(m_xTplus, axis_X);
			m_3dscreen.TurnMatrix(m_xTplus, axis_X);
		}
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(shetachgalgalHaShave);
	if(m_buttonId >= 17)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn + yTurnStart, axis_Y);
		m_3dscreen.TurnMatrix(xTurnStart, axis_X);
		if(m_bLbDown)
		{
			m_3dscreen.TurnMatrix(m_yTplus, axis_Y);
			m_3dscreen.TurnMatrix(m_xTplus, axis_X);
		}
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(galgalHaShave);
	if(m_buttonId >= 17)
	{
		if(m_bLbDown)
		{
			//m_3dscreen.ResetTranslation();
			//m_3dscreen.ResetShift();
			//m_3dscreen.TurnShape(m_yTplus, axis_Y, false);
			//m_3dscreen.TurnShape(m_xTplus, axis_X);
			m_3dscreen.InitMatrix();
			m_3dscreen.TurnMatrix(m_yTplus, axis_Y);
			m_3dscreen.TurnMatrix(m_xTplus, axis_X);
			m_3dscreen.Transform();
			m_3dscreen.Translate3Dto2D();
		}
		else
			m_3dscreen.Translate3Dto2D(FALSE);
	}
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	if(m_buttonId >= 16)
	{
		m_person.Reset();
		m_person.Shrink(0.5);
		if(m_xTurn < 0)
			m_person.Turn(180,axis_Y,false);
		m_person.Shift((double)trszArez / 2.0,axis_Y, false);
		m_person.Turn(xTurnStart + 90 - m_xTurn, axis_X,false);
		m_person.Turn(yTurnStart, axis_Y, !m_bLbDown);
		if(m_bLbDown)
		{
			m_person.Turn(m_yTplus, axis_Y, false);
			m_person.Turn(m_xTplus, axis_X);
		}
	}
	else
	{
		m_person.Hide();
	}

	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek21::OnMouseMove(UINT nFlags, CPoint point)
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
		m_xTurn = -cy / 3.0;

		if(m_xTurn > 90)
			m_xTurn = 90;
		else if(m_xTurn < -90)
			m_xTurn = -90;

		m_yTurn = cx / 4.0;

		Do3DPaint();
	}
	else if(m_bLbDown)
	{
		double cx = (p.x - m_pt.x);
		double cy = (p.y - m_pt.y);
		m_xTplus = cy / 2.0;


		m_yTplus = cx / 2.0;

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek21::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_bLbDown = (m_buttonId >= 14)?true:false;

	if(m_bLbDown)
		m_3dscreen.ClearScreen();


	CPerek3DBase::OnRButtonDown(nFlags, point);
}

void CPerek21::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_bLbDown = false;
	m_xTplus = m_yTplus = 0.0;

	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(galgalHaShave);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kavHaShave);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotevOlamD);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotevOlamZ);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotevD);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotevZ);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.ClearScreen();
	m_3dscreen.TrigerPaintAlow();


	CPerek3DBase::OnRButtonUp(nFlags, point);
}

void CPerek21::InitOnSubHeadButton(void)
{
	BITMAP bm;
	m_3dscreen.m_refreshDC.GetBitmap(&bm);
	CDC *pRefreshDC = m_3dscreen.m_refreshDC.operator CDC *();
	CRect rcR(bm.bmWidth - 290, 
		bm.bmHeight - 40, bm.bmWidth, bm.bmHeight);
	pRefreshDC->FillSolidRect(rcR,0);

	if(m_buttonId >= 14)
	{
		CFont font;
		VERIFY(font.CreateFont(
			-24,                     // nHeight
			0,                       // nWidth
			0,                       // nEscapement
			0,                       // nOrientation
			FW_SEMIBOLD,               // nWeight
			FALSE,                   // bItalic
			FALSE,                   // bUnderline
			0,                       // cStrikeOut
			HEBREW_CHARSET,          // nCharSet
			OUT_CHARACTER_PRECIS,      // nOutPrecision
			CLIP_CHARACTER_PRECIS,     // nClipPrecision
			PROOF_QUALITY,         // nQuality
			DEFAULT_PITCH | FF_SWISS,// nPitchAndFamily
			"Guttman Miryam Bold"));        // lpszFacename

		CString sTxt = "לחיצה ימנית ושמאלית";
		int n = pRefreshDC->SaveDC();
		COLORREF txtcolor = pRefreshDC->SetTextColor(RGB(0,0,255));
		pRefreshDC->SetBkMode(TRANSPARENT);
		CFont* pFont = pRefreshDC->SelectObject(&font);
		pRefreshDC->DrawText(sTxt, rcR, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);
		pRefreshDC->SelectObject(pFont);
		pRefreshDC->RestoreDC(n);
	}
	m_3dscreen.CopyRefresh(rcR);
	m_3dscreen.OnPaint();
}
