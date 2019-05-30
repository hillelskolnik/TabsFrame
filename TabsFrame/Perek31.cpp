// Perek31.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek31.h"


// CPerek31

IMPLEMENT_DYNCREATE(CPerek31, CPerek3DBase)

CPerek31::CPerek31()
: lasty(1000000)
, m_bRightBDown(false)
//, m_sliderRc(3,0,120, ipHeight)
, m_sliderHorRc(120, ipHeight - 80,ipWidth,ipHeight)
, m_xTurn2(0)
, m_xTurn3(0)
, m_xStart(-20.0)
, m_yStart(98.0)
, trsz(356)
, trszArez(50)
, trszSteps(0)
, ofanHaziHaYomCol(RGB(106,0,106))
, mashveHaYomCol(RGB(26,108,99))
, galgalMazalotCol(RGB(255,0,128))
, stepsArez(0)
, m_slider(this,CRect(3,0,120, ipHeight), CSlider::VerCaptionResultMazalot)
{
	trszSteps = DiameterSteps(trsz);
	stepsArez = DiameterSteps(trszArez);
	m_IDstart = ID_P31_1;
	m_IDidx = WT_PEREK_31;
	m_IDX_PEREK = IDX_PEREK_31;
}

CPerek31::~CPerek31()
{
}

