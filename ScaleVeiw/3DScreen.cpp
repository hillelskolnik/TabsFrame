//#include "3DScreen.h"
//#include "3DScreen.h"
//#include "3DScreen.h"
//#include "3DScreen.h"
//#include "3DScreen.h"


#include "stdafx.h"
#include "ScaleVeiw.h"
#include ".\3dscreen.h"
//#include "DEFF.H"

C3DScreen::C3DScreen(void)
: m_edgeLeft(0)
, m_edgeTop(0)
, m_edgeReight(0)
, m_edgeBottom(0)
, m_tansparentColpr(0x64000000)
, m_pPixelBuf(NULL)
, m_yEngle(0)
,m_hThread(NULL)
, m_uiThreadId(0)
, m_currentObject(NULL)
, m_pWnd(NULL)
, m_pDibBits(NULL)
,m_bQuit(false)
, m_bNotPaint(false)
{
	m_hThread = (HANDLE)::_beginthreadex(NULL, 0, SRun, this, 0, &m_uiThreadId);

	CString str;
	str.Format("GetCurrentThreadId(%d)", m_uiThreadId);
	HANDLE hEv = CreateEvent(NULL, TRUE, FALSE, str);
	DWORD hr = WaitForSingleObject(hEv, INFINITE);

	Sleep(50);
}

C3DScreen::~C3DScreen(void)
{
	m_bQuit = true;
	::PostThreadMessage(m_uiThreadId, WM_QUIT, 0, 0);
	::WaitForSingleObject(m_hThread, 1500);

	POSITION pos = m_3DObjectMap.GetStartPosition();
	int key = -1;
    C3DObject* ob = NULL;
	while(pos != NULL)
	{
		m_3DObjectMap.GetNextAssoc(pos, key, ob);
		delete ob;
	}

	m_pixselArr.RemoveAll();
	DeleteGdiObjects();
//	delete [] m_pDibBits;
}

bool C3DScreen::SetRelativeEdge(int edge, ScreenBorder sb)
{
	switch(sb)
	{
	case sb_left:
		if((edge + m_edgeReight) >= 1.0)
			return false;
		m_edgeLeft = edge;
		break;
	case sb_top:
		if((edge + m_edgeBottom) >= 1.0)
			return false;
		m_edgeTop = edge;
		break;
	case sb_right:
		if((edge + m_edgeLeft) >= 1.0)
			return false;
		m_edgeReight = edge;
		break;
	case sb_bottom:
		if((edge + m_edgeTop) >= 1.0)
			return false;
		m_edgeBottom = edge;
		break;
	}
	return true;
}

// Set logic image pixsel size
bool C3DScreen::SetSceenSize(int cx, int cy, double yEngle, double nearPlane, double farPlane)
{
	if(cx <= 0 || cy <= 0 || yEngle <= 0.0 || yEngle >= 90.0 ||
		nearPlane <= 0.0 || farPlane <= 0.0 || farPlane <= nearPlane)
		return false;

	double fullRatio = farPlane / nearPlane;
	m_info.cx = (int)(float)((double)(float)cx * fullRatio); 
	m_info.cy = (int)(float)((double)(float)cy * fullRatio); 
	m_rasterRc.SetRect(m_info.cx, m_info.cy, 0, 0);
	// fix ratio
	//fullRatio = (double)(float)m_cy / (double)(float)cy;

	m_info.middleSpace.x = (double)(float)m_info.cx / 2.0;
	m_info.middleSpace.y = (double)(float)m_info.cy / 2.0;

	// find ratio in middle way between far and near
	double halfWay = (nearPlane + farPlane) / 2.0;
	double halfRatio = halfWay / nearPlane;

	double cotangHalfYEngle = 1.0 / tan((yEngle / 2.0) * g_degtorad);
	m_info.middleSpace.z = halfRatio * cotangHalfYEngle * 
		((double)(float)cy / 2.0);

	// Use as Transform vector to convert x and y to logic screen
	// TransformVector / z * (x or y)
	m_info.TransformVector = cotangHalfYEngle * 
		((double)(float)cy / 2.0) * fullRatio;

	double zRadius = m_info.TransformVector - m_info.middleSpace.z;
	m_info.Near = m_info.middleSpace.z - zRadius;

	DeleteGdiObjects();
	m_pixselArr.RemoveAll();
	m_clearingArr.RemoveAll();
	m_clearingArr.SetSize(m_info.cx);
	m_pixselArr.SetSize(m_info.cx*m_info.cy);
	m_pPixelBuf = m_pixselArr.GetData();
	m_clearingArr.SetSize(m_info.cx);
	int size = m_clearingArr.GetCount();
	CScreenPixsel* p = m_clearingArr.GetData();
	for(register int i = 0; i < size; ++i, ++p)
		p->color = m_tansparentColpr;
		


	return true;
}

void C3DScreen::SetScreenTransparentColor(unsigned long color)
{
	m_tansparentColpr = color;
	m_tansparentColpr |= 0x64000000;
	int size = m_clearingArr.GetCount();
	CScreenPixsel* p = m_clearingArr.GetData();
	for(register int i = 0; i < size; ++i, ++p)
		p->color = m_tansparentColpr;

	p = m_clearingArr.GetData();

	CScreenPixsel* pixselBuf = m_pPixelBuf;
	int rowSize = m_info.cx * sizeof(CScreenPixsel);
	for(register int y = 0; y < m_info.cy; ++y, pixselBuf += m_info.cx)
        memcpy(pixselBuf, p, rowSize);

}

