#pragma once
#include "Perek3DBase.h"
#include "slider.h"
#include "atltypes.h"


// CPerek41 view

class CPerek41 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek41)

protected:
	CPerek41();           // protected constructor used by dynamic creation
	virtual ~CPerek41();

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
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void PaintSlider(void);
	virtual void InitOnSubHeadButton(void);
	void PaintResult(void);
	CSlider m_slider;
	CSlider m_sliderHor;
	double m_xTurn2;
public:
	virtual void Do3DPaint(void);
protected:
	double lastx;
	double m_xStart;
	double m_yStart;
	int trszArez;
	int trsz;
	double arezFine;
	int arezSteps;
	int trszSteps;
	double m_tosefetOfek;
	double angAliya;
public:
	CRect m_rcRes;
protected:
	unsigned long colOrechSkia;
	unsigned long color0;
};


