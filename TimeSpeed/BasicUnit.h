// BasicUnit.h: interface for the CTimeUnit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASICUNIT_H__A7B640E0_5DE9_11D5_8425_00784EC10000__INCLUDED_)
#define AFX_BASICUNIT_H__A7B640E0_5DE9_11D5_8425_00784EC10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef INPORTEXPORT_BU
#ifdef _USRDLL
#define INPORTEXPORT_BU __declspec(dllexport)
#else
#define INPORTEXPORT_BU __declspec(dllimport)
#endif
#endif

enum{
	YomErr =		-1,
	YomShabat =		0,
	YomRishon =		1,
	YomSheny =		2,
	YomShlishy =	3,
	YomR3eviei =	4,
	YomHamishy =	5,
	YomShishy =		6
};

enum{
	ShanaHasserra	= 0,
	ShanaKessidra	= 1,
	ShanaMelleha	= 2
};

enum{
	RoshHodeshErr	= -10,
	RoshHodesh2Days	= -1,
	RoshHodesh1Day	= 0,
	RoshHaShana		= 1
};

enum{
	CLASS_NOTYPE = 0x0001,
	CLASS_TA	= 0x0002,
	CLASS_DP	= 0x0004,
	CLASS_CS	= 0x0008,
	CLASS_LONG	= 0x0010,
	CLASS_DOUB	= 0x0020
};

enum{
	OP_NOP	= 0x0100,
	OP_P	= 0x0200,
	OP_MIN	= 0x0400,
	OP_MUL	= 0x0800,
	OP_D	= 0x1000
};

INPORTEXPORT_BU long MonthsInYear(long year);

class INPORTEXPORT_BU CTimeUnit  
{
public:
	long RegaimPercent;
	long Regaim;
	long Halakim;
	long Hours;
	long Days;
	CTimeUnit(long days, long hours = 0, long halakim = 0, long regaim = 0, long regaimPercent = 0);
	CTimeUnit();
	virtual ~CTimeUnit();

};


class INPORTEXPORT_BU CTimeAccessor  
{
public:
	double GetDoubleUnit();
	void SetUnit(double tu);
	void SetUnit(long days, long hours = 0, long halakim = 0, long regaim = 0, long regaimPercent = 0);
	void Organizer(bool bRemain = true);
	CTimeAccessor operator+=(const CTimeAccessor& ob);
	CTimeAccessor operator+(const CTimeAccessor& ob);
	CTimeAccessor operator*(long period);
	const CTimeAccessor operator+(const CTimeAccessor& ob) const;
	const CTimeAccessor operator*(long period) const;
	CTimeUnit& TimeUnit();
	const CTimeUnit& TimeUnit() const;
	operator const CTimeUnit& () const { return m_timeUnit; }
	CTimeAccessor(long days, long hours = 0, long halakim = 0, long regaim = 0, long regaimPercent = 0);
	CTimeAccessor();
	virtual ~CTimeAccessor();

protected:
	CTimeUnit m_timeUnit;
};


class INPORTEXPORT_BU CBaseRemain  
{
public:
	CBaseRemain():
	CycleRemaind(2, 16, 595),
	LeapYearRemaind(5, 21, 589),
	NormalYearRemaind(4, 8, 876),
	MonthRemaind(1, 12, 793),
	MolladTohho(2, 5, 204)
	{}
	virtual ~CBaseRemain(){}
	const CTimeAccessor CycleRemaind;
	const CTimeAccessor LeapYearRemaind;
	const CTimeAccessor NormalYearRemaind;
	const CTimeAccessor MonthRemaind;
	const CTimeAccessor MolladTohho;

};


class INPORTEXPORT_BU CBaseSum  
{
public:
	CBaseSum():
	CycleSum(6939, 16, 595),
	MonthSum(29, 12, 793),
	MolladTohho(0, 5, 204)
	{}
	virtual ~CBaseSum(){}
	const CTimeAccessor MolladTohho;
	const CTimeAccessor CycleSum;
	const CTimeAccessor MonthSum;
};

class INPORTEXPORT_BU CYearTypesAndCycles  
{
public:
	 CYearTypesAndCycles(long Y);
	void SetYear(long Y);
	CYearTypesAndCycles();
	virtual ~CYearTypesAndCycles();
	long NYears(){ return m_normalYears;}
	long LYears(){ return m_leapYears;}
	long Cycles(){ return m_cycles;}
	long Years(){ return m_years;}
	bool IsLeapYear(){ return m_isleapYear;}

private:
	void Set();
	void CurrentCycleYearsMode();
	void SetLeapMode();
protected:
	bool m_isleapYear;
	long m_cycles;
	long m_leapYears;
	long m_normalYears;
	long m_years;
};


