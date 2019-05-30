#include "3DObject.h"

#include "stdafx.h"
#include "scaleveiw.h"
#include "3dobject.h"

C3DObject::C3DObject(const CScreenInfo &info)
: m_leftScreen(0)
, m_topScreen(0)
, m_rightScreen(0)
, m_bottomScreen(0)
,m_objectType(t3d_rect)
,m_clearEreaRc(0,0,0,0)
,m_info(info)
, m_nPosTop(0)
, m_bPause(false)
, m_bmWidth(0)
, m_lightPt(0.0,0.0,-1.0)
{
}
double C3DObject::m_degtorad = g_degtorad;
double CMatrix::m_degtorad = g_degtorad;


C3DObject::~C3DObject(void)
{
	ClearRows();
	Clear2DScreen();
}

void C3DObject::ShiftObjectCenter(double shift, Axis ax, bool bBase)
{
	if(bBase)
	{
//		double cord = m_BaseShiftPoint.cord;
		double X = m_BaseShiftPoint.x;// * cord;
		double Y = m_BaseShiftPoint.y;// * cord;
		double Z = m_BaseShiftPoint.z;// * cord;
		switch(ax)
		{
		case axis_x:
			X += shift;
			break;
		case axis_y:
			Y += shift;
			break;
		case axis_z:
			Z += shift;
			break;
		}

//		m_BaseShiftPoint.cord = cord = sqrt(X*X+Y*Y+Z*Z);
		m_BaseShiftPoint.x = X;// / cord;
		m_BaseShiftPoint.y = Y;// / cord;
		m_BaseShiftPoint.z = Z;// / cord;
	}
	else
	{
//		double cord = m_ShiftPoint.cord;
		double X = m_ShiftPoint.x;// * cord;
		double Y = m_ShiftPoint.y;// * cord;
		double Z = m_ShiftPoint.z;// * cord;
		switch(ax)
		{
		case axis_x:
			X += shift;
			break;
		case axis_y:
			Y += shift;
			break;
		case axis_z:
			Z += shift;
			break;
		}

//		m_ShiftPoint.cord = cord = sqrt(X*X+Y*Y+Z*Z);
		m_ShiftPoint.x = X;// / cord;
		m_ShiftPoint.y = Y;// / cord;
		m_ShiftPoint.z = Z;// / cord;
	}

}

// Set object Shift point axises = 0
void C3DObject::ResetShift(void)
{
	m_ShiftPoint = m_BaseShiftPoint;
}


void C3DObject::TurnObjectCenter(double angle, Axis ax, bool bBase)
{
	angle *= m_degtorad;
	CDPoint xy = GetAngleCosSin(angle);
	if(bBase)
	{
		Turn(m_BaseShiftPoint, xy, ax);
//		SetC3DPointCord(m_BaseShiftPoint);
	}
	else
	{
		Turn(m_ShiftPoint, xy, ax);
//		SetC3DPointCord(m_ShiftPoint);
	}
}

void C3DObject::ClearRows(void)
{
	INT_PTR size = m_3DRowsArr.GetCount();
	td3DPixselColumnArr** pData = m_3DRowsArr.GetData();
	for(register int i = 0; i <size; ++i)
		delete pData[i];
	m_3DRowsArr.RemoveAll();

	pData = m_Translated3dRowsArr.GetData();
	for(register int i = 0; i < size; ++i)
		delete pData[i];
	m_Translated3dRowsArr.RemoveAll();

	pData = m_CameraTranslated3dRowsArr.GetData();
	for(register int i = 0; i < size; ++i)
		delete pData[i];
	m_CameraTranslated3dRowsArr.RemoveAll();
}

// Center of pixsel map x= y = z = 0
bool C3DObject::CreatObjectPixselMap(int cx, int cy, unsigned long Color,int num)
{
	if(cx <= 0 || cy <= 0 || num < 1)
		return false;
	m_objectType = t3d_rect;

	ClearRows();
	m_3DRowsArr.SetSize((cy + 1)*num);
	m_Translated3dRowsArr.SetSize((cy + 1)*num);
	m_CameraTranslated3dRowsArr.SetSize((cy + 1)*num);
	td3DPixselColumnArr** pData = m_3DRowsArr.GetData();
	td3DPixselColumnArr** pData2 = m_Translated3dRowsArr.GetData();
	td3DPixselColumnArr** pData3 = m_CameraTranslated3dRowsArr.GetData();

	CBase3DObjectPixsel pixsel;
	CBase3DObjectPixsel* pPixsels = NULL;
	CBase3DObjectPixsel* pPixsels2 = NULL;

	const double unit = 1.0;
	const double xTurnStep = 180.0 /(double)num;
	double xTurn = 0;

	for(int i = 0; i < num; ++i, xTurn += xTurnStep)
	{
		CDPoint tPt(cos(xTurn * g_degtorad),sin(xTurn * g_degtorad));
		double x = (double)cx / -2.0;
		double xx = x;
		double y = (double)cy / 2.0;

		for(register int posy = 0; posy <= cy; ++posy, ++pData, ++pData2, ++pData3 ,y -= unit)
		{
			*pData = new td3DPixselColumnArr;
			*pData2 = new td3DPixselColumnArr;
			*pData3 = new td3DPixselColumnArr;
			(*pData)->SetSize(cx + 1);
			(*pData2)->SetSize(cx + 1);
			(*pData3)->SetSize(cx + 1);
			pPixsels = (*pData)->GetData();
			pPixsels2 = (*pData2)->GetData();
			x = xx;
			for(register int posx = 0; posx < cx; ++posx, ++pPixsels, ++pPixsels2, x += unit)
			{	
				pixsel.color = (posy != cy)?Color:0x64000000;
				pixsel.p3D.z = 0;
				pixsel.p3D.x = x;
				pixsel.p3D.y = y;
				if(xTurn != 0)
					Turn(pixsel.p3D,tPt,axis_x);
				//pixsel.p3D.SetOp();
				*pPixsels = *pPixsels2 = pixsel;
			}
			pixsel.color = 0x64000000;
			pixsel.p3D.z = 0;
			pixsel.p3D.x = x;
			pixsel.p3D.y = y;
			if(xTurn != 0)
				Turn(pixsel.p3D,tPt,axis_x);
			//pixsel.p3D.SetOp();
			*pPixsels = *pPixsels2 = pixsel;
		}
	}

    TurnShape(0.0, axis_y);


	return true;
}

