// ScaleVeiw.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "ScaleVeiw.h"
#include "ScaleCtrl.h"
#include ".\scaleveiw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CScaleVeiwApp

BEGIN_MESSAGE_MAP(CScaleVeiwApp, CWinApp)
	//{{AFX_MSG_MAP(CScaleVeiwApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScaleVeiwApp construction

CScaleVeiwApp::CScaleVeiwApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CScaleVeiwApp object

CScaleVeiwApp theApp;


BOOL CScaleVeiwApp::InitInstance() 
{
//	DWORD id = GetCurrentThreadId();
//	::PostThreadMessage(id,BASIC_DLL_MSG, 10,10);
	// TODO: Add your specialized code here and/or call the base class
	
	return CWinApp::InitInstance();
}


int CScaleVeiwApp::ExitInstance() 
{
	int size = m_threadArr.GetSize();
	for(int i = 0; i < size; i++)
		::PostThreadMessage(m_threadArr[i], WM_QUIT, 0 ,0);
	
	return CWinApp::ExitInstance();
}

/*
__declspec(dllexport) unsigned int  InitScale(HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	UINT thid = 0;
	DWORD hTread = ::_beginthreadex(NULL, 0, CScaleCtrl::RunCtrl, hWnd, 0, &thid);

	theApp.m_threadArr.Add(thid);

//	::SendMessage(hWnd,BASIC_DLL_MSG, COMTOV_THREADID, thid);
	Sleep(0);

	return thid;
}

__declspec(dllexport) void CLOnLButtonDown(POINT point)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	static CPoint pt;
	pt = point;
	int size = theApp.m_threadArr.GetSize();
	for(int i = 0; i < size; i++)
		PostThreadMessage(theApp.m_threadArr[i], VTOCOM_LDWN, (WPARAM)&pt,0);
}

__declspec(dllexport) void CLOnMouseMove(POINT point)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	static CPoint pt;
	pt = point;
	int size = theApp.m_threadArr.GetSize();
	for(int i = 0; i < size; i++)
		PostThreadMessage(theApp.m_threadArr[i], VTOCOM_MM, (WPARAM)&pt,0);

}

__declspec(dllexport) void CLOnLButtonUp(POINT point)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int size = theApp.m_threadArr.GetSize();
	for(int i = 0; i < size; i++)
		PostThreadMessage(theApp.m_threadArr[i], VTOCOM_LUP, 0,0);

}

__declspec(dllexport) void CLPaint()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int size = theApp.m_threadArr.GetSize();
	for(int i = 0; i < size; i++)
		PostThreadMessage(theApp.m_threadArr[i], VTOCOM_DRAW, 0,0);

}

__declspec(dllexport) void CLClean()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int size = theApp.m_threadArr.GetSize();
	for(int i = 0; i < size; i++)
	{
		PostThreadMessage(theApp.m_threadArr[i], WM_QUIT, 0,0);
		Sleep(5);

	}

}
*/
