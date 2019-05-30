// Perek29.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek29.h"


// CPerek29

IMPLEMENT_DYNCREATE(CPerek29, CPerek3DBase)

CPerek29::CPerek29()
: trszArez(100)
, trsz(356)
, m_xStart(5.0)
, m_yStart(5.0)
, m_sliderRc(3,0,120, ipHeight)
, m_sliderHorRc(120, ipHeight - 80,ipWidth,ipHeight)
, m_xTurn2(0)
, lasty(1000000)
, m_fine(3)
, m_trszStep(0.0)
, m_color2(0)
{
	m_trszStep = (double)DiameterSteps(trsz, m_fine)/ 360.0;
	m_IDstart = ID_P29_1;
	m_IDidx = WT_PEREK_29;
	m_IDX_PEREK = IDX_PEREK_29;
}

CPerek29::~CPerek29()
{
}

BEGIN_MESSAGE_MAP(CPerek29, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P29_1, ID_P29_4, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P29_1, ID_P29_4, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CPerek29 diagnostics

#ifdef _DEBUG
void CPerek29::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek29::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek29 message handlers

enum
{
	halal
	,arez
	,mashveHaYom
	,roshIsrael
	,ofek
	,kotevZ
	,kotevD
	,galgalMazalot
	,mesibatHaYomVeHaLayla
	,shemesh
	,lamed
	,mem
	,ayn
	,tav
	,ofanHaziHaYom
	,zafon
	,darom
	,nekudaGalgalMazalot
};


int CPerek29::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];

	CClientDC dc(this);
	m_memDc.CreateCompatibleDC(&dc);
	m_memBm.CreateCompatibleBitmap(&dc, ipWidth,ipHeight);
	m_memDc.SelectObject(&m_memBm);
	m_memDc.SelectObject(&m_font);


	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 30.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();

	COLORREF color0 = cp.paragraphs[0].color;
	COLORREF color1 = cp.paragraphs[1].color;
	COLORREF color2 = cp.paragraphs[2].color;
	COLORREF color3 = cp.paragraphs[3].color;
	m_color2 = color2;

	CImageList imageList;
	imageList.Create(IDB_BITMAP_OTIYUT,9,0,RGB(255,255,128));
	CMyFBitmap bmOtyut;
	bmOtyut.CreateMyCompatibleBitmap(NULL,9,14,0);

	CDC *pDC = bmOtyut.GetMyPaintDC();
	int n = pDC->SaveDC();
	CBrush brOt(RGB(255,255,128));
	pDC->SelectObject(&brOt);

	m_3dscreen.BeginObject(lamed);
	m_3dscreen.CreatObjectPixselMap(9,14);
	imageList.Draw(pDC,12,CPoint(0,0), ILD_IMAGE);
	pDC->PatBlt(0,0,9,14,0X00A000C9);
	m_3dscreen.BitmapToObject(bmOtyut);
	m_3dscreen.ShiftObjectCenter(-(double)trsz /2.0 - 7.0, axis_X, true);

	m_3dscreen.BeginObject(mem);
	m_3dscreen.CreatObjectPixselMap(9,14);
	imageList.Draw(pDC,13,CPoint(0,0), ILD_IMAGE);
	pDC->PatBlt(0,0,9,14,0X00A000C9);
	m_3dscreen.BitmapToObject(bmOtyut);
	m_3dscreen.ShiftObjectCenter((double)trsz /2.0 + 7.0, axis_X, true);

	m_3dscreen.BeginObject(ayn);
	m_3dscreen.CreatObjectPixselMap(9,14);
	imageList.Draw(pDC,18,CPoint(0,0), ILD_IMAGE);
	pDC->PatBlt(0,0,9,14,0X00A000C9);
	m_3dscreen.BitmapToObject(bmOtyut);
	m_3dscreen.ShiftObjectCenter((double)trsz /2.0 + 7.0, axis_Y, true);
	m_3dscreen.TurnObjectCenter(m_xStart, axis_X, true);

	CBrush brTav(color3);
	pDC->SelectObject(&brTav);
	m_3dscreen.BeginObject(tav);
	m_3dscreen.CreatObjectPixselMap(9,14);
	imageList.Draw(pDC,26,CPoint(0,0), ILD_IMAGE);
	pDC->PatBlt(0,0,9,14,0X00A000C9);
	m_3dscreen.BitmapToObject(bmOtyut);
	m_3dscreen.ShiftObjectCenter(((double)trsz /2.0 + 11.0), axis_Y, true);
	m_3dscreen.TurnObjectCenter(30, axis_X, true);
	m_3dscreen.TurnObjectCenter(23.5, axis_Z, true);
	m_3dscreen.TurnObjectCenter(33, axis_X, true);


	CMyFBitmap bmDirection;
	bmDirection.CreateMyCompatibleBitmap(NULL,36,14,0);
	CPoint p(0,0);

	pDC = bmDirection.GetMyPaintDC();
	CBrush brZafon(color3);
	pDC->SelectObject(&brZafon);
	p.x = 0;
	imageList.Draw(pDC,16,p, ILD_IMAGE);
	p.x += 9;
	imageList.Draw(pDC,5,p, ILD_IMAGE);
	p.x += 9;
	imageList.Draw(pDC,19,p, ILD_IMAGE);
	p.x += 9;
	imageList.Draw(pDC,21,p, ILD_IMAGE);
	pDC->PatBlt(0,0,36,14,0X00A000C9);
	m_3dscreen.BeginObject(zafon);
	m_3dscreen.CreatObjectPixselMap(36,14);
	m_3dscreen.BitmapToObject(bmDirection);
	m_3dscreen.ShiftObjectCenter(-(double)trsz /2.0 - 20.0, axis_X, true);
	m_3dscreen.TurnObjectCenter(3.5, axis_Z, true);

	pDC = bmDirection.GetMyPaintDC();
	p.x = 0;
	imageList.Draw(pDC,14,p, ILD_IMAGE);
	p.x += 9;
	imageList.Draw(pDC,5,p, ILD_IMAGE);
	p.x += 9;
	imageList.Draw(pDC,24,p, ILD_IMAGE);
	p.x += 9;
	imageList.Draw(pDC,3,p, ILD_IMAGE);
	pDC->PatBlt(0,0,36,14,0X00A000C9);
	m_3dscreen.BeginObject(darom);
	m_3dscreen.CreatObjectPixselMap(36,14);
	m_3dscreen.BitmapToObject(bmDirection);
	m_3dscreen.ShiftObjectCenter((double)trsz /2.0 + 20.0, axis_X, true);
	m_3dscreen.TurnObjectCenter(-3.5, axis_Z, true);

	pDC->RestoreDC(n);


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

	steps = DiameterSteps(trsz);
	m_3dscreen.BeginObject(mashveHaYom);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(33,135,124));
	m_3dscreen.TurnShape(90.0, axis_Y, false, true);

	int kotTrsz = DiameterSteps(9);


	m_3dscreen.BeginObject(nekudaGalgalMazalot);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(/*RGB(255,128,128)*/color2, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(/*RGB(255,128,128)*/color2,0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2.0, axis_Y, true);

	m_3dscreen.BeginObject(ofek);
	m_3dscreen.CReateCircleLineObject(trsz, color0, m_fine);
	m_3dscreen.TurnShape(90 + m_xStart,axis_X, false, true);

	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(255,128,255));
	m_3dscreen.TurnShape(90 ,axis_Y, false, true);
	m_3dscreen.TurnShape(23.5 ,axis_Z, false, true);

	m_3dscreen.BeginObject(ofanHaziHaYom);
	m_3dscreen.CReateCircleLineObject(trsz, color1, m_fine);
	m_3dscreen.TurnShape(m_xStart,axis_X, false, true);

	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek29::OnMouseMove(UINT nFlags, CPoint point)
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
		case 2:
		case 3:
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
		default:
			m_xTurn = cy ;
			m_yTurn = cx / 4.0;
			break;
		}

		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek29::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(arez);
	if(true)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(- m_xStart - m_xTurn, axis_X);
		m_3dscreen.TurnShape(180.0 + m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(ofek);
	if(m_buttonId < 2)
	{
		if(lasty != m_yTurn)
		{
			m_3dscreen.ResetTranslation();
			m_3dscreen.TurnShape(m_yTurn,axis_Y);
			m_3dscreen.Translate3Dto2D();
		}
		else
		{
			m_3dscreen.Translate3Dto2D(FALSE);
		}
	}
	else if(m_buttonId >= 2)
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
			m_color2, fr_paintTranslated);
		m_3dscreen.TurnShape(m_yTurn,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(ofanHaziHaYom);
	if(m_buttonId == 1)
	{
		if(lasty != m_yTurn)
		{
			m_3dscreen.ResetTranslation();
			m_3dscreen.TurnShape(m_yTurn,axis_Y);
			m_3dscreen.Translate3Dto2D();
		}
		else
		{
			m_3dscreen.Translate3Dto2D(FALSE);
		}
	}
	else if(m_buttonId >= 2)
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
			m_color2, fr_paintTranslated);
		m_3dscreen.TurnShape(m_yTurn,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(galgalMazalot);
	if(m_buttonId >= 2)
	{
		double ay = AliyaYeshara(m_xTurn2+90, 23.5);
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(ay + m_xStart /*+ m_xTurn2*/,axis_X, false);
		m_3dscreen.TurnShape(m_yTurn,axis_Y);
		m_3dscreen.Translate3Dto2D();

	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	
	m_3dscreen.BeginObject(nekudaGalgalMazalot);
	if(m_buttonId >= 2)
	{
		m_3dscreen.ResetTranslation();
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


	m_3dscreen.BeginObject(mashveHaYom);
	if(m_buttonId >= 2)
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
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(zafon);
	if(m_buttonId >= 2)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(darom);
	if(m_buttonId >= 2)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(lamed);
	if(m_buttonId == 3)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(mem);
	if(m_buttonId == 3)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(ayn);
	if(m_buttonId == 3 )
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(tav);
	if(m_buttonId == 3 )
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn2,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	lasty = m_yTurn;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek29::PaintSlider(void)
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
	//case 0:
	case 2:
	case 3:
		{
			rc.DeflateRect(0,5);
			CBrush br(color);
			m_memDc.FrameRect(rc, &br);
		}
		break;
	//case 2:
	//case 3:
	//case 4:
	//case 9:
	//case 10:
	//case 13:
	//case 15:
	//	{
	//		rc.DeflateRect(0,5);
	//		CBrush br(color);
	//		m_memDc.FrameRect(rc, &br);

	//		rc2.DeflateRect(1,1,1,5);
	//		m_memDc.FrameRect(rc2, &br);
	//	}
	//	break;
	}

	dc.BitBlt(m_sliderRc.left,
		m_sliderRc.top,m_sliderRc.Width(),m_sliderRc.Height(),
		&m_memDc,0,0,SRCCOPY);

	dc.BitBlt(m_sliderHorRc.left,
		m_sliderHorRc.top,m_sliderHorRc.Width(),m_sliderHorRc.Height(),
		&m_memDc,m_sliderHorRc.left,m_sliderHorRc.top,SRCCOPY);

	m_memDc.RestoreDC(n);
}

void CPerek29::InitOnSubHeadButton(void)
{
	lasty = 1000000;
	m_yTurn = m_yStart;
	m_xTurn = 0;
	m_xTurn2 = (m_buttonId == 3)?-60:0;
	PaintSlider();
}

BOOL CPerek29::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_EXTRA_DRAW:
		PaintSlider();
		return TRUE;
	}

	return CPerek3DBase::OnWndMsg(message, wParam, lParam, pResult);
}
