#pragma once
#include "Perek3DBase.h"
#include "slider.h"
#include "atltypes.h"


// CPerek35 view

class CPerek35 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek35)

protected:
	CPerek35();           // protected constructor used by dynamic creation
	virtual ~CPerek35();

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
	void Do3DPaint(void);
protected:
	void PaintResult(void);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	CRect m_sliderHorRc;
	CSlider m_slider;
	CSlider m_slider2;
	double m_xTurn2;
	double m_xTurn3;
	void InitOnSubHeadButton(void);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void PaintSlider(void);
	double m_yStart;
	int trsz;
	int trszArez;
	int stepsArez;
	double m_xStart;
	int trszSteps;
	double lastx3;
	unsigned long galgalMazalotCol;
	unsigned long colorMasveYom;
	unsigned long color0;
	double lasty;
	double lastx2;
	unsigned long colorShemesh;
};