void C3DScreen::PaintTansparent(void)
{
	RGBQUAD* pCol = NULL;
	BYTE c[4] = {0,0,0,0};

	POSITION pos = m_3DObjectMap.GetStartPosition();
	int key = -1;
    C3DObject* ob = NULL;
	m_rasterRc.SetRect(m_info.cx, m_info.cy, 0, 0);
	while(pos != NULL)
	{
		m_3DObjectMap.GetNextAssoc(pos, key, ob);

		if(ob->m_bPause)
			continue;
		
		tdPixelRowArr& pixArr = ob->m_2DScreen;
		tdPixselArr** pPixData = pixArr.GetData();
		int nLeft = (int)(float)ob->m_leftScreen;
		int nTop = (int)(float)(ob->m_topScreen/*  + 1*/);
		int nRight = (int)(float)ob->m_rightScreen;
		int nBottom = (int)(float)ob->m_bottomScreen ;

		int sizePosCount = ob->m_sizePosArr.GetCount();
		int *pSizePos = ob->m_sizePosArr.GetData();
		int *pPos = ob->m_posArr.GetData();

		//++nTop; // to InflateRect rect
		int topPos = m_info.cy - nTop;
		if(topPos < 0)
		{
			nTop += topPos;
			pPixData -= topPos;
			pPos -= topPos * sizePosCount;
			pSizePos -= topPos;
		}

		int xcorection = 0;
		if(nLeft < 0)
		{
			xcorection = nLeft;
			nLeft = 0;
		}

		if(nRight > m_info.cx)
			nRight = m_info.cx;

		int pcy = nTop - nBottom;
		if(pcy <= 1)
			continue;

		int pcx = nRight - nLeft;
		if(pcx <= 1)
			continue;

		nBottom = m_info.cy - nBottom;
		int nopTop = m_info.cy - nTop;

		m_rasterRc.left = min(m_rasterRc.left, nLeft - 1);
		m_rasterRc.right = max(m_rasterRc.right, nRight +1);
		m_rasterRc.top = min(m_rasterRc.top, nopTop - 1);
		m_rasterRc.bottom = max(m_rasterRc.bottom, nBottom +1);

		int cymintop = nopTop;

		CRect rc(0,0, nRight, nBottom);
		//if(ob->m_objectType == t3d_rect)
		//{
		//	rc.SetRect(0,0,sizePosCount,sizePosCount);
		//}
		//else
			rc.InflateRect(2,2);
		//rc += CPoint(-1,-2);
		m_dibDC.BitBlt(rc.left,rc.top,rc.Width()
			,rc.Height(),m_refreshDC,rc.left,
			rc.top,SRCCOPY);

		CScreenPixsel* p = m_clearingArr.GetData();
		CScreenPixsel* psp;
/*		if(nLeft < 0)
		{
			pcx += nLeft;
			nLeft = 0;
		}*/
		int delsize = pcx * sizeof(CScreenPixsel);
		CScreenPixsel SPi;
		for(register int y = 0; y < pcy && y < nTop; ++y,
			++pSizePos, pPos += sizePosCount)
		{
//			if((cymintop + y) < 0)
//				continue;
			int SizePos = *pSizePos;
			if(SizePos && pcx / SizePos < 6)
			{
				psp = m_pPixelBuf +
					((cymintop + y) * m_info.cx + nLeft);
				
				memcpy(psp, p, delsize);
			}
			else
			{
				int nnLc = nLeft + xcorection;

				for(register int x = 0; x < SizePos/*pcx*/; ++x)//, sp++)
				{
					int Pos = *(pPos + x);
					if((nnLc + Pos) < 0 || (nnLc + Pos) >= m_info.cx)
						continue;
					psp = m_pPixelBuf +
						((cymintop + y) * m_info.cx + (nnLc + Pos));//x));
					*psp = SPi;
				}
			}
		}
	}
}

