// BasicShape.cpp: implementation of the CBasicShape class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ScaleVeiw.h"
#include "BasicShape.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBasicShape::CBasicShape()
{

}

CBasicShape::~CBasicShape()
{

}

CDPoint CBasicShape::GetDPoint(double ang, double len, const CDPoint &p)
{
	while(0.0 > ang)
		ang += 360.0;
	while(360.0 < ang)
		ang -= 360.0;
	double x = cos(ang * g_degtorad) * len;
	double y = sin(ang * g_degtorad) * len;
	CDPoint pt(x + p.x, y + p.y);
	return pt;
}

double CBasicShape::GetAng(const CDPoint &p, const CDPoint &pm)
{
	return atan2(p.y - pm.y, p.x - pm.x) * g_radtodeg;
}

double CBasicShape::GetLength(const CDPoint &p1, const CDPoint &p2)
{
	double cx = p1.x - p2.x;
	double cy = p1.y - p2.y;
	cx *= cx;
	cy *= cy;

	return sqrt(cx + cy);
}


