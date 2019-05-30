#pragma once
#include "Perek2DBase.h"
#include "atltypes.h"


// CPerek5 view

class CPerek5 : public CPerek2DBase
{
	DECLARE_DYNCREATE(CPerek5)

protected:
	CPerek5();           // protected constructor used by dynamic creation
	virtual ~CPerek5();

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
	virtual void DoDrawing(CDC* pDC);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	CRect m_rc;
	double m_degree;
	CPoint m_pMiddel;
	int m_nHalfWidth;
};


