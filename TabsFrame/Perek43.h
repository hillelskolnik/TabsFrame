#pragma once
#include "Perek3DBase.h"
#include "slider.h"
#include "atltypes.h"


// CPerek43 view

class CPerek43 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek43)

protected:
	CPerek43();           // protected constructor used by dynamic creation
	virtual ~CPerek43();

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
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void InitOnSubHeadButton(void);
	void PaintSlider(void);
	void PaintResult(void);
	CSlider m_slider;
	CSlider m_sliderHor;
	CSlider m_sliderMar;
	CSlider m_sliderMiz;
	CSlider m_sliderMedMiz;
	CSlider m_sliderSivuvYom;
	int trszArez;
	double arezFine;
	double m_xTurnMa;
	double m_xTurnMiz;
	double m_yTurnMedMiz;
	unsigned long colMedMiz;
	int arezSteps;
	unsigned long colMedMaarav;
	int trsz;
	double m_yTurnYomi;
	double kizuzMa;
	double kizuzMiz;
	CRect m_rcRes;
	double lastMiz;
	double lasty;
	double lastyYomi;
	double m_xTurn2;
	double lastxMiz;
	double lastx2;
};