// Tread loop run in this function
void C3DScreen::Run(void)
{
	BOOL bRet;

	MSG msg;

	PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);

	CString str;
	str.Format("GetCurrentThreadId(%d)", GetCurrentThreadId());
	HANDLE hEv = CreateEvent(NULL, TRUE, FALSE, str);
    SetEvent(hEv);

	while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
	{
		if(bRet == -1)
		{
			return;
		}
		else
		{
			m_cs.Lock();
			switch(msg.message)
			{
			case sc_OnPaint:
				if(m_bQuit)
					continue;
				{
					thOnPaint();
				}				
				break;
			case sc_DeleteObject:
				if(m_bQuit)
					continue;
				{
					thDeleteObject((int)msg.wParam);
				}				
				break;
			case sc_TrigerPaintAlow:
				if(m_bQuit)
					continue;
				{
					thTrigerPaintAlow(msg.wParam, msg.lParam);
				}				
				break;
			case sc_ScreenToDC:
				if(m_bQuit)
					continue;
				thScreenToDC(msg.wParam);
				break;
			case sc_Translate3Dto2D:
				if(m_bQuit)
				{
					delete [](BYTE*)msg.lParam;
					continue;
				}
				{
					int bDoObTrans, xStart, xStopSize;
					BYTE* params = (BYTE*)msg.lParam;
					BYTE* p = params;
					memcpy(&bDoObTrans, params, sizeof(int));
					params += sizeof(int);
					memcpy(&xStart, params, sizeof(int));
					params += sizeof(int);
					memcpy(&xStopSize, params, sizeof(int));

					thTranslate3Dto2D((C3DObject*)msg.wParam,
						bDoObTrans, xStart, xStopSize);
					delete [] p;
				}
				break;
			case sc_ResetShift:
				if(m_bQuit)
					continue;
				thResetShift((C3DObject*)msg.wParam);
				break;
			case sc_InitMatrix:
				if(m_bQuit)
					continue;
				thInitMatrix((C3DObject*)msg.wParam);
			case sc_Transform:
				if(m_bQuit)
					continue;
				thTransform((C3DObject*)msg.wParam, msg.lParam?true:false);
				break;
			case sc_ResetTranslation:
				if(m_bQuit)
					continue;
				thResetTranslation((C3DObject*)msg.wParam);
				break;
			case sc_PaintTansparent:
				if(m_bQuit)
					continue;
				PaintTansparent();
				break;
			case sc_TurnShape:
				{
					if(m_bQuit)
					{
						delete [](BYTE*)msg.lParam;
						continue;
					}
					double angle;
					Axis ax;
					int bLastTurn;
					bool bBase;
					BYTE* params = (BYTE*)msg.lParam;
					BYTE* p = params;
					memcpy(&angle, params, sizeof(double));
					params += sizeof(double);
					memcpy(&ax, params, sizeof(Axis));
					params += sizeof(Axis);
					memcpy(&bLastTurn, params, sizeof(int));
					params += sizeof(int);
					memcpy(&bBase, params, sizeof(bool));

					thTurnShape(angle, ax, bLastTurn, bBase,
						(C3DObject*)msg.wParam);
					delete [] p;
				}
				break;
			case sc_CreatObjectPixselMap:
				{
					if(m_bQuit)
					{
						delete [](BYTE*)msg.lParam;
						continue;
					}
					int cx, cy ,num;
					unsigned long transColor;
					BYTE* params = (BYTE*)msg.lParam;
					BYTE* p = params;
					memcpy(&cx, params, sizeof(int));
					params += sizeof(int);
					memcpy(&cy, params, sizeof(int));
					params += sizeof(int);
					memcpy(&transColor, params, sizeof(unsigned long));
					params += sizeof(unsigned long);
					memcpy(&num, params, sizeof(int));

					thCreatObjectPixselMap(cx, cy, transColor,
						(C3DObject*)msg.wParam, num);
					delete [] p;
				}
				break;
			case sc_FillRect:
				{
					if(m_bQuit)
					{
						delete [](BYTE*)msg.lParam;
						continue;
					}
					int x, y, cx, cy;
					unsigned long color;
					eFiillRectOp op;
					CFillRectData data;
					BYTE* params = (BYTE*)msg.lParam;
					BYTE* p = params;
					memcpy(&x, params, sizeof(int));
					params += sizeof(int);
					memcpy(&y, params, sizeof(int));
					params += sizeof(int);
					memcpy(&cx, params, sizeof(int));
					params += sizeof(int);
					memcpy(&cy, params, sizeof(int));
					params += sizeof(int);
					memcpy(&color, params, sizeof(unsigned long));
					params += sizeof(unsigned long);
					memcpy(&op, params, sizeof(eFiillRectOp));
					params += sizeof(eFiillRectOp);
					memcpy(&data, params, sizeof(CFillRectData));

					thFillRect(x, y, cx, cy, color,
						(C3DObject*)msg.wParam, op, data);
					delete [] p;
				}
				break;
			case sc_TurnObjectCenter:
				{
					if(m_bQuit)
					{
						delete [](BYTE*)msg.lParam;
						continue;
					}
					double angle;
					Axis ax;
					bool bBase;
					BYTE* params = (BYTE*)msg.lParam;
					BYTE* p = params;
					memcpy(&angle, params, sizeof(double));
					params += sizeof(double);
					memcpy(&ax, params, sizeof(Axis));
					params += sizeof(Axis);
					memcpy(&bBase, params, sizeof(bool));

					thTurnObjectCenter(angle, ax, bBase, (C3DObject*)msg.wParam);
					delete [] p;
				}
				break;
			case sc_TurnLightPt:
				{
					if(m_bQuit)
					{
						delete [](BYTE*)msg.lParam;
						continue;
					}
					double angle;
					Axis ax;
					bool bReset;
					BYTE* params = (BYTE*)msg.lParam;
					BYTE* p = params;
					memcpy(&angle, params, sizeof(double));
					params += sizeof(double);
					memcpy(&ax, params, sizeof(Axis));
					params += sizeof(Axis);
					memcpy(&bReset, params, sizeof(bool));

					thTurnLightPt(angle, ax, bReset, (C3DObject*)msg.wParam);
					delete [] p;
				}
				break;
			case sc_TurnMatrix:
				{
					if(m_bQuit)
					{
						delete [](BYTE*)msg.lParam;
						continue;
					}
					double angle;
					Axis ax;
					BYTE* params = (BYTE*)msg.lParam;
					BYTE* p = params;
					memcpy(&angle, params, sizeof(double));
					params += sizeof(double);
					memcpy(&ax, params, sizeof(Axis));

					thTurnMatrix(angle, ax, (C3DObject*)msg.wParam);
					delete [] p;
				}
				break;
			case sc_ShiftObjectCenter:
				{
					if(m_bQuit)
					{
						delete [](BYTE*)msg.lParam;
						continue;
					}
					double angle;
					Axis ax;
					bool bBase;
					BYTE* params = (BYTE*)msg.lParam;
					BYTE* p = params;
					memcpy(&angle, params, sizeof(double));
					params += sizeof(double);
					memcpy(&ax, params, sizeof(Axis));
					params += sizeof(Axis);
					memcpy(&bBase, params, sizeof(bool));

					thShiftObjectCenter(angle, ax, bBase, (C3DObject*)msg.wParam);
					delete [] p;
				}
				break;
			case sc_CreateSphereObject:
				{
					if(m_bQuit)
					{
						delete [](BYTE*)msg.lParam;
						continue;
					}
					int diameter;
					unsigned long color;
					double circle;
					double top;
					double bottom;
					double fine;
					BYTE* params = (BYTE*)msg.lParam;
					BYTE* p = params;
					memcpy(&diameter, params, sizeof(int));
					params += sizeof(int);
					memcpy(&color, params, sizeof(unsigned long));
					params += sizeof(unsigned long);
					memcpy(&circle, params, sizeof(double));
					params += sizeof(double);
					memcpy(&top, params, sizeof(double));
					params += sizeof(double);
					memcpy(&bottom, params, sizeof(double));
					params += sizeof(double);
					memcpy(&fine, params, sizeof(double));

					thCreateSphereObject(diameter, color, circle, top, bottom, fine, (C3DObject*)msg.wParam);
					delete [] p;
				}
				break;
			case sc_CreateCylinderObject:
				{
					if(m_bQuit)
					{
						delete [](BYTE*)msg.lParam;
						continue;
					}
					int topDiameter, bottomDiameter, height;
					unsigned long color;
					double circle;
					double fine;
					BYTE* params = (BYTE*)msg.lParam;
					BYTE* p = params;
					memcpy(&topDiameter, params, sizeof(int));
					params += sizeof(int);
					memcpy(&bottomDiameter, params, sizeof(int));
					params += sizeof(int);
					memcpy(&height, params, sizeof(int));
					params += sizeof(int);
					memcpy(&color, params, sizeof(unsigned long));
					params += sizeof(unsigned long);
					memcpy(&circle, params, sizeof(double));
					params += sizeof(double);
					memcpy(&fine, params, sizeof(double));

					thCreateCylinderObject(topDiameter, bottomDiameter, height, color, circle, fine, (C3DObject*)msg.wParam);
					delete [] p;
				}
				break;
			case sc_CreateFlatSpiralObject:
				{
					if(m_bQuit)
					{
						delete [](BYTE*)msg.lParam;
						continue;
					}
					int width, height, space, minRadius;
					double circle;
					unsigned long col;
					BYTE* params = (BYTE*)msg.lParam;
					BYTE* p = params;
					memcpy(&width, params, sizeof(int));
					params += sizeof(int);
					memcpy(&height, params, sizeof(int));
					params += sizeof(int);
					memcpy(&space, params, sizeof(int));
					params += sizeof(int);
					memcpy(&minRadius, params, sizeof(int));
					params += sizeof(unsigned long);
					memcpy(&circle, params, sizeof(double));
					params += sizeof(double);
					memcpy(&col, params, sizeof(unsigned long));

					thCreateFlatSpiralObject(width, height, space, minRadius, circle, col, (C3DObject*)msg.wParam);
					delete [] p;
				}
				break;
			case sc_CReateCircleLineObject:
				{
					if(m_bQuit)
					{
						delete [](BYTE*)msg.lParam;
						continue;
					}
					int diameter, num;
					double circle, fine;
					unsigned long col;
					BYTE* params = (BYTE*)msg.lParam;
					BYTE* p = params;
					memcpy(&diameter, params, sizeof(int));
					params += sizeof(int);
					memcpy(&col, params, sizeof(unsigned long));
					params += sizeof(int);
					memcpy(&fine, params, sizeof(double));
					params += sizeof(double);
					memcpy(&circle, params, sizeof(double));
					params += sizeof(double);
					memcpy(&num, params, sizeof(int));

					thCReateCircleLineObject(diameter, col, fine, circle, num, (C3DObject*)msg.wParam);
					delete [] p;
				}
				break;
			case sc_BitmapToObject:
				{
					if(m_bQuit)
					{
						CMyFBitmap* pBm;
						COLORREF transperant;
						BYTE* params = (BYTE*)msg.lParam;
						BYTE* p = params;
						memcpy(&pBm, params, sizeof(CMyFBitmap*));
						params += sizeof(CMyFBitmap*);
						memcpy(&transperant, params, sizeof(COLORREF));

						delete pBm;
						delete [] p;
						continue;
					}
					CMyFBitmap* pBm;
					COLORREF transperant;
					BYTE* params = (BYTE*)msg.lParam;
					BYTE* p = params;
					memcpy(&pBm, params, sizeof(CMyFBitmap*));
					params += sizeof(CMyFBitmap*);
					memcpy(&transperant, params, sizeof(COLORREF));

					thBitmapToObject(*pBm, transperant, (C3DObject*)msg.wParam);
					delete pBm;
					delete [] p;
				}
				break;
			case sc_CreateFlatBmObj:
				{
					if(m_bQuit)
					{
						CMyFBitmap* pBm;
						BYTE* params = (BYTE*)msg.lParam;
						BYTE* p = params;
						memcpy(&pBm, params, sizeof(CMyFBitmap*));

						delete pBm;
						delete [] p;
						continue;
					}
					CMyFBitmap* pBm;
					COLORREF transperant;
					BYTE* params = (BYTE*)msg.lParam;
					BYTE* p = params;
					memcpy(&pBm, params, sizeof(CMyFBitmap*));
					params += sizeof(CMyFBitmap*);
					memcpy(&transperant, params, sizeof(COLORREF));

					thCreateFlatBmObj(*pBm, transperant, (C3DObject*)msg.wParam);
					delete pBm;
					delete [] p;
				}
				break;
			case sc_CreateSphereBmObj:
				{
					if(m_bQuit)
					{
						CMyFBitmap* pBm;
						BYTE* params = (BYTE*)msg.lParam;
						BYTE* p = params;
						params += sizeof(int);
						memcpy(&pBm, params, sizeof(CMyFBitmap*));

						delete pBm;
						delete [] p;
						continue;
					}
					int diameter;
					CMyFBitmap* pBm;
					double top;
					double bottom; 
					unsigned long transperantcol;

					BYTE* params = (BYTE*)msg.lParam;
					BYTE* p = params;
					memcpy(&diameter, params, sizeof(int));
					params += sizeof(int);
					memcpy(&pBm, params, sizeof(CMyFBitmap*));
					params += sizeof(CMyFBitmap*);
					memcpy(&top, params, sizeof(double));
					params += sizeof(double);
					memcpy(&bottom, params, sizeof(double));
					params += sizeof(double);
					memcpy(&transperantcol, params, sizeof(unsigned long));

					thCreateSphereBmObj(diameter, *pBm, top, bottom, transperantcol, (C3DObject*)msg.wParam);
					delete pBm;
					delete [] p;
				}
				break;
			}
			m_cs.Unlock();
		}
	}

}

