// Perek39.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek39.h"


// CPerek39

IMPLEMENT_DYNCREATE(CPerek39, CPerek3DBase)

CPerek39::CPerek39()
: trsz(356)
, trszArez(50)
, m_zTurn(0)
, m_xTurn2(0)
, m_sliderHor(this, CRect(0, ipHeight-100,ipWidth,ipHeight),CSlider::simpleHorizontal)
, m_sliderx(this, CRect(0, 0,100,ipHeight-100),CSlider::VerCaptionResultMazalot)
, m_sliderz(this, CRect(100, 0,200,ipHeight-100),CSlider::VerMin90Plus90)
, m_xStart(5)
, m_yStart(10)
, trszSteps(0)
, m_orech(0)
, m_sliderOr(this, CRect(200, 0,450,100),CSlider::simpleHorizontal360)
, m_sliderMY(this, CRect(450, 0,700,100),CSlider::simpleHorizontal360)
, m_MY(0)
, colMazal(RGB(0,0,255))
, colSivuvMasve(RGB(0,255,128))
, orechMash(0)
, m_rcResult(ipWidth-150, 300, ipWidth, 450)
, fine2(1.0)
, trszSteps2(0)
{
	trszSteps = DiameterSteps(trsz);
	trszSteps2 = DiameterSteps(trsz, fine2);
	m_IDstart = ID_P39_1;
	m_IDidx = WT_PEREK_39;
	m_IDX_PEREK = IDX_PEREK_39;
}

CPerek39::~CPerek39()
{
}

