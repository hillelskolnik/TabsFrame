// MSlidrCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "MSlidrCtrl.h"


// CMSlidrCtrl

IMPLEMENT_DYNAMIC(CMSlidrCtrl, CSliderCtrl)

CMSlidrCtrl::CMSlidrCtrl()
{

}

CMSlidrCtrl::~CMSlidrCtrl()
{
}


BEGIN_MESSAGE_MAP(CMSlidrCtrl, CSliderCtrl)
	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CMSlidrCtrl::OnNMCustomdraw)
END_MESSAGE_MAP()



// CMSlidrCtrl message handlers



BOOL CMSlidrCtrl::OnEraseBkgnd(CDC* pDC)
{
	//CRect rc;
	//GetClientRect(rc);
	//pDC->FillSolidRect(rc, 0);//RGB(64,0,128));
	return FALSE;	
	
	//return CSliderCtrl::OnEraseBkgnd(pDC);
}

void CMSlidrCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	//// TODO: Add your control notification handler code here
	//*pResult = 0;
	LPNMCUSTOMDRAW lpcd = (LPNMCUSTOMDRAW)pNMHDR;
	CDC *pDC = CDC::FromHandle(lpcd->hdc);
	switch(lpcd->dwDrawStage)
	{
		case CDDS_PREPAINT:
			*pResult = CDRF_NOTIFYITEMDRAW ;
			break;
			//return;  
		case CDDS_ITEMPREPAINT:
		if (lpcd->dwItemSpec == TBCD_THUMB)
		{
			*pResult = CDRF_DODEFAULT;
			break;
		}
		if (lpcd->dwItemSpec == TBCD_CHANNEL)
		{
			CRect rc;
			GetClientRect(rc);
			Default();
			CBrush br(RGB(64,100,198));
			CBrush *oBr = pDC->SelectObject(&br);
			pDC->FloodFill(4,2,0);
			CBrush br2(RGB(255,255,255));
			if(GetSafeHwnd() == GetFocus()->GetSafeHwnd())
			{
				pDC->SelectObject(&br2);
				pDC->FrameRect(rc, &br2);
			}

			pDC->SelectObject(&oBr);
			*pResult = 0;
			break;
		}
	}
}
