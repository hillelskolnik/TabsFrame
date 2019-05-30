#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"
#include "afxwin.h"
#include "slider.h"
#include "person.h"


// CPerek32 view

class CPerek32 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek32)

protected:
	CPerek32();           // protected constructor used by dynamic creation
	virtual ~CPerek32();

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
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void InitOnSubHeadButton(void);
	void PaintResult(void);
	void PaintSlider(void);
	bool m_bRightBDown;
	double lasty;
	double m_yTurn;
	double m_yStart;
	double m_xTurn;
	double m_xTurn2;
	double m_xTurn3;
	double m_xTurn4;
	double m_xStart;
	CRect m_sliderHorRc;
	int trsz;
	int trszArez;
	int trszSteps;
	int stepsArez;
	CBitmap m_bmMazalot;
	unsigned long mashveHaYomCol;
	unsigned long galgalMazalotCol;
	CSlider m_slider2;
	CSlider m_slider;
	unsigned long color1;
	CPerson m_person;
public:
	double ToseffetYom(double mazal, double rochav);
protected:
	unsigned long colorLayla;
	unsigned long colorYom;
};


