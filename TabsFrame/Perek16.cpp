// Perek16.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek16.h"


// CPerek16

IMPLEMENT_DYNCREATE(CPerek16, CPerek3DBase)

CPerek16::CPerek16()
: m_distance(0)
,m_person(m_3dscreen)
{
	m_IDstart = ID_P16_1;
	m_IDidx = WT_PEREK_16;
	m_IDX_PEREK = IDX_PEREK_16;
}

CPerek16::~CPerek16()
{
}

BEGIN_MESSAGE_MAP(CPerek16, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P16_1, ID_P16_7, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P16_1, ID_P16_7, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek16 drawing


// CPerek16 diagnostics

#ifdef _DEBUG
void CPerek16::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek16::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek16 message handlers
const int trsz = 356;
const int trszArez = 175;


enum
{
	halal
	,arez
	,muzak
	,ofek
	,ofek2
	,ofek3
	,kaviHalal
	,rosh
	,regel
	,kohav
};

int CPerek16::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	COLORREF color0 = cp.paragraphs[0].color;
	COLORREF color1 = cp.paragraphs[1].color;
	COLORREF color2 = cp.paragraphs[2].color;
	COLORREF color3 = cp.paragraphs[3].color;
	COLORREF color4 = cp.paragraphs[4].color;
	COLORREF color5 = cp.paragraphs[5].color;
	COLORREF color6 = cp.paragraphs[6].color;

	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 45.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();

	m_3dscreen.NoPaint();

	int steps = DiameterSteps(trsz);
	m_3dscreen.BeginObject(halal);
	m_3dscreen.CreateSphereObject(trsz, RGBT(48,48,48, 0));
	m_3dscreen.FillRect(0,0,steps, steps/2, RGBT(0,0,0,0)
		,fr_zIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();
	m_3dscreen.ScreenToDC(TRUE);
	m_3dscreen.ClearScreen();
	m_3dscreen.DeleteObject(halal);


	m_3dscreen.BeginObject(ofek);
	m_3dscreen.CreatObjectPixselMap(trsz,trsz);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm1.GetMyPaintDC();
		CPen pen1(PS_SOLID,1,(COLORREF)0);
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
	m_3dscreen.TurnShape(90.0, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	CMyFBitmap bm3;
	bm3.CreateMyCompatibleBitmap(&dc,trszArez,trszArez,0);
	CDC *pdc3 = bm3.GetMyPaintDC();
	CBrush br3(RGB(255,255,255));
	pdc3->SelectObject(&br3);
	pdc3->Ellipse(0,0,trszArez,trszArez);

	m_3dscreen.BeginObject(ofek2);
	{
		COLORREF col = RGB(255,255,0);
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm1.GetMyPaintDC();
		CPen pen1(PS_SOLID,1,col);
		CBrush br1(HS_VERTICAL,col/*color3*/);
		pdc->SelectObject(&pen1);
		pdc->SelectObject(&br1);
		CRect rc(0,0,trsz,trsz);
		pdc->FillSolidRect(CRect(0,0,trsz, trsz),0);
		pdc->Ellipse(rc);

		int ms = (trsz - trszArez/* *4/5*/)/2;
		rc.DeflateRect(ms,ms);

		pdc3->BitBlt(0,0,trszArez,trszArez,
			pdc,rc.left,rc.top,SRCAND);

		rc.DeflateRect(2,2);
		CBrush br2(RGB(0,0,0)/*color3*/);
		CPen pen2(PS_SOLID, 1, (COLORREF)0);
		pdc->SelectObject(&br2);
		pdc->SelectObject(&pen2);
		pdc->Ellipse(rc);

		m_3dscreen.CreateFlatBmObj(bm1);
	}
	m_3dscreen.FillRect(0,0,trsz*trsz, 1, RGBT(160,80,0,0)
		,fr_xyIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.TurnShape(105.0, axis_X, false, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(30, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(ofek3);
	//m_3dscreen.CreatObjectPixselMap(trszArez,trszArez);
	//m_3dscreen.BitmapToObject(bm3, RGBT2(0,0));
	m_3dscreen.CreateFlatBmObj(bm3);
	m_3dscreen.FillRect(0,0,trszArez*trszArez, 1, RGBT(160,80,0,0)
		,fr_xyIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.BeginObject(kaviHalal);
	m_3dscreen.CReateCircleLineObject(trsz, RGBT(24,24,0, 0),
		1.0,360, 3);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	int kotTrsz = DiameterSteps(5);

	m_3dscreen.BeginObject(muzak);
	m_3dscreen.CreateSphereObject(5, 
		ColDev(color1, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color1
		,fr_zIntensity , 2.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	kotTrsz = DiameterSteps(9);

	m_3dscreen.BeginObject(rosh);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color5, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color5
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(trsz/2, axis_Y, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(regel);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color6, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color6
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-trsz/2, axis_Y, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	int sKohav = 13;
	kotTrsz = DiameterSteps(sKohav);

	m_3dscreen.BeginObject(kohav);
	m_3dscreen.CreateSphereObject(sKohav, 
		RGB(128,128,0));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, RGBT(255,255,128, 0)
		,fr_zIntensity , 6.5);
	m_3dscreen.ShiftObjectCenter(150, axis_X, true);
	m_3dscreen.TurnObjectCenter(50, axis_Z, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kohav+1);
	m_3dscreen.CreateSphereObject(sKohav, 
		RGB(128,128,0));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, RGBT(255,255,128, 0)
		,fr_zIntensity , 6.5);
	m_3dscreen.ShiftObjectCenter(-147, axis_X, true);
	m_3dscreen.TurnObjectCenter(-14, axis_Z, true);
	m_3dscreen.ShiftObjectCenter(-100, axis_Z, true);
	m_3dscreen.TurnObjectCenter(70, axis_Z, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kohav+2);
	m_3dscreen.CreateSphereObject(sKohav, 
		RGB(128,128,0));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, RGBT(255,255,128, 0)
		,fr_zIntensity , 6.5);
	m_3dscreen.ShiftObjectCenter(-135, axis_X, true);
	//m_3dscreen.TurnObjectCenter(-35, axis_Z, true);
	m_3dscreen.ShiftObjectCenter(-110, axis_Z, true);
	m_3dscreen.TurnObjectCenter(60, axis_Z, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(kohav+3);
	m_3dscreen.CreateSphereObject(sKohav, 
		RGB(128,128,0));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, RGBT(255,255,128, 0)
		,fr_zIntensity , 6.5);
	m_3dscreen.ShiftObjectCenter(-120, axis_X, true);
	m_3dscreen.ShiftObjectCenter(-10, axis_Z, true);
	m_3dscreen.TurnObjectCenter(60, axis_Z, true);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	int stepsArez = DiameterSteps(trszArez);
	m_3dscreen.BeginObject(arez);
	m_3dscreen.CreateSphereObject(trszArez, RGBT2(color2, 95));
	{
		m_3dscreen.BitmapToObject(bm11, RGBT2(0,95));
	}
	//m_3dscreen.FillRect(0,0,stepsArez, stepsArez/2, 
	//	RGBT(0,0,64,95)
	//	,fr_zIntensity , (double)trszArez / 2.0 - 0.5);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.Translate3Dto2D();

	m_person.Create();

	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek16::Do3DPaint(void)
{
	if(m_bPastCreate == false || m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();


	m_3dscreen.BeginObject(muzak);
	//if(m_buttonId == 1 || m_buttonId > 2)
	if(m_buttonId >= 1)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	double y2 = 30;
	if(m_buttonId > 3)
	{
		m_person.Reset();
		m_person.Turn(m_xTurn, axis_x, false);
		m_person.Turn(m_yTurn, axis_y);
	}
	else if(m_buttonId == 2)
	{
		double half = (double)trszArez / 2;
		m_person.Reset();
		m_person.Shift(half, axis_Y,false);
		m_person.Turn(15, axis_X,false);
		m_person.Turn(y2, axis_Y,false);
		m_person.Shift(m_distance, axis_Z);
	}
	else
		m_person.Hide();

	
	m_3dscreen.BeginObject(kohav);
	if(m_buttonId == 1)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn ,axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId == 2)
	{
		static double turn = 13;
		double mod = fmod(m_distance,3500);
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(turn ,axis_Z);
		turn -= 4;
		m_3dscreen.ShiftObjectCenter(mod-300,axis_Z);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kohav +1);
	if(m_buttonId == 1)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn ,axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId == 2)
	{
		static double turn = 13;
		double mod = fmod(m_distance,5500);
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.ShiftObjectCenter(mod-1000,axis_Z);
		m_3dscreen.TurnObjectCenter(turn ,axis_Z);
		turn -= 3;
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kohav +2);
	if(m_buttonId == 1)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn ,axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId == 2)
	{
		static double turn = 13;
		double mod = fmod(m_distance,1500);
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.ShiftObjectCenter(mod -1250,axis_Z);
		m_3dscreen.TurnObjectCenter(turn ,axis_Z);
		turn += 7;
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kohav +3);
	if(m_buttonId == 1)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn ,axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId == 2)
	{
		static double turn = 5;
		double mod = fmod(m_distance,2500);
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.ShiftObjectCenter(mod-400,axis_Z);
		m_3dscreen.TurnObjectCenter(turn ,axis_Z);
		turn += 2;
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(kaviHalal);
	if(m_buttonId >= 3 )
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(m_xTurn, axis_X, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(arez);
	if(m_buttonId >= 0 && m_buttonId < 2)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId == 2)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.ShiftObjectCenter(m_distance,axis_Z);
		m_3dscreen.TurnShape(105.0, axis_X,false);
		m_3dscreen.TurnShape(y2, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(ofek2);
	if(m_buttonId == 2)
	{
		m_3dscreen.Translate3Dto2D(FALSE);
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(ofek3);
	if(m_buttonId == 2)
	{
		double v = m_3dscreen.GetTransformVector();
		double z = m_3dscreen.GetMiddleZ();
		double half = (double)trszArez / 2 -1;
		double u = z*half/v;//m_3dscreen.GetTransformVector();
		//double p3dVect = (m_distance *2.41 + z)/z;//1 / (1 + (m_distance * 2.1 / z)); 
		half = (v*u)/(z+m_distance * (m_distance/v + 1)*1.4);
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.ShiftObjectCenter(half, axis_Y);
		m_3dscreen.TurnShape(105, axis_X, false);
		m_3dscreen.TurnObjectCenter(15, axis_X);
		m_3dscreen.TurnObjectCenter(y2, axis_Y);
		m_3dscreen.TurnShape(y2, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}


	m_3dscreen.BeginObject(rosh);
	if(m_buttonId >= 5)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_3dscreen.BeginObject(regel);
	if(m_buttonId == 6)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}


	m_3dscreen.BeginObject(ofek);
	if(m_buttonId >= 3)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnShape(m_xTurn, axis_X, false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
	{
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}


	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek16::OnMouseMove(UINT nFlags, CPoint point)
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
		double temp = sqrt(cx*cx+cy*cy);
		temp /= 45;
		m_distance = sqrt(cx*cx+cy*cy) * temp*temp;
		m_yTurn = cx / 2.0;
		m_xTurn = cy / 2.0;


		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek16::InitOnSubHeadButton(void)
{
	switch(m_buttonId)
	{
	case 2:
		m_distance = 0;
		break;
	case 3:
	case 4:
	case 5:
	case 6:
		m_xTurn = 15;
		m_yTurn = 0;
		Do3DPaint();
		break;
	}

}
