// MyBitmap.cpp: implementation of the CMyBitmap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ScaleVeiw.h"
#include "MyBitmap.h"
#include "DEFF.h"
#include ".\deff.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyBitmap::CMyBitmap(CMyBitmap &ob)
{
	if(ob.m_pWnd)
	{
		m_pWnd = ob.m_pWnd;
		CClientDC dc(m_pWnd);
		m_dc.CreateCompatibleDC(&dc);
		BITMAP bm;
		ob.GetBitmap(&bm);
		DWORD count = bm.bmWidthBytes * bm.bmHeight;
		LPBYTE buf = new BYTE[count];
		ob.GetBitmapBits(count, buf);
		bm.bmBits = buf;
		CreateBitmapIndirect(&bm);
		delete [] buf;
		m_oldBm = m_dc.SelectObject(this);
	}
}

CMyBitmap::CMyBitmap(CWnd *wnd):m_pWnd(wnd),
m_oldBm(NULL)
{
	if(m_pWnd)
	{
		CClientDC dc(m_pWnd);
		m_dc.CreateCompatibleDC(&dc);
	}
}

CMyBitmap::~CMyBitmap()
{
	if(m_oldBm)
		m_dc.SelectObject(m_oldBm);
}

bool CMyBitmap::CreateCompatibleBitmap(int cx, int cy)
{
	if(m_dc.GetSafeHdc() && m_pWnd)
	{
		CClientDC dc(m_pWnd);
		CBitmap::CreateCompatibleBitmap(&dc, cx,cy);
		m_oldBm = m_dc.SelectObject(this);
		return true;
	}
	return false;
}

bool CMyBitmap::CreateCompatibleBitmap(CWnd *wnd, int cx, int cy)
{
	m_pWnd = wnd;
	CClientDC dc(m_pWnd);
	m_dc.CreateCompatibleDC(&dc);

	return CreateCompatibleBitmap(cx, cy);
}

CDC* CMyBitmap::GetDC()
{
	return &m_dc;
}

void CMyBitmap::DrawTransparent(int x, int y, COLORREF maskCol, CDC *pDC)
{
	CClientDC dc(m_pWnd);
	BITMAP bm;
	GetBitmap(&bm);
	CMyBitmap bmCopy(*this);
	CMyBitmap bmMask;
	bmMask.CreateMask(bmCopy, maskCol);
	pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, bmMask, 0, 0, SRCAND);
	bmMask.GetDC()->PatBlt(0, 0, bm.bmWidth, bm.bmHeight, DSTINVERT);
	bmMask.Draw(bmCopy, SRCAND);
	pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, bmCopy, 0, 0, SRCPAINT);
}

void CMyBitmap::Draw(CDC *pDC, DWORD dwSop, int destx, int desty, int sourcex, int sourcey)
{
	BITMAP bm;
	GetBitmap(&bm);
	pDC->BitBlt(destx, desty, bm.bmWidth - sourcex, bm.bmHeight - sourcey, *this, sourcex, sourcey, dwSop);

}

void CMyBitmap::CreateMask(CMyBitmap &ob, COLORREF col)
{
	if(ob.m_pWnd)
	{
		m_pWnd = ob.m_pWnd;
		CClientDC dc(m_pWnd);
		m_dc.CreateCompatibleDC(&dc);		
		BITMAP bm;
		ob.GetBitmap(&bm);
		CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);
		m_oldBm = m_dc.SelectObject(this);
		COLORREF bkCol = ob.m_dc.SetBkColor(col);
		m_dc.BitBlt(0,0,bm.bmWidth, bm.bmHeight, ob, 0, 0, SRCCOPY);
		ob.m_dc.SetBkColor(bkCol);
	}
}

