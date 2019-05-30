// Perek33.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek33.h"


// CPerek33

IMPLEMENT_DYNCREATE(CPerek33, CPerek3DBase)

CPerek33::CPerek33()
: m_xTurn2(0)
, m_slider(this, CRect(3,2,120, ipHeight),CSlider::VerMin90Plus90)
, m_sliderHorRc(120, ipHeight - 80,ipWidth,ipHeight)
, m_person(m_3dscreen)
, trsz(356)
, trszArez(50)
, trszSteps(0)
, m_xStart(8.5)
, m_yStart(6)
, color1(0)
{
	trszSteps = DiameterSteps(trsz);
	m_IDstart = ID_P33_1;
	m_IDidx = WT_PEREK_33;
	m_IDX_PEREK = IDX_PEREK_33;
}

CPerek33::~CPerek33()
{
}

BEGIN_MESSAGE_MAP(CPerek33, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P33_1, ID_P33_2, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P33_1, ID_P33_2, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CPerek33 diagnostics

#ifdef _DEBUG
void CPerek33::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek33::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek33 message handlers

enum
{
	ofek
	,arez
	,ofekcir
	,kotevZafon
	,kotevDaron
	,kavSave
	,galgalMashve
	,ofanHaziHaYom
	,nekudatRosh

	,zafon

	,kavimArez
};


int CPerek33::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_slider.SetDeflate(0,7,0,4);
	m_slider.SetCaption("רוחב המדינה");
	m_slider.Init();

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];

	CMyFBitmap bm11;
	CString path = theApp.m_appPath + "Images\\Earth.bmp";
	CImage image22;
	image22.Load(path);
	bm11.CreateMyCompatibleBitmap(NULL, image22.GetWidth(),
		image22.GetHeight());
	image22.BitBlt(bm11.operator CDC *()->GetSafeHdc(),
		CPoint(0,0));


	CClientDC dc(this);
	m_memDc.CreateCompatibleDC(&dc);
	m_memBm.CreateCompatibleBitmap(&dc, ipWidth,ipHeight);
	m_memDc.SelectObject(&m_memBm);
	m_memDc.SelectObject(&m_font);


	COLORREF color0 = cp.paragraphs[0].color;
	color1 = cp.paragraphs[1].color;

	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 25.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();


	m_3dscreen.BeginObject(ofek);
	m_3dscreen.CreatObjectPixselMap(trsz,trsz);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm1.GetMyPaintDC();
		CPen pen1(PS_SOLID,1,(COLORREF)0);
		CBrush br1(RGB(255,255,96)/*color3*/);
		pdc->SelectObject(&pen1);
		pdc->SelectObject(&br1);
		CRect rc(0,0,trsz,trsz);
		pdc->FillSolidRect(CRect(0,0,trsz, trsz),0);
		pdc->Ellipse(rc);
		m_3dscreen.BitmapToObject(bm1, RGBT2(0,50));
	}
	m_3dscreen.FillRect(0,0,trsz, trsz, RGBT(96,48,0,70)
		,fr_xyIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.TurnShape(90.0 + m_xStart, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(ofekcir);
	m_3dscreen.CReateCircleLineObject(trsz-1, RGB(255,255,255));
	m_3dscreen.TurnShape(90.0 + m_xStart, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.BeginObject(arez);
	m_3dscreen.CreateSphereObject(trszArez, 0);
	m_3dscreen.BitmapToObject(bm11, RGBT2(0,0));
	m_3dscreen.TurnShape(-90.0, axis_X, false,true);
	m_3dscreen.ResetTranslation();

	COLORREF color3 = RGB(100,150,200);
	int kotTrsz = DiameterSteps(9);
	m_3dscreen.BeginObject(kotevZafon);
	m_3dscreen.CreateSphereObject(9, 
		ColBright(color3, -0.65));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color3,0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2.0, axis_Z, true);

	COLORREF color4 = RGB(128,48,100);
	m_3dscreen.BeginObject(kotevDaron);
	m_3dscreen.CreateSphereObject(9, 
		ColBright(color4, -0.65));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color4,0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz/2.0, axis_Z, true);

	COLORREF color5 = RGB(192,64,32);
	m_3dscreen.BeginObject(nekudatRosh);
	m_3dscreen.CreateSphereObject(9, 
		ColBright(color5, -0.65));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color5,0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2.0, axis_Y, true);

	m_3dscreen.BeginObject(kavSave);
	m_3dscreen.CReateCircleLineObject(trszArez + 1, RGBT(128,128,128,50));

	m_3dscreen.BeginObject(galgalMashve);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(192,64,128));

	m_3dscreen.BeginObject(ofanHaziHaYom);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(96,64,192));
	m_3dscreen.TurnShape(90.0, axis_Y, false, true);

	CreateText(zafon, "ץףונ", RGB(92,32,92));
	m_3dscreen.ShiftObjectCenter(
		(double)trsz / 2.0 + 20.0,axis_Z, true);


	m_person.Create();


	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek33::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(arez);
	//m_3dscreen.ResetTranslation();
	//m_3dscreen.TurnShape(m_xTurn2, axis_Z, false);
	//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
	//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
	//m_3dscreen.TurnShape(m_xStart, axis_X);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(m_xTurn2, axis_Z);
	m_3dscreen.TurnMatrix(m_xTurn, axis_X);
	m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
	m_3dscreen.TurnMatrix(m_xStart, axis_X);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kavSave);
	//m_3dscreen.ResetTranslation();
	//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
	//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
	//m_3dscreen.TurnShape(m_xStart, axis_X);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(m_xTurn, axis_X);
	m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
	m_3dscreen.TurnMatrix(m_xStart, axis_X);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();


	m_person.Reset();
	m_person.Shrink(0.2);
	m_person.Shift((double)trszArez / 2.0,axis_Y, false);
	m_person.Turn(m_yTurn + 180.0, axis_Y, false);
	m_person.Turn(m_xStart, axis_X);

	m_3dscreen.BeginObject(kotevZafon);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	m_3dscreen.TurnObjectCenter(m_xStart, axis_X);
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotevDaron);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	m_3dscreen.TurnObjectCenter(m_xStart, axis_X);
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	double plusy = (m_buttonId)? 0.0:7.0;
	m_3dscreen.BeginObject(zafon);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
	m_3dscreen.TurnObjectCenter(m_yTurn + plusy, axis_Y);
	m_3dscreen.TurnObjectCenter(m_xStart, axis_X);
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();



	m_3dscreen.BeginObject(nekudatRosh);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(m_xStart, axis_X);
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();


	CFillRectData data2;
	data2.vec = 0.4;
	data2.radius = (double)trsz/2.0;


	m_3dscreen.BeginObject(galgalMashve);
	m_3dscreen.ResetTranslation();
	//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
	//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
	//m_3dscreen.TurnShape(m_xStart, axis_X, false);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(m_xTurn, axis_X);
	m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
	m_3dscreen.TurnMatrix(m_xStart, axis_X);
	m_3dscreen.Transform(false);
	m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data2);
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(ofanHaziHaYom);
	if(m_buttonId == 0)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		m_3dscreen.TurnShape(m_xStart, axis_X, false);
		m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data2);
		m_3dscreen.TurnShape(0.0, axis_X);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.ResetTranslation();
		static const double oneStep = (double)trszSteps / 360.0;
		int stepsGova =  (int)(oneStep * m_xTurn);
		m_3dscreen.FillRect(0,0,stepsGova,3, color1, fr_paintTranslated);
		int start2 = (int)(oneStep * (m_xTurn + 90.0));
		int steps90minGova =  (int)(oneStep * (90.0 - m_xTurn));
		m_3dscreen.FillRect(start2,0,steps90minGova,3, color1, fr_paintTranslated);

		m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		m_3dscreen.TurnShape(m_xStart, axis_X, false);
		m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data2);
		m_3dscreen.TurnShape(0.0, axis_X);
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(ofekcir);
	m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(ofek);
	m_3dscreen.Translate3Dto2D(FALSE);

	PaintResult();
	//lasty = m_yTurn;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek33::PaintResult(void)
{
}

