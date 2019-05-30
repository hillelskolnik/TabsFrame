// CaliderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CaliderDlg.h"


// CCaliderDlg dialog

IMPLEMENT_DYNAMIC(CCaliderDlg, CDialog)
CCaliderDlg::CCaliderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCaliderDlg::IDD, pParent)
	, m_nElef(0)
	, m_nMeha(0)
	, m_nEser(0)
	, m_pWnd(NULL)
	, m_nEhad(0)
	, m_shnimLeft(0)
	, m_nMonths(0)
	, m_bLeap(false)
	, m_nMDay(0)
	, m_nYears(1)
	, m_daysInMonth(30)
	, m_nYearsJump(1)
	, m_shiftDays(0)
{
}

CCaliderDlg::~CCaliderDlg()
{
}

void CCaliderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_ELEF, m_ctrlElef);
	DDX_Control(pDX, IDC_SLIDER_MEHA, m_ctrlMeha);
	DDX_Control(pDX, IDC_SLIDER_ESER, m_ctrlEser);
	DDX_Slider(pDX, IDC_SLIDER_ELEF, m_nElef);
	DDX_Slider(pDX, IDC_SLIDER_MEHA, m_nMeha);
	DDX_Slider(pDX, IDC_SLIDER_ESER, m_nEser);
	DDX_Control(pDX, IDC_SLIDER_Ehad, m_ctrlEhad);
	DDX_Slider(pDX, IDC_SLIDER_Ehad, m_nEhad);
	DDX_Control(pDX, IDC_SLIDER_Month, m_ctrlMonths);
	DDX_Slider(pDX, IDC_SLIDER_Month, m_nMonths);
	DDX_Control(pDX, IDC_SLIDER_MDay, m_ctrlMDay);
	DDX_Slider(pDX, IDC_SLIDER_MDay, m_nMDay);
	DDX_Control(pDX, IDC_EDIT_YearsJump, m_edtYearsJump);
	DDX_Control(pDX, IDC_BUTTON_MIN, m_btnMin);
	DDX_Control(pDX, IDC_BUTTON_PLUS, m_btnPlus);
}


BEGIN_MESSAGE_MAP(CCaliderDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_MIN, OnBnClickedButtonMin)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, OnBnClickedButtonPlus)
	ON_EN_CHANGE(IDC_EDIT_YearsJump, OnEnChangeEditYearsjump)
END_MESSAGE_MAP()


// CCaliderDlg message handlers

void CCaliderDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//OnOK();
}

void CCaliderDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//OnCancel();
}


/*	UpdateData();
	if(m_nElef == 0 && m_nMeha == 0 && m_nEser == 0)
	{
		m_ctrlEser.SetPos(1);
	}
*/

BOOL CCaliderDlg::Create(CWnd* pWnd)
{
	m_pWnd = pWnd;
	return CDialog::Create(CCaliderDlg::IDD);
}

