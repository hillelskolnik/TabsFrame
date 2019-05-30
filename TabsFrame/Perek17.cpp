// Perek17.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek17.h"


// CPerek17
const double fine = 2;
const int trsz = 252;
const int sShemesh = 23;


IMPLEMENT_DYNCREATE(CPerek17, CPerek3DBase)

CPerek17::CPerek17()
:m_person(m_3dscreen)
, stepsTrsz(DiameterSteps(trsz, fine))
{
	m_IDstart = ID_P17_1;
	m_IDidx = WT_PEREK_17;
	m_IDX_PEREK = IDX_PEREK_17;
}

CPerek17::~CPerek17()
{
}

BEGIN_MESSAGE_MAP(CPerek17, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P17_1, ID_P17_4, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P17_1, ID_P17_4, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek17 drawing

// CPerek17 diagnostics

#ifdef _DEBUG
void CPerek17::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek17::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek17 message handlers

const double turnY = 0;

enum
{
	ofek
	,shemesh
	,shamaim
	,mizrach
	,maarav
	,darom
	,zafon
};

int CPerek17::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];

	CClientDC dc(this);
	COLORREF color0 = cp.paragraphs[0].color;
	COLORREF color1 = cp.paragraphs[1].color;
	COLORREF color2 = cp.paragraphs[2].color;
	COLORREF color3 = cp.paragraphs[3].color;

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

	CMyFBitmap bmKiv;
	bmKiv.CreateMyCompatibleBitmap(&dc,nSise,bmH,0);
	int nX = (nSise-nMiz)/2;
	CDC* pDirDc = bmKiv.GetMyPaintDC();
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


	m_3dscreen.BeginObject(ofek);
	m_3dscreen.CreatObjectPixselMap(trsz,trsz);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm1.GetMyPaintDC();
		CPen pen1(PS_SOLID,1,(COLORREF)RGB(255,255,0));
		CBrush br1(RGB(255,255,0)/*color3*/);
		pdc->SelectObject(&pen1);
		pdc->SelectObject(&br1);
		CRect rc(0,0,trsz,trsz);
		pdc->FillSolidRect(CRect(0,0,trsz, trsz),0);
		pdc->Ellipse(rc);
		m_3dscreen.BitmapToObject(bm1, RGBT2(0,0));
	}
	m_3dscreen.FillRect(0,0,trsz, trsz, RGBT(32,16,0,0)
		,fr_xyIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.TurnShape(105.0, axis_X, false, true);
	m_3dscreen.TurnShape(turnY, axis_Y, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_X);
	m_3dscreen.Translate3Dto2D();


	int stepsShem = DiameterSteps(sShemesh);
	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(64,0,0, 0));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(128,64,0,0)
		,fr_zIntensity , (double)sShemesh / 2.0 - 0.5);

	m_3dscreen.ShiftObjectCenter(-(dTrsx/2 + ((double)sShemesh)/2.0), axis_Z, true);
	m_3dscreen.TurnObjectCenter(-45, axis_X, true);
	m_3dscreen.TurnObjectCenter(23, axis_Z, true);
	m_3dscreen.TurnObjectCenter(44, axis_X, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(shamaim);
	m_3dscreen.CreateSphereObject(trsz, 
		RGBT(8,0,2, 95), 360,90,-90,fine);
	m_3dscreen.FillRect(0,0,stepsTrsz, stepsTrsz/4, RGBT(0,0,92,95)
		,fr_yIntensity , ((double)trsz) / 2.0 - 0.5);
	m_3dscreen.FillRect(0,stepsTrsz/4,stepsTrsz, stepsTrsz/4, 
		RGBT(16,24,64,95)
		,fr_yIntensity , ((double)trsz) / 2.0 - 0.5);
	m_3dscreen.TurnShape(15.0, axis_X, false, true);
	m_3dscreen.TurnShape(turnY, axis_Y, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_person.Create();

	m_3dscreen.TrigerPaintAlow(1);
	return 0;
}

void CPerek17::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	double xTurn = m_xTurn;
	if(m_buttonId == 1)
		xTurn -= 150;
	else if(m_buttonId == 2)
		xTurn -= 90;

	if(m_buttonId == 3)
	{
		m_person.Reset();
		m_person.Turn(-90, axis_y, false);
		m_person.Turn(15, axis_x, false);
		m_person.Turn(m_yTurn, axis_y);
	}
	else
	{
		m_person.Hide();
	}

	m_3dscreen.BeginObject(mizrach);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(20, axis_X);
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(maarav);
	if(m_buttonId >= 1)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(20, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);	
	}

	m_3dscreen.BeginObject(darom);
	if(m_buttonId >= 2)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnObjectCenter(15, axis_X);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);	
	}

	m_3dscreen.BeginObject(zafon);
	if(m_buttonId == 3)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnObjectCenter(15, axis_X);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);	
	}

	double dVec = sin(-xTurn * D);
	int vec = (int)(float)(dVec * 100);
	int sqrtVect = (int)(float)(sqrt(dVec) * 100);
	int sqVect = (int)(float)(dVec*dVec * 100);
	if(vec < 0)
		vec = 0;

	m_3dscreen.BeginObject(ofek);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.FillRect(0,0,stepsTrsz, stepsTrsz, RGBT(255,255,0,vec)
		,fr_colIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.TurnShape(m_yTurn, axis_Y);
	m_3dscreen.Translate3Dto2D();

	int stepsShem = DiameterSteps(sShemesh);

	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(255,255,0,vec)
		,fr_colIntensity , (double)sShemesh / 2.0 - 0.5);
	m_3dscreen.TurnObjectCenter(xTurn + 15, axis_X);
	m_3dscreen.TurnObjectCenter(32, axis_Z);
	m_3dscreen.TurnObjectCenter(turnY + m_yTurn, axis_Y);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(shamaim);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.FillRect(0,0,stepsTrsz, stepsTrsz/4, 
		RGBT(255 - sqrtVect*2,27 + sqVect ,55 + sqrtVect*2,sqrtVect)
		,fr_colIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.TurnShape(m_yTurn, axis_Y);
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek17::OnMouseMove(UINT nFlags, CPoint point)
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
		//double temp = sqrt(cx*cx+cy*cy);
		//temp /= 35;
		//m_distance = sqrt(cx*cx+cy*cy) * temp*temp;
		m_yTurn = cx / 10.5;
		if(m_buttonId == 3)
			m_xTurn = cy;
		else
			m_xTurn = cy / 4.0;


		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek17::InitOnSubHeadButton(void)
{
		m_yTurn = 0;
		m_xTurn = 0;
}