void CMyBitmap::DrawIcon(UINT unIcon, int x, int y, int cx, int cy)
{
	HICON hicon = (HICON)::LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(unIcon),
		IMAGE_ICON,
		cx,cy,
		LR_DEFAULTCOLOR);

	HDC htdc = m_dc.GetSafeHdc();

	::DrawState(htdc,NULL,NULL,(long)hicon,NULL,x,y,cx,cy,DST_ICON);
	
	::DestroyIcon(hicon);
}

//////////////////////////////////////////////////////////////////
//CMyFBitmap
/////////////////////////////////////////////////////////////////

CMyFBitmap::CMyFBitmap()
{
	m_Obm = NULL;
}

CMyFBitmap::~CMyFBitmap()
{
/*
	no such action needed !!!
	m_dcMem.SelectObject(m_Obm);

*/	
}

int CMyFBitmap::CreateMyCompatibleBitmap(CDC *pDC, int width, int height, COLORREF bkColor)
{
	m_width = width;
	m_height = height;
	int res;

	

	if(pDC == NULL){
		HDC hdc = ::GetDC(NULL);
		CDC dc;
		dc.Attach(hdc);
		CreateCompatibleBitmap(&dc, width, height);
		res = m_dcMem.CreateCompatibleDC(&dc);
	}
	else{
		CreateCompatibleBitmap(pDC, width, height);
		res = m_dcMem.CreateCompatibleDC(pDC);
	}

	m_br.CreateSolidBrush(bkColor);

	m_Obm = m_dcMem.SelectObject(this);


	return res;
}

BOOL CMyFBitmap::LoadMyBitmap(const CString& path)
{
	BOOL bl = LoadBitmap(path);
	BITMAP bm;
	GetBitmap(&bm);
	m_width = bm.bmWidth;
	m_height = bm.bmHeight;

	HDC hdc = ::GetDC(NULL);
	CDC dc;
	dc.Attach(hdc);
	m_dcMem.CreateCompatibleDC(&dc);
		
	m_Obm = m_dcMem.SelectObject(this);
	
	return bl;
}

BOOL CMyFBitmap::LoadMyBitmap(UINT nIDResource)
{
	BOOL bl = LoadBitmap(nIDResource);
	BITMAP bm;
	GetBitmap(&bm);
	m_width = bm.bmWidth;
	m_height = bm.bmHeight;

	HDC hdc = ::GetDC(NULL);
	CDC dc;
	dc.Attach(hdc);
	m_dcMem.CreateCompatibleDC(&dc);
		
	m_Obm = m_dcMem.SelectObject(this);
	
	return bl;
}


CDC* CMyFBitmap::GetMyPaintDC()
{
	m_dcMem.FillRect(CRect(0,0,m_width,m_height), &m_br);

	return &m_dcMem;
}

void CMyFBitmap::Draw(CDC *pDC, int x, int y, int fromx, int fromy)
{
	if(m_dcMem.GetSafeHdc() == NULL)
		return;
	pDC->BitBlt(x,y,m_width,m_height,&m_dcMem,fromx,fromy,SRCCOPY);
}

void CMyFBitmap::DrawSize(CDC *pDC, int cx, int cy, int fromx, int fromy)
{
	if(m_dcMem.GetSafeHdc() == NULL)
		return;
	pDC->BitBlt(0,0,cx,cy,&m_dcMem,fromx,fromy,SRCCOPY);
}

void CMyFBitmap::StrechDraw(CDC *pDC, int x, int y, int sx, int sy, int fromx, int fromy)
{
	if(m_dcMem.GetSafeHdc() == NULL)
		return;
	pDC->StretchBlt(x,y,sx,sy,&m_dcMem,fromx,fromx,m_width,m_height,SRCCOPY);
}


