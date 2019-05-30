// Perek30.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek30.h"


// CPerek30

IMPLEMENT_DYNCREATE(CPerek30, CPerek3DBase)

CPerek30::CPerek30()
: trszArez(50)
, trsz(356)
, m_fine(2.4)
, m_trszStep((double)DiameterSteps(trsz, m_fine)/ 360.0)
, m_xStart(5.0)
, m_yStart(5.0)
, m_xTurn2(0)
, m_sliderRc(3,0,120, ipHeight)
, m_sliderHorRc(120, ipHeight - 80,ipWidth,ipHeight)
, lasty(1000000)
, m_color1(0)
, m_xTurn3(0)
, m_bRightBDown(false)
, m_fineMashve(1.5)
{
	//m_trszStep = DiameterSteps(trsz, m_fine);
	m_IDstart = ID_P30_1;
	m_IDidx = WT_PEREK_30;
	m_IDX_PEREK = IDX_PEREK_30;
}

CPerek30::~CPerek30()
{
}

BEGIN_MESSAGE_MAP(CPerek30, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P30_1, ID_P30_9, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P30_1, ID_P30_9, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// CPerek30 drawing


// CPerek30 diagnostics

#ifdef _DEBUG
void CPerek30::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek30::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek30 message handlers
enum
{
	halal
	,arez
	,mashveHaYom
	,ofanHaziHaYom
	,nekudaMshve
	,nekudaGalgalMazalot
	,ofek
	,galgalMazalot
	,mesibatNekudatMazalot
	,nekudatMazalot
	,nekudatOleYomi
	,zavitHaNekudot

	,het

	,otiyotMazalot
	,otiyotMashve = 40
	,kavim = 50
};


int CPerek30::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

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


	COLORREF color0 = cp.paragraphs[0].color;
	COLORREF color1 = m_color1 = cp.paragraphs[1].color;
	COLORREF color2 = cp.paragraphs[2].color;
	COLORREF color3 = cp.paragraphs[3].color;
	color4 = cp.paragraphs[4].color;
	color5 = cp.paragraphs[5].color;
	COLORREF color6 = cp.paragraphs[6].color;
	color7 = cp.paragraphs[7].color;
	color8 = cp.paragraphs[8].color;

	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 30.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();

	int steps = DiameterSteps(trsz);
	m_3dscreen.BeginObject(halal);
	m_3dscreen.CreateSphereObject(trsz, RGBT(48,48,48, 0));
	m_3dscreen.FillRect(0,0,steps, steps/2, RGBT(0,0,0,0)
		,fr_zIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();
	m_3dscreen.ScreenToDC(TRUE);
	m_3dscreen.ClearScreen();
	m_3dscreen.DeleteObject(halal);

	m_3dscreen.BeginObject(arez);
	m_3dscreen.CreateSphereObject(trszArez, RGBT2(color2, 95));
	m_3dscreen.BitmapToObject(bm11, RGBT2(0,0));
	m_3dscreen.TurnShape(-90.0, axis_Z, false,true);
	m_3dscreen.ResetTranslation();


	m_3dscreen.BeginObject(mashveHaYom);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(33,135,124),m_fineMashve);
	m_3dscreen.TurnShape(270.0, axis_Y, false, true);


	m_3dscreen.BeginObject(ofanHaziHaYom);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(106,0,106), m_fine);

	int kotTrsz = DiameterSteps(9);

	m_3dscreen.BeginObject(nekudaMshve);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color0, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color0,0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2.0, axis_Y, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(nekudaGalgalMazalot);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color2, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color2,0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2.0, axis_Y, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(nekudatMazalot);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color3, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color3,0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz/2.0, axis_Z, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(nekudatOleYomi);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color3, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color3,0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz/2.0, axis_Z, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(255,128,255),m_fineMashve);
	m_3dscreen.TurnShape(270 ,axis_Y, false, true);

	m_3dscreen.BeginObject(ofek);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(128,64,0), m_fine);

	m_3dscreen.BeginObject(mesibatNekudatMazalot);
	m_3dscreen.CReateCircleLineObject(trsz, color3,m_fine);
	m_3dscreen.TurnShape(270,axis_y, false,true);

	m_3dscreen.BeginObject(zavitHaNekudot);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(255,255,255), 1.0, 180.0);


	CString sOtiyot = "טשתסאבםעקגדד";
	char cAlef = 'א';
	CImageList imageList;
	imageList.Create(IDB_BITMAP_OTIYUT,9,0,RGB(255,255,128));
	CMyFBitmap bmOtyut;
	bmOtyut.CreateMyCompatibleBitmap(NULL,9,14,0);

	double ang = 0;
	for(int i = otiyotMazalot; i < (otiyotMazalot + 12); ++i, ang+=30.0)
	{
		CDC *pDC = bmOtyut.GetMyPaintDC();
		int n = pDC->SaveDC();
		CBrush brOt(RGB(255,255,128));
		CBrush *obr = pDC->SelectObject(&brOt);

		m_3dscreen.BeginObject(i);
		m_3dscreen.CreatObjectPixselMap(9,14);
		imageList.Draw(pDC, sOtiyot[i-otiyotMazalot]-cAlef, CPoint(0,0), ILD_IMAGE);
		pDC->PatBlt(0,0,9,14,0X00A000C9);
		m_3dscreen.BitmapToObject(bmOtyut);
		m_3dscreen.ShiftObjectCenter(-(double)trsz /2.0 - 7.0, axis_Z, true);

		m_3dscreen.TurnObjectCenter(3.5, axis_Y, true);
		m_3dscreen.TurnObjectCenter(ang, axis_X, true);
		m_3dscreen.TurnObjectCenter(23.5, axis_Z, true);
		m_3dscreen.ResetTranslation();


		pDC->SelectObject(obr);
		pDC->RestoreDC(n);
	}

	{
		CDC *pDC = bmOtyut.GetMyPaintDC();
		int n = pDC->SaveDC();
		CBrush brOt(RGB(255,255,128));
		CBrush *obr = pDC->SelectObject(&brOt);

		m_3dscreen.BeginObject(het);
		m_3dscreen.CreatObjectPixselMap(9,14);
		imageList.Draw(pDC, 'ח'-cAlef, CPoint(0,0), ILD_IMAGE);
		pDC->PatBlt(0,0,9,14,0X00A000C9);
		m_3dscreen.BitmapToObject(bmOtyut);
		m_3dscreen.ShiftObjectCenter(-(double)trsz /2.0 - 7.0, axis_Z, true);

		m_3dscreen.TurnObjectCenter(33.5, axis_Y, true);
		m_3dscreen.TurnObjectCenter(AliyaYeshara(60, 23.5), axis_X, true);
		m_3dscreen.ResetTranslation();


		pDC->SelectObject(obr);
		pDC->RestoreDC(n);
	}

	ang = 30;
	sOtiyot = "קעו";
	for(int i = otiyotMashve; i < (otiyotMashve + 3); ++i, ang+=30.0)
	{
		CDC *pDC = bmOtyut.GetMyPaintDC();
		int n = pDC->SaveDC();
		CBrush brOt(RGB(255,255,128));
		CBrush *obr = pDC->SelectObject(&brOt);

		m_3dscreen.BeginObject(i);
		m_3dscreen.CreatObjectPixselMap(9,14);
		imageList.Draw(pDC, sOtiyot[i-otiyotMashve]-cAlef, CPoint(0,0), ILD_IMAGE);
		pDC->PatBlt(0,0,9,14,0X00A000C9);
		m_3dscreen.BitmapToObject(bmOtyut);
		m_3dscreen.ShiftObjectCenter(-(double)trsz /2.0 - 7.0, axis_Z, true);

		m_3dscreen.TurnObjectCenter(-3.5, axis_Y, true);
		m_3dscreen.TurnObjectCenter(AliyaYeshara(ang, 23.5), axis_X, true);
		m_3dscreen.ResetTranslation();


		pDC->SelectObject(obr);
		pDC->RestoreDC(n);
	}


	ang = 30;
	for(int i = kavim; i < (kavim + 4); ++i, ang+=30.0)
	{
		m_3dscreen.BeginObject(i);
		m_3dscreen.CReateCircleLineObject(trsz, color7, 1.0, 180.0);
		m_3dscreen.TurnShape(AliyaYeshara(ang, 23.5)+90, axis_X, false, true);
	}


	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek30::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = (p.x > 3)?TRUE:FALSE;


	if((m_bBntDown || m_bRightBDown) && m_bHandCursor )
	{
		double cx = (p.x - m_pt.x);
		double cy = (p.y - m_pt.y);

		switch(m_buttonId)
		{
		case 1:
		case 2:
			if(m_sliderRc.PtInRect(p))
			{
				m_xTurn2 = cy ;
			}
			else
			{
				m_yTurn = cx /2.5;
				m_yTurn += m_yStart;
				m_xTurn = cy /2;
			}
			break;
		case 3:
			if(m_sliderRc.PtInRect(p))
			{
				m_xTurn2 = cy ;
			}
			else if(m_sliderHorRc.PtInRect(p))
			{
				m_yTurn = cx /2.5;
				m_yTurn += m_yStart;
			}
			else if(m_bRightBDown)
			{
				m_xTurn = cy ;
			}
			else
			{
				m_xTurn3 = cy;
			}
			break;
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			if(m_sliderRc.PtInRect(p))
			{
				m_xTurn3 = cy;
				if(m_buttonId == 7)
				{
					m_xTurn3 /= 2.0;
					m_xTurn3 += 180;
				}
				else if(m_buttonId >= 6)
					m_xTurn3 /= 2.0;
			}
			else if(m_sliderHorRc.PtInRect(p))
			{
				m_yTurn = cx /2.5;
				if(m_buttonId != 7)
					m_yTurn += m_yStart;
			}
			else if(m_bRightBDown)
			{
				m_xTurn = cy ;
			}
			else
			{
				m_xTurn2 = cy ;
			}
			break;
		default:
			m_xTurn = cy ;
			m_yTurn = cx / 4.0;
			break;
		}

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek30::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	double plus7 = (m_buttonId == 7)?m_xTurn2:0;

	CFillRectData data2;
	data2.vec = 0.45;
	data2.radius = (double)trsz/2.0;


	m_3dscreen.BeginObject(arez);
	if(m_buttonId < 4)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(- m_xStart - m_xTurn, axis_X);
		//m_3dscreen.TurnShape(180.0 + m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(- m_xStart - m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(180.0 + m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId >= 4)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(- m_xStart + m_xTurn, axis_X);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(- m_xStart + m_xTurn, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(mashveHaYom);
	if(m_buttonId < 3)
	{
		if(lasty != m_yTurn)
		{
			m_3dscreen.ResetTranslation();
			m_3dscreen.TurnShape(m_xStart, axis_X, false);
			m_3dscreen.TurnShape(m_yTurn,axis_Y);
			m_3dscreen.Translate3Dto2D();
		}
		else
		{
			m_3dscreen.Translate3Dto2D(FALSE);
		}
	}
	else if(m_buttonId == 3)
	{
		static int steps = DiameterSteps(trsz, m_fineMashve);
		double xTurn3 = -m_xTurn3;
		while(xTurn3 > 360)
			xTurn3 -= 360;
		while(xTurn3 < 0)
			xTurn3 += 360;
		int x3Steps = (int)(((double)steps / 360.0) * xTurn3);

		m_3dscreen.ResetTranslation();
		m_3dscreen.FillRect(0,0,x3Steps,3, RGB(255,255,255),fr_paintTranslated);
		m_3dscreen.TurnShape(m_xStart, axis_X, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		m_3dscreen.FillRect(0,0,steps,3, 0,fr_zIntensityAll, data2);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId >= 4)
	{
		static int steps = DiameterSteps(trsz, m_fineMashve);
		double xTurn3 = -m_xTurn3;
		while(xTurn3 > 360)
			xTurn3 -= 360;
		while(xTurn3 < 0)
			xTurn3 += 360;

		xTurn3 = AliyaYeshara(xTurn3,23.5);
		int x3Steps = (int)(((double)steps / 360.0) * xTurn3);

		m_3dscreen.ResetTranslation();
		m_3dscreen.FillRect(0,0,x3Steps,3, color4,fr_paintTranslated);
		m_3dscreen.TurnShape(m_xStart + plus7, axis_X, false);
		m_3dscreen.TurnShape(m_yTurn,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(ofanHaziHaYom);
	if(m_buttonId == 0 || m_buttonId > 3)
	{
		if(lasty != m_yTurn || m_buttonId == 7)
		{
			m_3dscreen.ResetTranslation();
			m_3dscreen.TurnShape(m_xStart + plus7,axis_X, false);
			m_3dscreen.TurnShape(m_yTurn,axis_Y);
			m_3dscreen.Translate3Dto2D();
		}
		else
		{
			m_3dscreen.Translate3Dto2D(FALSE);
		}
	}
	else if(m_buttonId >= 1)
	{
		double aliyaYeshara = asin(SinNetyatAliyaYeshara(-m_xTurn2, 23.5))*ToD;
		double steps = fabs(aliyaYeshara * m_trszStep);
		double startSteps = m_trszStep * 90.0;
		if(aliyaYeshara < 0)
		{
			startSteps -= steps-1;
		}

		m_3dscreen.ResetTranslation();
		m_3dscreen.FillRect((int)startSteps,0,(int)steps,3,
			m_color1, fr_paintTranslated);
		m_3dscreen.TurnShape(m_xStart,axis_X, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		static int steps2 = DiameterSteps(trsz, m_fineMashve);
		m_3dscreen.FillRect(0,0,steps2,3, 0,fr_zIntensityAll, data2);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekudaMshve);
	if(m_buttonId < 4)
	{
//		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();

		m_3dscreen.TurnObjectCenter(m_xStart,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);


		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekudaGalgalMazalot);
	if(m_buttonId >= 2 && m_buttonId < 4)
	{
//		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();

		double aliyaYeshara = asin(SinNetyatAliyaYeshara(-m_xTurn2, 23.5))*ToD;
		m_3dscreen.TurnObjectCenter(aliyaYeshara,axis_Z);
		m_3dscreen.TurnObjectCenter(m_xStart,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);


		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(galgalMazalot);
	if(m_buttonId >= 2 && m_buttonId < 4)
	{
		double ay = AliyaYeshara(m_xTurn2, 23.5);
		m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(23.5 ,axis_Z, false);
		//m_3dscreen.TurnShape(ay + m_xStart+90 /*+ m_xTurn2*/,axis_X, false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(23.5 ,axis_Z);
		m_3dscreen.TurnMatrix(ay + m_xStart+90 /*+ m_xTurn2*/,axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform(false);
		static int steps = DiameterSteps(trsz, m_fineMashve);
		m_3dscreen.FillRect(0,0,steps,3, 0,fr_zIntensityAll, data2);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();

	}
	else if(m_buttonId >= 5)
	{
		static int steps = DiameterSteps(trsz, m_fineMashve);
		double xTurn3 = -m_xTurn3;
		while(xTurn3 > 360)
			xTurn3 -= 360;
		while(xTurn3 < 0)
			xTurn3 += 360;

		int x3Steps = (int)(((double)steps / 360.0) * xTurn3);

		double ay = AliyaYeshara(m_xTurn3, 23.5);
		m_3dscreen.ResetTranslation();
		m_3dscreen.FillRect(0,0,x3Steps,3, color5,fr_paintTranslated);

		//m_3dscreen.TurnShape(203.5 ,axis_Z, false);
		//m_3dscreen.TurnShape(ay + m_xStart  + plus7 ,axis_X, false);
		//m_3dscreen.TurnShape(m_yTurn,axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(203.5 ,axis_Z);
		m_3dscreen.TurnMatrix(ay + m_xStart  + plus7,axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(ofek);
	if(m_buttonId >= 4)
	{
		if(lasty != m_yTurn || m_buttonId == 7)
		{
			m_3dscreen.ResetTranslation();
			m_3dscreen.TurnShape(90 + m_xStart + plus7,axis_X, false);
			m_3dscreen.TurnShape(m_yTurn,axis_Y);
			m_3dscreen.Translate3Dto2D();
		}
		else
		{
			m_3dscreen.Translate3Dto2D(FALSE);
		}
	}
	else if(m_buttonId >= 3)
	{
		double aliyaYeshara = asin(SinNetyatAliyaYeshara(-m_xTurn2, 23.5))*ToD;
		double steps = fabs(aliyaYeshara * m_trszStep);
		double startSteps = m_trszStep * 90.0;
		if(aliyaYeshara < 0)
		{
			startSteps -= steps-1;
		}

		m_3dscreen.ResetTranslation();
		m_3dscreen.FillRect((int)startSteps,0,(int)steps,3,
			m_color1, fr_paintTranslated);
		m_3dscreen.TurnShape(90 + m_xStart + plus7,axis_X, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		static int steps2 = DiameterSteps(trsz, m_fineMashve);
		m_3dscreen.FillRect(0,0,steps2,3, 0,fr_zIntensityAll, data2);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(mesibatNekudatMazalot);
	if(m_buttonId == 3)
	{
		static int steps = DiameterSteps(trsz,m_fine);
		double sinNetya = SinNetyatAliyaYeshara(m_xTurn2, 23.5);
		double shiftX = sinNetya * (double)trsz / 2.0;
		double shrink = cos(asin(sinNetya));

		double xTurn3 = -m_xTurn3;
		while(xTurn3 > 360)
			xTurn3 -= 360;
		while(xTurn3 < 0)
			xTurn3 += 360;
		int x3Steps = (int)(((double)steps / 360.0) * xTurn3);

		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.InitMatrix();
		//m_3dscreen.FillRect(0,0,steps + 1,3,0,fr_shrink, shrink);
		m_3dscreen.FillRect(0,0,x3Steps,3, RGB(255,255,255),fr_paintTranslated);

		m_3dscreen.ShiftObjectCenter(shiftX, axis_X);
		//m_3dscreen.TurnShape(m_xStart, axis_X, false);
		m_3dscreen.TurnMatrix(m_xStart, axis_X);

		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(shrink, axis_S);
		m_3dscreen.Transform(false);
		m_3dscreen.FillRect(0,0,steps,3, 0,fr_zIntensityAll, data2);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekudatMazalot);
	if(m_buttonId == 3)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		double aliyaYeshara = asin(SinNetyatAliyaYeshara(m_xTurn2, 23.5))*ToD;
		m_3dscreen.TurnObjectCenter(aliyaYeshara, axis_Y);
		m_3dscreen.TurnObjectCenter(m_xTurn3 + m_xStart, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekudatOleYomi);
	if(m_buttonId == 3)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn3 + m_xStart, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(zavitHaNekudot);
	if(m_buttonId == 3)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(m_xTurn3 + m_xStart + 90.0, axis_X, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId >= 4)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(AliyaYeshara(m_xTurn3, 23.5) + m_xStart + 90.0 + plus7, axis_X, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	double ayOt = AliyaYeshara(m_xTurn3, 23.5);
	for(int i = otiyotMazalot; i < (otiyotMazalot + 12); ++i)
	{
		m_3dscreen.BeginObject(i);
		if(m_buttonId >= 6)
		{
			//m_3dscreen.ResetTranslation();
			m_3dscreen.ResetShift();

			m_3dscreen.TurnObjectCenter(ayOt + m_xStart + plus7, axis_X);
			m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
			m_3dscreen.TurnShape(0.0, axis_Y);
			m_3dscreen.Translate3Dto2D();
		}
		else
			m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	for(int i = otiyotMashve; i < (otiyotMashve + 3); ++i)
	{
		m_3dscreen.BeginObject(i);
		if(m_buttonId == 7)
		{
			//m_3dscreen.ResetTranslation();
			m_3dscreen.ResetShift();

			m_3dscreen.TurnObjectCenter(ayOt + m_xStart + plus7, axis_X);
			m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
			m_3dscreen.TurnShape(0.0, axis_Y);
			m_3dscreen.Translate3Dto2D();
		}
		else
			m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	for(int i = kavim; i < (kavim + 4); ++i)
	{
		m_3dscreen.BeginObject(i);
		if(m_buttonId == 7)
		{
			//m_3dscreen.ResetTranslation();
			//m_3dscreen.ResetShift();

			//m_3dscreen.TurnShape(ayOt + m_xStart + plus7, axis_X, false);
			//m_3dscreen.TurnShape(m_yTurn, axis_Y);
			m_3dscreen.InitMatrix();
			m_3dscreen.TurnMatrix(ayOt + m_xStart + plus7, axis_X);
			m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
			m_3dscreen.Transform();
			m_3dscreen.Translate3Dto2D();
		}
		else
			m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(het);
	if(m_buttonId == 7)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();

		m_3dscreen.TurnObjectCenter(ayOt + m_xStart + plus7, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	PaintResult();
	lasty = m_yTurn;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek30::InitOnSubHeadButton(void)
{
	lasty = 1000000;

	switch(m_buttonId)
	{
	case 1:
	case 2:
		m_xStart = 5.0;
		m_yTurn = m_yStart;
		m_xTurn = 0;
		m_xTurn2 = -60;
		m_xTurn3 = 0;
		break;
	case 3:
		m_xStart = 5.0;
		m_yTurn = m_yStart;
		m_xTurn = 0;
		m_xTurn2 = 90;
		m_xTurn3 = -20;
		break;
	case 7:
		m_xStart = 0.0;
		m_yTurn = 0;
		m_xTurn = 0;
		m_xTurn2 = 0;
		m_xTurn3 = 180;
		break;
	default:
		m_xStart = 5.0;
		m_yTurn = m_yStart;
		m_xTurn = 0;
		m_xTurn2 = 0;
		m_xTurn3 = 0;
		break;
	}
	PaintSlider();
}

void CPerek30::PaintSlider(void)
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
	switch(m_buttonId)
	{
	case 1:
	case 2:
		{
			rc.DeflateRect(0,5);
			CBrush br(color);
			m_memDc.FrameRect(rc, &br);
		}
		break;
	case 6:
	case 7:
	case 8:
		{
			CDC dcTemp;
			dcTemp.CreateCompatibleDC(&dc);
			CBitmap *old = dcTemp.SelectObject(&m_bmMazalot);

			dc.BitBlt(ipWidth-90, 340, 90, 320, &dcTemp,0,0,SRCCOPY);


			dcTemp.SelectObject(old);
		}
	case 3:
	case 4:
	case 5:
		{
			rc.DeflateRect(0,5);
			CBrush br(color);
			m_memDc.FrameRect(rc, &br);

			rc2.DeflateRect(1,1,1,5);
			m_memDc.FrameRect(rc2, &br);

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

			CString sTxt = "לחיצה ימנית ושמאלית";
			COLORREF txtcolor = m_memDc.SetTextColor(RGB(0,0,255));
			m_memDc.SetBkMode(TRANSPARENT);
			CFont* pFont = m_memDc.SelectObject(&font);
			m_memDc.DrawText(sTxt, rc2, 
				DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);
			m_memDc.SelectObject(pFont);
			m_memDc.SetTextColor(txtcolor);
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

BOOL CPerek30::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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

void CPerek30::OnRButtonDown(UINT nFlags, CPoint point)
{
	switch(m_buttonId)
	{
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		m_bRightBDown = true;
		break;
	}

	CPerek3DBase::OnRButtonDown(nFlags, point);
}

void CPerek30::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_bRightBDown = false;

	CPerek3DBase::OnRButtonUp(nFlags, point);
}

void CPerek30::PaintResult(void)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);

	int n = m_memDc.SaveDC();
	CRect rc(ipWidth - 150,140, ipWidth,230);
	m_memDc.FillSolidRect(rc,0);

	CRect rc2(ipWidth - 150,250, ipWidth,310);
	m_memDc.FillSolidRect(rc2,0);

	static CFont font;
	if(font.operator HFONT() == NULL)
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
	if(m_buttonId == 6 || m_buttonId == 7)
	{

		double xTurn3 = -m_xTurn3;
		while(xTurn3 > 360)
			xTurn3 -= 360;
		while(xTurn3 < 0)
			xTurn3 += 360;

		double t3 = floor(xTurn3);
		t3 = (xTurn3 - t3) * 60;
		xTurn3 = floor(xTurn3);

		double ay = AliyaYeshara(xTurn3,23.5);
		double tay = floor(ay);
		tay = (ay - tay) * 60;
		ay = floor(ay);

		CString sTxt;
		m_memDc.SetBkMode(TRANSPARENT);
		CFont* pFont = m_memDc.SelectObject(&font);

		sTxt.Format("%s\n%3.0f %-2.0f\'", "גלגל המזלות",xTurn3, t3 );
		COLORREF txtcolor = m_memDc.SetTextColor(color5);
		m_memDc.DrawText(sTxt, rc, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);

		sTxt.Format("%s\n%3.0f %-2.0f\'", "משוה היום",ay, tay );
		txtcolor = m_memDc.SetTextColor(color4);
		m_memDc.DrawText(sTxt, rc2, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);


		m_memDc.SetTextColor(txtcolor);
		m_memDc.SelectObject(pFont);
	}
	else if(m_buttonId == 8)
	{
		double xTurn3 = -m_xTurn3;
		while(xTurn3 > 360)
			xTurn3 -= 360;
		while(xTurn3 < 0)
			xTurn3 += 360;

		double t3 = floor(xTurn3);
		t3 = (xTurn3 - t3) * 60;
		xTurn3 = floor(xTurn3);

		double ayMin = AliyaYeshara(xTurn3 - 0.5,23.5);
		double ayMax = AliyaYeshara(xTurn3 + 0.5,23.5);
		if(ayMin > ayMax)
			ayMax += 360.0;
		double result = ayMax - ayMin;
		result -= 1.0;
		result *= 60.0;

		m_memDc.SetBkMode(TRANSPARENT);
		CFont* pFont = m_memDc.SelectObject(&font);
		COLORREF txtcolor = m_memDc.SetTextColor(color8);


		CString sTxt;
		sTxt.Format("%s\n%2.0f\'", "תוספת או גראון עלית המשוה",result);
		m_memDc.DrawText(sTxt, rc, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);

		sTxt.Format("%s\n%3.0f %-2.0f\'", "מעלות המזל",xTurn3, t3 );
		txtcolor = m_memDc.SetTextColor(color5);
		m_memDc.DrawText(sTxt, rc2, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);

		m_memDc.SetTextColor(txtcolor);
		m_memDc.SelectObject(pFont);
	}

	dc.BitBlt(rc.left,
		rc.top,rc.Width(),rc.Height(),
		&m_memDc,rc.left,rc.top,SRCCOPY);

	dc.BitBlt(rc2.left,
		rc2.top,rc2.Width(),rc2.Height(),
		&m_memDc,rc2.left,rc2.top,SRCCOPY);


	m_memDc.RestoreDC(n);
}
