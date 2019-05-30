// Perek48.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "Perek48.h"
#include "MainFrm.h"
#include "SpeedTable.h"
#include "DateStr.h"



// CPerek48

IMPLEMENT_DYNCREATE(CPerek48, CPerek3DBase)

CPerek48::CPerek48()
: color0(0)
, trsz(379)
, m_year(0)
, m_slider(this, CRect(0, 75,120,ipHeight- 75),CSlider::VerMin90Plus90)
, m_past(0)
, m_monthTurn(0)
, m_lastYeat(0)
, m_sAmity(0)
, m_ikarSmuel(1,6,23)
, m_speedShmuel(0,59,8,15,16,37,57)
, m_ikarAda(1,7,1)
, m_speedAda(0,59,8,17,7,46,8)
{
	m_ipWidth = m_ipHeight * 350 / 300;
	m_rcRes.SetRect(m_ipWidth - 110, 200, m_ipWidth, 300);
	int gova = 20;
	m_rcTishray = m_rcTamuz = m_rcNisan = CRect(50,gova, 214 + 30*12, gova +24);
	m_rcTamuz += CPoint(0,28);
	m_rcTishray += CPoint(0,678);
	m_rcTevet = m_rcTishray;
	m_rcTevet += CPoint(0,28);
	m_nCaptionBottom = 80;
	m_IDstart = ID_P48_1;
	m_IDidx = WT_PEREK_48;
	m_IDX_PEREK = IDX_PEREK_48;
}

CPerek48::~CPerek48()
{
}

BEGIN_MESSAGE_MAP(CPerek48, CPerek3DBase)
	ON_UPDATE_COMMAND_UI_RANGE(ID_P48_1, ID_P48_3, &CPerek2DBase::OnSubHeadUpdate)
	ON_COMMAND_RANGE(ID_P48_1, ID_P48_3, &CPerek3DBase::OnSubHeadBtn)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPerek48 diagnostics

#ifdef _DEBUG
void CPerek48::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek48::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek48 message handlers
enum
{
	galgalMazalot
	,shemesh
	,c21_spiralrag
	,c21_spiralmeurag
	,c21_spiralragmeu
};

