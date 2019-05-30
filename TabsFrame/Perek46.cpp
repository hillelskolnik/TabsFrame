// Perek46.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek46.h"


// CPerek46

IMPLEMENT_DYNCREATE(CPerek46, CPerek3DBase)

CPerek46::CPerek46()
: trszArez(9)
, m_slider(this, CRect(0, 0,100,ipHeight),CSlider::VerCaptionResultMazalot)
, m_slider2(this, CRect(100, 0,200,ipHeight),CSlider::VerCaptionResultMazalot)
, m_rcRes(ipWidth - 110, 150, ipWidth, 400)
, m_xTurn2(0)
, trsz(380)
, colEmzai(RGB(190,0,0))
, colAmity(RGB(255,255,0))
, trszGova(30)
, colGalgalMazalot(RGB(160,22,188))
, trszGalgalShemesh(310)
, govaRelasion(18)
, colOtiyot(RGB(90,222,36))
, color0(0)
, menatHaMslul(0)
, m_shemeshAmity(0)
, colMenat(RGB(0,255,0))
, colMaslul(RGB(64,255,128))
, m_maslul(0)
{
	trszGova = (int)((double)trszGalgalShemesh / govaRelasion);
	trszArez = trszGova / 2;
	m_IDstart = ID_P46_1;
	m_IDidx = WT_PEREK_46;
	m_IDX_PEREK = IDX_PEREK_46;
}

CPerek46::~CPerek46()
{
}

