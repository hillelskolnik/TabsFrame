// DPoint.cpp: implementation of the CDPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ScaleVeiw.h"
#include "DPoint.h"
#include ".\dpoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDPoint::CDPoint(double X, double Y):x(X),y(Y)
{

}

CDPoint::~CDPoint()
{

}
