// ScaleCtrl.h: interface for the CScaleCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCALECTRL_H__CE29A667_C08E_438D_9869_CB16C6D8EAEB__INCLUDED_)
#define AFX_SCALECTRL_H__CE29A667_C08E_438D_9869_CB16C6D8EAEB__INCLUDED_

#include "DEFF.H"	// Added by ClassView
#include "MyBitmap.h"	// Added by ClassView
#include "atltypes.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef CArray<CPoint, CPoint&> PointArr;


class CScaleCtrl  
{
public:
	void CtrlLoop();
	static unsigned __stdcall RunCtrl(LPVOID lpVoid);
	CScaleCtrl(HWND wnd);
	virtual ~CScaleCtrl();

protected:
	bool m_bIsHand;
	void DrawSpaces();
	void DrawSpaceBar(double ang);
	void DrawImage();
	void LoadImage();
	CMyBitmap m_image;
	void AddRgnCorner(PointArr &parr);
	void SetAngPntOnRect(CPoint &pt, double ang);
	CRgn m_notRgn;
	void CreateRgn();
	void DrawResult();
//	const double m_todeg;
	void SetResult(const CPoint &cpt, const CPoint &pt);
//	double m_result;
//	const double m_raddeg;
	CPoint StartPoint();
	CInit m_init;
	CWnd m_wnd;
	void PaintScreen();
	CPoint MakelongLine(CPoint pt);
	void MoseMove(CPoint pt);
	bool m_bDown;
	void CreateBm();
	CBitmap *m_oldBitmap;
	CDC m_memDc;
	CBitmap *m_memBitmap;
	CBrush *m_oldBrush;
	CScaleResult m_result;
public:
	void PaintScreen(CRect& rcn);
protected:
	CRect m_oldLineRc;
	CRect m_textRc;
};

#endif // !defined(AFX_SCALECTRL_H__CE29A667_C08E_438D_9869_CB16C6D8EAEB__INCLUDED_)