BEGIN_MESSAGE_MAP(CPerek46, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P46_1, ID_P46_1, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P46_1, ID_P46_1, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CPerek46 diagnostics

#ifdef _DEBUG
void CPerek46::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek46::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek46 message handlers

enum
{
	arez
	,galgalMazalot
	,gova
	,emzai
	,emzaiArez
	,emzaiGova
	,amity
	,shemesh
	,nekudatGova
	,lineVer
	,lineHor
	,Otiyot
};

int CPerek46::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CMyFBitmap bm11;
	CString path = theApp.m_appPath + "Images\\et.bmp";
	CImage image22;
	image22.Load(path);
	bm11.CreateMyCompatibleBitmap(NULL, image22.GetWidth(),
		image22.GetHeight());
	image22.BitBlt(bm11.operator CDC *()->GetSafeHdc(),
		CPoint(0,0));

	m_slider.SetDeflate(3,3,3,3);
	m_slider.SetCaption("מקום השמש האמצעי");
	m_slider.SetFrameColor(colEmzai);
	m_slider.SetFontSize(-16);
	m_slider.SetResultFormat("%.1f");
	m_slider.Init();

	m_slider2.SetDeflate(3,3,3,3);
	m_slider2.SetCaption("גובה השמש");
	m_slider2.SetFrameColor(colAmity);
	m_slider2.SetFontSize(-16);
	m_slider2.SetResultFormat("%.1f");
	m_slider2.Init();


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
	m_3dscreen.CreateSphereObject(trszArez, 0);
	m_3dscreen.BitmapToObject(bm11, RGBT2(0,0));
	m_3dscreen.TurnShape(55.0,axis_y, false,true);
	m_3dscreen.TurnShape(90.0,axis_x, false,true);
	m_3dscreen.ResetTranslation();


	int width = 20;
	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.CreateFlatSpiralObject(1080,width, -width, trsz/2 - width,360.0, 
		colGalgalMazalot);
	m_3dscreen.FillRect(0,1,1080,width-2, RGB(0,12,0));

	m_3dscreen.BeginObject(gova);
	m_3dscreen.CReateCircleLineObject(trszGova, RGB(255,32,128));
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(0.0,axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(emzai);
	m_3dscreen.CReateCircleLineObject(trszGalgalShemesh, RGB(128,0,255));
	m_3dscreen.ResetTranslation();
	m_3dscreen.ShiftObjectCenter((double)trszGova/2.0,axis_X,true);

	m_3dscreen.BeginObject(emzaiArez);
	m_3dscreen.CreatObjectPixselMap((trsz- 8)/2,1,colEmzai);
	m_3dscreen.ShiftObjectCenter((double)(trsz- 8) / 4.0, axis_X, true);

	m_3dscreen.BeginObject(amity);
	m_3dscreen.CreatObjectPixselMap((trsz)/2,1,colAmity);
	m_3dscreen.ShiftObjectCenter((double)(trsz) / 4.0, axis_X, true);

	m_3dscreen.BeginObject(emzaiGova);
	m_3dscreen.CreatObjectPixselMap(trszGalgalShemesh/2,1,colEmzai);
	m_3dscreen.ShiftObjectCenter((double)trszGalgalShemesh / 4.0, axis_X, true);

	int sShemesh = 13;
	int stepsShem = DiameterSteps(sShemesh);
	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(128,0,0, 60));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(255,128,0,60)
		,fr_zIntensity , (double)sShemesh / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(
		(double)trszGalgalShemesh / 2.0,axis_X, true);
	m_3dscreen.ResetTranslation();


	int sNekudatGova = 5;
	int stepsNekudatGova = DiameterSteps(sNekudatGova);
	m_3dscreen.BeginObject(nekudatGova);
	m_3dscreen.CreateSphereObject(sNekudatGova, 
		RGBT(128,0,0, 0));
	m_3dscreen.FillRect(0,0,stepsNekudatGova, stepsNekudatGova/2, RGBT(255,0,0,0)
		,fr_zIntensity , (double)sNekudatGova / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(
		(double)trszGova / 2.0,axis_X, true);
	m_3dscreen.ResetTranslation();


	m_3dscreen.BeginObject(lineVer);
	m_3dscreen.CreatObjectPixselMap(1,trsz-width*2,colGalgalMazalot);

	m_3dscreen.BeginObject(lineHor);
	m_3dscreen.CreatObjectPixselMap(trsz-width*2,1,colGalgalMazalot);

	int otiyot = Otiyot;
	CreateText(otiyot, "א", color0);
	m_3dscreen.ShiftObjectCenter(
		(double)trszGova / 2.0 + (double)trszGalgalShemesh / 2.0 - 14,axis_X,true);
	m_3dscreen.ShiftObjectCenter(
		-8,axis_y,true);
	m_3dscreen.ResetTranslation();

	otiyot++;
	CreateText(otiyot, "ז", colOtiyot);
	m_3dscreen.ShiftObjectCenter(
		(double)trszGova / 2.0 - (double)trszGalgalShemesh / 2.0 - 8,axis_X,true);
	m_3dscreen.ShiftObjectCenter(
		-8,axis_y,true);
	m_3dscreen.ResetTranslation();	

	otiyot++;
	CreateText(otiyot, "ן", colOtiyot);
	m_3dscreen.ShiftObjectCenter(
		(double)trszGalgalShemesh / 2.0 + 8,axis_x, true);
	m_3dscreen.ResetTranslation();


	otiyot++;
	CreateText(otiyot, "ע", colOtiyot);
	m_3dscreen.ShiftObjectCenter(
		(double)trszGalgalShemesh / 2.0 + 8,axis_x, true);
	m_3dscreen.ResetTranslation();


	otiyot++;
	CreateText(otiyot, "ט", colOtiyot);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ShiftObjectCenter(
		- 12,axis_y);
	m_3dscreen.ShiftObjectCenter(
		12,axis_x);
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek46::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(arez);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.ResetTranslation();

	m_maslul = CalcMaslul();

	double maslulHaShemesh = (m_xTurn - m_xTurn2);
	menatHaMslul = -CalcMenatHaMslul(maslulHaShemesh * D);
	double menatHaMslul2 = -CalcMenatHaMslul(maslulHaShemesh * D, govaRelasion);

	
	double xTurn = AdjusShemesAmity(ShemeshAmity2Emzai(m_shemeshAmity, m_xTurn2, govaRelasion));
	double govax = cos(m_xTurn2 * D) * (double)trszGova / 2.0;
	double govay = sin(m_xTurn2 * D) * (double)trszGova / 2.0;

	m_3dscreen.TurnLightPt(0,axis_X, true);
	m_3dscreen.TurnLightPt(90.0,axis_Y);
	m_3dscreen.TurnLightPt(xTurn + menatHaMslul/2,axis_Z);

	int stepsAmity = (int)(m_shemeshAmity * 3.0);
	if(stepsAmity < 0)
	{
		stepsAmity += 1080;
	}
	m_3dscreen.FillRect(0,5, stepsAmity,4, colAmity, fr_paintTranslated);
	int stepsEmzai = (int)(xTurn * 3.0);
	int stepMenat = (int)(menatHaMslul2 * 3.0);
	m_3dscreen.FillRect(0,9, stepsEmzai,4, colEmzai, fr_paintTranslated);
	if(stepMenat < 0)
	{
		stepMenat = -stepMenat;
		stepsEmzai -=stepMenat;
		if(stepsEmzai < 0)
			stepsEmzai += 1080;
	}
	m_3dscreen.FillRect(stepsEmzai,13,stepMenat,6, colMenat, fr_paintTranslated);
	if((stepsEmzai + stepMenat) > 1080)
	{
		stepMenat = (stepsEmzai + stepMenat) - 1080;
		m_3dscreen.FillRect(0,13,stepMenat,6, colMenat, fr_paintTranslated);
	}

	int stepMaslul = (int)(m_maslul * 3.0);
	int startGova = (int)(m_xTurn2 * 3.0);
	m_3dscreen.FillRect(startGova,1,stepMaslul,4, colMaslul, fr_paintTranslated);
	if((stepMaslul + startGova) > 1080)
	{
		stepMaslul = (stepMaslul + startGova) - 1080;
		m_3dscreen.FillRect(0,1,stepMaslul,4, colMaslul, fr_paintTranslated);
	}
	m_3dscreen.TurnShape(0.0, axis_y);
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.BeginObject(gova);
	m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(emzai);
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(m_xTurn2, axis_Z);
	m_3dscreen.TurnShape(0.0, axis_Z);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(emzaiArez);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(xTurn, axis_Z);
	m_3dscreen.TurnShape(xTurn, axis_Z);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(amity);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(m_shemeshAmity, axis_Z);
	m_3dscreen.TurnShape(m_shemeshAmity, axis_Z);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(emzaiGova);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(xTurn, axis_Z);
	m_3dscreen.ShiftObjectCenter(govax, axis_X);
	m_3dscreen.ShiftObjectCenter(govay, axis_Y);
	m_3dscreen.TurnShape(xTurn, axis_Z);
	m_3dscreen.Translate3Dto2D();



	m_3dscreen.BeginObject(lineVer);
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(m_xTurn2, axis_Z);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(lineHor);
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(m_xTurn2, axis_Z);
	m_3dscreen.Translate3Dto2D();


	int otiyot = Otiyot;
	for(; otiyot < (Otiyot + 2); ++otiyot)
	{
		m_3dscreen.BeginObject(otiyot);
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn2, axis_Z);
		m_3dscreen.TurnShape(0.0, axis_Z);
		m_3dscreen.Translate3Dto2D();
	}

	double fEmzai = m_xTurn2+90.0;//ShemeshAmity2Emzai(m_xTurn2+90.0, m_xTurn2, govaRelasion);
	m_3dscreen.BeginObject(otiyot);
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(fEmzai, axis_Z);
	m_3dscreen.ShiftObjectCenter(govax, axis_X);
	m_3dscreen.ShiftObjectCenter(govay, axis_Y);
	m_3dscreen.TurnShape(0.0, axis_Z);
	m_3dscreen.Translate3Dto2D();

	fEmzai = m_xTurn2+270.0;//AdjusShemesAmity(ShemeshAmity2Emzai(m_xTurn2+270.0, m_xTurn2, govaRelasion));
	m_3dscreen.BeginObject(++otiyot);
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(fEmzai, axis_Z);
	m_3dscreen.ShiftObjectCenter(govax, axis_X);
	m_3dscreen.ShiftObjectCenter(govay, axis_Y);
	m_3dscreen.TurnShape(0.0, axis_Z);
	m_3dscreen.Translate3Dto2D();

	otiyot++;
	m_3dscreen.BeginObject(otiyot);
	m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(xTurn, axis_Z);
	m_3dscreen.ShiftObjectCenter(govax, axis_X);
	m_3dscreen.ShiftObjectCenter(govay, axis_Y);
	m_3dscreen.TurnShape(0.0, axis_Z);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(nekudatGova);
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(m_xTurn2, axis_Z);
	m_3dscreen.TurnShape(0.0, axis_Z);
	m_3dscreen.Translate3Dto2D();

	PaintResult();
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek46::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = (p.x > 3 && p.y > 1 && p.x < ipWidth)?TRUE:FALSE;

	if( m_bBntDown && m_bHandCursor )
	{
		if(m_slider.PtInRect(p, m_xTurn))
		{
			m_shemeshAmity = ShemesAmity(m_xTurn, m_xTurn2);
			m_shemeshAmity = AdjusShemesAmity(m_shemeshAmity);
		}
		else if(m_slider2.PtInRect(p, m_xTurn2))
		{
			m_shemeshAmity = ShemesAmity(m_xTurn, m_xTurn2);
			m_shemeshAmity = AdjusShemesAmity(m_shemeshAmity);
		}
		else
		{
			m_xTurn2 = PointsToAng(m_pt, p);
			if(m_xTurn2 < 0.0)
				m_xTurn2 += 360.0;
			m_slider2.SetVal(m_xTurn2);
			m_shemeshAmity = ShemesAmity(m_xTurn, m_xTurn2);
			m_shemeshAmity = AdjusShemesAmity(m_shemeshAmity);
		}

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

BOOL CPerek46::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_EXTRA_DRAW:
		PaintSlider();
		PaintResult();
		Do3DPaint();
		return TRUE;
	}

	return CPerek3DBase::OnWndMsg(message, wParam, lParam, pResult);
}

