#pragma once
#include "Perek2DBase.h"
#include "atltypes.h"


// CPerek4 view

class CPerek4 : public CPerek2DBase
{
	DECLARE_DYNCREATE(CPerek4)

protected:
	CPerek4();           // protected constructor used by dynamic creation
	virtual ~CPerek4();

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
	void DoDrawing(CDC* pDC);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	void SetDgreeStartAng(void);
	CPoint m_pMiddel;
	double m_degree;
	CRect m_rc;
	CRect m_rctl;
	CRect m_rcbr;
	int m_radius;
	CRect m_rcArc;
};


