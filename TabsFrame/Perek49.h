#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"
#include "BaseSplitter.h"
#include "caliderdlg.h"
#include "speedtable.h"
#include "MsgView.h"
#include "afxwin.h"
#include "..\scaleveiw\deff.h"
#include "slider.h"
#include "..\timespeed\basicunit.h"


// CPerek49 view

class CPerek49 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek49)

protected:
	CPerek49();           // protected constructor used by dynamic creation
	virtual ~CPerek49();

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
	unsigned long color0;
public:
	virtual void Do3DPaint(void);
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	long m_past;
	long m_year;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	double m_xStart;
	double m_yStart;
	int trsz;
	double m_lastX;
	virtual void InitOnSubHeadButton(void);
	double m_shemeshEmzai;
	double m_shemeshAmity;
	double m_amityAliyaYeshara;
	void PaintResult(void);
	CRect m_rcRes;
};


class CPerek49Split : public CBasePerekSplit
{
	DECLARE_DYNCREATE(CPerek49Split)

protected:
	CPerek49Split();           // protected constructor used by dynamic creation
	virtual ~CPerek49Split();

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	CBaseSplitter m_leftSpliter;
public:
	virtual void Create(UINT nPane);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	CCaliderDlg m_calider;
};

// CPerek49Msg view

class CPerek49Msg : public CMsgView
{
	DECLARE_DYNCREATE(CPerek49Msg)

protected:
	CPerek49Msg();           // protected constructor used by dynamic creation
	virtual ~CPerek49Msg();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};

