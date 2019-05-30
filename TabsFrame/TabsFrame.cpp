// TabsFrame.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "MainFrm.h"

#include "ButtonEx.h"
#include "ToolExBar.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

struct CFontFile
{
	CString font;
	CString file;
};

const int fontArrLength = 3;

CFontFile fontsArr[fontArrLength] =
{
	{"Guttman Stam", "STAM.TTF"}
	,{"Tahoma", "TAHOMA.TTF"}
	,{"Guttman Miryam Bold", "MIRB.TTF"}
};

// CTabsFrameApp

BEGIN_MESSAGE_MAP(CTabsFrameApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CTabsFrameApp::OnAppAbout)
END_MESSAGE_MAP()


// CTabsFrameApp construction

CTabsFrameApp::CTabsFrameApp()
: m_appPath(_T(""))
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTabsFrameApp object

CTabsFrameApp theApp;



// CTabsFrameApp initialization

BOOL CTabsFrameApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	CString sPath;
	char *buf = m_appPath.GetBuffer(100);
	::GetModuleFileName(NULL, buf, 99);
	m_appPath.ReleaseBuffer();
	int pos = m_appPath.ReverseFind('\\');
	m_appPath = m_appPath.Left(pos + 1);


	if(InstallNeededFonts() == FALSE)
		return FALSE;

	CFile f;
	CString sFn = m_appPath + "HeadLines.hld";
	f.Open(sFn, CFile::modeRead);
	CArchive ar(&f, CArchive::load);
	m_chaptersParagraphs.Load(ar);


	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Thonat Shamaim"));
	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);






	// The one and only window has been initialized, so show and update it
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}


// CTabsFrameApp message handlers




// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CTabsFrameApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CTabsFrameApp message handlers
int CTabsFrameApp::CreateToolBm2(int idx, int nWidth, CDC* pDC
								, CToolBar &toolBar
								, UINT nIdCommand)
{
	CChapPage& cp = m_chaptersParagraphs.m_chapPageArr[idx];

	int size = (int)cp.paragraphs.GetCount();
	int btnWidth = nWidth * size;
	CToolExBar* ptool = (CToolExBar*)&toolBar;

	ptool->m_pBitmap = new CBitmap[size + 1];
//	*newBm = new CBitmap[size + 1];

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	int i = 0;
	CRect rc(0,0,nWidth,15);

	for(; i < size; ++i)
	{
		ptool->m_pBitmap[i].CreateCompatibleBitmap(pDC, nWidth, 15);
		CBitmap *pOld = dc.SelectObject(&ptool->m_pBitmap[i]);
		COLORREF color = cp.paragraphs[i].color;
		CBrush br(color);
		dc.FillRect(rc, &br);		

		dc.SelectObject(pOld);
	}
	ptool->m_pBitmap[i].CreateCompatibleBitmap(pDC, nWidth, 15);
	CToolBarCtrl &tool = toolBar.GetToolBarCtrl();
	CSize size2(nWidth, 15);
	tool.SetBitmapSize(size2);
	size2 += CSize(8, 7);
	tool.SetButtonSize(size2);
	toolBar.SetBitmap(ptool->m_pBitmap[size]);

	TBBUTTON tb;
	memset(&tb, 0, sizeof(tb));
	tb.fsStyle = TBSTYLE_BUTTON;
	tb.fsState = TBSTATE_ENABLED;
	tb.iString = -1;
	for(i = 0; i < 2; ++i)
	{
		tb.iBitmap = 0;
		tb.idCommand = nIdCommand + i;
		tool.InsertButton(i, &tb);
	}
	toolBar.SetButtonInfo(0, nIdCommand,  TBBS_SEPARATOR, nWidth);

	ptool->m_btnsCount = size;
	ptool->m_pButtons = new CButtonEx[size];
	for(int y = 0, i =0; i < size; ++i, y+= size2.cx)
	{
		ptool->m_pButtons[i].Create(NULL, WS_CHILD | WS_VISIBLE | BS_BITMAP 
			| BS_OWNERDRAW /*|  BS_3STATE | BS_PUSHLIKE*/
			,CRect(y,0,nWidth,size2.cy),&toolBar, nIdCommand + i);
		ptool->m_pButtons[i].SetBitmap(ptool->m_pBitmap[i]);
	}

	tool.HideButton(1);
	return 0;
}


