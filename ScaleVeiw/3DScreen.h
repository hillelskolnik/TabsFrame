#pragma once

#include "3dobject.h"
#include "afxwin.h"
#include "atltypes.h"
#include "afxmt.h"

enum ScreenBorder
{
	sb_left = 0,
	sb_top,
	sb_right,
	sb_bottom
};

#define OB_PAUSE -2

class CSimulation;

class INPORTEXPORT C3DScreen
{
public:
	friend class CSimulation;
	C3DScreen(void);
	~C3DScreen(void);
	// Set the screen border to place in the 3d screen
	bool SetRelativeEdge(int edge, ScreenBorder sb);
protected:
	enum
	{
		sc_ScreenToDC = WM_USER + 10,
		sc_Translate3Dto2D,
		sc_TurnShape,
		sc_TurnObjectCenter,
		sc_ShiftObjectCenter,
		sc_ResetShift,
		sc_ResetTranslation,
		sc_PaintTansparent,
		sc_CreatObjectPixselMap,
		sc_FillRect,
		sc_CreateSphereObject,
		sc_CreateCylinderObject,
		sc_OnPaint,
		sc_BitmapToObject,
		sc_CreateFlatSpiralObject,
		sc_CReateCircleLineObject,
		sc_DeleteObject,
		sc_TrigerPaintAlow,
		sc_CreateFlatBmObj,
		sc_CreateSphereBmObj,
		sc_TurnLightPt,
		sc_InitMatrix,
		sc_TurnMatrix,
		sc_Transform
	};
	tdPixselArr m_pixselArr;
	int m_edgeLeft;
	int m_edgeTop;
	int m_edgeReight;
	int m_edgeBottom;
public:
	// Set logic image pixsel size
	bool SetSceenSize(int cx, int cy, double yEngle, double nearPlane, double farPlane);
protected:
	unsigned long m_tansparentColpr;
public:
	void SetScreenTransparentColor(unsigned long color);
protected:
	CScreenPixsel* m_pPixelBuf;
	void PaintTansparent(void);
	// The field of view angle, in degrees, in the y-direction.
	double m_yEngle;
	// Use as Transform vector to convert x and y to logic screen
	// Map for 3Ds objects
	td3DObjectMap m_3DObjectMap;
	// Main thread handle
	HANDLE m_hThread;
public:
	// Tread loop run in this function
	void Run(void);
protected:
	// The thread id
	unsigned int m_uiThreadId;
public:
	// Static function for running thread
	static unsigned int __stdcall SRun(void* lpVoid);
protected:
	C3DObject* m_currentObject;
public:
	// Create new object if not exist and set it curent
	bool BeginObject(int id);
	// The transColor is an RBG and last byte is a transparency of the color 0 no transparency 100 full transparency.
	bool CreatObjectPixselMap(int cx, int cy, unsigned long transColor = 0x64000000, int num = 1);
	// filling color acording the position in the memory x y arrays
	bool FillRect(int x, int y, int cx, int cy, unsigned long color, 
		eFiillRectOp op = fr_paint, CFillRectData data = 0.0);
	void ResetShift(void);
	void ResetTranslation(void);
	void ShiftObjectCenter(double shift, Axis ax, bool bBase = false);
	void TurnObjectCenter(double angle, Axis ax, bool bBase = false);
	bool TurnShape(double angle = 0.0, Axis ax = axis_y, int bLastTurn = true,
		bool bBase = false);
	bool Translate3Dto2D(BOOL bDoObTrans = TRUE,
		int xStart = 0, int xStopSize = -1);
protected:
	CWnd* m_pWnd;
public:
	void SetScreenWnd(CWnd* pWnd);
	bool ScreenToDC(BOOL bPaintRefresh = FALSE);
protected:
	// the dib bits
	RGBQUAD* m_pDibBits;
	// dib bitmap handle
	HBITMAP m_hbm;
	HBITMAP m_hbmOld;
	CDC m_dibDC;
public:
	bool CreateScreenDC(void);
protected:
	void DeleteGdiObjects(void);
	CScreenInfo m_info;
	void thScreenToDC(BOOL bPaintRefresh);
	void thTranslate3Dto2D(C3DObject* ob, BOOL bDoObTrans,
		int xStart, int xStopSize);
	void thTurnShape(double angle, Axis ax, int bLastTurn, 
		bool bBase, C3DObject* ob);
	void thTurnObjectCenter(double angle, Axis ax, bool bBase, C3DObject* ob);
	void thShiftObjectCenter(double angle, Axis ax, bool bBase, C3DObject* ob);
	void thResetShift(C3DObject* ob);
	void thResetTranslation(C3DObject* ob);
	void thBeginObject(int id);
	void thCreatObjectPixselMap(int cx, int cy, unsigned long transColor, C3DObject* ob, int num);
	void thFillRect(int x, int y, int cx, int cy, unsigned long color, C3DObject* ob,
		eFiillRectOp op, CFillRectData data);
	// // flag to get out of thread loop when closing
	volatile bool m_bQuit;
public:
	// 3 <= diameter, 0 < circle <= 360, -90 <= bottom < top <= 90
	bool CreateSphereObject(int diameter, 
		unsigned long color, 
		double circle = 360.0, 
		double top = 90.0, 
		double bottom = -90.0
		, double fine = 1.0);

