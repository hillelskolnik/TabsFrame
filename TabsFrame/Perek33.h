#pragma once
#include "Perek3DBase.h"
#include "slider.h"
#include "atltypes.h"
#include "person.h"


// CPerek33 view

class CPerek33 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek33)

protected:
	CPerek33();           // protected constructor used by dynamic creation
	virtual ~CPerek33();

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
	void PaintResult(void);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	CSlider m_slider;
	CRect m_sliderHorRc;
	double m_xTurn2;
	CPerson m_person;
	void PaintSlider(void);
	virtual void InitOnSubHeadButton(void);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	int trsz;
	int trszArez;
	int trszSteps;
	double m_xStart;
	double m_yStart;
	unsigned long color1;
};


