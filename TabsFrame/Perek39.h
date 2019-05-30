#pragma once
#include "Perek3DBase.h"
#include "slider.h"
#include "atltypes.h"


// CPerek39 view

class CPerek39 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek39)

protected:
	CPerek39();           // protected constructor used by dynamic creation
	virtual ~CPerek39();

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
	int trsz;
	int trszArez;
	double m_zTurn;
	CSlider m_sliderx;
	CSlider m_sliderz;
public:
	void Do3DPaint(void);
protected:
	CSlider m_sliderHor;
	CSlider m_sliderOr;
	CSlider m_sliderMY;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void InitOnSubHeadButton(void);
	void PaintSlider(void);
	double m_xTurn2;
	double m_xStart;
	double m_yStart;
	double SivuvMashve(double angMazal, double rohavMedina);
public:
	double SivuvKeshetKtavim(double angMazal, double angRohavMedina);
protected:
	int trszSteps;
	double m_orech;
	double m_MY;
	unsigned long colMazal;
	unsigned long colSivuvMasve;
	double orechMash;
public:
	void PaintResult(void);
protected:
	CRect m_rcResult;
	double fine2;
	int trszSteps2;
};


