// Perek38.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek38.h"


// CPerek38

IMPLEMENT_DYNCREATE(CPerek38, CPerek3DBase)

CPerek38::CPerek38()
: color0(0)
, m_sliderHor(this, CRect(0, ipHeight - 120, ipWidth, ipHeight), CSlider::simpleHorizontal360)
, m_slider1(this, CRect(0, 0, 90, ipHeight-120), CSlider::VerMin90Plus90)
, m_slider2(this, CRect(90, 0, 180, ipHeight-120), CSlider::VerMin90Plus90)
, trsz(336)
, trszArez(236)
, m_yStart(15)
, m_xStart(5)
, colSofHaYeshuv(0)
, m_captionRc(ipWidth-150, 300, ipWidth, 400)
, m_xTurn1(0)
, m_xTurn2(0)
, lastx1(0)
, lastx2(0)
{
	m_IDstart = ID_P38_1;
	m_IDidx = WT_PEREK_38;
	m_IDX_PEREK = IDX_PEREK_38;

}

CPerek38::~CPerek38()
{
}

BEGIN_MESSAGE_MAP(CPerek38, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P38_1, ID_P38_1, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P38_1, ID_P38_1, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CPerek38 diagnostics

#ifdef _DEBUG
void CPerek38::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek38::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek38 message handlers

enum
{
	arez
	,kavOrech
	,kavRoshOrech
	,sofHaYeshuv
	,medina1
	,medina2
};

int CPerek38::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	m_sliderHor.SetCaption("קו אורך המדינה");
	m_sliderHor.Init();

	COLORREF color5 = RGB(192,64,32);
	m_slider1.SetDeflate(3,3,3,3);
	m_slider1.SetCaption("רוחב המדינה אחת");
	m_slider1.SetFrameColor(color5);
	m_slider1.SetFontSize(-16);
	m_slider1.Init();

	COLORREF color6 = RGB(192,64,128);
	m_slider2.SetDeflate(3,3,3,3);
	m_slider2.SetCaption("רוחב המדינה שניה");
	m_slider2.SetFrameColor(color6);
	m_slider2.SetFontSize(-16);
	m_slider2.Init();


	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];

	color0 = cp.paragraphs[0].color;
	colSofHaYeshuv = RGB(200, 150, 50);

	CClientDC dc(this);
	m_memDc.CreateCompatibleDC(&dc);
	m_memBm.CreateCompatibleBitmap(&dc, ipWidth,ipHeight);
	m_memDc.SelectObject(&m_memBm);
	m_memDc.SelectObject(&m_font);

	{
		CFont font;
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

		CString sTxt = "סןף הישוב";
		COLORREF txtcolor = m_memDc.SetTextColor(colSofHaYeshuv);
		int nTxtHeight = m_memDc.DrawText(sTxt, m_captionRc, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);

		m_memDc.SetTextColor(txtcolor);
		m_memDc.SelectObject(pFont);
	}

	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 25.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();
	m_3dscreen.NoPaint();

	m_3dscreen.BeginObject(arez);
	m_3dscreen.CreateSphereObject(trszArez, 0,360.0,90.0,-90.0,1.35);
	m_3dscreen.BitmapToObject(bm11, RGBT2(0,0));
	m_3dscreen.TurnShape(121.0, axis_Y, false,true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(kavOrech);
	m_3dscreen.CReateCircleLineObject(trszArez + 1, color0);
	m_3dscreen.TurnShape(90.0, axis_Y, false,true);

	m_3dscreen.BeginObject(kavRoshOrech);
	m_3dscreen.CReateCircleLineObject(trsz, color0);
	m_3dscreen.TurnShape(90.0, axis_Y, false,true);

	m_3dscreen.BeginObject(sofHaYeshuv);
	m_3dscreen.CReateCircleLineObject(trszArez + 2, colSofHaYeshuv,
		1.0, 180.0);
	m_3dscreen.TurnShape(90.0, axis_Y, false,true);
	m_3dscreen.TurnShape(90.0, axis_x, false,true);

	int kotTrsz = DiameterSteps(9);
	m_3dscreen.BeginObject(medina1);
	m_3dscreen.CreateSphereObject(9, 
		ColBright(color5, -0.65));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color5,0.35)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trszArez/2.0, axis_Z, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(medina2);
	m_3dscreen.CreateSphereObject(9, 
		ColBright(color6, -0.65));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color6,0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trszArez/2.0, axis_Z, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_xTurn2 = m_slider2.SetVal(30);

	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek38::OnMouseMove(UINT nFlags, CPoint point)
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
			m_slider1.PtInRect(p, m_xTurn1) == false  &&
			m_slider2.PtInRect(p, m_xTurn2) == false)			
			m_xTurn = cy / 3.0;

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek38::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(arez);
	if(!(lastx1 != m_xTurn1 || lastx2 != m_xTurn2))
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(-m_yTurn + m_yStart, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn + m_xStart, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(kavOrech);
	if(!(lastx1 != m_xTurn1 || lastx2 != m_xTurn2))
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yStart, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn + m_xStart, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(kavRoshOrech);
	if(!(lastx1 != m_xTurn1 || lastx2 != m_xTurn2))
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yStart, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn + m_xStart, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(sofHaYeshuv);
	if(!(lastx1 != m_xTurn1 || lastx2 != m_xTurn2))
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(-m_yTurn + m_yStart, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn + m_xStart, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(medina1);
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(-m_xTurn1, axis_X);
	m_3dscreen.TurnObjectCenter(m_yStart, axis_Y);
	m_3dscreen.TurnObjectCenter(m_xTurn + m_xStart, axis_X);
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(medina2);
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(-m_xTurn2, axis_X);
	m_3dscreen.TurnObjectCenter(m_yStart, axis_Y);
	m_3dscreen.TurnObjectCenter(m_xTurn + m_xStart, axis_X);
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	lastx1 = m_xTurn1;
	lastx2 = m_xTurn2;

	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

BOOL CPerek38::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_EXTRA_DRAW:
		m_sliderHor.InitOnSubHeadButton();
		m_slider1.InitOnSubHeadButton();
		m_slider2.InitOnSubHeadButton();
		PaintSlider();
		return TRUE;
	}

	return CPerek3DBase::OnWndMsg(message, wParam, lParam, pResult);
}

void CPerek38::InitOnSubHeadButton(void)
{
	m_yTurn = m_sliderHor.SetVal(0);
	m_xTurn = 0;
	m_sliderHor.InitOnSubHeadButton();
	m_slider1.InitOnSubHeadButton();
	m_slider2.InitOnSubHeadButton();
	PaintSlider();
}

void CPerek38::PaintSlider(void)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);

	dc.BitBlt(m_captionRc.left,
		m_captionRc.top,m_captionRc.Width(),m_captionRc.Height(),
		&m_memDc,m_captionRc.left,m_captionRc.top,SRCCOPY);
}
