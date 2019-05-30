#pragma once


// CMSlidrCtrl

class CMSlidrCtrl : public CSliderCtrl
{
	DECLARE_DYNAMIC(CMSlidrCtrl)

public:
	CMSlidrCtrl();
	virtual ~CMSlidrCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
};