BEGIN_MESSAGE_MAP(CPerek39, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P39_1, ID_P39_8, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P39_1, ID_P39_8, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek39 diagnostics

#ifdef _DEBUG
void CPerek39::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek39::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek39 message handlers
enum
{
	arez
	,ofek
	,mashveHaYom
	,galgalMazalot
	,nekudaZaf
	,nekudaDar
	,keshetKtavim
	,keshetKtavimOrech
	,mesibatShemshYomi
	,zafon
	,darom
	,mizrach
	,maarav
	,gimel
	,zayn
	,het
	,he
};

int CPerek39::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	m_sliderz.AddButtonId(0);
	m_sliderz.AddButtonId(1);
	m_sliderz.AddButtonId(6);
	m_sliderz.AddButtonId(7);
	m_sliderz.SetDeflate(3,3,3,3);
	m_sliderz.SetMinMax(0,60);
	m_sliderz.SetRefPoint(bottom);
	m_sliderz.Init();
	m_sliderz.SetVal(32);

	m_sliderx.SetDeflate(3,3,3,3);
	m_sliderx.SetCaption("מזל העולה");
	m_sliderx.Init();

	m_sliderOr.AddButtonId(6);
	m_sliderOr.AddButtonId(7);
	m_sliderOr.SetDeflate(3,3,3,3);
	m_sliderOr.SetCaption("אורך במזלות");
	m_sliderOr.SetMinMax(0,24);
	m_sliderOr.SetFrameColor(colMazal);
	m_sliderOr.SetResultFormat("%.1f");
	m_sliderOr.Init();

	m_sliderMY.AddButtonId(6);
	m_sliderMY.AddButtonId(7);
	m_sliderMY.SetDeflate(3,3,3,3);
	m_sliderMY.SetCaption("סיבוב משוה היום");
	m_sliderMY.SetMinMax(0,30);
	m_sliderMY.SetFrameColor(colSivuvMasve);
	m_sliderMY.SetResultFormat("%.1f");
	m_sliderMY.Init();

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];


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
	m_3dscreen.TurnShape(-90.0,axis_z, false,true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(ofek);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(255,255,255));
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(m_xStart+90.0, axis_x); 
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(mashveHaYom);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(0,0,160));
	m_3dscreen.TurnShape(90.0, axis_y,false,true); 

	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(160,160,0));
	m_3dscreen.TurnShape(90.0, axis_y,false,true); 
	m_3dscreen.TurnShape(23.5, axis_Z,false,true); 

	COLORREF color5 = RGB(160, 128, 96);
	int kotTrsz = DiameterSteps(9);
	m_3dscreen.BeginObject(nekudaZaf);
	m_3dscreen.CreateSphereObject(9, 
		ColBright(color5, -0.65));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color5,0.35)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2.0, axis_X, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(nekudaDar);
	m_3dscreen.CreateSphereObject(9, 
		ColBright(color5, -0.65));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color5,0.35)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz/2.0, axis_X, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(keshetKtavim);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(222,160,94)
		,1.0,180.0);
	m_3dscreen.TurnShape(90.0, axis_X,false,true); 

	m_3dscreen.BeginObject(keshetKtavimOrech);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(94,160,222)
		,1.0,180.0);
	m_3dscreen.TurnShape(90.0, axis_X,false,true); 

	m_3dscreen.BeginObject(mesibatShemshYomi);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(255,0,0), fine2);
	m_3dscreen.TurnShape(90,axis_y, false,true);

	CreateText(zafon, "ץףונ", RGB(92,32,92));
	m_3dscreen.ShiftObjectCenter(
		(double)trsz / 2.0,axis_x, true);
	m_3dscreen.ResetTranslation();

	CreateText(darom, "דרומ", RGB(92,32,92));
	m_3dscreen.ShiftObjectCenter(
		-(double)trsz / 2.0,axis_x, true);
	m_3dscreen.ResetTranslation();

	CreateText(mizrach, "םזרח", RGB(92,32,92));
	m_3dscreen.ShiftObjectCenter(
		-(double)trsz / 2.0+20.0,axis_z, true);
	m_3dscreen.ResetTranslation();

	CreateText(maarav, "םערב", RGB(92,32,92));
	m_3dscreen.ShiftObjectCenter(
		(double)trsz / 2.0-20.0,axis_z, true);
	m_3dscreen.ResetTranslation();

	COLORREF colOtiyot = RGB(0,225,0);
	CreateText(gimel, "ג", colOtiyot);
	m_3dscreen.ShiftObjectCenter(
		-(double)trsz / 2.0,axis_z, true);
	m_3dscreen.ResetTranslation();

	CreateText(zayn, "ז", colOtiyot);
	m_3dscreen.ShiftObjectCenter(
		-(double)trsz / 2.0,axis_z, true);
	m_3dscreen.ResetTranslation();

	CreateText(het, "ח", colOtiyot);
	m_3dscreen.ShiftObjectCenter(
		-(double)trsz / 2.0,axis_z, true);
	m_3dscreen.ResetTranslation();

	CreateText(he, "ה", colOtiyot);
	m_3dscreen.ShiftObjectCenter(
		-(double)(trsz + 2) / 2.0,axis_z, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek39::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	BOOL bAliya = TRUE;
	switch(m_buttonId)
	{
	case 1:
	case 3:
	case 5:
	case 7:
		bAliya = FALSE;
		break;
	}

	double extraTurn = bAliya? 0:180.0;

	double sivuvMashve = SivuvMashve(m_xTurn + extraTurn, m_zTurn);
	double sivkk= SivuvKeshetKtavim(m_xTurn + extraTurn, m_zTurn);
	double netiyatMaz = asin(SinNetyatAliyaYeshara(m_xTurn /* + extraTurn*/, 23.5))*ToD;

	m_3dscreen.BeginObject(arez);
	m_3dscreen.InitMatrix();
	if(m_buttonId < 6)
	{
		m_3dscreen.TurnMatrix(m_xTurn2,axis_X);
		m_3dscreen.TurnMatrix(m_zTurn,axis_z);
		m_3dscreen.TurnMatrix(m_yTurn+m_yStart + extraTurn,axis_y);
		m_3dscreen.TurnMatrix(m_xStart,axis_X);
	}
	else
	{
		m_3dscreen.TurnMatrix(m_xTurn2,axis_X);
		m_3dscreen.TurnMatrix(m_yTurn + extraTurn,axis_y);
	}
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	CFillRectData data2;
	data2.vec = 0.55;
	data2.radius = (double)trsz/2.0;


	m_3dscreen.BeginObject(mashveHaYom);
	if(m_buttonId < 6)
	{
		double haziSivkk = sivkk / 2.0;
		double range = cos(haziSivkk*D) * (double)trsz / 2.0;

		CFillRectData data;
		data.vec = range;

		m_3dscreen.TurnLightPt(0,axis_X, true);
		m_3dscreen.TurnLightPt(haziSivkk + extraTurn,axis_X);
		m_3dscreen.TurnLightPt(m_zTurn,axis_z);
		m_3dscreen.TurnLightPt(m_yTurn+m_yStart + extraTurn,axis_y);
		m_3dscreen.TurnLightPt(m_xStart,axis_X);

		m_3dscreen.ResetTranslation();
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_zTurn,axis_z);
		m_3dscreen.TurnMatrix(m_yTurn+m_yStart + extraTurn,axis_y);
		m_3dscreen.TurnMatrix(m_xStart,axis_X);
		m_3dscreen.Transform(false);
		m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data2);

		m_3dscreen.FillRect(0,0,trszSteps,3, RGB(255,74,74), 
			fr_PaintDiractionRange, data);

		m_3dscreen.TurnShape(0.0, axis_y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn + extraTurn,axis_y);
		m_3dscreen.Transform(false);
		m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data2);
		m_3dscreen.TurnShape(0.0, axis_y);
		m_3dscreen.Translate3Dto2D();
	}


	m_3dscreen.BeginObject(galgalMazalot);
	if(m_buttonId < 6)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(-sivuvMashve,axis_x);
		m_3dscreen.TurnMatrix(m_zTurn,axis_z);
		m_3dscreen.TurnMatrix(m_yTurn+m_yStart + extraTurn,axis_y);
		m_3dscreen.TurnMatrix(m_xStart,axis_X);
		m_3dscreen.Transform(false);
		m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data2);
		m_3dscreen.TurnShape(0.0, axis_y);
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId == 6)
	{
		CFillRectData data3;
		data3.vec = 0.35;
		data3.radius = (double)trsz/2.0;
		CFillRectData data;
		data.vec = cos(D*m_orech/2) * (double)trsz / 2.0;

		double turnBack = AliyaYeshara(m_xTurn- m_orech,23.5);
		double sAliya = 
			SinNetyatAliyaYeshara(m_xTurn- m_orech, 23.5);
		double kizuz = kizuzNetiyaLaOfek(-m_zTurn,sAliya);

		m_3dscreen.TurnLightPt(0,axis_X, true);
		m_3dscreen.TurnLightPt(m_xTurn - m_orech/2.0,axis_X);
		m_3dscreen.TurnLightPt(23.5,axis_z);
		m_3dscreen.TurnLightPt(-turnBack - kizuz - m_MY,axis_x);
		m_3dscreen.TurnLightPt(m_yTurn,axis_y);

		m_3dscreen.ResetTranslation();
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(-turnBack - kizuz - m_MY,axis_x);
		m_3dscreen.TurnMatrix(m_yTurn,axis_y);
		m_3dscreen.Transform(false);
		m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data3);
		m_3dscreen.FillRect(0,0,trszSteps,3, colMazal, 
			fr_PaintDiractionRange, data);
		m_3dscreen.TurnShape(0.0, axis_y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		CFillRectData data3;
		data3.vec = 0.35;
		data3.radius = (double)trsz/2.0;
		CFillRectData data;
		data.vec = cos(D*m_orech/2) * (double)trsz / 2.0;

		double turnBack = AliyaYeshara(m_xTurn- m_orech,23.5);
		double sAliya = 
			SinNetyatAliyaYeshara(m_xTurn - m_orech, 23.5);
		double kizuz = kizuzNetiyaLaOfek(m_zTurn,sAliya);

		m_3dscreen.TurnLightPt(0,axis_X, true);
		m_3dscreen.TurnLightPt(m_xTurn - m_orech/2.0/* + 180.0*/,axis_X);
		m_3dscreen.TurnLightPt(23.5,axis_z);
		m_3dscreen.TurnLightPt(180.0,axis_y);
		m_3dscreen.TurnLightPt(turnBack + kizuz + 180.0 + m_MY,axis_x);
		m_3dscreen.TurnLightPt(m_yTurn,axis_y);

		m_3dscreen.ResetTranslation();
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(180.0,axis_y);
		m_3dscreen.TurnMatrix(turnBack + kizuz + 180.0 + m_MY,axis_x);
		m_3dscreen.TurnMatrix(m_yTurn,axis_y);
		m_3dscreen.Transform(false);
		m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data3);
		m_3dscreen.FillRect(0,0,trszSteps,3, colMazal, 
			fr_PaintDiractionRange, data);
		m_3dscreen.TurnShape(0.0, axis_y);
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(nekudaZaf);
	m_3dscreen.ResetShift();
	if(m_buttonId < 6)
	{
		m_3dscreen.TurnObjectCenter(m_zTurn, axis_z);
		m_3dscreen.TurnObjectCenter(m_yTurn+m_yStart + extraTurn,axis_y);
		m_3dscreen.TurnObjectCenter(m_xStart,axis_X);
	}
	else
	{
		m_3dscreen.TurnObjectCenter(m_yTurn + extraTurn,axis_y);
	}
	m_3dscreen.TurnShape(0.0, axis_y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(nekudaDar);
	m_3dscreen.ResetShift();
	if(m_buttonId < 6)
	{
		m_3dscreen.TurnObjectCenter(m_zTurn, axis_z);
		m_3dscreen.TurnObjectCenter(m_yTurn+m_yStart + extraTurn,axis_y);
		m_3dscreen.TurnObjectCenter(m_xStart,axis_X);
	}
	else
	{
		m_3dscreen.TurnObjectCenter(m_yTurn + extraTurn,axis_y);
	}
	m_3dscreen.TurnShape(0.0, axis_y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(keshetKtavim);
	if(m_buttonId < 6)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(sivkk + extraTurn,axis_x);
		m_3dscreen.TurnMatrix(m_zTurn,axis_z);
		m_3dscreen.TurnMatrix(m_yTurn+m_yStart + extraTurn,axis_y);
		m_3dscreen.TurnMatrix(m_xStart,axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else if(/*m_buttonId >= 6*/false)
	{
		double zTurn = (m_buttonId == 6)? -m_zTurn:m_zTurn;
		double sAliya = 
			SinNetyatAliyaYeshara(m_xTurn, 23.5);
		double kizuz = kizuzNetiyaLaOfek(zTurn,sAliya);

		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix( - kizuz - m_MY + extraTurn, axis_x);
		m_3dscreen.TurnMatrix(m_yTurn + extraTurn,axis_y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(keshetKtavimOrech);
	if(m_buttonId >= 6)
	{
		double zTurn = (m_buttonId == 6)? -m_zTurn:m_zTurn;
		double sAliya = 
			SinNetyatAliyaYeshara(m_xTurn- m_orech, 23.5);
		double kizuz = kizuzNetiyaLaOfek(zTurn,sAliya);

		double alyMazal = AliyaYeshara(m_xTurn,23.5);
		double alyMazalMinOrech = AliyaYeshara(m_xTurn- m_orech,23.5);

		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix( - kizuz + (alyMazal - alyMazalMinOrech) - m_MY + extraTurn, axis_x);
		m_3dscreen.TurnMatrix(m_yTurn + extraTurn,axis_y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(mesibatShemshYomi);
	if(m_buttonId >= 6)
	{

		double zTurn = (m_buttonId == 6)? -m_zTurn:m_zTurn;
		double sAliya = 
			SinNetyatAliyaYeshara(m_xTurn, 23.5);
		double kizuz = kizuzNetiyaLaOfek(zTurn,sAliya);

		double zTurn2 = (m_buttonId == 6)? -m_zTurn:m_zTurn;
		double sAliya2 = 
			SinNetyatAliyaYeshara(m_xTurn  - m_orech, 23.5);
		double kizuz2 = kizuzNetiyaLaOfek(zTurn,sAliya2);

		double alyMazal = AliyaYeshara(m_xTurn,23.5);
		double alyMazalMinOrech = AliyaYeshara(m_xTurn- m_orech,23.5);
		kizuz2 = -kizuz2 + (alyMazal - alyMazalMinOrech);

		orechMash = -kizuz - kizuz2;
		while(orechMash > 360.0)
			orechMash -= 360.0;
		while(orechMash < 0.0)
			orechMash += 360.0;

		double sinNetya = SinNetyatAliyaYeshara(m_xTurn + extraTurn, 23.5);
		double shiftX = sinNetya * (double)trsz / 2.0;
		double shrink = cos(asin(sinNetya));

		CFillRectData data;
		data.vec = fabs(cos(D*orechMash/2) * shrink * (double)trsz / 2.0);

		m_3dscreen.TurnLightPt(0,axis_X, true);
		if(m_buttonId == 6)
			m_3dscreen.TurnLightPt(-(kizuz + orechMash/2.0) + 180 - m_MY,axis_X);
		else
			m_3dscreen.TurnLightPt((kizuz + orechMash/2.0) + 180 + m_MY,axis_X);
		m_3dscreen.TurnLightPt(m_yTurn,axis_y);

		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.InitMatrix();
		m_3dscreen.ShiftObjectCenter(shiftX, axis_X);

		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(shrink+0.001, axis_S);
		m_3dscreen.Transform(false);
		m_3dscreen.FillRect(0,0,trszSteps2,3, 0,fr_zIntensityAll, data2);
		m_3dscreen.FillRect(0,0,trszSteps2,3, colSivuvMasve, 
			fr_PaintDiractionRange, data);
		m_3dscreen.TurnShape(0.0, axis_y);
		m_3dscreen.Translate3Dto2D();
		PaintResult();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(zafon);
	m_3dscreen.ResetShift();
	if(m_buttonId < 6)
	{
		m_3dscreen.TurnObjectCenter(m_zTurn + 5, axis_z);
		m_3dscreen.TurnObjectCenter(m_yTurn+m_yStart + extraTurn,axis_y);
		m_3dscreen.TurnObjectCenter(m_xStart,axis_X);
	}
	else
	{
		m_3dscreen.TurnObjectCenter( 5, axis_z);
		m_3dscreen.TurnObjectCenter(m_yTurn + extraTurn,axis_y);
	}
	m_3dscreen.TurnShape(0.0, axis_y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(darom);
	m_3dscreen.ResetShift();
	if(m_buttonId < 6)
	{
		m_3dscreen.TurnObjectCenter(m_zTurn - 5, axis_z);
		m_3dscreen.TurnObjectCenter(m_yTurn+m_yStart + extraTurn,axis_y);
		m_3dscreen.TurnObjectCenter(m_xStart,axis_X);
	}
	else
	{
		m_3dscreen.TurnObjectCenter( -5, axis_z);
		m_3dscreen.TurnObjectCenter(m_yTurn + extraTurn,axis_y);
	}
	m_3dscreen.TurnShape(0.0, axis_y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(mizrach);
	m_3dscreen.ResetShift();
	if(m_buttonId < 6)
	{
		m_3dscreen.TurnObjectCenter(m_yTurn+m_yStart + extraTurn-8,axis_y);
		m_3dscreen.TurnObjectCenter(m_xStart,axis_X);
		m_3dscreen.ShiftObjectCenter(-15,axis_y);
	}
	else
	{
		m_3dscreen.TurnObjectCenter(m_yTurn + extraTurn-8,axis_y);
		m_3dscreen.ShiftObjectCenter(-15,axis_y);
	}
	m_3dscreen.TurnShape(0.0, axis_y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(maarav);
	m_3dscreen.ResetShift();
	if(m_buttonId < 6)
	{
		m_3dscreen.TurnObjectCenter(m_yTurn+m_yStart + extraTurn-12,axis_y);
		m_3dscreen.TurnObjectCenter(m_xStart,axis_X);
		m_3dscreen.ShiftObjectCenter(-15,axis_y);
	}
	else
	{
		m_3dscreen.TurnObjectCenter(m_yTurn + extraTurn-8,axis_y);
		m_3dscreen.ShiftObjectCenter(-25,axis_y);
	}
	m_3dscreen.TurnShape(0.0, axis_y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(gimel);
	if(m_buttonId >= 2 && m_buttonId < 6)
	{
		double toside = (m_buttonId < 4)? 3.0:-3.0;
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(netiyatMaz + toside,axis_Y);
		m_3dscreen.TurnObjectCenter(sivkk + extraTurn + toside,axis_x);
		m_3dscreen.TurnObjectCenter(m_zTurn,axis_z);
		m_3dscreen.TurnObjectCenter(m_yTurn+m_yStart + extraTurn,axis_y);
		m_3dscreen.TurnObjectCenter(m_xStart,axis_X);
		m_3dscreen.TurnShape(0.0, axis_y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(zayn);
	if(m_buttonId >= 2 && m_buttonId < 6)
	{
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn+m_yStart,axis_y);
		m_3dscreen.TurnObjectCenter(m_xStart-2.0,axis_X);
		m_3dscreen.TurnShape(0.0, axis_y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(het);
	if(m_buttonId >= 2 && m_buttonId < 6)
	{
		double toside = (m_buttonId%2)? -2.5:2.5;
		if(m_buttonId > 3)
			toside = - toside;
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(sivkk + extraTurn + toside,axis_x);
		m_3dscreen.TurnObjectCenter(m_zTurn,axis_z);
		m_3dscreen.TurnObjectCenter(m_yTurn+m_yStart + extraTurn,axis_y);
		m_3dscreen.TurnObjectCenter(m_xStart,axis_X);
		m_3dscreen.TurnShape(0.0, axis_y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(he);
	if(m_buttonId >= 2 && m_buttonId < 6)
	{
		double fix = (m_buttonId > 3)? 180.0:0.0;
		//double toside = (m_buttonId%2)? -2.5:2.5;
		//if(m_buttonId > 3)
		//	toside = - toside;
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(-sivuvMashve + fix - 4.0,axis_x);
		m_3dscreen.TurnObjectCenter(m_zTurn,axis_z);
		m_3dscreen.TurnObjectCenter(m_yTurn+m_yStart + extraTurn,axis_y);
		m_3dscreen.TurnObjectCenter(m_xStart,axis_X);
		m_3dscreen.TurnShape(0.0, axis_y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	CFillRectData data3;
	data3.vec = 0.8;
	data3.radius = (double)trsz/2.0;

	m_3dscreen.BeginObject(ofek);
	if(m_buttonId < 6)
	{
		m_3dscreen.Translate3Dto2D(FALSE);
	}
	else
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(90,axis_x);
		m_3dscreen.TurnMatrix(-m_zTurn,axis_z);
		m_3dscreen.TurnMatrix(m_yTurn + extraTurn,axis_y);
		m_3dscreen.Transform(false);
		m_3dscreen.FillRect(0,0,trszSteps,3, 0,fr_zIntensityAll, data3);
		m_3dscreen.TurnShape(0.0, axis_y);
		m_3dscreen.Translate3Dto2D();
	}


	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek39::OnMouseMove(UINT nFlags, CPoint point)
{

	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = (p.x > 3 && p.y > 1 && p.x < ipWidth)?TRUE:FALSE;

	if( m_bBntDown && m_bHandCursor )
	{
		double cy = (p.y - m_pt.y);

		switch(m_buttonId)
		{
		case 0:
		case 1:
			if(m_sliderHor.PtInRect(p, m_yTurn) == false &&
				m_sliderx.PtInRect(p, m_xTurn) == false  &&
				m_sliderz.PtInRect(p, m_zTurn) == false)			
				m_xTurn2 = cy ;
			break;
		case 6:
		case 7:
			if(m_sliderHor.PtInRect(p, m_yTurn) == false &&
				m_sliderx.PtInRect(p, m_xTurn) == false  &&
				m_sliderOr.PtInRect(p, m_orech) == false  &&
				m_sliderMY.PtInRect(p, m_MY) == false  &&
				m_sliderz.PtInRect(p, m_zTurn) == false)			
				m_xTurn2 = cy ;
			break;
		default:
			if(m_sliderHor.PtInRect(p, m_yTurn) == false &&
				m_sliderx.PtInRect(p, m_xTurn) == false)			
				m_xTurn2 = cy;
			break;
		}

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

BOOL CPerek39::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_EXTRA_DRAW:
		PaintSlider();
		return TRUE;
	}

	return CPerek3DBase::OnWndMsg(message, wParam, lParam, pResult);
}

void CPerek39::InitOnSubHeadButton(void)
{
	switch(m_buttonId)
	{
	case 0:
	case 1:
		m_sliderx.SetMinMaxRange(0,360);
		m_zTurn = m_sliderz.SetVal(32);
		break;
	case 2:
		m_sliderx.SetMinMaxRange(0,180);
		m_xTurn = m_sliderx.SetVal(0);
		m_zTurn = 32;
		break;
	case 3:
		m_sliderx.SetMinMaxRange(0,180);
		m_xTurn = m_sliderx.SetVal(0);
		m_zTurn = 32;
		break;
	case 4:
		m_sliderx.SetMinMaxRange(180,360);
		m_xTurn = m_sliderx.SetVal(180);
		m_zTurn = 32;
		break;
	case 5:
		m_sliderx.SetMinMaxRange(180,360);
		m_xTurn = m_sliderx.SetVal(180);
		m_zTurn = 32;
		break;
	default:
		m_sliderx.SetMinMaxRange(0,360);
		m_zTurn = m_sliderz.SetVal(32);
		m_yTurn = m_sliderHor.SetVal(0);
		m_orech = m_sliderOr.SetVal(15);
		m_MY = m_sliderMY.SetVal(0);
		break;
	}

	m_3dscreen.ClearScreen();
	switch(m_buttonId)
	{
	case 6:
	case 7:
		m_3dscreen.BeginObject(ofek);
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(90.0, axis_x); 
		m_3dscreen.Translate3Dto2D();
		break;
	default:
		m_3dscreen.BeginObject(ofek);
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(m_xStart+90.0, axis_x); 
		m_3dscreen.Translate3Dto2D();
		break;
	}

	PaintSlider();
}

void CPerek39::PaintSlider(void)
{
	m_sliderHor.InitOnSubHeadButton();
	m_sliderx.InitOnSubHeadButton();
	if(m_sliderz.IsOneOfId(m_buttonId))
		m_sliderz.InitOnSubHeadButton();
	if(m_sliderOr.IsOneOfId(m_buttonId))
		m_sliderOr.InitOnSubHeadButton();
	if(m_sliderMY.IsOneOfId(m_buttonId))
		m_sliderMY.InitOnSubHeadButton();

	PaintResult();
}

double CPerek39::SivuvMashve(double angMazal, double rohavMedina)
{
	double ehet = AliyaYeshara(angMazal, 23.5);
	double gz = asin(sin(angMazal*D) * sin(23.5*D) / sin((90.0-rohavMedina)*D)) * ToD;
	double zhet = AliyaYeshara(gz, 90.0-rohavMedina);
	double zhe = ehet - zhet;
	if(zhe < 0.0)
		zhe += 360.0;
	//TRACE("ehet = %f, zhet = %f, zhe = %f\n",ehet, zhet, zhe);
	return zhe;
}

double CPerek39::SivuvKeshetKtavim(double angMazal, double angRohavMedina)
{
	double gz = asin(sin(angMazal*D) * sin(23.5*D) / sin((90.0-angRohavMedina)*D)) * ToD;
	double zhet = AliyaYeshara(gz, 90.0-angRohavMedina);
	if(zhet > 180.0)
		zhet -= 360.0;
	return zhet;
}

void CPerek39::PaintResult(void)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	m_memDc.FillSolidRect(m_rcResult, 0);

	if(m_buttonId >= 6)
	{
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


		COLORREF txtcolor = m_memDc.SetTextColor(colSivuvMasve);
		m_memDc.SetBkMode(TRANSPARENT);
		CFont* pFont = m_memDc.SelectObject(&font);
		CString sTxt, sMsg;

		sMsg = (m_buttonId == 6)?"משוה העולה":"משוה השוקע";

		double temp = 360.0 - orechMash;
		sTxt.Format("%s\n%.1f",sMsg, temp);

		m_memDc.DrawText(sTxt, m_rcResult, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);

		m_memDc.SetTextColor(txtcolor);
		m_memDc.SelectObject(pFont);
	}


	dc.BitBlt(m_rcResult.left,m_rcResult.top,m_rcResult.Width(),m_rcResult.Height(),
		&m_memDc, m_rcResult.left,m_rcResult.top, SRCCOPY);
}
