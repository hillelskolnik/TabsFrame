// Perek11.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek11.h"


// CPerek11

IMPLEMENT_DYNCREATE(CPerek11, CPerek3DBase)

CPerek11::CPerek11()
{
	m_yTurn = m_xTurn = 7.5;

	m_IDstart = ID_P11_1;
	m_IDidx = WT_PEREK_11;
	m_IDX_PEREK = IDX_PEREK_11;
}

CPerek11::~CPerek11()
{
}

BEGIN_MESSAGE_MAP(CPerek11, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P11_1, ID_P11_6, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P11_1, ID_P11_6, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek11 drawing


// CPerek11 diagnostics

#ifdef _DEBUG
void CPerek11::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek11::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek11 message handlers
enum
{
	 eMuzak = 0
	,eRadius
	,eBariach
	,eGavnunit
	,eKarurit
	,eMavdil
	,eCador // must be last
};
int CPerek11::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);


	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];
	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 45.0, 3.0, 7.0);
	m_3dscreen.CreateScreenDC();

	int trsz = 296;
	int kotTrsz = DiameterSteps(7);

	m_3dscreen.BeginObject(eMuzak);
	m_3dscreen.CreateSphereObject(7, 
		ColDev(cp.paragraphs[1].color, 2));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(cp.paragraphs[1].color,0.6)
		,fr_zSquareIntensity , 3.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(0.0,axis_x);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(eRadius);
	m_3dscreen.CreateCylinderObject(3,5,trsz/2, 
		RGBT2(cp.paragraphs[2].color, 30)
		,360.0);
	m_3dscreen.ShiftObjectCenter((double)trsz / 4.0, axis_Y, true);
	m_3dscreen.TurnObjectCenter(270.0, axis_Z, true);
	m_3dscreen.TurnShape(270.0, axis_Z, false, true);
	m_3dscreen.TurnObjectCenter(-90.0, axis_Y, true);
	m_3dscreen.TurnShape(-90.0, axis_Y, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(eBariach);
	m_3dscreen.CreateCylinderObject(6,6,trsz, 
		RGBT2(cp.paragraphs[3].color, 30)
		,360.0);
	m_3dscreen.TurnShape(90.0, axis_Z, false, true);
	m_3dscreen.TurnShape(-90.0, axis_Y, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();


	double turnx = 20;

	double steps = DiameterSteps(trsz + 2);
	double deg = steps/360;
	m_3dscreen.BeginObject(eGavnunit);
	m_3dscreen.CreateSphereObject(trsz+2, 
		RGBT2(cp.paragraphs[4].color, 0)
		,360.0, 55,10);
	m_3dscreen.FillRect(0,0,(int)steps, (int)(float)(deg * 45), RGBT(0,0,255,0)
		,fr_yIntensity , ((double)(trsz + 2) / 2.0 - 0.5));
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	steps = DiameterSteps(trsz - 5);
	deg = steps/360;
	m_3dscreen.BeginObject(eKarurit);
	m_3dscreen.CreateSphereObject(trsz-5, 
		RGBT2(cp.paragraphs[5].color, 0)
		,360.0, 25,-10);
	m_3dscreen.FillRect(0,0,(int)steps, (int)(float)(deg * 35), RGBT(255,0,0,0)
		,fr_yIntensity , (double)(trsz - 5) / 2.0 - 0.5);
	m_3dscreen.TurnShape(-170.0, axis_Y, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();


	double ang = 0;
	double width = 0.2;
	int i = eCador;
	for(; i < (1 + eCador); ++i, ang += 36.0)
	{
		m_3dscreen.BeginObject(i);
		m_3dscreen.CReateCircleLineObject(trsz, 
			RGBT2(cp.paragraphs[0].color, 0), 1.2, 360.0, 5);
		//m_3dscreen.TurnShape(90.0, axis_Z,false,true);
		//m_3dscreen.TurnShape(ang, axis_Y,false,true);
		m_3dscreen.ResetTranslation();
		m_3dscreen.Translate3Dto2D();
	}

	ang = -60;
	double dtrsz = (double)trsz;
	for(; i < (6 + eCador); ++i, ang += 30.0)
	{
		double shiftY = sin(ang * D) * dtrsz / 2.0;
		double newtrsz = cos(ang * D) * dtrsz;
		m_3dscreen.BeginObject(i);
		m_3dscreen.CReateCircleLineObject((int)(float)newtrsz, 
			RGBT2(cp.paragraphs[0].color, 0), 1.5);
		m_3dscreen.TurnShape(90.0, axis_x, false, true);
		m_3dscreen.ShiftObjectCenter(shiftY, axis_y, true);
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.Translate3Dto2D();
	}
		m_3dscreen.BeginObject(eMavdil);
		m_3dscreen.CreatObjectPixselMap(trsz,trsz);
		CMyFBitmap bm;
		bm.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm.GetMyPaintDC();
		COLORREF col = RGB(16,16,16);
		CPen pen(PS_SOLID,1,col);
		CBrush br(col);
		pdc->SelectObject(&pen);
		pdc->SelectObject(&br);
		pdc->Ellipse(0,0,trsz,trsz);
		m_3dscreen.BitmapToObject(bm, RGBT2(0,80));
		m_3dscreen.ResetTranslation();
		m_3dscreen.Translate3Dto2D();



	m_3dscreen.TrigerPaintAlow();

	return 0;
}

void CPerek11::Do3DPaint(void)
{
	if(m_bSkip)
		return;
	m_bSkip = true;

	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(eMuzak);
	if(m_buttonId >= 1)
	{
		m_3dscreen.Translate3Dto2D(FALSE);
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(eRadius);
	if(m_buttonId == 2)
	{
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(eBariach);
	if(m_buttonId == 3)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	int i = eCador;
	for(; i < (1 + eCador); ++i)
	{
		m_3dscreen.BeginObject(i);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D(/*FALSE*/);
	}

	for(; i < (6 + eCador); ++i)
	{
		m_3dscreen.BeginObject(i);
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D(/*FALSE*/);
	}

	m_3dscreen.BeginObject(eGavnunit);
	if(m_buttonId == 4 || m_buttonId == 5)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(eKarurit);
	if(m_buttonId == 5)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(eMavdil);
	if(m_buttonId != 4 && m_buttonId != 5)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(m_xTurn+90, axis_X);
		m_3dscreen.Translate3Dto2D(/*FALSE*/);
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek11::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = TRUE;


	if(m_bBntDown && m_bHandCursor)
	{
		double cx = (p.x - m_pt.x);
		m_yTurn = cx /2.0;
		double cy = p.y - m_pt.y;
		m_xTurn = cy / 2.0;//distent / 4.0;
		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}