BOOL CCaliderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_edtYearsJump.SetWindowText("1");
	// TODO:  Add extra initialization here
	// TBS_DOWNISLEFT GWL_STYLE
	m_ctrlElef.SetRange(0, 6);
	m_ctrlElef.SetLineSize(1);

	m_ctrlMeha.SetRange(0, 9);
	m_ctrlMeha.SetLineSize(1);

	m_ctrlEser.SetRange(0, 9);
	m_ctrlEser.SetLineSize(1);

	m_ctrlEhad.SetRange(0, 9);
	m_ctrlEhad.SetLineSize(1);

	m_ctrlEhad.SetPos(1);

	m_ctrlMonths.SetRange(1, 12);
	m_ctrlMonths.SetLineSize(1);

	m_ctrlMDay.SetRange(1, 30);
	m_ctrlMDay.SetLineSize(1);

	CClientDC dc(this);
	COLORREF col = RGB(0,0,0);//RGB(64,64,255);
	m_yearsBm.CreateMyCompatibleBitmap(&dc, cal_cx, cal_cy, col);
	CMyFont font;
	font.Create(col,16777215);


	const int r = cal_cx - 5;
	const int py = 32;
	int y = 23;


	m_ctrlYArr.Add(y);
	char shnim[5] = {(char)237,(char)233,(char)240,(char)249,0};
	CString str= shnim;
	CDC* bmDC = m_yearsBm.GetMyPaintDC();
	int raligain = r - str.GetLength() * 9;//(cal_cx - str.GetLength() * 9) / 2;
	font.DrawString(bmDC,raligain,y, str);

    y += py / 2 + 5;
	m_ctrlYArr.Add(y);
	char alafim[6] = {(char)237,(char)233,(char)244,(char)236,(char)224,0};
	str = alafim;
	raligain = r - str.GetLength() * 9;
	font.DrawString(bmDC,raligain,y, str);

	y += py;
	m_ctrlYArr.Add(y);
	char meot[5] = {(char)250,(char)229,(char)224,(char)238,0};
	str = meot;
	raligain = r - str.GetLength() * 9;
	font.DrawString(bmDC,raligain,y, str);

	y += py;
	m_ctrlYArr.Add(y);
	char asaron[6] = {(char)250,(char)229,(char)248,(char)249,(char)242,0};
	str = asaron;
	raligain = r - str.GetLength() * 9;
	font.DrawString(bmDC,raligain,y, str);

	y += py;
	m_ctrlYArr.Add(y);
	char yhidot[7] = {250,229,227,233,231,233,0};
	str = yhidot;
	raligain = r - str.GetLength() * 9;
	font.DrawString(bmDC,raligain,y, str);
	m_shnimLeft = raligain - 8;

	y += py + 1;
	m_ctrlYArr.Add(y + 7);
	CPen pen(PS_SOLID,2, RGB(255, 255, 255));
	CPen* oldPen = bmDC->SelectObject(&pen);
	bmDC->MoveTo(3,m_ctrlYArr[0] - 3);
	bmDC->LineTo(cal_cx - 3, m_ctrlYArr[0] - 3);
	bmDC->LineTo(cal_cx - 3, y);
	bmDC->LineTo(3, y);
	bmDC->LineTo(3, m_ctrlYArr[0] - 3);
	bmDC->SelectObject(oldPen);

	m_dateFont.Create(RGB(240,15,116));
	BuildMonthRects();

	y = m_monthsRc.bottom + 5;
	m_ctrlYArr.Add(y);

	BuildMDaysRcsAndBms();

	UpdateData();
	PaintDate();
	PaintMonth();
	PaintMonthDays();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CCaliderDlg::SetResultWnd(CWnd* pWnd)
{
	m_pWnd = pWnd;
}

void CCaliderDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if(nSBCode == SB_ENDSCROLL /*|| nSBCode == SB_THUMBTRACK */
		|| nSBCode == SB_THUMBPOSITION )
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
		return;
	}

	if(pScrollBar->GetSafeHwnd() == m_ctrlMDay.GetSafeHwnd())
	{
		int pos = m_ctrlMDay.GetPos();
		if(pos == 1)
		{
			CDaysPast dp(m_nYears, m_nMonths, m_nMDay);
			CYMDs newDp = dp - (long)1;
			SetDate(newDp);
			CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
			return;
		}
		else if(m_ctrlMDay.GetRangeMax() == pos)
		{
			CDaysPast dp(m_nYears, m_nMonths, m_nMDay);
			CYMDs newDp = dp + (long)1;
			SetDate(newDp);
			CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
			return;
		}
	}
	else if(pScrollBar->GetSafeHwnd() == m_ctrlMonths.GetSafeHwnd())
	{
		int pos = m_ctrlMonths.GetPos();
		if(pos == 1)
		{
			CDaysPast dp(m_nYears, m_nMonths , m_nMDay);
			CYMDs newDp = dp - (long)29;
			SetDate(newDp);
			CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
			return;
		}
		else if(m_ctrlMonths.GetRangeMax() == pos)
		{
			CDaysPast dp(m_nYears, m_nMonths , m_nMDay);
			CYMDs newDp = dp + (long)29;
			SetDate(newDp);
			CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
			return;
		}
	}
	else if(pScrollBar->GetSafeHwnd() == m_ctrlEhad.GetSafeHwnd())
	{
		int pos = m_ctrlEhad.GetPos();
		if(pos == 0)
		{
			m_nYears -= 1;
			int nYears = m_nYears;
			m_nElef = nYears / 1000;
			nYears -= m_nElef * 1000;
			m_nMeha = nYears / 100;
			nYears -= m_nMeha * 100;
			m_nEser = nYears / 10;
			nYears -= m_nEser * 10;
			m_nEhad = nYears;
			SetYearsCtrlsPod();
			SetDate();
			CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
			return;
		}
		else if(m_ctrlEhad.GetRangeMax() == pos)
		{
			m_nYears += 1;
			int nYears = m_nYears;
			m_nElef = nYears / 1000;
			nYears -= m_nElef * 1000;
			m_nMeha = nYears / 100;
			nYears -= m_nMeha * 100;
			m_nEser = nYears / 10;
			nYears -= m_nEser * 10;
			m_nEhad = nYears;
			SetYearsCtrlsPod();
			SetDate();
			CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
			return;
		}
	}

	SetDate();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CCaliderDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if(m_ctrlElef.GetSafeHwnd() == NULL)
		return;

	// TODO: Add your message handler code here
	CClientDC dc(this);
	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetWindowExt(cal_cx, cal_cy);
	CRect rc;
	GetClientRect(rc);
	dc.SetViewportExt(cx,cy);
	dc.SetViewportOrg (0,  0) ;

	InvalidateRect(rc);

	CRect rc2;
	int r = m_shnimLeft - 5;
	int y = m_ctrlYArr[0];
	rc2.SetRect(5, y + 1, 20, y + 16);
	dc.LPtoDP(rc2);
	m_btnMin.MoveWindow(rc2);

	rc2.SetRect(m_shnimLeft - 15, y + 1, m_shnimLeft, y + 16);
	dc.LPtoDP(rc2);
	m_btnPlus.MoveWindow(rc2);

	rc2.SetRect(30, y, m_shnimLeft - 25, y + 16);
	dc.LPtoDP(rc2);
	m_edtYearsJump.MoveWindow(rc2);

	y = m_ctrlYArr[1];
	rc2.SetRect(5, y, m_shnimLeft, y + cal_ply);
	dc.LPtoDP(rc2);
	m_ctrlElef.MoveWindow(rc2);

	y = m_ctrlYArr[2];
	rc2.SetRect(5, y, m_shnimLeft, y + cal_ply);
	dc.LPtoDP(rc2);
	m_ctrlMeha.MoveWindow(rc2);

	y = m_ctrlYArr[3];
	rc2.SetRect(5, y, m_shnimLeft, y + cal_ply);
	dc.LPtoDP(rc2);
	m_ctrlEser.MoveWindow(rc2);

	y = m_ctrlYArr[4];
	rc2.SetRect(5, y, m_shnimLeft, y + cal_ply);
	dc.LPtoDP(rc2);
	m_ctrlEhad.MoveWindow(rc2);

	y = m_ctrlYArr[5];
	rc2.SetRect(7, y, cal_cx - 7, y + cal_ply);
	dc.LPtoDP(rc2);
	m_ctrlMonths.MoveWindow(rc2);

	y = m_ctrlYArr[6];
	rc2.SetRect(7, y, cal_cx - 7, y + cal_ply);
	dc.LPtoDP(rc2);
	m_ctrlMDay.MoveWindow(rc2);
}

void CCaliderDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetWindowExt(cal_cx, cal_cy);
	CRect rc;
	GetClientRect(rc);
	int cx = rc.Width();//pDC->GetDeviceCaps(LOGPIXELSX);
	int cy = rc.Height();//pDC->GetDeviceCaps(LOGPIXELSY);
	dc.SetViewportExt(cx,cy);
	dc.SetViewportOrg (0,  0) ;
	dc.SetStretchBltMode(HALFTONE);

	m_yearsBm.Draw(&dc, 0, 0);
}