// filling color acording the position in the memory x y arrays
bool C3DObject::FillRect(int x, int y, int cx, int cy, unsigned long color,
						 eFiillRectOp op, CFillRectData data)
{
	double radius = data.radius;
	if(op != fr_paint 
		&& op != fr_yPaintLessThen
		&& op != fr_yPaintLessThenBase
		&& op != fr_paintTranslated
		&& op != fr_PaintDiractionRange
		&& radius == 0.0 
		&& op != fr_shrink)
		return false;

	int subtrec = (op == fr_shrink)?0:1;
	int sizey = m_3DRowsArr.GetCount() - subtrec;
	if(sizey <= 0)
		return false;

	bool bTranslate = (op == fr_colIntensity 
		|| op == fr_zAtIntensity
		|| op == fr_shrink
		|| op == fr_lightOppositeDirection
		|| op == fr_yLightOppositeDirection
		|| op == fr_paintTranslated
		|| op == fr_zIntensityAll
		|| op == fr_yPaintLessThen
		|| op == fr_PaintDiractionRange
		);

	td3DPixselColumnArr** pData = 
		(bTranslate)?m_Translated3dRowsArr.GetData():m_3DRowsArr.GetData();

	//if(op == fr_zIntensityAll)
	//	pData = m_CameraTranslated3dRowsArr.GetData();

	int sizex = (*pData)->GetCount() - subtrec;
	pData += y;
	if(sizex <= 0)
		return false;

	CBase3DObjectPixsel* pPixsels = NULL;
	cy += y;
	cx += x;	

	double rs = (double)GetRValue(color);
	double gs = (double)GetGValue(color);
	double bs = (double)GetBValue(color);
	
	double rs2 = (double)GetRValue(data.color2);
	double gs2 = (double)GetGValue(data.color2);
	double bs2 = (double)GetBValue(data.color2);
	
	UINT nVec = color >> 24;
	if(nVec > 100)
		nVec = 100;

	double shr = radius;
	if(op == fr_shrink)
	{
		m_ShiftPoint.x *= shr; 
		m_ShiftPoint.y *= shr; 
		m_ShiftPoint.z *= shr; 
	}

	for(int posy = y; posy < cy && posy < sizey; ++posy, ++pData)
	{
		pPixsels = (*pData)->GetData() + x;
		for(register int posx = x; posx < cx && posx < sizex; ++posx, ++pPixsels)
		{
			switch(op)
			{
			case fr_paint:
			case fr_paintTranslated:
			default:
				pPixsels->color = color;
				break;
			case fr_PaintDiractionRange:
				{
					double cosAng =
						(pPixsels->p3D.x*m_lightPt.x + 
						pPixsels->p3D.y*m_lightPt.y +
						pPixsels->p3D.z*m_lightPt.z);
					if(cosAng >= data.vec)
					{
						COLORREF trans = pPixsels->color & 0XFF000000;
						pPixsels->color = color | trans;					
					}
				}
				break;
			case fr_shrink:
				{
					pPixsels->p3D.x *= shr; 
					pPixsels->p3D.y *= shr; 
					pPixsels->p3D.z *= shr; 
				}
				break;
			case fr_yPaintLessThen:
			case fr_yPaintLessThenBase:
				if(pPixsels->p3D.y < radius)
				{
					COLORREF trans = pPixsels->color & 0XFF000000;
					pPixsels->color = color | trans;					
				}
				break;
			case fr_yLightOppositeDirection:
			case fr_yLightOppositeDirectionBase:
				if(pPixsels->p3D.y < 0.0)
				{
					BYTE rn = (BYTE)(((double)GetRValue(pPixsels->color) + rs)/shr);
					BYTE gn = (BYTE)(((double)GetGValue(pPixsels->color) + gs)/shr);
					BYTE bn = (BYTE)(((double)GetBValue(pPixsels->color) + bs)/shr);
					COLORREF nc = RGB(rn, gn, bn);
					COLORREF trans = pPixsels->color & 0XFF000000;
					pPixsels->color = nc | trans;					
				}
				break;
			case fr_lightOppositeDirection:
			case fr_lightOppositeDirectionBase:
				{
					double cosAng =
						(pPixsels->p3D.x*m_lightPt.x + 
						pPixsels->p3D.y*m_lightPt.y +
						pPixsels->p3D.z*m_lightPt.z)/radius;
					if(cosAng < 0.0)
					{
						BYTE rn = (BYTE)(((double)GetRValue(pPixsels->color) + rs)/data.vec);
						BYTE gn = (BYTE)(((double)GetGValue(pPixsels->color) + gs)/data.vec);
						BYTE bn = (BYTE)(((double)GetBValue(pPixsels->color) + bs)/data.vec);
						COLORREF nc = RGB(rn, gn, bn);
						COLORREF trans = pPixsels->color & 0XFF000000;
						pPixsels->color = nc | trans;					
					}
					else if(data.vec2 > 0.0)
					{
						cosAng *= cosAng;
						double rd = (double)GetRValue(pPixsels->color);
						double gd = (double)GetGValue(pPixsels->color);
						double bd = (double)GetBValue(pPixsels->color);
						BYTE rn = (BYTE)(rd + (rs2 - rd) * cosAng * data.vec2);
						BYTE gn = (BYTE)(gd + (gs2 - gd) * cosAng * data.vec2);
						BYTE bn = (BYTE)(bd + (bs2 - bd) * cosAng * data.vec2);
						COLORREF nc = RGB(rn, gn, bn);
						COLORREF trans = pPixsels->color & 0XFF000000;
						pPixsels->color = nc | trans;					
					}
				}
				break;
			case fr_lightDirection:
			case fr_lightDirectionBase:
				{
					double cosAng =
						(pPixsels->p3D.x*m_lightPt.x + 
						pPixsels->p3D.y*m_lightPt.y +
						pPixsels->p3D.z*m_lightPt.z)/radius;
					if(cosAng >= 0.0)
					{
						double rd = (double)GetRValue(pPixsels->color);
						double gd = (double)GetGValue(pPixsels->color);
						double bd = (double)GetBValue(pPixsels->color);
						BYTE rn = (BYTE)(rd + (rs - rd) * cosAng);
						BYTE gn = (BYTE)(gd + (gs - gd) * cosAng);
						BYTE bn = (BYTE)(bd + (bs - bd) * cosAng);
						COLORREF nc = RGB(rn, gn, bn);
						COLORREF trans = pPixsels->color & 0XFF000000;
						pPixsels->color = nc | trans;					
					}
				}
				break;
			case fr_colIntensity:
				{
					if(pPixsels->color == 0x64000000)
						continue;
					
					double vec = (double)nVec / 100.0;
					if(vec > 1.0)
						vec = 1.0;
					double rd = (double)GetRValue(pPixsels->color);
					double gd = (double)GetGValue(pPixsels->color);
					double bd = (double)GetBValue(pPixsels->color);
					BYTE rn = (BYTE)(rd + (rs - rd) * vec);
					BYTE gn = (BYTE)(gd + (gs - gd) * vec);
					BYTE bn = (BYTE)(bd + (bs - bd) * vec);
					COLORREF nc = RGB(rn, gn, bn);
					COLORREF trans = pPixsels->color & 0XFF000000;
					pPixsels->color = nc | trans;					
				}
				break;
			case fr_zIntensity:
			case fr_zAtIntensity:
			case fr_zSquareIntensity:
				{
					if(pPixsels->color == 0x64000000)
						continue;
					double vec = fabs(pPixsels->p3D.z / radius);
					if(vec > 1.0)
						vec = 1.0;
					if(fr_zSquareIntensity == op)
					{
						//if(vec > 0.5)
						{
							vec *= vec;
							vec *= vec;
						}
					}
					double rd = (double)GetRValue(pPixsels->color);
					double gd = (double)GetGValue(pPixsels->color);
					double bd = (double)GetBValue(pPixsels->color);
					BYTE rn = (BYTE)(rd + (rs - rd) * vec);
					BYTE gn = (BYTE)(gd + (gs - gd) * vec);
					BYTE bn = (BYTE)(bd + (bs - bd) * vec);
					COLORREF nc = RGB(rn, gn, bn);
					COLORREF trans = pPixsels->color & 0XFF000000;
					pPixsels->color = nc | trans;					
				}
				break;
			case fr_zIntensityAll:
				{
					if(pPixsels->color == 0x64000000)
						continue;
					double vec = -pPixsels->p3D.z / radius;
					vec *= data.vec;
					if(vec > 0.0)
					{
						if(vec > 1.0)
							vec = 1.0;
						double rd = (double)GetRValue(pPixsels->color);
						double gd = (double)GetGValue(pPixsels->color);
						double bd = (double)GetBValue(pPixsels->color);
						BYTE rn = (BYTE)(rd + (255.0 - rd) * vec);
						BYTE gn = (BYTE)(gd + (255.0 - gd) * vec);
						BYTE bn = (BYTE)(bd + (255.0 - bd) * vec);
						COLORREF nc = RGB(rn, gn, bn);
						COLORREF trans = pPixsels->color & 0XFF000000;
						pPixsels->color = nc | trans;					
					}
					else
					{
						if(vec < -1.0)
							vec = -1.0;
						double rd = (double)GetRValue(pPixsels->color);
						double gd = (double)GetGValue(pPixsels->color);
						double bd = (double)GetBValue(pPixsels->color);
						BYTE rn = (BYTE)(rd + rd * vec);
						BYTE gn = (BYTE)(gd + gd * vec);
						BYTE bn = (BYTE)(bd + bd * vec);
						COLORREF nc = RGB(rn, gn, bn);
						COLORREF trans = pPixsels->color & 0XFF000000;
						pPixsels->color = nc | trans;					
					}
				}
				break;
			case fr_yIntensity:
				{
					if(pPixsels->color == 0x64000000)
						continue;
					double vec = fabs(pPixsels->p3D.y / radius);
					if(vec > 1.0)
						vec = 1.0;
					double rd = (double)GetRValue(pPixsels->color);
					double gd = (double)GetGValue(pPixsels->color);
					double bd = (double)GetBValue(pPixsels->color);
					BYTE rn = (BYTE)(rd + (rs - rd) * vec);
					BYTE gn = (BYTE)(gd + (gs - gd) * vec);
					BYTE bn = (BYTE)(bd + (bs - bd) * vec);
					COLORREF nc = RGB(rn, gn, bn);
					COLORREF trans = pPixsels->color & 0XFF000000;
					pPixsels->color = nc | trans;					
				}
				break;
			case fr_xyIntensity:
				{
					if(pPixsels->color == 0x64000000)
						continue;
					double vecx = fabs(pPixsels->p3D.x / radius);
					if(vecx > 1.0)
						vecx = 1.0;
					double vecy = fabs(pPixsels->p3D.y / radius);
					if(vecy > 1.0)
						vecy = 1.0;
					double vec = sqrt(vecx*vecx + vecy*vecy);
					double rd = (double)GetRValue(pPixsels->color);
					double gd = (double)GetGValue(pPixsels->color);
					double bd = (double)GetBValue(pPixsels->color);
					BYTE rn = (BYTE)(rd + (rs - rd) * vec);
					BYTE gn = (BYTE)(gd + (gs - gd) * vec);
					BYTE bn = (BYTE)(bd + (bs - bd) * vec);
					COLORREF nc = RGB(rn, gn, bn);
					COLORREF trans = pPixsels->color & 0XFF000000;
					pPixsels->color = nc | trans;					
				}
				break;
			}
		}
		sizex = (*pData)->GetCount() - subtrec;
	}

	return true;
}

