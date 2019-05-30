#pragma once
#include "Perek3DBase.h"
#include "atltypes.h"
#include "BaseSplitter.h"
#include "caliderdlg.h"
#include "speedtable.h"
#include "MsgView.h"
#include "afxwin.h"




// CPerek47 view

class CPerek47 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek47)

protected:
	CPerek47();           // protected constructor used by dynamic creation
	virtual ~CPerek47();

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
	int trszArez;
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void PaintResult(void);
	CRect m_rcRes;
	double m_xTurn2;
	int trsz;
	unsigned long colEmzai;
	unsigned long colAmity;
	int trszGova;
	unsigned long colGalgalMazalot;
	int trszGalgalShemesh;
	double govaRelasion;
	unsigned long colOtiyot;
	double menatHaMslul;
	double m_shemeshAmity;
	unsigned long colMenat;
	unsigned long colMaslul;
public:
	double CalcMaslul(void);
protected:
	double m_maslul;
};



class CPerek47Split : public CBasePerekSplit
{
	DECLARE_DYNCREATE(CPerek47Split)

protected:
	CPerek47Split();           // protected constructor used by dynamic creation
	virtual ~CPerek47Split();

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



// CPerek47Msg view

class CPerek47Msg : public CMsgView
{
	DECLARE_DYNCREATE(CPerek47Msg)

protected:
	CPerek47Msg();           // protected constructor used by dynamic creation
	virtual ~CPerek47Msg();

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


