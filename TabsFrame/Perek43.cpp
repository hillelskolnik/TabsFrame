// Perek43.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek43.h"


// CPerek43

IMPLEMENT_DYNCREATE(CPerek43, CPerek3DBase)

CPerek43::CPerek43()
: m_sliderHor(this, CRect(100, ipHeight-85,ipWidth,ipHeight),CSlider::simpleHorizontal)
, m_slider(this, CRect(0, 0,100,ipHeight),CSlider::VerCaptionResultMazalot)
, m_sliderMar(this, CRect(100, (ipHeight-85)/2,200,ipHeight-85),CSlider::VerMin90Plus90)
, m_sliderMiz(this, CRect(100, 0,200,(ipHeight-85)/2),CSlider::VerMin90Plus90)
, m_sliderMedMiz(this, CRect(200, 0,400,100),CSlider::simpleHorizontal360)
, m_sliderSivuvYom(this, CRect(400, 0,700,100),CSlider::simpleHorizontal360)
, trszArez(260)
, arezFine(1.35)
, m_xTurnMa(0)
, m_xTurnMiz(0)
, m_yTurnMedMiz(0)
, colMedMiz(RGB(0,255,0))
, arezSteps(0)
, colMedMaarav(RGB(255,192,64))
, trsz(300)
, m_yTurnYomi(0)
, kizuzMa(0)
, kizuzMiz(0)
, m_rcRes(ipWidth - 220, 150, ipWidth, 400)
, lastMiz(0)
, lasty(0)
, lastyYomi(0)
, m_xTurn2(0)
, lastxMiz(0)
, lastx2(0)
{
	arezSteps = DiameterSteps(trszArez, arezFine);
	m_IDstart = ID_P43_1;
	m_IDidx = WT_PEREK_43;
	m_IDX_PEREK = IDX_PEREK_43;
}

CPerek43::~CPerek43()
{
}

