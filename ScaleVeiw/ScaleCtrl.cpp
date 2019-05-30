// ScaleCtrl.cpp: implementation of the CScaleCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ScaleVeiw.h"
#include "ScaleCtrl.h"
#include ".\scalectrl.h"
//#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScaleCtrl::CScaleCtrl(HWND wnd)
:m_oldBitmap(NULL),m_memBitmap(NULL),
m_oldBrush(NULL),m_bDown(false), 
//m_raddeg(asin(1.0) / 90.0),
//m_todeg(90.0 / asin(1.0)),
m_bIsHand(false)
,m_oldLineRc(0,0,0,0)
,m_textRc(0,0,0,0)
{
	m_wnd.Attach(wnd);
	CClientDC dc(&m_wnd);
	m_memDc.CreateCompatibleDC(&dc);
}

CScaleCtrl::~CScaleCtrl()
{
	m_wnd.Detach();
	m_memDc.SelectObject(m_oldBitmap);
	delete m_memBitmap;

}

unsigned __stdcall CScaleCtrl::RunCtrl(LPVOID lpVoid)
{
	CScaleCtrl a((HWND)lpVoid);
	a.CtrlLoop();

	return 0;
}

void CScaleCtrl::CtrlLoop()
{
	BOOL bRet;

	MSG msg;

	PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);

	CString str;
	str.Format("GetCurrentThreadId(%d)", GetCurrentThreadId());
	HANDLE hEv = CreateEvent(NULL, TRUE, FALSE, str);
    SetEvent(hEv);
	
	while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
	{
		if(bRet == -1)
		{
			return;
		}
		else
		{
			switch(msg.message)
			{
			case VTOCOM_INIT:
				{
					CInit *pinit = (CInit*)msg.wParam;
					m_init = *pinit;
					m_result.id = m_init.id;
					CreateBm();
					CloseHandle(hEv);
					delete pinit;
				}
				break;
			case VTOCOM_LDWN:
				m_bDown = true;
				MoseMove(*(CPoint*)msg.wParam);
				break;
			case VTOCOM_LUP:
				m_bDown = false;
				break;
			case VTOCOM_MM:
				MoseMove(*(CPoint*)msg.wParam);
				break;
			case VTOCOM_DRAW:
				PaintScreen();
				break;
			}
		}
	}
}

void CScaleCtrl::CreateBm()
{
	if(m_memBitmap)
	{
		m_oldBitmap = m_memDc.SelectObject(m_memBitmap);
		delete m_memBitmap;
	}

	m_memBitmap = new CBitmap;
	CClientDC dc(&m_wnd);
	m_memBitmap->CreateCompatibleBitmap(&dc,m_init.rc.Width(), m_init.rc.Height());
	m_oldBitmap = m_memDc.SelectObject(m_memBitmap);
	CBrush br(m_init.brCol);
	CPen pn(m_init.pnStyle, m_init.pnWidth, m_init.pnCol);
	m_memDc.SelectObject(&pn);
	m_oldBrush = m_memDc.SelectObject(&br);
	m_memDc.PatBlt(0, 0, m_init.rc.Width(), m_init.rc.Height(), PATCOPY);
	CRect rc(0,0, m_init.rc.Width(), m_init.rc.Height());
	rc.DeflateRect(m_init.deflate, m_init.deflate);
	CPoint cpt = rc.CenterPoint();
	m_memDc.Ellipse(rc);
	m_memDc.MoveTo(cpt);
	CPoint pt = StartPoint();
	m_memDc.LineTo(pt);
	m_oldLineRc.SetRect(cpt,pt);
	CreateRgn();

	CBrush rgnbr(m_init.rgnCol);
	CRgn rg;
	rg.CreateRectRgn(0,0,1,1);
	rg.CopyRgn(&m_notRgn);
	rg.OffsetRgn(-m_init.rc.left, -m_init.rc.top);
	m_memDc.FillRgn(&rg, &rgnbr);

	if((m_init.dwFlags & INIT_SPACES))
		DrawSpaces();


	if((m_init.dwFlags & INIT_IMAGE))
	{
		LoadImage();
		DrawImage();
	}

	SetResult(cpt, pt);
	DrawResult();

	
//	PaintScreen();

}

