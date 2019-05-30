// Triangle.h: interface for the CTriangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIANGLE_H__BC25EF52_4488_419D_99B9_8289A627DC63__INCLUDED_)
#define AFX_TRIANGLE_H__BC25EF52_4488_419D_99B9_8289A627DC63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BasicShape.h"

class CTriangle : public CBasicShape  
{
public:
	const double m_area;
	CTriangle(const CDPoint &P1, const CDPoint &P2, const CDPoint &P3);
	virtual ~CTriangle();

};

#endif // !defined(AFX_TRIANGLE_H__BC25EF52_4488_419D_99B9_8289A627DC63__INCLUDED_)
