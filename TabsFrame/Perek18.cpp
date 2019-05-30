// Perek18.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek18.h"


// CPerek18

IMPLEMENT_DYNCREATE(CPerek18, CPerek3DBase)

CPerek18::CPerek18()
: m_person(m_3dscreen)
{
	m_IDstart = ID_P18_1;
	m_IDidx = WT_PEREK_18;
	m_IDX_PEREK = IDX_PEREK_18;
}

CPerek18::~CPerek18()
{
}

BEGIN_MESSAGE_MAP(CPerek18, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P18_1, ID_P18_9, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P18_1, ID_P18_9, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek18 drawing


// CPerek18 diagnostics

#ifdef _DEBUG
void CPerek18::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek18::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek18 message handlers

const int trsz = 290;
const double xStart = 15;
const double yStart = 5;
const int sShemesh = 23;

enum
{
	ofek
	,rosh
	,regel
	,ofanHzi
	,ofanHziShetach
	,zavitYeshara
	,mizrach
	,maarav
	,shemesh
	,kotevMaa
	,kotevMiz
};


int CPerek18::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;
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


	CString sMiz = cp.paragraphs[5].sParagraph;
	CString sMaa = cp.paragraphs[6].sParagraph;

	int nMiz = dc.GetTextExtent(sMiz).cx;
	int nSise = nMiz;
	int nMaa = dc.GetTextExtent(sMaa).cx;
	nSise = max(nSise,nMaa);
	int nY = dc.GetTextExtent(sMiz).cy;
	int bmH = 18;
	nY = (bmH-nY)/2;
	nSise += 4;

	CMyFBitmap bmKiv;
	bmKiv.CreateMyCompatibleBitmap(&dc,nSise,bmH,0);
	int nX = (nSise-nMiz)/2;
	CDC* pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SelectObject(&font);
	pDirDc->SetBkMode(TRANSPARENT);
	pDirDc->SetTextColor(color5);
	pDirDc->TextOutA(nX,nY,sMiz);

	double dTrsx = trsz;
	m_3dscreen.BeginObject(mizrach);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter((dTrsx/4) , axis_X, true);
	m_3dscreen.ShiftObjectCenter((dTrsx/8) , axis_Y, true);

	nX = (nSise-nMaa)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SetTextColor(color6);
	pDirDc->TextOutA(nX,nY,sMaa);

	m_3dscreen.BeginObject(maarav);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter(-(dTrsx/4) , axis_X, true);
	m_3dscreen.ShiftObjectCenter((dTrsx/8) , axis_Y, true);

	int stepsShem = DiameterSteps(sShemesh);
	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(128,0,0, 0));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(192,96,0,0)
		,fr_zIntensity , (double)sShemesh / 2.0 - 0.5);

	m_3dscreen.ShiftObjectCenter(-(dTrsx/2 + ((double)sShemesh)/4.0), axis_Z, true);
	m_3dscreen.TurnObjectCenter(-45, axis_X, true);
	m_3dscreen.TurnObjectCenter(23, axis_Z, true);
	m_3dscreen.TurnObjectCenter(42.5, axis_X, true);
	m_3dscreen.TurnObjectCenter(90, axis_Y, true);
	m_3dscreen.TurnObjectCenter(90, axis_Z, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();


	double shiftAng = 75;
	double dtrsz = (double)trsz;
	double shiftZ = sin(shiftAng * D) * dtrsz / 2.0;
	double newtrsz = cos(shiftAng * D) * dtrsz;
	m_3dscreen.BeginObject(zavitYeshara);
	m_3dscreen.CReateCircleLineObject((int)(float)newtrsz, 
		RGBT2(color4, 0), 2.5, 90.0);
	m_3dscreen.TurnShape(90.0, axis_z, false, true);
	m_3dscreen.ShiftObjectCenter(-shiftZ, axis_Z, true);
	m_3dscreen.TurnObjectCenter(xStart, axis_X, true);
	m_3dscreen.TurnShape(xStart, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();


	int kotTrsz = DiameterSteps(9);
	m_3dscreen.BeginObject(kotevMiz);
	m_3dscreen.CreateSphereObject(9, 
		RGBT(0,0,96, 0));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color8
		,fr_zIntensity , (double)kotTrsz / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(((double)trsz / 2.0), axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kotevMaa);
	m_3dscreen.CreateSphereObject(9, 
		RGBT(0,0,96, 0));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color8
		,fr_zIntensity , (double)kotTrsz / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(-((double)trsz / 2.0), axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();


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
		m_3dscreen.BitmapToObject(bm1, RGBT2(0,0));
	}
	m_3dscreen.FillRect(0,0,trsz, trsz, RGBT(96,48,0,0)
		,fr_xyIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.TurnShape(90.0 + xStart, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(ofanHzi);
	m_3dscreen.CReateCircleLineObject(trsz,color2);
	m_3dscreen.TurnShape(90.0, axis_Y, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.BeginObject(ofanHziShetach);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm1.GetMyPaintDC();
		CPen pen1(PS_SOLID,1,(COLORREF)color3);
		CBrush br1((COLORREF)0);
		pdc->SelectObject(&pen1);
		pdc->SelectObject(&br1);
		CRect rc(0,0,trsz,trsz);
		pdc->FillSolidRect(CRect(0,0,trsz, trsz),0);
		//pdc->Ellipse(rc);

		double degree = 0;
		for(int i = 0; i < 120; ++i, degree += 3.0)
		{
			DrawPolyLines(2, rc.Width() / 2,
				rc.CenterPoint(),bm1, degree, 180.0);
		}

		m_3dscreen.CreateFlatBmObj(bm1);
	}
	//m_3dscreen.FillRect(0,0,trsz, trsz, RGBT(96,48,0,0)
	//	,fr_xyIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.TurnShape(90.0, axis_Y, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(rosh);
	m_3dscreen.CreateSphereObject(9, 
		RGBT(32,0,54, 0));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color0/*RGB(255,255,255)*/
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(trsz/2, axis_Y, true);
	m_3dscreen.TurnObjectCenter(xStart, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(regel);
	m_3dscreen.CreateSphereObject(9, 
		RGBT(32,0,64, 0));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color1/*RGB(255,255,255)*/
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-trsz/2, axis_Y, true);
	m_3dscreen.TurnObjectCenter(xStart, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_person.Create();

	m_3dscreen.TrigerPaintAlow(1);
	return 0;
}

void CPerek18::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();


	m_3dscreen.BeginObject(ofek);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(m_yTurn+yStart, axis_Y);
	m_3dscreen.Translate3Dto2D();

	double dVec = sin((m_xTurn + 90) * D);
	int vec = (int)(float)(dVec * 100);
	int sqrtVect = (int)(float)(sqrt(dVec) * 100);
	int sqVect = (int)(float)(dVec*dVec * 100);
	if(vec < 0)
		vec = 0;

	int stepsShem = DiameterSteps(sShemesh);

	m_3dscreen.BeginObject(shemesh);
	if(m_buttonId >= 7)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(100+vec*3/2,55+vec*2,0,0)
			,fr_zAtIntensity , (double)sShemesh / 2.0 - 0.5);
		if(m_buttonId == 8)
			m_3dscreen.TurnObjectCenter(m_xTurn, axis_Z);
		m_3dscreen.TurnObjectCenter(32+xStart, axis_X);
		m_3dscreen.TurnObjectCenter(yStart + m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}


	m_3dscreen.BeginObject(kotevMaa);
	if(m_buttonId == 8)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn+yStart, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kotevMiz);
	if(m_buttonId == 8)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn+yStart, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(mizrach);
	if(m_buttonId >= 5)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn+yStart, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(maarav);
	if(m_buttonId >= 6)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn+yStart, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(zavitYeshara);
	if(m_buttonId == 4)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn+yStart, axis_Y);
		m_3dscreen.TurnShape(m_yTurn+yStart, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(ofanHzi);
	if(m_buttonId >= 2)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnShape(m_yTurn+yStart, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(ofanHziShetach);
	if(m_buttonId >= 3)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnShape(m_yTurn+yStart, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_person.Reset();
	m_person.Turn(xStart,axis_X,false);
	m_person.Turn(m_yTurn+yStart, axis_Y);

	m_3dscreen.BeginObject(rosh);
	if(m_buttonId >= 0)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn+yStart, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(regel);
	if(m_buttonId >= 1)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn+yStart, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}


	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek18::OnMouseMove(UINT nFlags, CPoint point)
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
		m_yTurn = cx / 6.5;
		m_xTurn = cy / 4.0;


		Do3DPaint();
	}


	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek18::InitOnSubHeadButton(void)
{
	m_yTurn = m_xTurn = 0;
}
