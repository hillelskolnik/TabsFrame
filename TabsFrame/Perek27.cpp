// Perek27.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek27.h"


// CPerek27

IMPLEMENT_DYNCREATE(CPerek27, CPerek3DBase)

CPerek27::CPerek27()
: trsz(340)
, m_yTurn(0)
, m_xTurn(0)
, trsz2(trsz + 10)
, lasty(1000000)
, ofekAng(5)
, yTurn1(15)
, m_sliderRc(3,0,120, ipHeight)
, m_xTurnShemesh(0)
, m_sliderHorRc(120, ipHeight - 100,ipWidth,ipHeight)
, sShemesh(23)
, yTurn56(20)
, shemeshMesibaFine(1.5)
, shemeshMesibaSize(DiameterSteps(trsz, shemeshMesibaFine))
, m_nMazalotStarsSize(0)
{
	m_IDstart = ID_P27_1;
	m_IDidx = WT_PEREK_27;
	m_IDX_PEREK = IDX_PEREK_27;
}

CPerek27::~CPerek27()
{
}

BEGIN_MESSAGE_MAP(CPerek27, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P27_1, ID_P27_6, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P27_1, ID_P27_6, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CPerek27 diagnostics

#ifdef _DEBUG
void CPerek27::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek27::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG

enum
{
	ofek
	,galgalShemesh
	,kavLekuty
	,galgalMazalot
	,galgalMazalot2
	,galgalMazalot3
	,mesibaYomit
	,hezKivunMesiba1
	,hezKivunMesiba2
	,hezKivunMesibaShem1
	,hezKivunMesibaShem2
	,shemesh
	,mesibatShemshYomi
	,ShemotKarov
	,ShemotRachok
};
// CPerek27 message handlers

int CPerek27::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CMyFBitmap bm33;
	CString path = theApp.m_appPath + "Images\\ShemotKarovHfuch.bmp";
	CImage image44;
	image44.Load(path);
	bm33.CreateMyCompatibleBitmap(NULL, image44.GetWidth(),
		image44.GetHeight());
	image44.BitBlt(bm33.operator CDC *()->GetSafeHdc(),
		CPoint(0,0));
	m_nMazalotStarsSize = image44.GetWidth();

	CMyFBitmap bm66;
	path = theApp.m_appPath + "Images\\ShemotRachokHfuch.bmp";
	CImage image88;
	image88.Load(path);
	bm66.CreateMyCompatibleBitmap(NULL, image88.GetWidth(),
		image88.GetHeight());
	image88.BitBlt(bm66.operator CDC *()->GetSafeHdc(),
		CPoint(0,0));


	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];

	CClientDC dc(this);
	m_memDc.CreateCompatibleDC(&dc);
	m_memBm.CreateCompatibleBitmap(&dc, ipWidth,ipHeight);
	m_memDc.SelectObject(&m_memBm);
	m_memDc.SelectObject(&m_font);


	COLORREF color0 = cp.paragraphs[0].color;
	COLORREF color1 = cp.paragraphs[1].color;
	COLORREF color2 = cp.paragraphs[2].color;
	COLORREF color3 = cp.paragraphs[3].color;
	COLORREF color4 = cp.paragraphs[4].color;
	COLORREF color5 = cp.paragraphs[5].color;

	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 30.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();

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
	m_3dscreen.TurnShape(90.0 + ofekAng, axis_X, false, true);

	m_3dscreen.BeginObject(galgalShemesh);
	m_3dscreen.CReateCircleLineObject(trsz, color0);
	m_3dscreen.TurnShape(90, axis_Y, false, true);
	m_3dscreen.TurnShape(23.5, axis_Z, false, true);
	
	m_3dscreen.BeginObject(kavLekuty);
	m_3dscreen.CReateCircleLineObject(trsz2, color1);
	m_3dscreen.TurnShape(90, axis_Y, false, true);
	m_3dscreen.TurnShape(23.5, axis_Z, false, true);
	

	int mazTrsz = (int)(cos(9.0*D)*(double)trsz);
	double shiftMaz = sin(9.0*D)*(double)trsz * 0.5;
	m_3dscreen.BeginObject(galgalMazalot2);
	m_3dscreen.CReateCircleLineObject(mazTrsz,color2);
	m_3dscreen.ShiftObjectCenter(shiftMaz,axis_Z, true);
	m_3dscreen.TurnObjectCenter(23.5,axis_x, true);
	m_3dscreen.TurnShape(23.5,axis_x, false,true);
	m_3dscreen.TurnObjectCenter(-90,axis_Y, true);
	m_3dscreen.TurnShape(-90,axis_y, false,true);

	m_3dscreen.BeginObject(galgalMazalot3);
	m_3dscreen.CReateCircleLineObject(mazTrsz,color2);
	m_3dscreen.ShiftObjectCenter(-shiftMaz,axis_Z, true);
	m_3dscreen.TurnObjectCenter(23.5,axis_x, true);
	m_3dscreen.TurnShape(23.5,axis_x, false,true);
	m_3dscreen.TurnObjectCenter(-90,axis_Y, true);
	m_3dscreen.TurnShape(-90,axis_y, false,true);


	m_3dscreen.BeginObject(galgalMazalot);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,1080,48,0);
		CDC* pdc = bm1.GetMyPaintDC();
		int n = pdc->SaveDC();
		CPen pen1(PS_SOLID,1,color2);
		pdc->SelectObject(&pen1);
		CPoint topp(0,0);
		CPoint bottomp(0,47);
		CPoint plusp(90,0);
		for(int i = 0; i < 12; ++i, topp += plusp, bottomp += plusp)
		{
			pdc->MoveTo(topp);
			pdc->LineTo(bottomp);
		}

		m_3dscreen.CreateSphereBmObj(trsz,bm1,9,-9);
		pdc->RestoreDC(n);
	}
	m_3dscreen.TurnShape(113.5,axis_x, false,true);
	m_3dscreen.TurnShape(-90,axis_y, false,true);

	m_3dscreen.BeginObject(mesibaYomit);
	m_3dscreen.CReateCircleLineObject(trsz2,color3);
	m_3dscreen.TurnShape(32,axis_X, false, true);
	m_3dscreen.TurnShape(-90,axis_Y, false, true);
	m_3dscreen.TurnShape(ofekAng,axis_X, false, true);


	int kotTrsz = DiameterSteps(9);
	m_3dscreen.BeginObject(hezKivunMesiba1);
	m_3dscreen.CreateCylinderObject(1,9,32, ColDev(color3, 2));
	m_3dscreen.FillRect(0,0,kotTrsz, 32, ColBright(color3, 0.6)
		,fr_zIntensity ,  4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz2/2.0,axis_Z, true);

	m_3dscreen.BeginObject(hezKivunMesiba2);
	m_3dscreen.CreateCylinderObject(1,9,32, ColDev(color3, 2));
	m_3dscreen.FillRect(0,0,kotTrsz, 32, ColBright(color3, 0.6)
		,fr_zIntensity , 5.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz2/2.0,axis_Z, true);
	m_3dscreen.TurnObjectCenter(180,axis_X, true);
	m_3dscreen.TurnShape(180,axis_X, false, true);

	m_3dscreen.BeginObject(hezKivunMesibaShem1);
	m_3dscreen.CreateCylinderObject(9,1,32, ColDev(color4, 2));
	m_3dscreen.FillRect(0,0,kotTrsz, 32, ColBright(color4, 0.6)
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz/2.0,axis_Z, true);
	m_3dscreen.TurnObjectCenter(90,axis_X, true);
	m_3dscreen.TurnShape(90,axis_X, false, true);

	m_3dscreen.BeginObject(hezKivunMesibaShem2);
	m_3dscreen.CreateCylinderObject(9,1,32, ColDev(color4, 2));
	m_3dscreen.FillRect(0,0,kotTrsz, 32, ColBright(color4, 0.6)
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz/2.0,axis_Z, true);
	m_3dscreen.TurnObjectCenter(270,axis_X, true);
	m_3dscreen.TurnShape(270,axis_X, false, true);


	int stepsShem = DiameterSteps(sShemesh);
	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(128,0,0, 0));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(255,128,0,0)
		,fr_zIntensity , (double)sShemesh / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(
		(double)trsz / 2.0,axis_Z, true);

	m_3dscreen.BeginObject(mesibatShemshYomi);
	m_3dscreen.CReateCircleLineObject(trsz, color5, shemeshMesibaFine);
	m_3dscreen.TurnShape(90,axis_y, false,true);


	m_3dscreen.BeginObject(ShemotKarov);
	{
		CDC &dc2 = *(bm33.operator CDC *());
		CBrush br(color5);
		CBrush* obr = dc2.SelectObject(&br);
		dc2.PatBlt(0,0,1080,48,0X00A000C9);
		dc2.SelectObject(obr);
	}
		m_3dscreen.CreateSphereBmObj(trsz,
			bm33,9,-9);
	m_3dscreen.TurnShape(113.5,axis_x, false,true);
	m_3dscreen.TurnShape(-90,axis_y, false,true);

	m_3dscreen.BeginObject(ShemotRachok);
	{
		CDC &dc2 = *(bm66.operator CDC *());
		CBrush br(color5);
		CBrush* obr = dc2.SelectObject(&br);
		dc2.PatBlt(0,0,1080,48,0X00A000C9);
		dc2.SelectObject(obr);
	}
		m_3dscreen.CreateSphereBmObj(trsz,
			bm66,9,-9);
	m_3dscreen.TurnShape(113.5,axis_x, false,true);
	m_3dscreen.TurnShape(-90,axis_y, false,true);


	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek27::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = (p.x > 3)?TRUE:FALSE;


	if(m_bBntDown && m_bHandCursor )
	{
		double cx = (p.x - m_pt.x);
		double cy = (p.y - m_pt.y);

		switch(m_buttonId)
		{
		case 1:
			m_xTurn = cy;
			m_yTurn = cx / 3.0;
			m_yTurn -= yTurn1;
			break;
		case 4:
		case 5:
			if(m_sliderRc.PtInRect(p))
			{
				m_xTurnShemesh = -cy;
			}
			else if(m_sliderHorRc.PtInRect(p))
			{
				m_yTurn = cx / 3.0;
				m_yTurn -= yTurn56;
			}
			else
			{
				m_xTurn = cy;
			}
			break;
		default:
			m_xTurn = cy;
			m_yTurn = cx / 3.0;
			break;
		}

		Do3DPaint();
	}
	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek27::Do3DPaint(void)
{
	if(m_bPastCreate == false || m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(ofek);
	if(lasty == m_yTurn)
	{
		m_3dscreen.Translate3Dto2D(FALSE);
	}
	else
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(galgalShemesh);
	if(true)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		//m_3dscreen.TurnShape(ofekAng, axis_X, false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(ofekAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0 ,OB_PAUSE);

	m_3dscreen.BeginObject(kavLekuty);
	if(m_buttonId < 3 && m_buttonId)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		//m_3dscreen.TurnShape(ofekAng, axis_X, false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(ofekAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0 ,OB_PAUSE);

	m_3dscreen.BeginObject(galgalMazalot);
	if(m_buttonId  >= 2)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		//m_3dscreen.TurnShape(ofekAng, axis_X, false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(ofekAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0 ,OB_PAUSE);

	m_3dscreen.BeginObject(galgalMazalot2);
	if(m_buttonId  >= 2)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		//m_3dscreen.TurnShape(ofekAng, axis_X, false);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(ofekAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0 ,OB_PAUSE);

	m_3dscreen.BeginObject(galgalMazalot3);
	if(m_buttonId  >= 2)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		//m_3dscreen.TurnShape(ofekAng, axis_X, false);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(ofekAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0 ,OB_PAUSE);


	m_3dscreen.BeginObject(mesibaYomit);
	if(m_buttonId  >= 3)
	{
		if(lasty == m_yTurn)
		{
			m_3dscreen.Translate3Dto2D(FALSE);
		}
		else
		{
			m_3dscreen.ResetTranslation();
			m_3dscreen.TurnShape(m_yTurn, axis_Y);
			m_3dscreen.Translate3Dto2D();
		}
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0 ,OB_PAUSE);


	m_3dscreen.BeginObject(hezKivunMesiba1);
	if(m_buttonId >= 3)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		//m_3dscreen.TurnShape(ofekAng, axis_X, false);


		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(ofekAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(hezKivunMesiba2);
	if(m_buttonId >= 3)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		//m_3dscreen.TurnShape(ofekAng, axis_X, false);


		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(ofekAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(hezKivunMesibaShem1);
	if(m_buttonId >= 4)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurnShemesh, axis_X);
		m_3dscreen.TurnShape(m_xTurnShemesh, axis_X, false);
		m_3dscreen.TurnObjectCenter(23.5, axis_Z);
		m_3dscreen.TurnShape(23.5, axis_Z, false);

		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnShape(m_xTurn, axis_X, false);
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		m_3dscreen.TurnShape(32, axis_Z, false);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		m_3dscreen.TurnShape(ofekAng, axis_X, false);


		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(hezKivunMesibaShem2);
	if(m_buttonId >= 4)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurnShemesh, axis_X);
		m_3dscreen.TurnShape(m_xTurnShemesh, axis_X, false);
		m_3dscreen.TurnObjectCenter(23.5, axis_Z);
		m_3dscreen.TurnShape(23.5, axis_Z, false);

		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnShape(m_xTurn, axis_X, false);
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		m_3dscreen.TurnShape(32, axis_Z, false);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		m_3dscreen.TurnShape(ofekAng, axis_X, false);


		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(shemesh);
	if(m_buttonId >= 4)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurnShemesh + 180, axis_X);
		m_3dscreen.TurnObjectCenter(23.5, axis_Z);

		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);

		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(mesibatShemshYomi);
	if(m_buttonId == 5)
	{
		double sinNetya = SinNetyatAliyaYeshara(m_xTurnShemesh, 23.5);
		double shiftX = sinNetya * (double)trsz / 2.0;
		double shrink = cos(asin(sinNetya));
		m_3dscreen.ResetShift();
		m_3dscreen.InitMatrix();
		m_3dscreen.ShiftObjectCenter(shiftX, axis_X);
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		m_3dscreen.TurnMatrix(ofekAng, axis_X);

		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(shrink, axis_S);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(ShemotKarov);
	if(m_buttonId == 5 )
	{
		double step = (double)m_nMazalotStarsSize / 360;
		double startAng = m_xTurn + 280;
		while(startAng > 360)
			startAng -= 360;
		while(startAng < 0)
			startAng += 360;
		int startPos = (int)(startAng * step);
		int size = (int)(step * 160);
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		//m_3dscreen.TurnShape(ofekAng, axis_X, false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(ofekAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D(TRUE, startPos, size);
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(ShemotRachok);
	if(m_buttonId == 5 )
	{
		double step = (double)m_nMazalotStarsSize / 360;
		double startAng = m_xTurn + 100;
		while(startAng > 360)
			startAng -= 360;
		while(startAng < 0)
			startAng += 360;
		int startPos = (int)(startAng * step);
		int size = (int)(step * 160);
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		//m_3dscreen.TurnShape(ofekAng, axis_X, false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(ofekAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D(TRUE, startPos, size);
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	lasty = m_yTurn;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek27::InitOnSubHeadButton(void)
{
	lasty = 1000000;
	switch(m_buttonId)
	{
	case 1:
		m_xTurn = 0;
		m_yTurn = -yTurn1;
		m_xTurnShemesh = 0;
		break;
	case 4:
	case 5:
		m_xTurn = 0;
		m_yTurn = -yTurn56;
		m_xTurnShemesh = 0;
		break;
	default:
		m_xTurnShemesh = 0;
		m_xTurn = 0;
		m_yTurn = 0;
		break;
	}
	PaintSlider();
}

BOOL CPerek27::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_EXTRA_DRAW:
		PaintSlider();
		return TRUE;
	}

	return CPerek3DBase::OnWndMsg(message, wParam, lParam, pResult);
}

void CPerek27::PaintSlider(void)
{
	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];
	COLORREF color = cp.paragraphs[m_buttonId].color;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	CRect rc(0,0,m_sliderRc.Width(),m_sliderRc.Height());
	CRect rc2 = m_sliderHorRc;
	int n = m_memDc.SaveDC();
	m_memDc.FillSolidRect(rc,0);
	m_memDc.FillSolidRect(rc2,0);
	m_memDc.FillSolidRect(rc,0);

	switch(m_buttonId)
	{
	case 4:
	case 5:
		{
			rc.DeflateRect(0,5);
			CBrush br(color);
			m_memDc.FrameRect(rc, &br);

			rc2.DeflateRect(1,1,1,5);
			m_memDc.FrameRect(rc2, &br);
		}
		break;
	}
	dc.BitBlt(m_sliderRc.left,
		m_sliderRc.top,m_sliderRc.Width(),m_sliderRc.Height(),
		&m_memDc,0,0,SRCCOPY);

	dc.BitBlt(m_sliderHorRc.left,
		m_sliderHorRc.top,m_sliderHorRc.Width(),m_sliderHorRc.Height(),
		&m_memDc,m_sliderHorRc.left,m_sliderHorRc.top,SRCCOPY);

	m_memDc.RestoreDC(n);
}
