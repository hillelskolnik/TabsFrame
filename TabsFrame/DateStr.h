#pragma once
#include "..\TimeSpeed\basicunit.h"

class CDateStr
{
public:
	CDateStr(const CTimeUnit& ob);
	~CDateStr(void);
	CString GetYearStr(void);
	CString GetMonthStr(void);
	CString GetMDayStr(void);
	CString GetHourMinuts(void);
	CString ShahaStr(void);
	CString GetDateAndMinuts(void);
	CString GetWeekDay(void);
protected:
	int m_years;
	int m_month;
	int m_wday;
	CTimeUnit m_MDays;
public:
	void operator=(const CTimeUnit& ob);
};
