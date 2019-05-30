#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"
#include "person.h"


// CPerek17 view

class CPerek17 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek17)

protected:
	CPerek17();           // protected constructor used by dynamic creation
	virtual ~CPerek17();

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
	CPerson m_person;
public:
	virtual void Do3DPaint(void);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	int stepsTrsz;
	virtual void InitOnSubHeadButton(void);
};


