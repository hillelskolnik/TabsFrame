// Perek36.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek36.h"


// CPerek36

IMPLEMENT_DYNCREATE(CPerek36, CPerek3DBase)

CPerek36::CPerek36()
: color0(0)
, m_sliderHor(this, CRect(0, ipHeight - 120, ipWidth, ipHeight), CSlider::simpleHorizontal360)
, trsz(336)
, trszArez(236)
, m_yStart(15)
, m_xStart(5)
, colSofHaYeshuv(0)
, m_captionRc(ipWidth-150, 300, ipWidth, 400)
{
	m_IDstart = ID_P36_1;
	m_IDidx = WT_PEREK_36;
	m_IDX_PEREK = IDX_PEREK_36;
}

CPerek36::~CPerek36()
{
}

BEGIN_MESSAGE_MAP(CPerek36, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P36_1, ID_P36_1, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P36_1, ID_P36_1, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CPerek36 diagnostics

#ifdef _DEBUG
void CPerek36::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek36::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek36 message handlers
enum
{
	arez
	,kavOrech
	,kavRoshOrech
	,sofHaYeshuv
};

int CPerek36::OnCreate(LPCREATESTRUCT lpCreateStruct)
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



	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek36::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = (p.x > 3 && p.y > 1 && p.x < ipWidth)?TRUE:FALSE;

	if( m_bBntDown && m_bHandCursor )
	{
		double cy = (p.y - m_pt.y);

		if(m_sliderHor.PtInRect(p, m_yTurn) == false)
			m_xTurn = cy / 3.0;

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek36::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(arez);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(-m_yTurn + m_yStart, axis_Y);
	m_3dscreen.TurnMatrix(m_xTurn + m_xStart, axis_X);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kavOrech);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(m_yStart, axis_Y);
	m_3dscreen.TurnMatrix(m_xTurn + m_xStart, axis_X);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kavRoshOrech);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(m_yStart, axis_Y);
	m_3dscreen.TurnMatrix(m_xTurn + m_xStart, axis_X);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(sofHaYeshuv);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(-m_yTurn + m_yStart, axis_Y);
	m_3dscreen.TurnMatrix(m_xTurn + m_xStart, axis_X);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

BOOL CPerek36::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_EXTRA_DRAW:
		m_sliderHor.InitOnSubHeadButton();
		PaintSlider();
		return TRUE;
	}

	return CPerek3DBase::OnWndMsg(message, wParam, lParam, pResult);
}

void CPerek36::InitOnSubHeadButton(void)
{
	m_yTurn = m_sliderHor.SetVal(0);
	m_xTurn = 0;
	m_sliderHor.InitOnSubHeadButton();
	PaintSlider();
}

void CPerek36::PaintSlider(void)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);

	dc.BitBlt(m_captionRc.left,
		m_captionRc.top,m_captionRc.Width(),m_captionRc.Height(),
		&m_memDc,m_captionRc.left,m_captionRc.top,SRCCOPY);
}
