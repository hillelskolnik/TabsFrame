#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"


// CPerek26 view

class CPerek26 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek26)

protected:
	CPerek26();           // protected constructor used by dynamic creation
	virtual ~CPerek26();

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
	const double ofekAng;
	int m_nMazalotStarsSize;
	virtual void InitOnSubHeadButton(void);
	const int timerElaps;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
protected:
	double lasty;
	int conusHeight;
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void PaintSlider(void);
	CRect m_sliderRc;
	const double chap3startY;
	CRect m_sliderHorRc;
	double m_xTurn2;
	double mazalMesibaFine;
	int mazalMesibaSize;
	void PaintResult(void);
	double chap4startY;
	double diameterEgulKotev;
	double shiftEgulKotev;
	int sizeEgulKotev;
};


