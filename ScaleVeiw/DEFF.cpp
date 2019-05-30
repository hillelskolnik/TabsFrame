

#include "stdafx.h"
#include ".\3dobject.h"
#include ".\deff.h"
#include "ScaleCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CInit::CInit():rc(0,0,0,0),id(0),brCol(RGB(206,0,206)),rgnCol(RGB(206,64,206)),
		pnStyle(PS_SOLID),pnWidth(2),
		pnCol(RGB(255,0,0)),deflate(18),startang(0.0),
		endang(360.0),minval(0.0),maxval(360.0),
		startval(0.0),dwFlags(0),dwSpaces(1)
		, image(0)
{
}

CInit::~CInit()
{
}


CScales::CScales(void)
:m_hWnd(NULL)
{
}

CScales::~CScales(void)
{
	Clean();
}

void CScales::SetWind(HWND hWnd)
{
	m_hWnd = hWnd;
}

bool CScales::InitScale(CInit& init)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(m_hWnd == NULL)
		return false;


	UINT thid = 0;
	HANDLE hTread = (HANDLE)::_beginthreadex(NULL, 0, CScaleCtrl::RunCtrl, m_hWnd, 0, &thid);
	CScales::ThreadInfo info = {thid, hTread};
	m_threadArr.Add(info);

	CString str;
	str.Format("GetCurrentThreadId(%d)", thid);
	HANDLE hEv = CreateEvent(NULL, TRUE, FALSE, str);
	DWORD hr = WaitForSingleObject(hEv, INFINITE);

	CInit *pinit = new CInit();
	*pinit = init;
	Sleep(50);
	BOOL res = PostThreadMessage(thid, VTOCOM_INIT, (WPARAM)pinit,0);

	CloseHandle(hEv);// WAIT_OBJECT_0
	
	return true;
}

void CScales::Clean(void)
{
	int size = m_threadArr.GetSize();
	for(int i = 0; i < size; i++)
	{
		PostThreadMessage(m_threadArr[i].threadId, WM_QUIT, 0,0);
		WaitForSingleObject(m_threadArr[i].hThread, 100);
	}
	m_threadArr.RemoveAll();
}

void CScales::OnLButtonDown(POINT point)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	static CPoint pt;
	pt = point;
	int size = m_threadArr.GetSize();
	for(int i = 0; i < size; i++)
		PostThreadMessage(m_threadArr[i].threadId, VTOCOM_LDWN, (WPARAM)&pt,0);
}

void CScales::OnLButtonUp(POINT point)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int size = m_threadArr.GetSize();
	for(int i = 0; i < size; i++)
		PostThreadMessage(m_threadArr[i].threadId, VTOCOM_LUP, 0,0);
}

void CScales::OnMouseMove(POINT point)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	static CPoint pt;
	pt = point;
	int size = m_threadArr.GetSize();
	for(int i = 0; i < size; i++)
		PostThreadMessage(m_threadArr[i].threadId, VTOCOM_MM, (WPARAM)&pt,0);
}

void CScales::Paint(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int size = m_threadArr.GetSize();
	for(int i = 0; i < size; i++)
		PostThreadMessage(m_threadArr[i].threadId, VTOCOM_DRAW, 0,0);
}
