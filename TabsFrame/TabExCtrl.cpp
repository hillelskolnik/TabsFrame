// TabExCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "TabExCtrl.h"


// CTabExCtrl

IMPLEMENT_DYNAMIC(CTabExCtrl, CTabCtrl)

CTabExCtrl::CTabExCtrl()
{

}

CTabExCtrl::~CTabExCtrl()
{
}


BEGIN_MESSAGE_MAP(CTabExCtrl, CTabCtrl)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CTabExCtrl message handlers



BOOL CTabExCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= TCS_OWNERDRAWFIXED;

	return CTabCtrl::PreCreateWindow(cs);
}

void CTabExCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CRect rect = lpDrawItemStruct->rcItem;
	rect.NormalizeRect();
	int nTabIndex = lpDrawItemStruct->itemID;
	if (nTabIndex < 0) 
		return;
	BOOL bSelected = (nTabIndex == GetCurSel());

	CString label;
	TC_ITEM tci;
	tci.mask = TCIF_TEXT|TCIF_IMAGE | TCIF_PARAM;
	tci.pszText = label.GetBuffer(64);
	tci.cchTextMax = 63;
	if (!GetItem(nTabIndex, &tci )) 
		return;
	label.ReleaseBuffer();

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	if (!pDC) 
		return;
	int nSavedDC = pDC->SaveDC();

	// For some bizarre reason the rcItem you get extends above the actual
	// drawing area. We have to workaround this "feature".
	rect.top += ::GetSystemMetrics(SM_CYEDGE);

	pDC->SetBkMode(TRANSPARENT);
	//pDC->FillSolidRect(rect, ::GetSysColor(COLOR_BTNFACE));
	RectPaint(rect, pDC, RGB(192,192,192), RGB(222,222,255));

	// Draw image
	CImageList* pImageList = GetImageList();
	if (pImageList && tci.iImage >= 0) {

		rect.left += pDC->GetTextExtent(_T(" ")).cx;		// Margin

		// Get height of image so we 
		IMAGEINFO info;
		pImageList->GetImageInfo(tci.iImage, &info);
		CRect ImageRect(info.rcImage);
		int nYpos = rect.top;

		pImageList->Draw(pDC, tci.iImage, CPoint(rect.left, nYpos), ILD_TRANSPARENT);
		rect.left += ImageRect.Width();
	}

	if (bSelected) {
		//pDC->SetTextColor(m_crSelColour);
		pDC->SelectObject(&m_font);
		rect.top -= ::GetSystemMetrics(SM_CYEDGE);
		pDC->DrawText(label, rect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	} else {
		//pDC->SetTextColor(m_crUnselColour);
		pDC->SelectObject(&m_font);
		pDC->DrawText(label, rect, DT_SINGLELINE|DT_BOTTOM|DT_CENTER);
	}

	pDC->RestoreDC(nSavedDC);
}

int CTabExCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	ModifyStyle(0,TCS_OWNERDRAWFIXED);

	VERIFY(m_font.CreateFont(
		-15,                     // nHeight
		0,                       // nWidth
		0,                       // nEscapement
		0,                       // nOrientation
		FW_NORMAL,               // nWeight
		FALSE,                   // bItalic
		FALSE,                   // bUnderline
		0,                       // cStrikeOut
		HEBREW_CHARSET,          // nCharSet
		OUT_DEFAULT_PRECIS,      // nOutPrecision
		CLIP_DEFAULT_PRECIS,     // nClipPrecision
		DEFAULT_QUALITY,         // nQuality
		DEFAULT_PITCH | FF_SWISS,// nPitchAndFamily
		"Guttman Stam"));        // lpszFacename

	return 0;
}

BOOL CTabExCtrl::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	GetClientRect(rc);

	RectPaint(rc,pDC);
	return TRUE;

	return CTabCtrl::OnEraseBkgnd(pDC);
}