CString CCaliderDlg::BuildDateStr(void)
{
	char letter[23] = 
	{224,225,226,227,228,229,
	230,231,232,233,235,236,238,240,241,242,244,
	246,247,248,249,250,0};
	CString str;

	switch(m_nElef)
	{
	case 0:
		str += " ";
		break;
	case 1:
		str += letter[0];
		break;
	case 2:
		str += letter[1];
		break;
	case 3:
		str += letter[2];
		break;
	case 4:
		str += letter[3];
		break;
	case 5:
		str += letter[4];
		break;
	case 6:
		str += letter[5];
		break;
	}
	str += " ";

	int hundreds = 18;
	switch(m_nMeha)
	{
	case 4:
		hundreds++;
	case 3:
		hundreds++;
	case 2:
		hundreds++;
	case 1:
		str += letter[hundreds];
		break;
	case 8:
		hundreds++;
	case 7:
		hundreds++;
	case 6:
		hundreds++;
	case 5:
		str += letter[21];
		str += letter[hundreds];
		break;
	case 9:
		str += letter[21];
		str += letter[21];
		str += letter[hundreds];
		break;
	}

	int eser = 10;
	switch(m_nEser)
	{
	case 9:
		eser++;
	case 8:
		eser++;
	case 7:
		eser++;
	case 6:
		eser++;
	case 5:
		eser++;
	case 4:
		eser++;
	case 3:
		eser++;
	case 2:
		str += letter[eser];
		break;
	case 1:
		if(m_nEhad == 5 || m_nEhad == 6)
		{
			str += letter[eser - 2];
			str += letter[m_nEhad];
			break;
		}
		eser--;
		str += letter[eser];
		break;
	}

	int ahadim = 0;
	switch(m_nEhad)
	{
		break;
	case 9:
		ahadim++;
	case 8:
		ahadim++;
	case 7:
		ahadim++;
	case 6:
		ahadim++;
	case 5:
		if(m_nEser == 1 && ahadim < 2)
			break;
		ahadim++;
	case 4:
		ahadim++;
	case 3:
		ahadim++;
	case 2:
		ahadim++;
	case 1:
		str += letter[ahadim];
		break;
	}

	int size = 8 - str.GetLength();
	for(int i = 0; i < size; i++)
		str += " ";
	str = str.MakeReverse();

	CString months = GetMonthStr(m_nMonths, m_bLeap);
	size = 5 - months.GetLength();
	for(int i = 0; i < size; i++)
		months += " ";

	str = CString("  ") + months + str;

	CString mdays;
	mdays += GetMDayStr(m_nMDay);
	size = 2 - mdays.GetLength();
	for(int i = 0; i < size; i++)
		mdays += " ";

	str =  CString("   ") + mdays + str;

	return str;
}

void CCaliderDlg::PaintDate(void)
{
	CString str = BuildDateStr();
	int r = cal_cx - 5;
	int strLength = str.GetLength() * 9;
	int raligain = r - strLength;

	m_dateFont.DrawString(m_yearsBm,raligain,3, str);
	CClientDC dc(this);
	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetWindowExt(cal_cx, cal_cy);
	CRect rc4;
	GetClientRect(rc4);
	dc.SetViewportExt(rc4.Width(),rc4.Height());
	dc.SetViewportOrg (0,  0) ;
	dc.SetStretchBltMode(HALFTONE);

	dc.BitBlt(raligain, 3, strLength, 14, m_yearsBm,raligain, 3,
		SRCCOPY);

}

// idx from 1 to 13
CString CCaliderDlg::GetMonthStr(int idx, bool bLeap)
{
	if(idx == 0 || (bLeap == false && idx == 13))
		return "";

	CString str;
	char tishray[5] = {233,248,249,250,0};
	char heshvan[5] = {239,229,249,231,0};
	char kislev[5] = {229,236,241,235,0};
	char tevet[4] = {250,225,232,0};
	char shvat[4] = {232,225,249,0};
	char adar[4] = {248,227,224,0};
	char adar1[6] = {224,32,248,227,224,0};
	char adar2[6] = {225,32,248,227,224,0};
	char nisan[5] = {239,241,233,240,0};
	char iyar[5] = {248,233,233,224,0};
	char sivan[5] = {239,229,233,241,0};
	char tamoz[5] = {230,229,238,250,0};
	char av[3] = {225,224,0};
	char elul[5] = {236,229,236,224,0};

	char *mon[9] = {adar, adar1, adar2, nisan, iyar, sivan,
	tamoz, av, elul};

	int nAdd = (bLeap == false)? 0:1;
	int newIdx = idx - nAdd - 4;
	switch(idx)
	{
	case 1:
		str = tishray;
		break;
	case 2:
		str = heshvan;
		break;
	case 3:
		str = kislev;
		break;
	case 4:
		str = tevet;
		break;
	case 5:
		str = shvat;
		break;
	case 6:
		str = mon[nAdd];
		break;
	case 7:
		str = mon[newIdx];
		break;
	case 8:
		str = mon[newIdx];
		break;
	case 9:
		str = mon[newIdx];
		break;
	case 10:
		str = mon[newIdx];
		break;
	case 11:
		str = mon[newIdx];
		break;
	case 12:
		str = mon[newIdx];
		break;
	case 13:
		str = mon[newIdx];
		break;
	}

	return str;
}

