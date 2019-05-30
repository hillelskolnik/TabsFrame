#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"


// CPerek14 view

class CPerek14 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek14)

protected:
	CPerek14();           // protected constructor used by dynamic creation
	virtual ~CPerek14();

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
	double m_zTurn;
	int m_nekudaSteps;
	void PaintSlider(void);
	CRect m_sliderHorRc;
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void InitOnSubHeadButton(void);
};


