// DPoint.h: interface for the CDPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DPOINT_H__9F27FD5A_4943_4F52_B70A_82C3F2A75A58__INCLUDED_)
#define AFX_DPOINT_H__9F27FD5A_4943_4F52_B70A_82C3F2A75A58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CDPoint  
{
public:
	double y;
	double x;
	CDPoint(double X = 0.0, double Y = 0.0);
	virtual ~CDPoint();

};

#endif // !defined(AFX_DPOINT_H__9F27FD5A_4943_4F52_B70A_82C3F2A75A58__INCLUDED_)
