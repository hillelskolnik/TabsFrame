// Perek50.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek50.h"

#include "MainFrm.h"
#include "SpeedTable.h"


// CPerek50

IMPLEMENT_DYNCREATE(CPerek50, CPerek3DBase)

CPerek50::CPerek50()
: color0(0)
, m_past(0)
, m_year(0)
, m_xStart(10.0)
, m_yStart(90.0)
, trsz(360)
, m_lastX(0)
, m_shemeshEmzai(0)
, m_shemeshAmity(0)
, m_amityAliyaYeshara(0)
, m_angNetiya(0)
, m_kizuz(0)
, trszArez(50)
, arezSteps(0)
{
	arezSteps = DiameterSteps(trszArez);

	m_ipWidth = m_ipHeight * 350 / 300;
	m_rcRes.SetRect(m_ipWidth - 120, 170, m_ipWidth, 600);
	m_pt.SetPoint(m_ipWidth/2, m_ipHeight/2);
	m_IDstart = ID_P50_1;
	m_IDidx = WT_PEREK_50;
	m_IDX_PEREK = IDX_PEREK_50;
}

CPerek50::~CPerek50()
{
}

BEGIN_MESSAGE_MAP(CPerek50, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P50_1, ID_P50_1, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P50_1, ID_P50_1, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CPerek50 diagnostics

#ifdef _DEBUG
void CPerek50::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek50::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek50 message handlers



IMPLEMENT_DYNCREATE(CPerek50Split, CBasePerekSplit)

CPerek50Split::CPerek50Split()
{

}

CPerek50Split::~CPerek50Split()
{
}

BEGIN_MESSAGE_MAP(CPerek50Split, CBasePerekSplit)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPerek50Split diagnostics

#ifdef _DEBUG
void CPerek50Split::AssertValid() const
{
	CWnd::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek50Split::Dump(CDumpContext& dc) const
{
	CWnd::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek50Split message handlers

void CPerek50Split::Create(UINT nPane)
{
	CMainFrame* m_pMainFrame = (CMainFrame*)AfxGetMainWnd();

	CreateStatic(m_pMainFrame,1,2,WS_CHILD | WS_VISIBLE | WS_BORDER, nPane);
	m_leftSpliter.CreateStatic(this,2,1,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		IdFromRowCol(0,0));

	CRect rc;
	m_pMainFrame->GetClientRect(rc);

	CreateView(0,1,RUNTIME_CLASS(CPerek50), CSize(0, 0), NULL);
	m_leftSpliter.CreateView(0,0,RUNTIME_CLASS(CPerek50Msg), CSize(0, 0), NULL);
	m_leftSpliter.CreateDlg(1,0,&m_calider,CSize(cal_cx,cal_cy),CCaliderDlg::IDD);
	m_calider.SetResultWnd(this);
	m_calider.SetDate(g_IkarRefael);

	ShowWindow(SW_SHOW);

	m_bIsSplitCreated = true;
	OnSize(0, rc.Width(), rc.Height());
}

void CPerek50Split::OnSize(UINT nType, int cx, int cy)
{
	CBasePerekSplit::OnSize(nType, cx, cy);

	int fourfifthx = cx - cal_cx - 25;
	if(GetSafeHwnd() && m_bIsSplitCreated)
	{
		SetColumnInfo(1, fourfifthx, 10);
		SetColumnInfo(0, cx - fourfifthx, 10);
		CRect rc;
		m_leftSpliter.GetClientRect(rc);
		m_leftSpliter.SetRowInfo(0, rc.Height()/3, rc.Height()/8);
		RecalcLayout();
		m_leftSpliter.RecalcLayout();
	}
}




// CPerek50Msg

IMPLEMENT_DYNCREATE(CPerek50Msg, CMsgView)

CPerek50Msg::CPerek50Msg()
{

}

CPerek50Msg::~CPerek50Msg()
{
}

BEGIN_MESSAGE_MAP(CPerek50Msg, CMsgView)
END_MESSAGE_MAP()


// CPerek50Msg drawing

void CPerek50Msg::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	CRect rc;
	GetClientRect(rc);
	int cx = rc.Width();
	int cy = rc.Height();
	pDC->SetStretchBltMode(HALFTONE);
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(250, 250);
	pDC->SetViewportExt(cx, cy);
	pDC->SetViewportOrg(0, 0);
	pDC->SetBkMode(TRANSPARENT);
	CRect rc2(0,30,250,250);
	CString sTxt, sMsg;

	COLORREF txtcolor = pDC->SetTextColor(RGB(0,255,0));
	CFont* pFont = pDC->SelectObject(&m_fontHe);
	sMsg = "העיקור ב' ניסן ה' אלפים תצ";

	int h = pDC->DrawText(sMsg, rc2, 
		DT_CENTER | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/) + 10;
	rc2.top += h;

	sMsg = "גובה השמש";
	pDC->SetTextColor(RGB(190,0,0));
	h = pDC->DrawText(sMsg, rc2, 
		DT_CENTER | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);
	rc2.top += h;
	pDC->SelectObject(&m_fontEn);
	sMsg = "97° 56\' 48\"";
	h = pDC->DrawText(sMsg, rc2, 
		DT_CENTER | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/)+10;
	rc2.top += h;

	pDC->SelectObject(&m_fontHe);
	sMsg = "אמצע השמש";
	pDC->SetTextColor(RGB(128,0,128));
	h = pDC->DrawText(sMsg, rc2, 
		DT_CENTER | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);
	rc2.top += h;

	pDC->SelectObject(&m_fontEn);
	sMsg = "356° 53\' 15\"";
	h = pDC->DrawText(sMsg, rc2, 
		DT_CENTER | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);
	rc2.top += h;

	pDC->SelectObject(&m_fontHe);
	sMsg = "זמן חצות מקומי בירושלים לפי שעוננו הוא 11:39";
	pDC->SetTextColor(RGB(255,255,0));
	h = pDC->DrawText(sMsg, rc2, 
		DT_CENTER | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);
	rc2.top += h;

	pDC->SetTextColor(txtcolor);
	pDC->SelectObject(pFont);
}


// CPerek50Msg diagnostics

#ifdef _DEBUG
void CPerek50Msg::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek50Msg::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


enum
{
	ofek
	,ofekcir

	,ofanHzi
	,ofanHziShetach
	,galgalMashve
	,galgalMazalot
	,shemesh
	,shemesh2
	,maarav


	,arez
};
// CPerek50Msg message handlers

int CPerek50::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	color0 = cp.paragraphs[0].color;

	CClientDC dc(this);
	m_memDc.CreateCompatibleDC(&dc);
	m_memBm.CreateCompatibleBitmap(&dc, m_ipWidth,m_ipHeight);
	m_memDc.SelectObject(&m_memBm);
	m_memDc.SelectObject(&m_font);


	m_3dscreen.SetScreenWnd(this);
	m_3dscreen.SetSceenSize(350,300, 25.0, 3.0, 7.0);
	m_3dscreen.SetScreenTransparentColor(0);
	m_3dscreen.CreateScreenDC();
	m_3dscreen.NoPaint();


	m_3dscreen.BeginObject(ofek);
	m_3dscreen.CreatObjectPixselMap(trsz,trsz);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm1.GetMyPaintDC();
		CPen pen1(PS_SOLID,1,(COLORREF)0);
		CBrush br1(RGB(255,255,96)/*color3*/);
		pdc->SelectObject(&pen1);
		pdc->SelectObject(&br1);
		CRect rc(0,0,trsz,trsz);
		pdc->FillSolidRect(CRect(0,0,trsz, trsz),0);
		pdc->Ellipse(rc);
		m_3dscreen.BitmapToObject(bm1, RGBT2(0,50));
	}
	m_3dscreen.FillRect(0,0,trsz, trsz, RGBT(96,48,0,70)
		,fr_xyIntensity , (double)trsz / 2.0 - 0.5);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(ofekcir);
	m_3dscreen.CReateCircleLineObject(trsz-1, RGB(255,255,255));
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(galgalMashve);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(255,0,128));
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.CReateCircleLineObject(trsz, RGB(128,0,255));
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(ofanHzi);
	m_3dscreen.CReateCircleLineObject(trsz,RGB(255,0,255));
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(ofanHziShetach);
	{
		CMyFBitmap bm1;
		bm1.CreateMyCompatibleBitmap(&dc,trsz,trsz,0);
		CDC* pdc = bm1.GetMyPaintDC();
		CPen pen1(PS_SOLID,1,RGB(255,128,255));
		CBrush br1((COLORREF)0);
		pdc->SelectObject(&pen1);
		pdc->SelectObject(&br1);
		CRect rc(0,0,trsz,trsz);
		pdc->FillSolidRect(CRect(0,0,trsz, trsz),0);

		double degree = 0;
		for(int i = 0; i < 12; ++i, degree += 30.0)
		{
			DrawPolyLines(2, rc.Width() / 2,
				rc.CenterPoint(),bm1, degree, 180.0);
		}

		m_3dscreen.CreateFlatBmObj(bm1);
	}
	m_3dscreen.ResetTranslation();

	int sShemesh = 9;
	int stepsShem = DiameterSteps(sShemesh);
	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(128,0,0, 20));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(255,128,0,20)
		,fr_zIntensity , (double)sShemesh / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(
		(double)trsz / 2.0,axis_y, true);
	m_3dscreen.ResetTranslation();

	m_3dscreen.BeginObject(shemesh2);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(0,0,128, 20));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(0,128,255,20)
		,fr_zIntensity , (double)sShemesh / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(
		(double)trsz / 2.0,axis_y, true);
	m_3dscreen.ResetTranslation();

	CreateText(maarav, "םערב", RGB(92,32,92));
	m_3dscreen.ShiftObjectCenter(
		-(double)trsz / 2.0-2.0,axis_z, true);
	m_3dscreen.ResetTranslation();


	m_3dscreen.BeginObject(arez);
	m_3dscreen.CreateSphereObject(trszArez, 0,360,90,-90);
	m_3dscreen.BitmapToObject(bm11, RGBT2(0,0));
	m_3dscreen.TurnShape(145.0,axis_y, false,true);
	m_3dscreen.TurnShape(90.0,axis_z, false,true);
	m_3dscreen.ResetTranslation();


	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}