void CMyFBitmap::DrawTransparent(CDC *pDC, int x, int y, COLORREF crColor, int fromx, int fromy)
{
	if(m_dcMem.GetSafeHdc() == NULL)
		return;

	COLORREF crOldBack = pDC->SetBkColor(RGB(255,255,255));
	COLORREF crOldText = pDC->SetTextColor(RGB(0,0,0));
	CDC  dcTrans;

	// Create one memory for the mask
	//dcImage.CreateCompatibleDC(pDC);
	dcTrans.CreateCompatibleDC(pDC);

	// Select the image into the appropriate dc
//	CBitmap* pOldBitmapImage = dcImage.SelectObject(this);

	// Create the mask bitmap
	CBitmap bitmapTrans;
	int nWidth = m_width;
	int nHeight = m_height;
	bitmapTrans.CreateBitmap(nWidth, nHeight, 1, 1, NULL);

	// Select the mask bitmap into the appropriate dc
	CBitmap* pOldBitmapTrans = dcTrans.SelectObject(&bitmapTrans);

	// Build mask based on transparent colour
	m_dcMem.SetBkColor(crColor);
	dcTrans.BitBlt(0, 0, nWidth, nHeight, &m_dcMem, 0, 0, SRCCOPY);
	//pDC->BitBlt(x,y,nWidth,nHeight,&dcTrans,0,0,SRCCOPY);

	// Do the work - True Mask method - cool if not actual display
	pDC->BitBlt(x, y, nWidth, nHeight, &m_dcMem, 0, 0, SRCINVERT);
	pDC->BitBlt(x, y, nWidth, nHeight, &dcTrans, 0, 0, SRCAND);
	pDC->BitBlt(x, y, nWidth, nHeight, &m_dcMem, 0, 0, SRCINVERT);
//	pDC->BitBlt(x, y, nWidth, nHeight, &m_dcMem, 0, 0, SRCPAINT);

	// Restore settings
//	dcImage.SelectObject(pOldBitmapImage);
	dcTrans.SelectObject(pOldBitmapTrans);
	pDC->SetBkColor(crOldBack);
	pDC->SetTextColor(crOldText);

}

void CMyFBitmap::StrechTranspareDraw(CDC *pDC, int x, int y, int sx, int sy, COLORREF crColor)
{
	if(m_dcMem.GetSafeHdc() == NULL)
		return;

	COLORREF crOldBack = pDC->SetBkColor(RGB(255,255,255));
	COLORREF crOldText = pDC->SetTextColor(RGB(0,0,0));
	CDC  dcTrans, dcImage;

	// Create two memory dcs for the image and the mask
	dcImage.CreateCompatibleDC(pDC);
	dcTrans.CreateCompatibleDC(pDC);

	// Select the image into the appropriate dc
	CBitmap stach;
	stach.CreateCompatibleBitmap(pDC,sx,sy);
	CBitmap* pOldBitmapImage = dcImage.SelectObject(&stach);
	dcImage.StretchBlt(0,0,sx,sy,&m_dcMem,0,0,m_width,m_height,SRCCOPY);

	// Create the mask bitmap
	CBitmap bitmapTrans;
	int nWidth = sx;
	int nHeight = sy;
	bitmapTrans.CreateBitmap(nWidth, nHeight, 1, 1, NULL);

	// Select the mask bitmap into the appropriate dc
	CBitmap* pOldBitmapTrans = dcTrans.SelectObject(&bitmapTrans);

	// Build mask based on transparent colour
	dcImage.SetBkColor(crColor);
	dcTrans.BitBlt(0, 0, nWidth, nHeight, &dcImage, 0, 0, SRCCOPY);

	// Do the work - True Mask method - cool if not actual display
	pDC->BitBlt(x, y, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT);
	pDC->BitBlt(x, y, nWidth, nHeight, &dcTrans, 0, 0, SRCAND);
	pDC->BitBlt(x, y, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT);

	// Restore settings
	dcImage.SelectObject(pOldBitmapImage);
	dcTrans.SelectObject(pOldBitmapTrans);
	pDC->SetBkColor(crOldBack);
	pDC->SetTextColor(crOldText);


}

