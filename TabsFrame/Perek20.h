#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"


// CPerek20 view

class CPerek20 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek20)

protected:
	CPerek20();           // protected constructor used by dynamic creation
	virtual ~CPerek20();

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
	int m_stepsKav;
};


