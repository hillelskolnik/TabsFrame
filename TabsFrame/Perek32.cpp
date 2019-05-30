// Perek32.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek32.h"


// CPerek32

IMPLEMENT_DYNCREATE(CPerek32, CPerek3DBase)

CPerek32::CPerek32()
: m_bRightBDown(false)
, lasty(0)
, m_yTurn(0)
, m_yStart(5)
, m_xTurn(0)
, m_xTurn2(0)
, m_xTurn3(0)
, m_xTurn4(0)
, m_xStart(5)
, trsz(356)
, trszArez(100)
, trszSteps(0)
, stepsArez(0)
, m_sliderHorRc(220, ipHeight - 80,ipWidth,ipHeight)
, mashveHaYomCol(RGB(26,108,99))
, galgalMazalotCol(RGB(255,0,128))
, m_slider2(this, CRect(90,2,180, ipHeight),CSlider::VerCaptionResultMazalot)
, m_slider(this, CRect(3,2,90, ipHeight),CSlider::VerMin90Plus90)
, color1(0)
, m_person(m_3dscreen)
, colorLayla(RGB(120,64,5))
, colorYom(/*RGB(245,128,10)*/RGB(255,255,10))
{
	trszSteps = DiameterSteps(trsz);
	stepsArez = DiameterSteps(trszArez);
	m_IDstart = ID_P32_1;
	m_IDidx = WT_PEREK_32;
	m_IDX_PEREK = IDX_PEREK_32;
}

CPerek32::~CPerek32()
{
}

BEGIN_MESSAGE_MAP(CPerek32, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P32_1, ID_P32_2, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P32_1, ID_P32_2, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()




// CPerek32 diagnostics

#ifdef _DEBUG
void CPerek32::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek32::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek32 message handlers
enum
{
	ofek
	,arez
	,ofekcir
	,mashveHaYom
	,galgalMazalot
	,mazalMesiba
	,shemesh
	,zafon

	,kavimArez
};
int CPerek32::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_slider2.SetDeflate(1,7,0,4);
	m_slider2.SetCaption("מזל");
	m_slider2.Init();

	m_slider.SetDeflate(0,7,0,4);
	m_slider.SetCaption("רוחב המדינה");
	m_slider.Init();

	m_bmMazalot.LoadBitmap(IDB_BITMAP_MAZALOT);

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
	m_3dscreen.TurnShape(-90.0, axis_Z, false,true);

	m_3dscreen.BeginObject(mashveHaYom);
	m_3dscreen.CReateCircleLineObject(trsz, mashveHaYomCol/*,m_fineMashve*/);
	m_3dscreen.TurnShape(90.0, axis_Y, false, true);

	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.CReateCircleLineObject(trsz, galgalMazalotCol/*,m_fineMashve*/);
	m_3dscreen.TurnShape(90 ,axis_Y, false, true);
	m_3dscreen.TurnShape(23.5 ,axis_Z, false, true);

	m_3dscreen.BeginObject(mazalMesiba);
	m_3dscreen.CReateCircleLineObject(trsz, colorYom);
	m_3dscreen.TurnShape(90,axis_y, false,true);

	int sShemesh = 17;
	int stepsShem = DiameterSteps(sShemesh);
	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(128,0,0, 0));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(255,128,0,0)
		,fr_zIntensity , (double)sShemesh / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(
		(double)trsz / 2.0,axis_Y, true);


	m_3dscreen.BeginObject(kavimArez);
	m_3dscreen.CReateCircleLineObject(trszArez + 1, RGBT(128,128,128,50),
		1.0,360,6);
	m_3dscreen.TurnShape(90,axis_Z, false,true);

	CreateText(zafon, "ץףונ", RGB(92,32,92));
	m_3dscreen.ShiftObjectCenter(
		(double)trsz / 3.0,axis_X, true);



	m_person.Create();


	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek32::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(arez);

	//m_3dscreen.ResetTranslation();

		double sinNetiya = SinNetyatAliyaYeshara(m_xTurn2, 23.5);
		double angNetiya = asin(sinNetiya) * ToD;

		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnLightPt(0,axis_X, true);
		m_3dscreen.TurnLightPt(270.0,axis_X);
		m_3dscreen.TurnLightPt(angNetiya,axis_Z);
		m_3dscreen.TurnLightPt(m_xTurn4 - m_xTurn3,axis_X);

