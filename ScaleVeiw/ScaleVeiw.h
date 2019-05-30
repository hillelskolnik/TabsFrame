// ScaleVeiw.h : main header file for the SCALEVEIW DLL
//

#if !defined(AFX_SCALEVEIW_H__0072C659_5B4C_4AFA_A196_6C4528045A90__INCLUDED_)
#define AFX_SCALEVEIW_H__0072C659_5B4C_4AFA_A196_6C4528045A90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CScaleVeiwApp
// See ScaleVeiw.cpp for the implementation of this class
//

class CScaleVeiwApp : public CWinApp
{
public:
	CArray<DWORD,DWORD> m_threadArr;
	CScaleVeiwApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScaleVeiwApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CScaleVeiwApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

const double g_degtorad = asin(1.0) / 90.0;
const double g_radtodeg = 90.0 / asin(1.0);

#endif // !defined(AFX_SCALEVEIW_H__0072C659_5B4C_4AFA_A196_6C4528045A90__INCLUDED_)
