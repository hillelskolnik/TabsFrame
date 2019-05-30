#pragma once


// CMsgView view

class CMsgView : public CView
{
	DECLARE_DYNCREATE(CMsgView)

protected:
	CMsgView();           // protected constructor used by dynamic creation
	virtual ~CMsgView();

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
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
	virtual void SetFonts();
	CFont m_fontHe;
	CFont m_fontEn;
};