void CScaleCtrl::MoseMove(CPoint pt)
{
	{
		CClientDC dc(&m_wnd);
		dc.SetMapMode(MM_ISOTROPIC);
		dc.SetWindowExt(cs_cx, cs_cy);
		CRect rc;
		m_wnd.GetClientRect(rc);
		int cx = rc.Width();//pDC->GetDeviceCaps(LOGPIXELSX);
		int cy = rc.Height();//pDC->GetDeviceCaps(LOGPIXELSY);
//		TRACE("cx = %d   cy = %d\n", cx,cy);
		dc.SetViewportExt(cx,cy);
		dc.SetViewportOrg (0,  0) ;
		dc.DPtoLP(&pt);
	}
	if(m_init.rc.PtInRect(pt))
	{
		if(m_bIsHand == false)
		{
			m_wnd.SendMessage(BASIC_DLL_MSG, COMTOV_SETCUPTURE);
			m_bIsHand = true;
		}

		if(m_bDown && !m_notRgn.PtInRegion(pt))
		{
			m_memDc.PatBlt(0, 0, m_init.rc.Width(), m_init.rc.Height(), PATCOPY);
			CRect rc(0,0, m_init.rc.Width(), m_init.rc.Height());
			rc.DeflateRect(m_init.deflate, m_init.deflate);
			CPoint cpt = rc.CenterPoint();
			CPoint pt2(pt.x - m_init.rc.left, pt.y - m_init.rc.top);
			m_memDc.Ellipse(rc);
			m_memDc.MoveTo(cpt);
			CPoint pt3 = MakelongLine(pt2);
			m_memDc.LineTo(pt3);
			CRect nrc(cpt,pt3);

			CBrush rgnbr(m_init.rgnCol);
			CRgn rg;
			rg.CreateRectRgn(0,0,1,1);
			rg.CopyRgn(&m_notRgn);
			rg.OffsetRgn(-m_init.rc.left, -m_init.rc.top);
			m_memDc.FillRgn(&rg, &rgnbr);

			if((m_init.dwFlags & INIT_SPACES))
				DrawSpaces();

			if((m_init.dwFlags & INIT_IMAGE))
					DrawImage();

			SetResult(cpt, pt3);
			DrawResult();
			PaintScreen(nrc);
//			PaintScreen();
		}
	}
	else if(m_bIsHand)
	{
		m_wnd.SendMessage(BASIC_DLL_MSG, COMTOV_RELEASECUPTURE);
		m_bIsHand = false;
	}
}

CPoint CScaleCtrl::MakelongLine(CPoint pt)
{
		CRect rc(0,0, m_init.rc.Width(), m_init.rc.Height());
		rc.DeflateRect(m_init.deflate, m_init.deflate);
		CPoint cpt = rc.CenterPoint();
		double cx = (double)pt.x - (double)cpt.x;
		double cy = (double)pt.y - (double)cpt.y;
		double len1 = sqrt(cx*cx + cy*cy);
		double fullLen = ((double)rc.Width() / 2.0);
		double tomul = fullLen/len1;

		return CPoint((int)((double)cx * tomul + (double)cpt.x), 
			(int)((double)cy * tomul + (double)cpt.y));

}

void CScaleCtrl::PaintScreen()
{
	CClientDC dc(&m_wnd);
	{
		dc.SetMapMode(MM_ISOTROPIC);
		dc.SetWindowExt(cs_cx, cs_cy);
		CRect rc;
		m_wnd.GetClientRect(rc);
		int cx = rc.Width();//pDC->GetDeviceCaps(LOGPIXELSX);
		int cy = rc.Height();//pDC->GetDeviceCaps(LOGPIXELSY);
		//TRACE("cx = %d   cy = %d\n", cx,cy);
		dc.SetViewportExt(cx,cy);
		dc.SetViewportOrg (0,  0) ;
	}
	dc.BitBlt(m_init.rc.left,m_init.rc.top,m_init.rc.Width(),
		m_init.rc.Height(),&m_memDc,0,0,SRCCOPY);
}

CPoint CScaleCtrl::StartPoint()
{
	CRect rc(0,0, m_init.rc.Width(), m_init.rc.Height());
	rc.DeflateRect(m_init.deflate, m_init.deflate);
	CPoint cpt = rc.CenterPoint();
	double degperunit = m_init.endang /
		(m_init.maxval - m_init.minval);
	double startang = m_init.startang + 
		(degperunit * (m_init.startval - m_init.minval));
	startang *= g_degtorad;
	double len = (double)rc.Width() / 2.0;
	double cy = sin(startang) * len;
	double cx = cos(startang) * len;

	CPoint stpt(cpt.x + (int)cx, cpt.y - (int)cy);

	return stpt;
}

