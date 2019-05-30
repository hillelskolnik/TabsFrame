// Perek20.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek20.h"


// CPerek20
const int trszArez = 175;
const double fine = 2.0;
const int plus = 4;

IMPLEMENT_DYNCREATE(CPerek20, CPerek3DBase)

CPerek20::CPerek20()
: m_stepsKav(DiameterSteps(trszArez + plus, fine))
{
	m_IDstart = ID_P20_1;
	m_IDidx = WT_PEREK_20;
	m_IDX_PEREK = IDX_PEREK_20;
}

CPerek20::~CPerek20()
{
}

BEGIN_MESSAGE_MAP(CPerek20, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P20_1, ID_P20_4, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P20_1, ID_P20_4, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek20 drawing


// CPerek20 diagnostics

#ifdef _DEBUG
void CPerek20::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek20::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek20 message handlers

const int trsz = 356;
const double xTurnStart = 7.5;

enum
{
	halal
	,arez
	,kavHaShave
	,shetachgalgalHaShave
	,galgalHaShave
	,kotevZ
	,kotevD
	,kavRohav
};

int CPerek20::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();
	m_3dscreen.ScreenToDC(TRUE);
	m_3dscreen.ClearScreen();
	m_3dscreen.DeleteObject(halal);


	m_3dscreen.BeginObject(arez);
	m_3dscreen.CreateSphereObject(trszArez, RGBT2(color2, 95));
	m_3dscreen.BitmapToObject(bm11, RGBT2(0,0));
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kavHaShave);
	m_3dscreen.CReateCircleLineObject(trszArez+2, color1);
	m_3dscreen.TurnShape(90 + xTurnStart , axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kavRohav);
	m_3dscreen.CReateCircleLineObject(trszArez+plus, color3, fine);
	m_3dscreen.TurnShape(90 + xTurnStart, axis_X,false ,true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(galgalHaShave);
	m_3dscreen.CReateCircleLineObject(trsz, color0);
	m_3dscreen.TurnShape(90 + xTurnStart, axis_X);
	m_3dscreen.Translate3Dto2D();

	int kotTrsz = DiameterSteps(9);
	m_3dscreen.BeginObject(kotevZ);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color2, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color2
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(((double)trsz / 2.0), axis_Y, true);
	m_3dscreen.TurnObjectCenter(xTurnStart, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotevD);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color2, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color2
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-((double)trsz / 2.0), axis_Y, true);
	m_3dscreen.TurnObjectCenter(xTurnStart, axis_X, true);
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
		CPen pen1(PS_SOLID,4,(COLORREF)color0);
		CBrush br1((COLORREF)0);
		pdc->SelectObject(&pen1);
		pdc->SelectObject(&br1);
		CRect rc(0,0,trsz,trsz);
		pdc->FillSolidRect(CRect(0,0,trsz, trsz),0);
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
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek20::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(shetachgalgalHaShave);
	//m_3dscreen.ResetTranslation();
	//m_3dscreen.ResetShift();
	//m_3dscreen.TurnShape(m_yTurn, axis_Y,false);
	//m_3dscreen.TurnShape(xTurnStart, axis_X);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
	m_3dscreen.TurnMatrix(xTurnStart, axis_X);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(galgalHaShave);
	m_3dscreen.Translate3Dto2D(FALSE);


	m_3dscreen.BeginObject(arez);
	//m_3dscreen.ResetTranslation();
	//m_3dscreen.ResetShift();
	//m_3dscreen.TurnShape(m_yTurn, axis_Y,false);
	//m_3dscreen.TurnShape(xTurnStart, axis_X);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
	m_3dscreen.TurnMatrix(xTurnStart, axis_X);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kavHaShave);
	if(m_buttonId > 0)
		m_3dscreen.Translate3Dto2D(FALSE);
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kotevZ);
	if(m_buttonId > 1)
		m_3dscreen.Translate3Dto2D(FALSE);
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kotevD);
	if(m_buttonId > 1)
		m_3dscreen.Translate3Dto2D(FALSE);
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kavRohav);
	if(m_buttonId == 3)
	{
		double vec = cos(m_xTurn * D);
		double half = (double)trszArez / 2 + 2;
		double shiftY = sin(m_xTurn * D) * half;
//		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		//m_3dscreen.FillRect(0,0,m_stepsKav + 1, 3, 0
		//	,fr_shrink , vec);
		m_3dscreen.ShiftObjectCenter(shiftY, axis_Y);
		m_3dscreen.TurnObjectCenter(xTurnStart, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(vec, axis_S);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else 
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek20::OnMouseMove(UINT nFlags, CPoint point)
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

	CPerek3DBase::OnMouseMove(nFlags, point);
}