bool C3DObject::ResetTranslation(void)
{
	int sizey = m_3DRowsArr.GetCount();
	int sizex = 0;
	register td3DPixselColumnArr** pData = m_3DRowsArr.GetData();
	register td3DPixselColumnArr** pData2 = m_Translated3dRowsArr.GetData();
	for(register int i = 0; i < sizey; ++i, ++pData, ++pData2)
	{
		sizex = (*pData)->GetCount();
		memcpy((*pData2)->GetData(),
			(*pData)->GetData(),
			sizex * sizeof(CBase3DObjectPixsel));
	}
	//m_matrix.Reset();
	//m_turnVec = C3DPoint();
	return true;
}

bool C3DObject::TurnBaseShape(double angle, Axis ax)
{
	if(angle == 0.0)
		return true;
	angle *= m_degtorad;
	CDPoint xy = GetAngleCosSin(angle);
	INT_PTR sizey = m_Translated3dRowsArr.GetCount();
	INT_PTR sizex = 0;
	td3DPixselColumnArr** pData = m_3DRowsArr.GetData();
	CBase3DObjectPixsel* pPixsels = NULL;

	for(INT_PTR y = 0; y < sizey; ++y, ++pData)
	{
		sizex = (*pData)->GetCount();
		pPixsels = (*pData)->GetData();
		for(register INT_PTR x = 0; x < sizex; ++x, ++pPixsels)
		{
			Turn(pPixsels->p3D, xy, ax);
			//pPixsels->p3D.SetOp();
		}
	}

	return true;
}


