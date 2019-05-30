#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"
#include "person.h"

// CPerek18 view

class CPerek18 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek18)

protected:
	CPerek18();           // protected constructor used by dynamic creation
	virtual ~CPerek18();

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
	virtual void InitOnSubHeadButton(void);
	CPerson m_person;
};


