#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"
#include "..\scaleveiw\deff.h"


// CPerek12 view

class CPerek12 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek12)

protected:
	CPerek12();           // protected constructor used by dynamic creation
	virtual ~CPerek12();

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
	void Do3DPaint(void);
protected:
	virtual void InitOnSubHeadButton(void);
protected:
};


