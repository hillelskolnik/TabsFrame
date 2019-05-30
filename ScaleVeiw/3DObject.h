#pragma once
#include "atltypes.h"
#include <math.h>
#include "dpoint.h"
#include "deff.h"


struct C3DPoint
{
	C3DPoint(double X = 0.0, double Y = 0.0, double Z = 0.0)
		:x(X),y(Y),z(Z)/*,op(noNull)*/{}
	double x;
	double y;
	double z;
};

struct CMatrix
{
	double m[3][3];
	static double m_degtorad;
	CMatrix(){Init();}
	void Init(void)
	{
		m[0][0] = 1.0;
		m[0][1] = 0.0;
		m[0][2] = 0.0;
		m[1][0] = 0.0;
		m[1][1] = 1.0;
		m[1][2] = 0.0;
		m[2][0] = 0.0;
		m[2][1] = 0.0;
		m[2][2] = 1.0;
	}
	void RotX(double a)
	{
		double c = cos(a *m_degtorad);    
		double s = sin(a *m_degtorad);
		m[0][0] = 1.0;
		m[0][1] = 0.0;
		m[0][2] = 0.0;
		m[1][0] = 0.0;
		m[1][1] = c;
		m[1][2] = s;
		m[2][0] = 0.0;
		m[2][1] = -s;
		m[2][2] = c;
	}
	void RotY(double a)
	{
		double c = cos(a *m_degtorad);    
		double s = sin(a *m_degtorad);
		m[0][0] = c;
		m[0][1] = 0.0;
		m[0][2] = -s;
		m[1][0] = 0.0;
		m[1][1] = 1.0;
		m[1][2] = 0.0;
		m[2][0] = s;
		m[2][1] = 0.0;
		m[2][2] = c;
	}
	void RotZ(double a)
	{
		double c = cos(a *m_degtorad);    
		double s = sin(a *m_degtorad);
		m[0][0] = c;
		m[0][1] = -s;
		m[0][2] = 0.0;
		m[1][0] = s;
		m[1][1] = c;
		m[1][2] = 0.0;
		m[2][0] = 0.0;
		m[2][1] = 0.0;
		m[2][2] = 1.0;
	}
	void Mul(CMatrix& m1, CMatrix& m2)
	{
		m[0][0] = m1.m[0][0]*m2.m[0][0] + m1.m[0][1]*m2.m[1][0] + m1.m[0][2]*m2.m[2][0];
		m[0][1] = m1.m[0][0]*m2.m[0][1] + m1.m[0][1]*m2.m[1][1] + m1.m[0][2]*m2.m[2][1];
		m[0][2] = m1.m[0][0]*m2.m[0][2] + m1.m[0][1]*m2.m[1][2] + m1.m[0][2]*m2.m[2][2];
		m[1][0] = m1.m[1][0]*m2.m[0][0] + m1.m[1][1]*m2.m[1][0] + m1.m[1][2]*m2.m[2][0];
		m[1][1] = m1.m[1][0]*m2.m[0][1] + m1.m[1][1]*m2.m[1][1] + m1.m[1][2]*m2.m[2][1];
		m[1][2] = m1.m[1][0]*m2.m[0][2] + m1.m[1][1]*m2.m[1][2] + m1.m[1][2]*m2.m[2][2];
		m[2][0] = m1.m[2][0]*m2.m[0][0] + m1.m[2][1]*m2.m[1][0] + m1.m[2][2]*m2.m[2][0];
		m[2][1] = m1.m[2][0]*m2.m[0][1] + m1.m[2][1]*m2.m[1][1] + m1.m[2][2]*m2.m[2][1];
		m[2][2] = m1.m[2][0]*m2.m[0][2] + m1.m[2][1]*m2.m[1][2] + m1.m[2][2]*m2.m[2][2];
	}
	void Transform(C3DPoint& p, C3DPoint& pDest)
	{
		pDest.x = (p.x * m[0][0] + p.y * m[0][1] + p.z * m[0][2]);
		pDest.y = (p.x * m[1][0] + p.y * m[1][1] + p.z * m[1][2]);
		pDest.z = (p.x * m[2][0] + p.y * m[2][1] + p.z * m[2][2]);
	}
	void Scale(double s)
	{
		m[0][0] *= s; 
		m[0][1] *= s; 
		m[0][2] *= s; 
		m[1][0] *= s; 
		m[1][1] *= s; 
		m[1][2] *= s; 
		m[2][0] *= s; 
		m[2][1] *= s; 
		m[2][2] *= s; 
	}
};