BEGIN_MESSAGE_MAP(CPerek43, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P43_1, ID_P43_2, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P43_1, ID_P43_2, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek43 diagnostics

#ifdef _DEBUG
void CPerek43::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek43::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


enum
{
	arez
	,medinaMaarav
	,medinaMiz
	,shemesh
};

int CPerek43::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	m_slider.SetResultFormat("%.1f");
	m_slider.Init();

	m_sliderMar.SetDeflate(3,3,3,3);
	m_sliderMar.SetFrameColor(colMedMaarav);
	m_sliderMar.SetFontSize(-16);
	m_sliderMar.SetResultFormat("%.1f");
	m_sliderMar.SetCaption("רוחב מדינה מערבית");
	m_sliderMar.SetRefPoint(bottom);
	m_sliderMar.SetMinMax(0,65);
	m_sliderMar.Init();
	m_xTurnMa = m_sliderMar.SetVal(32);

	m_sliderMiz.SetDeflate(3,3,3,3);
	m_sliderMiz.SetFrameColor(colMedMiz);
	m_sliderMiz.SetFontSize(-16);
	m_sliderMiz.SetResultFormat("%.1f");
	m_sliderMiz.SetCaption("רוחב מדינה מזרחית");
	m_sliderMiz.SetRefPoint(bottom);
	m_sliderMiz.SetMinMax(0,65);
	m_sliderMiz.Init();
	m_sliderMiz.SetMinMaxRange(0, m_xTurnMa);
	m_xTurnMiz = m_sliderMiz.SetVal(0);

	m_sliderMedMiz.SetDeflate(3,3,3,3);
	m_sliderMedMiz.SetFrameColor(colMedMiz);
	m_sliderMedMiz.SetCaption("מדינה מזרחית ב");
	m_sliderMedMiz.SetMinMax(0,30);
	m_sliderMedMiz.SetResultFormat("%.1f");
	m_sliderMedMiz.Init();
	m_yTurnMedMiz = m_sliderMedMiz.SetVal(8);

	m_sliderSivuvYom.SetDeflate(3,3,3,3);
	m_sliderSivuvYom.SetRefPoint(middle);
	m_sliderSivuvYom.SetFrameColor(RGB(255,192,128));
	m_sliderSivuvYom.SetMinMax(-60,60);
	m_sliderSivuvYom.SetResultFormat("%.1f");
	m_sliderSivuvYom.Init();

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];

	//color0 = cp.paragraphs[0].color;

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
	m_3dscreen.TurnShape(55.0,axis_y, false,true);
	//m_3dscreen.TurnShape(90.0,axis_z, false,true);
	m_3dscreen.ResetTranslation();

	int kotTrsz = DiameterSteps(9);
	m_3dscreen.BeginObject(medinaMaarav);
	m_3dscreen.CreateSphereObject(9, 
		ColBright(colMedMaarav, -0.65));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(colMedMaarav,0.35)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trszArez/2.0, axis_Z, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(medinaMiz);
	m_3dscreen.CreateSphereObject(9, 
		ColBright(colMedMiz, -0.65));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(colMedMiz,0.35)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trszArez/2.0, axis_Z, true);
	m_3dscreen.ResetTranslation();

	int sShemesh = 13;
	int stepsShem = DiameterSteps(sShemesh);
	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(128,0,0, 20));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(255,128,0,20)
		,fr_zIntensity , (double)sShemesh / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(
		(double)trsz / 2.0,axis_X, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek43::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	double sinNetiya = SinNetyatAliyaYeshara(m_xTurn, 23.5);
	double angNetiya = asin(sinNetiya) * ToD;
	kizuzMa = kizuzNetiyaLaOfek(m_xTurnMa,sinNetiya);
	kizuzMiz = kizuzNetiyaLaOfek(m_xTurnMiz,sinNetiya);


	m_3dscreen.BeginObject(arez);
	if(lastMiz == m_yTurnMedMiz && lastxMiz == m_xTurnMiz)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnLightPt(0,axis_X, true);
		m_3dscreen.TurnLightPt(90.0,axis_Y);
		m_3dscreen.TurnLightPt(angNetiya,axis_Z);
		if(m_buttonId)
			m_3dscreen.TurnLightPt(180,axis_Y);

		if(m_buttonId)
			m_3dscreen.TurnLightPt(-m_yTurn - kizuzMa,axis_Y);
		else
			m_3dscreen.TurnLightPt(-m_yTurn + kizuzMa,axis_Y);
		m_3dscreen.TurnLightPt(-m_yTurnYomi,axis_Y);


		CFillRectData data;
		data.radius = (double)trszArez / 2.0;
		data.vec2 = 0.4;
		m_3dscreen.FillRect(0,0,arezSteps,arezSteps/2, RGB(24,24,24), 
			fr_lightOppositeDirection, data);


		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn/* + m_yStart*/, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn2, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(medinaMaarav);
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(-m_xTurnMa + m_xTurn2, axis_x);
	m_3dscreen.TurnShape(0.0, axis_x);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(medinaMiz);
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(-m_xTurnMiz, axis_x);
	m_3dscreen.TurnObjectCenter(m_yTurnMedMiz, axis_y);
	m_3dscreen.TurnObjectCenter(m_xTurn2, axis_x);
	m_3dscreen.TurnShape(0.0, axis_x);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(angNetiya,axis_Z);
	if(m_buttonId)
		m_3dscreen.TurnObjectCenter(180,axis_Y);

	if(m_buttonId)
		m_3dscreen.TurnObjectCenter(-kizuzMa,axis_Y);
	else
		m_3dscreen.TurnObjectCenter(kizuzMa,axis_Y);

	m_3dscreen.TurnObjectCenter(-m_yTurnYomi,axis_Y);
	m_3dscreen.TurnObjectCenter(m_xTurn2,axis_X);
	m_3dscreen.TurnShape(0.0, axis_x);
	m_3dscreen.Translate3Dto2D();


	if(lasty == m_yTurn && lastyYomi == m_yTurnYomi && lastx2 == m_xTurn2)
		PaintResult();
	lastyYomi = m_yTurnYomi;
	lasty = m_yTurn;
	lastMiz = m_yTurnMedMiz;
	lastxMiz = m_xTurnMiz;
	lastx2 = m_xTurn2;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek43::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = (p.x > 3 && p.y > 1 && p.x < ipWidth)?TRUE:FALSE;

	if( m_bBntDown && m_bHandCursor )
	{
		double cy = (p.y - m_pt.y);

		bool b1 = m_sliderHor.PtInRect(p, m_yTurn);
		if(b1 == false)
			b1 = m_slider.PtInRect(p, m_xTurn);
		if(b1 == false && m_sliderMar.PtInRect(p, m_xTurnMa))
		{
			b1 = true;
			m_sliderMiz.SetMinMaxRange(0, m_xTurnMa);
			if(m_xTurnMa < m_xTurnMiz)
			{
				m_xTurnMiz = m_sliderMiz.SetVal(m_xTurnMa);
			}
		}
		else if(b1 == false)
			b1 = m_sliderMiz.PtInRect(p, m_xTurnMiz);
		if(b1 == false)
			b1 = m_sliderMedMiz.PtInRect(p, m_yTurnMedMiz);
		if(b1 == false)
			b1 = m_sliderSivuvYom.PtInRect(p, m_yTurnYomi);
		if(b1 == false)
			m_xTurn2 = cy / 3.0;

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

BOOL CPerek43::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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

void CPerek43::InitOnSubHeadButton(void)
{
	lastx2 = m_xTurn2;
	lastxMiz = m_xTurnMiz;
	lasty = m_yTurn;
	lastyYomi = m_yTurnYomi = m_sliderSivuvYom.SetVal(0);
	PaintSlider();
}

void CPerek43::PaintSlider(void)
{
	m_slider.SetCaption(m_buttonId?"שקיעה במזל":"זריחה במזל");
	m_slider.InitOnSubHeadButton();
	m_sliderHor.InitOnSubHeadButton();
	m_sliderMar.InitOnSubHeadButton();
	m_sliderMiz.InitOnSubHeadButton();
	m_sliderMedMiz.InitOnSubHeadButton();
	m_sliderSivuvYom.SetCaption(m_buttonId?"סיבוב המשוה מהשקיעה":"סיבוב המשוה מהזריחה");
	m_sliderSivuvYom.InitOnSubHeadButton();
}

void CPerek43::PaintResult(void)
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

	COLORREF txtcolor = m_memDc.SetTextColor(colMedMaarav);
	m_memDc.SetBkMode(TRANSPARENT);
	CFont* pFont = m_memDc.SelectObject(&font);
	CString sTxt, sMsg;

	if(m_buttonId)
		sMsg = "קדימת השקיעה במדינה המערבית";
	else
		sMsg = "קדימת הזריחה במדינה המערבית";

	double tkizuzMa = kizuzMa;

	if(tkizuzMa > 180.0)
		tkizuzMa -= 360.0;
	if(m_buttonId)
		tkizuzMa = -tkizuzMa;

	sTxt.Format("%s\n%.1f",sMsg, tkizuzMa);

	int h = m_memDc.DrawText(sTxt, rc, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/) + 10;

	rc.top = m_rcRes.top +h;



	if(m_buttonId)
		sMsg = "קדימת השקיעה במדינה המזרחית";
	else
		sMsg = "קדימת הזריחה במדינה המזרחית";

	double tkizuzMiz = kizuzMiz;

	if(tkizuzMiz > 180.0)
		tkizuzMiz -= 360.0;
	if(m_buttonId)
		tkizuzMiz = -tkizuzMiz;

	sTxt.Format("%s\n%.1f",sMsg, tkizuzMiz);

	m_memDc.SetTextColor(colMedMiz);
	h += m_memDc.DrawText(sTxt, rc, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/) + 10;

	rc.top = m_rcRes.top +h;

	if(m_buttonId)
		sMsg = "הפרש השקיעה בין המדינה המערבית למיזרחית";
	else
		sMsg = "הפרש הזריחה בין המדינה המערבית למיזרחית";
	double hefresh = tkizuzMa - (tkizuzMiz + m_yTurnMedMiz);

	sTxt.Format("%s\n%.1f",sMsg, hefresh);

	m_memDc.SetTextColor(RGB(0,0,255));
	h += m_memDc.DrawText(sTxt, rc, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);

	if(hefresh > 0.0)
	{
		h += 10;
		rc.top = m_rcRes.top +h;
		if(m_buttonId)
			sMsg = "שקיעה מערבית מוקדמת ב";
		else
			sMsg = "זרריחה מערבית מוקדמת ב";

		sTxt.Format("%s\n%.1f",sMsg, hefresh);
		m_memDc.SetTextColor(RGB(255,0,0));
		h += m_memDc.DrawText(sTxt, rc, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);
	}


	rc = m_rcRes;

	rc.bottom = rc.top + h;

	if(rc.bottom > m_rcRes.bottom)
		m_rcRes.bottom = rc.bottom;

	m_memDc.SetTextColor(txtcolor);
	m_memDc.SelectObject(pFont);

	dc.BitBlt(rc.left,rc.top,rc.Width(),m_rcRes.Height(),
		&m_memDc, rc.left,rc.top, SRCCOPY);

}
