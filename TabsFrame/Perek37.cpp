// Perek37.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek37.h"


// CPerek37

IMPLEMENT_DYNCREATE(CPerek37, CPerek3DBase)

CPerek37::CPerek37()
: color0(0)
, m_sliderHor(this, CRect(0, ipHeight - 120, ipWidth, ipHeight), CSlider::simpleHorizontal360)
, m_sliderHor2(this, CRect(0, 0, ipWidth-400, 120), CSlider::simpleHorizontal360)
, m_slider(this, CRect(0, 120, 120, ipHeight - 120), CSlider::VerMin90Plus90)
, trsz(336)
, trszArez(236)
, m_yStart(15)
, m_xStart(5)
, colSofHaYeshuv(0)
, m_captionRc(ipWidth-150, 300, ipWidth, 500)
, m_yTurn2(0)
, m_yTosefetMaarav(0)
, m_nCapHeight(0)
, lastyTosefet(0)
{
	m_IDstart = ID_P37_1;
	m_IDidx = WT_PEREK_37;
	m_IDX_PEREK = IDX_PEREK_37;
}

CPerek37::~CPerek37()
{
}

BEGIN_MESSAGE_MAP(CPerek37, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P37_1, ID_P37_1, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P37_1, ID_P37_1, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CPerek37 diagnostics

#ifdef _DEBUG
void CPerek37::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek37::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek37 message handlers

enum
{
	arez
	,kavOrech
	,kavTosefetOrech
	,kavRoshOrech
	,sofHaYeshuv
};

int CPerek37::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	m_sliderHor2.SetMinMax(0,180);
	m_sliderHor2.SetDeflate(3,3,3,3);
	m_sliderHor2.SetCaption("מעלות המדינה השנית מערבה");
	m_sliderHor2.Init();

	m_slider.SetDeflate(3,3,3,3);
	m_slider.Init();


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
		m_nCapHeight = m_memDc.DrawText(sTxt, m_captionRc, 
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
	m_3dscreen.CReateCircleLineObject(trszArez + 2, color0);
	m_3dscreen.TurnShape(90.0, axis_Y, false,true);

	m_3dscreen.BeginObject(kavTosefetOrech);
	m_3dscreen.CReateCircleLineObject(trszArez + 2, ColBright(color0, 0.4)
		,1.0, 180.0);
	m_3dscreen.TurnShape(90.0, axis_Y, false,true);
	m_3dscreen.TurnShape(90.0, axis_x, false,true);

	m_3dscreen.BeginObject(kavRoshOrech);
	m_3dscreen.CReateCircleLineObject(trsz, color0);
	m_3dscreen.TurnShape(90.0, axis_Y, false,true);

	m_3dscreen.BeginObject(sofHaYeshuv);
	m_3dscreen.CReateCircleLineObject(trszArez + 2, colSofHaYeshuv,
		1.0, 180.0);
	m_3dscreen.TurnShape(90.0, axis_Y, false,true);
	m_3dscreen.TurnShape(90.0, axis_x, false,true);



	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek37::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = (p.x > 3 && p.y > 1 && p.x < ipWidth)?TRUE:FALSE;

	if( m_bBntDown && m_bHandCursor )
	{
		//double cy = (p.y - m_pt.y);
		double cx = (p.x - m_pt.x);

		if(m_sliderHor.PtInRect(p, m_yTurn) == false
			&& m_sliderHor2.PtInRect(p, m_yTosefetMaarav) == false
			&& m_slider.PtInRect(p, m_xTurn) == false
			)
		{
			m_yTurn2 = cx / 2.0;
		}

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek37::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(arez);
	if(lastyTosefet == m_yTosefetMaarav)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(-m_yTurn + m_yStart + m_yTurn2, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn + m_xStart, axis_X);
		//m_3dscreen.TurnMatrix(m_yTurn2, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(kavOrech);
	if(lastyTosefet == m_yTosefetMaarav)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yStart + m_yTurn2, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn + m_xStart, axis_X);
		//m_3dscreen.TurnMatrix(m_yTurn2, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(kavTosefetOrech);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(m_yStart + m_yTosefetMaarav + m_yTurn2, axis_Y);
	m_3dscreen.TurnMatrix(m_xTurn + m_xStart, axis_X);
	//m_3dscreen.TurnMatrix(m_yTurn2, axis_Y);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kavRoshOrech);
	if(lastyTosefet == m_yTosefetMaarav)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yStart + m_yTurn2, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn + m_xStart, axis_X);
		//m_3dscreen.TurnMatrix(m_yTurn2, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(sofHaYeshuv);
	if(lastyTosefet == m_yTosefetMaarav)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(-m_yTurn + m_yStart + m_yTurn2, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn + m_xStart, axis_X);
		//m_3dscreen.TurnMatrix(m_yTurn2, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	if(lastyTosefet != m_yTosefetMaarav)
		PaintResult();

	lastyTosefet = m_yTosefetMaarav;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

BOOL CPerek37::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_EXTRA_DRAW:
		m_sliderHor.InitOnSubHeadButton();
		m_sliderHor2.InitOnSubHeadButton();
		m_slider.InitOnSubHeadButton();
		PaintSlider();
		PaintResult();
		return TRUE;
	}

	return CPerek3DBase::OnWndMsg(message, wParam, lParam, pResult);
}

void CPerek37::InitOnSubHeadButton(void)
{
	lastyTosefet = m_yTosefetMaarav;
	m_yTurn = m_sliderHor.SetVal(0);
	m_xTurn = m_slider.SetVal(0);
	m_sliderHor.InitOnSubHeadButton();
	m_sliderHor2.InitOnSubHeadButton();
	m_slider.InitOnSubHeadButton();
	PaintSlider();
	PaintResult();
}

void CPerek37::PaintSlider(void)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);

	dc.BitBlt(m_captionRc.left,
		m_captionRc.top,m_captionRc.Width(),m_nCapHeight,
		&m_memDc,m_captionRc.left,m_captionRc.top,SRCCOPY);
}

void CPerek37::PaintResult(void)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);

	CRect rc = m_captionRc;
	rc.top += m_nCapHeight;

	double tzman = m_yTosefetMaarav / 15.0;
	double shaot = floor(tzman);
	double dakot = tzman - shaot;
	dakot *= 60.0;
	CString sNull = (dakot < 9.5)?"0":"";
	CString sTxt;
	sTxt.Format("%s\n%2.0f:%s%.0f","הבדל השעות לפי הבדל האורך", shaot, sNull, dakot);

	CRect rc2 = rc;
	static int txtHeight = 0;
	if(txtHeight)
	{
		rc2.bottom = rc2.top + txtHeight + 5;
		m_memDc.FillSolidRect(rc2,0);
	}

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

	COLORREF txtcolor = m_memDc.SetTextColor(color0);
	txtHeight = m_memDc.DrawText(sTxt, rc2, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);

	m_memDc.SetTextColor(txtcolor);
	m_memDc.SelectObject(pFont);

	dc.BitBlt(rc2.left,rc2.top,rc2.Width(),rc2.Height(),
		&m_memDc, rc2.left,rc2.top,SRCCOPY);
}
