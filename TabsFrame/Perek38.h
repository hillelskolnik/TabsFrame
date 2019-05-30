#pragma once
#include "Perek3DBase.h"
#include "slider.h"
#include "atltypes.h"


// CPerek38 view

class CPerek38 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek38)

protected:
	CPerek38();           // protected constructor used by dynamic creation
	virtual ~CPerek38();

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
	CSlider m_slider1;
	CSlider m_slider2;
	int trsz;
	int trszArez;
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void InitOnSubHeadButton(void);
	double m_yStart;
	double m_xStart;
	unsigned long colSofHaYeshuv;
	void PaintSlider(void);
	CRect m_captionRc;
	double m_xTurn1;
	double m_xTurn2;
	double lastx1;
	double lastx2;
};


