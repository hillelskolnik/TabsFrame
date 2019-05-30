// Perek42.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek42.h"


// CPerek42

IMPLEMENT_DYNCREATE(CPerek42, CPerek3DBase)

CPerek42::CPerek42()
: m_xTurn2(0)
, m_sliderHor(this, CRect(120, ipHeight-85,ipWidth,ipHeight),CSlider::simpleHorizontal)
, m_slider(this, CRect(0, 0,120,ipHeight),CSlider::VerCaptionResultMazalot)
, lastx(0)
, m_xStart(24)
, m_yStart(5)
, trszArez(50)
, trsz(304)
, arezFine(1.0)
, arezSteps(0)
, trszSteps(0)
, m_tosefetOfek(0)
, angAliya(0)
, m_rcRes(ipWidth - 200, 250, ipWidth, 600)
, colOrechSkia(RGB(255,0,128))
, color0(0)
{
	arezSteps = DiameterSteps(trszArez, arezFine);
	trszSteps = DiameterSteps(trsz);
	m_IDstart = ID_P42_1;
	m_IDidx = WT_PEREK_42;
	m_IDX_PEREK = IDX_PEREK_42;
}

CPerek42::~CPerek42()
{
}

BEGIN_MESSAGE_MAP(CPerek42, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P42_1, ID_P42_1, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P42_1, ID_P42_1, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CPerek42 diagnostics

#ifdef _DEBUG
void CPerek42::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek42::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek42 message handlers
enum
{
	arez
	,ofek
	,mashveHaYom
	,galgalMazalot
	,nekudaZaf
	,nekudaDar
	,keshetKtavim
	,mesibatShemshYomi
	,zafon
	,darom
	,mizrach
	,maarav
	,eMavdil
};


int CPerek42::OnCreate(LPCREATESTRUCT lpCreateStruct)
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



	m_sliderHor.SetDeflate(3,3,3,3);
	m_sliderHor.Init();

	m_slider.SetDeflate(3,3,3,3);
	m_slider.SetCaption("מזל השוקע");
	m_slider.SetResultFormat("%.1f");
	m_slider.Init();

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];

	color0 = cp.paragraphs[0].color;

	CClientDC dc(this);
	m_memDc.CreateCompatibleDC(&dc);
	m_memBm.CreateCompatibleBitmap(&dc, ipWidth,ipHeight);
	m_memDc.SelectObject(&m_memBm);
	m_memDc.SelectObject(&m_font);


	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 25.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();
	m_3dscreen.NoPaint();

	m_3dscreen.BeginObject(arez);
	m_3dscreen.CreateSphereObject(trszArez, 0,360,90,-90,arezFine);
	m_3dscreen.BitmapToObject(bm11, RGBT2(0,0));
	m_3dscreen.TurnShape(145.0,axis_y, false,true);
	m_3dscreen.TurnShape(90.0,axis_z, false,true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(ofek);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(128,128,128));
	m_3dscreen.TurnShape(90.0, axis_x, false,true); 
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(mashveHaYom);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(0,0,160));
	m_3dscreen.TurnShape(90.0, axis_y,false,true);

	m_3dscreen.FillRect(0,0,trszSteps/2,3, colOrechSkia, 
		fr_paint);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(160,160,0));
	m_3dscreen.TurnShape(90.0, axis_y,false,true); 
	m_3dscreen.TurnShape(23.5, axis_Z,false,true); 

	m_3dscreen.BeginObject(keshetKtavim);
	m_3dscreen.CReateCircleLineObject(trsz, color0/*
		,1.0,180.0*/);
	m_3dscreen.TurnShape(90.0, axis_X,false,true); 

	COLORREF color5 = RGB(160, 128, 96);
	int kotTrsz = DiameterSteps(9);
	m_3dscreen.BeginObject(nekudaZaf);
	m_3dscreen.CreateSphereObject(9, 
		ColBright(color5, -0.65));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color5,0.35)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz/2.0, axis_X, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(nekudaDar);
	m_3dscreen.CreateSphereObject(9, 
		ColBright(color5, -0.65));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color5,0.35)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2.0, axis_X, true);
	m_3dscreen.ResetTranslation();

		m_3dscreen.BeginObject(eMavdil);
		m_3dscreen.CreatObjectPixselMap(trsz,trsz);
		CMyFBitmap bm;
		bm.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm.GetMyPaintDC();
		COLORREF col = ColBright(color0,0.65);//RGB(16,16,16);
		CPen pen(PS_SOLID,1,col);
		CBrush br(col);
		pdc->SelectObject(&pen);
		pdc->SelectObject(&br);
		pdc->Ellipse(0,0,trsz,trsz);
		m_3dscreen.BitmapToObject(bm, RGBT2(0,40));
		m_3dscreen.FillRect(0,0,trsz, trsz, RGBT2(ColBright(color0,-0.65),40)
			,fr_xyIntensity , (double)trsz / 2.0 - 0.5);
		m_3dscreen.TurnShape(90.0, axis_X,false,true); 
		m_3dscreen.ResetTranslation();


	CreateText(zafon, "ץףונ", RGB(92,32,92));
	m_3dscreen.ShiftObjectCenter(
		-(double)trsz / 2.0,axis_x, true);
	m_3dscreen.ResetTranslation();

	CreateText(darom, "דרומ", RGB(92,32,92));
	m_3dscreen.ShiftObjectCenter(
		(double)trsz / 2.0,axis_x, true);
	m_3dscreen.ResetTranslation();

	CreateText(maarav, "םערב", RGB(92,32,92));
	m_3dscreen.ShiftObjectCenter(
		-(double)trsz / 2.0-2.0,axis_z, true);
	m_3dscreen.ResetTranslation();



	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek42::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(arez);

		double sinNetiya = SinNetyatAliyaYeshara(m_xTurn, 23.5);
		double angNetiya = asin(sinNetiya) * ToD;
		angAliya = AliyaYeshara(m_xTurn, 23.5);
		double sAliya = 
			SinNetyatAliyaYeshara(m_xTurn, 23.5);
		double kizuz = kizuzNetiyaLaOfek(32.0,sAliya);



	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(-32, axis_Z);
	m_3dscreen.TurnMatrix(m_xTurn2 + m_xStart, axis_X);
	m_3dscreen.TurnMatrix(m_yTurn + m_yStart, axis_Y);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	CFillRectData data2;
	data2.vec = 0.65;
	data2.radius = (double)trsz/2.0;


	m_3dscreen.BeginObject(ofek);
	m_3dscreen.ResetTranslation();
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(m_xTurn2 + m_xStart, axis_X);
	m_3dscreen.TurnMatrix(m_yTurn + m_yStart, axis_Y);
	m_3dscreen.Transform(false);
	m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data2);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(mashveHaYom);
	{
		m_tosefetOfek = kizuz;
		if(m_tosefetOfek > 180.0)
			m_tosefetOfek -= 360.0;

		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(kizuz, axis_X);
		m_3dscreen.TurnMatrix(-32, axis_Z);
		m_3dscreen.TurnMatrix(m_xTurn2 + m_xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn + m_yStart, axis_Y);
		m_3dscreen.Transform();
	}
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.ResetTranslation();
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(angAliya + kizuz, axis_X);
	m_3dscreen.TurnMatrix(-32, axis_Z);
	m_3dscreen.TurnMatrix(m_xTurn2 + m_xStart, axis_X);
	m_3dscreen.TurnMatrix(m_yTurn + m_yStart, axis_Y);
	m_3dscreen.Transform(false);
	m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data2);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(keshetKtavim);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(kizuz, axis_X);
	m_3dscreen.TurnMatrix(-32, axis_Z);
	m_3dscreen.TurnMatrix(m_xTurn2 + m_xStart, axis_X);
	m_3dscreen.TurnMatrix(m_yTurn + m_yStart, axis_Y);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(nekudaZaf);
	m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(-32.0,axis_Z);
		m_3dscreen.TurnObjectCenter(m_xTurn2 + m_xStart, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn + m_yStart, axis_Y);
	m_3dscreen.TurnShape(0.0,axis_x);
	m_3dscreen.Translate3Dto2D();
	
	m_3dscreen.BeginObject(nekudaDar);
	m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(-32.0,axis_Z);
		m_3dscreen.TurnObjectCenter(m_xTurn2 + m_xStart, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn + m_yStart, axis_Y);
	m_3dscreen.TurnShape(0.0,axis_x);
	m_3dscreen.Translate3Dto2D();
	
	m_3dscreen.BeginObject(zafon);
	m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(-36.0,axis_Z);
		m_3dscreen.TurnObjectCenter(m_xTurn2 + m_xStart, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn + m_yStart, axis_Y);
	m_3dscreen.TurnShape(0.0,axis_x);
	m_3dscreen.Translate3Dto2D();
	
	m_3dscreen.BeginObject(darom);
	m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(-28.0,axis_Z);
		m_3dscreen.TurnObjectCenter(m_xTurn2 + m_xStart, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn + m_yStart, axis_Y);
	m_3dscreen.TurnShape(0.0,axis_x);
	m_3dscreen.Translate3Dto2D();
	
	m_3dscreen.BeginObject(maarav);
	m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn2 + m_xStart + 10, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn + m_yStart+ 7, axis_Y);
	m_3dscreen.TurnShape(0.0,axis_x);
	m_3dscreen.Translate3Dto2D();
	
	m_3dscreen.BeginObject(eMavdil);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(kizuz, axis_X);
	m_3dscreen.TurnMatrix(-32, axis_Z);
	m_3dscreen.TurnMatrix(m_xTurn2 + m_xStart, axis_X);
	m_3dscreen.TurnMatrix(m_yTurn + m_yStart, axis_Y);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();


	if(lastx != m_xTurn)
		PaintResult();

	lastx = m_xTurn;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek42::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = (p.x > 3 && p.y > 1 && p.x < ipWidth)?TRUE:FALSE;

	if( m_bBntDown && m_bHandCursor )
	{
		double cy = (p.y - m_pt.y);

		if(m_sliderHor.PtInRect(p, m_yTurn) == false &&
			m_slider.PtInRect(p, m_xTurn) == false)
			m_xTurn2 = cy / 2.5;

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

BOOL CPerek42::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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

void CPerek42::PaintSlider(void)
{
	m_slider.InitOnSubHeadButton();
	m_sliderHor.InitOnSubHeadButton();
}

void CPerek42::InitOnSubHeadButton(void)
{
	m_yTurn = m_sliderHor.SetVal(0);
	m_xTurn = m_slider.SetVal(0);
	m_xTurn2 = 0;
	PaintSlider();
}

void CPerek42::PaintResult(void)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	m_memDc.FillSolidRect(m_rcRes, 0);

	CRect rc = m_rcRes;

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

	COLORREF txtcolor = m_memDc.SetTextColor(color0);
	m_memDc.SetBkMode(TRANSPARENT);
	CFont* pFont = m_memDc.SelectObject(&font);
	CString sTxt, sMsg;

	sMsg = "מעלות המשוה השוקע";

	double temp = angAliya + m_tosefetOfek;
	if(temp >= 360.0)
		temp -= 360.0;
	else if(temp < 0.0)
		temp += 360.0;

	double halakim = floor(temp);
	halakim = (temp - halakim) * 60.0;
	temp = floor(temp);


	sTxt.Format("%s\n%3.0f '%-2.0f",sMsg, temp, halakim);

	int h = m_memDc.DrawText(sTxt, rc, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/) + 10;

	rc.top += h;


	temp = angAliya + m_tosefetOfek + 180.0;
	halakim = floor(temp);
	halakim = (temp - halakim) * 60.0;
	temp = floor(temp);
	if(temp >= 360.0)
		temp -= 360.0;
	else if(temp < 0.0)
		temp += 360.0;

	CString sHalakim = (halakim < 9.5)?"0":"";
	if(halakim > 59.5)
	{
		halakim = 0;
		temp++;
	}

	sMsg = "מעלות המשוה העולה";
	sTxt.Format("%s\n%3.0f '%s%.0f",sMsg, temp, sHalakim, halakim);

	m_memDc.SetTextColor(colOrechSkia);
	h += m_memDc.DrawText(sTxt, rc, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);


	m_rcRes.bottom = m_rcRes.top + h;

	m_memDc.SetTextColor(txtcolor);
	m_memDc.SelectObject(pFont);
	dc.BitBlt(m_rcRes.left,m_rcRes.top,m_rcRes.Width(),m_rcRes.Height(),
		&m_memDc, m_rcRes.left,m_rcRes.top, SRCCOPY);

}
