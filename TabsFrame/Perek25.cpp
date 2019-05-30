// Perek25.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek25.h"


// CPerek25

IMPLEMENT_DYNCREATE(CPerek25, CPerek3DBase)

CPerek25::CPerek25()
: backfromMabul(57.40352/*41.12*/)
,m_sliderRc(10,0,150, ipHeight)
, m_hieghtOffSet(100)
, posy(m_hieghtOffSet)
, sShemesh(13)
, turnX4(5)
{
	m_IDstart = ID_P25_1;
	m_IDidx = WT_PEREK_25;
	m_IDX_PEREK = IDX_PEREK_25;
}

CPerek25::~CPerek25()
{
}

BEGIN_MESSAGE_MAP(CPerek25, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P25_1, ID_P25_7, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P25_1, ID_P25_7, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek25 drawing


#ifdef _DEBUG
void CPerek25::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek25::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek25 message handlers
const int trsz = 340;

enum
{
	ofek
	,ZurotMazalot
	,galgalMazalot
	,eMavdil
	,ShemotKarov
	,shemesh
	,mesibatShemesh
	,nekuda1
	,nekuda2
	,galgalShave
	,darom
	,zafon
	,nekuda1ya
	,nekuda2ya
	,nekuda1smu
	,nekuda2smu
};


int CPerek25::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;


	CMyFBitmap bm11;
	CString path = theApp.m_appPath + "Images\\MazalotStarsZurot.bmp";
	CImage image22;
	image22.Load(path);
	bm11.CreateMyCompatibleBitmap(NULL, image22.GetWidth(),
		image22.GetHeight());
	image22.BitBlt(bm11.operator CDC *()->GetSafeHdc(),
		CPoint(0,0));


	CMyFBitmap bm33;
	path = theApp.m_appPath + "Images\\ShemotKarov.bmp";
	CImage image44;
	image44.Load(path);
	bm33.CreateMyCompatibleBitmap(NULL, image44.GetWidth(),
		image44.GetHeight());
	image44.BitBlt(bm33.operator CDC *()->GetSafeHdc(),
		CPoint(0,0));
//	m_nMazalotStarsSize = image22.GetWidth();


	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];

	CClientDC dc(this);
	m_memDc.CreateCompatibleDC(&dc);
	m_memBm.CreateCompatibleBitmap(&dc, m_sliderRc.Width(), m_sliderRc.Height());
	m_memDc.SelectObject(&m_memBm);
	m_memDc.SelectObject(&m_font);


	COLORREF color0 = cp.paragraphs[0].color;
	COLORREF color1 = cp.paragraphs[1].color;
	COLORREF color2 = cp.paragraphs[2].color;
	COLORREF color3 = cp.paragraphs[3].color;
	COLORREF color4 = cp.paragraphs[4].color;
	COLORREF color5 = cp.paragraphs[5].color;
	COLORREF color6 = cp.paragraphs[6].color;

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

	CString sDar = "מזלות דרומיים";
	CString sZaf = "מזלות צפוניים";

	int nDar = dc.GetTextExtent(sDar).cx;
	int nSise = nDar;
	int nZaf = dc.GetTextExtent(sZaf).cx;
	nSise = max(nSise,nZaf);
	int nY = dc.GetTextExtent(sZaf).cy;
	int bmH = 18;
	nY = (bmH-nY)/2;
	nSise += 4;

	CMyFBitmap bmKiv;
	bmKiv.CreateMyCompatibleBitmap(&dc,nSise,bmH,0);
	int nX = (nSise-nDar)/2;
	CDC* pDirDc = bmKiv.GetMyPaintDC();
	int n = pDirDc->SaveDC();
	pDirDc->SelectObject(&font);
	pDirDc->SetBkMode(TRANSPARENT);
	pDirDc->SetTextColor(color5);
	pDirDc->TextOutA(nX,nY,sDar);

	double dTrsx = trsz + sShemesh/2;
	m_3dscreen.BeginObject(darom);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter(-(dTrsx/2) , axis_Z, true);
	m_3dscreen.TurnObjectCenter(60,axis_X, true);
	

	nX = (nSise-nZaf)/2;
	pDirDc = bmKiv.GetMyPaintDC();
	pDirDc->SetTextColor(color4);
	pDirDc->TextOutA(nX,nY,sZaf);

	m_3dscreen.BeginObject(zafon);
	m_3dscreen.CreatObjectPixselMap(nSise, bmH);
	m_3dscreen.BitmapToObject(bmKiv);
	m_3dscreen.ShiftObjectCenter((dTrsx/2) , axis_Z, true);
	m_3dscreen.TurnObjectCenter(60,axis_X, true);

	m_3dscreen.BeginObject(ZurotMazalot);
	m_3dscreen.CreateSphereBmObj(trsz,
		bm11,25,-25);


	m_3dscreen.BeginObject(ShemotKarov);
	{
		CDC &dc2 = *(bm33.operator CDC *());
		CBrush br(RGB(64,64,64));
		CBrush* obr = dc2.SelectObject(&br);
		dc2.PatBlt(0,0,1080,48,0X00A000C9);
		dc2.SelectObject(obr);
	}
		m_3dscreen.CreateSphereBmObj(trsz,
			bm33,9,-9,RGBT2(0,95));
	m_3dscreen.TurnShape(23.5,axis_x, false,true);


	m_3dscreen.BeginObject(galgalMazalot);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,1080,48,0);
		CDC* pdc = bm1.GetMyPaintDC();
		int n = pdc->SaveDC();
		pdc->RestoreDC(n);
		CPen pen1(PS_SOLID,1,color0);
		pdc->SelectObject(&pen1);
		pdc->MoveTo(0,0);
		pdc->LineTo(1079,0);
		pdc->MoveTo(0,47);
		pdc->LineTo(1079,47);
		CPoint topp(0,0);
		CPoint bottomp(0,47);
		CPoint plusp(90,0);
		for(int i = 0; i < 12; ++i, topp += plusp, bottomp += plusp)
		{
			pdc->MoveTo(topp);
			pdc->LineTo(bottomp);
		}

		m_3dscreen.CreateSphereBmObj(trsz,bm1,9,-9,RGBT2(0,80));
		pdc->RestoreDC(n);
	}
	m_3dscreen.TurnShape(23.5,axis_x, false,true);


	m_3dscreen.BeginObject(eMavdil);
	m_3dscreen.CreatObjectPixselMap(trsz,trsz);
	{
		CMyFBitmap bm;
		bm.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm.GetMyPaintDC();
		COLORREF col = RGB(16,16,16);
		CPen pen(PS_SOLID,1,col);
		CBrush br(col);
		pdc->SelectObject(&pen);
		pdc->SelectObject(&br);
		pdc->Ellipse(0,0,trsz,trsz);
		m_3dscreen.BitmapToObject(bm, RGBT2(0,30));
	}
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(0.0,axis_Y);
	m_3dscreen.ResetTranslation();
	m_3dscreen.Translate3Dto2D();

	int stepsShem = DiameterSteps(sShemesh);
	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(128,0,0, 0));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(255,128,0,0)
		,fr_zIntensity , (double)sShemesh / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(
		(double)trsz / 2.0 - (double)sShemesh/2 - 2,axis_X, true);

	m_3dscreen.BeginObject(mesibatShemesh);
	m_3dscreen.CReateCircleLineObject(trsz-2,color1);
	m_3dscreen.TurnShape(113.5,axis_X,false,true);

	m_3dscreen.BeginObject(galgalShave);
	m_3dscreen.CReateCircleLineObject(trsz,color3);
	m_3dscreen.TurnShape(90 + turnX4,axis_X);
	m_3dscreen.Translate3Dto2D();


	int kotTrsz = DiameterSteps(9);
	m_3dscreen.BeginObject(nekuda1);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color3, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color3
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz/2, axis_X, true);

	m_3dscreen.BeginObject(nekuda2);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color3, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color3
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2, axis_X, true);


	m_3dscreen.BeginObject(nekuda1ya);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color6, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color6
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2, axis_X, true);

	m_3dscreen.BeginObject(nekuda2ya);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color6, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color6
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter((double)trsz/2, axis_X, true);

	m_3dscreen.BeginObject(nekuda1smu);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color6, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color6
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz/2, axis_X, true);

	m_3dscreen.BeginObject(nekuda2smu);
	m_3dscreen.CreateSphereObject(9, 
		ColDev(color6, 3));
	m_3dscreen.FillRect(0,0,kotTrsz, kotTrsz/2, color6
		,fr_zIntensity , 4.5);
	m_3dscreen.ShiftObjectCenter(-(double)trsz/2, axis_X, true);


	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek25::Do3DPaint(void)
{
	if(m_bPastCreate == false || m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(ZurotMazalot);
	if(m_buttonId < 6)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		switch(m_buttonId)
		{
		case 0:
			m_3dscreen.TurnShape(-backfromMabul,axis_y, false);
			break;
		case 2:
			m_3dscreen.TurnShape(-m_xTurn,axis_y, false);
			break;
		}
		m_3dscreen.TurnShape(23.5,axis_x, false);
		if(m_buttonId != 3)
		{
			m_3dscreen.TurnShape(m_yTurn,axis_Y);
		}
		else
		{
			m_3dscreen.TurnShape(m_yTurn,axis_Y,false);
			m_3dscreen.TurnShape(turnX4,axis_X);
		}
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(mesibatShemesh);
	if(m_buttonId == 1 || m_buttonId == 6)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnShape(m_yTurn,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(zafon);
	if(m_buttonId >= 4)
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
	if(m_buttonId >= 5)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekuda1);
	if(m_buttonId >= 3)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		if(m_buttonId != 3)
		{
			m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		}
		else
		{
			m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
			m_3dscreen.TurnObjectCenter(turnX4,axis_X);
		}
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekuda2);
	if(m_buttonId >= 3)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		if(m_buttonId != 3)
		{
			m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		}
		else
		{
			m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
			m_3dscreen.TurnObjectCenter(turnX4,axis_X);
		}
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekuda1ya);
	if(m_buttonId == 6)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn,axis_Y);
		m_3dscreen.TurnObjectCenter(23.5,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekuda2ya);
	if(m_buttonId == 6)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(-m_xTurn,axis_Y);
		m_3dscreen.TurnObjectCenter(23.5,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekuda1smu);
	if(m_buttonId == 6)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(-m_xTurn,axis_Y);
		m_3dscreen.TurnObjectCenter(23.5,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(nekuda2smu);
	if(m_buttonId == 6)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn,axis_Y);
		m_3dscreen.TurnObjectCenter(23.5,axis_X);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(shemesh);
	if(m_buttonId == 1)
	{
		m_3dscreen.ResetTranslation();
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xTurn, axis_Y);
		m_3dscreen.TurnObjectCenter(23.5,axis_x);
		m_3dscreen.TurnObjectCenter(m_yTurn,axis_Y);
		m_3dscreen.TurnShape(0.0,axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(galgalShave);
	if(m_buttonId == 3)
	{
		m_3dscreen.Translate3Dto2D(FALSE);
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	if(m_buttonId != 3)
	{
		m_3dscreen.TurnShape(m_yTurn,axis_Y);
	}
	else
	{
		m_3dscreen.TurnShape(m_yTurn,axis_Y,false);
		m_3dscreen.TurnShape(turnX4,axis_X);
	}
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(ShemotKarov);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	if(m_buttonId != 3)
	{
		m_3dscreen.TurnShape(m_yTurn,axis_Y);
	}
	else
	{
		m_3dscreen.TurnShape(m_yTurn,axis_Y,false);
		m_3dscreen.TurnShape(turnX4,axis_X);
	}
	double startAng = 180.0 - m_yTurn;
	if(startAng < 0)
		startAng += 360;
	else if(startAng > 360)
		startAng -= 360;
	int startp = (int)(startAng*3);
	m_3dscreen.Translate3Dto2D(TRUE, startp, 540);


	m_3dscreen.BeginObject(eMavdil);
	if(m_buttonId != 6)
		m_3dscreen.Translate3Dto2D(FALSE);
	else
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);


	switch(m_buttonId)
	{
//	case 1:
	case 2:
//	case 6:
		PaintSlider();
		break;
	}
//	lasty = m_yTurn;
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

void CPerek25::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = (p.x > 10)?TRUE:FALSE;


	if(m_bBntDown && m_bHandCursor )
	{
		double cx = (p.x - m_pt.x);
		double cy = (p.y - m_pt.y);

		switch(m_buttonId)
		{
		case 6:
			if(m_sliderRc.PtInRect(p))
			{
				double step = 90 / (double)(m_sliderRc.Height()-m_hieghtOffSet*2);
				int y = p.y;
				if(y < m_hieghtOffSet)
				{
					y = m_hieghtOffSet;
				}
				else if((m_sliderRc.Height()- m_hieghtOffSet) < y)
				{
					y = m_sliderRc.Height()- m_hieghtOffSet;
				}
				double size = (m_sliderRc.top + m_hieghtOffSet) - y;
				posy = y;
				
				m_xTurn = step * size;
			}
			else
			{
				m_yTurn = cx /2.5;
			}
			break;
		case 1:
			if(m_sliderRc.PtInRect(p))
			{
				m_xTurn = cy ;
			}
			else
			{
				m_yTurn = cx / 2.3;
			}
			break;
		case 2:
			if(m_sliderRc.PtInRect(p))
			{
				double step = backfromMabul / (double)(m_sliderRc.Height()-m_hieghtOffSet*2);
				int y = p.y;
				if(y < m_hieghtOffSet)
				{
					y = m_hieghtOffSet;
				}
				else if((m_sliderRc.Height()- m_hieghtOffSet) < y)
				{
					y = m_sliderRc.Height()- m_hieghtOffSet;
				}
				double size = y - (m_sliderRc.top + m_hieghtOffSet);
				posy = y;
				
				m_xTurn = step * size;
			}
			else
			{
				m_yTurn = cx / 2.3 ;
				while(m_yTurn > 360)
					m_yTurn -= 360;
				while(m_yTurn < 0)
					m_yTurn += 360;
			}
			break;
		case 4:
			m_yTurn = cx / 2.3;
			m_yTurn += 180;
			break;
		default:
			m_xTurn = cy / 3.0;
			m_yTurn = cx / 2.3;
			break;
		}
		Do3DPaint();
	
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek25::PaintSlider(void)
{
	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[m_IDX_PEREK];
	COLORREF color = cp.paragraphs[m_buttonId].color;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	CRect rc(0,0,m_sliderRc.Width(),m_sliderRc.Height());
	int n = m_memDc.SaveDC();
	m_memDc.FillSolidRect(rc,0);
	if(m_buttonId == 1 || m_buttonId == 2 || m_buttonId == 6 )
	{
		rc.DeflateRect(0,5);
		CBrush br(color);
		m_memDc.FrameRect(rc, &br);

		if(m_buttonId == 2)
		{
			CString sText = "מקום הכוכבים בימינו";
			CRect TextRc(0,0,m_sliderRc.Width(), 105);
			m_memDc.SetBkMode(TRANSPARENT);
			m_memDc.SetTextColor(color);
			m_memDc.DrawText(sText, TextRc, 
			DT_CENTER | DT_WORDBREAK | DT_TOP | DT_RTLREADING);

			sText = "לאחר המבול";
			TextRc.SetRect(0,m_sliderRc.Height()-100, 
				m_sliderRc.Width(),m_sliderRc.Height());
			m_memDc.DrawText(sText, TextRc, 
			DT_CENTER | DT_WORDBREAK | DT_TOP | DT_RTLREADING);

			CPen pen(PS_SOLID,1,color);
			m_memDc.SelectObject(&pen);
			m_memDc.MoveTo(10, posy);
			m_memDc.LineTo(m_sliderRc.Width()-10,posy);
		}
}

	dc.BitBlt(m_sliderRc.left,
		m_sliderRc.top,m_sliderRc.Width(),m_sliderRc.Height(),
		&m_memDc,0,0,SRCCOPY);
	m_memDc.RestoreDC(n);
}

BOOL CPerek25::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_EXTRA_DRAW:
		PaintSlider();
		return TRUE;
	}

	return CPerek3DBase::OnWndMsg(message, wParam, lParam, pResult);
}

void CPerek25::InitOnSubHeadButton(void)
{
	switch(m_buttonId)
	{
	case 4:
		m_xTurn = 0;
		m_yTurn = 180;
		break;
	case 6:
		m_xTurn = 30;
		m_yTurn = 0;
		break;
	default:
		m_xTurn = 0;
		m_yTurn = 0;
		posy = m_hieghtOffSet;
		break;
	}
	PaintSlider();
}