//	m_3dscreen.TurnShape(m_xTurn3, axis_X, false);

		CFillRectData data;
		data.radius = (double)trszArez / 2.0;
		data.vec2 = 0.4;
		m_3dscreen.FillRect(0,0,stepsArez,stepsArez/2, RGB(24,24,24), 
			fr_lightOppositeDirection, data);

	//m_3dscreen.TurnShape(m_xTurn3, axis_X, false);
	//m_3dscreen.TurnShape(m_xTurn, axis_Z, false);
	//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
	//m_3dscreen.TurnShape(m_xStart, axis_X);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(m_xTurn3, axis_X);
	m_3dscreen.TurnMatrix(m_xTurn, axis_Z);
	m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
	m_3dscreen.TurnMatrix(m_xStart, axis_X);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kavimArez);
	//m_3dscreen.ResetTranslation();
	//m_3dscreen.TurnShape(m_xTurn3, axis_X, false);
	//m_3dscreen.TurnShape(m_xTurn, axis_Z, false);
	//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
	//m_3dscreen.TurnShape(m_xStart, axis_X);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(m_xTurn3, axis_X);
	m_3dscreen.TurnMatrix(m_xTurn, axis_Z);
	m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
	m_3dscreen.TurnMatrix(m_xStart, axis_X);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.BeginObject(mashveHaYom);
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_xTurn, axis_Z, false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		//m_3dscreen.TurnShape(m_xStart, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_Z);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xStart, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(galgalMazalot);
		//m_3dscreen.ResetTranslation();
		double aliyaYeshra = AliyaYeshara(m_xTurn2, 23.5);
		//m_3dscreen.TurnShape(aliyaYeshra + m_xTurn4 - 90, axis_X,false);
		//m_3dscreen.TurnShape(m_xTurn, axis_Z,false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		//m_3dscreen.TurnShape(m_xStart, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(aliyaYeshra + m_xTurn4 - 90, axis_X);
		m_3dscreen.TurnMatrix(m_xTurn, axis_Z);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xStart, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();


	double sinNetya = SinNetyatAliyaYeshara(-m_xTurn2, 23.5);
	double shiftX = sinNetya * (double)trsz / 2.0;
	double shrink = cos(asin(sinNetya));

	m_3dscreen.BeginObject(mazalMesiba);
	if(/*m_buttonId == 0*/true)	{

		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.InitMatrix();


		double vec = ToseffetYom(-m_xTurn2, m_xTurn) * ((double)trsz / 2.0)/* * shrink*/;
		m_3dscreen.FillRect(0,0,trszSteps + 1,3, colorLayla
			,fr_yPaintLessThen, -vec);

		m_3dscreen.ShiftObjectCenter(shiftX, axis_X);
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_Z);
		m_3dscreen.TurnMatrix(m_xTurn, axis_Z);

		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnObjectCenter(m_xStart, axis_X);
		m_3dscreen.TurnMatrix(m_xStart, axis_X);
		m_3dscreen.TurnMatrix(shrink, axis_S);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(asin(-sinNetya) * ToD, axis_Z);
	m_3dscreen.TurnObjectCenter(m_xTurn4, axis_X);
	m_3dscreen.TurnObjectCenter(m_xTurn, axis_Z);
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	m_3dscreen.TurnObjectCenter(m_xStart, axis_X);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_person.Reset();
	m_person.Shrink(0.2);
	m_person.Shift((double)trszArez / 2.0,axis_Y, false);
	m_person.Turn(m_yTurn + 180.0, axis_Y, false);
	m_person.Turn(m_xStart, axis_X);

	m_3dscreen.BeginObject(zafon);
	if(m_yTurn < m_yStart*2 &&  m_yTurn > 0)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_Z);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnObjectCenter(m_xStart, axis_X);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(ofekcir);
	m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(ofek);
	m_3dscreen.Translate3Dto2D(FALSE);


	PaintResult();
	lasty = m_yTurn;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek32::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = (p.x > 3 && p.y > 1)?TRUE:FALSE;


	if((m_bBntDown || m_bRightBDown) && m_bHandCursor )
	{
		double cx = (p.x - m_pt.x);
		double cy = (p.y - m_pt.y);

		if(m_slider2.PtInRect(p, m_xTurn2))
		{
			m_xTurn2 = -m_xTurn2;
		}
		else if(m_sliderHorRc.PtInRect(p))
		{
			m_yTurn = cx /2.5;
			m_yTurn += m_yStart;
		}
		else if(m_bRightBDown)
		{
			m_xTurn3 = cy;
		}
		else if(m_slider.PtInRect(p, m_xTurn) == false)
		{
			m_xTurn4 = cy;
		}

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek32::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_bRightBDown = true;

	CPerek3DBase::OnRButtonDown(nFlags, point);
}

