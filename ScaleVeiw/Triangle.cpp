// Triangle.cpp: implementation of the CTriangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ScaleVeiw.h"
#include "Triangle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTriangle::CTriangle(const CDPoint &P1, const CDPoint &P2, const CDPoint &P3):m_area(0.0)
{
	double ang1 = GetAng(P2, P1);
	double ang2 = GetAng(P3, P1);
	double ang3 = ang2 - ang1;
	double len1 = GetLength(P2, P1);
	double len2 = GetLength(P3, P1);
	CDPoint ph = GetDPoint(ang3, len2, P1);
	double height = ph.y - P1.y;
	if(height < 0.0)
		height = -height;
	(double)m_area = height * len1 / 2.0;
}

CTriangle::~CTriangle()
{

}
