#pragma once
#include "afxwin.h"
#include "atltypes.h"

#include "Perek2DBase.h"


// CPerek2 view

class CPerek2 : public CPerek2DBase
{
	DECLARE_DYNCREATE(CPerek2)

protected:
	CPerek2();           // protected constructor used by dynamic creation
	virtual ~CPerek2();

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

	CRect m_rc;
	CRect m_rcMiddel;
	CPoint m_pMiddel;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	double m_degree;
public:
	virtual void SetDgreeStartAng(void);
};


