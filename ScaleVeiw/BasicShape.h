// BasicShape.h: interface for the CBasicShape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASICSHAPE_H__84BB522D_A674_4637_8E81_27C343A4346A__INCLUDED_)
#define AFX_BASICSHAPE_H__84BB522D_A674_4637_8E81_27C343A4346A__INCLUDED_

#include "DPoint.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBasicShape  
{
public:
	static double GetLength(const CDPoint &p1, const CDPoint &p2 = CDPoint());
	static double GetAng(const CDPoint &p, const CDPoint &pm = CDPoint());
	static CDPoint GetDPoint(double ang, double len = 1.0, const CDPoint &p = CDPoint());
	CBasicShape();
	virtual ~CBasicShape();

};

#endif // !defined(AFX_BASICSHAPE_H__84BB522D_A674_4637_8E81_27C343A4346A__INCLUDED_)
