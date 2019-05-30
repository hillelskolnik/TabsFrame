#pragma once
#include "Perek3DBase.h"
#include "slider.h"
#include "atltypes.h"


// CPerek44 view

class CPerek44 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek44)

protected:
	CPerek44();           // protected constructor used by dynamic creation
	virtual ~CPerek44();

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
	int trszArez;
public:
	void Do3DPaint(void);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	CSlider m_slider;
	CSlider m_slider2;
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void PaintSlider(void);
	void PaintResult(void);
	virtual void InitOnSubHeadButton(void);
	CRect m_rcRes;
	double m_xTurn2;
	int trsz;
	unsigned long colEmzai;
	unsigned long colAmity;
	int trszGova;
	unsigned long colGalgalMazalot;
	int trszGalgalShemesh;
	double govaRelasion;
public:
	unsigned long colOtiyot;
};


