// Perek23.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek23.h"


// CPerek23

IMPLEMENT_DYNCREATE(CPerek23, CPerek3DBase)

CPerek23::CPerek23()
: lasty(0)
{
	m_IDstart = ID_P23_1;
	m_IDidx = WT_PEREK_23;
	m_IDX_PEREK = IDX_PEREK_23;
}

CPerek23::~CPerek23()
{
}

BEGIN_MESSAGE_MAP(CPerek23, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P23_1, ID_P23_3, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P23_1, ID_P23_3, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPerek23 drawing

// CPerek23 diagnostics

#ifdef _DEBUG
void CPerek23::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek23::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG

const double xStart = 5;
const double yStart = 10;
const int timerElaps = 40;
const int sShemesh = 13;
const int trsz = 330;

enum
{
	ofek
	,mizrach
	,maarav
	,darom
	,zafon
	,ofanHzi
	,shemesh
	,galgalShemeshShetach
	,galgalHayomy
	,galgalHayomyKav
	,kavHatchalatYom

};

const double mahalachShemesh = 0.98562628336755646817248459958932;

// CPerek23 message handlers

int CPerek23::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

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
	m_3dscreen.ShiftObjectCenter((dTrsx/2 + nSise) , axis_X, true);
	m_3dscreen.ResetTranslation();
	
	nX = (nSise-nMaa)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SetTextColor(colKiv);
	pDirDc->TextOutA(nX,nY,sMaa);

	m_3dscreen.BeginObject(maarav);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter(-(dTrsx/2 + nSise) , axis_X, true);
	m_3dscreen.ResetTranslation();

	nX = (nSise-nDar)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SetTextColor(colKiv);
	pDirDc->TextOutA(nX,nY,sDar);

	m_3dscreen.BeginObject(darom);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter(-(dTrsx/2 + nSise) , axis_Z, true);
	m_3dscreen.ResetTranslation();

	nX = (nSise-nZaf)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SetTextColor(colKiv);
	pDirDc->TextOutA(nX,nY,sZaf);

	m_3dscreen.BeginObject(zafon);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter((dTrsx/2 + nSise) , axis_Z, true);
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

	m_3dscreen.BeginObject(ofanHzi);
	m_3dscreen.CReateCircleLineObject(trsz,color1);
	m_3dscreen.TurnShape(90.0, axis_Y, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	double dTrsx2 = trsz;
	int stepsShem = DiameterSteps(sShemesh);
	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(128,0,0, 0));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(255,128,0,0)
		,fr_zIntensity , (double)sShemesh / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(-dTrsx2/2, axis_X, true);
	m_3dscreen.ResetTranslation();

	int trszGS = trsz ;
	m_3dscreen.BeginObject(galgalShemeshShetach);
	m_3dscreen.CReateCircleLineObject(trsz,RGB(255,255,0));

	m_3dscreen.BeginObject(galgalHayomy);
	m_3dscreen.CReateCircleLineObject(trsz,RGB(255,0,128));
	m_3dscreen.TurnShape(90,axis_z,false,true);

	m_3dscreen.BeginObject(galgalHayomyKav);
	m_3dscreen.CreatObjectPixselMap(trsz,1,RGB(255,0,128),2);
	m_3dscreen.TurnShape(90,axis_z,false,true);

	m_3dscreen.BeginObject(kavHatchalatYom);
	m_3dscreen.CreatObjectPixselMap(trsz,1,color0,2);

	m_3dscreen.TrigerPaintAlow(1);
	return 0;
}