bool C3DObject::TurnShape(double angle, Axis ax, int bLastTurn)
{
	if(angle == 0.0 && bLastTurn == false)
		return true;

	//if(bLastTurn != TURN_SIMPLE)
	//{
	//	TurnMatrix(ax, angle);
	//	if(bLastTurn == FALSE)
	//		return true;
	//}

	//if(bLastTurn != TURN_SIMPLE)
	//	m_matrix.SetOp();


	angle *= m_degtorad;


	CDPoint xy = GetAngleCosSin(angle);

	bool bangNull = !(xy.y == 0.0 && xy.x == 1.0);
	if(bangNull == false && bLastTurn == false)
		return true;

	INT_PTR sizey = m_Translated3dRowsArr.GetCount();
	INT_PTR sizex = 0;
	td3DPixselColumnArr** pData2 = m_Translated3dRowsArr.GetData();
	td3DPixselColumnArr** pData3 = m_CameraTranslated3dRowsArr.GetData();
	CBase3DObjectPixsel* pPixsels2 = NULL;
	CBase3DObjectPixsel* pPixsels3 = NULL;

	double oldHeight = (int)(float)(m_topScreen - m_bottomScreen);
	double oldWidth = (int)(float)(m_rightScreen - m_leftScreen);

	m_leftScreen = (double)m_info.cx;
	m_rightScreen = -m_leftScreen;
	m_bottomScreen = (double)m_info.cy;
	m_topScreen = -m_bottomScreen;

	m_nPosTop = 0;

	double p3dx = 0.0;
	double p3dy = 0.0;
	double p3dz = 0.0;
	double cord = 0.0;
	double p3dVect = 0.0;
	double centerz = m_info.middleSpace.z + m_ShiftPoint.z/* *
		m_ShiftPoint.cord*/;
	double shiftPX = /*m_ShiftPoint.cord * */m_ShiftPoint.x;
	double shiftPY = /*m_ShiftPoint.cord * */m_ShiftPoint.y;

	//int operation = 1;
	//if(bLastTurn == TURN_SIMPLE && bangNull)
	//	operation = 0;


	for(INT_PTR y = 0; y < sizey; ++y, ++pData2, ++pData3)
	{
		sizex = (*pData2)->GetCount();
		pPixsels2 = (*pData2)->GetData();
		pPixsels3 = (*pData3)->GetData();
		for(register INT_PTR x = 0; x < sizex; ++x, ++pPixsels2, ++pPixsels3)
		{

			if(bangNull)
				Turn(pPixsels2->p3D, xy, ax);

			if(bLastTurn == TRUE)
			{
//				cord = pPixsels2->p3D.cord;

				p3dz = pPixsels2->p3D.z + centerz;
				p3dVect = m_info.TransformVector / (p3dz);

				p3dx = pPixsels2->p3D.x/* * cord */+ shiftPX;
				p3dx *= p3dVect;
				p3dx += m_info.middleSpace.x;

				p3dy = pPixsels2->p3D.y/* * cord */+ shiftPY;
				p3dy *= p3dVect;
				p3dy += m_info.middleSpace.y;
				

				pPixsels3->p3D.x = p3dx;
				pPixsels3->p3D.y = p3dy;
				pPixsels3->p3D.z = p3dz;// + m_info.middleSpace.z;
				pPixsels3->color = pPixsels2->color;
				pPixsels3->xpos = pPixsels2->xpos;
				if(p3dz <= m_info.Near)
					continue;


				if(p3dx < m_leftScreen)
				{
					m_leftScreen = p3dx;
				}
				if(p3dx > m_rightScreen)
				{
					m_rightScreen = p3dx;
				}
				if(p3dy < m_bottomScreen)
				{
					m_bottomScreen = p3dy;
				}
				if(p3dy > m_topScreen)
				{
					m_topScreen = p3dy;
				}
			}
		}
	}

	if(bLastTurn == TRUE)
	{

		m_leftScreen = floor(m_leftScreen);

		m_rightScreen = ceil(m_rightScreen);

		m_bottomScreen = floor(m_bottomScreen);

		m_topScreen = ceil(m_topScreen);

		double height = m_topScreen - m_bottomScreen;
		double width = m_rightScreen - m_leftScreen;

        INT_PTR sizey = m_2DScreen.GetCount();
		INT_PTR sizex = 0;
		if(sizey)
		{
			tdPixselArr** pData2d = m_2DScreen.GetData();
			sizex = (*pData2d)->GetSize();
		}

		int nWidth = (int)(float)((m_info.TransformVector / m_info.Near) * width);
		if(sizey < (INT_PTR)height || sizex < (INT_PTR)width)
		{
			int nHeiht = (int)(float)((m_info.TransformVector / m_info.Near) * height);
			nWidth = max(max(nHeiht, nWidth), max(sizey, sizex));
			Clear2DScreen();

			m_2DScreen.SetSize(nWidth);
			tdPixselArr** pData2d = m_2DScreen.GetData();
			for(INT_PTR i = 0; i < nWidth; ++i, ++pData2d)
			{
				*pData2d = new tdPixselArr();
				(*pData2d)->SetSize(nWidth);
			}
			m_resetObScreen.SetSize(nWidth);
			m_sizePosArr.SetSize(nWidth);
			m_posArr.SetSize(nWidth*nWidth);
		}
		else
		{
			int noldWidth = (int)(float)oldWidth;
			int noldHeight = (int)(float)oldHeight;
			if(noldWidth < 0 || noldHeight < 0)
			{
				noldWidth = sizex;
				noldHeight = sizey;
			}
			int resetLen = sizeof(CScreenPixsel) * noldWidth;
			int IntSize = sizeof(int);
			int *pSizePos = m_sizePosArr.GetData();
			int *pPos = m_posArr.GetData();
			int posZize = m_sizePosArr.GetCount();
			CScreenPixsel PIx;
			for(int i = 0; i < noldHeight; ++i,//)
				pSizePos++, pPos += posZize)
			{
				if(*pSizePos == 0)
					continue;
				// Optimize refreshing speed
				if(noldWidth / *pSizePos < 10)
				{
					memcpy(m_2DScreen[i]->GetData(),
						m_resetObScreen.GetData(), resetLen);
				}
				else
				{
					CScreenPixsel* pp = m_2DScreen[i]->GetData();
					for(int j = 0; j < *pSizePos; ++j)
						pp[*(pPos + j)] = PIx;
				}
				memset(pPos, 0, (*pSizePos) * IntSize);
			}
			memset(m_sizePosArr.GetData(), 0, posZize * IntSize);
		}
	}
		

	return true;
}

