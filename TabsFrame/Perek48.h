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

enum eTkufot
{
	tkufat_nisan,
	tkufat_tamuz,
	tkufat_tishray,
	tkufat_tevet
};

// CPerek48 view

class CPerek48 : public CPerek3DBase
{
	DECLARE_DYNCREATE(CPerek48)

protected:
	CPerek48();           // protected constructor used by dynamic creation
	virtual ~CPerek48();

public:
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
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	virtual void Do3DPaint(void);
protected:
	int trsz;
public:
	double GetTkufaEmzaiAng(long year, eTkufot tkufa);
public:
	double GetTkufaEmzaiTryAng(long year, eTkufot tkufa);
public:
	long GetTkufaMonth(long &year, eTkufot tkufa);
	CString GetTkufaStr(long year, eTkufot tkufa);
protected:
	CMyFBitmap m_dateNisanBm;
	CMyFont m_dateNisanFont;
	CMyFBitmap m_dateTamuzBm;
	CMyFont m_dateTamuzFont;
	CMyFBitmap m_dateTishrayBm;
	CMyFont m_dateTishrayFont;
	CMyFBitmap m_dateTevetBm;
	CMyFont m_dateTevetFont;
	CRect m_rcNisan;
	void TkufutResult(void);
	long m_year;
	CRect m_rcTamuz;
	CRect m_rcTishray;
	CRect m_rcTevet;
	void DrawTkufaAmity(void);
	CSlider m_slider;
	void InitOnSubHeadButton(void);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	long m_past;
	double m_monthTurn;
public:
	double GetNisanRambam(int year);
protected:
	long m_lastYeat;
	double m_sAmity;
	CRect m_rcRes;
	void PaintResult(void);
public:
	double GetTishrayShmuel(int year);
protected:
	void DrawTkufaShmuel(void);
	CDaysPast m_ikarSmuel;
	CCircleSpeed m_speedShmuel;
	CDaysPast m_ikarAda;
	CCircleSpeed m_speedAda;
	CString GetTkufatSmueaStr(long year, eTkufot tkufa);
	CString GetTkufatAdaStr(long year, eTkufot tkufa);
	void DrawTkufaAda(void);
	double GetTishrayAda(int year);
};


class CPerek48Split : public CBasePerekSplit
{
	DECLARE_DYNCREATE(CPerek48Split)

protected:
	CPerek48Split();           // protected constructor used by dynamic creation
	virtual ~CPerek48Split();

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



// CPerek48Msg view

class CPerek48Msg : public CMsgView
{
	DECLARE_DYNCREATE(CPerek48Msg)

protected:
	CPerek48Msg();           // protected constructor used by dynamic creation
	virtual ~CPerek48Msg();

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


