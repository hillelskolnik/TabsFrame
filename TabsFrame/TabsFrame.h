// TabsFrame.h : main header file for the TabsFrame application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTabsFrameApp:
// See TabsFrame.cpp for the implementation of this class
//

#include "RegMsg.h"
#include "chaptersparagraphs.h"

#include<math.h>


class CTabsFrameApp : public CWinApp
{
public:
	CTabsFrameApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	CChaptersParagraphs m_chaptersParagraphs;
public:
	CString m_appPath;
public:
	int CreateToolBm2(int idx, int nWidth, 
		CDC* pDC, CToolBar &toolBar, UINT nIdCommand);
	int CreateToolBm(int idx, int nWidth, CBitmap& newBm, 
		CDC* pDC, CToolBar &toolBar, UINT nIdCommand);
public:
	BOOL InstallNeededFonts(void);
public:
	static int CALLBACK EnumFontFamExProc(ENUMLOGFONTEX* lpelfe, NEWTEXTMETRICEX* lpntme, WORD fontType, LPARAM lParam);
};

extern CTabsFrameApp theApp;


const double D = asin((double)1) / 90.0;
const double ToD = 90.0 / asin((double)1);
const double pi = asin((double)1) * 2.0;

class C2DPoint  
{
public:
	double y;
	double x;
	C2DPoint():x(0.0),y(0.0){}
	C2DPoint(const double &ang ):x(cos(ang * D)),y(sin(ang * D)){}
	C2DPoint& operator = (const double &ang)
	{
		x = (cos(ang * D));
		y = (sin(ang * D));
		return *this;
	}
	C2DPoint& operator = (const C2DPoint &ob)
	{
		x = ob.x;
		y = ob.y;
		return *this;
	}
	CPoint GetScreenPt(CPoint& ptNull)
	{
		return CPoint((int)(float)x+ptNull.x, -((int)(float)y)+ptNull.y);
	}
	C2DPoint& operator *= (const double &vec)
	{
		x *= vec;
		y *= vec;
		return *this;
	}
	C2DPoint operator * (const double &vec)
	{
		C2DPoint p = *this;
		return (p *= vec);
	}
	virtual ~C2DPoint(){};
};
inline void Turn(double& x, double& y, const C2DPoint& xy);
inline void Turn(C2DPoint& toT, const C2DPoint& xy)
{
	Turn(toT.x,toT.y,xy);
}

inline void Turn(double& x, double& y, const C2DPoint& xy)
{
	double ox = x;
	x = x * xy.x - y * xy.y;
	y = y * xy.x + ox * xy.y;
}
inline void RectPaint(CRect& rc, CDC* pDC,
					  COLORREF minColor = RGB(0,0,128),
					  COLORREF maxColor = RGB(130,160,234),
					  double minAng = -60,
					  double maxAng = 60,
					  BOOL bHorizontal = TRUE)
{
	int steps = bHorizontal? rc.Height(): rc.Width();
	double stepAng = (maxAng - minAng) / (double)steps;
	float rmin = (float)GetRValue(minColor);
	float gmin = (float)GetGValue(minColor);
	float bmin = (float)GetBValue(minColor);
	float rnax = (float)GetRValue(maxColor);
	float gnax = (float)GetGValue(maxColor);
	float bnax = (float)GetBValue(maxColor);
	float rdif = (float)(rnax - rmin);
	float gdif = (float)(gnax - gmin);
	float bdif = (float)(bnax - bmin);

	for(int i = 0; i < steps; ++i, maxAng -= stepAng)
	{
		double vec = cos(maxAng * D);
		BYTE r = (BYTE)(rmin + (rdif * vec));
		BYTE g = (BYTE)(gmin + (gdif * vec));
		BYTE b = (BYTE)(bmin + (bdif * vec));
		COLORREF newColor = RGB(r,g,b);
		CBrush br(newColor);
		CBrush *oBr = pDC->SelectObject(&br);

		if(bHorizontal)
			pDC->PatBlt(rc.left,rc.top + i,rc.Width(),1, PATCOPY);
		else
			pDC->PatBlt(rc.left + i,rc.top,1,rc.Height(), PATCOPY);

		pDC->SelectObject(oBr);
	}
}
class CTrackMouseEvent : public tagTRACKMOUSEEVENT
{
public:
	CTrackMouseEvent(CWnd* pWnd, DWORD dwFlags = TME_LEAVE, DWORD dwHoverTime = HOVER_DEFAULT)
	{
		ASSERT_VALID(pWnd);
		ASSERT(::IsWindow(pWnd->m_hWnd));

		this->cbSize = sizeof(TRACKMOUSEEVENT);
		this->dwFlags = dwFlags;
		this->hwndTrack = pWnd->m_hWnd;
		this->dwHoverTime = dwHoverTime;
	}

	BOOL Track()
		{ return _TrackMouseEvent(this); }
};

inline double AliyaYeshara(double ang, double alfa)
{
	ang *= D;
	double x = cos(ang);
	double y = sin(ang) * cos(alfa * D);
	double aliya = atan2(y, x) * ToD;
	if(aliya < 0.0)
		aliya += 360.0;
	return aliya;
}