void CCaliderDlg::BuildMonthRects(void)
{
	int y = m_ctrlYArr[5] + cal_ply + 10;
	int space = 5;
	int width = 44;
	int height = 13;
	int sides = (cal_cx - (space * 2 + width * 3 + 6)) / 2;
	int right = cal_cx - sides;
	CRect xRc(right - width, y, right, y + height);
	CRect moveRc;
	CPoint movex(-width - space, 0);
	CPoint movey(0, height + space);

	for(int ym = 0; ym < 4; ym++, xRc += movey)
	{
		moveRc = xRc;
		for(int xm = 0; xm < 3; xm++, moveRc += movex)
		{
			m_mothsRcArr.Add(moveRc);
		}
	}
	moveRc = xRc;
	moveRc += movex;
	m_mothsRcArr.Add(moveRc);

    CPoint cp(-sides, -y +1);

	m_monthsRc.SetRect(m_mothsRcArr[2].left, m_mothsRcArr[0].top,
		m_mothsRcArr[0].right, m_mothsRcArr[12].bottom);
	m_monthsRc.InflateRect(5,6);
	CClientDC dc(this);
	COLORREF col = RGB(64,64,255);
	m_normalMonthsBm.CreateMyCompatibleBitmap(&dc,
		 m_monthsRc.Width(), m_monthsRc.Height(), col);
	m_leapMonthsBm.CreateMyCompatibleBitmap(&dc,
		 m_monthsRc.Width(), m_monthsRc.Height(), col);
	CMyFont font;
	font.Create(RGB(32,32,192),16777215);

	CDC* bmDC = m_normalMonthsBm.GetMyPaintDC();
	CString str;
	int size;
	for(int i = 1; i <= 12; i++)
	{
		str = GetMonthStr(i, false);
		size = 5 - str.GetLength();
		for(int j = 0; j < size; j++)
			str += " ";
		moveRc = m_mothsRcArr[i - 1];
		moveRc += cp;
		font.DrawString(bmDC,moveRc.left,moveRc.top, str);
	}

	bmDC = m_leapMonthsBm.GetMyPaintDC();
	for(int i = 1; i <= 13; i++)
	{
		str = GetMonthStr(i, true);
		size = 5 - str.GetLength();
		for(int j = 0; j < size; j++)
			str += " ";
		moveRc = m_mothsRcArr[i - 1];
		moveRc += cp;
		font.DrawString(bmDC,moveRc.left,moveRc.top, str);
	}
}

void CCaliderDlg::PaintMonth(void)
{
	CDC* yearDC = m_yearsBm.operator CDC *();
	CClientDC dc(this);
	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetWindowExt(cal_cx, cal_cy);
	CRect rc4;
	GetClientRect(rc4);
	dc.SetViewportExt(rc4.Width(),rc4.Height());
	dc.SetViewportOrg (0,  0) ;
	dc.SetStretchBltMode(HALFTONE);

	int left = -3;
	CRect rc3 = m_monthsRc;
	if(m_bLeap == true)
	{
		yearDC->BitBlt(rc3.left + left, rc3.top,
			rc3.Width(), rc3.Height()
			,m_leapMonthsBm, 0, 0, SRCCOPY);		
	}
	else
	{
		yearDC->BitBlt(rc3.left + left, rc3.top,
			rc3.Width(), rc3.Height()
			,m_normalMonthsBm, 0, 0, SRCCOPY);
	}
	int pos = m_ctrlMonths.GetPos();
	CRect rc = m_mothsRcArr[pos - 1];
	rc.InflateRect(1,1);
	rc += CPoint(2 + left, -4);
	CPen pen(PS_SOLID,2, RGB(255, 0, 0));
	CPen* oldPen = yearDC->SelectObject(&pen);
	yearDC->MoveTo(rc.left, rc.top);
	yearDC->LineTo(rc.right, rc.top);
	yearDC->LineTo(rc.right, rc.bottom);
	yearDC->LineTo(rc.left, rc.bottom);
	yearDC->LineTo(rc.left, rc.top);
	yearDC->SelectObject(oldPen);

	dc.BitBlt(rc3.left, rc3.top, rc3.Width(), 
		rc3.Height(), yearDC, rc3.left, rc3.top, SRCCOPY);
}

void CCaliderDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetWindowExt(cal_cx, cal_cy);
	CRect rc4;
	GetClientRect(rc4);
	dc.SetViewportExt(rc4.Width(),rc4.Height());
	dc.SetViewportOrg (0,  0) ;
	dc.DPtoLP(&point);

	int size = (m_bLeap == false)? 12:13;
	int i = 0;
	for(i = 0; i < size; i++)
	{
		CRect r = m_mothsRcArr[i];
		r.InflateRect(1,1);
		r += CPoint(2, -4);
		if(r.PtInRect(point))
			break;
	}

	if(i < size)
	{
		m_nMonths = i + 1;
		CMollad mol(m_nYears, m_nMonths);
		m_daysInMonth = mol.DaysInMonth();
		m_ctrlMDay.SetRange(1, m_daysInMonth, TRUE);
		if(m_daysInMonth < m_nMDay)
		{
			m_nMDay = m_daysInMonth;
			m_ctrlMDay.SetPos(m_nMDay);
		}
		m_ctrlMonths.SetPos(m_nMonths);
		//UpdateData(FALSE);
		PaintDate();
		PaintMonth();
		m_ctrlMonths.SetFocus();

		PaintMonthDays();
		CDaysPast dp(m_nYears, m_nMonths, m_nMDay);
		m_result.id = 0;
		m_result.result = (long)dp;
		m_result.val = ((CYMDs)dp).Years;
		if(m_pWnd)
			m_pWnd->PostMessage(BASIC_DLL_MSG, COMTOV_RESULT, (LPARAM)&m_result);
		CDialog::OnLButtonDown(nFlags, point);
		return;
	}

	for(i = 0; i < m_daysInMonth; i++)
	{
		CRect r = m_mothDsRcArr[i];
		r.InflateRect(1,1);
		r += CPoint(m_shiftDays, 0);
		if(r.PtInRect(point))
			break;	
	}

	if(i < m_daysInMonth)
	{
		m_nMDay = i + 1;
		m_ctrlMDay.SetPos(m_nMDay);
		/*UpdateData(FALSE);*/
		PaintDate();
		PaintMonthDays();
		m_ctrlMDay.SetFocus();
		CDaysPast dp(m_nYears, m_nMonths, m_nMDay);
		m_result.id = 0;
		m_result.result = (long)dp;
		m_result.val = ((CYMDs)dp).Years;		
		if(m_pWnd)
			m_pWnd->PostMessage(BASIC_DLL_MSG, COMTOV_RESULT, (LPARAM)&m_result);
	}

	CDialog::OnLButtonDown(nFlags, point);
}

CString CCaliderDlg::GetMDayStr(int day)
{
	if(day < 1 || day > 30)
		return "";
	char letter[13] = 
	{224,225,226,227,228,229,
	230,231,232,233,235,236,0};

	CString str;
	int asarot = day / 10;
	int yamim = day % 10;

	if(asarot == 1 && (yamim == 5 || yamim == 6))
	{
		str += letter[yamim];
		str += letter[8];
		return str;
	}

	if(yamim)
	{
		str += letter[yamim - 1];
	}

	if(asarot)
	{
		str += letter[8 + asarot];
	}
	

	return str;

}