struct CLineBase
{
	CLineBase(double shift, double fine)
		:p1(shift, 0, fine * 0.5)
		,p2(shift - 0.5 * fine, 0, -fine * 0.5)
		,p3(shift - fine, 0, fine * 0.5)
	{}
	C3DPoint p1;
	C3DPoint p2;
	C3DPoint p3;
};

//typedef CArray<C3DPoint> tdC3DPointArr;

struct CBase3DObjectPixsel
{
	CBase3DObjectPixsel():color(0),xpos(-1){}
	unsigned long color;
	unsigned long xpos;
	C3DPoint p3D;
};

typedef CArray<CBase3DObjectPixsel> td3DPixselColumnArr;
typedef CArray<td3DPixselColumnArr*, td3DPixselColumnArr*> td3DRowsArr;

#define clean_z 1000000.0

struct CScreenPixsel
{
	CScreenPixsel():color(0x64000000),lastZ(clean_z){}
	unsigned long color;
	double lastZ;
};
typedef CArray<CScreenPixsel> tdPixselArr;

typedef CArray<tdPixselArr*, tdPixselArr*> tdPixelRowArr;



enum T3D
{
	t3d_rect = 1
	,t3d_sphere
	,t3d_sphereBm
	,t3d_FlatBm
	,t3d_cylinder
	,t3d_circle
};

struct CScreenInfo
{
	CScreenInfo()
		: TransformVector(0)
		, cx(0)
		, cy(0)
		, Near(0)
	{}

	// The distance from the viewer to the far clipping plane (always positive).
	// m_TransformVector / z * (x or y)
	double TransformVector;
	// Logic width of 3D screen
	int cx;
	// Logic height of 3D screen
	int cy;
	// The distance from the viewer to the near clipping plane (always positive).
	double Near;
	// Represent the middle space point
	C3DPoint middleSpace;
};

typedef CArray<int> tdIntArr;

