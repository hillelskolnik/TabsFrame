// Perek34.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek34.h"


// CPerek34

IMPLEMENT_DYNCREATE(CPerek34, CPerek3DBase)

CPerek34::CPerek34()
: m_xTurn2(0)
, m_xTurn3(0)
, m_sliderHorRc(180, ipHeight - 80,ipWidth,ipHeight)
, m_slider2(this, CRect(90,2,180, ipHeight),CSlider::VerCaptionResultMazalot)
, m_slider(this, CRect(3,2,90, ipHeight),CSlider::VerMin90Plus90)
, m_yStart(12)
, trsz(356)
, trszArez(50)
, stepsArez(0)
, m_xStart(8.5)
, trszSteps(0)
, lastx3(1000000)
, galgalMazalotCol(0)
, colorMasveYom(0)
, color0(0)
, lasty(0)
, lastx2(0)
{
	trszSteps = DiameterSteps(trsz);
	stepsArez = DiameterSteps(trszArez);
	m_IDstart = ID_P34_1;
	m_IDidx = WT_PEREK_34;
	m_IDX_PEREK = IDX_PEREK_34;
}

CPerek34::~CPerek34()
{
}

BEGIN_MESSAGE_MAP(CPerek34, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P34_1, ID_P34_1, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P34_1, ID_P34_1, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CPerek34 diagnostics

#ifdef _DEBUG
void CPerek34::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek34::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek34 message handlers

enum
{
	ofek
	,arez
	,ofekcir
	,kavSave
	,galgalMashve
	,ofanHaziHaYom
	,nekudatRosh
	,shemesh
	,galgalMazalot
};

int CPerek34::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_slider2.SetDeflate(1,7,0,4);
	m_slider2.SetCaption("מזל");
	m_slider2.Init();

	m_slider.SetDeflate(0,7,0,4);
	m_slider.SetCaption("רוחב המדינה");
	m_slider.SetRefPoint(bottom);
	m_slider.SetMinMax(0, 90);
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
	m_3dscreen.TurnShape(90.0, axis_X, false,true);

	m_3dscreen.BeginObject(kavSave);
	m_3dscreen.CReateCircleLineObject(trszArez + 1, RGBT(128,128,128,50));

	colorMasveYom = RGB(192,64,128);
	m_3dscreen.BeginObject(galgalMashve);
	m_3dscreen.CReateCircleLineObject(trsz, colorMasveYom);

	m_3dscreen.BeginObject(ofanHaziHaYom);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(96,64,192));
	m_3dscreen.TurnShape(90.0, axis_Y, false, true);

	COLORREF color5 = RGB(192,64,32);
	int kotTrsz = DiameterSteps(9);
	m_3dscreen.BeginObject(nekudatRosh);
	m_3dscreen.CreateSphereObject(9, 
		ColBright(color5, -0.65));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color5,0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2.0, axis_Y, true);
	m_3dscreen.TurnObjectCenter(m_xStart, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	int sShemesh = 17;
	int stepsShem = DiameterSteps(sShemesh);
	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(128,0,0, 0));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(255,128,0,0)
		,fr_zIntensity , (double)sShemesh / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(
		(double)trsz / 2.0,axis_Y, true);

	galgalMazalotCol = ColBright(RGB(200,147,78), -0.6);
	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.CReateCircleLineObject(trsz, galgalMazalotCol/*,m_fineMashve*/);
	m_3dscreen.TurnShape(23.5 ,axis_Y, false, true);



	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek34::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();


	double sinNetya = SinNetyatAliyaYeshara(m_xTurn3, 23.5);
	m_3dscreen.BeginObject(arez);
	{
		double angNetiya = asin(sinNetya) * ToD;

		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnLightPt(0,axis_X, true);
		m_3dscreen.TurnLightPt(270.0 + angNetiya,axis_X);
		m_3dscreen.TurnLightPt(-m_xTurn2, axis_Z);

		CFillRectData data;
		data.radius = (double)trszArez / 2.0;
		data.vec2 = 0.4;
		m_3dscreen.FillRect(0,0,stepsArez,stepsArez/2, RGB(24,24,24), 
			fr_lightOppositeDirection, data);


		m_3dscreen.TurnShape(m_xTurn2, axis_Z, false);
		m_3dscreen.TurnShape(-m_xTurn, axis_X, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		m_3dscreen.TurnShape(m_xStart, axis_X);
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(kavSave);
	if(lastx3== m_xTurn3)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(-m_xTurn, axis_X, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		m_3dscreen.TurnShape(m_xStart, axis_X);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	CFillRectData data2;
	data2.vec = 0.4;
	data2.radius = (double)trsz/2.0;

	m_3dscreen.BeginObject(galgalMashve);
	if(lastx3== m_xTurn3)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(-m_xTurn, axis_X, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		m_3dscreen.TurnShape(m_xStart, axis_X, false);
		m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data2);
		m_3dscreen.TurnShape(0.0, axis_X);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(ofanHaziHaYom);
	//if(lastx3== m_xTurn3)
	{
		double angNetya = asin(sinNetya) * ToD;
		double govaShemes = 90 - (-angNetya + m_xTurn);
		double emzaNetiya = govaShemes / 2;
		double range = fabs(cos(emzaNetiya * D)) * (double)trsz / 2;


		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnLightPt(0,axis_X, true);
		m_3dscreen.TurnLightPt(180.0 + emzaNetiya,axis_X);

		CFillRectData data;
		data.vec = range;
		m_3dscreen.FillRect(0,0,trszSteps,3, color0, 
			fr_PaintDiractionRange, data);

		m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		m_3dscreen.TurnShape(m_xStart, axis_X, false);
		m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data2);
		m_3dscreen.TurnShape(0.0, axis_X);
		m_3dscreen.Translate3Dto2D();
	}
	//else
	//	m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(nekudatRosh);
	m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(ofekcir);
	m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(asin(sinNetya) * ToD, axis_X);
	m_3dscreen.TurnObjectCenter(-m_xTurn, axis_X);
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	m_3dscreen.TurnObjectCenter(m_xStart, axis_X);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.ResetTranslation();
	double aliyaYeshra = AliyaYeshara(m_xTurn3, 23.5);
	m_3dscreen.TurnShape(-aliyaYeshra, axis_Z,false);
	m_3dscreen.TurnShape(-m_xTurn, axis_X,false);
	m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
	m_3dscreen.TurnShape(m_xStart, axis_X, false);
	m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data2);
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.BeginObject(ofek);
	m_3dscreen.Translate3Dto2D(FALSE);

	PaintResult();
	lastx3 = m_xTurn3;
	lastx2 = m_xTurn2;
	lasty = m_yTurn;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek34::PaintResult(void)
{
	if(lastx2 != m_xTurn2 || lasty != m_yTurn)
		return;
	CClientDC dc(this);
	OnPrepareDC(&dc);

	CRect rc(ipWidth-150, 200, ipWidth, 500);
	CRect rc2(rc);

	m_memDc.FillSolidRect(rc,0);


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

	m_memDc.SetBkMode(TRANSPARENT);
	CFont* pFont = m_memDc.SelectObject(&font);

	CString sTxt;
	COLORREF txtcolor = m_memDc.SetTextColor(colorMasveYom);
	sTxt.Format("%s\n%4.1f","גובה משוה היום מהאופק הדרומי" ,(90.0 - m_xTurn));
	int nTxtHeight = m_memDc.DrawText(sTxt, rc2, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);

	rc2.top += nTxtHeight;
	m_memDc.SetTextColor(galgalMazalotCol);
	double angNetya = asin(SinNetyatAliyaYeshara(m_xTurn3, 23.5)) * ToD;
	sTxt.Format("%s\n%4.1f","תוספת נטיית גלגל המזלות ממשוה היום" ,angNetya);
	nTxtHeight = m_memDc.DrawText(sTxt, rc2, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);

	rc2.top += nTxtHeight;
	m_memDc.SetTextColor(color0);
	sTxt.Format("%s\n%4.1f","גובה השמש מאופק הדרומי באופן חצי היום" ,
		(90.0 - m_xTurn + angNetya));
	nTxtHeight = m_memDc.DrawText(sTxt, rc2, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);



	m_memDc.SetTextColor(txtcolor);
	m_memDc.SelectObject(pFont);

	dc.BitBlt(rc.left,
		rc.top,rc.Width(),rc.Height(),
		&m_memDc,rc.left,rc.top,SRCCOPY);

}

void CPerek34::OnMouseMove(UINT nFlags, CPoint point)
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
		else if(m_slider.PtInRect(p, m_xTurn) == false &&
			m_slider2.PtInRect(p, m_xTurn3) == false)
		{
			m_xTurn2 = -cy ;
		}

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek34::InitOnSubHeadButton(void)
{
	m_yTurn = m_yStart;
	m_xTurn = m_slider.SetVal(0);
	m_xTurn2 = 0;
	lastx3 = m_xTurn3 = m_slider2.SetVal(0);

	PaintSlider();
}

BOOL CPerek34::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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

void CPerek34::PaintSlider(void)
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
	m_slider2.InitOnSubHeadButton();

	dc.BitBlt(m_sliderHorRc.left,
		m_sliderHorRc.top,m_sliderHorRc.Width(),m_sliderHorRc.Height(),
		&m_memDc,m_sliderHorRc.left,m_sliderHorRc.top,SRCCOPY);

	m_memDc.RestoreDC(n);
}