inline double SinNetyatAliyaYeshara(double ang, double alfa)
{
	return sin(ang * D) * sin(alfa * D);
}

inline double kizuzNetiyaLaOfek(double angNetiya, double sinNetiya)
{
	double t = asin(1.0 / cos(angNetiya * D) * sinNetiya) * ToD;
	return AliyaYeshara(t, 90 - angNetiya);
}

inline double CosSphereAlfaRule(double alfaB, double alfaC, double a)
{
	return acos(-cos(alfaB * D) * cos(alfaC * D) + 
		sin(alfaB * D) * sin(alfaC * D) * cos(a * D)) * ToD;
}

inline double SinSphereRule(double A, double alfaA, double alfaC)
{
	if(alfaA == 0.0)
		return 0.0;

	return asin((sin(A * D) * sin(alfaC * D)) / sin(alfaA * D)) * ToD;

}

inline COLORREF ColDev(COLORREF col, BYTE dev)
{
	BYTE r = GetRValue(col)/dev;
	BYTE g = GetGValue(col)/dev;
	BYTE b = GetBValue(col)/dev;
	return RGB(r,g,b);
}

inline COLORREF ColBright(COLORREF col, double vec)
{
	if(vec > 1.0)
		vec = 1.0;
	else if(vec < -1.0)
		vec = -1.0;

	double r = GetRValue(col);
	double g = GetGValue(col);
	double b = GetBValue(col);
	if(vec > 0.0)
	{
		double dr = 255.0 - r;
		double dg = 255.0 - g;
		double db = 255.0 - b;
		r += dr * vec;
		g += dg * vec;
		b += db * vec;
	}
	else
	{
		r += r * vec;
		g += g * vec;
		b += b * vec;
	}

	return RGB((BYTE)r,(BYTE)g,(BYTE)b);
}

inline double CalcMenatHaMslul(double maslulHaShemesh, double memuza = 28.87708884)
{
	double menatHaMslul = 
		atan(sin(maslulHaShemesh) / ( + memuza +
		cos(maslulHaShemesh)));
	menatHaMslul /= D;

	return menatHaMslul;
}

inline double ShemesAmity(double shmEmzai, double govaSemesh, double memuza = 28.87708884)
{
	//////////////////////////////////////////////////////////////
	////  Calculating menat ha maslul
	//circlespeed emzaSun = (m_speedEmzaSun * past) + m_ikarEmzaSun;
	//circlespeed govaSun = (m_speedGovaSun * past) + m_ikarGovaSun;
	//circlespeed maslulHaShemesh = emzaSun - govaSun;
	//double angMaslulHaShemash = maslulHaShemesh.GetAccurateDouble();
	//double menatHaMslul = CalcMenatHaMslul(angMaslulHaShemash * m_D);

	//circlespeed menatHaShemesh;
	//menatHaShemesh.setspeed(menatHaMslul);

	//if(style == SP_MENATHAMASLUL)
	//	return menatHaShemesh;

	//////////////////////////////////////////////////////////////
	////  Calculating mekkom ha shmesh ha amity
	////circlespeed shemeshAmity = menatHaShemesh + emzaSun;
	//circlespeed shemeshAmity = emzaSun - menatHaShemesh;

	//if(style == SP_SHEMESHAMITY)
	//	return shemeshAmity;

	double maslulHaShemesh = (shmEmzai - govaSemesh);
	double menatHaMslul = CalcMenatHaMslul(maslulHaShemesh * D, memuza);


	return shmEmzai - menatHaMslul;
}

inline double AdjusShemesAmity(double shemeshAmity)
{
	if(shemeshAmity >= 359.99 && shemeshAmity < 360.0)
		shemeshAmity = 0.0;
	else if(shemeshAmity > 360.0)
		shemeshAmity -= 360.0;
	else if(shemeshAmity < -360.0)
		shemeshAmity += 360.0;
	return shemeshAmity;
}

inline double ShemeshAmity2Emzai(double amity, double govaSemesh, double memuza = 28.87708884)
{
	double c1 = (amity - govaSemesh);
	double C = sin((c1/2.0)*D)*2.0;
	double a = (180-c1)/2.0;
	double d = 180.0 - a;
	double c2 = asin(sin(d*D) * C / memuza)*ToD;
	double e = 180.0 - (d+c2 + govaSemesh);
	double emzai = 180.0 - (a+e);

	while(emzai < 0.0)
		emzai += 360.0;
	while(emzai > 360.0)
		emzai -= 360.0;
	return emzai;
}

inline CString MaalotHalakim(double ang)
{
	bool bMinus = ang < -0.000001;
	ang = fabs(ang);
	double tay = floor(ang);
	tay = (ang - tay) * 60;
	ang = floor(ang);

	CString sTxt;

	sTxt.Format("%s%3.0f %-2.0f\'",bMinus?"-":"" ,ang, tay );

	return sTxt;
}