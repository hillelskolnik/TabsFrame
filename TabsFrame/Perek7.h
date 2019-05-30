#pragma once
#include "Perek2DBase.h"
#include "atltypes.h"


// CPerek7 view

class CPerek7 : public CPerek2DBase
{
	DECLARE_DYNCREATE(CPerek7)

protected:
	CPerek7();           // protected constructor used by dynamic creation
	virtual ~CPerek7();

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
	CRect m_rc;
	CPoint m_pt;
	CPoint m_pAlef;
	CPoint m_pBet;
	CRect m_rcMouse;
};