BEGIN_MESSAGE_MAP(CPerek31, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P31_1, ID_P31_2, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P31_1, ID_P31_2, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// CPerek31 diagnostics

#ifdef _DEBUG
void CPerek31::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek31::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


enum
{
	halal
	,arez
	,ofanHaziHaYom
	,mashveHaYom
	,galgalMazalot

	,shemesh
	,hezKivunMesibaShem1
	,hezKivunMesibaShem2

	,otiyotMazalot
};
// CPerek31 message handlers

int CPerek31::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_slider.SetDeflate(1,7,0,4);
	m_slider.SetCaption("מעלות המזל");
	m_slider.Init();

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
	m_memDc.CreateCompatibleDC(&dc);
	m_memBm.CreateCompatibleBitmap(&dc, ipWidth,ipHeight);
	m_memDc.SelectObject(&m_memBm);
	m_memDc.SelectObject(&m_font);


	COLORREF color0 = cp.paragraphs[0].color;

	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 25.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();
	m_3dscreen.NoPaint();


	int steps = DiameterSteps(trsz);
	m_3dscreen.BeginObject(halal);
	m_3dscreen.CreateSphereObject(trsz, RGBT(56,44,52, 0));
	m_3dscreen.FillRect(0,0,steps, steps/2, RGBT(0,0,0,0)
		,fr_zIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();
	m_3dscreen.ScreenToDC(TRUE);
	m_3dscreen.ClearScreen();
	m_3dscreen.DeleteObject(halal);

	m_3dscreen.BeginObject(arez);
	m_3dscreen.CreateSphereObject(trszArez, 0);
	m_3dscreen.BitmapToObject(bm11, RGBT2(0,0));
	m_3dscreen.TurnShape(-90.0, axis_Z, false,true);

	m_3dscreen.BeginObject(ofanHaziHaYom);
	m_3dscreen.CReateCircleLineObject(trsz, ofanHaziHaYomCol/*, m_fine*/);

	m_3dscreen.BeginObject(mashveHaYom);
	m_3dscreen.CReateCircleLineObject(trsz, mashveHaYomCol/*,m_fineMashve*/);
	m_3dscreen.TurnShape(90.0, axis_Z, false, true);

	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.CReateCircleLineObject(trsz, galgalMazalotCol/*,m_fineMashve*/);
	m_3dscreen.TurnShape(203.5 ,axis_X, false, true);


	CString sOtiyot = "טשתסאבםעקגדד";
	char cAlef = 'א';
	CImageList imageList;
	imageList.Create(IDB_BITMAP_OTIYUT,9,0,RGB(255,255,128));
	CMyFBitmap bmOtyut;
	bmOtyut.CreateMyCompatibleBitmap(NULL,9,14,0);

	double ang = 0;
	for(int i = otiyotMazalot; i < (otiyotMazalot + 12); ++i, ang+=30.0)
	{
		CDC *pDC = bmOtyut.GetMyPaintDC();
		int n = pDC->SaveDC();
		CBrush brOt(galgalMazalotCol);
		CBrush *obr = pDC->SelectObject(&brOt);

		m_3dscreen.BeginObject(i);
		m_3dscreen.CreatObjectPixselMap(9,14);
		imageList.Draw(pDC, sOtiyot[i-otiyotMazalot]-cAlef, CPoint(0,0), ILD_IMAGE);
		pDC->PatBlt(0,0,9,14,0X00A000C9);
		m_3dscreen.BitmapToObject(bmOtyut);
		m_3dscreen.ShiftObjectCenter((double)trsz /2.0 + 7.0, axis_Y, true);

		m_3dscreen.TurnObjectCenter(3.5, axis_X, true);
		m_3dscreen.TurnObjectCenter(-ang, axis_Z, true);
		m_3dscreen.TurnObjectCenter(23.5, axis_Y, true);


		pDC->SelectObject(obr);
		pDC->RestoreDC(n);
	}

	int kotTrsz = DiameterSteps(9);
	m_3dscreen.BeginObject(hezKivunMesibaShem1);
	m_3dscreen.CreateCylinderObject(9,1,32, ColDev(galgalMazalotCol, 2));
	m_3dscreen.FillRect(0,0,kotTrsz, 32, ColBright(galgalMazalotCol, 0.6)
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2.0,axis_Y, true);
	m_3dscreen.TurnShape(90,axis_Z, false, true);

	m_3dscreen.BeginObject(hezKivunMesibaShem2);
	m_3dscreen.CreateCylinderObject(9,1,32, ColDev(galgalMazalotCol, 2));
	m_3dscreen.FillRect(0,0,kotTrsz, 32, ColBright(galgalMazalotCol, 0.6)
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2.0,axis_Y, true);
	m_3dscreen.TurnShape(90,axis_Z, false, true);

	int sShemesh = 17;
	int stepsShem = DiameterSteps(sShemesh);
	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(128,0,0, 0));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(255,128,0,0)
		,fr_zIntensity , (double)sShemesh / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(
		(double)trsz / 2.0,axis_Y, true);




	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek31::Do3DPaint(void)
{
	if(m_bPastCreate == false || m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	CFillRectData data2;
	data2.vec = 0.4;
	data2.radius = (double)trsz/2.0;


	m_3dscreen.BeginObject(arez);

	m_3dscreen.ResetTranslation();

		double sinNetiya = SinNetyatAliyaYeshara(m_xTurn, 23.5);
		double angNetiya = asin(sinNetiya) * ToD;

		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnLightPt(0,axis_X, true);
		m_3dscreen.TurnLightPt(270.0,axis_X);
		m_3dscreen.TurnLightPt(angNetiya,axis_Z);
		//m_3dscreen.TurnLightPt(m_xTurn2,axis_X);

	m_3dscreen.TurnShape(m_xTurn2, axis_X, false);

		CFillRectData data;
		data.radius = (double)trszArez / 2.0;
		data.vec2 = 0.4;
		m_3dscreen.FillRect(0,0,stepsArez,stepsArez/2, RGB(24,24,24), 
			fr_lightOppositeDirection, data);

	m_3dscreen.TurnShape(m_xTurn3, axis_X, false);
	m_3dscreen.TurnShape(m_yTurn + 90, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(ofanHaziHaYom);
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(m_xTurn3, axis_X, false);
	m_3dscreen.TurnShape(m_yTurn + 90, axis_Y, false);
	m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data2);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	double xTurn = -m_xTurn;
	while(xTurn > 360)
		xTurn -= 360;
	while(xTurn < 0)
		xTurn += 360;

	m_3dscreen.BeginObject(mashveHaYom);
	{

		double xTurnt = AliyaYeshara(xTurn,23.5);
		int x3Steps = (int)(((double)trszSteps / 360.0) * xTurnt);

		m_3dscreen.ResetTranslation();
		m_3dscreen.FillRect(0,0,x3Steps,3, ColBright(mashveHaYomCol, 0.7),fr_paintTranslated);
		m_3dscreen.TurnShape(-m_xTurn3, axis_Z, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data2);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(galgalMazalot);
	{

		int x3Steps = (int)(((double)trszSteps / 360.0) * xTurn);

		double ay = AliyaYeshara(xTurn, 23.5);
		m_3dscreen.ResetTranslation();
		m_3dscreen.FillRect(0,0,x3Steps,3, ColBright(galgalMazalotCol, 0.75),fr_paintTranslated);

		m_3dscreen.TurnShape(ay - m_xTurn3 + 90.0, axis_Z, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data2);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}


	double ayOt = AliyaYeshara(xTurn, 23.5);
	for(int i = otiyotMazalot; i < (otiyotMazalot + 12); ++i)
	{
		m_3dscreen.BeginObject(i);

		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();

		m_3dscreen.TurnObjectCenter(ayOt - m_xTurn3, axis_Z);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(hezKivunMesibaShem1);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(-xTurn - 270, axis_Z);
	m_3dscreen.TurnShape(-xTurn - 270, axis_Z, false);
	m_3dscreen.TurnObjectCenter(23.5, axis_Y);
	m_3dscreen.TurnShape(23.5, axis_Y, false);
	m_3dscreen.TurnObjectCenter(ayOt - m_xTurn3, axis_Z);
	m_3dscreen.TurnShape(ayOt - m_xTurn3, axis_Z, false);
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	m_3dscreen.TurnShape(m_yTurn, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(hezKivunMesibaShem2);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(-xTurn - 90, axis_Z);
	m_3dscreen.TurnShape(-xTurn - 90, axis_Z, false);
	m_3dscreen.TurnObjectCenter(23.5, axis_Y);
	m_3dscreen.TurnShape(23.5, axis_Y, false);
	m_3dscreen.TurnObjectCenter(ayOt - m_xTurn3, axis_Z);
	m_3dscreen.TurnShape(ayOt - m_xTurn3, axis_Z, false);
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	m_3dscreen.TurnShape(m_yTurn, axis_Y);
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(-xTurn, axis_Z);
	m_3dscreen.TurnObjectCenter(23.5, axis_Y);
	m_3dscreen.TurnObjectCenter(ayOt - m_xTurn3, axis_Z);
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	PaintResult();
	lasty = m_yTurn;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek31::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = (p.x > 3)?TRUE:FALSE;


	if((m_bBntDown || m_bRightBDown) && m_bHandCursor )
	{
		double cx = (p.x - m_pt.x);
		double cy = (p.y - m_pt.y);

		if(m_slider.PtInRect(p, m_xTurn))
		{
			m_xTurn = -m_xTurn ;
		}
		else if(m_sliderHorRc.PtInRect(p))
		{
			m_yTurn = cx /2.5;
			m_yTurn += m_yStart;
		}
		else if(m_bRightBDown)
		{
			m_xTurn2 = cy ;
		}
		else
		{
			m_xTurn3 = cy / 2.0 + m_xStart;
		}

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek31::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_bRightBDown = true;

	CPerek3DBase::OnRButtonDown(nFlags, point);
}

void CPerek31::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_bRightBDown = false;

	CPerek3DBase::OnRButtonUp(nFlags, point);
}

void CPerek31::InitOnSubHeadButton(void)
{
	lasty = 1000000;

	m_yTurn = m_yStart;
	//m_xTurn = 0;
	m_xTurn2 = 0;
	m_xTurn3 = m_xStart;

	PaintSlider();
}

void CPerek31::PaintSlider(void)
{
	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];
	COLORREF color = cp.paragraphs[m_buttonId].color;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	CRect rc2 = m_sliderHorRc;
	int n = m_memDc.SaveDC();
	m_memDc.FillSolidRect(rc2,0);

	{
		int top = 440;
		int left = 150;

		int rieght = 0;
		int rch = 30;
		int width = left - rieght;
		CRect rcTemp(ipWidth-left, top, ipWidth- rieght, top + rch);
		CPoint pd(0,rch);

		CFont fontTemp;
			VERIFY(fontTemp.CreateFont(
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

		CString sTxt = "אופן חצי היום";
		COLORREF txtcolor = m_memDc.SetTextColor(ofanHaziHaYomCol);
		m_memDc.SetBkMode(TRANSPARENT);
		CFont* pFont = m_memDc.SelectObject(&fontTemp);
		m_memDc.DrawText(sTxt, rcTemp, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);

		rcTemp += pd;
		sTxt = "משוה היום";
		m_memDc.SetTextColor(mashveHaYomCol);
		m_memDc.DrawText(sTxt, rcTemp, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);

		rcTemp += pd;
		sTxt = "גלגל המזלות";
		m_memDc.SetTextColor(galgalMazalotCol);
		m_memDc.DrawText(sTxt, rcTemp, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);


		dc.BitBlt(ipWidth-left, top, rcTemp.Width(), rcTemp.bottom - top, 
			&m_memDc,ipWidth-left,top,SRCCOPY);

		m_memDc.SelectObject(pFont);
		m_memDc.SetTextColor(txtcolor);
	}


	CBrush br(color);

	rc2.DeflateRect(1,1,1,5);
	m_memDc.FrameRect(rc2, &br);

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
	COLORREF txtcolor = m_memDc.SetTextColor(RGB(0,0,255));
	m_memDc.SetBkMode(TRANSPARENT);
	CFont* pFont = m_memDc.SelectObject(&font);
	m_memDc.DrawText(sTxt, rc2, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);
	m_memDc.SelectObject(pFont);
	m_memDc.SetTextColor(txtcolor);


	m_slider.InitOnSubHeadButton();

	dc.BitBlt(m_sliderHorRc.left,
		m_sliderHorRc.top,m_sliderHorRc.Width(),m_sliderHorRc.Height(),
		&m_memDc,m_sliderHorRc.left,m_sliderHorRc.top,SRCCOPY);

	m_memDc.RestoreDC(n);
}

BOOL CPerek31::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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

void CPerek31::PaintResult(void)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);

	int n = m_memDc.SaveDC();
	CRect rc(ipWidth - 150,130, ipWidth,240);
	m_memDc.FillSolidRect(rc,0);

	CRect rc3(ipWidth - 150,310, ipWidth,370);
	m_memDc.FillSolidRect(rc3,0);

	static CFont font;
	if(font.operator HFONT() == NULL)
		VERIFY(font.CreateFont(
			-20,                     // nHeight
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


	{
		double xTurn3 = -m_xTurn;
		while(xTurn3 > 360)
			xTurn3 -= 360;
		while(xTurn3 < 0)
			xTurn3 += 360;

		double t3 = floor(xTurn3);
		t3 = (xTurn3 - t3) * 60;
		xTurn3 = floor(xTurn3);

		static const double sdAng = 0.985647222222222;

		double ayMin = 0;
		double ayMax = 0;

		if(m_buttonId == 0)
		{
			ayMin = AliyaYeshara(xTurn3 - sdAng*0.5,23.5);
			ayMax = AliyaYeshara(xTurn3 + sdAng*0.5,23.5);
		}
		else
		{
			const double govaShemesh = 99.390833333333333333333333333333;
			ayMin = AliyaYeshara(ShemesAmity(xTurn3 - sdAng*0.5, govaShemesh),23.5);
			ayMax = AliyaYeshara(ShemesAmity(xTurn3 + sdAng*0.5, govaShemesh),23.5);
		}

		if(ayMin > ayMax)
			ayMax += 360.0;
		double result = ayMax - ayMin;
		result -= 1.0;
		result *= 60.0;

		static double sunday = 360.0/365.25;
		static double middleday = 360.0 + sunday;
		static double seconndsday = 24*3600;
		static double secondsDeg = seconndsday / middleday;

		double secondsReal = secondsDeg * (middleday + result/60);
		double hours = floor(secondsReal / 3600);
		secondsReal -= hours * 3600;
		double minuts = floor(secondsReal / 60);
		secondsReal -= minuts * 60;

		if(secondsReal > 59.95)
		{
			minuts++;
			secondsReal = 0;
		}

		if(minuts == 60.0)
		{
			hours++;
			minuts = 0;
		}

		CString sMinuts = (minuts < 10.0)?"0":"";
		CString sSeconds = (secondsReal < 10.0)?"0":"";

		m_memDc.SetBkMode(TRANSPARENT);
		CFont* pFont = m_memDc.SelectObject(&font);
		COLORREF txtcolor = m_memDc.SetTextColor(ColBright(mashveHaYomCol, 0.7));


		CString sTxt;
		sTxt.Format("%s\n%2.1f\'", "תוספת או גראון עלית המשוה בחלקים",result);
		m_memDc.DrawText(sTxt, rc, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);

		sTxt.Format("%s\n%2.0f:%s%.0f:%s%.1f", "אורך היום",
			hours,sMinuts,minuts,sSeconds,secondsReal);
		/*txtcolor = */m_memDc.SetTextColor(ColBright(RGB(255,128,0), 0.2));
		m_memDc.DrawText(sTxt, rc3, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);

		m_memDc.SetTextColor(txtcolor);
		m_memDc.SelectObject(pFont);
	}

	dc.BitBlt(rc.left,
		rc.top,rc.Width(),rc.Height(),
		&m_memDc,rc.left,rc.top,SRCCOPY);

	dc.BitBlt(rc3.left,
		rc3.top,rc3.Width(),rc3.Height(),
		&m_memDc,rc3.left,rc3.top,SRCCOPY);


	m_memDc.RestoreDC(n);
}

