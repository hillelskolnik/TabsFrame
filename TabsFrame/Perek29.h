#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"


// CPerek29 view

class CPerek29 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek29)

protected:
	CPerek29();           // protected constructor used by dynamic creation
	virtual ~CPerek29();

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
	int trszArez;
	int trsz;
public:
	CRect m_sliderRc;
protected:
	CRect m_sliderHorRc;
	double m_xStart;
	double m_yStart;
	void Do3DPaint(void);
	void PaintSlider(void);
	virtual void InitOnSubHeadButton(void);
	double m_xTurn2;
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	double lasty;
	double m_trszStep;
	unsigned long m_color2;
	double m_fine;
};