int CPerek48::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPerek3DBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CMyFBitmap bm11;
	CString path = theApp.m_appPath + "Images\\mazalot1.bmp";
	CImage image22;
	image22.Load(path);
	bm11.CreateMyCompatibleBitmap(NULL, image22.GetWidth(),
		image22.GetHeight());
	image22.BitBlt(bm11.operator CDC *()->GetSafeHdc(),
		CPoint(0,0));


	m_dateNisanBm.CreateMyCompatibleBitmap(NULL, 36*9,14, RGB(255,0,0));
	m_dateNisanFont.Create(RGB(255,0,0),RGB(255,255,255));

	m_dateTamuzBm.CreateMyCompatibleBitmap(NULL, 36*9,14, RGB(0,135,255));
	m_dateTamuzFont.Create(RGB(0,135,255),RGB(255,255,255));

	m_dateTishrayBm.CreateMyCompatibleBitmap(NULL, 36*9,14, RGB(180,180,0));
	m_dateTishrayFont.Create(RGB(180,180,0),RGB(255,255,255));

	m_dateTevetBm.CreateMyCompatibleBitmap(NULL, 36*9,14, RGB(0,135,0));
	m_dateTevetFont.Create(RGB(0,135,0),RGB(255,255,255));

	m_slider.SetDeflate(3,3,3,3);
	m_slider.SetCaption("שעות היום");
	m_slider.SetResultFormat("%.1f");
	m_slider.SetMinMax(0,24);
	m_slider.SetRefPoint(bottom);
	m_slider.Init();
	m_slider.SetVal(0);

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


	path = theApp.m_appPath;
	CImage image;
	image.Load(path + "Images\\onot.bmp");

	HDC hdc = m_3dscreen.m_refreshDC.operator CDC *()->GetSafeHdc();
	BITMAP bm;
	m_3dscreen.m_refreshDC.GetBitmap(&bm);
	int left = (bm.bmWidth - image.GetWidth()) / 2;
	int top = (bm.bmHeight - image.GetHeight()) / 2;
	CRect rc(left,top,bm.bmWidth, bm.bmHeight);
	image.BitBlt(hdc, rc, CPoint(0,0));
	m_3dscreen.CopyRefreshToDib();


	int width = image22.GetHeight();
	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.CreateFlatSpiralObject(1080,width, -width, trsz/2 - width,360.0, 
		0);
	m_3dscreen.BitmapToObject(bm11);
	m_3dscreen.ResetTranslation();
	m_3dscreen.TurnShape(0.0,axis_y);
	m_3dscreen.Translate3Dto2D();

	int sShemesh = 13;
	int stepsShem = DiameterSteps(sShemesh);
	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.CreateSphereObject(sShemesh, 
		RGBT(128,0,0, 20));
	m_3dscreen.FillRect(0,0,stepsShem, stepsShem/2, RGBT(255,128,0,20)
		,fr_zIntensity , (double)sShemesh / 2.0 - 0.5);
	m_3dscreen.ShiftObjectCenter(
		160.0 / 2.0,axis_x, true);
	m_3dscreen.ResetTranslation();

	{
		m_3dscreen.BeginObject(c21_spiralrag);
		CImage imagespiralrag;
		CMyFBitmap piralragBm;
		imagespiralrag.Load(path + "Images\\hodashim_ragilragil.bmp");
		m_3dscreen.CreateFlatSpiralObject(imagespiralrag.GetWidth(),
			imagespiralrag.GetHeight(),
			4, 100, 522, RGB(0,0,255));

		piralragBm.CreateMyCompatibleBitmap(NULL, imagespiralrag.GetWidth(),
			imagespiralrag.GetHeight());
		imagespiralrag.BitBlt(piralragBm.operator CDC *()->GetSafeHdc(),
			CPoint(0,0));
		m_3dscreen.BitmapToObject(piralragBm);

		m_3dscreen.ResetShift();
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	{
		m_3dscreen.BeginObject(c21_spiralragmeu);
		CImage imagespiralrag;
		CMyFBitmap piralragBm;
		imagespiralrag.Load(path + "Images\\hodashim_ragilmuberet.bmp");
		m_3dscreen.CreateFlatSpiralObject(imagespiralrag.GetWidth(),
			imagespiralrag.GetHeight(),
			4, 100, 553.5, RGB(0,0,255));

		piralragBm.CreateMyCompatibleBitmap(NULL, imagespiralrag.GetWidth(),
			imagespiralrag.GetHeight());
		imagespiralrag.BitBlt(piralragBm.operator CDC *()->GetSafeHdc(),
			CPoint(0,0));
		m_3dscreen.BitmapToObject(piralragBm);

		m_3dscreen.ResetShift();
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}
	{
		m_3dscreen.BeginObject(c21_spiralmeurag);
		CImage imagespiralrag;
		CMyFBitmap piralragBm;
		imagespiralrag.Load(path + "Images\\hodashim_maubar_ragil.bmp");
		m_3dscreen.CreateFlatSpiralObject(imagespiralrag.GetWidth(),
			imagespiralrag.GetHeight(),
			4, 100, 550.5, RGB(0,0,255));

		piralragBm.CreateMyCompatibleBitmap(NULL, imagespiralrag.GetWidth(),
			imagespiralrag.GetHeight());
		imagespiralrag.BitBlt(piralragBm.operator CDC *()->GetSafeHdc(),
			CPoint(0,0));
		m_3dscreen.BitmapToObject(piralragBm);

		m_3dscreen.ResetShift();
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(0.0, axis_Y);
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.TrigerPaintAlow(1);
	m_3dscreen.TrigerPaintAlow();
	return 0;
}


BOOL CPerek48::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_EXTRA_DRAW:
		{
			m_slider.InitOnSubHeadButton();
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
				switch(m_buttonId)
				{
				case 0:
					DrawTkufaAmity();
					break;
				case 1:
					DrawTkufaShmuel();
					break;
				case 2:
					DrawTkufaAda();
					break;
				}
			}
			Do3DPaint();			
		}
		return TRUE;
	}

	return CPerek3DBase::OnWndMsg(message, wParam, lParam, pResult);
}

