// Perek19.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek19.h"


// CPerek19
const int trsz = 270;

IMPLEMENT_DYNCREATE(CPerek19, CPerek3DBase)

CPerek19::CPerek19()
: lasty(0)
, m_nMazalotStarsSize(0)
{
	m_IDstart = ID_P19_1;
	m_IDidx = WT_PEREK_19;
	m_IDX_PEREK = IDX_PEREK_19;
}

CPerek19::~CPerek19()
{
}

BEGIN_MESSAGE_MAP(CPerek19, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P19_1, ID_P19_12, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P19_1, ID_P19_12, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


// CPerek19 drawing

// CPerek19 diagnostics

#ifdef _DEBUG
void CPerek19::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek19::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek19 message handlers
const double xStart = 15;
const double yStart = 5;
const int timerElaps = 60;



enum
{
	ofek
	,galgalMazalot
	,galgalMazalot2
	,mizrach
	,maarav
	,darom
	,zafon
	,galgalHayomy
	,galgalHayomyShetach
	,sky
	,helekD
	,helekZ
	,kotevZ
	,kotevD
	,kotevMaa
	,kotevMiz
	,ofanHzi
	,ofanHziShetach
	,zavitYeshara
	,haziMizMaa
};

int CPerek19::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CMyFBitmap bm11;
	CString path = theApp.m_appPath + "Images\\MazalotStars.BMP";
	CImage image22;
	image22.Load(path);
	bm11.CreateMyCompatibleBitmap(NULL, image22.GetWidth(),
		image22.GetHeight());
	image22.BitBlt(bm11.operator CDC *()->GetSafeHdc(),
		CPoint(0,0));
	m_nMazalotStarsSize = image22.GetWidth();

	CMyFBitmap bm22;
	path = theApp.m_appPath + "Images\\MazalotStars2.BMP";
	CImage image44;
	image44.Load(path);
	bm22.CreateMyCompatibleBitmap(NULL, image44.GetWidth(),
		image44.GetHeight());
	image44.BitBlt(bm22.operator CDC *()->GetSafeHdc(),
		CPoint(0,0));

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];

	CClientDC dc(this);
	COLORREF color0 = cp.paragraphs[0].color;
	COLORREF color1 = cp.paragraphs[1].color;
	COLORREF color2 = cp.paragraphs[2].color;
	COLORREF color3 = cp.paragraphs[3].color;
	COLORREF color4 = cp.paragraphs[4].color;
	COLORREF color5 = cp.paragraphs[5].color;
	COLORREF color6 = cp.paragraphs[6].color;
	COLORREF color7 = cp.paragraphs[7].color;
	COLORREF color8 = cp.paragraphs[8].color;
	COLORREF color9 = cp.paragraphs[9].color;
	COLORREF color10 = cp.paragraphs[10].color;
	COLORREF color11 = cp.paragraphs[11].color;

	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 45.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();


	CFont font;
	VERIFY(font.CreateFont(
		-12,                     // nHeight
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

	CString sMiz = "מזרח";
	CString sMaa = "מערב";
	CString sDar = "דרום";
	CString sZaf = "צפון";
	CString sHZaf = "חלק צפוני";
	CString sHDar = "חלק דרומי";
	int nMiz = dc.GetTextExtent(sMiz).cx;
	int nSise = nMiz;
	int nMaa = dc.GetTextExtent(sMaa).cx;
	nSise = max(nSise,nMaa);
	int nDar = dc.GetTextExtent(sDar).cx;
	nSise = max(nSise,nDar);
	int nZaf = dc.GetTextExtent(sZaf).cx;
	nSise = max(nSise,nZaf);
	int nHZaf = dc.GetTextExtent(sHZaf).cx;
	nSise = max(nSise,nHZaf);
	int nHDar = dc.GetTextExtent(sHDar).cx;
	nSise = max(nSise,nHDar);
	int nY = dc.GetTextExtent(sZaf).cy;
	int bmH = 18;
	nY = (bmH-nY)/2;
	nSise += 4;

	CMyFBitmap bmKiv;
	bmKiv.CreateMyCompatibleBitmap(&dc,nSise,bmH,0);
	int nX = (nSise-nMiz)/2;
	CDC* pDirDc = bmKiv.GetMyPaintDC();
	int n = pDirDc->SaveDC();
	pDirDc->SelectObject(&font);
	pDirDc->SetBkMode(TRANSPARENT);
	pDirDc->SetTextColor(color0);
	pDirDc->TextOutA(nX,nY,sMiz);

	double dTrsx = trsz;
	m_3dscreen.BeginObject(mizrach);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter(-(dTrsx/2 + 3) , axis_Z, true);
	
	nX = (nSise-nMaa)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SetTextColor(color1);
	pDirDc->TextOutA(nX,nY,sMaa);

	m_3dscreen.BeginObject(maarav);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter((dTrsx/2 + 3) , axis_Z, true);

	nX = (nSise-nDar)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SetTextColor(color2);
	pDirDc->TextOutA(nX,nY,sDar);

	m_3dscreen.BeginObject(darom);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter(-(dTrsx/2 + nSise) , axis_X, true);

	nX = (nSise-nZaf)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SetTextColor(color3);
	pDirDc->TextOutA(nX,nY,sZaf);

	m_3dscreen.BeginObject(zafon);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter((dTrsx/2 + nSise) , axis_X, true);

	nX = (nSise-nHZaf)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SetTextColor(color4);
	pDirDc->TextOutA(nX,nY,sHZaf);

	m_3dscreen.BeginObject(helekZ);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter((dTrsx/3.0 + 0) , axis_X, true);
	m_3dscreen.TurnObjectCenter(10 , axis_Z, true);

	nX = (nSise-nHZaf)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SetTextColor(color4);
	pDirDc->TextOutA(nX,nY,sHDar);

	m_3dscreen.BeginObject(helekD);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter(-(dTrsx/3.0 + 0) , axis_X, true);
	m_3dscreen.TurnObjectCenter(-10 , axis_Z, true);

	pDirDc->RestoreDC(n);

	m_3dscreen.BeginObject(ofek);
	m_3dscreen.CreatObjectPixselMap(trsz,trsz);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm1.GetMyPaintDC();
		int n = pdc->SaveDC();
		CPen pen1(PS_SOLID,1,(COLORREF)0);
		CBrush br1(RGB(255,255,96)/*color3*/);
		CPen* oPen = pdc->SelectObject(&pen1);
		CBrush* obr = pdc->SelectObject(&br1);
		CRect rc(0,0,trsz,trsz);
		pdc->FillSolidRect(CRect(0,0,trsz, trsz),0);
		pdc->Ellipse(rc);
		m_3dscreen.BitmapToObject(bm1, RGBT2(0,0));
		pdc->SelectObject(oPen);
		pdc->SelectObject(obr);
		pdc->RestoreDC(n);
	}
	m_3dscreen.FillRect(0,0,trsz, trsz, RGBT(96,48,0,0)
		,fr_xyIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.TurnShape(90.0 + xStart, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.CreateSphereBmObj(trsz,
		bm11,25,-25);
	//m_3dscreen.CreateSphereObject(trsz, RGBT2(0, 0)
	//	,360.0,25.0,-25.0);
	//{
	//	m_3dscreen.BitmapToObject(bm11, RGBT2(0,0));
	//}
	m_3dscreen.TurnShape(-90,axis_x, false,true);
	m_3dscreen.TurnShape(90,axis_y, false,true);
	m_3dscreen.TurnShape(-23.5,axis_z, false,true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(galgalMazalot2);
	m_3dscreen.CreateSphereBmObj(trsz,
		bm22,25,-25);
	m_3dscreen.TurnShape(-90,axis_x, false,true);
	m_3dscreen.TurnShape(90,axis_y, false,true);
	m_3dscreen.TurnShape(-23.5,axis_z, false,true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(galgalHayomy);
	m_3dscreen.CReateCircleLineObject(trsz, color2);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(galgalHayomyShetach);
//	m_3dscreen.CreatObjectPixselMap(trsz,trsz);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm1.GetMyPaintDC();
		int n = pdc->SaveDC();
		CPen pen1(PS_SOLID,1,(COLORREF)color2);
		CBrush br1((COLORREF)0);
		CPen* oPen = pdc->SelectObject(&pen1);
		CBrush* obr = pdc->SelectObject(&br1);
		CRect rc(0,0,trsz,trsz);
		pdc->FillSolidRect(CRect(0,0,trsz, trsz),0);
		//pdc->Ellipse(rc);

		double degree = 0;
		for(int i = 0; i < 24; ++i, degree += 15.0)
		{
			DrawPolyLines(2, rc.Width() / 2,
				rc.CenterPoint(),bm1, degree, 180.0);
		}

		//m_3dscreen.BitmapToObject(bm1, RGBT2(0,0));
		m_3dscreen.CreateFlatBmObj(bm1);
		pdc->SelectObject(oPen);
		pdc->SelectObject(obr);
		pdc->RestoreDC(n);
	}
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	int steps = DiameterSteps(trsz);
	m_3dscreen.BeginObject(sky);
	m_3dscreen.CreateSphereObject(trsz, RGBT(128,0,192, 95));
	m_3dscreen.FillRect(0,0,steps, steps/4, RGBT(0,128,255,95)
		,fr_yIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.FillRect(0,steps/4,steps, steps/4, RGBT(0,0,1,95)
		,fr_yIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();

	int kotTrsz = DiameterSteps(9);
	m_3dscreen.BeginObject(kotevD);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color5, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color5
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-((double)trsz / 2.0), axis_Z, true);
	m_3dscreen.TurnObjectCenter( 32, axis_X,true);
	m_3dscreen.TurnObjectCenter( 90, axis_Y,true);
	m_3dscreen.TurnObjectCenter(xStart, axis_X,true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotevZ);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color5, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color5
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(((double)trsz / 2.0), axis_Z, true);
	m_3dscreen.TurnObjectCenter( 32, axis_X,true);
	m_3dscreen.TurnObjectCenter( 90, axis_Y,true);
	m_3dscreen.TurnObjectCenter(xStart, axis_X,true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotevMiz);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color6, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color6
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(((double)trsz / 2.0), axis_X, true);
	m_3dscreen.TurnObjectCenter(90.0, axis_Y,true);
	m_3dscreen.TurnObjectCenter(xStart, axis_X,true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotevMaa);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color6, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color6
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-((double)trsz / 2.0), axis_X, true);
	m_3dscreen.TurnObjectCenter(90.0, axis_Y,true);
	m_3dscreen.TurnObjectCenter(xStart, axis_X,true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(ofanHzi);
	m_3dscreen.CReateCircleLineObject(trsz,color7);
	m_3dscreen.TurnShape(xStart, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.BeginObject(ofanHziShetach);
//	m_3dscreen.CreatObjectPixselMap(trsz,trsz);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm1.GetMyPaintDC();
		int n = pdc->SaveDC();
		CPen pen1(PS_SOLID,1,(COLORREF)color7);
		CBrush br1((COLORREF)0);
		CPen* oPen = pdc->SelectObject(&pen1);
		CBrush* obr = pdc->SelectObject(&br1);
		CRect rc(0,0,trsz,trsz);
		pdc->FillSolidRect(CRect(0,0,trsz, trsz),0);

		double degree = 0;
		for(int i = 0; i < 120; ++i, degree += 3.0)
		{
			DrawPolyLines(2, rc.Width() / 2,
				rc.CenterPoint(),bm1, degree, 180.0);
		}

		//m_3dscreen.BitmapToObject(bm1, RGBT2(0,0));
		m_3dscreen.CreateFlatBmObj(bm1);
		pdc->SelectObject(oPen);
		pdc->SelectObject(obr);
		pdc->RestoreDC(n);
	}
	m_3dscreen.TurnShape(xStart, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();


	double shiftAng = 75;
	double dtrsz = (double)trsz;
	double shiftZ = sin(shiftAng * D) * dtrsz / 2.0;
	double newtrsz = cos(shiftAng * D) * dtrsz;
	m_3dscreen.BeginObject(zavitYeshara);
	m_3dscreen.CReateCircleLineObject((int)(float)newtrsz, 
		RGBT2(color8, 0), 2.5, 90.0);
	m_3dscreen.TurnShape(-90.0, axis_z, false, true);
	m_3dscreen.ShiftObjectCenter(-shiftZ, axis_Z, true);
	m_3dscreen.TurnObjectCenter(-58, axis_X, true);
	m_3dscreen.TurnShape(-58, axis_X, false, true);
	m_3dscreen.TurnObjectCenter(xStart, axis_Z, true);
	m_3dscreen.TurnShape(xStart, axis_Z, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(haziMizMaa);
	m_3dscreen.CReateCircleLineObject(trsz + 2, 
		RGBT2(color9, 0), 3.5, 90.0);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.TrigerPaintAlow(1);
	return 0;
}

void CPerek19::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(haziMizMaa);
	if(m_buttonId == 9 || m_buttonId == 10)
	{
		m_3dscreen.InitMatrix();
		if(m_buttonId == 10)
			m_3dscreen.TurnMatrix( 90, axis_Z);
		m_3dscreen.TurnMatrix(32, axis_X);
		m_3dscreen.TurnMatrix(90, axis_Y);
		m_3dscreen.TurnMatrix(xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);	
	}


	bool bShowKiv = (m_buttonId >= 0 && m_buttonId < 4);
	double yKiv = m_yTurn;
	if(m_buttonId != 1)
		yKiv += 180;
	m_3dscreen.BeginObject(mizrach);
	if(bShowKiv)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(yKiv, axis_Y);
		m_3dscreen.TurnObjectCenter(20, axis_X);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);	
	}

	m_3dscreen.BeginObject(maarav);
	if(bShowKiv)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(yKiv, axis_Y);
		m_3dscreen.TurnObjectCenter(20, axis_X);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);	
	}

	m_3dscreen.BeginObject(darom);
	if(bShowKiv)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(yKiv, axis_Y);
		m_3dscreen.TurnObjectCenter(15, axis_X);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);	
	}

	m_3dscreen.BeginObject(zafon);
	if(bShowKiv)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(yKiv, axis_Y);
		m_3dscreen.TurnObjectCenter(15, axis_X);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);	
	}

	m_3dscreen.BeginObject(helekZ);
	if(m_buttonId == 4)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(yKiv, axis_Y);
		m_3dscreen.TurnObjectCenter(15, axis_X);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);	
	}

	m_3dscreen.BeginObject(helekD);
	if(m_buttonId == 4)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(yKiv, axis_Y);
		m_3dscreen.TurnObjectCenter(15, axis_X);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);	
	}

	m_3dscreen.BeginObject(kotevZ);
	if(m_buttonId >= 5)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);	
	}

	m_3dscreen.BeginObject(kotevD);
	if(m_buttonId >= 5)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);	
	}

	m_3dscreen.BeginObject(kotevMaa);
	if(m_buttonId >= 6  &&  m_buttonId != 11)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kotevMiz);
	if(m_buttonId >= 6 &&  m_buttonId != 11)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(galgalHayomy);
	if(m_buttonId >= 2)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(32, axis_X);
		m_3dscreen.TurnMatrix(90, axis_Y);
		m_3dscreen.TurnMatrix(xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);	
	}

	m_3dscreen.BeginObject(galgalHayomyShetach);
	if(m_buttonId >= 2)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_Z);
		m_3dscreen.TurnMatrix(32, axis_X);
		m_3dscreen.TurnMatrix(90, axis_Y);
		m_3dscreen.TurnMatrix(xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);	
	}


	m_3dscreen.BeginObject(ofanHzi);
	if(m_buttonId >= 7 &&  m_buttonId != 11)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(ofanHziShetach);
	if(m_buttonId >= 7 &&  m_buttonId != 11)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(zavitYeshara);
	if(m_buttonId == 8)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn+90, axis_Y);
		m_3dscreen.TurnShape(m_yTurn+90, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(ofek);
	if(lasty != m_yTurn)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE );
	lasty = m_yTurn;

	m_3dscreen.BeginObject(galgalMazalot2);
	if(m_buttonId == 2)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(-32, axis_Z);
		m_3dscreen.TurnMatrix(xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(galgalMazalot);
	if(m_buttonId == 0)
	{
		double degSteps = (double)(m_nMazalotStarsSize/ 360.0);
		double startang = m_xTurn - 85.0;
		if(startang < 0)
			startang += 360;
		int nStart = (int)(float)(startang * degSteps);
		int size = (int)(float)(115 * degSteps);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(-32, axis_Z);
		m_3dscreen.TurnMatrix(xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D(TRUE ,nStart , size);
	}
	else if(m_buttonId == 1)
	{
		double degSteps = (double)(m_nMazalotStarsSize/ 360.0);
		double startang = m_xTurn - 190.0;
		if(startang < 0)
			startang += 360;
		int nStart = (int)(float)(startang * degSteps);
		int size = (int)(float)(110 * degSteps);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(-32, axis_Z);
		m_3dscreen.TurnMatrix(-xStart, axis_X);
		m_3dscreen.TurnMatrix(180+m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D(TRUE ,nStart , size);
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(sky);
	if(m_buttonId >= 3)
	{
		m_3dscreen.Translate3Dto2D(FALSE);
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek19::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = TRUE;


	if(m_bBntDown && m_bHandCursor )
	{
		double cx = (p.x - m_pt.x);
		double cy = (p.y - m_pt.y);
		switch(m_buttonId)
		{
		case 0:
		case 1:
		case 2:
			break;
		default:
			m_xTurn = cy / 4.0;
			break;
		}

		m_yTurn = cx / 6.5;
		switch(m_buttonId)
		{
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
			m_yTurn -= 85;
			break;
		}

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek19::InitOnSubHeadButton(void)
{
	lasty = 10000000;
	switch(m_buttonId)
	{
	case 0:
	case 1:
	case 2:
		SetTimer(1,timerElaps,NULL);
		SetFocus();
		break;
	default:
		KillTimer(1);
		break;
	}
		switch(m_buttonId)
		{
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
			m_yTurn = -85;
			break;
		}
}

void CPerek19::OnTimer(UINT_PTR nIDEvent)
{
	m_xTurn += 0.5;
	if(m_xTurn > 360)
		m_xTurn -= 360;
	if(m_bNoTimerDraw == false)
		Do3DPaint();

	CPerek3DBase::OnTimer(nIDEvent);
}

void CPerek19::OnSetFocus(CWnd* pOldWnd)
{
	CPerek3DBase::OnSetFocus(pOldWnd);

	switch(m_buttonId)
	{
	case 0:
	case 1:
	case 2:
		SetTimer(1,timerElaps,NULL);
		break;
	default:
		KillTimer(1);
		break;
	}
}

void CPerek19::OnKillFocus(CWnd* pNewWnd)
{
	CPerek3DBase::OnKillFocus(pNewWnd);

	KillTimer(1);
}
