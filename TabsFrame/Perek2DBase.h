#pragma once
#include "afxwin.h"
#include "toolexbar.h"
#include "ButtonEx.h"
#include "TabsFrame.h"
#include "atltypes.h"


// CPerek2DBase view

class CPerek2DBase : public CView
{
	DECLARE_DYNAMIC(CPerek2DBase)

protected:
	CPerek2DBase();           // protected constructor used by dynamic creation
	virtual ~CPerek2DBase();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	static void DrawPolyLines(int nLine, double frad, 
		CPoint &p, CDC* pDC, 
		double dStartAng = 90, 
		double dOptionAng = 0)
	{
		if(nLine <= 1)
			return;
		if(dOptionAng == 0)
			dOptionAng = 360.0 / (float)nLine;
		else
			dOptionAng /= (double)(nLine - 1);
		CArray<CPoint, CPoint&> arr;
		for(int i = 0; i < nLine;++i, dStartAng += dOptionAng)
		{
			C2DPoint dp(dStartAng);
			CPoint pt((int)(float)(dp.x * frad) + p.x, 
				 p.y - ((int)(float)(dp.y * frad)));
			arr.Add(pt);
			if(i == 0)
				pDC->MoveTo(pt);
			else if(i < (nLine - 1))
				pDC->LineTo(pt);
			else
			{
				pDC->LineTo(pt);
				pDC->LineTo(arr[0]);
			}
		}

	}
public:
	virtual void DoDrawing(CDC* pDC);
protected:
	unsigned int m_buttonId;
	CToolExBar m_wndTool;
	CBitmap m_memBm;
	CDC m_memDc;
public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
protected:
	BOOL m_bBntDown;
	BOOL m_bHandCursor;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
public:

	static double PointsToAng(CPoint& pMiddel, CPoint& p)
	{
		double y = (double)(pMiddel.y - p.y);
		double x = (double)(p.x - pMiddel.x);
		return atan2(y,x) * ToD;
	}
public:

	static void DrawLine(double length, CPoint& middelP, double& ang, 
		CDC* pDC, COLORREF color, int nWidth = 2)
	{
		double y = sin(ang * D) * -length;
		double x = cos(ang * D) * length;
		CPoint p(middelP.x + (int)(float)x, middelP.y + (int)(float)y);
		CPen pen(PS_SOLID, nWidth, color);
		CPen* oPen = pDC->SelectObject(&pen);
		pDC->MoveTo(middelP);
		pDC->LineTo(p);

		pDC->SelectObject(oPen);
	}
	static CPoint GetAnglePoint(double len, double ang, CPoint &p)
	{
		double y = sin(ang * D) * -len;
		double x = cos(ang * D) * len;
		CPoint p2(p.x + (int)(float)x, p.y + (int)(float)y);
		return p2;
	}
protected:
	CFont m_font;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	unsigned int m_IDstart;
public:
	afx_msg void OnSubHeadUpdate(CCmdUI* pCmdUI);
public:
	virtual void SetDgreeStartAng(void);
public:
	afx_msg virtual void OnSubHeadBtn(UINT Id);
protected:
	unsigned int m_IDidx;
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	int m_IDX_PEREK;
public:
	static int DiameterSteps(int diameter, double fine = 1.0);
protected:
	CRect m_rcGetWnd;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	int m_ipWidth;
	int m_ipHeight;
	bool m_bNoTimerDraw;
	bool m_bNoDilay;
};


