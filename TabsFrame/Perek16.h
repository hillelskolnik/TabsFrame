#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"
#include "person.h"
#include "..\scaleveiw\3dscreen.h"


// CPerek16 view

class CPerek16 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek16)

protected:
	CPerek16();           // protected constructor used by dynamic creation
	virtual ~CPerek16();

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
	double m_distance;
	void InitOnSubHeadButton(void);
	CPerson m_person;
};