void CPerek46::PaintSlider(void)
{
	m_slider.InitOnSubHeadButton();
	m_slider2.InitOnSubHeadButton();
}

void CPerek46::PaintResult(void)
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

	COLORREF txtcolor = m_memDc.SetTextColor(colEmzai);
	m_memDc.SetBkMode(TRANSPARENT);
	CFont* pFont = m_memDc.SelectObject(&font);
	CString sTxt, sMsg;

	sMsg = "שמש אמצעי";

	sTxt.Format("%s\n%s",sMsg, MaalotHalakim(m_xTurn));

	int h = m_memDc.DrawText(sTxt, rc, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/) + 10;

	rc.top = m_rcRes.top +h;

	sMsg = "שמש אמיתי";
	sTxt.Format("%s\n%s",sMsg, MaalotHalakim(m_shemeshAmity));

	m_memDc.SetTextColor(colAmity);
	h += m_memDc.DrawText(sTxt, rc, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/) + 10;

	rc.top = m_rcRes.top +h;



	CString sTosseffetHessur;
	if(menatHaMslul > 0.000001)
		sTosseffetHessur = "הוספה";
	else if(menatHaMslul < -0.000001)
		sTosseffetHessur = "חסור";

	sMsg = "מנת המסלול";
	sTxt.Format("%s\n%s\n%s",sMsg, MaalotHalakim(menatHaMslul), sTosseffetHessur);

	m_memDc.SetTextColor(colMenat);
	h += m_memDc.DrawText(sTxt, rc, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/) + 10;

	rc.top = m_rcRes.top +h;

	sMsg = "גובה השמש";
	sTxt.Format("%s\n%s",sMsg, MaalotHalakim(m_xTurn2));

	m_memDc.SetTextColor(color0);
	h += m_memDc.DrawText(sTxt, rc, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/) + 10;

	rc.top = m_rcRes.top +h;

	sMsg = "מסלול השמש";


	double xTurn = m_xTurn;
	if(xTurn < m_xTurn2)
		xTurn += 360.0;
	double maslul = xTurn - m_xTurn2;

	sTxt.Format("%s\n%s",sMsg, MaalotHalakim(maslul));

	m_memDc.SetTextColor(colMaslul);
	h += m_memDc.DrawText(sTxt, rc, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/) + 10;

	rc.top = m_rcRes.top +h;


	rc = m_rcRes;

	rc.bottom = rc.top + h;

	if(rc.bottom > m_rcRes.bottom)
		m_rcRes.bottom = rc.bottom;

	m_memDc.SetTextColor(txtcolor);
	m_memDc.SelectObject(pFont);

	dc.BitBlt(rc.left,rc.top,rc.Width(),m_rcRes.Height(),
		&m_memDc, rc.left,rc.top, SRCCOPY);
}

void CPerek46::InitOnSubHeadButton(void)
{
	m_xTurn2 = m_slider2.SetVal(90.0);
	m_xTurn = m_slider.SetVal(90.0);
	m_shemeshAmity = ShemesAmity(m_xTurn, m_xTurn2);
	m_shemeshAmity = AdjusShemesAmity(m_shemeshAmity);
	PaintSlider();
}

double CPerek46::CalcMaslul(void)
{
	double xTurn = AdjusShemesAmity(ShemeshAmity2Emzai(m_shemeshAmity, m_xTurn2, govaRelasion));
	if(xTurn < m_xTurn2)
		xTurn += 360.0;
	return xTurn - m_xTurn2;
}