void CPerek32::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_bRightBDown = false;

	CPerek3DBase::OnRButtonUp(nFlags, point);
}

BOOL CPerek32::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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

void CPerek32::InitOnSubHeadButton(void)
{
	lasty = 1000000;

	m_yTurn = m_yStart;
	m_xTurn = m_slider.SetVal(0);
	m_xTurn2 = m_slider2.SetVal(0);
	m_xTurn3 = 0;
	m_xTurn4 = 0;

	PaintSlider();
}

void CPerek32::PaintResult(void)
{
	if(m_buttonId == 1)
	{
		CClientDC dc(this);
		OnPrepareDC(&dc);

	static const double radian = asin(1.0);
	///// Day and night
	double tyom = asin(ToseffetYom(-m_xTurn2, m_xTurn)) / radian * 12.0;//0;

	double orechYom = 12.0 + tyom;
	double orechLayla = 24.0 - orechYom;

	double dakotYom = fmod(orechYom, 1.0);
	double shaotYom = orechYom - dakotYom;
	dakotYom *= 60.0;

	double dakotLayla = fmod(orechLayla, 1.0);
	double shaotLayla = orechLayla - dakotLayla;
	dakotLayla *= 60.0;
	///////////////////////

	/// full days or night

	static const double dayconvert = 364.9 / 2.0;
	double absRochav = fabs(m_xTurn);
	double days = 0.0;
	if(absRochav > 66.5)
	{
		double val = (90.0 - absRochav/* - 66.5*/) / 23.5;
		days = asin(val) / radian * dayconvert;
		days = dayconvert - days;
	}

	//////////////////////

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

		COLORREF txtcolor = m_memDc.SetTextColor(colorYom);
		CRect rc(ipWidth-120, 200, ipWidth, 260);
		m_memDc.FillSolidRect(rc,0);
		CString sTxt;
		sTxt.Format("%s\n%2.0f:%2.0f","יום" ,shaotYom,dakotYom);
		m_memDc.DrawText(sTxt, rc, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);

		m_memDc.SetTextColor(colorLayla);
		CRect rc2(ipWidth-120, 260, ipWidth, 320);
		m_memDc.FillSolidRect(rc2,0);
		sTxt.Format("%s\n%2.0f:%2.0f","לילה" ,shaotLayla,dakotLayla);
		m_memDc.DrawText(sTxt, rc2, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);

		m_memDc.SetTextColor(color1);
		CRect rc3(ipWidth-120, 320, ipWidth, 440);
		m_memDc.FillSolidRect(rc3,0);
		sTxt.Format("%s\n%.0f","ימים שהם רק יום או לילה לפי רוחב המדינה" ,days);
		m_memDc.DrawText(sTxt, rc3, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);


		m_memDc.SetTextColor(txtcolor);
		m_memDc.SelectObject(pFont);

		dc.BitBlt(rc.left,
			rc.top,rc.Width(),rc.Height(),
			&m_memDc,rc.left,rc.top,SRCCOPY);

		dc.BitBlt(rc2.left,
			rc2.top,rc2.Width(),rc2.Height(),
			&m_memDc,rc2.left,rc2.top,SRCCOPY);

		dc.BitBlt(rc3.left,
			rc3.top,rc3.Width(),rc3.Height(),
			&m_memDc,rc3.left,rc3.top,SRCCOPY);
	}
}

