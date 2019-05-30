// MsgView.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "MsgView.h"


// CMsgView

IMPLEMENT_DYNCREATE(CMsgView, CView)

CMsgView::CMsgView()
{
	SetFonts();
}

CMsgView::~CMsgView()
{
}

BEGIN_MESSAGE_MAP(CMsgView, CView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CMsgView drawing

void CMsgView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CMsgView diagnostics

#ifdef _DEBUG
void CMsgView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMsgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMsgView message handlers

BOOL CMsgView::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	GetClientRect(rc);
	pDC->PatBlt(0,0,rc.Width(), rc.Height(), BLACKNESS); 

	return TRUE;

	return CView::OnEraseBkgnd(pDC);
}

void CMsgView::SetFonts()
{
		VERIFY(m_fontHe.CreateFont(
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

		VERIFY(m_fontEn.CreateFont(
			-20,                     // nHeight
			0,                       // nWidth
			0,                       // nEscapement
			0,                       // nOrientation
			FW_SEMIBOLD,               // nWeight
			FALSE,                   // bItalic
			FALSE,                   // bUnderline
			0,                       // cStrikeOut
			ANSI_CHARSET,          // nCharSet
			OUT_CHARACTER_PRECIS,      // nOutPrecision
			CLIP_CHARACTER_PRECIS,     // nClipPrecision
			PROOF_QUALITY,         // nQuality
			DEFAULT_PITCH | FF_SWISS,// nPitchAndFamily
			"Guttman Miryam Bold"));        // lpszFacename
}