void CCaliderDlg::BuildMDaysRcsAndBms(void)
{
	int y = m_ctrlYArr[6] + cal_ply + 5;
	int bmWidth = cal_cx - 10;
	int space = 5;
	int width = 14;
	int height = 10;
	int sides = (bmWidth - (space * 8 + width * 9)) / 2;
	int right = bmWidth - sides;
	int left = (cal_cx - bmWidth) / 2;

	CRect xRc(right - width, y + space, right, y + space + height);
	CRect moveRc;
	CPoint movex(-width - space, 0);
	CPoint movey(0, height + space);

	for(int ym = 0, pos = 0; ym < 4; ym++, xRc += movey)
	{
		moveRc = xRc;
		for(int xm = 0; xm < 8 && pos < 30; xm++, moveRc += movex, pos++)
		{
			m_mothDsRcArr.Add(moveRc);
		}
	}

	m_monthDRc.SetRect(left, y,
		space + bmWidth, m_mothDsRcArr[29].bottom + space);

	CClientDC dc(this);
	COLORREF col = RGB(64,64,255);
	m_MonthHaserBm.CreateMyCompatibleBitmap(&dc,
		 m_monthsRc.Width(), m_monthsRc.Height(), col);
	m_MonthMalleBm.CreateMyCompatibleBitmap(&dc,
		 m_monthsRc.Width(), m_monthsRc.Height(), col);
	CMyFont font;
	font.Create(RGB(32,32,192),16777215, TRUE);

	CPoint fi(-24, -y);
	CDC* bmDC = m_MonthHaserBm.GetMyPaintDC();
	CString str;
	int size;
	for(int i = 1; i <= 29; i++)
	{
		str = GetMDayStr(i);
		size = str.GetLength();
		if(size == 1)
			str += " ";
		moveRc = m_mothDsRcArr[i - 1];
		moveRc += fi;
		font.DrawString(bmDC,moveRc.left,moveRc.top, str);
	}

	bmDC = m_MonthMalleBm.GetMyPaintDC();
	for(int i = 1; i <= 30; i++)
	{
		str = GetMDayStr(i);
		size = str.GetLength();
		if(size == 1)
			str += " ";
		moveRc = m_mothDsRcArr[i - 1];
		moveRc += fi;
		font.DrawString(bmDC,moveRc.left,moveRc.top, str);
	}

	CPoint p(- 18, 0);
	CRect *prc = m_mothDsRcArr.GetData();
	for(int i = 0; i < 30; i++, prc++)
		*prc += p;
}

void CCaliderDlg::PaintMonthDays(void)
{
	CDC* yearDC = m_yearsBm.operator CDC *();
	CClientDC dc(this);
	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetWindowExt(cal_cx, cal_cy);
	CRect rc4;
	GetClientRect(rc4);
	dc.SetViewportExt(rc4.Width(),rc4.Height());
	dc.SetViewportOrg (0,  0) ;
	dc.SetStretchBltMode(HALFTONE);

	m_shiftDays = 15;

	CRect rc3 = m_monthDRc;
	if(m_daysInMonth == 29)
	{
		yearDC->BitBlt(rc3.left + m_shiftDays, rc3.top,
			rc3.Width(), rc3.Height()
			,m_MonthHaserBm, 0, 0, SRCCOPY);		
	}
	else
	{
		yearDC->BitBlt(rc3.left + m_shiftDays, rc3.top,
			rc3.Width(), rc3.Height()
			,m_MonthMalleBm, 0, 0, SRCCOPY);
	}

	int pos = m_ctrlMDay.GetPos();
	CRect rc = m_mothDsRcArr[pos - 1];
	rc.InflateRect(1,1);
	rc += CPoint(m_shiftDays,0);
	CPen pen(PS_SOLID,2, RGB(255, 0, 0));
	CPen* oldPen = yearDC->SelectObject(&pen);
	yearDC->MoveTo(rc.left, rc.top);
	yearDC->LineTo(rc.right, rc.top);
	yearDC->LineTo(rc.right, rc.bottom);
	yearDC->LineTo(rc.left, rc.bottom);
	yearDC->LineTo(rc.left, rc.top);
	yearDC->SelectObject(oldPen);


	dc.BitBlt(rc3.left, rc3.top, rc3.Width(), 
		rc3.Height(), yearDC, rc3.left, rc3.top, SRCCOPY);
}