class C3DObject
{
public:
	C3DObject(const CScreenInfo &info);
	virtual ~C3DObject(void);
protected:
	// Object Shifting point
	C3DPoint m_ShiftPoint;
	C3DPoint m_BaseShiftPoint;
	C3DPoint m_turnVec;
public:
	void ShiftObjectCenter(double shift, Axis ax, bool bBase);
	// Set object Shift point axises = 0
	void ResetShift(void);
	inline static void Turn(double& x, double& y, const CDPoint& xy);
	inline static void Turn(C3DPoint& threeDpoint, const CDPoint& xy, Axis ax);
	void TurnObjectCenter(double angle, Axis ax, bool bBase);
protected:
	td3DRowsArr m_3DRowsArr;
	void ClearRows(void);
public:
	// Center of pixsel map x= y = z = 0
	bool CreatObjectPixselMap(int cx, int cy, unsigned long transColor = 0x64000000, int num=1);
	// filling color acording the position in the memory x y arrays
	bool FillRect(int x, int y, int cx, int cy, unsigned long color,
		eFiillRectOp op, CFillRectData data);
protected:
	td3DRowsArr m_Translated3dRowsArr;
	td3DRowsArr m_CameraTranslated3dRowsArr;
public:
	bool ResetTranslation(void);
	bool TurnShape(double angle, Axis ax, int bLastTurn = true);
	bool TurnBaseShape(double angle, Axis ax);
protected:
	double m_leftScreen;
	double m_topScreen;
	double m_rightScreen;
	double m_bottomScreen;
public:
	bool Translate3Dto2D(int xStart, int xStopSize);
protected:
	tdPixelRowArr m_2DScreen;
	void Clear2DScreen(void);
	T3D m_objectType;
	friend class C3DScreen;
	// Erea to paint transperant beror next paint
	CRect m_clearEreaRc;
	const CScreenInfo& m_info;
public:
	static double m_degtorad;
	// 3 <= diameter, 0 < circle <= 360,   -90 <= botoom < top <= 90
	bool CreateSphereObject(int diameter, unsigned long color, double circle, double top, double bottom, double fine);
	int m_nPosTop;
	// topDiameter and topDameter one must be > then 0 and non < 0, height > 0, circle > 0 and <+ 360
	bool CreateCylinderObject(int topDiameter, int bottomDiameter, int height, unsigned long color, double circle, double fine);
protected:
	CDPoint GetAngleCosSin(double angle);
	tdPixselArr m_resetObScreen;
	tdIntArr m_sizePosArr;
	tdIntArr m_posArr;
public:
	bool CreateFlatSpiralObject(int width, int height, int space, int minRadius, double circle, COLORREF col);
protected:
	bool m_bPause;
public:
	bool CReateCircleLineObject(int diameter, unsigned long color, double fine, double circle, int num);
public:
	bool CreateSphereBmObj(int diameter, CMyFBitmap& bm, double top, double bottom, unsigned long transperantcol);
protected:
	int m_bmWidth;
public:
	bool CreateFlatBmObj(CMyFBitmap& bm, unsigned long transperantcol);
protected:
	C3DPoint m_lightPt;
public:
	void TurnLightPt(double angle, Axis ax, bool bReset);
public:

//	static double VectorXVector(C3DPoint& p3d, const double& x, const double& y, const double& z)
//	{
//		//switch(p3d.op)
//		//{
//		//case xNull:
//		//	return p3d.y*y + p3d.z*z;
//		//case yNull:
//		//	return p3d.x*x + p3d.z*z;
//		//case zNull:
//		//	return p3d.x*x + p3d.y*y;
//		//case xyNull:
//		//	return p3d.z*z;
//		//case yzNull:
//		//	return p3d.x*x;
//		//case xzNull:
//		//	return p3d.y*y;
//		//case noNull:
//		//return p3d.x*x - p3d.y*y + p3d.z*z;
//		//}
//		////allNull
//		return 0.0;
//	}
//	void Turn(C3DPoint& p3d)
//	{
//		//switch(m_matrix.op)
//		//{
//		//case xt:
//		//	{
//		//		double y = VectorXVector(p3d,
//		//			m_matrix.matrix[1],m_matrix.matrix[4],m_matrix.matrix[7]);
//		//		p3d.z = VectorXVector(p3d,
//		//			m_matrix.matrix[2],m_matrix.matrix[5],m_matrix.matrix[8]);
//		//		p3d.y = y;
//		//	}
//		//	break;
//		//case yt:
//		//	{
//		//		double x = VectorXVector(p3d,
//		//			m_matrix.matrix[0],m_matrix.matrix[3],m_matrix.matrix[6]);
//		//		p3d.z = VectorXVector(p3d,
//		//			m_matrix.matrix[2],m_matrix.matrix[5],m_matrix.matrix[8]);
//		//		p3d.x = x;
//		//	}
//		//	break;
//		//case zt:
//		//	{
//		//		double x = VectorXVector(p3d,
//		//			m_matrix.matrix[0],m_matrix.matrix[3],m_matrix.matrix[6]);
//		//		p3d.y = VectorXVector(p3d,
//		//			m_matrix.matrix[1],m_matrix.matrix[4],m_matrix.matrix[7]);
//		//		p3d.x = x;
//		//	}
//		//	break;
//		//case allt:
//		//	{
//				//double x = p3d.x*m_matrix.matrix[0]-
//				//	(p3d.z*p3d.y + m_matrix.matrix[6]*m_matrix.matrix[3]);
//				//	//VectorXVector(p3d,
//				//	//m_matrix.matrix[0],m_matrix.matrix[3],m_matrix.matrix[6]);
//				//double y = p3d.y*m_matrix.matrix[4]-
//				//	(p3d.z*p3d.x + m_matrix.matrix[7]*m_matrix.matrix[1]);
//				//	//VectorXVector(p3d,
//				//	//m_matrix.matrix[1],m_matrix.matrix[4],m_matrix.matrix[7]);
//				//p3d.z = p3d.z*m_matrix.matrix[8]-
//				//	(p3d.y*p3d.x + m_matrix.matrix[5]*m_matrix.matrix[2]);
//				//	//VectorXVector(p3d,
//				//	//m_matrix.matrix[2],m_matrix.matrix[5],m_matrix.matrix[8]);
//				//p3d.x = x;
//				//p3d.y = y;
//		//	}
//		//	break;
//		//}
//	}
////protected:
////	CMatrix m_matrix;
////public:
////	void TurnMatrix(Axis ax, double ang);
protected:
	CMatrix m_matrix;
public:
	void Transform(bool bWorldTranslation);
};



inline void C3DObject::Turn(double& x, double& y, const CDPoint& xy)
{
	double ox = x;
	x = x * xy.x - y * xy.y;
	y = y * xy.x + ox * xy.y;


}

inline void C3DObject::Turn(C3DPoint& threeDpoint, const CDPoint& xy, Axis ax)
{
	switch(ax)
	{
	case axis_x:
		Turn(threeDpoint.z, threeDpoint.y, xy);
		break;
	case axis_y:
		Turn(threeDpoint.x, threeDpoint.z, xy);
		break;
	case axis_z:
		Turn(threeDpoint.x, threeDpoint.y, xy);
		break;
	}
}



typedef CMap<int, int, C3DObject*, C3DObject*> td3DObjectMap;