bool C3DObject::Translate3Dto2D(int xStart, int xStopSize)
{
	if(m_leftScreen == m_rightScreen 
		|| m_bottomScreen == m_topScreen)
		return true;
	int tempSize = xStopSize;
//	TurnShape(0.0, axis_y);
	double height = m_topScreen - m_bottomScreen;
	double width = m_rightScreen - m_leftScreen;

	int ls = (int)(float)m_leftScreen;
	int ts = (int)(float)m_topScreen;


	INT_PTR ncy = (int)(float)height;
	INT_PTR ncx = (int)(float)width;


	int sizey = m_CameraTranslated3dRowsArr.GetCount() - 1;
	if(sizey <= 0)
		return false;

	td3DPixselColumnArr** pData = m_CameraTranslated3dRowsArr.GetData();
	int sizex = (*pData)->GetCount() - 1;
	if(sizex <= 0)
		return false;
	if(xStopSize < 0 || xStopSize > sizex || 
		m_objectType == t3d_sphereBm || m_objectType == t3d_FlatBm)
		xStopSize = sizex;
	int realPos = 0;

	tdPixselArr** pData2d = m_2DScreen.GetData();

	// y 1 x 1
	CBase3DObjectPixsel* pPixsels11 = NULL;
	// y 2 x 1
	CBase3DObjectPixsel* pPixsels21 = NULL;
	// y 1 x 2
	CBase3DObjectPixsel* pPixsels12 = NULL;
	// y 2 x 2
	CBase3DObjectPixsel* pPixsels22 = NULL;

	BYTE color[4] = {0,0,0,0};
	BYTE c[4] = {0,0,0,0};
	int posZizeCount = m_sizePosArr.GetCount();

	bool bInsMod = ((xStart + tempSize) > m_bmWidth)?true:false;
	long pixselxPos = 0;
	int plusPosx = (m_objectType == t3d_sphereBm || m_objectType == t3d_FlatBm)?2:1;
	for(int posy = 0; posy < sizey; ++posy, ++pData) 
	{
		for(register int posx = 0; posx < xStopSize; posx += plusPosx)//, ++pPixsels11,
//			++pPixsels21)
		{
			switch(m_objectType)
			{
			case t3d_sphereBm:
			case t3d_FlatBm:
				//if(posx % 2)
				//	continue;
				pPixsels11 = (*(pData))->GetData() + posx;
				pixselxPos = pPixsels11->xpos;
				if(tempSize > 0)
					if(bInsMod)
					{
						if(pixselxPos < xStart && pixselxPos > (xStart+ tempSize - m_bmWidth))
							continue;
					}
					else
					{
						if(pixselxPos < xStart || pixselxPos > (xStart+ tempSize))
							continue;
					}
				realPos = posx;
				break;
			default:
				realPos = (posx + xStart) % sizex;
				break;
			}

			// y 1 x 1
			pPixsels11 = (*(pData))->GetData() + realPos;
			*((DWORD*)color) = pPixsels11->color;
			// if color 100% transparent then continue
			if(color[3] == 100)
				continue;
			// y 2 x 1
			pPixsels21 = (*(pData + 1))->GetData() + realPos;
			pPixsels12 = pPixsels11 + 1;
			pPixsels22 = pPixsels21 + 1;
//			double p[4][3] =
//			{
//				// y 1 x 1
//				{pPixsels11->p3D.x, pPixsels11->p3D.y, pPixsels11->p3D.z},
//				// y 1 x 2
//				{pPixsels12->p3D.x, pPixsels12->p3D.y, pPixsels12->p3D.z},
//				// y 2 x 2
//				{pPixsels22->p3D.x, pPixsels22->p3D.y, pPixsels22->p3D.z},
//				// y 2 x 1
//				{pPixsels21->p3D.x, pPixsels21->p3D.y, pPixsels21->p3D.z}
//			};
//			BYTE left = 0;
//			BYTE top = 0;
//			BYTE right = 0;
//			BYTE bottom = 0;
//			BYTE Near = 0;
//			BYTE Far = 0;
//
//			BYTE rPlus1 = 1;
//			for(; rPlus1 < 4; rPlus1++)
//			{
//				left = 
//					(p[left][axis_x] <= p[rPlus1][axis_x])?left:rPlus1;
//				Near = 
//					(p[Near][axis_z] <= p[rPlus1][axis_z])?Near:rPlus1;
//				bottom = 
//					(p[bottom][axis_y]<= p[rPlus1][axis_y])m?bottom:rPlus1;
//			}
//
//			if(p[Near][axis_z] <= m_info.Near)
//				continue;
//			right = (left + 2) % 4;
//			top = (bottom + 2) % 4;
//			Far = (Near + 2) % 4;
//
//			// if shape flat continue
////			if(p[left][axis_x] == p[right][axis_x]
////			|| p[top][axis_y] == p[bottom][axis_y])
////				continue;

			//int nposLeft = (int)(float)(p[left][axis_x]);//floor - 0.1
			//int nposTop = (int)(float)(p[top][axis_y]);//ceil + 0.005
			//int nposRight = (int)(float)(p[right][axis_x]);//ceil + 0.002
			//int nposBottom = (int)(float)(p[bottom][axis_y]);//floor - 0.1
			double totalz = (pPixsels11->p3D.z + pPixsels12->p3D.z + pPixsels22->p3D.z + pPixsels21->p3D.z) / 4.0;
			if(totalz <= m_info.Near)
				continue;

			int nposLeft = (int)(float)min((min(pPixsels11->p3D.x, pPixsels12->p3D.x)),(min(pPixsels22->p3D.x ,pPixsels21->p3D.x)));
			int nposTop = (int)(float)max((max(pPixsels11->p3D.y, pPixsels12->p3D.y)),(max(pPixsels22->p3D.y ,pPixsels21->p3D.y)));
			int nposRight = (int)(float)max((max(pPixsels11->p3D.x, pPixsels12->p3D.x)),(max(pPixsels22->p3D.x ,pPixsels21->p3D.x)));
			int nposBottom = (int)(float)min((min(pPixsels11->p3D.y, pPixsels12->p3D.y)),(min(pPixsels22->p3D.y ,pPixsels21->p3D.y)));

			const int pox = nposLeft;
			//double totalz = (p[Near][axis_z] + p[Far][axis_z]) / 2.0;

			int tsMinNposTop;
			for(; nposTop > nposBottom && (ts- nposTop) < ncy; --nposTop)
			{
				tsMinNposTop = ts - nposTop;
				if(tsMinNposTop < 0)
					continue;

				CScreenPixsel* sp = (*(pData2d + 
					(tsMinNposTop)))->GetData();
				int *pSizePos = m_sizePosArr.GetData() + tsMinNposTop;

				nposLeft = pox;
				sp += (nposLeft - ls);	

				for(; nposLeft < nposRight; ++nposLeft, ++sp)
				{
					if(sp->lastZ < totalz)// + 0.1
						continue;
					if(sp->lastZ == clean_z)
					{
						int *pPos = m_posArr.GetData() +
							(tsMinNposTop * posZizeCount + (*pSizePos));
						*pPos = (nposLeft - ls);
						++(*pSizePos);
					}
					sp->lastZ = totalz;
					if(sp->color == pPixsels11->color)
						continue;
					*((DWORD*)c) = sp->color;
					if(c[3] == 100 || m_objectType == t3d_sphere)
					{
						sp->color =	pPixsels11->color;
					}
					else
					{
						c[0] = (c[0] + color[0]) / 2;
						c[1] = (c[1] + color[1]) / 2;
						c[2] = (c[2] + color[2]) / 2;
						c[3] = (c[3] + color[3]) / 2;
						sp->color = *((DWORD*)c);
					}
/*					switch(m_objectType)
					{
					case t3d_rect:
					case t3d_sphere:
					case t3d_cylinder:
						sp->lastZ = totalz;
						break;
					}*/
				}
			}
		}
	}


	return true;
}

void C3DObject::Clear2DScreen(void)
{
	INT_PTR size = m_2DScreen.GetCount();
	tdPixselArr** pData = m_2DScreen.GetData();
	for(register INT_PTR i = 0; i < size; ++i)
		delete pData[i];
	m_2DScreen.RemoveAll();

}

// 3 <= diameter, 0 < circle <= 360,   -90 <= botoom < top <= 90
bool C3DObject::CreateSphereObject(int diameter, 
								   unsigned long color, 
								   double circle, 
								   double top, 
								   double bottom
								   , double fine)
{
	if(diameter <= 3 || circle <= 0.0 || circle > 360.0 ||
		-90.0 > bottom || top <= bottom || top > 90.0 || fine < 1.0)
		return false;

	m_objectType = t3d_sphere;
	ClearRows();
	double lfpi = atan2(0.0, -1.0);
	double lfcirclePixsel = ((double)diameter * lfpi) / fine;
	lfcirclePixsel = ceil(lfcirclePixsel);
	double mod4 = fmod(lfcirclePixsel, 4.0);
	if(mod4 != 0.0)
		lfcirclePixsel += 4.0 - mod4;
	int ncirclePixsel = (int)(float)
		ceil(lfcirclePixsel * circle / 360.0);
	const double circleStep = 360.0 / lfcirclePixsel;
	const double radius = (double)diameter / 2.0;
	int ySteps = 
		((int)(double)ceil((top - bottom) / circleStep)) + 1;

	m_3DRowsArr.SetSize(ySteps);
	m_Translated3dRowsArr.SetSize(ySteps);
	m_CameraTranslated3dRowsArr.SetSize(ySteps);
	td3DPixselColumnArr** pData = m_3DRowsArr.GetData();
	td3DPixselColumnArr** pData2 = m_Translated3dRowsArr.GetData();
	td3DPixselColumnArr** pData3 = m_CameraTranslated3dRowsArr.GetData();

	CBase3DObjectPixsel pixsel;
	CBase3DObjectPixsel* pPixsels = NULL;
	CBase3DObjectPixsel* pPixsels2 = NULL;

	double cord = 0.0, angley = top;
	double anglex = 0.0;
	for(int posy = 0; posy < ySteps; ++posy,
		angley -= circleStep, ++pData, ++pData2, ++pData3, anglex = 0.0)
	{
		cord = cos(angley * g_degtorad) * radius;
		*pData = new td3DPixselColumnArr;
		*pData2 = new td3DPixselColumnArr;
		*pData3 = new td3DPixselColumnArr;
		(*pData)->SetSize(ncirclePixsel + 1);
		(*pData2)->SetSize(ncirclePixsel + 1);
		(*pData3)->SetSize(ncirclePixsel + 1);
		pPixsels = (*pData)->GetData();
		pPixsels2 = (*pData2)->GetData();
		for(register int xpos = 0; xpos < ncirclePixsel; ++xpos,
			anglex += circleStep, ++pPixsels, ++pPixsels2)
		{
			pixsel.color = (posy != ySteps)?color:0x64000000;
			pixsel.p3D.x = cos(anglex * g_degtorad) * cord;
			pixsel.p3D.z = sin(anglex * g_degtorad) * cord;
			pixsel.p3D.y = sin(angley * g_degtorad) * radius;
			//pixsel.p3D.SetOp();
			*pPixsels = *pPixsels2 = pixsel;
		}
		if(circle == 360.0)
			anglex = 0.0;
		pixsel.color = 0x64000000;
		pixsel.p3D.x = cos(anglex * g_degtorad) * cord;
		pixsel.p3D.z = sin(anglex * g_degtorad) * cord;
		pixsel.p3D.y = sin(angley * g_degtorad) * radius;
		//pixsel.p3D.SetOp();
		*pPixsels = *pPixsels2 = pixsel;
	}

	TurnShape(0.0, axis_y);
	return true;
}