void CPerek50::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();


	m_3dscreen.BeginObject(arez);


		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnLightPt(0,axis_X, true);
		m_3dscreen.TurnLightPt(270.0,axis_X);
		m_3dscreen.TurnLightPt(m_angNetiya,axis_Z);
		m_3dscreen.TurnLightPt(m_kizuz,axis_X);
		m_3dscreen.TurnLightPt(90.0,axis_X);


		CFillRectData data;
		data.radius = (double)trszArez / 2.0;
		data.vec2 = 0.4;
		m_3dscreen.FillRect(0,0,arezSteps,arezSteps/2, RGB(24,24,24), 
			fr_lightOppositeDirection, data);


	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(-32, axis_Z);
	m_3dscreen.TurnMatrix(m_xTurn + m_xStart, axis_X);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();


	m_3dscreen.BeginObject(ofekcir);
	if(m_lastX != m_xTurn)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(90.0, axis_X);
		m_3dscreen.TurnMatrix(m_yStart, axis_Y);

		m_3dscreen.TurnMatrix(m_xStart+m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);


	m_3dscreen.BeginObject(galgalMashve);
	if(m_lastX != m_xTurn)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(32.0, axis_X);
		m_3dscreen.TurnMatrix(m_yStart, axis_Y);
		m_3dscreen.TurnMatrix(m_xStart+m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.InitMatrix();
	m_3dscreen.TurnMatrix(90.0, axis_y); 
	m_3dscreen.TurnMatrix(23.5, axis_Z); 
	m_3dscreen.TurnMatrix(m_amityAliyaYeshara + m_kizuz, axis_X);
	m_3dscreen.TurnMatrix(-32, axis_Z);
	m_3dscreen.TurnMatrix(m_yStart-90.0, axis_Y);
	m_3dscreen.TurnMatrix(m_xTurn + m_xStart, axis_X);
	m_3dscreen.Transform();
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(ofek);
	if(m_lastX != m_xTurn)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(90.0, axis_X);
		m_3dscreen.TurnMatrix(m_yStart, axis_Y);
		m_3dscreen.TurnMatrix(m_xStart+m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(maarav);
	if(m_lastX != m_xTurn)
	{
		m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_xStart+m_xTurn + 10, axis_X);
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(shemesh2);
	m_3dscreen.ResetShift();
	m_3dscreen.TurnObjectCenter(-m_shemeshAmity, axis_Z);
	m_3dscreen.TurnObjectCenter(23.5, axis_Y);
	m_3dscreen.TurnObjectCenter(m_shemeshEmzai, axis_Z);
	m_3dscreen.TurnObjectCenter(32.0, axis_X);
	m_3dscreen.TurnObjectCenter(m_yStart, axis_Y);
	m_3dscreen.TurnObjectCenter(m_xStart+m_xTurn, axis_X);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.ResetShift();
		m_3dscreen.TurnObjectCenter(m_angNetiya,axis_Z);
		m_3dscreen.TurnObjectCenter(m_kizuz + 90.0,axis_X);
		m_3dscreen.TurnObjectCenter(-32.0,axis_Z);
		m_3dscreen.TurnObjectCenter(m_yStart - 90.0, axis_Y);
		m_3dscreen.TurnObjectCenter(m_xTurn + m_xStart, axis_X);
	m_3dscreen.TurnShape(0.0, axis_Y);
	m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(ofanHzi);
	if(m_lastX != m_xTurn)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xStart+m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(ofanHziShetach);
	if(m_lastX != m_xTurn)
	{
		m_3dscreen.InitMatrix();
		m_3dscreen.TurnMatrix(m_xStart+m_xTurn, axis_X);
		m_3dscreen.Transform();
		m_3dscreen.Translate3Dto2D();
	}
	else
		m_3dscreen.Translate3Dto2D(FALSE);

	m_lastX = m_xTurn;
	PaintResult();
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

BOOL CPerek50::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_EXTRA_DRAW:
		{
			Do3DPaint();			
		}
		return TRUE;
	case BASIC_DLL_MSG:
		{
			CScaleResult &result = *((CScaleResult*)lParam);
			long year = result.val;
			m_past = (long)(result.result);
			if(year != m_year)
			{
				m_year = year;
			}
			CDaysPast dpRefael(g_IkarRefael);
			double past = m_past - (long)dpRefael;
			// middel time between midday and sun set
			past += 1.0 - 0.260101350308642 / 2.0;
			CCircleSpeed cs = g_table.emzaShemesh * past;
			CCircleSpeed res = cs + g_IkaryRefael.emzaShemesh;
			m_shemeshEmzai = res.GetAccurateDouble();
			cs = g_table.govaShemesh * past;
			res = cs + g_IkaryRefael.govaShemesh;
			double gova = res.GetAccurateDouble();
			m_shemeshAmity = AdjusShemesAmity(ShemesAmity(m_shemeshEmzai, gova));
			m_amityAliyaYeshara = AliyaYeshara(m_shemeshAmity, 23.5);

			double sinNetiya = SinNetyatAliyaYeshara(m_shemeshAmity, 23.5);
			m_angNetiya = asin(sinNetiya) * ToD;
			double sAliya = 
				SinNetyatAliyaYeshara(m_shemeshAmity, 23.5);
			m_kizuz = kizuzNetiyaLaOfek(32.0,sAliya);

			Do3DPaint();			
		}
		return TRUE;
	}

	return CPerek3DBase::OnWndMsg(message, wParam, lParam, pResult);
}