void CPerek48::Do3DPaint(void)
{
	if(/*m_bPastCreate == false || */m_bSkip)
		return;
	m_bSkip = true;
	m_3dscreen.ClearScreen();

	m_3dscreen.BeginObject(galgalMazalot);
	m_3dscreen.Translate3Dto2D(FALSE);

	m_3dscreen.BeginObject(shemesh);
	m_3dscreen.ResetShift();
	CDaysPast ikar(g_IkarRefael);
	long ikarDays = (long)ikar;
	long past = m_past - ikarDays;
	CCircleSpeed emzaShemeshDate = g_IkaryRefael.emzaShemesh + g_table.emzaShemesh * past;
	CCircleSpeed minShlishShaa = g_table.emzaShemesh * (double)(-1.0/72.0);
	CCircleSpeed shotHayom = g_table.emzaShemesh * (m_xTurn / 24.0);
	CCircleSpeed theAng = emzaShemeshDate + minShlishShaa + shotHayom;
	double dAng = theAng.GetAccurateDouble();

	CCircleSpeed govaShemeshDate = g_IkaryRefael.govaShemesh + g_table.govaShemesh * past;
	CCircleSpeed govaMinShlishShaa = g_table.govaShemesh * (double)(-1.0/72.0);
	CCircleSpeed govaShotHayom = g_table.govaShemesh * (m_xTurn / 24.0);
	CCircleSpeed theGovaAng = govaShemeshDate + govaMinShlishShaa + govaShotHayom;
	double sGovaAng = theGovaAng.GetAccurateDouble();
	m_sAmity = ShemesAmity(dAng, sGovaAng);


	m_3dscreen.TurnObjectCenter(m_sAmity, axis_z);
	m_3dscreen.TurnShape(0.0, axis_y);
	m_3dscreen.Translate3Dto2D();

	CYearTypesAndCycles ytacnext(m_year + 1);
	bool Leapnext  = ytacnext.IsLeapYear();
	CYearTypesAndCycles ytac(m_year);
	bool Leap  = ytac.IsLeapYear();

	DWORD dwFlags = 7;
	if(Leap == false && Leapnext == true)
	{
		dwFlags -= 1;
		m_3dscreen.BeginObject(c21_spiralragmeu);
	}

	if(Leap == true && Leapnext == false)
	{
		dwFlags -= 2;
		m_3dscreen.BeginObject(c21_spiralmeurag);
	}

	if(Leap == false && Leapnext == false)
	{
		dwFlags -= 4;
		m_3dscreen.BeginObject(c21_spiralrag);
	}

	if(m_lastYeat == m_year)
	{
		m_3dscreen.Translate3Dto2D(FALSE);
	}
	else
	{
		switch(m_buttonId)
		{
		case 0:
			m_monthTurn = GetNisanRambam(m_year);
			break;
		case 1:
			m_monthTurn = GetTishrayShmuel(m_year);
			break;
		case 2:
			m_monthTurn = GetTishrayAda(m_year);
			break;
		}
		m_3dscreen.ResetShift();
		m_3dscreen.ResetTranslation();
		m_3dscreen.TurnShape(m_monthTurn, axis_Z);
		m_3dscreen.Translate3Dto2D();
	}

	if(dwFlags & 1)
	{
		m_3dscreen.BeginObject(c21_spiralragmeu);
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}
	if(dwFlags & 2)
	{
		m_3dscreen.BeginObject(c21_spiralmeurag);
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}
	if(dwFlags & 4)
	{
		m_3dscreen.BeginObject(c21_spiralrag);
		m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);
	}

	m_lastYeat = m_year;
	TkufutResult();
	PaintResult();
	m_3dscreen.ScreenToDC();
	m_3dscreen.TrigerPaintAlow(1);
}

IMPLEMENT_DYNCREATE(CPerek48Split, CBasePerekSplit)

CPerek48Split::CPerek48Split()
{

}

CPerek48Split::~CPerek48Split()
{
}

BEGIN_MESSAGE_MAP(CPerek48Split, CBasePerekSplit)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPerek48Split diagnostics

