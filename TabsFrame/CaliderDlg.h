#pragma once
#include "afxcmn.h"
#include "atltypes.h"
#include "resource.h"
#include "afxwin.h"
#include "mslidrctrl.h"

enum
{
	cal_cx = 190,
	cal_cy = 450,
	cal_ply = 30
};

typedef CArray<CRect, CRect> tdrcArr;

// CCaliderDlg dialog

class CCaliderDlg : public CDialog
{
	DECLARE_DYNAMIC(CCaliderDlg)

public:
	CCaliderDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCaliderDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_CLINDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CMSlidrCtrl m_ctrlElef;
	CMSlidrCtrl m_ctrlMeha;
	CMSlidrCtrl m_ctrlEser;
	int m_nElef;
	int m_nMeha;
	int m_nEser;
protected:
	CWnd* m_pWnd;
public:
	BOOL Create(CWnd* pWnd);
	virtual BOOL OnInitDialog();
	void SetResultWnd(CWnd* pWnd);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CMSlidrCtrl m_ctrlEhad;
	int m_nEhad;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
protected:
	CMyFBitmap m_yearsBm;
	int m_shnimLeft;
	CArray<int, int> m_ctrlYArr;
	CString BuildDateStr(void);
	CMyFont m_dateFont;
	void PaintDate(void);
public:
	CMSlidrCtrl m_ctrlMonths;
	int m_nMonths;
protected:
	bool m_bLeap;	
	 tdrcArr m_mothsRcArr;
	CMyFBitmap m_leapMonthsBm;
	CMyFBitmap m_normalMonthsBm;
public:
	// idx from 1 to 13
	CString GetMonthStr(int idx, bool bLeap);
protected:
	void BuildMonthRects(void);
	CRect m_monthsRc;
	void PaintMonth(void);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CMSlidrCtrl m_ctrlMDay;
	int m_nMDay;
protected:
	int m_nYears;
public:
	CString GetMDayStr(int day);
protected:
	void BuildMDaysRcsAndBms(void);
	 tdrcArr m_mothDsRcArr;
	CMyFBitmap m_MonthMalleBm;
	CMyFBitmap m_MonthHaserBm;
	CRect m_monthDRc;
	int m_daysInMonth;
	void PaintMonthDays(void);
	CScaleResult m_result;
public:
	afx_msg void OnBnClickedButtonMin();
	afx_msg void OnBnClickedButtonPlus();
	CEdit m_edtYearsJump;
	afx_msg void OnEnChangeEditYearsjump();
	CButton m_btnMin;
	CButton m_btnPlus;
protected:
	int m_nYearsJump;
	void SetDate(void);
public:
	void SetYearsCtrlsPod(void);
public:
	void SetDate(CYMDs date);
protected:
	int m_shiftDays;
};
