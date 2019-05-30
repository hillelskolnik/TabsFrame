#pragma once
#include "Perek2DBase.h"
#include "..\scaleveiw\3dscreen.h"
#include "..\scaleveiw\deff.h"
#include "atltypes.h"


// CPerek3DBase view

class CPerek3DBase : public CPerek2DBase
{
	DECLARE_DYNCREATE(CPerek3DBase)

protected:
	CPerek3DBase();           // protected constructor used by dynamic creation
	virtual ~CPerek3DBase();

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	C3DScreen m_3dscreen;
	CScales m_scale;
public:
	void OnSubHeadBtn(UINT Id);
public:
	virtual void Do3DPaint(void);
public:
	virtual void SetDgreeStartAng(void);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	virtual void DoDrawing(CDC* pDC);
protected:
	void CaptionDraw(CDC* pDC);
	virtual void InitOnSubHeadButton(void);
	bool m_bSkip;
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	bool m_bPastCreate;
	CPoint m_pt;
	double m_xTurn;
	double m_yTurn;
	void CreateText(int id, CString text, unsigned long txtColor, unsigned long bkColor = 0, unsigned int txtBmId = IDB_BITMAP_OTIYUT);
	int m_nCaptionBottom;
};