#ifdef _DEBUG
void CPerek48Split::AssertValid() const
{
	CWnd::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek48Split::Dump(CDumpContext& dc) const
{
	CWnd::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek48Split message handlers

void CPerek48Split::Create(UINT nPane)
{
	CMainFrame* m_pMainFrame = (CMainFrame*)AfxGetMainWnd();

	CreateStatic(m_pMainFrame,1,2,WS_CHILD | WS_VISIBLE | WS_BORDER, nPane);
	m_leftSpliter.CreateStatic(this,2,1,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		IdFromRowCol(0,0));

	CRect rc;
	m_pMainFrame->GetClientRect(rc);

	CreateView(0,1,RUNTIME_CLASS(CPerek48), CSize(0, 0), NULL);
	m_leftSpliter.CreateView(0,0,RUNTIME_CLASS(CPerek48Msg), CSize(0, 0), NULL);
	m_leftSpliter.CreateDlg(1,0,&m_calider,CSize(cal_cx,cal_cy),CCaliderDlg::IDD);
	m_calider.SetResultWnd(this);
	m_calider.SetDate(g_IkarRefael);

	ShowWindow(SW_SHOW);

	m_bIsSplitCreated = true;
	OnSize(0, rc.Width(), rc.Height());
}

void CPerek48Split::OnSize(UINT nType, int cx, int cy)
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
// Perek48.cpp : implementation file
//

// CPerek48Msg

IMPLEMENT_DYNCREATE(CPerek48Msg, CMsgView)

CPerek48Msg::CPerek48Msg()
{

}

CPerek48Msg::~CPerek48Msg()
{
}

BEGIN_MESSAGE_MAP(CPerek48Msg, CMsgView)
END_MESSAGE_MAP()


// CPerek48Msg drawing

void CPerek48Msg::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CPerek48Msg diagnostics

#ifdef _DEBUG
void CPerek48Msg::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPerek48Msg::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPerek48Msg message handlers

double CPerek48::GetTkufaEmzaiAng(long year, eTkufot tkufa)
{
	double tkufaAmity = 360;
	long month = GetTkufaMonth(year, tkufa);
	switch(tkufa)
	{
	case tkufat_tamuz:
		tkufaAmity = 90;
		break;
	case tkufat_tishray:
		tkufaAmity = 180;
		break;
	case tkufat_tevet:
		tkufaAmity = 270;
		break;
	}
	CDaysPast thisYear(year, month);
	CDaysPast ikar(g_IkarRefael);
	long ikarDays = (long)ikar;
	long dateDays = (long)thisYear;
	long past = dateDays - ikarDays;
	CCircleSpeed gova = g_IkaryRefael.govaShemesh + g_table.govaShemesh * past;
	double thisGova = gova.GetAccurateDouble();
	double tkufaEmzai = AdjusShemesAmity(ShemeshAmity2Emzai(tkufaAmity, thisGova));
	return tkufaEmzai;
}

double CPerek48::GetTkufaEmzaiTryAng(long year, eTkufot tkufa)
{
	long month = GetTkufaMonth(year, tkufa);

	CDaysPast thisYear(year, month);
	CDaysPast ikar(g_IkarRefael);
	long ikarDays = (long)ikar;
	long dateDays = (long)thisYear;
	long past = dateDays - ikarDays;
	CCircleSpeed emzaTry = g_IkaryRefael.emzaShemesh + g_table.emzaShemesh * past;
	double tkufaEmzaiTry = emzaTry.GetAccurateDouble();
	return tkufaEmzaiTry;
}

CString CPerek48::GetTkufaStr(long year, eTkufot tkufa)
{
	double tkufaEmzai = GetTkufaEmzaiAng(year, tkufa);
	double tkufaEmzaiTry = GetTkufaEmzaiTryAng(year, tkufa);
	if(tkufaEmzai < tkufaEmzaiTry)
		tkufaEmzai += 360;
	double diff = tkufaEmzai - tkufaEmzaiTry;
	//if(diff > 60)
	//	diff -= 360.0;
	CCircleSpeed sDiff(1);
	sDiff = sDiff * diff;
	double toAdd = diff / g_table.emzaShemesh.GetAccurateDouble();
	CTimeAccessor taToAdd;
	taToAdd.SetUnit(toAdd);
	long month = GetTkufaMonth(year, tkufa);
	CDaysPast baseDate(year,month);
	CTimeAccessor baseTry(baseDate, 0, 360);
	baseTry += taToAdd;
	baseTry.Organizer(false);
	CDateStr ds = (CTimeUnit)baseTry;
	return ds.GetDateAndMinuts();
}
long CPerek48::GetTkufaMonth(long &year, eTkufot tkufa)
{
	long month = 0;
	switch(tkufa)
	{
	case tkufat_nisan:
		month = 6;
		break;
	case tkufat_tamuz:
		month = 9;
		break;
	case tkufat_tishray:
		month = 12;
		//year++;
		break;
	case tkufat_tevet:
		year++;
		month = 3;
		break;
	}
	if(tkufa == tkufat_nisan || tkufa == tkufat_tamuz || tkufa == tkufat_tishray)
	{
		CYearTypesAndCycles ytac(year);
		bool bLeap = ytac.IsLeapYear();
		if(bLeap)
			month++;
	}

	return month;
}

void CPerek48::TkufutResult(void)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);

	dc.BitBlt(m_rcNisan.left,m_rcNisan.top, m_rcNisan.Width(), m_rcNisan.Height(),
		&m_memDc,m_rcNisan.left,m_rcNisan.top, SRCCOPY);
	dc.BitBlt(m_rcTamuz.left,m_rcTamuz.top, m_rcTamuz.Width(), m_rcTamuz.Height(),
		&m_memDc,m_rcTamuz.left,m_rcTamuz.top, SRCCOPY);
	dc.BitBlt(m_rcTishray.left,m_rcTishray.top, m_rcTishray.Width(), m_rcTishray.Height(),
		&m_memDc,m_rcTishray.left,m_rcTishray.top, SRCCOPY);
	dc.BitBlt(m_rcTevet.left,m_rcTevet.top, m_rcTevet.Width(), m_rcTevet.Height(),
		&m_memDc,m_rcTevet.left,m_rcTevet.top, SRCCOPY);
}