void CPerek23::OnMouseMove(UINT nFlags, CPoint point)
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

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek23::Do3DPaint(void)
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


	m_3dscreen.BeginObject(mizrach);
	//m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	m_3dscreen.TurnObjectCenter(5, axis_X);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(maarav);
	//m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	m_3dscreen.TurnObjectCenter(5, axis_X);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(darom);
	//m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	m_3dscreen.TurnObjectCenter(20, axis_X);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(zafon);
	//m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	m_3dscreen.TurnObjectCenter(20, axis_X);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(ofanHzi);
	if(m_buttonId > 0)
	{	
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
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(shemesh);
	if(m_buttonId > 2)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(-90, axis_Z);
		m_3dscreen.TurnObjectCenter(32+xStart, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(-m_xTurn / 365.25, axis_Z);
		m_3dscreen.TurnObjectCenter(-23.5, axis_X);
		m_3dscreen.TurnObjectCenter(-90, axis_Z);
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_Z);
		m_3dscreen.TurnObjectCenter(32+xStart, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);


		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}

	
	m_3dscreen.BeginObject(galgalShemeshShetach);
	if(m_buttonId > 2)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();
		//m_3dscreen.TurnShape(-23, axis_X,false);
		//m_3dscreen.TurnShape(-90, axis_Z,false);
		//m_3dscreen.TurnShape(32+xStart, axis_X,false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(-23.5, axis_X);
		m_3dscreen.TurnMatrix(-90.0, axis_Z);
		m_3dscreen.TurnMatrix(32+xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();
		//m_3dscreen.TurnShape(-m_xTurn / 365.25, axis_Z,false);
		//m_3dscreen.TurnShape(-23, axis_X,false);
		//m_3dscreen.TurnShape(-90+m_xTurn, axis_Z,false);
		//m_3dscreen.TurnShape(32+xStart, axis_X,false);


		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(-m_xTurn / 365.25, axis_Z);
		m_3dscreen.TurnMatrix(-23.5, axis_X);
		m_3dscreen.TurnMatrix(-90.0+m_xTurn, axis_Z);
		m_3dscreen.TurnMatrix(32+xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(galgalHayomy);
	//m_3dscreen.ResetTranslation();
	//m_3dscreen.ResetShift();
	//m_3dscreen.TurnShape(32+xStart, axis_X,false);
	//m_3dscreen.TurnShape(m_yTurn, axis_Y);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(32+xStart, axis_X);
	m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.BeginObject(galgalHayomyKav);
	if(m_buttonId > 2)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();
		//m_3dscreen.TurnShape(32+xStart, axis_X,false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(32+xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();
		//m_3dscreen.TurnShape(m_xTurn, axis_Z,false);
		//m_3dscreen.TurnShape(32+xStart, axis_X,false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_Z);
		m_3dscreen.TurnMatrix(32+xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(kavHatchalatYom);
	//m_3dscreen.ResetTranslation();
	//m_3dscreen.ResetShift();
	//m_3dscreen.TurnShape(-90, axis_Z,false);
	//m_3dscreen.TurnShape(32+xStart, axis_X,false);
	//m_3dscreen.TurnShape(m_yTurn, axis_Y);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(-90, axis_Z);
	m_3dscreen.TurnMatrix(32+xStart, axis_X);
	m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	PaintResult();
	lasty = m_yTurn;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek23::InitOnSubHeadButton(void)
{
	lasty = 10000000;
	switch(m_buttonId)
	{
	case 2:
		SetTimer(1,timerElaps,NULL);
		break;
	case 1:
	case 0:
		KillTimer(1);
		SetTimer(2,timerElaps,NULL);
		break;
	}
	m_xTurn = 0;
	m_yTurn = yStart;
}

void CPerek23::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 1)
	{
		if(m_xTurn < 355)
			m_xTurn += mahalachShemesh;
		else
			m_xTurn += mahalachShemesh/3;

		if(m_xTurn >= (360+mahalachShemesh))
		{
			m_xTurn = 360+mahalachShemesh;
			KillTimer(1);
			SetTimer(2, 50,NULL);
		}
		else
		{
			if(m_bNoTimerDraw == false)
				Do3DPaint();
		}
	}
	else if(nIDEvent == 2)
	{
		if(m_bNoTimerDraw == false)
			Do3DPaint();
		KillTimer(2);
	}

	CPerek3DBase::OnTimer(nIDEvent);
}

void CPerek23::PaintResult(void)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);

	CRect rc(ipWidth - 150,80, ipWidth,110);
	dc.FillSolidRect(rc,0);



	if(m_buttonId == 2)
	{
		CFont font;
		VERIFY(font.CreateFont(
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

		CString sTxt;
		sTxt.Format("%.4f",m_xTurn);
		int n = dc.SaveDC();
		COLORREF txtcolor = dc.SetTextColor(RGB(255,0,0));
		dc.SetBkMode(TRANSPARENT);
		CFont* pFont = dc.SelectObject(&font);
		dc.DrawText(sTxt, rc, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);
		dc.SelectObject(pFont);
		dc.RestoreDC(n);
	}
	//m_3dscreen.CopyRefresh(rcR);
	//m_3dscreen.OnPaint();
}

BOOL CPerek23::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_EXTRA_DRAW:
		PaintResult();
		return TRUE;
	}

	return CPerek3DBase::OnWndMsg(message, wParam, lParam, pResult);
}
