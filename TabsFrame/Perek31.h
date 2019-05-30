#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"
#include "afxwin.h"
#include "slider.h"


// CPerek31 view

class CPerek31 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek31)

protected:
	CPerek31();           // protected constructor used by dynamic creation
	virtual ~CPerek31();

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
public:
	virtual void Do3DPaint(void);
protected:
	double lasty;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	bool m_bRightBDown;
	CRect m_sliderRc;
	CRect m_sliderHorRc;
	double m_xTurn2;
	double m_xTurn3;
	double m_xStart;
	double m_yStart;
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
protected:
	int trsz;
	int trszArez;
	virtual void InitOnSubHeadButton(void);
	void PaintSlider(void);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void PaintResult(void);
	int trszSteps;
	unsigned long ofanHaziHaYomCol;
	unsigned long mashveHaYomCol;
	unsigned long galgalMazalotCol;
	int stepsArez;
protected:
	CSlider m_slider;
};


