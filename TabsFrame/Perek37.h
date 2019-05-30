#pragma once
#include "Perek3DBase.h"
#include "slider.h"
#include "atltypes.h"


// CPerek37 view

class CPerek37 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek37)

protected:
	CPerek37();           // protected constructor used by dynamic creation
	virtual ~CPerek37();

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
	unsigned long color0;
public:
	void Do3DPaint(void);
protected:
	CSlider m_sliderHor;
	CSlider m_sliderHor2;
	CSlider m_slider;
	int trsz;
	int trszArez;
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void InitOnSubHeadButton(void);
	double m_yStart;
	double m_xStart;
	unsigned long colSofHaYeshuv;
	void PaintSlider(void);
	CRect m_captionRc;
	double m_yTurn2;
	double m_yTosefetMaarav;
	int m_nCapHeight;
	void PaintResult(void);
	double lastyTosefet;
};