// Static function for running thread
unsigned int __stdcall C3DScreen::SRun(void* lpVoid)
{
	C3DScreen* a = (C3DScreen*)lpVoid;
	a->Run();
	return 0;
}

// Create new object if not exist and set it curent
bool C3DScreen::BeginObject(int id)
{
	C3DObject* ob = NULL;
	if(m_3DObjectMap.Lookup(id, ob) == FALSE)
	{
		ob = new C3DObject(m_info);
		m_3DObjectMap[id] = ob;
	}

	m_currentObject = ob;

	return true;
}

// The transColor is an RBG and last byte is a transparency of the color 0 no transparency 100 full transparency.
bool C3DScreen::CreatObjectPixselMap(int cx, int cy, unsigned long transColor, int num)
{
	if(m_currentObject == NULL)
		return false;

	BYTE* params = new BYTE[sizeof(int)*3 + sizeof(unsigned long)];
	BYTE* p = params;
	memcpy(p, &cx, sizeof(int));
	p += sizeof(int);
	memcpy(p, &cy, sizeof(int));
	p += sizeof(int);
	memcpy(p, &transColor, sizeof(unsigned long));
	p += sizeof(unsigned long);
	memcpy(p, &num, sizeof(unsigned long));

	PostThreadMessage(m_uiThreadId, sc_CreatObjectPixselMap,
		(WPARAM)m_currentObject, (LPARAM)params);
	return true;
}

// filling color acording the position in the memory x y arrays
bool C3DScreen::FillRect(int x, int y, int cx, int cy, unsigned long color,
						 eFiillRectOp op, CFillRectData data)
{
	if(m_currentObject == NULL)
		return false;

	BYTE* params = new BYTE[sizeof(int)*5 + sizeof(unsigned long) + sizeof(CFillRectData)];
	BYTE* p = params;
	memcpy(p, &x, sizeof(int));
	p += sizeof(int);
	memcpy(p, &y, sizeof(int));
	p += sizeof(int);
	memcpy(p, &cx, sizeof(int));
	p += sizeof(int);
	memcpy(p, &cy, sizeof(int));
	p += sizeof(int);
	memcpy(p, &color, sizeof(unsigned long));
	p += sizeof(unsigned long);
	memcpy(p, &op, sizeof(eFiillRectOp));
	p += sizeof(eFiillRectOp);
	memcpy(p, &data, sizeof(CFillRectData));

	PostThreadMessage(m_uiThreadId, sc_FillRect,
		(WPARAM)m_currentObject, (LPARAM)params);

	return true;
}

void C3DScreen::ResetShift(void)
{
	if(m_currentObject == NULL)
		return ;

	PostThreadMessage(m_uiThreadId, sc_ResetShift,
		(WPARAM)m_currentObject, 0);
}

void C3DScreen::ResetTranslation(void)
{
	if(m_currentObject == NULL)
		return ;

	PostThreadMessage(m_uiThreadId, sc_ResetTranslation,
		(WPARAM)m_currentObject, 0);
}

void C3DScreen::ShiftObjectCenter(double shift, Axis ax, bool bBase)
{
	if(m_currentObject == NULL)
		return ;

	BYTE* params = new BYTE[sizeof(double) + sizeof(Axis) + sizeof(bool)];
	BYTE* p = params;
	memcpy(p, &shift, sizeof(double));
	p += sizeof(double);
	memcpy(p, &ax, sizeof(Axis));
	p += sizeof(Axis);
	memcpy(p, &bBase, sizeof(bool));

	PostThreadMessage(m_uiThreadId, sc_ShiftObjectCenter,
		(WPARAM)m_currentObject, (LPARAM)params);
}

void C3DScreen::TurnObjectCenter(double angle, Axis ax, bool bBase)
{
	if(m_currentObject == NULL)
		return ;

	BYTE* params = new BYTE[sizeof(double) + sizeof(Axis) + sizeof(bool)];
	BYTE* p = params;
	memcpy(p, &angle, sizeof(double));
	p += sizeof(double);
	memcpy(p, &ax, sizeof(Axis));
	p += sizeof(Axis);
	memcpy(p, &bBase, sizeof(bool));

	PostThreadMessage(m_uiThreadId, sc_TurnObjectCenter,
		(WPARAM)m_currentObject, (LPARAM)params);
	
}

bool C3DScreen::TurnShape(double angle, Axis ax, int bLastTurn,
						  bool bBase)
{
	if(m_currentObject == NULL)
		return false;

	BYTE* params = new BYTE[sizeof(double) + sizeof(Axis) + sizeof(bool) + sizeof(int)];
	BYTE* p = params;
	memcpy(p, &angle, sizeof(double));
	p += sizeof(double);
	memcpy(p, &ax, sizeof(Axis));
	p += sizeof(Axis);
	memcpy(p, &bLastTurn, sizeof(int));
	p += sizeof(int);
	memcpy(p, &bBase, sizeof(bool));

	PostThreadMessage(m_uiThreadId, sc_TurnShape,
		(WPARAM)m_currentObject, (LPARAM)params);

	return true;
}

bool C3DScreen::Translate3Dto2D(BOOL bDoObTrans,
		int xStart, int xStopSize)
{
	if(m_currentObject == NULL || m_info.cx == 0 || m_info.cy == 0
		|| m_pPixelBuf == NULL)
		return false;

	BYTE* params = new BYTE[3 * sizeof(int)];
	BYTE* p = params;
	memcpy(p, &bDoObTrans, sizeof(int));
	p += sizeof(int);
	memcpy(p, &xStart, sizeof(int));
	p += sizeof(int);
	memcpy(p, &xStopSize, sizeof(int));


	PostThreadMessage(m_uiThreadId, sc_Translate3Dto2D, 
		(WPARAM)m_currentObject, (LPARAM)params);


	return true;
}

