#pragma once
#include "Perek3DBase.h"
#include "person.h"
#include "atltypes.h"


// CPerek28 view

class CPerek28 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek28)

protected:
	CPerek28();           // protected constructor used by dynamic creation
	virtual ~CPerek28();

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
	virtual void Do3DPaint(void);
protected:
	CPerson m_person;
	int stepsArez;
	CRect m_sliderRc;
	CRect m_sliderHorRc;
	void PaintSlider(void);
	void InitOnSubHeadButton(void);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	double m_xStart;
	double m_yStart;
	double lasty;
	double standPos;
	double fine2;
	int steps2;
	double m_xTurn2;
	int stepsTrsz;
	int stepsMashve;
};