void CPerek50::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = (p.x > 3 && p.y > 1 && p.x < m_ipWidth)?TRUE:FALSE;
	if( m_bBntDown && m_bHandCursor )
	{
		double cy = (p.y - m_pt.y);
		m_xTurn = cy / 4.0;
		Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

void CPerek50::InitOnSubHeadButton(void)
{
	m_lastX = 100000;
	PaintResult();
}

void CPerek50::PaintResult(void)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	m_memDc.FillSolidRect(m_rcRes, 0);

	CRect rc = m_rcRes;

	static CFont font;
	if(font.operator HFONT() == NULL)
		VERIFY(font.CreateFont(
			-20,                     // nHeight
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

	COLORREF txtcolor = m_memDc.SetTextColor(RGB(255,255,0));
	m_memDc.SetBkMode(TRANSPARENT);
	CFont* pFont = m_memDc.SelectObject(&font);
	CString sTxt, sMsg;



	double shaa = (m_amityAliyaYeshara - AliyaYeshara(m_shemeshEmzai, 23.5));
	if(shaa > 15.0)
		shaa -= 360.0;
	else if(shaa < -15.0)
		shaa += 360.0;

	
	double tzman = shaa / 15.0 + 12.0;
	double shaot = floor(tzman);
	double dakot = tzman - shaot;
	dakot *= 60.0;
	CString sNull = (dakot < 9.5)?"0":"";
//	sTxt.Format("%2.0f:%s%.0f", shaot, sNull, dakot);

	sMsg = "חצות היום לפי שעון מקומי 12:00 ירושלים";
	sTxt.Format("%s\n%2.0f:%s%.0f",sMsg, shaot, sNull, dakot);

	int h = m_memDc.DrawText(sTxt, rc, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/) + 10;

	sMsg = "חצות היום לפי שעוננו ירושלים";
	m_memDc.SetTextColor(RGB(255,32,160));

	tzman = shaa / 15.0 + 11.65;
	shaot = floor(tzman);
	dakot = tzman - shaot;
	dakot *= 60.0;
	sNull = (dakot < 9.5)?"0":"";
//	sTxt.Format("%2.0f:%s%.0f", shaot, sNull, dakot);

	sTxt.Format("%s\n%2.0f:%s%.0f",sMsg, shaot, sNull, dakot);

	rc.top = m_rcRes.top +h;

	h += m_memDc.DrawText(sTxt, rc, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/) + 10;


	double tosefetOfek = m_kizuz;
	if(tosefetOfek > 180.0)
		tosefetOfek -= 360.0;


	double temp = (shaa + 90.0 + tosefetOfek) / 15.0 + 11.65;
	double halakim = floor(temp);
	halakim = (temp - halakim) * 60.0;
	temp = floor(temp);

	CString sHalakim = (halakim < 9.5)?"0":"";
	if(halakim > 59.5)
	{
		halakim = 0;
		temp++;
	}

	sMsg = "זמן השקיעה אמצע גוף השמש גובה הים ירושלים לפי שעוננו";
	sTxt.Format("%s\n%3.0f:%s%.0f",sMsg, temp, sHalakim, halakim);

	rc.top = m_rcRes.top +h;
	m_memDc.SetTextColor(RGB(255,128,0));
	h += m_memDc.DrawText(sTxt, rc, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/);

	rc = m_rcRes;
	rc.bottom = m_rcRes.top +h;

	m_memDc.SetTextColor(txtcolor);
	m_memDc.SelectObject(pFont);

	dc.BitBlt(rc.left,rc.top,rc.Width(),m_rcRes.Height(),
		&m_memDc, rc.left,rc.top, SRCCOPY);
}