void C3DScreen::SetScreenWnd(CWnd* pWnd)
{
	m_pWnd = pWnd;
}

bool C3DScreen::ScreenToDC(BOOL bPaintRefresh)
{
	::PostThreadMessage(m_uiThreadId, sc_ScreenToDC, (WPARAM)bPaintRefresh,0);
	return true;
}

bool C3DScreen::CreateScreenDC(void)
{
	if(m_dibDC.GetSafeHdc())
		return true;

	CClientDC cdc(m_pWnd);
	m_dibDC.CreateCompatibleDC(&cdc);

	BITMAPINFO BMI;
    memset(&BMI, 0, sizeof(BITMAPINFO));
    // Fill in the header info.
    BMI.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	BMI.bmiHeader.biWidth       = m_info.cx;
    BMI.bmiHeader.biHeight      = m_info.cy;
    BMI.bmiHeader.biPlanes      = 1;
    BMI.bmiHeader.biBitCount    = 32 ;           // Must use 32 bpps 
    BMI.bmiHeader.biCompression = BI_RGB ; // to use this flag.


	m_hbm = CreateDIBSection( m_dibDC.GetSafeHdc(),
										 &BMI,
										 DIB_RGB_COLORS,
							   (VOID **) &m_pDibBits,
										 NULL,
										 0);
	if(m_hbm == NULL)
	{
		m_dibDC.DeleteDC();
		return false;
	}

	m_hbmOld = (HBITMAP)::SelectObject(m_dibDC.GetSafeHdc(), m_hbm);

	CArray<RGBQUAD, RGBQUAD> arr;
	arr.SetSize(m_info.cx);
	RGBQUAD screenColor;
	screenColor.rgbRed = GetRValue(m_tansparentColpr);
	screenColor.rgbGreen = GetGValue(m_tansparentColpr);
	screenColor.rgbBlue = GetBValue(m_tansparentColpr);
	screenColor.rgbReserved = 0;
    RGBQUAD* pSc = &screenColor;

	RGBQUAD* pCol = arr.GetData();
	int sizeRGBQUAD = sizeof(RGBQUAD);
	for(register int x = 0; x < m_info.cx; ++x, ++pCol)
		memcpy(pCol, pSc, sizeRGBQUAD);

	pCol = arr.GetData();
	int arrSize = sizeRGBQUAD * m_info.cx;
	RGBQUAD* pDibBits = m_pDibBits;
	for(register int y = 0; y < m_info.cy; ++y, pDibBits += m_info.cx)
		memcpy(pDibBits, pCol, arrSize);

	m_refreshDC.CreateMyCompatibleBitmap(&cdc,m_info.cx,m_info.cy,
		m_tansparentColpr & 0xFFFFFF);
	m_refreshDC.GetMyPaintDC();
    
	return true;
}

void C3DScreen::DeleteGdiObjects(void)
{
	if(m_dibDC.GetSafeHdc() && m_hbmOld)
	{
		::SelectObject(m_dibDC.GetSafeHdc(), m_hbmOld);
		m_hbmOld = NULL;
		m_dibDC.DeleteDC();
	}
	if(m_hbm)
	{
		::DeleteObject(m_hbm);
		m_hbm = NULL;
	}
}

void C3DScreen::thScreenToDC(BOOL bPaintRefresh)
{
	if(m_pWnd == NULL || m_info.cx == 0 || m_info.cy == 0
		|| m_pPixelBuf == NULL || m_dibDC.GetSafeHdc() == NULL
		|| m_hbm == NULL || m_pDibBits == NULL)
		return;
	CRect rc = *((CRect*)m_pWnd->SendMessage(WM_GET_WND_RC));
//	m_pWnd->GetClientRect(rc);
	CClientDC dc(m_pWnd);
		dc.SetMapMode(MM_ISOTROPIC);
		dc.SetWindowExt(m_info.cx,m_info.cy);
		int cx = rc.Width();
		int cy = rc.Height();
		//TRACE("cx = %d   cy = %d\n", cx,cy);
		dc.SetViewportExt(cx,cy);
		dc.SetViewportOrg (m_edgeLeft,  m_edgeTop) ;
	dc.SetStretchBltMode(HALFTONE);

    //CRect sa = GetDestinationRect();
	
	RGBQUAD* pCol = NULL;
	BYTE c[4] = {0,0,0,0};

	POSITION pos = m_3DObjectMap.GetStartPosition();
	int key = -1;
    C3DObject* ob = NULL;

	//if(bPaintRefresh)
	//	m_rasterRc.SetRect(m_info.cx, m_info.cy, 0, 0);

	while(pos != NULL)
	{
		m_3DObjectMap.GetNextAssoc(pos, key, ob);

		if(ob->m_bPause)
			continue;
		
		int nLeft = (int)(float)ob->m_leftScreen;// - pcx/2;
		int nRight = (int)(float)ob->m_rightScreen;// - pcx/2;
		int nTop = (int)(float)ob->m_topScreen ;//-pcy;
		int nBottom = (int)(float)ob->m_bottomScreen;

		int topPos = m_info.cy - nTop;
		if(topPos < 0)
		{
			nTop += topPos;
		}

		int xcorection = 0;
		if(nLeft < 0)
		{
			xcorection = -nLeft;
			nLeft = 0;
		}

		if(nRight > m_info.cx)
			nRight = m_info.cx;

		int pcy = nTop - nBottom;
		if(pcy <= 1)
			continue;

		int pcx = nRight - nLeft;
		if(pcx <= 1)
			continue;

		int cymintop = m_info.cy - nTop;
		int cyminbottom = m_info.cy - nBottom;
		m_rasterRc.left = min(m_rasterRc.left, nLeft - 1);
		m_rasterRc.right = max(m_rasterRc.right, nRight + 1);
		m_rasterRc.top = min(m_rasterRc.top, cymintop - 1);
		m_rasterRc.bottom = max(m_rasterRc.bottom, cyminbottom+1);


		for(int y = 0; y < pcy && y < nTop; ++y)
		{
			if((cymintop + y) <= 0)
				continue;
			for(register int x = 0; x < pcx; ++x)
			{
				if((nLeft + x) < 0)
					continue;
				CScreenPixsel* psp = m_pPixelBuf +
					((cymintop + y) * m_info.cx + (nLeft + x));
				*((DWORD*)c) = psp->color;
				if(c[3] == 100)
					continue;
				pCol = m_pDibBits + 
					((nTop - y) * 
					m_info.cx + (nLeft + x));

				pCol->rgbRed = c[0];
				pCol->rgbGreen = c[1];
				pCol->rgbBlue = c[2];
			}
		}
	}

	if(bPaintRefresh)
	{
		CDC* pDC = m_refreshDC.GetMyPaintDC();
		pDC->BitBlt(m_rasterRc.left,m_rasterRc.top,
			m_rasterRc.Width(),m_rasterRc.Height(),
			&m_dibDC,
			m_rasterRc.left,m_rasterRc.top,SRCCOPY);
	}
	else
	{
		dc.BitBlt(m_rasterRc.left,
			m_rasterRc.top,m_rasterRc.Width(),
			m_rasterRc.Height()
			,&m_dibDC,m_rasterRc.left,
			m_rasterRc.top,	SRCCOPY);
//		m_rasterRc.InflateRect(3,3);
	}
}

