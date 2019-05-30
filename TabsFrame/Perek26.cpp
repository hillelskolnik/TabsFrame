// Perek26.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek26.h"


// CPerek26

IMPLEMENT_DYNCREATE(CPerek26, CPerek3DBase)

CPerek26::CPerek26()
: trsz(340)
, ofekAng(5)
, m_nMazalotStarsSize(0)
, timerElaps(45)
, lasty(0)
, conusHeight(100)
, m_sliderRc(3,0,120, ipHeight)
, chap3startY(32.5)
, m_sliderHorRc(120, ipHeight - 100,ipWidth,ipHeight)
, m_xTurn2(0)
, mazalMesibaFine(2.0)
, mazalMesibaSize(DiameterSteps(trsz,mazalMesibaFine))
, chap4startY(20)
, diameterEgulKotev(sin(23.5 * D) * (double)trsz)
, shiftEgulKotev(cos(23.5 * D) * (double)trsz/2.0)
, sizeEgulKotev(DiameterSteps((int)diameterEgulKotev))
{
	m_IDstart = ID_P26_1;
	m_IDidx = WT_PEREK_26;
	m_IDX_PEREK = IDX_PEREK_26;
}

CPerek26::~CPerek26()
{
}

BEGIN_MESSAGE_MAP(CPerek26, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P26_1, ID_P26_10, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P26_1, ID_P26_10, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()




// CPerek26 diagnostics

#ifdef _DEBUG
void CPerek26::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek26::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


enum
{
	ofek
	,galgalMashveHaYom
	,galgalMazalot
	,galgalMazalot2
	,galgalMazalot3
	,nekuda1
	,nekuda2
	,ShemotKarov
	,ShemotRachok
	,hezOle
	,hezYored
	,mazalOle
	,mazalShokea
	,mazalNekuda
	,mazalMesiba
	,hezKivunMesiba1
	,hezKivunMesiba2
	,darom
	,zafon
	,kotevMZ
	,kotevMD
	,kotevMsZ
	,kotevMsD
	,egulKotevZ
	,egulKotevD
	,hez23_5
	,keshet23_5
	,nekuda23_5
	,kavLemalaLemata
};
int CPerek26::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	COLORREF color6 = cp.paragraphs[6].color;
	COLORREF color7 = cp.paragraphs[7].color;
	COLORREF color8 = cp.paragraphs[8].color;
	COLORREF color9 = cp.paragraphs[9].color;

	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(400,300, 30.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();

	CFont font;
	VERIFY(font.CreateFont(
		18,                     // nHeight
		0,                       // nWidth
		0,                       // nEscapement
		0,                       // nOrientation
		FW_EXTRALIGHT,               // nWeight
		FALSE,                   // bItalic
		FALSE,                   // bUnderline
		0,                       // cStrikeOut
		HEBREW_CHARSET,          // nCharSet
		OUT_CHARACTER_PRECIS,      // nOutPrecision
		CLIP_CHARACTER_PRECIS,     // nClipPrecision
		PROOF_QUALITY,         // nQuality
		DEFAULT_PITCH/* | FF_SWISS*/,// nPitchAndFamily
		"Guttman Miryam Bold"));        // lpszFacename

	CString sOle = "מזל עולה";
	CString sShokea = "מזל שוקע";
	CString sDar = "דרום";
	CString sZaf = "צפון";

	int nOle = dc.GetTextExtent(sOle).cx;
	int nSise = nOle;
	int nShokea = dc.GetTextExtent(sShokea).cx;
	nSise = max(nSise,nShokea);
	int nDar = dc.GetTextExtent(sDar).cx;
	nSise = max(nSise,nDar);
	int nZaf = dc.GetTextExtent(sZaf).cx;
	nSise = max(nSise,nZaf);
	int nY = dc.GetTextExtent(sShokea).cy;
	int bmH = 22;
	nY = (bmH-nY)/2;
	nSise += 4;

	CMyFBitmap bmKiv;
	bmKiv.CreateMyCompatibleBitmap(&dc,nSise,bmH,0);
	int nX = (nSise-nOle)/2;
	CDC* pDirDc = bmKiv.GetMyPaintDC();
	int n = pDirDc->SaveDC();
	pDirDc->SelectObject(&font);
	pDirDc->SetBkMode(TRANSPARENT);
//	pDirDc->SetStretchBltMode(HALFTONE);
	pDirDc->SetTextColor(color3);
	pDirDc->TextOutA(nX,nY,sOle);

	double dtrsz = (double)trsz;
	m_3dscreen.BeginObject(mazalOle);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter(-(dtrsz/2) , axis_Z, true);
	m_3dscreen.ShiftObjectCenter(-(double)(conusHeight + bmH + 10), axis_y, true);
	m_3dscreen.TurnObjectCenter(-45, axis_Z, true);
	m_3dscreen.TurnObjectCenter(ofekAng/* + extraX*/, axis_X);
	m_3dscreen.ResetTranslation();	

	nX = (nSise-nShokea)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->TextOutA(nX,nY,sShokea);

	m_3dscreen.BeginObject(mazalShokea);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter((dtrsz/2) , axis_Z, true);
	m_3dscreen.ShiftObjectCenter((double)(conusHeight + bmH + 10), axis_y, true);
	m_3dscreen.TurnObjectCenter(-45, axis_Z, true);
	m_3dscreen.TurnObjectCenter(ofekAng/* + extraX*/, axis_X);
	m_3dscreen.ResetTranslation();

	nX = (nSise-nDar)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SetTextColor(color4);
	pDirDc->TextOutA(nX,nY,sDar);

	m_3dscreen.BeginObject(darom);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter(-(double)(trsz/2) , axis_X, true);
	m_3dscreen.ResetTranslation();

	nX = (nSise-nZaf)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SetTextColor(color4);
	pDirDc->TextOutA(nX,nY,sZaf);

	m_3dscreen.BeginObject(zafon);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter((double)(trsz/2) , axis_X, true);
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
	m_3dscreen.TurnShape(90.0 + ofekAng, axis_X, false, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(galgalMashveHaYom);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(255,255,0));
	m_3dscreen.TurnShape(32, axis_X, false, true);
	m_3dscreen.TurnShape(-90, axis_Y, false, true);


	int mazTrsz = (int)(cos(9.0*D)*(double)trsz);
	double shiftMaz = sin(9.0*D)*(double)trsz * 0.5;
	m_3dscreen.BeginObject(galgalMazalot2);
	m_3dscreen.CReateCircleLineObject(mazTrsz,color0);
	m_3dscreen.ShiftObjectCenter(shiftMaz,axis_Z, true);
	m_3dscreen.TurnObjectCenter(23.5,axis_x, true);
	m_3dscreen.TurnShape(23.5,axis_x, false,true);
	m_3dscreen.TurnObjectCenter(-90,axis_Y, true);
	m_3dscreen.TurnShape(-90,axis_y, false,true);

	m_3dscreen.BeginObject(galgalMazalot3);
	m_3dscreen.CReateCircleLineObject(mazTrsz,color0);
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
		CPen pen1(PS_SOLID,1,color0);
		pdc->SelectObject(&pen1);
		//pdc->MoveTo(0,0);
		//pdc->LineTo(1079,0);
		//pdc->MoveTo(0,47);
		//pdc->LineTo(1079,47);
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

	int kotTrsz = DiameterSteps(9);
	m_3dscreen.BeginObject(nekuda1);
	m_3dscreen.CreateSphereObject(9, 
		color0);
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color0, 0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz/2, axis_Z, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(nekuda2);
	m_3dscreen.CreateSphereObject(9, 
		color0);
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, ColBright(color0, 0.65)
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2, axis_Z, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(ShemotKarov);
	{
		CDC &dc2 = *(bm33.operator CDC *());
		CBrush br(color1);
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
		CBrush br(color2);
		CBrush* obr = dc2.SelectObject(&br);
		dc2.PatBlt(0,0,1080,48,0X00A000C9);
		dc2.SelectObject(obr);
	}
		m_3dscreen.CreateSphereBmObj(trsz,
			bm66,9,-9);
	m_3dscreen.TurnShape(113.5,axis_x, false,true);
	m_3dscreen.TurnShape(-90,axis_y, false,true);


	m_3dscreen.BeginObject(hezOle);
	m_3dscreen.CreateCylinderObject(1,9,conusHeight, /*color3*/RGB(64,0,128));
	m_3dscreen.FillRect(0,0,kotTrsz, conusHeight, RGB(255,255,255)
		,fr_zIntensity , (double)kotTrsz / 4.0);
	m_3dscreen.ShiftObjectCenter(-((double)trsz/2.0/* - 3.5*/),axis_z,true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(hezYored);
	m_3dscreen.CreateCylinderObject(1,9,conusHeight, /*color3*/RGB(64,0,128));
	m_3dscreen.FillRect(0,0,kotTrsz, conusHeight, RGB(255,255,255)
		,fr_zIntensity , (double)kotTrsz / 4.0);
	m_3dscreen.ShiftObjectCenter(((double)trsz/2.0/* - 3.5*/),axis_z,true);
	m_3dscreen.ResetTranslation();

	int stepsMazNek = DiameterSteps(13);
	m_3dscreen.BeginObject(mazalNekuda);
	m_3dscreen.CreateSphereObject(13, 
		color4);
	m_3dscreen.FillRect(0,0,stepsMazNek, stepsMazNek/2, ColBright(color4,0.65)
		,fr_zSquareIntensity , 6.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz/2, axis_Z, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(mazalMesiba);
	m_3dscreen.CReateCircleLineObject(trsz, color4, mazalMesibaFine);
	m_3dscreen.TurnShape(90,axis_y, false,true);

	m_3dscreen.BeginObject(hezKivunMesiba1);
	m_3dscreen.CreateCylinderObject(1,9,32, 
		ColDev(color4, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, conusHeight, color4
		,fr_zIntensity , 4.5);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(hezKivunMesiba2);
	m_3dscreen.CreateCylinderObject(1,9,32, 
		ColDev(color4, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, conusHeight, color4
		,fr_zIntensity , 4.5);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(kotevMZ);
	m_3dscreen.CreateSphereObject(9, 
			ColDev(color5, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color5
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2, axis_X, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(kotevMD);
	m_3dscreen.CreateSphereObject(9, 
			ColDev(color5, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color5
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz/2, axis_X, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(kotevMsZ);
	m_3dscreen.CreateSphereObject(9, 
			ColDev(color6, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color6
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2, axis_X, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(kotevMsD);
	m_3dscreen.CreateSphereObject(9, 
			ColDev(color6, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color6
		,fr_zSquareIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz/2, axis_X, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(egulKotevZ);
	m_3dscreen.CReateCircleLineObject((int)diameterEgulKotev, color7);
	m_3dscreen.ShiftObjectCenter(shiftEgulKotev, axis_Z, true);
	m_3dscreen.TurnShape(90,axis_Z,false,true);
	m_3dscreen.TurnObjectCenter(32+ofekAng,axis_X,true);
	m_3dscreen.TurnShape(32+ofekAng,axis_X,false,true);

	m_3dscreen.BeginObject(egulKotevD);
	m_3dscreen.CReateCircleLineObject((int)diameterEgulKotev, color7);
	m_3dscreen.ShiftObjectCenter(-shiftEgulKotev, axis_Z, true);
	m_3dscreen.TurnShape(270,axis_Z,false,true);
	m_3dscreen.TurnObjectCenter(32+ofekAng,axis_X,true);
	m_3dscreen.TurnShape(32+ofekAng,axis_X,false,true);

	double diameterHez23_5 = diameterEgulKotev/2.0;
	m_3dscreen.BeginObject(hez23_5);
	m_3dscreen.CreatObjectPixselMap((int)diameterHez23_5,1,color8,2);
	m_3dscreen.TurnShape(90,axis_Z,false,true);
	m_3dscreen.ShiftObjectCenter(diameterHez23_5/2.0, axis_Y, true);
	m_3dscreen.ShiftObjectCenter(shiftEgulKotev, axis_Z, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(keshet23_5);
	m_3dscreen.CReateCircleLineObject(trsz, color8, 1.0, 23.5);
	m_3dscreen.TurnShape(90.0,axis_Z,false,true);
	m_3dscreen.TurnShape(90.0,axis_Y,false,true);
	m_3dscreen.TurnShape(-90,axis_X,false,true);


	m_3dscreen.BeginObject(nekuda23_5);
	m_3dscreen.CreateSphereObject(4, color8);
	m_3dscreen.FillRect(0,0,16, 8, ColBright(color8, 0.8)
		,fr_zSquareIntensity , 2.0);
	m_3dscreen.ShiftObjectCenter(shiftEgulKotev, axis_Z, true);
	m_3dscreen.TurnObjectCenter(32+ofekAng,axis_X,true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(kavLemalaLemata);
	m_3dscreen.CReateCircleLineObject(trsz, color9, 1.0, 47.0);
	m_3dscreen.TurnShape(66.5,axis_Z,false,true);
	m_3dscreen.TurnShape(ofekAng-58,axis_X,false,true);

	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek26::OnMouseMove(UINT nFlags, CPoint point)
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
		case 2:
			SetTimer(1,timerElaps,NULL);
			m_yTurn = cx /8.5;
			break;
		case 7:
			SetTimer(1,timerElaps,NULL);
			m_yTurn = cx /5.0;
			break;
		case 3:
			if(m_sliderRc.PtInRect(p))
			{
				m_xTurn = cy ;
			}
			else
			{
				m_yTurn = cx /12.5;
				m_yTurn -= chap3startY;
			}
			break;
		case 4:
			if(m_sliderRc.PtInRect(p))
			{
				m_xTurn2 = -cy / 2.0;
			}
			else if(m_sliderHorRc.PtInRect(p))
			{
				m_yTurn = cx /12.5;
				m_yTurn -= chap4startY;
			}
			else
			{
				m_xTurn = cy ;
			}
			break;
		case 5:
		case 6:
			if(m_sliderRc.PtInRect(p))
			{
				m_xTurn = cy ;
			}
			else
			{
				m_yTurn = cx /4.0;
				//m_yTurn -= chap3startY;
			}
			break;
		case 8:
			m_yTurn = cx /5.5;
			m_xTurn = cy /2;
			break;
		case 9:
			m_yTurn = cx /5.5;
			m_xTurn = cy;
			break;
		default:
			m_yTurn = cx /8.5;
			m_xTurn = cy /2;
			break;
		}


		Do3DPaint();
	}


	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek26::Do3DPaint(void)
{
	if(m_bPastCreate == false || m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();


	int mazTrsz = (int)(cos(9.0*D)*(double)trsz);
	int mazSteps = DiameterSteps(mazTrsz);
	CFillRectData data2;
	data2.vec = 0.65;
	data2.radius = (double)trsz/2.0;


	m_3dscreen.BeginObject(ofek);
	if(lasty == m_yTurn)
	{
		m_3dscreen.Translate3Dto2D(FALSE);
	}
	else
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(galgalMashveHaYom);
	if(m_buttonId <= 6)
	{
		if(lasty == m_yTurn)
		{
			m_3dscreen.Translate3Dto2D(FALSE);
		}
		else
		{
			int Steps = DiameterSteps(trsz);
			m_3dscreen.ResetTranslation();
			m_3dscreen.TurnShape(ofekAng, axis_X, false);
			m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
			m_3dscreen.FillRect(0,0,Steps,3, 0,fr_zIntensityAll, data2);
			m_3dscreen.TurnShape(0.0, axis_Y);
			m_3dscreen.Translate3Dto2D();
		}
	}
	else
	{
		if(lasty == m_yTurn)
		{
			m_3dscreen.Translate3Dto2D(FALSE);
		}
		else
		{
			int Steps = DiameterSteps(trsz);
			m_3dscreen.ResetTranslation();
			//m_3dscreen.TurnShape(90, axis_Y);
			//m_3dscreen.TurnShape(ofekAng, axis_X, false);
			//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
			m_3dscreen.InitMatrix();
			m_3dscreen.TurnMatrix(90, axis_Y);
			m_3dscreen.TurnMatrix(ofekAng, axis_X);
			m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
			m_3dscreen.Transform(false);
			m_3dscreen.FillRect(0,0,Steps,3, 0,fr_zIntensityAll, data2);
			m_3dscreen.TurnShape(0.0, axis_Y);
			m_3dscreen.Translate3Dto2D();
		}
	}

	data2.radius = (double)mazTrsz/2.0;

	m_3dscreen.BeginObject(nekuda1);
	//m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
	m_3dscreen.TurnObjectCenter(32, axis_Z);
	if(m_buttonId > 6)
		m_3dscreen.TurnObjectCenter(90, axis_Y);
	m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(nekuda2);
	//m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
	m_3dscreen.TurnObjectCenter(32, axis_Z);
	if(m_buttonId > 6)
		m_3dscreen.TurnObjectCenter(90, axis_Y);
	m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.ResetTranslation();
	//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
	//m_3dscreen.TurnShape(32, axis_Z, false);
	//if(m_buttonId > 6)
	//	m_3dscreen.TurnShape(90, axis_Y, false);
	//m_3dscreen.TurnShape(ofekAng, axis_X, false);
	//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(m_xTurn, axis_X);
	m_3dscreen.TurnMatrix(32, axis_Z);
	if(m_buttonId > 6)
		m_3dscreen.TurnMatrix(90, axis_Y);
	m_3dscreen.TurnMatrix(ofekAng, axis_X);
	m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
	m_3dscreen.Transform(false);

	m_3dscreen.FillRect(0,0,mazSteps,3, 0,fr_zIntensityAll, data2);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(galgalMazalot2);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
	//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
	m_3dscreen.TurnMatrix(m_xTurn, axis_X);
	m_3dscreen.TurnObjectCenter(32, axis_Z);
	//m_3dscreen.TurnShape(32, axis_Z, false);
	m_3dscreen.TurnMatrix(32, axis_Z);
	if(m_buttonId > 6)
	{
		m_3dscreen.TurnObjectCenter(90, axis_Y);
		//m_3dscreen.TurnShape(90, axis_Y, false);
		m_3dscreen.TurnMatrix(90, axis_Y);
	}
	m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
	//m_3dscreen.TurnShape(ofekAng, axis_X, false);
	m_3dscreen.TurnMatrix(ofekAng, axis_X);
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
	m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
	m_3dscreen.Transform(false);
	m_3dscreen.FillRect(0,0,mazSteps,3, 0,fr_zIntensityAll, data2);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(galgalMazalot3);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
	//m_3dscreen.TurnShape(m_xTurn, axis_X, false);
	m_3dscreen.TurnMatrix(m_xTurn, axis_X);
	m_3dscreen.TurnObjectCenter(32, axis_Z);
	//m_3dscreen.TurnShape(32, axis_Z, false);
	m_3dscreen.TurnMatrix(32, axis_Z);
	if(m_buttonId > 6)
	{
		m_3dscreen.TurnObjectCenter(90, axis_Y);
		//m_3dscreen.TurnShape(90, axis_Y, false);
		m_3dscreen.TurnMatrix(90, axis_Y);
	}
	m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
	//m_3dscreen.TurnShape(ofekAng, axis_X, false);
	m_3dscreen.TurnMatrix(ofekAng, axis_X);
	m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
	//m_3dscreen.TurnShape(m_yTurn, axis_Y, false);
	m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
	m_3dscreen.Transform(false);
	m_3dscreen.FillRect(0,0,mazSteps,3, 0,fr_zIntensityAll, data2);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(ShemotKarov);
	if(m_buttonId == 1 || m_buttonId == 4 )
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
	else if(m_buttonId == 3)
	{
		double step = (double)m_nMazalotStarsSize / 360;
		double startAng = m_xTurn + 325;
		while(startAng > 360)
			startAng -= 360;
		while(startAng < 0)
			startAng += 360;
		int startPos = (int)(startAng * step);
		int size = (int)(step * 65);
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
	if(m_buttonId == 2 || m_buttonId == 4 )
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
	else if(m_buttonId == 3)
	{
		double step = (double)m_nMazalotStarsSize / 360;
		double startAng = m_xTurn + 145;
		while(startAng > 360)
			startAng -= 360;
		while(startAng < 0)
			startAng += 360;
		int startPos = (int)(startAng * step);
		int size = (int)(step * 70);
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

	m_3dscreen.BeginObject(hezOle);
	if(m_buttonId == 3)
	{
		double xTurn = -m_xTurn;
		while(xTurn > 360)
			xTurn -= 360;
		while(xTurn < 0)
			xTurn += 360;
		double alfaA = CosSphereAlfaRule(122,23.5,-xTurn);
		double angAy = SinSphereRule(-xTurn,alfaA,23.5);
//		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();


		m_3dscreen.ShiftObjectCenter(-(double)conusHeight / 2.0, axis_y);
		m_3dscreen.TurnObjectCenter(-45, axis_Z);
		//m_3dscreen.TurnShape(-45, axis_Z, false);
		m_3dscreen.TurnObjectCenter(ofekAng/* + extraX*/, axis_X);
		//m_3dscreen.TurnShape(ofekAng/* + extraX*/, axis_X, false);
		m_3dscreen.TurnObjectCenter(m_yTurn - angAy/* + extraY*/, axis_Y);
		//m_3dscreen.TurnShape(m_yTurn - angAy/* + extraY*/, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(-45, axis_Z);
		m_3dscreen.TurnMatrix(ofekAng/* + extraX*/, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn - angAy/* + extraY*/, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(mazalOle);
	if(m_buttonId == 3)
	{
		double xTurn = -m_xTurn;
		while(xTurn > 360)
			xTurn -= 360;
		while(xTurn < 0)
			xTurn += 360;
		double alfaA = CosSphereAlfaRule(122,23.5,-xTurn);
		double angAy = SinSphereRule(-xTurn,alfaA,23.5);
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();


		m_3dscreen.TurnObjectCenter(m_yTurn - angAy, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(mazalShokea);
	if(m_buttonId == 3)
	{
		double xTurn = -m_xTurn;
		while(xTurn > 360)
			xTurn -= 360;
		while(xTurn < 0)
			xTurn += 360;
		double alfaA = CosSphereAlfaRule(122,23.5,-xTurn);
		double angAy = SinSphereRule(-xTurn,alfaA,23.5);
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();


		m_3dscreen.TurnObjectCenter(m_yTurn - angAy, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);



	m_3dscreen.BeginObject(hezYored);
	if(m_buttonId == 3)
	{
		double xTurn = -m_xTurn;
		while(xTurn > 360)
			xTurn -= 360;
		while(xTurn < 0)
			xTurn += 360;
		double alfaA = CosSphereAlfaRule(122,23.5,-xTurn);
		double angAy = SinSphereRule(-xTurn,alfaA,23.5);
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();


		m_3dscreen.ShiftObjectCenter(-(double)conusHeight / 2.0, axis_y);
		m_3dscreen.TurnObjectCenter(135, axis_Z);
		//m_3dscreen.TurnShape(135, axis_Z, false);
		m_3dscreen.TurnObjectCenter(ofekAng/* + extraX*/, axis_X);
		//m_3dscreen.TurnShape(ofekAng/* + extraX*/, axis_X, false);
		m_3dscreen.TurnObjectCenter(m_yTurn - angAy/* + extraY*/, axis_Y);
		//m_3dscreen.TurnShape(m_yTurn - angAy/* + extraY*/, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(135, axis_Z);
		m_3dscreen.TurnMatrix(ofekAng/* + extraX*/, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn - angAy/* + extraY*/, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(mazalNekuda);
	if(m_buttonId == 4)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn2, axis_X);
		m_3dscreen.TurnObjectCenter(23.5, axis_Z);
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		m_3dscreen.TurnObjectCenter(ofekAng/* + extraX*/, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);

		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);



	m_3dscreen.BeginObject(mazalMesiba);
	if(m_buttonId == 4)
	{
		double sinNetya = SinNetyatAliyaYeshara(m_xTurn2, 23.5);
		double shiftX = sinNetya * (double)trsz / 2.0;
		double shrink = cos(asin(sinNetya));
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		//m_3dscreen.FillRect(0,0,mazalMesibaSize + 1,3,0,fr_shrink, shrink);
		m_3dscreen.ShiftObjectCenter(shiftX, axis_X);
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		//m_3dscreen.TurnShape(ofekAng, axis_X, false);

		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(ofekAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.TurnMatrix(shrink, axis_S);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(hezKivunMesiba1);
	if(m_buttonId == 4)
	{
		double sinNetya = SinNetyatAliyaYeshara(m_xTurn2, 23.5);
		double shiftX = sinNetya * (double)trsz / 2.0;
		double shiftZ = cos(asin(sinNetya)) * (double)trsz / 2.0;
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.ShiftObjectCenter(shiftX, axis_X);
		m_3dscreen.ShiftObjectCenter(-shiftZ, axis_Z);
		m_3dscreen.TurnObjectCenter(m_xTurn + ofekAng, axis_X);
		//m_3dscreen.TurnShape(m_xTurn + ofekAng, axis_X, false);
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		//m_3dscreen.TurnShape(ofekAng, axis_X, false);


		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn + ofekAng, axis_X);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(ofekAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(hezKivunMesiba2);
	if(m_buttonId == 4)
	{
		double sinNetya = SinNetyatAliyaYeshara(m_xTurn2, 23.5);
		double shiftX = sinNetya * (double)trsz / 2.0;
		double shiftZ = cos(asin(sinNetya)) * (double)trsz / 2.0;
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.ShiftObjectCenter(shiftX, axis_X);
		m_3dscreen.ShiftObjectCenter(-shiftZ, axis_Z);
		m_3dscreen.TurnObjectCenter(m_xTurn + ofekAng + 180, axis_X);
		//m_3dscreen.TurnShape(m_xTurn + ofekAng + 180, axis_X, false);
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		//m_3dscreen.TurnShape(32, axis_Z, false);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		//m_3dscreen.TurnShape(ofekAng, axis_X, false);


		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xTurn + ofekAng + 180, axis_X);
		m_3dscreen.TurnMatrix(32, axis_Z);
		m_3dscreen.TurnMatrix(ofekAng, axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(darom);
	if(m_buttonId >= 4 && m_buttonId != 9)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(22, axis_Z);
		if(m_buttonId > 6)
			m_3dscreen.TurnObjectCenter(90, axis_Y);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(zafon);
	if(m_buttonId >= 4)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(22, axis_Z);
		if(m_buttonId > 6)
			m_3dscreen.TurnObjectCenter(90, axis_Y);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kotevMZ);
	if(m_buttonId >= 5)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(23.5, axis_Z);
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		if(m_buttonId > 6)
			m_3dscreen.TurnObjectCenter(90, axis_Y);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kotevMD);
	if(m_buttonId >= 5 && m_buttonId != 9)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(23.5, axis_Z);
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_X);
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		if(m_buttonId > 6)
			m_3dscreen.TurnObjectCenter(90, axis_Y);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kotevMsZ);
	if(m_buttonId >= 6)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		if(m_buttonId > 6)
			m_3dscreen.TurnObjectCenter(90, axis_Y);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kotevMsD);
	if(m_buttonId >= 6 && m_buttonId != 9)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(32, axis_Z);
		if(m_buttonId > 6)
			m_3dscreen.TurnObjectCenter(90, axis_Y);
		m_3dscreen.TurnObjectCenter(ofekAng, axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(egulKotevZ);
	if(m_buttonId == 7)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		static double step = (double)sizeEgulKotev / 360.0;
		int steps = (int)(step * -m_xTurn);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D(TRUE,0,steps);
	}
	else if(m_buttonId >= 8)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(egulKotevD);
	if(m_buttonId == 7)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		static double step = (double)sizeEgulKotev / 360.0;
		int steps = (int)(step * -m_xTurn);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D(TRUE,0,steps);
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(hez23_5);
	if(m_buttonId == 8)
	{
		//m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		//m_3dscreen.TurnShape(-m_xTurn,axis_Z,false);
		m_3dscreen.TurnObjectCenter(-m_xTurn,axis_Z);
		m_3dscreen.TurnObjectCenter(32+ofekAng,axis_X);
		//m_3dscreen.TurnShape(32+ofekAng,axis_X,false);
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(-m_xTurn,axis_Z);
		m_3dscreen.TurnMatrix(32+ofekAng,axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(keshet23_5);
	if(m_buttonId == 8)
	{
		//m_3dscreen.ResetTranslation();
		//m_3dscreen.ResetShift();
		//m_3dscreen.TurnShape(-m_xTurn,axis_Z,false);
		//m_3dscreen.TurnShape(32+ofekAng,axis_X,false);
		//m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(-m_xTurn,axis_Z);
		m_3dscreen.TurnMatrix(32+ofekAng,axis_X);
		m_3dscreen.TurnMatrix(m_yTurn, axis_Y);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekuda23_5);
	if(m_buttonId == 8)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn, axis_Y);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(kavLemalaLemata);
	if(m_buttonId == 9)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnShape(m_yTurn, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	switch(m_buttonId)
	{
	case 4:
		PaintResult();
		break;
	}

	lasty = m_yTurn;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek26::InitOnSubHeadButton(void)
{
	lasty = 1000000;
	switch(m_buttonId)
	{
	case 1:
		m_yTurn = 0;
		m_xTurn = 0;
		SetTimer(1,timerElaps,NULL);
		break;
	case 2:
		m_yTurn = -chap3startY;
		m_xTurn = 0;
		SetTimer(1,timerElaps,NULL);
	case 7:
		m_yTurn = 0;
		m_xTurn = 0;
		SetTimer(1,timerElaps,NULL);
		break;
	case 3:
		KillTimer(1);
		m_yTurn = -chap3startY;
		m_xTurn = 0;
		SetTimer(2,100,NULL);
		break;
	case 4:
		KillTimer(1);
		m_yTurn = -chap4startY;
		m_xTurn = 0;
		SetTimer(2,100,NULL);
		break;
	default:
		KillTimer(1);
		m_yTurn = 0;
		m_xTurn = 0;
		SetTimer(2,100,NULL);
		break;
	}
	PaintSlider();
	PaintResult();
}

void CPerek26::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case 1:
			switch(m_buttonId)
			{
			case 7:
				--m_xTurn;
				break;
			default:
				m_xTurn -= 1.0/3.0;
				break;
			}
			if(m_xTurn <= -360)
				m_xTurn += 360;
			break;
	case 2:
		KillTimer(nIDEvent);
		break;
	}

	if(m_bNoTimerDraw == false)
		Do3DPaint();


	CPerek3DBase::OnTimer(nIDEvent);
}

void CPerek26::OnSetFocus(CWnd* pOldWnd)
{
	CPerek3DBase::OnSetFocus(pOldWnd);

	switch(m_buttonId)
	{
	case 1:
	case 2:
	case 7:
		SetTimer(1,timerElaps,NULL);
		break;
	default:
		KillTimer(1);
		break;
	}
}

void CPerek26::OnKillFocus(CWnd* pNewWnd)
{
	CPerek3DBase::OnKillFocus(pNewWnd);

	KillTimer(1);
}

BOOL CPerek26::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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

void CPerek26::PaintSlider(void)
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
	case 3:
	case 5:
	case 6:
		{
			rc.DeflateRect(0,5);
			CBrush br(color);
			m_memDc.FrameRect(rc, &br);
		}
		break;
	case 4:
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

void CPerek26::PaintResult(void)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);

	CRect rc(ipWidth - 140,150, ipWidth,180);
	m_memDc.FillSolidRect(rc,0);



	if(m_buttonId == 4)
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

		CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];
		COLORREF color = cp.paragraphs[m_buttonId].color;

		double Netya = asin(SinNetyatAliyaYeshara(m_xTurn2, 23.5)) * ToD;
		CString sKivun = (Netya == 0)?"":(Netya < 0)?"לדרום":"לצפון"; 
		CString sTxt;
		sTxt.Format("%.2f  %s",fabs(Netya), sKivun);
		int n = m_memDc.SaveDC();
		COLORREF txtcolor = m_memDc.SetTextColor(color);
		m_memDc.SetBkMode(TRANSPARENT);
		CFont* pFont = m_memDc.SelectObject(&font);
		m_memDc.DrawText(sTxt, rc, 
			DT_RIGHT | DT_WORDBREAK | DT_TOP | DT_RTLREADING);
		m_memDc.SelectObject(pFont);
		m_memDc.RestoreDC(n);
	}
	dc.BitBlt(rc.left,
		rc.top,rc.Width(),rc.Height(),
		&m_memDc,rc.left,rc.top,SRCCOPY);
}
