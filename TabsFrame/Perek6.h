#pragma once
#include "Perek2DBase.h"
#include "atltypes.h"


// CPerek6 view

class CPerek6 : public CPerek2DBase
{
	DECLARE_DYNCREATE(CPerek6)

protected:
	CPerek6();           // protected constructor used by dynamic creation
	virtual ~CPerek6();

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
	double m_degree;
	CPoint m_pMiddel;
	int m_nHalfWidth;
};


