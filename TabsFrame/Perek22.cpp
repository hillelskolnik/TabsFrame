// Perek22.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek22.h"


// CPerek22

IMPLEMENT_DYNCREATE(CPerek22, CPerek3DBase)

const int trsz = 256;

CPerek22::CPerek22()
: lasty(0)
, m_nMazalotStars2Size(0)
, m_nMazalotStarsSize(0)
{
	m_IDstart = ID_P22_1;
	m_IDidx = WT_PEREK_22;
	m_IDX_PEREK = IDX_PEREK_22;
}

CPerek22::~CPerek22()
{
}

BEGIN_MESSAGE_MAP(CPerek22, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P22_1, ID_P22_3, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P22_1, ID_P22_3, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


// CPerek22 drawing

// CPerek22 diagnostics

#ifdef _DEBUG
void CPerek22::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek22::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek22 message handlers
const double xStart = 15;
const double yStart = 5;
const int timerElaps = 45;
const int sShemesh = 23;
const int plusElapse = 8;

enum
{
	ofek
	,galgalMazalot
	,galgalMazalot2
	,mizrach
	,maarav
	,darom
	,zafon
	,shemesh
	,galgalShemeshShetach
	,galgalShemes
	,galgalHayomyShetach
	,galgalHayomy

};

const double mahalachShemesh = 0.98562628336755646817248459958932;

int CPerek22::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CMyFBitmap bm11;
	CString path = theApp.m_appPath + "Images\\MazalotStars3.BMP";
	CImage image22;
	image22.Load(path);
	bm11.CreateMyCompatibleBitmap(NULL, image22.GetWidth(),
		image22.GetHeight());
	image22.BitBlt(bm11.operator CDC *()->GetSafeHdc(),
		CPoint(0,0));
	m_nMazalotStarsSize = image22.GetWidth();

	CMyFBitmap bm33;
	path = theApp.m_appPath + "Images\\MazalotStars2.BMP";
	CImage image44;
	image44.Load(path);
	bm33.CreateMyCompatibleBitmap(NULL, image44.GetWidth(),
		image44.GetHeight());
	image44.BitBlt(bm33.operator CDC *()->GetSafeHdc(),
		CPoint(0,0));
	m_nMazalotStars2Size = image44.GetWidth();

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];

	CClientDC dc(this);
	COLORREF color0 = cp.paragraphs[0].color;
	COLORREF color1 = cp.paragraphs[1].color;
	COLORREF color2 = cp.paragraphs[2].color;

	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 30.0, 3.0, 7.0);
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

	int nMiz = dc.GetTextExtent(sMiz).cx;
	int nSise = nMiz;
	int nMaa = dc.GetTextExtent(sMaa).cx;
	nSise = max(nSise,nMaa);
	int nDar = dc.GetTextExtent(sDar).cx;
	nSise = max(nSise,nDar);
	int nZaf = dc.GetTextExtent(sZaf).cx;
	nSise = max(nSise,nZaf);
	int nY = dc.GetTextExtent(sZaf).cy;
	int bmH = 18;
	nY = (bmH-nY)/2;
	nSise += 4;

	COLORREF colKiv = RGB(0,0,255);

	CMyFBitmap bmKiv;
	bmKiv.CreateMyCompatibleBitmap(&dc,nSise,bmH,0);
	int nX = (nSise-nMiz)/2;
	CDC* pDirDc = bmKiv.GetMyPaintDC();
	int n = pDirDc->SaveDC();
	pDirDc->SelectObject(&font);
	pDirDc->SetBkMode(TRANSPARENT);
	pDirDc->SetTextColor(colKiv);
	pDirDc->TextOutA(nX,nY,sMiz);

	double dTrsx = trsz + sShemesh/2;
	m_3dscreen.BeginObject(mizrach);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ShiftObjectCenter(-(dTrsx/2 + nSise) , axis_Z, true);
	
	nX = (nSise-nMaa)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SetTextColor(colKiv);
	pDirDc->TextOutA(nX,nY,sMaa);

	m_3dscreen.BeginObject(maarav);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter((dTrsx/2 + nSise) , axis_Z, true);
	m_3dscreen.ResetTranslation();

	nX = (nSise-nDar)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SetTextColor(colKiv);
	pDirDc->TextOutA(nX,nY,sDar);

	m_3dscreen.BeginObject(darom);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter(-(dTrsx/2 + nSise) , axis_X, true);
	m_3dscreen.ResetTranslation();

	nX = (nSise-nZaf)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SetTextColor(colKiv);
	pDirDc->TextOutA(nX,nY,sZaf);

	m_3dscreen.BeginObject(zafon);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter((dTrsx/2 + nSise) , axis_X, true);
	m_3dscreen.ResetTranslation();


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
	m_3dscreen.CreateSphereBmObj(trsz + sShemesh*2,
		bm11,25,-25);
	m_3dscreen.TurnShape(90,axis_x, false,true);
	m_3dscreen.TurnShape(90,axis_y, false,true);
	m_3dscreen.TurnShape(-23.5,axis_z, false,true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(galgalMazalot2);
	m_3dscreen.CreateSphereBmObj(trsz + sShemesh*2,
		bm33,25,-25);
	m_3dscreen.TurnShape(90,axis_x, false,true);
	m_3dscreen.TurnShape(90,axis_y, false,true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	int stepsShem = DiameterSteps(sShemesh);
	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(64,0,0, 0));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(200,120,0,0)
		,fr_zIntensity , (double)sShemesh / 2.0);
	m_3dscreen.ShiftObjectCenter((dTrsx/2 /*+ ((double)sShemesh)/2.0*/), axis_Z, true);
	m_3dscreen.ResetTranslation();

	int trszGS = trsz + sShemesh;
	m_3dscreen.BeginObject(galgalShemeshShetach);
	//m_3dscreen.CreatObjectPixselMap(trszGS,trszGS);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trszGS,trszGS,0);
		CDC* pdc = bm1.GetMyPaintDC();
		CPen pen1(PS_SOLID,1,(COLORREF)color1);
		CBrush br1((COLORREF)0);
		pdc->SelectObject(&pen1);
		pdc->SelectObject(&br1);
		CRect rc(0,0,trszGS,trszGS);
		pdc->FillSolidRect(CRect(0,0,trszGS, trszGS),0);
		//rc.DeflateRect(2,2);
		//pdc->Ellipse(rc);

		double degree = 0;
		for(int i = 0; i < 12; ++i, degree += 30.0)
		{
			DrawPolyLines(2, rc.Width() / 2,
				rc.CenterPoint(),bm1, degree, 180.0);
		}

		//m_3dscreen.BitmapToObject(bm1, RGBT2(0,0));
		m_3dscreen.CreateFlatBmObj(bm1);
	}
	m_3dscreen.TurnShape(90, axis_Y, false, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(galgalShemes);
	m_3dscreen.CReateCircleLineObject(trszGS, color1);
	m_3dscreen.TurnShape(90, axis_Y, false, true);

	int trszGY = trsz + sShemesh*2-4;
	m_3dscreen.BeginObject(galgalHayomyShetach);
//	m_3dscreen.CreatObjectPixselMap(trszGY,trszGY);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trszGY,trszGY,0);
		CDC* pdc = bm1.GetMyPaintDC();
		CPen pen1(PS_SOLID,1,(COLORREF)color2);
		CBrush br1((COLORREF)0);
		pdc->SelectObject(&pen1);
		pdc->SelectObject(&br1);
		CRect rc(0,0,trszGY,trszGY);
		pdc->FillSolidRect(CRect(0,0,trszGY, trszGY),0);
		//rc.DeflateRect(2,2);
		//pdc->Ellipse(rc);

		double degree = 0;
		for(int i = 0; i < 12; ++i, degree += 30.0)
		{
			DrawPolyLines(2, rc.Width() / 2,
				rc.CenterPoint(),bm1, degree, 180.0);
		}

		//m_3dscreen.BitmapToObject(bm1, RGBT2(0,0));
		m_3dscreen.CreateFlatBmObj(bm1);
	}
	m_3dscreen.TurnShape(90, axis_Y, false, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(galgalHayomy);
	m_3dscreen.CReateCircleLineObject(trszGY, color2);
	m_3dscreen.TurnShape(90, axis_Y, false, true);
	m_3dscreen.TurnShape(32, axis_Z, false, true);
	m_3dscreen.TurnShape(xStart, axis_X,false, true);


	m_3dscreen.TrigerPaintAlow(1);
	return 0;
}