void C3DScreen::thTranslate3Dto2D(C3DObject* ob, BOOL bDoObTrans,
		int xStart, int xStopSize)
{
	if(xStopSize == -2)
	{
		ob->m_bPause = true;
		return;
	}
	else
	{
		ob->m_bPause = false;
	}
	bool res = true;
	if(bDoObTrans)
		res = ob->Translate3Dto2D(xStart, xStopSize);
	tdPixelRowArr& pixArr = ob->m_2DScreen;
	tdPixselArr** pPixData = pixArr.GetData();

	int nLeft = (int)(float)ob->m_leftScreen;
	int nTop = (int)(float)ob->m_topScreen ;
//	int nRight = (int)(float)ob->m_rightScreen;
	int nBottom = (int)(float)ob->m_bottomScreen ;

	int sizePosCount = ob->m_sizePosArr.GetCount();
	int *pSizePos = ob->m_sizePosArr.GetData();
	int *pPos = ob->m_posArr.GetData();


	int topPos = m_info.cy - nTop;
	if(topPos < 0)
	{
		nTop += topPos;
		pPixData -= topPos;
		pPos -= topPos * sizePosCount;
		pSizePos -= topPos;
	}

	int pcy = nTop - nBottom;
	if(pcy <= 1)
		return;

	int cymintop = m_info.cy - nTop;
	// the x y of m_2DScreen to world x y
	BYTE color[4] = {0,0,0,0};
	BYTE c[4] = {0,0,0,0};


	for(int y = 0; y < pcy && y < nTop; ++y, ++pPixData,
		++pSizePos, pPos += sizePosCount)
	{		
		int SizePos = *pSizePos;
//		CScreenPixsel* sp = (*pPixData)->GetData() + xcorection;
		for(register int x = 0; x < SizePos/*pcx*/; ++x)//, sp++)
		{
			int Pos = *(pPos + x);
			if((nLeft + Pos) < 0 || (nLeft + Pos) >= m_info.cx)
				continue;
			CScreenPixsel* sp = (*pPixData)->GetData() + Pos;
//			if(sp->lastZ == clean_z)//(nLeft + x) < 0)
//				continue;
			*((DWORD*)color) = sp->color;

			CScreenPixsel* psp = m_pPixelBuf +
				((cymintop + y) * m_info.cx + (nLeft + Pos));//x));
			
			*((DWORD*)c) = psp->color;
			// if sp->lastZ far then psp->lastZ do not paint it.
			bool bNear = sp->lastZ > psp->lastZ;
			if(bNear )
				continue;
			psp->lastZ = sp->lastZ;
			if(psp->color == sp->color)
				continue;
			bool bc3NotTransparent = c[3] == 0;

			if(c[3] == 100 || (color[3] == 0 && bc3NotTransparent))//c[3] == 100
			{
				psp->color =	sp->color;
			}
			else //if(bNear)
			{
				//2 Transparents
				int color3 = 100 - color[3];
				int c3 =  color[3];//100 - c[3];
				c[0] = (c[0] * c3 + color[0] * color3) 
					/ (c3 + color3);
				c[1] = (c[1] * c3 + color[1] * color3) 
					/ (c3 + color3);
				c[2] = (c[2] * c3 + color[2] * color3) 
					/ (c3 + color3);
//				c[3] = (c[3] * c3 + color[3] * color3) 
//					/ (c3 + color3);

				psp->color = *((DWORD*)c);
			}
		}
	}
}

void C3DScreen::thTurnShape(double angle, Axis ax, int bLastTurn,
							bool bBase,
							C3DObject* ob)
{
	if(bBase)
		ob->TurnBaseShape(angle, ax);
	else
		ob->TurnShape(angle, ax, bLastTurn);
}

void C3DScreen::thTurnObjectCenter(double angle, Axis ax, bool bBase, C3DObject* ob)
{
	ob->TurnObjectCenter(angle, ax, bBase);
}

void C3DScreen::thShiftObjectCenter(double angle, Axis ax, bool bBase, C3DObject* ob)
{
	ob->ShiftObjectCenter(angle, ax, bBase);
}

void C3DScreen::thResetShift(C3DObject* ob)
{
	ob->ResetShift();
}

void C3DScreen::thResetTranslation(C3DObject* ob)
{
//	PaintTansparent();
	ob->ResetTranslation();
}

void C3DScreen::thBeginObject(int id)
{
}

void C3DScreen::thCreatObjectPixselMap(int cx, int cy, 
									   unsigned long transColor, 
									   C3DObject* ob,
									   int num)
{
	ob->CreatObjectPixselMap(cx, cy, transColor, num);
}

void C3DScreen::thFillRect(int x, int y, int cx, int cy, unsigned long color, C3DObject* ob,
						   eFiillRectOp op, CFillRectData data)
{
	ob->FillRect(x, y, cx, cy, color, op, data);
}

// 3 <= diameter, 0 < circle <= 360, -90 <= bottom < top <= 90
bool C3DScreen::CreateSphereObject(int diameter, unsigned long color, 
								   double circle, double top, 
								   double bottom, double fine)
{
	if(m_currentObject == NULL)
		return false;

	BYTE* params = new BYTE[sizeof(int) + sizeof(unsigned long) + 4 * sizeof(double)];
	BYTE* p = params;
	memcpy(p, &diameter, sizeof(int));
	p += sizeof(int);
	memcpy(p, &color, sizeof(unsigned long));
	p += sizeof(unsigned long);
	memcpy(p, &circle, sizeof(double));
	p += sizeof(double);
	memcpy(p, &top, sizeof(double));
	p += sizeof(double);	
	memcpy(p, &bottom, sizeof(double));
	p += sizeof(double);	
	memcpy(p, &fine, sizeof(double));

	PostThreadMessage(m_uiThreadId, sc_CreateSphereObject,
		(WPARAM)m_currentObject, (LPARAM)params);

	return true;
}

void C3DScreen::thCreateSphereObject(int diameter, unsigned long color, 
		double circle, double top, double bottom, double fine, C3DObject* ob)
{
	ob->CreateSphereObject(diameter, color, circle, top, bottom, fine);
}


void C3DScreen::ClearScreen(void)
{
	PostThreadMessage(m_uiThreadId, sc_PaintTansparent,
		0, 0);
}

bool C3DScreen::CreateCylinderObject(int topDiameter, 
									 int bottomDiameter, 
									 int height, 
									 unsigned long color, 
									 double circle,
									 double fine)
{
	if(m_currentObject == NULL)
		return false;

	BYTE* params = new BYTE[3 * sizeof(int) + sizeof(unsigned long) + sizeof(double) * 2];
	BYTE* p = params;
	memcpy(p, &topDiameter, sizeof(int));
	p += sizeof(int);
	memcpy(p, &bottomDiameter, sizeof(int));
	p += sizeof(int);
	memcpy(p, &height, sizeof(int));
	p += sizeof(int);
	memcpy(p, &color, sizeof(unsigned long));
	p += sizeof(unsigned long);
	memcpy(p, &circle, sizeof(double));
	p += sizeof(double);
	memcpy(p, &fine, sizeof(double));

	PostThreadMessage(m_uiThreadId, sc_CreateCylinderObject,
		(WPARAM)m_currentObject, (LPARAM)params);
	return true;
}