void CPerek32::PaintSlider(void)
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

	CFont font;
	VERIFY(font.CreateFont(
		-22,                     // nHeight
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
	rc2.right -= 2;
	m_memDc.DrawText(sTxt, rc2, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);
	rc2.right += 2;

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

		m_memDc.SelectObject(&fontTemp);


		sTxt = "משוה היום";
		m_memDc.SetTextColor(mashveHaYomCol);
		m_memDc.DrawText(sTxt, rcTemp, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);

		rcTemp += pd;
		sTxt = "גלגל המזלות";
		m_memDc.SetTextColor(galgalMazalotCol);
		m_memDc.DrawText(sTxt, rcTemp, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);

		if(m_buttonId == 0)
		{
			rcTemp += pd;
			sTxt = "יום";
			m_memDc.SetTextColor(colorYom);
			m_memDc.DrawText(sTxt, rcTemp, 
				DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);

			rcTemp += pd;
			sTxt = "לילה";
			m_memDc.SetTextColor(colorLayla);
			m_memDc.DrawText(sTxt, rcTemp, 
				DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);
		}
		else
		{
			rcTemp += pd;
			m_memDc.FillSolidRect(rcTemp,0);
			rcTemp += pd;
			m_memDc.FillSolidRect(rcTemp,0);
		}

		dc.BitBlt(ipWidth-left, top, rcTemp.Width(), rcTemp.bottom - top, 
			&m_memDc,ipWidth-left,top,SRCCOPY);

		m_memDc.SelectObject(pFont);
		m_memDc.SetTextColor(txtcolor);
	}

	


	m_slider.InitOnSubHeadButton();
	m_slider2.InitOnSubHeadButton();

	dc.BitBlt(m_sliderHorRc.left,
		m_sliderHorRc.top,m_sliderHorRc.Width(),m_sliderHorRc.Height(),
		&m_memDc,m_sliderHorRc.left,m_sliderHorRc.top,SRCCOPY);

	m_memDc.RestoreDC(n);
}

double CPerek32::ToseffetYom(double mazal, double rochav)
{
	if((mazal == 0.0 || mazal == 180.0) && (rochav != 90.0 && rochav != -90.0))
		return 0;
	else if((mazal == 0.0 || mazal == 180.0) && (rochav == 90.0 || rochav == -90.0))
		return 1.0;

	double sinNetya = SinNetyatAliyaYeshara(mazal, 23.5);
	double b = sin(rochav * D) * sinNetya;
	double yom = cos(asin(sinNetya));
	double tyom = 0;

	if(rochav != 90.0 && rochav != -90.0)
		tyom = 1 / cos(rochav * D) * b;
	else if(b > 0.0)
		return 1.0;
	else 
		return -1.0;

	if((b > 0.0 && tyom < yom) || (b < 0.0 && -tyom < yom))
		tyom = tyom/yom;
	else if(tyom == 0.0)
		return 0.0;
	else if(b > 0.0 )
		tyom = 1.0;
	else 
		tyom = -1.0;


	return tyom;
}