void CPerek22::OnMouseMove(UINT nFlags, CPoint point)
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

		m_yTurn = cx / 3.5;
		switch(m_buttonId)
		{
		case 1:
			m_yTurn += 45;
			break;
		}

		if(m_yTurn < 0)
			m_yTurn += 360;
		else if(m_yTurn > 360)
			m_yTurn -= 360;

		int elapse = timerElaps;
		if(m_buttonId == 2)
			elapse += plusElapse;
		SetTimer(1,elapse,NULL);
		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek22::InitOnSubHeadButton(void)
{
	lasty = 10000000;
	int elapse = timerElaps;
	if(m_buttonId == 2)
		elapse += plusElapse;
	SetTimer(1,elapse,NULL);
	SetFocus();
	switch(m_buttonId)
	{
	case 0:
		m_yTurn = 0;
		break;
	case 1:
	case 2:
		m_yTurn = 30;
		break;
	}
}

void CPerek22::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(ofek);
	if(lasty != m_yTurn)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE );
	

	double yKiv = m_yTurn;
	//if(m_buttonId != 1)
	//	yKiv += 180;

	bool bShowKiv = true;
	m_3dscreen.BeginObject(mizrach);
	if(bShowKiv)
	{
		//m_3dscreen.ResetTranslation();
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
		//m_3dscreen.ResetTranslation();
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
		//m_3dscreen.ResetTranslation();
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
		//m_3dscreen.ResetTranslation();
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

	m_3dscreen.BeginObject(galgalMazalot);
	if(m_buttonId == 0)
	{
		//static int i = DiameterSteps(trsz + sShemesh*2);
//		m_3dscreen.ResetTranslation();
//		m_3dscreen.ResetShift();
		double turnBack = AliyaYeshara(m_xTurn,23.5);
		double degSteps = ((double)m_nMazalotStarsSize/ 360.0);
		double startang = turnBack - 15;
		if(startang < 0)
			startang += 360;
		double sAliya = 
			asin(SinNetyatAliyaYeshara(m_xTurn, 23.5)) *ToD;
		int nStart = (int)(float)(startang * degSteps-sAliya*1.8 - 15);
		int size = (int)(float)((90 + sAliya) * degSteps);

		//m_3dscreen.TurnShape(-turnBack, axis_X, false);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		//m_3dscreen.TurnShape(xStart, axis_X,false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(-turnBack, axis_X);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D(TRUE ,nStart , size);
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(galgalMazalot2);
	if(m_buttonId == 1)
	{
		if(lasty != m_yTurn)	
		{ 
			static double degSteps = ((double)m_nMazalotStars2Size/ 360.0);
			static int size = (int)(float)(degSteps * 180);

			double t = (m_yTurn > 270 || m_yTurn < 90)?90:270;
			t -= xStart;
			int nStart = (int)(float)(degSteps * t);
			//m_3dscreen.ResetTranslation();
			//m_3dscreen.ResetShift();
			//m_3dscreen.TurnShape(8.5,axis_z, false);
			//m_3dscreen.TurnShape(xStart, axis_X,false);
			//m_3dscreen.TurnShape(m_yTurn, axis_Y);
			m_3dscreen.InitMatrix();
			m_3dscreen.TurnMatrix(8.5,axis_z);
			m_3dscreen.TurnMatrix(xStart, axis_X);
			m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
			m_3dscreen.Transform();
			m_3dscreen.Translate3Dto2D(TRUE ,nStart , size);
		}
		else
			m_3dscreen.Translate3Dto2D(FALSE);
	}
	else if(m_buttonId == 2)
	{
			//m_3dscreen.ResetTranslation();
			//m_3dscreen.ResetShift();
			//m_3dscreen.TurnShape(-23.5, axis_Z, false);
			//m_3dscreen.TurnShape(-m_xTurn * 365.25, axis_X, false);
			//m_3dscreen.TurnShape(32, axis_Z, false);
			//m_3dscreen.TurnShape(xStart, axis_X,false);

			//m_3dscreen.TurnShape(m_yTurn, axis_Y);
			m_3dscreen.InitMatrix();
			m_3dscreen.TurnMatrix(-23.5,axis_z);
			m_3dscreen.TurnMatrix(-m_xTurn * 365.25, axis_X);
			m_3dscreen.TurnMatrix(32, axis_Z);
			m_3dscreen.TurnMatrix(xStart, axis_X);
			m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
			m_3dscreen.Transform();
			m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(galgalShemeshShetach);
	if(m_buttonId == 1)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();

		//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
		//m_3dscreen.TurnShape(8.5, axis_Z, false);
		//m_3dscreen.TurnShape(xStart, axis_X,false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(8.5, axis_Z);
		m_3dscreen.TurnMatrix(xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId == 2)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();
		//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
		//m_3dscreen.TurnShape(-23.5, axis_Z, false);
		//m_3dscreen.TurnShape(-m_xTurn * 365.25, axis_X, false);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		//m_3dscreen.TurnShape(xStart, axis_X,false);

		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(-23.5, axis_Z);
		m_3dscreen.TurnMatrix(-m_xTurn * 365.25, axis_X);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(galgalShemes);
	if(m_buttonId == 1)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();

		//m_3dscreen.TurnShape(8.5, axis_Z, false);
		//m_3dscreen.TurnShape(xStart, axis_X,false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(8.5, axis_Z);
		m_3dscreen.TurnMatrix(xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId == 2)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();
		//m_3dscreen.TurnShape(-23.5, axis_Z, false);
		//m_3dscreen.TurnShape(-m_xTurn * 365.25, axis_X, false);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		//m_3dscreen.TurnShape(xStart, axis_X,false);

		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(-23.5, axis_Z);
		m_3dscreen.TurnMatrix(-m_xTurn * 365.25, axis_X);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(galgalHayomyShetach);
	if(m_buttonId == 2)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();

		//m_3dscreen.TurnShape(-m_xTurn * 365.25, axis_X, false);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		//m_3dscreen.TurnShape(xStart, axis_X,false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(-m_xTurn * 365.25, axis_X);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(galgalHayomy);
	if(m_buttonId == 2)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();

		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);



	m_3dscreen.BeginObject(shemesh);
	if(m_buttonId == 0)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnObjectCenter(-23.5, axis_Z);

		double turnBack = AliyaYeshara(m_xTurn,23.5);
		m_3dscreen.TurnObjectCenter(-turnBack, axis_X);
		double sAliya = 
			SinNetyatAliyaYeshara(m_xTurn, 23.5);
		double kizuz = kizuzNetiyaLaOfek(32,sAliya);

		m_3dscreen.TurnObjectCenter(-kizuz, axis_X);
		m_3dscreen.TurnObjectCenter(32.0, axis_Z);
		m_3dscreen.TurnObjectCenter(xStart, axis_X);

		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);

		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId == 1)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnObjectCenter(8.5, axis_Z);
		m_3dscreen.TurnObjectCenter(xStart, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnObjectCenter(-23.5, axis_Z);
		m_3dscreen.TurnObjectCenter(-m_xTurn * 365.25, axis_X);
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		m_3dscreen.TurnObjectCenter(xStart, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);

		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}

	lasty = m_yTurn;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek22::OnTimer(UINT_PTR nIDEvent)
{
	switch(m_buttonId)
	{
	case 0:
	case 1:
		m_xTurn += mahalachShemesh;
		break;
	case 2:
		m_xTurn += mahalachShemesh/360;
		break;
	}
	if(m_xTurn > 360)
		m_xTurn -= 360;

	if(m_bNoTimerDraw == false)
		Do3DPaint();

	CPerek3DBase::OnTimer(nIDEvent);
}

void CPerek22::OnKillFocus(CWnd* pNewWnd)
{
	CPerek3DBase::OnKillFocus(pNewWnd);

	KillTimer(1);
}

void CPerek22::OnSetFocus(CWnd* pOldWnd)
{
	CPerek3DBase::OnSetFocus(pOldWnd);

	int elapse = timerElaps;
	if(m_buttonId == 2)
		elapse += plusElapse;
	SetTimer(1,elapse,NULL);
}