int CTabsFrameApp::CreateToolBm(int idx, int nWidth, CBitmap& newBm, CDC* pDC
								, CToolBar &toolBar
								, UINT nIdCommand)
{
	CChapPage& cp = m_chaptersParagraphs.m_chapPageArr[idx];

	int size = (int)cp.paragraphs.GetCount();
	int btnWidth = nWidth * size;
	newBm.CreateCompatibleBitmap(pDC, btnWidth, 15);

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap *pOld = dc.SelectObject(&newBm);
	int i = 0;
	for(int x = 0; i < size; ++i, x += nWidth)
	{
		CRect rc(x,0, x+nWidth, 15);
		COLORREF color = cp.paragraphs[i].color;
		CBrush br(color);
		dc.FillRect(rc, &br);		
	}
	dc.SelectObject(pOld);
	CToolBarCtrl &tool = toolBar.GetToolBarCtrl();
	CSize size2(nWidth, 15);
	tool.SetBitmapSize(size2);
	size2 += CSize(8, 7);
	tool.SetButtonSize(size2);
	toolBar.SetBitmap(newBm);
	TBBUTTON tb;
	memset(&tb, 0, sizeof(tb));
	tb.fsStyle = TBSTYLE_BUTTON;
	tb.fsState = TBSTATE_ENABLED;
	tb.iString = -1;
	for(i = 0; i < size; ++i)
	{
		tb.iBitmap = i;
		tb.idCommand = nIdCommand + i;
		tool.InsertButton(i, &tb);
	}

	return 0;
}

#pragma warning( disable : 4996 )

BOOL CTabsFrameApp::InstallNeededFonts(void)
{
	CMapStringToString fontMap;
	CDC dc;
	dc.CreateCompatibleDC(NULL);
	for(int i = 0; i < fontArrLength; ++i)
	{
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));
		lf.lfCharSet = HEBREW_CHARSET;
		strcpy(lf.lfFaceName, fontsArr[i].font);

		::EnumFontFamiliesEx(dc.GetSafeHdc(), &lf, 
			(FONTENUMPROC )EnumFontFamExProc, 
			(LPARAM)&fontMap, 0);

		CString sFaceName = fontsArr[i].font;
		CFont font;
		CString val;
		BOOL bRes = fontMap.Lookup(sFaceName, val);
		if(bRes == FALSE)
		{
			CString szPath = _tgetenv("windir");
			CString sDest = szPath + "\\Fonts\\" + fontsArr[i].file;
			CString sSrc = m_appPath + "Fonts\\" + fontsArr[i].file;
			bRes = CopyFile(sSrc, sDest, FALSE);

			if(bRes)
			{
				::AddFontResourceA((LPCSTR)(LPCTSTR)sDest);
				SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
			}

			if(bRes == FALSE)
			{
				CString sMsg;
				sMsg.Format("Failed to copy file %s of Font face %s",
					fontsArr[i].file, fontsArr[i].font);
				AfxMessageBox(sMsg);
			}
		}
	}
	return TRUE;
}

int CALLBACK CTabsFrameApp::EnumFontFamExProc(ENUMLOGFONTEX* lpelfe, NEWTEXTMETRICEX* lpntme, WORD fontType, LPARAM lParam)
{
	CMapStringToString& fontMap = *((CMapStringToString*)lParam);
	CString sName = (LPSTR)lpelfe->elfLogFont.lfFaceName;
	fontMap[sName] = sName;
	CString sFullName = (LPCTSTR)lpelfe->elfFullName;
	if(sName != sFullName)
	{
		fontMap[sFullName] = sFullName;
	}
	return 0;
}
