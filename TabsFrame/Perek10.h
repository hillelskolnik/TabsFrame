#pragma once
#include "Perek2DBase.h"
#include "atltypes.h"
#include "tabsframe.h"


// CPerek10 view

class CPerek10 : public CPerek2DBase
{
	DECLARE_DYNCREATE(CPerek10)

protected:
	CPerek10();           // protected constructor used by dynamic creation
	virtual ~CPerek10();

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
	void DoDrawing(CDC* pDC);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	double m_diameter;
	double m_top;
	double m_ptyNull;
	double m_right;
	CRect m_rc;
	CPoint m_pt;
	double m_radius;
	CPoint m_plb;
	C2DPoint m_dPArr[12];
	void InitDPArr(void);
	double m_step;
	double m_angStep;
	CPoint m_pmt7;
	CPoint m_plt7;
};