void C3DScreen::thCreateCylinderObject(int topDiameter, int bottomDiameter, 
									   int height, unsigned long color, 
									   double circle, double fine, C3DObject* ob)
{
	ob->CreateCylinderObject(topDiameter, bottomDiameter, height, color, circle, fine);
}

//CRect C3DScreen::GetDestinationRect(void)
//{
//	double left = (double)cs_cx * m_edgeLeft;
//	double top = (double)cs_cy * m_edgeTop;
//	double reight = (double)cs_cx - 
//		((double)cs_cx * m_edgeReight);
//	double bottom = (double)cs_cy - 
//		((double)cs_cy * m_edgeBottom);
//	int nleft = (int)(float)left;
//	int ntop = (int)(float)top;
//	int nreight = (int)(float)reight;
//	int nbottom = (int)(float)bottom;
//	CRect windArea(nleft, ntop, nreight, nbottom);
//
//	// best fiting screen in window
//	float windRelation = (float)windArea.Width()
//		/ (float)windArea.Height();
//	float psRelation = (float)m_info.cx / (float)m_info.cy;
//	float mulRlation = 0.0f;
//	bool bWndGt = windRelation > psRelation;
//	if(bWndGt)
//	{
//		mulRlation = (float)windArea.Height()
//			/ (float)m_info.cy;
//	}
//	else
//	{
//		mulRlation = (float)windArea.Width()
//			/ (float)m_info.cx;
//	}
//	float gt = bWndGt?(float)windArea.Width():(float)windArea.Height();
//	float space = bWndGt?(float)m_info.cx : (float)m_info.cy;
//	space *= mulRlation;
//	space = (gt - space) / 2.0f;
//	CRect sa = windArea;
//	if(bWndGt)
//		sa.DeflateRect((int)space, 0); 
//	else
//		sa.DeflateRect(0, (int)space); 
//	////////
//	return sa;
//}

void C3DScreen::OnPaint(void)
{
//	PostThreadMessage(m_uiThreadId, sc_OnPaint,
//		0,0);
	if(m_bQuit || m_bNotPaint)
		return;
	//m_cs.Lock();
	thOnPaint();
	//m_cs.Unlock();
}

void C3DScreen::thOnPaint(void)
{
	CClientDC dc(m_pWnd);
	dc.SetMapMode(MM_ISOTROPIC);
	dc.SetWindowExt(m_info.cx,m_info.cy);
	CRect rc = *((CRect*)m_pWnd->SendMessage(WM_GET_WND_RC));
//	m_pWnd->GetClientRect(rc);
	int cx = rc.Width();
	int cy = rc.Height();
	//TRACE("cx = %d   cy = %d\n", cx,cy);
	dc.SetViewportExt(cx,cy);
	dc.SetViewportOrg (m_edgeLeft,  m_edgeTop) ;
	dc.SetStretchBltMode(HALFTONE);
	//CRect sa = GetDestinationRect();
	dc.BitBlt(0,0,m_info.cx,m_info.cy
		,&m_dibDC,0,0,SRCCOPY);
	//CRect sa = GetDestinationRect();
	//dc.StretchBlt(sa.left,sa.top,sa.Width(),sa.Height()
	//	,&m_dibDC,0,0,m_info.cx,m_info.cy,SRCCOPY);
}

void C3DScreen::CopyRefreshToDib(void)
{
	m_dibDC.BitBlt(0,0,m_info.cx,m_info.cy,m_refreshDC,0,0,SRCCOPY);
}

void C3DScreen::BitmapToObject(CMyFBitmap& bm, COLORREF transperant)
{
	if(m_currentObject == NULL)
		return ;

	CMyFBitmap* pBm = new CMyFBitmap(bm);

	BYTE* params = new BYTE[sizeof(CMyFBitmap*) + sizeof(COLORREF)];
	BYTE* p = params;
	memcpy(p, &pBm, sizeof(CMyFBitmap*));
	p += sizeof(CMyFBitmap*);
	memcpy(p, &transperant, sizeof(COLORREF));

	PostThreadMessage(m_uiThreadId, sc_BitmapToObject,
		(WPARAM)m_currentObject, (LPARAM)params);
}

void C3DScreen::thBitmapToObject(CMyFBitmap& bm, COLORREF transperant, C3DObject* ob)
{
	td3DRowsArr& arr = ob->m_3DRowsArr;
	int sizey = arr.GetCount() - 1;
	td3DPixselColumnArr** pData = arr.GetData();
	int sizex = (*pData)->GetCount() - 1;
	CBase3DObjectPixsel* pPixsel = NULL;//(*pData)->GetData();
	CMyFBitmap objBm;
	if(bm.m_height == sizey && bm.m_width == sizex)
	{
		objBm = bm;
	}
	else
	{
		objBm.CreateMyCompatibleBitmap(bm, sizex, sizey);
		CDC* pDC = objBm.operator CDC *();
		pDC->SetStretchBltMode(HALFTONE);
		bm.StrechDraw(objBm,0,0,sizex, sizey);
	}

	CDC* pDC = objBm.operator CDC *();
	COLORREF col = 0;
	COLORREF tran = (COLORREF)100 << 24;
	COLORREF colTran = transperant  & 0XFF000000;
	transperant &= 0XFFFFFF;


	for(int y = 0; y < sizey; ++y, ++pData)
	{
		pPixsel = (*pData)->GetData();
		for(int x = 0; x < sizex; ++x, ++pPixsel)
		{
			col = pDC->GetPixel(x,y);
			if(col == transperant)
			{
				col |= tran;
				pPixsel->color = col;
			}
			else
				pPixsel->color = col | colTran;
		}
	}
}

void C3DScreen::TurnPoint(C3DPoint& p, double angle, Axis ax)
{ 
	angle *= C3DObject::m_degtorad;
	CDPoint yx(cos(angle),sin(angle));
	C3DObject::Turn(p,yx,ax);
}

bool C3DScreen::CreateFlatSpiralObject(int width, 
									   int height,
									   int space,
									   int minRadius, 
									   double circle, 
									   unsigned long col)
{
	if(m_currentObject == NULL)
		return false;

	BYTE* params = new BYTE[4 * sizeof(int) + sizeof(unsigned long) + sizeof(double)];
	BYTE* p = params;
	memcpy(p, &width, sizeof(int));
	p += sizeof(int);
	memcpy(p, &height, sizeof(int));
	p += sizeof(int);
	memcpy(p, &space, sizeof(int));
	p += sizeof(int);
	memcpy(p, &minRadius, sizeof(int));
	p += sizeof(int);
	memcpy(p, &circle, sizeof(double));
	p += sizeof(double);
	memcpy(p, &col, sizeof(unsigned long));

	PostThreadMessage(m_uiThreadId, sc_CreateFlatSpiralObject,
		(WPARAM)m_currentObject, (LPARAM)params);
	return true;
}

void C3DScreen::thCreateFlatSpiralObject(int width, int height, int space, int minRadius, double circle, unsigned long col, C3DObject* ob)
{
	ob->CreateFlatSpiralObject(width, height, space, minRadius, circle, col);
}

void C3DScreen::thCReateCircleLineObject(int diameter, unsigned long color, double fine, double circle, int num,C3DObject* ob)
{
	ob->CReateCircleLineObject(diameter, color, fine, circle, num);
}