// topDiameter and topDameter one must be > then 0 and non < 0, height > 0, startAngle < endAngle and > 0 < 360
bool C3DObject::CreateCylinderObject(int topDiameter, 
									 int bottomDiameter, 
									 int height, 
									 unsigned long color, 
									 double circle, double fine)
{
	if((topDiameter +  bottomDiameter) <= 0 || topDiameter < 0 || 
		bottomDiameter < 0 || height <= 0 || 
		circle < 0.0 || circle > 360.0)
		return false;

	m_objectType = t3d_cylinder;
	ClearRows();
	double lfpi = atan2(0.0, -1.0);
	int diameter = max( topDiameter, bottomDiameter);
	double lfcirclePixsel = ((double)diameter * lfpi) / fine;
	lfcirclePixsel = ceil(lfcirclePixsel);
	int ncirclePixsel = (int)(float)
		ceil(lfcirclePixsel * circle / 360.0);
	const double circleStep = 360.0 / lfcirclePixsel;
	double radius = (double)topDiameter / 2.0;
	double modFine = fmod((double)height, fine) / fine;
	double radiusEnlargement = 
		(double)(bottomDiameter - topDiameter) * fine
		/ (((double)height  + modFine) * 2.0);

	double lfheight = ((double)height + modFine) / 2.0;
	height /= (int)(float)fine;
	height++;

	m_3DRowsArr.SetSize(height);
	m_Translated3dRowsArr.SetSize(height);
	m_CameraTranslated3dRowsArr.SetSize(height);
	td3DPixselColumnArr** pData = m_3DRowsArr.GetData();
	td3DPixselColumnArr** pData2 = m_Translated3dRowsArr.GetData();
	td3DPixselColumnArr** pData3 = m_CameraTranslated3dRowsArr.GetData();

	CBase3DObjectPixsel pixsel;
	CBase3DObjectPixsel* pPixsels = NULL;
	CBase3DObjectPixsel* pPixsels2 = NULL;

	double anglex = 0.0;
	for(int posy = 0; posy < height; ++posy, ++pData, ++pData2, ++pData3
		, radius += radiusEnlargement, lfheight -= fine)
	{
		*pData = new td3DPixselColumnArr;
		*pData2 = new td3DPixselColumnArr;
		*pData3 = new td3DPixselColumnArr;
		(*pData)->SetSize(ncirclePixsel + 1);
		(*pData2)->SetSize(ncirclePixsel + 1);
		(*pData3)->SetSize(ncirclePixsel + 1);
		pPixsels = (*pData)->GetData();
		pPixsels2 = (*pData2)->GetData();
		for(register int xpos = 0; xpos < ncirclePixsel; ++xpos,
			anglex += circleStep, ++pPixsels, ++pPixsels2)
		{
			pixsel.color = (posy != height)?color:0x64000000;
			pixsel.p3D.y = lfheight;
			pixsel.p3D.x = cos(anglex * g_degtorad) * radius;
			pixsel.p3D.z = sin(anglex * g_degtorad) * radius;
			//pixsel.p3D.SetOp();
			*pPixsels = *pPixsels2 = pixsel;
		}
		anglex = 0.0;
		pixsel.color = 0x64000000;
		pixsel.p3D.y = lfheight;
		pixsel.p3D.x = cos(anglex * g_degtorad) * radius;
		pixsel.p3D.z = sin(anglex * g_degtorad) * radius;
		//pixsel.p3D.SetOp();
		*pPixsels = *pPixsels2 = pixsel;
	}

	TurnShape(0.0, axis_y);
	return true;
}


CDPoint C3DObject::GetAngleCosSin(double angle)
{
	CDPoint p(cos(angle), sin(angle));
	return p;
}

bool C3DObject::CreateFlatSpiralObject(int width, 
									   int height, 
									   int space, 
									   int minRadius, 
									   double circle, 
									   COLORREF col)
{
	if(width < 6 || height < 1 || (height - space) < 0 || minRadius < 1 ||
		circle <= 0)
		return false;

	double lfWidthStep = circle / (double)width;
	double lfHeightPerStepIncrease = 
		((double)(height + space) / 360.0) * lfWidthStep;
	double maxRadius = (double)(minRadius + height);

	height++;

	m_3DRowsArr.SetSize(height);
	m_Translated3dRowsArr.SetSize(height);
	m_CameraTranslated3dRowsArr.SetSize(height);
	td3DPixselColumnArr** pData = m_3DRowsArr.GetData();
	td3DPixselColumnArr** pData2 = m_Translated3dRowsArr.GetData();
	td3DPixselColumnArr** pData3 = m_CameraTranslated3dRowsArr.GetData();

	CBase3DObjectPixsel pixsel;
	CBase3DObjectPixsel* pPixsels = NULL;
	CBase3DObjectPixsel* pPixsels2 = NULL;

	double anglex = 0.0;
	double radius = 0;
	for(int posy = 0; posy < height; ++posy, ++pData, 
		++pData2, ++pData3, --maxRadius)
	{
		radius = maxRadius;
		*pData = new td3DPixselColumnArr;
		*pData2 = new td3DPixselColumnArr;
		*pData3 = new td3DPixselColumnArr;
		(*pData)->SetSize(width + 1);
		(*pData2)->SetSize(width + 1);
		(*pData3)->SetSize(width + 1);
		pPixsels = (*pData)->GetData();
		pPixsels2 = (*pData2)->GetData();
		for(register int xpos = 0; xpos < width; ++xpos,
			anglex += lfWidthStep, ++pPixsels, ++pPixsels2
			, radius += lfHeightPerStepIncrease)
		{
			pixsel.color = (posy != height)?col:0x64000000;
			pixsel.p3D.y = sin(anglex * g_degtorad) * radius;
			pixsel.p3D.x = cos(anglex * g_degtorad) * radius;
			*pPixsels = *pPixsels2 = pixsel;
		}
		pixsel.color = 0x64000000;
		pixsel.p3D.y = sin(anglex * g_degtorad) * radius;
		pixsel.p3D.x = cos(anglex * g_degtorad) * radius;
		*pPixsels = *pPixsels2 = pixsel;
		anglex = 0.0;
	}

	TurnShape(0.0, axis_y);

	return false;
}

