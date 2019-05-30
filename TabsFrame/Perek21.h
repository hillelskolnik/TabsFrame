#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"
#include "person.h"


// CPerek21 view

class CPerek21 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek21)

protected:
	CPerek21();           // protected constructor used by dynamic creation
	virtual ~CPerek21();

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
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	double m_stepsKav;
	double m_stepsRochavMevukash;
	double m_stepsTrszP2;
	CPerson m_person;
protected:
	bool m_bLbDown;
	double m_yTplus;
	double m_xTplus;
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
protected:
	virtual void InitOnSubHeadButton(void);
};


