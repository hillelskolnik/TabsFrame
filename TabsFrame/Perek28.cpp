// Perek28.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek28.h"


// CPerek28

IMPLEMENT_DYNCREATE(CPerek28, CPerek3DBase)

CPerek28::CPerek28()
: trszArez(175)
, trsz(356)
, m_person(m_3dscreen)
, stepsArez(DiameterSteps(175,1.35))
, m_sliderRc(3,0,120, ipHeight)
, m_sliderHorRc(120, ipHeight - 80,ipWidth,ipHeight)
, m_xStart(5.0)
, m_yStart(5.0)
, lasty(1000000)
, standPos(45)
, fine2(3.0)
, steps2(DiameterSteps(trsz, fine2))
, m_xTurn2(0)
, stepsTrsz(DiameterSteps(trsz))
, stepsMashve(DiameterSteps(trszArez+2))
{
	m_IDstart = ID_P28_1;
	m_IDidx = WT_PEREK_28;
	m_IDX_PEREK = IDX_PEREK_28;
}

CPerek28::~CPerek28()
{
}

BEGIN_MESSAGE_MAP(CPerek28, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P28_1, ID_P28_16, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P28_1, ID_P28_16, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CPerek28 diagnostics

#ifdef _DEBUG
void CPerek28::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek28::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek28 message handlers

enum
{
	halal
	,arez
	,kavMashve
	,mashveHaYom
	,rosh
	,roshIsrael
	,ofek
	,kotevZ
	,kotevD
	,galgalMazalot
	,mesibatHaYomVeHaLayla
	,shemesh
	,alef
	,gimel
	,vav
	,chet
	,tet
	,lamed
	,mem
	,samech
	,ayn
	,kuf
	,maarav
	,ofanHaziHaYom
	,zafon
	,darom
	,nekudaGalgalMazalot
	,hezKivunMesiba1
	,hezKivunMesiba2
	,ofekAynKuf
	,medinot
	,haziArez
};

int CPerek28::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	COLORREF color12 = cp.paragraphs[12].color;
	COLORREF color13 = cp.paragraphs[13].color;
	COLORREF color14 = cp.paragraphs[14].color;
	COLORREF color15 = cp.paragraphs[15].color;

	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 30.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();

	CImageList imageList;
	imageList.Create(IDB_BITMAP_OTIYUT,9,0,RGB(255,255,128));
	CMyFBitmap bmOtyut;
	bmOtyut.CreateMyCompatibleBitmap(NULL,9,14,0);

	CDC *pDC = bmOtyut.GetMyPaintDC();
	int n = pDC->SaveDC();
	CBrush brOt(RGB(255,255,128));
	pDC->SelectObject(&brOt);

	m_3dscreen.BeginObject(alef);
	m_3dscreen.CreatObjectPixselMap(9,14);
	imageList.Draw(pDC,0,CPoint(0,0), ILD_IMAGE);
	pDC->PatBlt(0,0,9,14,0X00A000C9);
	m_3dscreen.BitmapToObject(bmOtyut);
	m_3dscreen.ShiftObjectCenter(-(double)trsz /2.0 - 7.0, axis_Y, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(gimel);
	m_3dscreen.CreatObjectPixselMap(9,14);
	imageList.Draw(pDC,2,CPoint(0,0), ILD_IMAGE);
	pDC->PatBlt(0,0,9,14,0X00A000C9);
	m_3dscreen.BitmapToObject(bmOtyut);
	m_3dscreen.ShiftObjectCenter(-(double)trsz /2.0 - 7.0, axis_Y, true);
	m_3dscreen.TurnObjectCenter(23.5, axis_Z, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(vav);
	m_3dscreen.CreatObjectPixselMap(9,14);
	imageList.Draw(pDC,5,CPoint(0,0), ILD_IMAGE);
	pDC->PatBlt(0,0,9,14,0X00A000C9);
	m_3dscreen.BitmapToObject(bmOtyut);
	m_3dscreen.ShiftObjectCenter((double)trsz /2.0 + 7.0, axis_Y, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(tet);
	m_3dscreen.CreatObjectPixselMap(9,14);
	imageList.Draw(pDC,8,CPoint(0,0), ILD_IMAGE);
	pDC->PatBlt(0,0,9,14,0X00A000C9);
	m_3dscreen.BitmapToObject(bmOtyut);
	m_3dscreen.ShiftObjectCenter(-(double)trsz /2.0 - 7.0, axis_Z, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(lamed);
	m_3dscreen.CreatObjectPixselMap(9,14);
	imageList.Draw(pDC,12,CPoint(0,0), ILD_IMAGE);
	pDC->PatBlt(0,0,9,14,0X00A000C9);
	m_3dscreen.BitmapToObject(bmOtyut);
	m_3dscreen.ShiftObjectCenter(-(double)trsz /2.0 - 7.0, axis_X, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(mem);
	m_3dscreen.CreatObjectPixselMap(9,14);
	imageList.Draw(pDC,13,CPoint(0,0), ILD_IMAGE);
	pDC->PatBlt(0,0,9,14,0X00A000C9);
	m_3dscreen.BitmapToObject(bmOtyut);
	m_3dscreen.ShiftObjectCenter((double)trsz /2.0 + 7.0, axis_X, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(samech);
	m_3dscreen.CreatObjectPixselMap(9,14);
	imageList.Draw(pDC,17,CPoint(0,0), ILD_IMAGE);
	pDC->PatBlt(0,0,9,14,0X00A000C9);
	m_3dscreen.BitmapToObject(bmOtyut);
	m_3dscreen.ShiftObjectCenter((double)trsz /2.0 + 7.0, axis_Y, true);
	m_3dscreen.TurnObjectCenter(23.5, axis_Z, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(ayn);
	m_3dscreen.CreatObjectPixselMap(9,14);
	imageList.Draw(pDC,18,CPoint(0,0), ILD_IMAGE);
	pDC->PatBlt(0,0,9,14,0X00A000C9);
	m_3dscreen.BitmapToObject(bmOtyut);
	m_3dscreen.ShiftObjectCenter((double)trsz /2.0 + 7.0, axis_Y, true);
	m_3dscreen.TurnObjectCenter(30 + m_xStart, axis_X, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(kuf);
	m_3dscreen.CreatObjectPixselMap(9,14);
	imageList.Draw(pDC,23,CPoint(0,0), ILD_IMAGE);
	pDC->PatBlt(0,0,9,14,0X00A000C9);
	m_3dscreen.BitmapToObject(bmOtyut);
	m_3dscreen.ShiftObjectCenter((double)trsz /2.0 + 7.0, axis_Y, true);
	m_3dscreen.TurnObjectCenter(60, axis_X, true);
	m_3dscreen.ResetTranslation();


	CBrush brOt2(RGB(255,0,64));
	pDC->SelectObject(&brOt2);

	m_3dscreen.BeginObject(chet);
	m_3dscreen.CreatObjectPixselMap(9,14);
	imageList.Draw(pDC,7,CPoint(0,0), ILD_IMAGE);
	pDC->PatBlt(0,0,9,14,0X00A000C9);
	m_3dscreen.BitmapToObject(bmOtyut);
	m_3dscreen.ShiftObjectCenter((double)trszArez /2.0 + 7.0, axis_Y, true);
	m_3dscreen.ResetTranslation();

	CMyFBitmap bmMaarav;
	bmMaarav.CreateMyCompatibleBitmap(NULL,36,14,0);
	CPoint p(0,0);
	pDC = bmMaarav.GetMyPaintDC();
	CBrush brMaarav(color5);
	pDC->SelectObject(&brMaarav);
	imageList.Draw(pDC,1,p, ILD_IMAGE);
	p.x += 9;
	imageList.Draw(pDC,24,p, ILD_IMAGE);
	p.x += 9;
	imageList.Draw(pDC,18,p, ILD_IMAGE);
	p.x += 9;
	imageList.Draw(pDC,13,p, ILD_IMAGE);
	pDC->PatBlt(0,0,36,14,0X00A000C9);
	m_3dscreen.BeginObject(maarav);
	m_3dscreen.CreatObjectPixselMap(36,14);
	m_3dscreen.BitmapToObject(bmMaarav);
	m_3dscreen.ShiftObjectCenter(-(double)trsz /2.0 - 7.0, axis_Z, true);
	m_3dscreen.TurnObjectCenter(m_xStart + 7.0, axis_X, true);
	m_3dscreen.ResetTranslation();

	pDC = bmMaarav.GetMyPaintDC();
	CBrush brZafon(color7);
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
	m_3dscreen.BitmapToObject(bmMaarav);
	m_3dscreen.ShiftObjectCenter(-(double)trsz /2.0 - 20.0, axis_X, true);
	m_3dscreen.TurnObjectCenter(3.5, axis_Z, true);
	m_3dscreen.ResetTranslation();

	pDC = bmMaarav.GetMyPaintDC();
	CBrush brDarom(color8);
	pDC->SelectObject(&brDarom);
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
	m_3dscreen.BitmapToObject(bmMaarav);
	m_3dscreen.ShiftObjectCenter((double)trsz /2.0 + 20.0, axis_X, true);
	m_3dscreen.TurnObjectCenter(-3.5, axis_Z, true);
	m_3dscreen.ResetTranslation();

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
	m_3dscreen.CreateSphereObject(trszArez, RGBT2(color2, 95)
		,360.0,90.0,-90.0, 1.35);
	m_3dscreen.BitmapToObject(bm11, RGBT2(0,0));
	m_3dscreen.TurnShape(-90.0, axis_Z, false,true);


	m_3dscreen.BeginObject(kavMashve);
	m_3dscreen.CReateCircleLineObject(trszArez+2, color0);
	m_3dscreen.TurnShape(90.0, axis_Y, false, true);

	steps = DiameterSteps(trsz);
	m_3dscreen.BeginObject(mashveHaYom);
	m_3dscreen.CReateCircleLineObject(trsz, color0);
	m_3dscreen.FillRect(0,0,steps,steps/2, RGB(1,1,1), 
		fr_yLightOppositeDirectionBase, 4.0);
	m_3dscreen.TurnShape(90.0, axis_Y, false, true);

	int kotTrsz = DiameterSteps(9);

	m_3dscreen.BeginObject(rosh);
	m_3dscreen.CreateSphereObject(9, 
		color0);
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color0,0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(trsz/2, axis_Y, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(roshIsrael);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color14, 2));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color14,0.2)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(trsz/2, axis_Y, true);

	m_3dscreen.BeginObject(medinot);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color13, 2));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color13,0.2)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(trszArez/2, axis_Y, true);

	m_3dscreen.BeginObject(nekudaGalgalMazalot);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color10, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color10,0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-trsz/2, axis_Z, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(ofek);
	m_3dscreen.CReateCircleLineObject(trsz, color1);
	m_3dscreen.TurnShape(90 + m_xStart,axis_X, false, true);

	m_3dscreen.BeginObject(ofekAynKuf);
	m_3dscreen.CReateCircleLineObject(trsz, color11);
	m_3dscreen.TurnShape(30 + m_xStart,axis_X, false, true);

	m_3dscreen.BeginObject(haziArez);
	m_3dscreen.CReateCircleLineObject(trszArez+3, color15);
	m_3dscreen.TurnShape(30 + m_xStart,axis_X, false, true);


	m_3dscreen.BeginObject(kotevZ);
	m_3dscreen.CreateSphereObject(9, 
		color1);
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color1,0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(trsz/2, axis_X, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(kotevD);
	m_3dscreen.CreateSphereObject(9, 
		color1);
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color1,0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-trsz/2, axis_X, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.CReateCircleLineObject(trsz, color9);
	m_3dscreen.TurnShape(90 ,axis_Y, false, true);
	m_3dscreen.TurnShape(23.5 ,axis_Z, false, true);

	m_3dscreen.BeginObject(mesibatHaYomVeHaLayla);
	m_3dscreen.CReateCircleLineObject(trsz, color2, fine2);
	m_3dscreen.FillRect(0,0,steps2 + 1,steps2/2, RGB(1,1,1), 
		fr_yLightOppositeDirectionBase, 4.0);
	m_3dscreen.TurnShape(90.0, axis_Y, false, true);

	int sShemesh = 23;
	int stepsShem = DiameterSteps(sShemesh);
	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(128,0,0, 0));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(255,128,0,0)
		,fr_zIntensity , (double)sShemesh / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(
		(double)trsz / 2.0,axis_Y, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(ofanHaziHaYom);
	m_3dscreen.CReateCircleLineObject(trsz, color6);
	m_3dscreen.TurnShape(m_xStart,axis_X, false, true);

	m_3dscreen.BeginObject(hezKivunMesiba1);
	m_3dscreen.CreateCylinderObject(1,9,32, ColDev(color9, 2));
	m_3dscreen.FillRect(0,0,kotTrsz, 32, ColBright(color9, 0.2)
		,fr_zIntensity ,  4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2.0,axis_Z, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(hezKivunMesiba2);
	m_3dscreen.CreateCylinderObject(1,9,32, ColDev(color9, 2));
	m_3dscreen.FillRect(0,0,kotTrsz, 32, ColBright(color9, 0.2)
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2.0,axis_Z, true);
	m_3dscreen.TurnObjectCenter(180,axis_X, true);
	m_3dscreen.TurnShape(180,axis_X, false, true);
	m_3dscreen.ResetTranslation();

	m_person.Create();

	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek28::OnMouseMove(UINT nFlags, CPoint point)
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
		case 0:
		case 1:
			if(m_sliderRc.PtInRect(p))
			{
				m_xTurn = cy ;
			}
			else
			{
				m_yTurn = cx /2.5;
				m_yTurn += m_yStart;
			}
			break;
		case 2:
		case 3:
		case 4:
		case 9:
		case 10:
		case 15:
			if(m_sliderRc.PtInRect(p))
			{
				m_xTurn = cy /2;
			}
			else if(m_sliderHorRc.PtInRect(p))
			{
				m_yTurn = cx /2.5;
				m_yTurn += m_yStart;
			}
			else
			{
				m_xTurn2 = cy ;
			}
			break;
		case 13:
			if(m_sliderRc.PtInRect(p))
			{
				m_xTurn2 = cy ;
			}
			else if(m_sliderHorRc.PtInRect(p))
			{
				m_yTurn = cx /2.5;
				m_yTurn += m_yStart;
			}
			else
			{
				m_xTurn = cy /2;
				m_xTurn += 90;
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

void CPerek28::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	static const double Israel = 63;
	m_3dscreen.BeginObject(arez);
	if(m_buttonId < 2)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(m_xTurn, axis_X,false);
		m_3dscreen.FillRect(0,0,stepsArez,stepsArez/2, RGB(1,1,1), 
			fr_yLightOppositeDirection, 4.0);
		m_3dscreen.TurnShape(m_xStart, axis_X,false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId == 2)
	{
		double sinNetiya = SinNetyatAliyaYeshara(m_xTurn, 23.5);
		double angNetiya = asin(sinNetiya) * ToD;

		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnLightPt(0,axis_X, true);
		m_3dscreen.TurnLightPt(270.0,axis_X);
		m_3dscreen.TurnLightPt(angNetiya,axis_Z);
		m_3dscreen.TurnLightPt(m_xTurn2,axis_X);

		CFillRectData data;
		data.radius = (double)trszArez / 2.0;
		data.vec2 = 0.4;
		m_3dscreen.FillRect(0,0,stepsArez,stepsArez/2, RGB(1,1,1), 
			fr_lightOppositeDirection, data);
		m_3dscreen.TurnShape(m_xStart, axis_X,false);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();

	}
	else if( m_buttonId == 9 || m_buttonId == 10)
	{
		double sinNetiya = SinNetyatAliyaYeshara(m_xTurn, 23.5);
		double angNetiya = asin(sinNetiya) * ToD;

		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnLightPt(0,axis_X, true);
		m_3dscreen.TurnLightPt(270.0,axis_X);
		m_3dscreen.TurnLightPt(angNetiya,axis_Z);
		m_3dscreen.TurnLightPt(m_xTurn2,axis_X);
		m_3dscreen.TurnLightPt(180, axis_Y);
		m_3dscreen.TurnLightPt(   Israel, axis_X);

		CFillRectData data;
		data.radius = (double)trszArez / 2.0;
		data.vec2 = 0.4;

		m_3dscreen.FillRect(0,0,stepsArez,stepsArez/2, RGB(1,1,1), 
			fr_lightOppositeDirection, data);

		//m_3dscreen.TurnShape(180, axis_Y, false);
		//m_3dscreen.TurnShape(   Israel, axis_X, false);
		//m_3dscreen.FillRect(0,0,stepsArez,stepsArez/2, RGB(1,1,1), 
		//	fr_lightOppositeDirection, data);
		//m_3dscreen.TurnShape(m_xStart, axis_X,false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(180, axis_Y);
		m_3dscreen.TurnMatrix(Israel, axis_X);
		m_3dscreen.TurnMatrix(m_xStart, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();

	}
	else if(m_buttonId >= 3 )
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(- m_xStart - m_xTurn - Israel, axis_X,false);
		m_3dscreen.TurnShape(180.0 + m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(shemesh);
	if(m_buttonId == 2 || m_buttonId == 10)
	{
		double sinNetiya = SinNetyatAliyaYeshara(m_xTurn, 23.5);
		double angNetiya = asin(sinNetiya) * ToD;
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(angNetiya, axis_Z);
		m_3dscreen.TurnObjectCenter(m_xTurn2 + m_xStart, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	if(m_buttonId < 2)
	{
		m_person.Reset();
		m_person.Shrink(0.2);
		m_person.Shift((double)trszArez/2.0,axis_Y,false);
		m_person.Turn(standPos,axis_X, false);
		m_person.Turn(m_yTurn,axis_Y);
	}
	else
		m_person.Hide();

	m_3dscreen.BeginObject(kavMashve);
	if(m_buttonId < 2)
	{
		if(lasty != m_yTurn)
		{
			m_3dscreen.InitMatrix();
			m_3dscreen.TurnMatrix(m_xStart, axis_X);
			m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
			m_3dscreen.Transform();
			m_3dscreen.Translate3Dto2D();
		}
		else
		{
			m_3dscreen.Translate3Dto2D(FALSE);
		}
	}
	else if(m_buttonId >= 2)
	{
			m_3dscreen.InitMatrix();
			m_3dscreen.TurnMatrix(m_xStart + m_xTurn, axis_X);
			m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
			m_3dscreen.Transform();
			m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(mashveHaYom);
	if((m_buttonId < 2 || m_buttonId > 3) &&  m_buttonId < 11)
	{
		if(lasty != m_yTurn)
		{
			m_3dscreen.InitMatrix();
			m_3dscreen.TurnMatrix(m_xStart, axis_X);
			m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
			m_3dscreen.Transform();
			m_3dscreen.Translate3Dto2D();
		}
		else
		{
			m_3dscreen.Translate3Dto2D(FALSE);
		}
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(rosh);
	if(m_buttonId < 2)
	{
//		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xStart + standPos, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(roshIsrael);
	if(m_buttonId == 14)
	{
//		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		m_3dscreen.TurnObjectCenter(m_xStart + m_xTurn + 30, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(ofek);
	if(m_buttonId == 1)
	{
		if(lasty != m_yTurn)
		{
			m_3dscreen.InitMatrix();
			m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
			m_3dscreen.Transform();
			m_3dscreen.Translate3Dto2D();
		}
		else
		{
			m_3dscreen.Translate3Dto2D(FALSE);
		}
	}
	else if(m_buttonId >= 3 && m_buttonId < 13)
	{
			m_3dscreen.InitMatrix();
			m_3dscreen.TurnMatrix(m_xTurn2, axis_X);
			m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
			m_3dscreen.Transform();
			m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(ofekAynKuf);
	if(m_buttonId == 13 || m_buttonId == 15)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn + m_xTurn2, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId >= 11)
	{
		double plusAng =  (m_buttonId == 12)?30:0;
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn + plusAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}	
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(haziArez);
	if(m_buttonId == 15)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn + m_xTurn2, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(medinot);
	if(m_buttonId == 13)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn + m_xTurn2 + m_xStart-60,axis_X);
		m_3dscreen.TurnShape(m_xTurn + m_xTurn2 + m_xStart-150.0,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kotevZ);
	if(m_buttonId == 1)
	{
		if(lasty != m_yTurn)
		{
			//m_3dscreen.ResetTranslation();
			m_3dscreen.ResetShift();
			m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
			m_3dscreen.TurnShape(0.0,axis_Y);
			m_3dscreen.Translate3Dto2D();
		}
		else
		{
			m_3dscreen.Translate3Dto2D(FALSE);
		}
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kotevD);
	if(m_buttonId == 1)
	{
		if(lasty != m_yTurn)
		{
			//m_3dscreen.ResetTranslation();
			m_3dscreen.ResetShift();
			m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
			m_3dscreen.TurnShape(0.0,axis_Y);
			m_3dscreen.Translate3Dto2D();
		}
		else
		{
			m_3dscreen.Translate3Dto2D(FALSE);
		}
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(galgalMazalot);
	if(m_buttonId == 9 || m_buttonId == 10)
	{
		double ay = AliyaYeshara(m_xTurn, 23.5);
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(ay + m_xStart + m_xTurn2,axis_X, false);
		//m_3dscreen.TurnShape(m_yTurn,axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(ay + m_xStart + m_xTurn2,axis_X);
		m_3dscreen.TurnMatrix(m_yTurn,axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();

	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(mesibatHaYomVeHaLayla);
	if(m_buttonId == 2)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();

		//m_3dscreen.TurnShape(m_xTurn2 + m_xStart,axis_X,false);
		//m_3dscreen.TurnShape(m_yTurn,axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xStart + m_xTurn2,axis_X);
		m_3dscreen.TurnMatrix(m_yTurn,axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();

	}
	else if(m_buttonId == 10)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();

		double sinNetiya = SinNetyatAliyaYeshara(-m_xTurn, 23.5);
		double cosNetiya = cos(asin(sinNetiya));
		double shift = sinNetiya * (double)trsz / 2.0;

//		m_3dscreen.FillRect(0,0,steps2+1,3, 0, fr_shrink, cosNetiya);
		m_3dscreen.ShiftObjectCenter(shift, axis_X);
//		m_3dscreen.TurnShape(m_xTurn2 + m_xStart,axis_X,false);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
//		m_3dscreen.TurnShape(m_yTurn,axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xStart + m_xTurn2,axis_X);
		m_3dscreen.TurnMatrix(m_yTurn,axis_Y);
		m_3dscreen.TurnMatrix(cosNetiya,axis_S);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(chet);
	if(m_buttonId == 14)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(32.0,axis_Z);
		m_3dscreen.TurnObjectCenter(m_xTurn + m_xStart + 30,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(tet);
	if(m_buttonId >= 3 && m_buttonId < 13)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn2 + m_xStart + 3.0,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(lamed);
	if(m_buttonId >= 3)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(mem);
	if(m_buttonId >= 3)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(alef);
	if(m_buttonId >= 4 && m_buttonId < 11)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn2 + m_xStart,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(vav);
	if(m_buttonId >= 4 && m_buttonId < 11)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn2 + m_xStart,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(gimel);
	if(m_buttonId == 9 || m_buttonId == 10)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn + m_xTurn2 + m_xStart,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(samech);
	if(m_buttonId == 9 || m_buttonId == 10)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn + m_xTurn2 + m_xStart,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(ayn);
	if(m_buttonId == 11 || (m_buttonId > 13 && m_buttonId < 15))
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn + m_xTurn2/* + m_xStart*/,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kuf);
	if(m_buttonId == 12)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn + m_xTurn2/* + m_xStart*/,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(maarav);
	if(m_buttonId >= 5 && m_buttonId < 13)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn2,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(ofanHaziHaYom);
	if(m_buttonId >= 6 && m_buttonId < 9)
	{
		if(lasty != m_yTurn)
		{
			//m_3dscreen.ResetTranslation();
			//m_3dscreen.TurnShape(m_yTurn,axis_Y);
			m_3dscreen.InitMatrix();
			m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
			m_3dscreen.Transform();
			m_3dscreen.Translate3Dto2D();
		}
		else
		{
			m_3dscreen.Translate3Dto2D(FALSE);
		}
	}
	else if(m_buttonId == 9 || m_buttonId == 10)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_xTurn2,axis_X);
		//m_3dscreen.TurnShape(m_yTurn,axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn2, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else if(m_buttonId == 13)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_xTurn + m_xTurn2-60,axis_X);
		//m_3dscreen.TurnShape(m_yTurn,axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn + m_xTurn2-60, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(zafon);
	if(m_buttonId >= 7)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(darom);
	if(m_buttonId >= 8)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekudaGalgalMazalot);
	if(m_buttonId == 10)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();

		double Netiya = asin(SinNetyatAliyaYeshara(-m_xTurn, 23.5))*ToD;
		m_3dscreen.TurnObjectCenter(Netiya,axis_Y);
		m_3dscreen.TurnObjectCenter(m_xTurn2 + m_xStart,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(hezKivunMesiba1);
	if(m_buttonId == 10 || m_buttonId == 9)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();

		m_3dscreen.TurnObjectCenter(m_xTurn2 - 1.0,axis_X);
		//m_3dscreen.TurnShape(m_xTurn2 - 1.0,axis_X, false);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		
		//m_3dscreen.TurnShape(m_yTurn,axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn2 - 1.0, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(hezKivunMesiba2);
	if(m_buttonId == 10 || m_buttonId == 9)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();

		m_3dscreen.TurnObjectCenter(m_xTurn2 - 1.0,axis_X);
		//m_3dscreen.TurnShape(m_xTurn2 - 1.0,axis_X, false);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		
		//m_3dscreen.TurnShape(m_yTurn,axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn2 - 1.0, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);




	lasty = m_yTurn;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek28::PaintSlider(void)
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
	case 0:
	case 1:
		{
			rc.DeflateRect(0,5);
			CBrush br(color);
			m_memDc.FrameRect(rc, &br);
		}
		break;
	case 2:
	case 3:
	case 4:
	case 9:
	case 10:
	case 13:
	case 15:
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

void CPerek28::InitOnSubHeadButton(void)
{
	lasty = 1000000;
	m_yTurn = m_yStart;
	m_xTurn = (m_buttonId == 13)?90:0;
	m_xTurn2 = 0;
	PaintSlider();


	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];
	COLORREF color = cp.paragraphs[m_buttonId].color;

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
	COLORREF color12 = cp.paragraphs[12].color;
	COLORREF color13 = cp.paragraphs[13].color;
	COLORREF color14 = cp.paragraphs[14].color;
	COLORREF color15 = cp.paragraphs[15].color;

	m_3dscreen.BeginObject(ofek);
	switch(m_buttonId)
	{
	case 1:
		m_3dscreen.FillRect(0,0,stepsTrsz, 3, color);
		break;
	case 3:
	case 4:
		m_3dscreen.FillRect(0,0,stepsTrsz, 3, color3);
		break;
	}

	m_3dscreen.BeginObject(mashveHaYom);
	switch(m_buttonId)
	{
	case 0:
	case 1:
		m_3dscreen.FillRect(0,0,stepsTrsz, 3, color0);
		break;
	case 4:
		m_3dscreen.FillRect(0,0,stepsTrsz, 3, color4);
		break;
	}

	m_3dscreen.BeginObject(kavMashve);
	switch(m_buttonId)
	{
	case 0:
	case 1:
	case 2:
	case 9:
	case 10:
		m_3dscreen.FillRect(0,0,stepsMashve,3, color0);
		m_3dscreen.FillRect(0,0,stepsMashve,3, RGB(1,1,1), 
			fr_yLightOppositeDirectionBase, 4.0);
		break;
	default:
		m_3dscreen.FillRect(0,0,stepsMashve,3, color0);
		break;
	}

	m_3dscreen.BeginObject(ofekAynKuf);
	switch(m_buttonId)
	{
	case 12:
		m_3dscreen.FillRect(0,0,stepsTrsz,3, color12);
		break;
	case 13:
		m_3dscreen.FillRect(0,0,stepsTrsz,3, color13);
		break;
	case 15:
		m_3dscreen.FillRect(0,0,stepsTrsz,3, color15);
		break;
	default:
		m_3dscreen.FillRect(0,0,stepsTrsz,3, color11);
		break;
	}

}

BOOL CPerek28::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_EXTRA_DRAW:
		PaintSlider();
		return TRUE;
	}

	return CPerek3DBase::OnWndMsg(message, wParam, lParam, pResult);
}