	void thCreateSphereObject(int diameter, 
		unsigned long color, 
		double circle, double top, double bottom, double fine, C3DObject* ob);
	void ClearScreen(void);
protected:
	tdPixselArr m_clearingArr;
public:
	bool CreateCylinderObject(int topDiameter, int bottomDiameter, 
		int height, unsigned long color, 
		double circle = 360.0, double fine = 1.0);
protected:
	void thCreateCylinderObject(int topDiameter, int bottomDiameter, 
		int height, unsigned long color, double circle, double fine, 
		C3DObject* ob);
	CRect m_rasterRc;
	//CRect GetDestinationRect(void);
public:
	void OnPaint(void);
	CMyFBitmap m_refreshDC;
protected:
	void thOnPaint(void);
public:
	void CopyRefreshToDib(void);
protected:
	CCriticalSection m_cs;
public:
	void BitmapToObject(CMyFBitmap& bm, COLORREF transperant = 0);
	void thBitmapToObject(CMyFBitmap& bm, COLORREF transperant, C3DObject* ob);
	static void TurnPoint(C3DPoint& p, double angle, Axis ax);
	bool CreateFlatSpiralObject(int width, int height, int space, int minRadius, double circle, unsigned long col);
	void thCreateFlatSpiralObject(int width, int height, int space, int minRadius, double circle, unsigned long col, C3DObject* ob);
	void CReateCircleLineObject(int diameter, unsigned long color, double fine = 1.0, double circle = 360.0, int num = 1);
	void thCReateCircleLineObject(int diameter, unsigned long color, double fine, double circle, int num, C3DObject* ob);
public:
	bool DeleteObject(int id);
public:
	bool thDeleteObject(int id);
protected:
	bool m_bNotPaint;
public:
	void NoPaint(void);
public:
	void TrigerPaintAlow(WPARAM wParam = 0, LPARAM lParam = 0);
public:
	void thTrigerPaintAlow(WPARAM wParam, LPARAM lParam);
public:
	void CopyRefresh(CRect& rc);
public:
	double GetTransformVector(void);
public:
	double GetMiddleZ(void);
public:
	void CreateSphereBmObj(int diameter, CMyFBitmap& bm, double top=90, double bottom=-90, unsigned long transperantcol = 0);
	void thCreateSphereBmObj(int diameter, CMyFBitmap& bm, double top, 
		double bottom, unsigned long transperantcol, C3DObject* ob);
public:
	void CreateFlatBmObj(CMyFBitmap& bm, unsigned long transperant = 0);
public:
	void thCreateFlatBmObj(CMyFBitmap& bm, unsigned long transperant, C3DObject* ob);
public:
	void TurnLightPt(double angle, Axis ax, bool bReset = false);
	void thTurnLightPt(double angle, Axis ax, bool bReset, C3DObject* ob);
public:
	void thInitMatrix(C3DObject* ob);
public:
	void InitMatrix(void);
public:
	void TurnMatrix(double angle, Axis ax);
public:
	void thTurnMatrix(double angle, Axis ax, C3DObject* ob);
public:
	void Transform(bool bWorldTranslation = true);
public:
	void thTransform(C3DObject* ob, bool bWorldTranslation);
};
