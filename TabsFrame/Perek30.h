#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"
#include "afxwin.h"

// CPerek30 view

class CPerek30 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek30)

protected:
	CPerek30();           // protected constructor used by dynamic creation
	virtual ~CPerek30();

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	int trszArez;
	int trsz;
public:
	double m_fine;
protected:
	double m_trszStep;
	double m_xStart;
	double m_yStart;
	CRect m_sliderRc;
	CRect m_sliderHorRc;
	double m_xTurn2;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	virtual void Do3DPaint(void);
protected:
	virtual void InitOnSubHeadButton(void);
	void PaintSlider(void);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	double lasty;
	unsigned long m_color1;
	double m_xTurn3;
	bool m_bRightBDown;
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
protected:
	double m_fineMashve;
	COLORREF color4;
	COLORREF color5;
public:
	void PaintResult(void);
protected:
	CBitmap m_bmMazalot;
	COLORREF color7;
	COLORREF color8;
};