void CMyFBitmap::LoadIcon(UINT unIcon, int cx, int cy)
{
	HICON m_hicon = (HICON)::LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(unIcon),
		IMAGE_ICON,
		cx,cy,
		LR_DEFAULTCOLOR);

	CreateMyCompatibleBitmap(NULL,cx,cy,0xffffff);
	
	HDC htdc = m_dcMem.m_hDC;

	::DrawState(htdc,NULL,NULL,(long)m_hicon,NULL,0,0,cx,cy,DST_ICON);

	
	::DestroyIcon(m_hicon);

}


CMyFBitmap& CMyFBitmap::operator =(CMyFBitmap& ob)
{
	CreateMyCompatibleBitmap(ob, ob.m_width, ob.m_height);
	ob.Draw(*this, 0,0);
	return *this;
}



//////////////////////////////////////////////////////////////////////
// CMyFont Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyFont::CMyFont()
{

}

CMyFont::~CMyFont()
{
	int fSize = m_fontList.GetSize();
	for(int i = 0; i < fSize; i++){
		delete m_fontList.GetAt(i);
	}

	m_fontList.RemoveAll();

}

void CMyFont::LoadSource(UINT unSourceFont, int cx, int cy, COLORREF bk, COLORREF front)
{
	m_fontCx = cx;
	m_fontCy = cy;
	CMyFBitmap sorc;
	sorc.LoadMyBitmap(unSourceFont);
	BITMAP bm;
	sorc.GetBitmap(&bm);


	int nWidth = bm.bmWidth;
	int nHeight = bm.bmHeight;



	
	
	int fSize = m_fontList.GetSize();
	for(int i = 0; i < fSize; i++){
		delete m_fontList.GetAt(i);
	}
	m_fontList.RemoveAll();

	for(int line = 0; (cy + line) <= nHeight; line+= cy){
		for(int col = 0; (cx + col) <= nWidth; col+= cx){
			CMyFBitmap* font = new CMyFBitmap;
			font->CreateMyCompatibleBitmap(NULL,cx,cy,RGB(255,255,255));
			sorc.DrawSize(font->GetMyPaintDC(),cx,cy,col,line);
			m_fontList.Add(font);
		}

	}
}

void CMyFont::LoadSourceEx(UINT unSourceFont, int cx, int cy, COLORREF bk, COLORREF front)
{
	m_fontCx = cx;
	m_fontCy = cy;

	CBitmap bmBk;
	bmBk.LoadBitmap(unSourceFont);


	BITMAP bm;
	bmBk.GetBitmap(&bm);

	int nWidth = bm.bmWidth;
	int nHeight = bm.bmHeight;
	
	HDC hdc = ::GetDC(NULL);
	CDC dc;
	dc.Attach(hdc);
	CDC maskbkDC;
	maskbkDC.CreateCompatibleDC(&dc);

	CBitmap* Ombm = maskbkDC.SelectObject(&bmBk);

	CBitmap invbmBk;
	invbmBk.CreateCompatibleBitmap(&dc,nWidth,nHeight);
	CDC invmaskbkDC;
	invmaskbkDC.CreateCompatibleDC(&dc);

	CBitmap* Oinvmbm = invmaskbkDC.SelectObject(&invbmBk);

	invmaskbkDC.BitBlt(0,0,nWidth,nHeight,&maskbkDC,0,0,NOTSRCCOPY);

	CDC colorDC;
	colorDC.CreateCompatibleDC(&dc);
	CBitmap colorBm;
	colorBm.CreateCompatibleBitmap(&dc,nWidth,nHeight);
	CBitmap* OcolorBm = colorDC.SelectObject(&colorBm);
	CBrush BrBk(bk);
	CBrush BrFront(front);

	CRect rc(0,0,nWidth,nHeight);

	colorDC.FillRect(&rc,&BrBk);
	maskbkDC.BitBlt(0,0,nWidth,nHeight,&colorDC,0,0,SRCAND);

	colorDC.FillRect(&rc,&BrFront);
	invmaskbkDC.BitBlt(0,0,nWidth,nHeight,&colorDC,0,0,SRCAND);
	invmaskbkDC.BitBlt(0,0,nWidth,nHeight,&maskbkDC,0,0,SRCPAINT);

	CMyFBitmap sorc;

	sorc.CreateMyCompatibleBitmap(NULL,nWidth,nHeight,RGB(255,255,255));

	CDC* srcDC = sorc.GetMyPaintDC();

	srcDC->BitBlt(0,0,nWidth,nHeight,&invmaskbkDC,0,0,SRCCOPY);


	int fSize = m_fontList.GetSize();
	for(int i = 0; i < fSize; i++){
		delete m_fontList.GetAt(i);
	}
	m_fontList.RemoveAll();

	for(int line = 0; (cy + line) <= nHeight; line+= cy){
		for(int col = 0; (cx + col) <= nWidth; col+= cx){
			CMyFBitmap* font = new CMyFBitmap;
			font->CreateMyCompatibleBitmap(NULL,cx,cy,RGB(255,255,255));
			sorc.DrawSize(font->GetMyPaintDC(),cx,cy,col,line);
			m_fontList.Add(font);
		}

	}

	maskbkDC.SelectObject(Ombm);
	invmaskbkDC.SelectObject(Oinvmbm);
	colorDC.SelectObject(OcolorBm);

}