void CPerek48::DrawTkufaAmity(void)
{
	CString str = GetTkufaStr(m_year, tkufat_nisan);
	CDC *pDC = m_dateNisanBm.GetMyPaintDC();
	m_dateNisanFont.DrawString(pDC,0,0,str);
	m_dateNisanBm.StrechDraw(&m_memDc,m_rcNisan.left,
		m_rcNisan.top, m_rcNisan.Width(), m_rcNisan.Height());

	str = GetTkufaStr(m_year, tkufat_tamuz);
	pDC = m_dateTamuzBm.GetMyPaintDC();
	m_dateTamuzFont.DrawString(pDC,0,0,str);
	m_dateTamuzBm.StrechDraw(&m_memDc,m_rcTamuz.left,
		m_rcTamuz.top, m_rcTamuz.Width(), m_rcTamuz.Height());

	str = GetTkufaStr(m_year, tkufat_tishray);
	pDC = m_dateTishrayBm.GetMyPaintDC();
	m_dateTishrayFont.DrawString(pDC,0,0,str);
	m_dateTishrayBm.StrechDraw(&m_memDc,m_rcTishray.left,
		m_rcTishray.top, m_rcTishray.Width(), m_rcTishray.Height());

	str = GetTkufaStr(m_year, tkufat_tevet);
	pDC = m_dateTevetBm.GetMyPaintDC();
	m_dateTevetFont.DrawString(pDC,0,0,str);
	m_dateTevetBm.StrechDraw(&m_memDc,m_rcTevet.left,
		m_rcTevet.top, m_rcTevet.Width(), m_rcTevet.Height());
}

void CPerek48::InitOnSubHeadButton(void)
{
	m_lastYeat = 0;
	switch(m_buttonId)
	{
	case 0:
		DrawTkufaAmity();
		break;
	case 1:
		DrawTkufaShmuel();
		break;
	case 2:
		DrawTkufaAda();
		break;
	}
	m_slider.InitOnSubHeadButton();
}