void CPerek33::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = (p.x > 3 && p.y > 1)?TRUE:FALSE;


	if( m_bBntDown && m_bHandCursor )
	{
		double cx = (p.x - m_pt.x);
		double cy = (p.y - m_pt.y);

		if(m_sliderHorRc.PtInRect(p))
		{
			m_yTurn = cx /2.5;
			m_yTurn += (m_buttonId == 0)?m_yStart: m_yStart + 95.0;
		}
		else if(m_slider.PtInRect(p, m_xTurn) == false)
		{
			m_xTurn2 = -cy ;
		}

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek33::PaintSlider(void)
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


	m_slider.InitOnSubHeadButton();

	dc.BitBlt(m_sliderHorRc.left,
		m_sliderHorRc.top,m_sliderHorRc.Width(),m_sliderHorRc.Height(),
		&m_memDc,m_sliderHorRc.left,m_sliderHorRc.top,SRCCOPY);

	m_memDc.RestoreDC(n);
}

void CPerek33::InitOnSubHeadButton(void)
{
	switch(m_buttonId)
	{
	case 0:
		m_yTurn = m_yStart;
		m_slider.SetRefPoint(middle);
		m_slider.SetMinMax(-90.0,90.0);
		break;
	case 1:
		m_yTurn = m_yStart + 95.0;
		m_slider.SetRefPoint(bottom);
		m_slider.SetMinMax(0.0,90.0);
		break;
	}

	m_xTurn = m_slider.SetVal(0);
	m_xTurn2 = 0;

	PaintSlider();
}

BOOL CPerek33::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_EXTRA_DRAW:
		PaintSlider();
		PaintResult();
		return TRUE;
	}

	return CPerek3DBase::OnWndMsg(message, wParam, lParam, pResult);
}
