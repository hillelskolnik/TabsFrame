// MyBitmap.h: interface for the CMyBitmap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYBITMAP_H__21AC67A1_E659_406B_911D_73F0717A2966__INCLUDED_)
#define AFX_MYBITMAP_H__21AC67A1_E659_406B_911D_73F0717A2966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyBitmap : public CBitmap  
{
public:
	void DrawIcon(UINT unIcon, int x = 0, int y = 0, int cx = 32, int cy = 32);
	void CreateMask(CMyBitmap &ob, COLORREF col);
	void Draw(CDC *pDC, DWORD dwSop = SRCCOPY, int destx = 0, int desty = 0, int sourcex = 0, int sourcey = 0);
	void DrawTransparent(int x, int y, COLORREF maskCol, CDC *pDC);
	CDC* GetDC();
	bool CreateCompatibleBitmap(CWnd *wnd, int cx, int cy);
	bool CreateCompatibleBitmap(int cx, int cy);
	CMyBitmap(CWnd *wnd = NULL);
	CMyBitmap(CMyBitmap &ob);
	virtual ~CMyBitmap();
	operator CDC* () {return &m_dc;}

protected:
	CBitmap* m_oldBm;
	CDC m_dc;
	CWnd* m_pWnd;
};


#endif // !defined(AFX_MYBITMAP_H__21AC67A1_E659_406B_911D_73F0717A2966__INCLUDED_)