void CMyFont::DrawString(CDC *pDC, int x, int y, CString &str, BYTE sp)
{
	int strSize = str.GetLength();
	int px;
	

	for(int pos = 0; pos < strSize; pos++){
		px = (m_fontCx + sp) * pos + x;
		
		switch((BYTE)str.GetAt(pos)){
		case '0': m_fontList[0]->Draw(pDC,px,y);
			break;
		case '1': m_fontList[1]->Draw(pDC,px,y);
			break;
		case '2': m_fontList[2]->Draw(pDC,px,y);
			break;
		case '3': m_fontList[3]->Draw(pDC,px,y);
			break;
		case '4': m_fontList[4]->Draw(pDC,px,y);
			break;
		case '5': m_fontList[5]->Draw(pDC,px,y);
			break;
		case '6': m_fontList[6]->Draw(pDC,px,y);
			break;
		case '7': m_fontList[7]->Draw(pDC,px,y);
			break;
		case '8': m_fontList[8]->Draw(pDC,px,y);
			break;
		case '9': m_fontList[9]->Draw(pDC,px,y);
			break;
		case ' ': m_fontList[10]->Draw(pDC,px,y);
			break;
		case '-': m_fontList[11]->Draw(pDC,px,y);
			break;
		case '+': m_fontList[12]->Draw(pDC,px,y);
			break;
		case '°': m_fontList[13]->Draw(pDC,px,y);
			break;
		case '\'': m_fontList[14]->Draw(pDC,px,y);
			break;
		case '\"': m_fontList[15]->Draw(pDC,px,y);
			break;
		case '.': m_fontList[16]->Draw(pDC,px,y);
			break;
		case '*': m_fontList[17]->Draw(pDC,px,y);
			break;
		case '=': m_fontList[18]->Draw(pDC,px,y);
			break;
		case '/': m_fontList[19]->Draw(pDC,px,y);
			break;
		case 'a': m_fontList[20]->Draw(pDC,px,y);
			break;
		case 'b': m_fontList[21]->Draw(pDC,px,y);
			break;
		case 'c': m_fontList[22]->Draw(pDC,px,y);
			break;
		case 'd': m_fontList[23]->Draw(pDC,px,y);
			break;
		case 'e': m_fontList[24]->Draw(pDC,px,y);
			break;
		case 'f': m_fontList[25]->Draw(pDC,px,y);
			break;
		case 'g': m_fontList[26]->Draw(pDC,px,y);
			break;
		case 'h': m_fontList[27]->Draw(pDC,px,y);
			break;
		case 'i': m_fontList[28]->Draw(pDC,px,y);
			break;
		case 'j': m_fontList[29]->Draw(pDC,px,y);
			break;
		case 'k': m_fontList[30]->Draw(pDC,px,y);
			break;
		case 'l': m_fontList[31]->Draw(pDC,px,y);
			break;
		case 'm': m_fontList[32]->Draw(pDC,px,y);
			break;
		case 'n': m_fontList[33]->Draw(pDC,px,y);
			break;
		case 'o': m_fontList[34]->Draw(pDC,px,y);
			break;
		case 'p': m_fontList[35]->Draw(pDC,px,y);
			break;
		case 'q': m_fontList[36]->Draw(pDC,px,y);
			break;
		case 'r': m_fontList[37]->Draw(pDC,px,y);
			break;
		case 's': m_fontList[38]->Draw(pDC,px,y);
			break;
		case 't': m_fontList[39]->Draw(pDC,px,y);
			break;
		case 'u': m_fontList[40]->Draw(pDC,px,y);
			break;
		case 'v': m_fontList[41]->Draw(pDC,px,y);
			break;
		case 'w': m_fontList[42]->Draw(pDC,px,y);
			break;
		case 'x': m_fontList[43]->Draw(pDC,px,y);
			break;
		case 'y': m_fontList[44]->Draw(pDC,px,y);
			break;
		case 'z': m_fontList[45]->Draw(pDC,px,y);
			break;
		case h_al: m_fontList[46]->Draw(pDC,px,y);
			break;
		case h_be: m_fontList[47]->Draw(pDC,px,y);
			break;
		case h_g: m_fontList[48]->Draw(pDC,px,y);
			break;
		case h_d: m_fontList[49]->Draw(pDC,px,y);
			break;
		case h_he: m_fontList[50]->Draw(pDC,px,y);
			break;
		case h_v: m_fontList[51]->Draw(pDC,px,y);
			break;
		case h_z: m_fontList[52]->Draw(pDC,px,y);
			break;
		case h_het: m_fontList[53]->Draw(pDC,px,y);
			break;
		case h_tet: m_fontList[54]->Draw(pDC,px,y);
			break;
		case h_yod: m_fontList[55]->Draw(pDC,px,y);
			break;
		case h_haf: m_fontList[56]->Draw(pDC,px,y);
			break;
		case h_haf_s: m_fontList[57]->Draw(pDC,px,y);
			break;
		case h_la: m_fontList[58]->Draw(pDC,px,y);
			break;
		case h_me: m_fontList[59]->Draw(pDC,px,y);
			break;
		case h_me_s: m_fontList[60]->Draw(pDC,px,y);
			break;
		case h_n: m_fontList[61]->Draw(pDC,px,y);
			break;
		case h_n_s: m_fontList[62]->Draw(pDC,px,y);
			break;
		case h_sa: m_fontList[63]->Draw(pDC,px,y);
			break;
		case h_ayn: m_fontList[64]->Draw(pDC,px,y);
			break;
		case h_fe: m_fontList[65]->Draw(pDC,px,y);
			break;
		case h_fe_s: m_fontList[66]->Draw(pDC,px,y);
			break;
		case h_za: m_fontList[67]->Draw(pDC,px,y);
			break;
		case h_za_s: m_fontList[68]->Draw(pDC,px,y);
			break;
		case h_ko: m_fontList[69]->Draw(pDC,px,y);
			break;
		case h_re: m_fontList[70]->Draw(pDC,px,y);
			break;
		case h_shin: m_fontList[71]->Draw(pDC,px,y);
			break;
		case h_taf: m_fontList[72]->Draw(pDC,px,y);
			break;
		case '(': m_fontList[73]->Draw(pDC,px,y);
			break;
		case ')': m_fontList[74]->Draw(pDC,px,y);
			break;
		case ':': m_fontList[75]->Draw(pDC,px,y);
			break;
		case '<': m_fontList[76]->Draw(pDC,px,y);
			break;
		case '>': m_fontList[77]->Draw(pDC,px,y);
			break;
		case ',': m_fontList[78]->Draw(pDC,px,y);
			break;
		default: m_fontList[10]->Draw(pDC,px,y);
			break;
		}

	}
}