void CCaliderDlg::OnBnClickedButtonMin()
{
	// TODO: Add your control notification handler code here
	if(m_nYears <= m_nYearsJump)
		return;
	m_nYears -= m_nYearsJump;
	int nYears = m_nYears;
	m_nElef = nYears / 1000;
	nYears -= m_nElef * 1000;
	m_nMeha = nYears / 100;
	nYears -= m_nMeha * 100;
	m_nEser = nYears / 10;
	nYears -= m_nEser * 10;
	m_nEhad = nYears;
//	UpdateData(FALSE);
	SetYearsCtrlsPod();
	SetDate();
}

void CCaliderDlg::OnBnClickedButtonPlus()
{
	// TODO: Add your control notification handler code here
	if(m_nYears + m_nYearsJump >= 7000)
		return;
	m_nYears += m_nYearsJump;
	int nYears = m_nYears;
	m_nElef = nYears / 1000;
	nYears -= m_nElef * 1000;
	m_nMeha = nYears / 100;
	nYears -= m_nMeha * 100;
	m_nEser = nYears / 10;
	nYears -= m_nEser * 10;
	m_nEhad = nYears;
	//UpdateData(FALSE);
	SetYearsCtrlsPod();
	SetDate();
}

void CCaliderDlg::OnEnChangeEditYearsjump()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	CString txt;
	m_edtYearsJump.GetWindowText(txt);
	if(txt == "" || txt == "0")
	{
		txt = "1";
		m_edtYearsJump.SetWindowText(txt);
	}
	sscanf_s(txt, "%d", &m_nYearsJump);
}

void CCaliderDlg::SetDate(void)
{
	UpdateData();
	if(m_nElef == 0 && m_nMeha == 0 && m_nEser == 0 &&
		m_nEhad == 0)
	{
		m_nEhad = 1;
		m_ctrlEhad.SetPos(m_nEhad);
		//UpdateData(FALSE);
	}

	m_nYears = m_nElef * 1000 + m_nMeha * 100 + 
		m_nEser * 10 + m_nEhad;
	CYearTypesAndCycles ytac(m_nYears);
	m_bLeap = ytac.IsLeapYear();

	if(m_bLeap == true)
	{
		m_ctrlMonths.SetRange(1, 13, TRUE);
	}
	else
	{
		m_ctrlMonths.SetRange(1, 12, TRUE);
	}

    CMollad mol(m_nYears, m_ctrlMonths.GetPos());
	m_daysInMonth = mol.DaysInMonth();
	if(m_daysInMonth < m_nMDay)
	{
		m_nMDay = m_daysInMonth;
		m_ctrlMDay.SetPos(m_nMDay);
		//UpdateData(FALSE);
	}
	m_ctrlMDay.SetRange(1, m_daysInMonth, TRUE);

	UpdateData();
	PaintDate();
	PaintMonth();
	PaintMonthDays();

	CDaysPast dp(m_nYears, m_nMonths, m_nMDay);
	m_result.id = 0;
	m_result.result = (long)dp;
	m_result.val = ((CYMDs)dp).Years;
	if(m_pWnd)
		m_pWnd->PostMessage(BASIC_DLL_MSG, COMTOV_RESULT, (LPARAM)&m_result);
}

void CCaliderDlg::SetYearsCtrlsPod(void)
{
	m_ctrlElef.SetPos(m_nElef);
	m_ctrlMeha.SetPos(m_nMeha);
	m_ctrlEser.SetPos(m_nEser);
	m_ctrlEhad.SetPos(m_nEhad);
}

void CCaliderDlg::SetDate(CYMDs date)
{
	if(date.Years >= 7000 || date.Months == 0 || date.Months > 13)
		return;
	m_nYears = date.Years;
	int nYears = m_nYears;
	m_nElef = nYears / 1000;
	nYears -= m_nElef * 1000;
	m_nMeha = nYears / 100;
	nYears -= m_nMeha * 100;
	m_nEser = nYears / 10;
	nYears -= m_nEser * 10;
	m_nEhad = nYears;

	m_nMonths = date.Months;
	m_ctrlMonths.SetPos(m_nMonths);
	m_nMDay = date.MDays;
	m_ctrlMDay.SetPos(m_nMDay);
	SetYearsCtrlsPod();
	SetDate();

}
