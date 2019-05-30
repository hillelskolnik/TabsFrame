#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"
#include "..\scaleveiw\deff.h"


// CPerek13 view

class CPerek13 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek13)

protected:
	CPerek13();           // protected constructor used by dynamic creation
	virtual ~CPerek13();

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
protected:
	double m_zTurn;
public:
	void Do3DPaint(void);
};


