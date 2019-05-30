// BasicUnit.cpp: implementation of the CTimeUnit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BasicUnit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long MonthsInYear(long year)
{
	CYearTypesAndCycles info(year);
	return (info.IsLeapYear())? 13 : 12;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTimeUnit::CTimeUnit()
{
	Days = Hours = Halakim = Regaim = RegaimPercent = 0;
}

CTimeUnit::~CTimeUnit()
{

}

CTimeUnit::CTimeUnit(long days, long hours, 
					 long halakim, long regaim, 
					 long regaimPercent)
:Days(days),Hours(hours),Halakim(halakim),
Regaim(regaim),RegaimPercent(regaimPercent)
{

}

//////////////////////////////////////////////////////////////////////
// CTimeAccessor Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTimeAccessor::CTimeAccessor()
{

}

CTimeAccessor::~CTimeAccessor()
{

}

CTimeAccessor::CTimeAccessor(long days, long hours,
							 long halakim, long regaim, long regaimPercent)
:m_timeUnit(days, hours, halakim, regaim, regaimPercent)
{

}

CTimeUnit& CTimeAccessor::TimeUnit()
{
	return m_timeUnit;
}

const CTimeUnit& CTimeAccessor::TimeUnit() const
{
	return m_timeUnit;
}

const CTimeAccessor CTimeAccessor::operator *(long period) const
{
	CTimeAccessor a;
	CTimeUnit u = m_timeUnit;
	u.Days *= period;
	u.Hours *= period;
	u.Halakim *= period;
	u.Regaim *= period;
	u.RegaimPercent *= period;

	a.TimeUnit() = u;

	return a;
}

const CTimeAccessor CTimeAccessor::operator +(const CTimeAccessor & ob) const
{
	CTimeAccessor a;
	CTimeUnit au = m_timeUnit;
	CTimeUnit obu = ob.TimeUnit();
	au.Days += obu.Days;
	au.Hours += obu.Hours;
	au.Halakim += obu.Halakim;
	au.Regaim += obu.Regaim;
	au.RegaimPercent += obu.RegaimPercent;

	a.TimeUnit() = au;

	return a;
}

CTimeAccessor CTimeAccessor::operator *(long period)
{
	CTimeAccessor a;
	CTimeUnit u = m_timeUnit;
	u.Days *= period;
	u.Hours *= period;
	u.Halakim *= period;
	u.Regaim *= period;
	u.RegaimPercent *= period;

	a.TimeUnit() = u;

	return a;
}

CTimeAccessor CTimeAccessor::operator +(const CTimeAccessor & ob)
{
	CTimeAccessor a;
	CTimeUnit au = m_timeUnit;
	CTimeUnit obu = ob.TimeUnit();
	au.Days += obu.Days;
	au.Hours += obu.Hours;
	au.Halakim += obu.Halakim;
	au.Regaim += obu.Regaim;
	au.RegaimPercent += obu.RegaimPercent;

	a.TimeUnit() = au;

	return a;
}

CTimeAccessor CTimeAccessor::operator +=(const CTimeAccessor & ob)
{
	CTimeAccessor a;
	CTimeUnit& au = m_timeUnit;
	CTimeUnit obu = ob.TimeUnit();
	au.Days += obu.Days;
	au.Hours += obu.Hours;
	au.Halakim += obu.Halakim;
	au.Regaim += obu.Regaim;
	au.RegaimPercent += obu.RegaimPercent;

	a.TimeUnit() = au;

	return a;
}

void CTimeAccessor::Organizer(bool bRemain)
{
	// for negative value
	__int64 RegaimPercent = m_timeUnit.RegaimPercent;
	__int64 Regaim = m_timeUnit.Regaim;
	__int64 Halakim = m_timeUnit.Halakim;
	__int64 Hours = m_timeUnit.Hours;
	__int64 Days = m_timeUnit.Days;
	RegaimPercent += Regaim * 100;
	Regaim = 0;
	RegaimPercent += Halakim * 100 * 76;
	Halakim = 0;
	RegaimPercent += Hours * 100 * 76 * 1080;
	Hours = 0;
	RegaimPercent += Days * 100 * 76 * 1080 * 24;
	Days = 0;

	Regaim += RegaimPercent / 100;
	RegaimPercent %= 100;
	Halakim += Regaim / 76;
	Regaim %= 76;
	Hours += Halakim / 1080;
	Halakim %= 1080;
	Days += Hours / 24;
	Hours %= 24;
	if(bRemain)
		Days %= 7;

	m_timeUnit.RegaimPercent = (long)RegaimPercent;
	m_timeUnit.Regaim = (long)Regaim;
	m_timeUnit.Halakim = (long)Halakim;
	m_timeUnit.Hours = (long)Hours;
	m_timeUnit.Days = (long)Days;

	//m_timeUnit.Regaim += m_timeUnit.RegaimPercent / 100;
	//m_timeUnit.RegaimPercent %= 100;
	//m_timeUnit.Halakim += m_timeUnit.Regaim / 76;
	//m_timeUnit.Regaim %= 76;
	//m_timeUnit.Hours += m_timeUnit.Halakim / 1080;
	//m_timeUnit.Halakim %= 1080;
	//m_timeUnit.Days += m_timeUnit.Hours / 24;
	//m_timeUnit.Hours %= 24;
	//if(bRemain)
	//	m_timeUnit.Days %= 7;
}

void CTimeAccessor::SetUnit(long days, long hours, long halakim, long regaim, long regaimPercent)
{
	m_timeUnit.Days = days;
	m_timeUnit.Hours = hours;
	m_timeUnit.Halakim = halakim;
	m_timeUnit.Regaim = regaim;
	m_timeUnit.RegaimPercent = regaimPercent;
}

void CTimeAccessor::SetUnit(double tu)
{
	m_timeUnit.Days = (long)(float)tu;
	tu -= (long)(float)tu;
	tu *= 24.0;
	m_timeUnit.Hours = (long)(float)tu;
	tu -= (long)(float)tu;
	tu *= 1080.0;
	m_timeUnit.Halakim = (long)(float)tu;
	tu -= (long)(float)tu;
	tu *= 76.0;
	m_timeUnit.Regaim = (long)(float)tu;
	tu -= (long)(float)tu;
	tu *= 100.0;
	m_timeUnit.RegaimPercent = (long)(float)tu;
}

double CTimeAccessor::GetDoubleUnit()
{
	double dDoubleSpeed = 0.0;
	dDoubleSpeed =  (double)m_timeUnit.Days;
	dDoubleSpeed += (double)m_timeUnit.Hours / 24.0;
	dDoubleSpeed += (double)m_timeUnit.Halakim / (24.0 * 1080.0);
	dDoubleSpeed += (double)m_timeUnit.Regaim / 
		(24.0 * 1080.0 * 76.0);
	dDoubleSpeed += (double)m_timeUnit.RegaimPercent / 
		(24.0 * 1080.0 * 76.0 * 100.0);

	return dDoubleSpeed;
}

//////////////////////////////////////////////////////////////////////
// BaseRemain Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
// BaseSum Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// CYearTypesAndCycles Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CYearTypesAndCycles::CYearTypesAndCycles()
{
	SetYear(1);
}

CYearTypesAndCycles::~CYearTypesAndCycles()
{

}

void CYearTypesAndCycles::SetLeapMode()
{
  switch(m_years%19){
    case 1:
    case 2:
    case 4:
    case 5:
    case 7:
    case 9:
    case 10:
    case 12:
    case 13:
    case 15:
    case 16:
    case 18: m_isleapYear = false;
	break;
    case 3:
    case 6:
    case 8:
    case 11:
    case 14:
    case 17:
    case 0:  m_isleapYear = true;
	break;
    }

}

void CYearTypesAndCycles::CurrentCycleYearsMode()
{
	long Y = m_years;

   Y--;
   m_cycles = Y / 19;
   switch(Y % 19){
     case 18: m_normalYears++;
     case 17: m_leapYears++;
     case 16: m_normalYears++;
     case 15: m_normalYears++;
     case 14: m_leapYears++;
     case 13: m_normalYears++;
     case 12: m_normalYears++;
     case 11: m_leapYears++;
     case 10: m_normalYears++;
     case 9:  m_normalYears++;
     case 8:  m_leapYears++;
     case 7:  m_normalYears++;
     case 6:  m_leapYears++;
     case 5:  m_normalYears++;
     case 4:  m_normalYears++;
     case 3:  m_leapYears++;
     case 2:  m_normalYears++;
     case 1:  m_normalYears++;
     case 0:
	break;
	}

}

void CYearTypesAndCycles::Set()
{
	m_normalYears = m_leapYears = m_cycles = 0;
}

void CYearTypesAndCycles::SetYear(long Y)
{
	Set();
	m_years = Y;
	CurrentCycleYearsMode();
	SetLeapMode();
}

CYearTypesAndCycles::CYearTypesAndCycles(long Y)
{
	SetYear(Y);
}

//////////////////////////////////////////////////////////////////////
// CMollad Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMollad::CMollad(long Y, long M)
{
	SetDate(Y, M);
}

CMollad::~CMollad()
{

}

void CMollad::Calculator()
{
	m_timeAccessor = MonthRemaind * (m_month - 1);
	m_timeAccessor.Organizer();
	m_timeAccessor += NormalYearRemaind * m_normalYears;
	m_timeAccessor.Organizer();
	m_timeAccessor += LeapYearRemaind * m_leapYears;
	m_timeAccessor.Organizer();
	m_timeAccessor += CycleRemaind * m_cycles;
	m_timeAccessor.Organizer();
	m_timeAccessor += MolladTohho;
	m_timeAccessor.Organizer();
}

void CMollad::SetDate(long Y, long M)
{
	SetYear(Y);
	m_month = M;
	Calculator();
	SetDateCorrect();
}

void CMollad::SetDateCorrect()
{
	if(m_isleapYear)
		if(m_month <= 13 && m_month > 0 && m_years > 0)
			m_isDateCorrect = true;
		else
			m_isDateCorrect = false;
	else
		if(m_month <= 12 && m_month > 0 && m_years > 0)
			m_isDateCorrect = true;
		else
			m_isDateCorrect = false;
}

long CMollad::YomRoshHaShana()
{
	if(m_month > 1)
		return -1;

	CTimeUnit tu = m_timeAccessor.TimeUnit();
	long Day = tu.Days;
	CYearTypesAndCycles This(m_years), last(m_years - 1);

	if(tu.Hours >= 18)
		Day++;
	else 
		if((!This.IsLeapYear() && Day == 3) &&
			(tu.Hours == 9 && tu.Halakim >= 204 ||
			tu.Hours > 9))
			Day += 2;
		else
			if((last.IsLeapYear() && Day == 2) &&
				(tu.Hours == 15 && tu.Halakim >= 589
				|| tu.Hours > 15))
				Day++;
	if(Day == 1 || Day == 4 || Day == 6)
		Day++;

	return Day % 7;

}

long CMollad::YearKind()
{
// 0 for hasserra 1 for kessidra  2 for melleha	
	if(m_years == 1)
		return 1;
	CMollad current(m_years), next(m_years + 1);
	long currentYear = current.YomRoshHaShana();
	long nextYear = next.YomRoshHaShana();
	long yearKind;

	if(currentYear >= nextYear)
		nextYear += 7;

	yearKind = nextYear - currentYear;
	if(m_isleapYear)
		yearKind -= 5;
	else 
		yearKind -= 3;

	return yearKind;
}

long CMollad::DaysFromRHShanna()
{
	long daysPast = 0;
	if(m_isDateCorrect) {
		long yearKind = YearKind();
		switch(m_month) {
		case 13: daysPast += 30;
		case 12: if(m_isleapYear)
					daysPast += 29;
				 else
					daysPast += 30;
		case 11: if(m_isleapYear)
					daysPast += 30;
				 else
					daysPast += 29;
		case 10: if(m_isleapYear)
					daysPast += 29;
				 else
					daysPast += 30; 
		case 9: if(m_isleapYear)
					daysPast += 30;
				else
					daysPast += 29;
		case 8:  if(m_isleapYear)
					daysPast += 29;
				 else
					daysPast += 30;
		case 7: if(m_isleapYear)
					daysPast += 30;
				else
					daysPast += 29;
		case 6: daysPast += 30;
		case 5: daysPast += 29;
		case 4: if(yearKind == ShanaHasserra)
					daysPast += 29;
				else
					daysPast += 30;
		case 3: if(yearKind == ShanaMelleha)
					daysPast += 30;
				else
					daysPast += 29;
		case 2: daysPast += 30;
		case 1:;

		}
	}
	else
		return -1;

	return daysPast;
}

long CMollad::YomKviha()
{
	if(!m_isDateCorrect)
		return -1;
	CMollad a(m_years);
	long YomRHoddesh = a.YomRoshHaShana() + DaysFromRHShanna();

	return YomRHoddesh % 7;
}

long CMollad::RoshHodeshKind()
{
	if(m_isDateCorrect) {
		long yearKind = YearKind();
		switch(m_month) {
		case 13: return RoshHodesh2Days;
		case 12: if(m_isleapYear)
					return RoshHodesh1Day;
				 else
					return RoshHodesh2Days;
		case 11: if(m_isleapYear)
					return RoshHodesh2Days;
				 else
					return RoshHodesh1Day;
		case 10: if(m_isleapYear)
					return RoshHodesh1Day;
				 else
					return RoshHodesh2Days; 
		case 9: if(m_isleapYear)
					return RoshHodesh2Days;
				else
					return RoshHodesh1Day;
		case 8:  if(m_isleapYear)
					return RoshHodesh1Day;
				 else
					return RoshHodesh2Days;
		case 7: if(m_isleapYear)
					return RoshHodesh2Days;
				else
					return RoshHodesh1Day;
		case 6: return RoshHodesh2Days;
		case 5: return RoshHodesh1Day;
		case 4: if(yearKind == ShanaHasserra)
					return RoshHodesh1Day;
				else
					return RoshHodesh2Days;
		case 3: if(yearKind == ShanaMelleha)
					return RoshHodesh2Days;
				else
					return RoshHodesh1Day;
		case 2: return RoshHodesh2Days;
		case 1: return RoshHaShana;

		}
	}

	return RoshHodeshErr;

}

long CMollad::DaysInMonth()
{
	if(m_isDateCorrect)
		if((m_isleapYear && m_month == 13) ||
			(!m_isleapYear && m_month == 12)) 
		{
			return 29;
		}
		else 
		{
			CMollad info(m_years, m_month + 1);
			if(info.RoshHodeshKind() == RoshHodesh1Day ) 
			{
				return 29;
			}
			else 
			{
				return 30;
			}
		}

		return -1;
}

long CMollad::DaysInYear()
{
	if(m_isleapYear)
		return (YearKind() + 383);

	return (YearKind() + 353);
}

long CMollad::Month()
{
	return m_month;
}

bool CMollad::IsDateCorrect()
{
	return m_isDateCorrect;
}

CTimeUnit CMollad::TimeUnit()
{
	return m_timeAccessor.TimeUnit();
}

//////////////////////////////////////////////////////////////////////
// CDaysPast Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDaysPast::CDaysPast()
{
	SetDate();
}

CDaysPast::CDaysPast(long Y, long M, long D)
{
	SetDate(Y, M, D);
}

CDaysPast::CDaysPast(const CYMDs & ymd)
{
	*this = ymd;
}

CDaysPast::~CDaysPast()
{

}

void CDaysPast::SetDate(long Y, long M, long D)
{
	SetYear( Y ); //YearTypeAndCycles member
	m_month = M;
	m_Mdays = D;
	Calculator();

}

void CDaysPast::Calculator()
{
		CMollad info(m_years, m_month);
		CTimeAccessor total;
		long molladKvihaDif = info.YomKviha() - info.TimeUnit().Days;
		if(molladKvihaDif < 0 )
			molladKvihaDif += 7;

		total = CycleSum * m_cycles;
		total.Organizer(false);
		total += MonthSum * (m_leapYears * 13);
		total.Organizer(false);
		total += MonthSum * (m_normalYears * 12);
		total.Organizer(false);
		total += MonthSum * (m_month - 1);
		total.Organizer(false);
		total += MolladTohho;
		total.Organizer(false);

		m_daysPast = total.TimeUnit().Days + molladKvihaDif
			+ (m_Mdays - 1);
}

CDaysPast::operator CYMDs()
{
	CYMDs a = {m_years, m_month, m_Mdays};
	return a;
}

CDaysPast::operator CYMDs() const
{
	CYMDs a = {m_years, m_month, m_Mdays};
	return a;
}

bool CDaysPast::IsMonthCorrect()
{
	CMollad info(m_years, m_month);
	return info.IsDateCorrect();
}

bool CDaysPast::IsDayInMonthCorrect()
{
	CMollad info(m_years, m_month);
	if(!info.IsDateCorrect())
		return false;

	if(info.DaysInMonth() >= m_Mdays)
		return true;

	return false;
}

CYMDs CDaysPast::operator =(const CYMDs & units)
{
	SetDate(units.Years, units.Months, units.MDays);
	return (CYMDs)*this;
}

CYMDs CDaysPast::operator =(const CDaysPast & ob)
{
	*this = (CYMDs)ob;
	return (CYMDs)*this;
}

CYMDs CDaysPast::operator +(long days)
{
	CYMDs units = (CYMDs)*this;
	if(days == 0)
		return units;
	else if(days < 0)
	{
		days = -days;
		return *this - days;
	}
	long years = 100;

	CDaysPast past(units.Years + years);

	while((long)past - m_daysPast <= days)
	{
		units.Years += years;
		past.SetDate(units.Years + years);
	}

	years = 10;
	past.SetDate(units.Years + years);

	while((long)past - m_daysPast <= days)
	{
		units.Years += years;
		past.SetDate(units.Years + years);
	}

	years = 1;
	past.SetDate(units.Years + years);

	while((long)past - m_daysPast <= days)
	{
		units.Years += years;
		past.SetDate(units.Years + years);
	}

	if(m_years != units.Years)
		units.Months = 1;
	past.SetDate(units.Years,units.Months + 1);

	while((long)past - m_daysPast <= days && 
		past.IsMonthCorrect())
	{
		units.Months += 1;
		past.SetDate(units.Years, units.Months + 1);
	}

	if(m_years != units.Years || m_month != units.Months)
		units.MDays = 1;
	past.SetDate(units.Years, units.Months, units.MDays + 1);

	while((long)past - m_daysPast <= days)
	{
		units.MDays += 1;
		past.SetDate(units.Years, units.Months, units.MDays + 1);
	}

	return units;	
}

CYMDs CDaysPast::operator -(long days)
{
	CYMDs units = {-1L,-1L,-1L};
	if(days > m_daysPast)
		return units;
	units = (CYMDs)*this;
	if(days == 0)
		return units;
	else if(days < 0)
	{
		days = -days;
		return *this + days;
	}
	long years = 100;
	CDaysPast past;

	if(units.Years > years)
	{
		past.SetDate(units.Years - years, 
			MonthsInYear(units.Years - years), 29);

		while(m_daysPast - (long)past <= days)
		{
			units.Years -= years;
			if(!(units.Years > years))
				break;
			past.SetDate(units.Years - years,
				MonthsInYear(units.Years - years), 29);
		}
	}

	years = 10;
	if(units.Years > years)
	{
		past.SetDate(units.Years - years,
			MonthsInYear(units.Years - years), 29);

		while(m_daysPast - (long)past <= days)
		{
			units.Years -= years;
			if(!(units.Years > years))
				break;
			past.SetDate(units.Years - years,
				MonthsInYear(units.Years - years), 29);
		}
	}

	years = 1;
	if(units.Years > years)
	{
		past.SetDate(units.Years - years,
			MonthsInYear(units.Years - years), 29);

		while(m_daysPast - (long)past <= days)
		{
			units.Years -= years;
			if(!(units.Years > years))
				break;
			past.SetDate(units.Years - years,
				MonthsInYear(units.Years - years), 29);
		}
	}

	if(m_years != units.Years)
	{
		if(m_isleapYear)
			units.Months = 13;
		else
			units.Months = 12;
	}

	if(units.Months > 1)
	{
		long MDays;
		{
			CMollad info(units.Years, units.Months - 1);
			MDays = info.DaysInMonth();
		}
		past.SetDate(units.Years,units.Months - 1, MDays);

		while(m_daysPast - (long)past <= days)
		{
			units.Months -= 1;
			if(!(units.Months > 1))
				break;
			{
				CMollad info(units.Years, units.Months - 1);
				MDays = info.DaysInMonth();
			}
			past.SetDate(units.Years,units.Months - 1, MDays);
		}
	}

	if(m_years != units.Years || m_month != units.Months)
	{
		CMollad info(units.Years, units.Months);
		units.MDays = info.DaysInMonth();
	}

	if(units.MDays > 1)
	{
		past.SetDate(units.Years, units.Months, units.MDays - 1);

		while(m_daysPast - (long)past <= days)
		{
			units.MDays -= 1;
			if(!(units.MDays > 1))
				break;
			past.SetDate(units.Years, units.Months, units.MDays - 1);
		}
	}

	return units;	
}

long CDaysPast::operator -(const CDaysPast & ob)
{
	return ((long)*this) - (long)ob;
}

bool CDaysPast::IsLeapYear()
{
	return m_isleapYear;
}

long CDaysPast::DaysInMonth()
{
	CMollad info(m_years, m_month);
	return info.DaysInMonth();
}

long CDaysPast::WeekDay()
{
	return (m_daysPast + 2) % 7;
}

//////////////////////////////////////////////////////////////////////
// CCircleSpeed Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCircleSpeed::CCircleSpeed():sixth(0),fifth(0),fourth(0),
third(0),second(0),part(0),degree(0),cycles(0)
{

}

CCircleSpeed::~CCircleSpeed()
{

}

CCircleSpeed::CCircleSpeed(long d, long p, long s, long th, long fo, long fi, long si, long c)
{
	SetSpeed(d,  p, s, th, fo, fi, si, c);
}

void CCircleSpeed::SetSpeed(long d, long p, long s, long th, long fo, long fi, long si, long c)
{
	sixth = si;
	fifth = fi;
	fourth = fo;
	third = th;
	second = s;
	part = p;
	degree = d;
	cycles = c;
	Corgenizer();
}

void CCircleSpeed::Corgenizer()
{
	CCircleSpeed check;
	if(sixth < 0 && *this > check) {
		sixth += 60;
		fifth--;
	}
	else {
		fifth += sixth / 60;
		sixth %= 60;
	}	
	if(fifth < 0 && *this > check) {
		fifth += 60;
		fourth--;
	}
	else {
		fourth += fifth / 60;
		fifth %= 60;
	}
	if(fourth < 0 && *this > check) {
		fourth += 60;
		third--;
	}
	else {
		third += fourth / 60;
		fourth %= 60;
	}
	if(third < 0 && *this > check) {
		third += 60;
		second--;
	}
	else {
		second += third / 60;
		third %= 60;
	}
	if(second < 0 && *this > check) {
		second += 60;
		part--;
	}
	else {
		part += second / 60;
		second %= 60;
	}
	if(part < 0 && *this > check) {
		part += 60;
		degree--;
	}
	else {
		degree += part / 60;
		part %= 60;
	}
	if(degree < 0 && cycles ) {
		degree += 360;
		cycles--;
	}
	else {
		cycles += degree / 360;
		degree %= 360;
	}
}

bool CCircleSpeed::operator >(const CCircleSpeed & ob)
{
	if(cycles > ob.cycles)
		return true;
	else if(cycles == ob.cycles )
		if(degree > ob.degree) 
			return true;
		else if(degree == ob.degree)
			if(part > ob.part)
				return true;
			else if(part == ob.part)
				if(second > ob.second)
					return true;
				else if(second == ob.second)
					if(third > ob.third)
						return true;
					else if(third == ob.third)
						if(fourth > ob.fourth)
							return true;
						else if(fourth == ob.fourth)
							if(fifth > ob.fifth)
								return true;
							else if(fifth == ob.fifth)
								if(sixth > ob.sixth)
									return true;
	return false;
}

bool CCircleSpeed::operator ==(const CCircleSpeed & ob)
{
	return (cycles == ob.cycles && degree == ob.degree && part == ob.part && 
		second == ob.second && third == ob.third && fourth == ob.fourth
		&& fifth == ob.fifth && sixth == ob.sixth);
}

bool CCircleSpeed::operator >=(const CCircleSpeed & ob)
{
	return (*this > ob || *this == ob);
}

void CCircleSpeed::SetSpeed(double Degree)
{
	cycles =  (long)(float)Degree / 360;
	degree =  (long)(float)Degree % 360;
	Degree -= (long)(float)Degree;
	Degree *= 60.0;
	part   =  (long)(float)Degree;
	Degree -= (long)(float)Degree;
	Degree *= 60.0;
	second =  (long)(float)Degree;
	Degree -= (long)(float)Degree;
	Degree *= 60.0;
	third  =  (long)(float)Degree;
	Degree -= (long)(float)Degree;
	Degree *= 60.0;
	fourth =  (long)(float)Degree;
	Degree -= (long)(float)Degree;
	Degree *= 60.0;
	fifth  =  (long)(float)Degree;
	Degree -= (long)(float)Degree;
	Degree *= 60.0;
	sixth  =  (long)(float)Degree;
	Corgenizer();

}

CCircleSpeed CCircleSpeed::operator -(const CCircleSpeed & ob)
{
	CCircleSpeed temp = *this;
	CCircleSpeed obt = ob;
	while(obt > temp)
		temp.cycles++;		

	temp.cycles -=	obt.cycles;
	temp.degree -=	obt.degree;
	temp.part -=	obt.part;
	temp.second -=	obt.second;
	temp.third -=	obt.third;
	temp.fourth -=	obt.fourth;
	temp.fifth -=	obt.fifth;
	temp.sixth -=	obt.sixth;
	temp.Corgenizer();

	return temp;
}

CCircleSpeed CCircleSpeed::operator +(const CCircleSpeed & ob)
{
	CCircleSpeed temp;
	temp.cycles = cycles + ob.cycles;
	temp.degree = degree + ob.degree;
	temp.part = part + ob.part;
	temp.second = second + ob.second;
	temp.third = third + ob.third;
	temp.fourth = fourth + ob.fourth;
	temp.fifth = fifth + ob.fifth;
	temp.sixth = sixth + ob.sixth;
	temp.Corgenizer();

	return temp;
}

double CCircleSpeed::GetSpeed()
{
	const double t = 60.0;
	double dDoubleSpeed = 0.0;
	dDoubleSpeed =  (double)cycles * 360.0;
	dDoubleSpeed += (double)degree;
	dDoubleSpeed += (double)part	 /	t;
	dDoubleSpeed += (double)second	 /	(t*t);
	dDoubleSpeed += (double)third	 /	(t*t*t);
	dDoubleSpeed += (double)fourth	 /	(t*t*t*t);
	dDoubleSpeed += (double)fifth	 /	(t*t*t*t*t);
	dDoubleSpeed += (double)sixth	 /	(t*t*t*t*t*t);

	return dDoubleSpeed;
}

double CCircleSpeed::GetAccurateDouble()
{
	const double t = 60.0;
	double dDoubleSpeed = 0.0;
	dDoubleSpeed = (double)degree;
	dDoubleSpeed += (double)part	 /	t;
	dDoubleSpeed += (double)second	 /	(t*t);
	dDoubleSpeed += (double)third	 /	(t*t*t);
	dDoubleSpeed += (double)fourth	 /	(t*t*t*t);
	dDoubleSpeed += (double)fifth	 /	(t*t*t*t*t);
	dDoubleSpeed += (double)sixth	 /	(t*t*t*t*t*t);

	return dDoubleSpeed;

}

CCircleSpeed CCircleSpeed::operator *(const long n)
{
	CCircleSpeed temp;
	temp.cycles = cycles * n;
	temp.degree = degree * n;
	temp.part = part * n;
	temp.second = second * n;
	temp.third = third * n;
	temp.fourth = fourth * n;
	temp.fifth = fifth * n;
	temp.sixth = sixth * n;
	temp.Corgenizer();

	return temp;
}

CCircleSpeed CCircleSpeed::operator *(const double n)
{
	CCircleSpeed temp;
	double s = GetAccurateDouble();
	s *= n;
	temp.SetSpeed(s);

	return temp;
}

CTimeAccessor CCircleSpeed::operator /(const CCircleSpeed & ob)
{
	CCircleSpeed temp,Ttemp;
	Ttemp = *this;
	CTimeUnit T;
	temp = ob;
	T.Days = Ttemp.Divider(temp);
	Ttemp = (Ttemp - (temp * (long)T.Days));
	Ttemp = (Ttemp * 24L);
	T.Hours = Ttemp.Divider(temp);
	Ttemp = (Ttemp - (temp * (long)T.Hours));
	Ttemp = (Ttemp * 1080L);
	T.Halakim = Ttemp.Divider(temp);
	Ttemp = (Ttemp - (temp * (long)T.Halakim));
	Ttemp = (Ttemp * 76L);
	T.Regaim = Ttemp.Divider(temp);
	Ttemp = (Ttemp - (temp * (long)T.Regaim));
	Ttemp = (Ttemp * 100L);
	T.RegaimPercent = Ttemp.Divider(temp);

	CTimeAccessor A;
	A.TimeUnit() = T;
	A.Organizer(false);

	return A;
}

// Convert CTimeUnit to CCircleSpeed compatible
CCircleSpeed CCircleSpeed::TuToCs(const CTimeUnit & tu)
{
	CCircleSpeed cs;
	cs.cycles = tu.Days / 360;
	cs.degree = tu.Days % 360;
	// 24 Hours/part
	cs.part = (tu.Hours * 5) / 2;
	cs.second = ((tu.Hours * 5) % 2) * 30;
	// 5/2 Halakim/part
	cs.part += tu.Halakim / 432;
	long temp = ((tu.Halakim % 432) * 5);
	cs.second += temp / 36;
	temp = ((temp % 36) * 5);
	cs.third = temp / 3;
	cs.fourth = (temp % 3) * 20;
	// 25/3 Regaim/third
	temp = (tu.Regaim * 25);
	cs.third += temp / 228;
	cs.fourth += (temp * 3) / 95;
	temp = (temp * 3) % 95;
	cs.fifth = (temp * 12) / 19;
	cs.sixth = (((temp * 12) % 19) * 60) / 19;
	// 125/19 RegaimPercent/fourth
	temp = tu.RegaimPercent * 125;
	cs.fourth += temp / 1900;
	temp = (temp % 1900) * 3;
	cs.fifth += temp / 95;
	cs.sixth += ((temp % 95) * 12) / 19;
	cs.Corgenizer();

	return cs;
}

long CCircleSpeed::Divider(CCircleSpeed & ob)
{
	if(ob > *this) return 0;
	if(ob == *this) return 1;
	
	long sum;
	CCircleSpeed temp;
	temp = (ob * 60L);
	for(sum = 60; *this > temp; sum *= 60, temp = (temp * 60L));
	if(temp == *this) 
		return sum;
	for(; temp > *this; temp = (temp - ob), sum--);

	return sum;

}

CCircleSpeed CCircleSpeed::operator /(const CTimeUnit & tu)
{
	CCircleSpeed conOfTu = TuToCs(tu);
	CCircleSpeed Ttemp = *this, res;

	res.degree = Ttemp.Divider(conOfTu);
	Ttemp = (Ttemp - (conOfTu * res.degree));
	Ttemp = (Ttemp * 60L);
	res.part = Ttemp.Divider(conOfTu);
	Ttemp = (Ttemp - (conOfTu * res.part));
	Ttemp = (Ttemp * 60L);
	res.second = Ttemp.Divider(conOfTu);
	Ttemp = (Ttemp - (conOfTu * res.second));
	Ttemp = (Ttemp * 60L);
	res.third = Ttemp.Divider(conOfTu);
	Ttemp = (Ttemp - (conOfTu * res.third));
	Ttemp = (Ttemp * 60L);
	res.fourth = Ttemp.Divider(conOfTu);
	Ttemp = (Ttemp - (conOfTu * res.fourth));
	Ttemp = (Ttemp * 60L);
	res.fifth = Ttemp.Divider(conOfTu);
	Ttemp = (Ttemp - (conOfTu * res.fifth));
	Ttemp = (Ttemp * 60L);
	res.sixth = Ttemp.Divider(conOfTu);
	res.Corgenizer();

	return res;
}

CCircleSpeed CCircleSpeed::operator *(const CTimeAccessor & ta)
{
	CTimeUnit tu = ta.TimeUnit();
	double ThisSpeed = GetSpeed();
	double plusSpeed = 0.0;

	plusSpeed = ThisSpeed * ((double)tu.Hours / 24.0);
	plusSpeed += ThisSpeed * ((double)tu.Halakim / 25920.0);
	plusSpeed += ThisSpeed * ((double)tu.Regaim / 1969920.0);
	plusSpeed += ThisSpeed * ((double)tu.RegaimPercent / 196992000.0);
	CCircleSpeed temp = (*this) * (long)tu.Days, temp2;
	temp2.SetSpeed(plusSpeed);
	temp = temp + temp2;
	return temp;
}

////////////////////////////////////////////////////////
// CTypes Struct members  //////////////////////////////
////////////////////////////////////////////////////////

void CTypes::Clear()
{
	switch(ty)
	{
	case CLASS_TA: delete u.ta;
		break;
	case CLASS_DP: delete u.dp;
		break;
	case CLASS_CS: delete u.cs;
		break;
	}

	ty = CLASS_NOTYPE;
	op = OP_NOP;
}

CTypes::~CTypes()
{
	Clear();
}

long& CTypes::operator =(const long & val)
{
	Clear();
	ty = CLASS_LONG;
	u.l = val;
	return u.l;
}

double& CTypes::operator =(const double & val)
{
	Clear();
	ty = CLASS_DOUB;
	u.d = val;
	return u.d;
}

CTimeAccessor& CTypes::operator =(const CTimeAccessor & val)
{
	Clear();
	ty = CLASS_TA;
	u.ta = new CTimeAccessor;
	*(u.ta) = val;
	u.ta->Organizer(false);
	return *(u.ta);
}

CDaysPast& CTypes::operator =(const CDaysPast & val)
{
	Clear();
	ty = CLASS_DP;
	u.dp = new CDaysPast;
	*(u.dp) = val;
	return *(u.dp);
}

CCircleSpeed& CTypes::operator =(const CCircleSpeed & val)
{
	Clear();
	ty = CLASS_CS;
	u.cs = new CCircleSpeed;
	*(u.cs) = val;
	return *(u.cs);
}

CTypes& CTypes::operator =(const CTypes & val)
{
	op = val.op;
	switch(val.ty)
	{
	case CLASS_NOTYPE: 
		Clear();
		ty = val.ty;
		break; 
	case CLASS_TA: 
		*this = *(val.u.ta);
		break;
	case CLASS_DP:
		*this = *(val.u.dp);
		break;
	case CLASS_CS:
		*this = *(val.u.cs);
		break;
	case CLASS_LONG:
		*this = val.u.l;
		break;
	case CLASS_DOUB:
		*this = val.u.d;
		break;
	}
	
	return *this;
}

CTypes::CTypes(const CTypes & val)
{
	*this = val;
}

DWORD CTypes::Operations(DWORD className)
{
	switch(className)
	{
	case CLASS_NOTYPE:
		return OP_NOP;
	case CLASS_TA:
		return OP_P | OP_MUL;
	case CLASS_DP:
		return OP_P | OP_MIN;
	case CLASS_CS:
		return OP_P | OP_MIN | OP_MUL | OP_D;
	case CLASS_LONG:
		return OP_NOP;
	case CLASS_DOUB:
		return OP_NOP;
	}

	return OP_NOP;
}

DWORD CTypes::WithClass()
{
	switch(ty | op)
	{
	case CLASS_TA | OP_MUL:
		return CLASS_LONG;
	case CLASS_TA | OP_P:
		return CLASS_TA;
	case CLASS_DP | OP_P:
		return CLASS_LONG;
	case CLASS_DP | OP_MIN:
		return CLASS_DP | CLASS_LONG;
	case CLASS_CS | OP_MUL:
		return CLASS_LONG | CLASS_DOUB | CLASS_TA;
	case CLASS_CS | OP_P:
		return CLASS_CS;
	case CLASS_CS | OP_MIN:
		return CLASS_CS;
	case CLASS_CS | OP_D:
		return CLASS_CS | CLASS_TA;
	}

	return CLASS_NOTYPE;
}

CTypes CTypes::DoOp(const CTypes & val)
{
	CTypes temp;
	switch(ty | op)
	{
	case CLASS_TA | OP_MUL:
		temp = *(this->u.ta) * val.u.l;
		return temp;
	case CLASS_TA | OP_P:
		temp = *(this->u.ta) + *(val.u.ta);
		return temp;
	case CLASS_DP | OP_P:
		temp = *(this->u.dp) + val.u.l;
		return temp;
	case CLASS_DP | OP_MIN:
		switch(val.ty)
		{
		case CLASS_DP:
			temp = *(this->u.dp) - *(val.u.dp);
			break;
		case CLASS_LONG:
			temp = *(this->u.dp) - val.u.l;
			break;
		}
		return temp;
	case CLASS_CS | OP_MUL:
		switch(val.ty)
		{
		case CLASS_LONG:
			temp = *(this->u.cs) * val.u.l;
			break;
		case CLASS_DOUB:
			temp = *(this->u.cs) * val.u.d;
			break;
		case CLASS_TA:
			temp = *(this->u.cs) * *(val.u.ta);
			break;
		}
		return temp;
	case CLASS_CS | OP_P:
		temp = *(this->u.cs) + *(val.u.cs);
		return temp;
	case CLASS_CS | OP_MIN:
		temp = *(this->u.cs) - *(val.u.cs);
		return temp;
	case CLASS_CS | OP_D:
		switch(val.ty)
		{
		case CLASS_CS:
			temp = *(this->u.cs) / *(val.u.cs);
			break;
		case CLASS_TA:
			temp = *(this->u.cs) / *(val.u.ta);
			break;
		}
		return temp;
	}

	return temp;
}