void CScaleCtrl::SetResult(const CPoint &cpt, const CPoint &pt)
{
	double x = (double)pt.x - (double)cpt.x;
	double y = (double)cpt.y - (double)pt.y;
	double ang = atan2(y,x) * g_radtodeg;
	ang -= m_init.startang;
//	TRACE("ang1 = %lf\n",ang);
	while(ang < 0.0)
		ang += 360;
	double unitperdeg = (m_init.maxval - m_init.minval) / 
		m_init.endang;

	if(ang > m_init.endang)
	{
		if(ang - m_init.endang > 360.0 - ang)
			m_result.result = m_init.minval;
		else
			m_result.result = m_init.maxval;
		return;
	}

	m_result.result = (unitperdeg * ang) + m_init.minval;
	m_wnd.PostMessage(BASIC_DLL_MSG, COMTOV_RESULT,
		(LPARAM)&m_result);

}

void CScaleCtrl::DrawResult()
{
	CString str;
	str.Format("%.1lf", m_result.result);
	CSize textlen = m_memDc.GetTextExtent(str);

	int x = (m_init.rc.Width() - textlen.cx) / 2;
	int y = m_init.rc.Height() - textlen.cy;
	m_memDc.TextOut(x,y - 1,str);

	CPoint tl(m_init.rc.left + x,
		m_init.rc.top + y);
	CPoint br(tl.x + textlen.cx, tl.y + textlen.cy);
	CRect rc1, rc2 = m_textRc;
	rc1.SetRect(tl, br);
	m_textRc.UnionRect(rc1,rc2);
}

void CScaleCtrl::CreateRgn()
{
	PointArr parr;
	CPoint p;
	SetAngPntOnRect(p, m_init.startang);
	parr.Add(p);
	AddRgnCorner(parr);
	SetAngPntOnRect(p, m_init.startang + m_init.endang);
	parr.Add(p);
	p = m_init.rc.CenterPoint();
	parr.Add(p);
	m_notRgn.CreatePolygonRgn(parr.GetData(), parr.GetSize(), ALTERNATE);
}

void CScaleCtrl::SetAngPntOnRect(CPoint &pt, double ang)
{
	while(ang > 360.0)
		ang -= 360.0;

	while(ang < 0.0)
		ang += 360.0;


	double halfWdth = (double)m_init.rc.Width() / 2.0;

	if(ang > 315.0 || (0.0 <= ang && 45.0 >= ang))
	{
		pt.x = m_init.rc.right;
		double cord = tan(ang * g_degtorad) * halfWdth;
		pt.y = -(int)cord + m_init.rc.CenterPoint().y;

	}
	else if(ang > 45.0 && 135.0 >= ang)
	{
		pt.y = m_init.rc.top;
		if(ang > 89.5 && ang < 90.5)
		{
			pt.x = m_init.rc.CenterPoint().x;
			return;
		}
		double cord = (1.0 / tan(ang * g_degtorad)) * halfWdth;
		pt.x = (int)cord + m_init.rc.CenterPoint().x;
	}
	else if(ang > 135.0 && 225.0 >= ang)
	{
		pt.x = m_init.rc.left;
		double cord = tan(ang * g_degtorad) * halfWdth;
		pt.y = (int)cord + m_init.rc.CenterPoint().y;
	}
	else if(ang > 225.0 && 315.0 >= ang)
	{
		pt.y = m_init.rc.bottom;
		if(ang > 269.5 && ang < 270.5)
		{
			pt.x = m_init.rc.CenterPoint().x;
			return;
		}
		double cord = (1.0 / tan(ang * g_degtorad)) * halfWdth;
		pt.x = -(int)cord + m_init.rc.CenterPoint().x;
	}

}

void CScaleCtrl::AddRgnCorner(PointArr &parr)
{
	double len = 360.0 - m_init.endang;

	if(len <= 0.0)
		return;

	double startang = m_init.startang;


	double start = 400.0;

	if(startang > 315.0 || 
		(0.0 <= startang && 45.0 > startang))
	{
		start = 315.0;
		if(0.0 <= startang && 45.0 > startang)
			startang += 360.0;
	}
	else if(startang > 225.0)
	{
		start = 225.0;
	}
	else if(startang > 135.0 )
	{
		start = 135.0;
	}
	else if(startang > 45.0)
	{
		start = 45.0;
	}

	if(start == 400.0)
		return;

	if(!(startang - len < start))
		return;

	for(;len > 0.0; len -= 90.0, start -= 90.0)
	{
		CPoint p;
		SetAngPntOnRect(p, start);
		parr.Add(p);
	}

}

