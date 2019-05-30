#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"


// CPerek27 view

class CPerek27 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek27)

protected:
	CPerek27();           // protected constructor used by dynamic creation
	virtual ~CPerek27();

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
public:
	virtual void Do3DPaint(void);
protected:
	const int trsz;
	double m_yTurn;
	double m_xTurn;
	int trsz2;
	double lasty;
	virtual void InitOnSubHeadButton(void);
	double ofekAng;
	double yTurn1;
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void PaintSlider(void);
	CRect m_sliderRc;
	double m_xTurnShemesh;
	CRect m_sliderHorRc;
	const int sShemesh;
	double yTurn56;
	const double shemeshMesibaFine;
	const int shemeshMesibaSize;
	int m_nMazalotStarsSize;
};


