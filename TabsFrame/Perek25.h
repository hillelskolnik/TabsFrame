#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"


// CPerek25 view

class CPerek25 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek25)

protected:
	CPerek25();           // protected constructor used by dynamic creation
	virtual ~CPerek25();

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
	double backfromMabul;
	void PaintSlider(void);
	CRect m_sliderRc;
	COLORREF color2;
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	virtual void InitOnSubHeadButton(void);
protected:
	int m_hieghtOffSet;
	int posy;
	int sShemesh;
	double turnX4;
};