bool C3DObject::CReateCircleLineObject(int diameter, unsigned long color, double fine, double circle, int num)
{
	if(diameter <= 3 || circle <= 0.0 || circle > 360.0 ||
		fine < 1.0)
		return false;

	m_objectType = t3d_circle;
	ClearRows();
	double lfpi = atan2(0.0, -1.0);
	double lfcirclePixsel = ((double)diameter * lfpi) / fine;
	lfcirclePixsel = ceil(lfcirclePixsel);
	double mod4 = fmod(lfcirclePixsel, 4.0);
	if(mod4 != 0.0)
		lfcirclePixsel += 4.0 - mod4;
	int ncirclePixsel = (int)(float)
		ceil(lfcirclePixsel * circle / 360.0);
	const double circleStep = 360.0 / lfcirclePixsel;
	CDPoint tp(cos(g_degtorad * circleStep), sin(g_degtorad * circleStep));
	const double radius = (double)diameter / 2.0;
	int ySteps = 3;


	m_3DRowsArr.SetSize(ySteps * num);
	m_Translated3dRowsArr.SetSize(ySteps * num);
	m_CameraTranslated3dRowsArr.SetSize(ySteps * num);
	td3DPixselColumnArr** pData = m_3DRowsArr.GetData();
	td3DPixselColumnArr** pData2 = m_Translated3dRowsArr.GetData();
	td3DPixselColumnArr** pData3 = m_CameraTranslated3dRowsArr.GetData();

	CBase3DObjectPixsel pixsel;
	CBase3DObjectPixsel** pPixsels = new CBase3DObjectPixsel*[ySteps * num];
	CBase3DObjectPixsel** pPixsels2 = new CBase3DObjectPixsel*[ySteps * num];
	for(int posy = 0; posy < ySteps * num; ++posy,
		++pData, ++pData2, ++pData3)
	{
		*pData = new td3DPixselColumnArr;
		*pData2 = new td3DPixselColumnArr;
		*pData3 = new td3DPixselColumnArr;
		(*pData)->SetSize(ncirclePixsel + 1);
		(*pData2)->SetSize(ncirclePixsel + 1);
		(*pData3)->SetSize(ncirclePixsel + 1);
		pPixsels[posy] = (*pData)->GetData();
		pPixsels2[posy] = (*pData2)->GetData();
	}

	double angYTurn = 180.0 / (double)num;
	double toTurnY = 0.0;
	for(int nCircle = 0; nCircle < num; ++nCircle, toTurnY += angYTurn)
	{
		int numOfsetXArr = nCircle * ySteps;
		CDPoint ptYTurn(cos(g_degtorad * toTurnY), sin(g_degtorad * toTurnY));
		CLineBase lb(radius, fine);
		for(register int xpos = 0; xpos < ncirclePixsel; ++xpos,
			 ++pPixsels[numOfsetXArr], ++pPixsels2[numOfsetXArr],
			++pPixsels[1 + numOfsetXArr], ++pPixsels2[1 + numOfsetXArr],
			++pPixsels[2 + numOfsetXArr], ++pPixsels2[2 + numOfsetXArr])
		{
			pixsel.color = color;
			pixsel.p3D = lb.p1;
			Turn(pixsel.p3D, ptYTurn, axis_y);
			//pixsel.p3D.SetOp();
			*pPixsels[numOfsetXArr] = *pPixsels2[numOfsetXArr] = pixsel;
			pixsel.p3D = lb.p2;
			Turn(pixsel.p3D, ptYTurn, axis_y);
			//pixsel.p3D.SetOp();
			*pPixsels[1 + numOfsetXArr] = *pPixsels2[1 + numOfsetXArr] = pixsel;
			pixsel.color = 0x64000000;
			pixsel.p3D = lb.p3;
			Turn(pixsel.p3D, ptYTurn, axis_y);
			//pixsel.p3D.SetOp();
			*pPixsels[2 + numOfsetXArr] = *pPixsels2[2 + numOfsetXArr] = pixsel;

			Turn(lb.p1, tp, axis_z);
			Turn(lb.p2, tp, axis_z);
			Turn(lb.p3, tp, axis_z);
		}
		pixsel.color = 0x64000000;
		pixsel.p3D = lb.p1;
		Turn(pixsel.p3D, ptYTurn, axis_y);
		//pixsel.p3D.SetOp();
		*pPixsels[numOfsetXArr] = *pPixsels2[numOfsetXArr] = pixsel;
		pixsel.p3D = lb.p2;
		Turn(pixsel.p3D, ptYTurn, axis_y);
		//pixsel.p3D.SetOp();
		*pPixsels[1 + numOfsetXArr] = *pPixsels2[1 + numOfsetXArr] = pixsel;
		pixsel.p3D = lb.p3;
		Turn(pixsel.p3D, ptYTurn, axis_y);
		//pixsel.p3D.SetOp();
		*pPixsels[2 + numOfsetXArr] = *pPixsels2[2 + numOfsetXArr] = pixsel;

		++pPixsels[numOfsetXArr];	  
		++pPixsels[1 + numOfsetXArr]; 
		++pPixsels[2 + numOfsetXArr]; 
		++pPixsels2[numOfsetXArr];
		++pPixsels2[1 + numOfsetXArr];
		++pPixsels2[2 + numOfsetXArr];

	}
	delete [] pPixsels;
	delete [] pPixsels2;


	TurnShape(0.0, axis_y);
	return true;
}