void C3DScreen::CReateCircleLineObject(int diameter, 
									   unsigned long color, 
									   double fine, 
									   double circle,
									   int num)
{
	if(m_currentObject == NULL)
		return;

	BYTE* params = new BYTE[sizeof(int) * 2 + sizeof(unsigned long) + sizeof(double) * 2];
	BYTE* p = params;
	memcpy(p, &diameter, sizeof(int));
	p += sizeof(int);
	memcpy(p, &color, sizeof(unsigned long));
	p += sizeof(unsigned long);
	memcpy(p, &fine, sizeof(double));
	p += sizeof(double);
	memcpy(p, &circle, sizeof(double));
	p += sizeof(double);
	memcpy(p, &num, sizeof(int));

	PostThreadMessage(m_uiThreadId, sc_CReateCircleLineObject,
		(WPARAM)m_currentObject, (LPARAM)params);
}

bool C3DScreen::DeleteObject(int id)
{
	PostThreadMessage(m_uiThreadId, sc_DeleteObject,
		(WPARAM)id, 0);
	return false;
}

bool C3DScreen::thDeleteObject(int id)
{
	C3DObject* ob = NULL;
	if(m_3DObjectMap.Lookup(id, ob) == TRUE)
	{
		delete ob;
		m_3DObjectMap.RemoveKey(id);
	}

	m_currentObject = NULL;
	return true;
}

void C3DScreen::NoPaint(void)
{
	m_bNotPaint = true;
}

void C3DScreen::TrigerPaintAlow(WPARAM wParam, LPARAM lParam)
{
	PostThreadMessage(m_uiThreadId, sc_TrigerPaintAlow,
		wParam, lParam);
}

void C3DScreen::thTrigerPaintAlow(WPARAM wParam, LPARAM lParam)
{
	m_bNotPaint = false;
	m_pWnd->PostMessageA(WM_ON_TRIGER_MSG, wParam, lParam);
}

void C3DScreen::CopyRefresh(CRect& rc)
{
	//m_cs.Lock();

	m_dibDC.FillSolidRect(rc,0);
	m_dibDC.BitBlt(rc.left,rc.top,rc.Width(),
		rc.Height(),m_refreshDC,rc.left,rc.top,SRCCOPY);

	//m_cs.Unlock();

}

double C3DScreen::GetTransformVector(void)
{
	return m_info.TransformVector;
}

double C3DScreen::GetMiddleZ(void)
{
	return m_info.middleSpace.z;
}

void C3DScreen::CreateSphereBmObj(int diameter, CMyFBitmap& bm, 
								  double top, double bottom, 
								  unsigned long transperantcol)
{
	if(m_currentObject == NULL)
		return;

	CMyFBitmap* pBm = new CMyFBitmap(bm);

	BYTE* params = new BYTE[sizeof(CMyFBitmap*) + sizeof(int) + sizeof(unsigned long) + sizeof(double) * 2];
	BYTE* p = params;
	memcpy(p, &diameter, sizeof(int));
	p += sizeof(int);
	memcpy(p, &pBm, sizeof(CMyFBitmap*));
	p += sizeof(CMyFBitmap*);
	memcpy(p, &top, sizeof(double));
	p += sizeof(double);
	memcpy(p, &bottom, sizeof(double));
	p += sizeof(double);
	memcpy(p, &transperantcol, sizeof(unsigned long));

	PostThreadMessage(m_uiThreadId, sc_CreateSphereBmObj,
		(WPARAM)m_currentObject, (LPARAM)params);
}

void C3DScreen::thCreateSphereBmObj(int diameter, CMyFBitmap& bm, 
								  double top, double bottom, 
								  unsigned long transperantcol, C3DObject* ob)
{
	ob->CreateSphereBmObj(diameter,bm,top,bottom,transperantcol);
}

void C3DScreen::CreateFlatBmObj(CMyFBitmap& bm, unsigned long transperant)
{
	if(m_currentObject == NULL)
		return ;

	CMyFBitmap* pBm = new CMyFBitmap(bm);

	BYTE* params = new BYTE[sizeof(CMyFBitmap*) + sizeof(COLORREF)];
	BYTE* p = params;
	memcpy(p, &pBm, sizeof(CMyFBitmap*));
	p += sizeof(CMyFBitmap*);
	memcpy(p, &transperant, sizeof(COLORREF));

	PostThreadMessage(m_uiThreadId, sc_CreateFlatBmObj,
		(WPARAM)m_currentObject, (LPARAM)params);
}

void C3DScreen::thCreateFlatBmObj(CMyFBitmap& bm, unsigned long transperant, C3DObject* ob)
{
	ob->CreateFlatBmObj(bm, transperant);
}

void C3DScreen::TurnLightPt(double angle, Axis ax, bool bReset)
{
	if(m_currentObject == NULL)
		return ;

	BYTE* params = new BYTE[sizeof(double) + sizeof(Axis) + sizeof(bool)];
	BYTE* p = params;
	memcpy(p, &angle, sizeof(double));
	p += sizeof(double);
	memcpy(p, &ax, sizeof(Axis));
	p += sizeof(Axis);
	memcpy(p, &bReset, sizeof(bool));

	PostThreadMessage(m_uiThreadId, sc_TurnLightPt,
		(WPARAM)m_currentObject, (LPARAM)params);
}

void C3DScreen::thTurnLightPt(double angle, Axis ax, bool bReset, C3DObject* ob)
{
	ob->TurnLightPt(angle, ax, bReset);
}

void C3DScreen::thInitMatrix(C3DObject* ob)
{
	ob->m_matrix.Init();
}

void C3DScreen::InitMatrix(void)
{
	if(m_currentObject == NULL)
		return ;

	PostThreadMessage(m_uiThreadId, sc_InitMatrix,
		(WPARAM)m_currentObject, 0);
}

void C3DScreen::TurnMatrix(double angle, Axis ax)
{
	if(m_currentObject == NULL)
		return ;

	BYTE* params = new BYTE[sizeof(double) + sizeof(Axis)];
	BYTE* p = params;
	memcpy(p, &angle, sizeof(double));
	p += sizeof(double);
	memcpy(p, &ax, sizeof(Axis));

	PostThreadMessage(m_uiThreadId, sc_TurnMatrix,
		(WPARAM)m_currentObject, (LPARAM)params);
}

void C3DScreen::thTurnMatrix(double angle, Axis ax, C3DObject* ob)
{
	CMatrix m1, tm;
	tm = ob->m_matrix;
	switch(ax)
	{
	case axis_x:
		m1.RotX(angle);
		break;
	case axis_y:
		m1.RotY(angle);
		break;
	case axis_z:
		m1.RotZ(angle);
		break;
	case axis_s:
		ob->m_matrix.Scale(angle);
		return;
	}

	ob->m_matrix.Mul(m1, tm);
}

void C3DScreen::Transform(bool bWorldTranslation)
{
	if(m_currentObject == NULL)
		return ;

	PostThreadMessage(m_uiThreadId, sc_Transform,
		(WPARAM)m_currentObject, (LPARAM)bWorldTranslation);
}

void C3DScreen::thTransform(C3DObject* ob, bool bWorldTranslation)
{
	ob->Transform(bWorldTranslation);
}