void CPerek48::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint p = point;
	dc.DPtoLP(&p);

	m_bHandCursor  = m_slider.PntInRect(p);
	if( m_bBntDown && m_bHandCursor )
	{
		double cy = (p.y - m_pt.y);

		if(m_slider.PtInRect(p, m_xTurn))
			Do3DPaint();
	}

	CPerek3DBase::OnMouseMove(nFlags, point);
}

double CPerek48::GetNisanRambam(int year)
{
	//CYearTypesAndCycles ytac(year);
	//bool bLeap = ytac.IsLeapYear();
	long month = 7;//bLeap? 8 : 7;

	CDaysPast thisYear(year/*, month*/);
	CDaysPast ikar(g_IkarRefael);
	long ikarDays = (long)ikar;
	long dateDays = (long)thisYear;
	long past = dateDays - ikarDays;
	CCircleSpeed gova = g_IkaryRefael.govaShemesh + g_table.govaShemesh * past;
	double thisGova = gova.GetAccurateDouble();
	CCircleSpeed emzai = g_IkaryRefael.emzaShemesh + g_table.emzaShemesh * past;
	double thisEmzai = emzai.GetAccurateDouble();
	double amity = AdjusShemesAmity(ShemesAmity(thisEmzai, thisGova));

	CMollad molad(year);
	amity += (double)(molad.YearKind() + 2);

	return amity;
}

void CPerek48::PaintResult(void)
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

	sMsg = "שמש אמיתי";

	sTxt.Format("%s\n%s",sMsg, MaalotHalakim(m_sAmity));

	int h = m_memDc.DrawText(sTxt, rc, 
		DT_RIGHT | DT_WORDBREAK | DT_TOP /*| DT_RTLREADING*/) + 10;

	rc.bottom = m_rcRes.top +h;

	m_memDc.SetTextColor(txtcolor);
	m_memDc.SelectObject(pFont);

	dc.BitBlt(rc.left,rc.top,rc.Width(),m_rcRes.Height(),
		&m_memDc, rc.left,rc.top, SRCCOPY);
}

double CPerek48::GetTishrayShmuel(int year)
{
	static long nIkarShmuel = (long)m_ikarSmuel;
	CDaysPast roshHodeshTishray(year);
	long pastTishray = (long)roshHodeshTishray;
	CCircleSpeed tishrayAng = m_speedShmuel * (pastTishray - nIkarShmuel);
	double ang = tishrayAng.GetAccurateDouble();

	CMollad molad(year);
	ang += (double)(molad.YearKind() - 0);

	return ang;
}

void CPerek48::DrawTkufaShmuel(void)
{
	CString str = GetTkufatSmueaStr(m_year, tkufat_nisan);
	CDC *pDC = m_dateNisanBm.GetMyPaintDC();
	m_dateNisanFont.DrawString(pDC,0,0,str);
	m_dateNisanBm.StrechDraw(&m_memDc,m_rcNisan.left,
		m_rcNisan.top, m_rcNisan.Width(), m_rcNisan.Height());

	str = GetTkufatSmueaStr(m_year, tkufat_tamuz);
	pDC = m_dateTamuzBm.GetMyPaintDC();
	m_dateTamuzFont.DrawString(pDC,0,0,str);
	m_dateTamuzBm.StrechDraw(&m_memDc,m_rcTamuz.left,
		m_rcTamuz.top, m_rcTamuz.Width(), m_rcTamuz.Height());

	str = GetTkufatSmueaStr(m_year, tkufat_tishray);
	pDC = m_dateTishrayBm.GetMyPaintDC();
	m_dateTishrayFont.DrawString(pDC,0,0,str);
	m_dateTishrayBm.StrechDraw(&m_memDc,m_rcTishray.left,
		m_rcTishray.top, m_rcTishray.Width(), m_rcTishray.Height());

	str = GetTkufatSmueaStr(m_year, tkufat_tevet);
	pDC = m_dateTevetBm.GetMyPaintDC();
	m_dateTevetFont.DrawString(pDC,0,0,str);
	m_dateTevetBm.StrechDraw(&m_memDc,m_rcTevet.left,
		m_rcTevet.top, m_rcTevet.Width(), m_rcTevet.Height());
}