class INPORTEXPORT_BU CMollad : 
	public CYearTypesAndCycles, 
	protected CBaseRemain  
{
public:
	CTimeUnit TimeUnit();
	bool IsDateCorrect();
	long Month();
	long DaysInYear();
	long DaysInMonth();
	long RoshHodeshKind();
	long YomKviha();
	long DaysFromRHShanna();
	long YearKind();
	long YomRoshHaShana();
	void SetDateCorrect();
	void SetDate(long Y, long M = 1);
	CMollad(long Y = 1, long M = 1);
	virtual ~CMollad();

protected:
	long m_month;
	bool m_isDateCorrect;
	void Calculator();
	CTimeAccessor m_timeAccessor;
};


struct INPORTEXPORT_BU CYMDs
{
	long Years;
	long Months;
	long MDays;
};


class INPORTEXPORT_BU CDaysPast : 
	protected CYearTypesAndCycles, 
	protected CBaseSum  
{
public:
	 CDaysPast(const CYMDs& ymd);
	long operator - (const CDaysPast& ob);
	long WeekDay();
	long DaysInMonth();
	bool IsLeapYear();
	CYMDs operator-(long days);
	CYMDs operator + (long days);
	CYMDs operator=(const CDaysPast& ob);
	CYMDs operator=(const CYMDs& units);
	bool IsDayInMonthCorrect();
	bool IsMonthCorrect();
	operator CYMDs ();
	operator CYMDs () const;
	operator long (){return m_daysPast;}
	operator long () const{return m_daysPast;}
	void SetDate(long Y = 1, long M = 1, long D = 1);
	CDaysPast(long Y, long M = 1, long D = 1);
	CDaysPast();
	virtual ~CDaysPast();

protected:
	long m_daysPast;
	void Calculator();
	long m_Mdays;
	long m_month;
};


class INPORTEXPORT_BU CCircleSpeed  
{
public:
	CCircleSpeed operator * (const CTimeAccessor& ta);
	CCircleSpeed operator/(const CTimeUnit& tu);
	static CCircleSpeed TuToCs(const CTimeUnit& tu);
	long Divider( CCircleSpeed & ob);
	CTimeAccessor operator / (const CCircleSpeed& ob);
	CCircleSpeed operator *(const double n);
	CCircleSpeed operator *(const long n);
	double GetAccurateDouble();
	double GetSpeed();
	CCircleSpeed operator +(const CCircleSpeed & ob);
	CCircleSpeed operator -(const CCircleSpeed & ob);
	void SetSpeed(double s);
	bool operator >=(const CCircleSpeed & ob);
	bool operator ==(const CCircleSpeed & ob);
	bool operator > (const CCircleSpeed & ob);
	void SetSpeed(long d, long p = 0, long s = 0, long th = 0, long fo = 0, long fi = 0, long si = 0, long c = 0);
	 CCircleSpeed(long d, long p = 0, long s = 0, long th = 0, long fo = 0, long fi = 0, long si = 0, long c = 0);
	CCircleSpeed();
	virtual ~CCircleSpeed();

	long sixth;
	long fifth;
	long fourth;
	long third;
	long second;
	long part;
	long degree;
	long cycles;
protected:
	void Corgenizer();
};

struct INPORTEXPORT_BU CTypes{

public:
	CTypes():ty(CLASS_NOTYPE),op(OP_NOP){}
	int ty;
	int op;
	union _u{
		long			l;
		double			d;
		CTimeAccessor*	ta;
		CDaysPast*		dp;
		CCircleSpeed*	cs;
	}u;
protected:

public:
	CTypes DoOp(const CTypes& val);
	DWORD WithClass();
	static DWORD Operations(DWORD className);
	void Clear();
	CTypes(const CTypes& val);
	CTypes& operator = (const CTypes& val);
	CCircleSpeed& operator = (const CCircleSpeed& val);
	CDaysPast& operator = (const CDaysPast& val);
	CTimeAccessor& operator = (const CTimeAccessor& val);
	double& operator = (const double& val);
	long& operator = (const long& val);
	 ~CTypes();
};

#endif // !defined(AFX_BASICUNIT_H__A7B640E0_5DE9_11D5_8425_00784EC10000__INCLUDED_)
