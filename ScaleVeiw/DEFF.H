

#if !defined(AFX_STDAFX_DEFF_H__0343E319_AA87_449A_9C91_A6DF0B9C2C79__INCLUDED_)
#define AFX_STDAFX_DEFF_H__0343E319_AA87_449A_9C91_A6DF0B9C2C79__INCLUDED_

#include <afxtempl.h>

#pragma warning(disable : 4251 4275 4309)

#ifndef INPORTEXPORT
#ifdef _USRDLL
#define INPORTEXPORT __declspec(dllexport)
#else
#define INPORTEXPORT __declspec(dllimport)
#endif
#endif

#define RGBT(r,g,b,t) RGB(r,g,b) | ((DWORD)(t) << 24)
#define RGBT2(c,t) c | ((DWORD)(t) << 24)

#define TURN_SIMPLE -1


enum
{
	cs_cx = 1024,
	cs_cy = 768
};

//#include ".\3dscreen.h"

enum eFiillRectOp
{
	fr_paint
	,fr_paintTranslated
	,fr_zIntensity
	,fr_zIntensityAll
	,fr_zSquareIntensity
	,fr_zAtIntensity
	,fr_yIntensity
	,fr_xyIntensity
	,fr_colIntensity
	,fr_shrink
	,fr_lightOppositeDirection
	,fr_lightOppositeDirectionBase
	,fr_lightDirection
	,fr_lightDirectionBase
	,fr_yLightOppositeDirection
	,fr_yLightOppositeDirectionBase
	,fr_yPaintLessThen
	,fr_yPaintLessThenBase
	,fr_PaintDiractionRange
};

enum
{
	BASIC_DLL_MSG = WM_USER + 10,
};

enum
{
	COMTOV_THREADID = 1,
	COMTOV_RESULT,
	COMTOV_SETCUPTURE,
	COMTOV_RELEASECUPTURE
};

enum
{
	VTOCOM_INIT = WM_APP + 10,
	VTOCOM_LDWN,
	VTOCOM_LUP,
	VTOCOM_DRAW,
	VTOCOM_MM,
	WM_ON_TRIGER_MSG,
	WM_GET_WND_RC
};

enum
{
	INIT_IMAGE		= 0X00000001,
	INIT_SPACES		= 0X00000002
};

enum
{
	image_class
	,image_yom
};

enum  INPORTEXPORT Axis
{
	axis_x = 0,
	axis_y = 1,
	axis_z = 2,
	axis_s = 3
};

#define	axis_X  (Axis)0
#define	axis_Y  (Axis)1
#define	axis_Z  (Axis)2
#define	axis_S  (Axis)3

struct INPORTEXPORT CFillRectData
{
	CFillRectData(double rad = 0.0)
		:radius(rad)
		,vec(4.0)
		,vec2(0)
		,color2(RGB(255,255,255))
		{}
	void operator = (const double &rad){radius = rad;}
	double radius;
	double vec;
	double vec2;
	COLORREF color2;
	struct P3d
	{
		P3d():x(0),y(0),z(-1.0){}
		double x;
		double y;
		double z;
	} p3d;
};


struct INPORTEXPORT CScaleResult
{
	CScaleResult():result(0.0),id(-1), val(0)
	{}
	double result;
	int id;
	unsigned long val;
};

struct INPORTEXPORT CInit
{
	CInit();
	~CInit();

	DWORD dwSpaces;
	DWORD dwFlags;
	CRect rc;
	int id;
	COLORREF brCol;
	COLORREF rgnCol;
	int pnStyle;
	int pnWidth;
	COLORREF pnCol;
	int deflate;
	double startang;
	double endang;
	double minval;
	double maxval;
	double startval;
	int image;
};


class INPORTEXPORT CScales
{
public:
	CScales(void);
	virtual ~CScales(void);
protected:
	struct ThreadInfo
	{
		unsigned int threadId;
		HANDLE hThread;		
	};
	CArray<ThreadInfo> m_threadArr;
	HWND m_hWnd;
public:
	void SetWind(HWND hWnd);
	bool InitScale(CInit& init);
	void Clean(void);
	void OnLButtonDown(POINT point);
	void OnLButtonUp(POINT point);
	void OnMouseMove(POINT point);
	void Paint(void);
};

enum He
{
	h_al = 224
	,h_be
	,h_g
	,h_d
	,h_he
	,h_v
	,h_z
	,h_het
	,h_tet
	,h_yod
	,h_haf_s
	,h_haf
	,h_la
	,h_me_s
	,h_me
	,h_n_s
	,h_n
	,h_sa
	,h_ayn
	,h_fe_s
	,h_fe
	,h_za_s
	,h_za
	,h_ko
	,h_re
	,h_shin
	,h_taf
};

class INPORTEXPORT CMyFBitmap : public CBitmap  
{
public:
	operator CDC*(){return &m_dcMem;}
	void LoadIcon(UINT unIcon, int cx = 16, int cy = 16);
	void DrawSize(CDC *pDC, int cx, int cy, int fromx = 0, int fromy = 0);
	BOOL LoadMyBitmap( UINT nIDResource );
	void StrechTranspareDraw(CDC *pDC, int x, int y, int sx, int sy, COLORREF crColor);
	void DrawTransparent(CDC *pDC, int x, int y,   COLORREF clrTransparency, int fromx = 0, int fromy = 0);
	void StrechDraw(CDC *pDC, int x, int y, int sx, int sy, int fromx = 0, int fromy = 0);
	void Draw(CDC* pDC, int x, int y, int fromx = 0, int fromy = 0);
	CDC* GetMyPaintDC();
	int CreateMyCompatibleBitmap(CDC* pDC, int width, int height, COLORREF bkColor = 0xffffff);
	CMyFBitmap();
	virtual ~CMyFBitmap();

protected:
	int m_height;
	int m_width;
	CBrush m_br;
	CDC m_dcMem;
	CBitmap* m_Obm;
public:
	CMyFBitmap& operator =(CMyFBitmap& ob);

	CMyFBitmap(CMyFBitmap& ob)
	{
		*this = ob;
	}
	friend class C3DScreen;
	friend class C3DObject;
	BOOL LoadMyBitmap(const CString& path);
};

class INPORTEXPORT CMyFont  
{
public:
	void DrawString(CDC *pDC, int x, int y, CString &str, COLORREF clTransperent);
	void DrawStrechString(CDC *pDC, int x, int y, CString &str, int strechx, int strechy);
	void LoadSourceEx(UINT unSourceFont, int cx = 9, int cy = 14, COLORREF bk = 0xffffff, COLORREF front = 0);
	void DrawString(CDC* pDC, int x, int y, CString& str, BYTE sp = 0);
	void LoadSource(UINT unSourceFont, int cx = 9, int cy = 14, COLORREF bk = 0xffffff, COLORREF front = 0);
	CMyFont();
	virtual ~CMyFont();

protected:
	int m_fontCy;
	int m_fontCx;
	CArray <CMyFBitmap*, CMyFBitmap*> m_fontList;

public:
	void Create(COLORREF bk = 0xffffff, COLORREF front = 0, BOOL bSmall = FALSE);
};


#endif //AFX_STDAFX_DEFF_H__0343E319_AA87_449A_9C91_A6DF0B9C2C79__INCLUDED_