CString CPerek48::GetTkufatSmueaStr(long year, eTkufot tkufa)
{
	static double yearDays = 365.25;
	double addtoyear = 0;
	switch(tkufa)
	{
	case tkufat_tamuz:
		addtoyear = yearDays * 0.25;
		break;
	case tkufat_tishray:
		addtoyear = yearDays * 0.5;
		break;
	case tkufat_tevet:
		addtoyear = yearDays * 0.75;
		break;
	}

	double days = yearDays * (double)(year - 1) + addtoyear;
	//if(year > 1)
	//	days--;
	long nDays = (long)(float)days;
	double remain = days - floor(days);

	CYMDs tkufaDate = m_ikarSmuel + nDays;
	CDaysPast dp(tkufaDate);
	CTimeAccessor taRemain;
	taRemain.SetUnit(remain);
	CTimeAccessor theDate(dp);
	theDate += taRemain;
	theDate.Organizer(false);

	CDateStr ds = (CTimeUnit)theDate;
	return ds.GetDateAndMinuts();
}

void CPerek48::DrawTkufaAda(void)
{
	CString str = GetTkufatAdaStr(m_year, tkufat_nisan);
	CDC *pDC = m_dateNisanBm.GetMyPaintDC();
	m_dateNisanFont.DrawString(pDC,0,0,str);
	m_dateNisanBm.StrechDraw(&m_memDc,m_rcNisan.left,
		m_rcNisan.top, m_rcNisan.Width(), m_rcNisan.Height());

	str = GetTkufatAdaStr(m_year, tkufat_tamuz);
	pDC = m_dateTamuzBm.GetMyPaintDC();
	m_dateTamuzFont.DrawString(pDC,0,0,str);
	m_dateTamuzBm.StrechDraw(&m_memDc,m_rcTamuz.left,
		m_rcTamuz.top, m_rcTamuz.Width(), m_rcTamuz.Height());

	str = GetTkufatAdaStr(m_year, tkufat_tishray);
	pDC = m_dateTishrayBm.GetMyPaintDC();
	m_dateTishrayFont.DrawString(pDC,0,0,str);
	m_dateTishrayBm.StrechDraw(&m_memDc,m_rcTishray.left,
		m_rcTishray.top, m_rcTishray.Width(), m_rcTishray.Height());

	str = GetTkufatAdaStr(m_year, tkufat_tevet);
	pDC = m_dateTevetBm.GetMyPaintDC();
	m_dateTevetFont.DrawString(pDC,0,0,str);
	m_dateTevetBm.StrechDraw(&m_memDc,m_rcTevet.left,
		m_rcTevet.top, m_rcTevet.Width(), m_rcTevet.Height());
}


CString CPerek48::GetTkufatAdaStr(long year, eTkufot tkufa)
{
	static double yearDays = 365.246822211054;
	double addtoyear = 0;
	switch(tkufa)
	{
	case tkufat_tamuz:
		addtoyear = yearDays * 0.25;
		break;
	case tkufat_tishray:
		addtoyear = yearDays * 0.5;
		break;
	case tkufat_tevet:
		addtoyear = yearDays * 0.75;
		break;
	}

	double days = yearDays * (double)(year - 1) + addtoyear;
	//if(year > 1)
	//	days--;
	long nDays = (long)(float)days;
	double remain = days - floor(days);

	CYMDs tkufaDate = m_ikarAda + nDays;
	CDaysPast dp(tkufaDate);
	CTimeAccessor taRemain;
	taRemain.SetUnit(remain);
	CTimeAccessor theDate(dp);
	theDate += taRemain;
	theDate.Organizer(false);

	CDateStr ds = (CTimeUnit)theDate;
	return ds.GetDateAndMinuts();
}

double CPerek48::GetTishrayAda(int year)
{
	static long nIkarAda = (long)m_ikarAda;
	CDaysPast roshHodeshTishray(year);
	long pastTishray = (long)roshHodeshTishray;
	CCircleSpeed tishrayAng = m_speedAda * (pastTishray - nIkarAda);
	double ang = tishrayAng.GetAccurateDouble();

	CMollad molad(year);
	ang += (double)(molad.YearKind() - 2);

	return ang;
}
