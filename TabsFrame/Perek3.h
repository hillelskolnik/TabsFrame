#pragma once
#include "Perek2DBase.h"
#include "atltypes.h"



// CPerek3 view

class CPerek3 : public CPerek2DBase
{
	DECLARE_DYNCREATE(CPerek3)

protected:
	CPerek3();           // protected constructor used by dynamic creation
	virtual ~CPerek3();

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
public:
	void SetDgreeStartAng(void);
protected:
	double m_degree;
	CRect m_rc;
	CPoint m_pMiddel;
	int bplus;
public:
	CRect m_rcHalf;
};