void CScaleCtrl::LoadImage()
{
	m_image.CreateCompatibleBitmap(&m_wnd, 32,32);
//	m_image.GetDC()->FillRect(CRect(0,0,32,32), &CBrush(RGB(203,203,203)));
	m_image.GetDC()->PatBlt(0,0,32,32, WHITENESS);
	switch(m_init.image)
	{
	case image_class:
		m_image.DrawIcon(IDI_ICON1);
		break;
	case image_yom:
		m_image.DrawIcon(IDI_ICON_YOM);
		break;
	default:
		m_image.DrawIcon(IDI_ICON1);
		break;
	}
}

void CScaleCtrl::DrawImage()
{
	BITMAP bm;
	m_image.GetBitmap(&bm);
	int x = (m_init.rc.Width() - bm.bmWidth) / 2;
	int y = (m_init.rc.Height() - bm.bmHeight) / 2;
///	m_image.DrawTransparent(x,y, RGB(203,203,203), &m_memDc);
	m_image.DrawTransparent(x,y, RGB(255,255,255), &m_memDc);
//	m_image.Draw(&m_memDc, SRCCOPY, x, y);

}

void CScaleCtrl::DrawSpaceBar(double ang)
{
	CRect rc(0,0, m_init.rc.Width(), m_init.rc.Height());
	rc.DeflateRect(m_init.deflate, m_init.deflate);
	int leng = rc.Width() / 2;
	CPoint cpt = rc.CenterPoint();

	double x = cos(ang * g_degtorad);
	double y = sin(ang * g_degtorad);

	CPoint pt1(cpt.x + (int)((double)leng * x), cpt.y - (int)((double)leng * y));
	leng += 8;
	CPoint pt2(cpt.x + (int)((double)leng * x), cpt.y - (int)((double)leng * y));
	m_memDc.MoveTo(pt1);
	m_memDc.LineTo(pt2);
}

void CScaleCtrl::DrawSpaces()
{
	int bars = m_init.dwSpaces;
	double space = m_init.endang / (double)bars;
	if(m_init.endang < 360.0)
		bars++;

	double drawang = m_init.startang;

	for(int i = 0; i < bars; i++, drawang += space)
		DrawSpaceBar(drawang);
}

void CScaleCtrl::PaintScreen(CRect& rcn)
{
	CClientDC dc(&m_wnd);
	{
		dc.SetMapMode(MM_ISOTROPIC);
		dc.SetWindowExt(cs_cx, cs_cy);
		CRect rc;
		m_wnd.GetClientRect(rc);
		int cx = rc.Width();//pDC->GetDeviceCaps(LOGPIXELSX);
		int cy = rc.Height();//pDC->GetDeviceCaps(LOGPIXELSY);
		//TRACE("cx = %d   cy = %d\n", cx,cy);
		dc.SetViewportExt(cx,cy);
		dc.SetViewportOrg (0,  0) ;
	}
	//m_oldLineRc
	CRect rc = m_oldLineRc;

	if(!rc.IsRectNull())
	{
		rc.NormalizeRect();
		rc.InflateRect(2,2);
		CPoint pt(rc.left, rc.top);//);rc.Width(),rc.Height()
		rc += CPoint(m_init.rc.left,m_init.rc.top);
		dc.BitBlt(rc.left, rc.top, rc.Width(),
			rc.Height(),&m_memDc,pt.x,pt.y,SRCCOPY);
	}
	rc = rcn;
	if(!rc.IsRectNull())
	{
		rc.NormalizeRect();
		rc.InflateRect(2,2);
		CPoint pt(rc.left, rc.top);//);rc.Width(),rc.Height()
		rc += CPoint(m_init.rc.left,m_init.rc.top);
		dc.BitBlt(rc.left, rc.top, rc.Width(),
			rc.Height(),&m_memDc,pt.x,pt.y,SRCCOPY);
	}
	m_oldLineRc = rcn;
	rc = m_textRc;
	if(!rc.IsRectNull())
	{
		rc.InflateRect(2,2);
		CPoint pt(rc.left - m_init.rc.left, rc.top - m_init.rc.top);//);rc.Width(),rc.Height()
//		rc += CPoint(m_init.rc.left,m_init.rc.top);
		dc.BitBlt(rc.left, rc.top, rc.Width(),
			rc.Height(),&m_memDc,pt.x,pt.y,SRCCOPY);
	}

}
