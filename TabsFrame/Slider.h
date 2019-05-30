#pragma once
#include "atltypes.h"
#include "afxcoll.h"
#include "afxwin.h"

enum pointPos
{
	middle
	,bottom
};

class CSlider
{
public:
	enum types
	{
		simpleVertical	= 0
		,VerCaptionResultMazalot
		,VerMin90Plus90
		,simpleHorizontal360
		,simpleHorizontal
	} m_type;
	CSlider(CView *pView, CRect rc, CSlider::types type = simpleVertical);
public:
	~CSlider(void);
protected:
	CRect m_rc;
	CView* m_pView;
	CPoint m_pt;
	
	CUIntArray m_onButtonsShow;
public:
	void AddButtonId(unsigned int id);
public:
	void InitOnSubHeadButton(void);
protected:
	int m_lastpos;
public:
	bool IsOneOfId(unsigned int id);
public:
	void Init(void);
protected:
	CBitmap m_memBm;
	CDC m_memDc;
	bool m_bNotDefaultColor;
public:
	unsigned long GetDefaultColor(void);
protected:
	unsigned long m_bkColor;
	unsigned long m_frameColor;
	CRect m_rcDeflate;
public:
	void SetDeflate(int left, int top, int right, int bottom);
protected:
	void Deflate(CRect& rc);
	void Paint(CClientDC& dc);
public:
	bool PtInRect(CPoint& p, double& turn, bool bReversed = false);
public:
	void SetCaption(const CString& str);
protected:
	CString m_sCaption;
	// Top caption hhieght
	int m_nTopCapHieght;
	// Bottom caption hieght
	int m_nBotCapHieght;
	double m_minVal;
	double m_maxVal;
	CFont m_font;
	int m_nFontSize;
	CString m_sFaceName;
	void CreateFont(void);
public:
	void PaintPos(int pos, CClientDC& dc);
protected:
	CPen m_pen;
public:
	void CleanPos(CClientDC& dc);
protected:
	double m_stepsToVal;
	void PaintResult(CClientDC& dc);
	double m_turn;
	unsigned long m_textColor;
public:
	void PaintBk(void);
protected:
	CBitmap m_bmMazalot;
	CDC m_dcMazalot;
public:
	double SetVal(double val);
public:
	void SetMinMax(double fMin, double fMax);
public:
	void SetRefPoint(pointPos pos);
protected:
	CString m_sFormatResult;
public:
	void SetResultFormat(CString sFormat);
protected:
	int m_left;
	int m_right;
public:
	void SetFontSize(int size);
public:
	void SetFrameColor(unsigned long col);
protected:
	double m_rangeTop;
	double m_rangeBottom;
public:
	void SetMinMaxRange(double fMin, double fMax);
public:
	bool PntInRect(CPoint& p);
};