bool C3DObject::CreateSphereBmObj(int diameter, 
								  CMyFBitmap& bm, 
								  double top, 
								  double bottom, 
								  unsigned long transperantcol)
{
	if(diameter < 3 || -90.0 > bottom || top <= bottom || top > 90.0)
		return false;

	m_objectType = t3d_sphereBm;
	ClearRows();
	m_3DRowsArr.SetSize(2);
	m_Translated3dRowsArr.SetSize(2);
	m_CameraTranslated3dRowsArr.SetSize(2);
	td3DPixselColumnArr** pData = m_3DRowsArr.GetData();
	td3DPixselColumnArr** pData2 = m_Translated3dRowsArr.GetData();
	td3DPixselColumnArr** pData3 = m_CameraTranslated3dRowsArr.GetData();

	CBase3DObjectPixsel pixsel, pixsely2, pixsel3;
	pixsely2.color = 0x64000000;
	m_bmWidth = bm.m_width;
	const double xStep = 360.0 / (double)m_bmWidth;
	const double yStep = (top-bottom) /(double)bm.m_height;
	const double radius = (double)diameter / 2.0;

	*pData = new td3DPixselColumnArr;
	*pData2 = new td3DPixselColumnArr;
	*pData3 = new td3DPixselColumnArr;
	td3DPixselColumnArr& pPixsels11 = *(*pData);
	td3DPixselColumnArr& pPixsels21 = *(*pData2);
	td3DPixselColumnArr& pPixsels31 = *(*pData3);

	pData++;
	pData2++;
	pData3++;
	*pData = new td3DPixselColumnArr;
	*pData2 = new td3DPixselColumnArr;
	*pData3 = new td3DPixselColumnArr;
	td3DPixselColumnArr& pPixsels12 = *(*pData);
	td3DPixselColumnArr& pPixsels22 = *(*pData2);
	td3DPixselColumnArr& pPixsels32 = *(*pData3);

	COLORREF trans = transperantcol & 0XFF000000;
	COLORREF transCol = transperantcol & 0X00FFFFFF;
	CDC* pDC = bm.operator CDC *();

	double cord = 0.0, angley = top, angley2 = top - yStep;
	double cord2 = 0.0;
	for(int posy = 0; posy < bm.m_height; ++posy, angley -= yStep, angley2 -= yStep)
	{
		cord = cos(angley * g_degtorad) * radius;
		cord2 = cos(angley2 * g_degtorad) * radius;
		double anglex = 0.0, anglex2 = xStep;
		for(int posx = 0; posx < bm.m_width; ++posx, anglex += xStep, anglex2 += xStep)
		{
			COLORREF pixCol = pDC->GetPixel(posx,posy);
			if(pixCol == transCol)
				continue;
			pixsel.color = pixCol | trans;
			pixsel.p3D.x = cos(anglex * g_degtorad) * cord;
			pixsel.p3D.z = sin(anglex * g_degtorad) * cord;
			pixsel.p3D.y = sin(angley * g_degtorad) * radius;
			pixsel.xpos = posx;
			//pixsel.p3D.SetOp();

			pPixsels11.Add(pixsel);
			pPixsels21.Add(pixsel);

			pPixsels31.Add(pixsel3);
			pPixsels32.Add(pixsel3);
			pPixsels31.Add(pixsel3);
			pPixsels32.Add(pixsel3);

			pixsel.color = 0x64000000;
			pixsel.p3D.x = cos(anglex2 * g_degtorad) * cord;
			pixsel.p3D.z = sin(anglex2 * g_degtorad) * cord;
			pixsel.p3D.y = sin(angley * g_degtorad) * radius;
			pixsel.xpos = -1;
			//pixsel.p3D.SetOp();

			pPixsels11.Add(pixsel);
			pPixsels21.Add(pixsel);

			pixsel.p3D.x = cos(anglex * g_degtorad) * cord2;
			pixsel.p3D.z = sin(anglex * g_degtorad) * cord2;
			pixsel.p3D.y = sin(angley2 * g_degtorad) * radius;
			//pixsel.p3D.SetOp();

			pPixsels12.Add(pixsel);
			pPixsels22.Add(pixsel);

			pixsel.p3D.x = cos(anglex2 * g_degtorad) * cord2;
			pixsel.p3D.z = sin(anglex2 * g_degtorad) * cord2;
			pixsel.p3D.y = sin(angley2 * g_degtorad) * radius;
			//pixsel.p3D.SetOp();

			pPixsels12.Add(pixsel);
			pPixsels22.Add(pixsel);
		}
	}


	TurnShape(0.0, axis_y);
	return true;
}

bool C3DObject::CreateFlatBmObj(CMyFBitmap& bm, unsigned long transperantcol)
{
 	m_objectType = t3d_FlatBm;
	m_bmWidth = bm.m_width;

	ClearRows();
	m_3DRowsArr.SetSize(2);
	m_Translated3dRowsArr.SetSize(2);
	m_CameraTranslated3dRowsArr.SetSize(2);
	td3DPixselColumnArr** pData = m_3DRowsArr.GetData();
	td3DPixselColumnArr** pData2 = m_Translated3dRowsArr.GetData();
	td3DPixselColumnArr** pData3 = m_CameraTranslated3dRowsArr.GetData();

	CBase3DObjectPixsel pixsel, pixsely2, pixsel3;
	pixsely2.color = 0x64000000;

	*pData = new td3DPixselColumnArr;
	*pData2 = new td3DPixselColumnArr;
	*pData3 = new td3DPixselColumnArr;
	td3DPixselColumnArr& pPixsels11 = *(*pData);
	td3DPixselColumnArr& pPixsels21 = *(*pData2);
	td3DPixselColumnArr& pPixsels31 = *(*pData3);

	pData++;
	pData2++;
	pData3++;
	*pData = new td3DPixselColumnArr;
	*pData2 = new td3DPixselColumnArr;
	*pData3 = new td3DPixselColumnArr;
	td3DPixselColumnArr& pPixsels12 = *(*pData);
	td3DPixselColumnArr& pPixsels22 = *(*pData2);
	td3DPixselColumnArr& pPixsels32 = *(*pData3);

	COLORREF trans = transperantcol & 0XFF000000;
	COLORREF transCol = transperantcol & 0X00FFFFFF;
	CDC* pDC = bm.operator CDC *();
	
	
	double y = (double)bm.m_height / 2.0;
	for(int posy = 0; posy < bm.m_height; ++posy, --y)
	{
		double x = -(double)bm.m_width / 2.0;
		for(int posx = 0; posx < bm.m_width; ++posx, ++x)
		{
			COLORREF pixCol = pDC->GetPixel(posx,posy);
			if(pixCol == transCol)
				continue;
			pixsel.color = pixCol | trans;
			pixsel.p3D.x = x;
			pixsel.p3D.y = y;
			pixsel.xpos = posx;
			//pixsel.p3D.SetOp();

			pPixsels11.Add(pixsel);
			pPixsels21.Add(pixsel);

			pPixsels31.Add(pixsel3);
			pPixsels32.Add(pixsel3);
			pPixsels31.Add(pixsel3);
			pPixsels32.Add(pixsel3);

			pixsel.color = 0x64000000;
			pixsel.p3D.x = x + 1.0;
			pixsel.p3D.y = y;
			pixsel.xpos = -1;
			//pixsel.p3D.SetOp();

			pPixsels11.Add(pixsel);
			pPixsels21.Add(pixsel);

			pixsel.p3D.x = x;
			pixsel.p3D.y = y + 1.0;
			//pixsel.p3D.SetOp();

			pPixsels12.Add(pixsel);
			pPixsels22.Add(pixsel);

			pixsel.p3D.x = x + 1.0;
			pixsel.p3D.y = y + 1.0;
			//pixsel.p3D.SetOp();

			pPixsels12.Add(pixsel);
			pPixsels22.Add(pixsel);
		}
	}


	TurnShape(0.0, axis_y);
	return false;
}

void C3DObject::TurnLightPt(double angle, Axis ax, bool bReset)
{
	if(bReset)
	{
		m_lightPt.x = 0.0;
		m_lightPt.y = 0.0;
		m_lightPt.z = -1.0;
		return;
	}
	angle *= m_degtorad;
	CDPoint xy = GetAngleCosSin(angle);
	Turn(m_lightPt, xy, ax);
}

void C3DObject::Transform(bool bWorldTranslation)
{
	INT_PTR sizey = m_3DRowsArr.GetCount();
	INT_PTR sizex = 0;
	td3DPixselColumnArr** pData = m_3DRowsArr.GetData();
	td3DPixselColumnArr** pData2 = m_Translated3dRowsArr.GetData();
	CBase3DObjectPixsel* pPixsels = NULL;
	CBase3DObjectPixsel* pPixsels2 = NULL;

	for(INT_PTR y = 0; y < sizey; ++y, ++pData, ++pData2)
	{
		sizex = (*pData)->GetCount();
		pPixsels = (*pData)->GetData();
		pPixsels2 = (*pData2)->GetData();
		for(register INT_PTR x = 0; x < sizex; ++x, ++pPixsels, ++pPixsels2)
		{
			m_matrix.Transform(pPixsels->p3D, pPixsels2->p3D);
		}
	}

	if(bWorldTranslation)
		TurnShape(0.0, axis_y);
}