void CMyFont::DrawStrechString(CDC * pDC, int x, int y,
							   CString & str, int strechx,
							   int strechy)
{
	int len = str.GetLength();
	len *= m_fontCx;
	CMyFBitmap bm;
	bm.CreateMyCompatibleBitmap(NULL, len, m_fontCy);

	DrawString(bm.GetMyPaintDC(), 0, 0, str);

	bm.StrechDraw(pDC,x,y,strechx,strechy);
}

void CMyFont::DrawString(CDC * pDC, int x, int y, CString & str, COLORREF clTransperent)
{
	int strSize = str.GetLength();
	int px;
	

	for(int pos = 0; pos < strSize; pos++){
		px = m_fontCx * pos + x;
		
		switch((BYTE)str.GetAt(pos)){
		case '0': m_fontList[0]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '1': m_fontList[1]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '2': m_fontList[2]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '3': m_fontList[3]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '4': m_fontList[4]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '5': m_fontList[5]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '6': m_fontList[6]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '7': m_fontList[7]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '8': m_fontList[8]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '9': m_fontList[9]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case ' ': m_fontList[10]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '-': m_fontList[11]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '+': m_fontList[12]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '°': m_fontList[13]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '\'': m_fontList[14]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '\"': m_fontList[15]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '.': m_fontList[16]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '*': m_fontList[17]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '=': m_fontList[18]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '/': m_fontList[19]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'a': m_fontList[20]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'b': m_fontList[21]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'c': m_fontList[22]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'd': m_fontList[23]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'e': m_fontList[24]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'f': m_fontList[25]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'g': m_fontList[26]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'h': m_fontList[27]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'i': m_fontList[28]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'j': m_fontList[29]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'k': m_fontList[30]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'l': m_fontList[31]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'm': m_fontList[32]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'n': m_fontList[33]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'o': m_fontList[34]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'p': m_fontList[35]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'q': m_fontList[36]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'r': m_fontList[37]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 's': m_fontList[38]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 't': m_fontList[39]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'u': m_fontList[40]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'v': m_fontList[41]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'w': m_fontList[42]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'x': m_fontList[43]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'y': m_fontList[44]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case 'z': m_fontList[45]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_al: m_fontList[46]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_be: m_fontList[47]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_g: m_fontList[48]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_d: m_fontList[49]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_he: m_fontList[50]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_v: m_fontList[51]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_z: m_fontList[52]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_het: m_fontList[53]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_tet: m_fontList[54]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_yod: m_fontList[55]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_haf: m_fontList[56]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_haf_s: m_fontList[57]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_la: m_fontList[58]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_me: m_fontList[59]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_me_s: m_fontList[60]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_n: m_fontList[61]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_n_s: m_fontList[62]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_sa: m_fontList[63]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_ayn: m_fontList[64]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_fe: m_fontList[65]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_fe_s: m_fontList[66]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_za: m_fontList[67]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_za_s: m_fontList[68]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_ko: m_fontList[69]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_re: m_fontList[70]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_shin: m_fontList[71]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case h_taf: m_fontList[72]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '(': m_fontList[73]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case ')': m_fontList[74]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case ':': m_fontList[75]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '<': m_fontList[76]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case '>': m_fontList[77]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		case ',': m_fontList[78]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		default: m_fontList[10]->DrawTransparent(pDC,px,y,clTransperent);
			break;
		}

	}

}

void CMyFont::Create(COLORREF bk, COLORREF front, BOOL bSmall)
{
	if(bSmall)
		LoadSourceEx(IDB_BITMAP_FONT,7,11,bk,front);
	else
		LoadSourceEx(IDB_BITMAP_FONT1,9,14,bk,front);
}


