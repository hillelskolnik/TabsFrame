#include "StdAfx.h"
#include "DateStr.h"

CDateStr::CDateStr(const CTimeUnit& ob)
{
	*this = ob;
}

CDateStr::~CDateStr(void)
{
}
CString CDateStr::GetYearStr(void)
{
	if(m_years == 0 || m_years > 6999)
		return "";

	char letter[23] = 
	{224,225,226,227,228,229,
	230,231,232,233,235,236,238,240,241,242,244,
	246,247,248,249,250,0};
	CString str;

	int years = m_years;
	int nElef = years / 1000;
	years %= 1000;
	int nMeha = years / 100;
	years %= 100;
	int nEser = years / 10;
	years %= 10;
	int nEhad = years;

	switch(nElef)
	{
	case 0:
		str += " ";
		break;
	case 1:
		str += letter[0];
		break;
	case 2:
		str += letter[1];
		break;
	case 3:
		str += letter[2];
		break;
	case 4:
		str += letter[3];
		break;
	case 5:
		str += letter[4];
		break;
	case 6:
		str += letter[5];
		break;
	}
	str += " ";

	int hundreds = 18;
	switch(nMeha)
	{
	case 4:
		hundreds++;
	case 3:
		hundreds++;
	case 2:
		hundreds++;
	case 1:
		str += letter[hundreds];
		break;
	case 8:
		hundreds++;
	case 7:
		hundreds++;
	case 6:
		hundreds++;
	case 5:
		str += letter[21];
		str += letter[hundreds];
		break;
	case 9:
		str += letter[21];
		str += letter[21];
		str += letter[hundreds];
		break;
	}

	int eser = 10;
	switch(nEser)
	{
	case 9:
		eser++;
	case 8:
		eser++;
	case 7:
		eser++;
	case 6:
		eser++;
	case 5:
		eser++;
	case 4:
		eser++;
	case 3:
		eser++;
	case 2:
		str += letter[eser];
		break;
	case 1:
		if(nEhad == 5 || nEhad == 6)
		{
			str += letter[eser - 2];
			str += letter[nEhad];
			break;
		}
		eser--;
		str += letter[eser];
		break;
	}

	int ahadim = 0;
	switch(nEhad)
	{
		break;
	case 9:
		ahadim++;
	case 8:
		ahadim++;
	case 7:
		ahadim++;
	case 6:
		ahadim++;
	case 5:
		if(nEser == 1 && ahadim < 2)
			break;
		ahadim++;
	case 4:
		ahadim++;
	case 3:
		ahadim++;
	case 2:
		ahadim++;
	case 1:
		str += letter[ahadim];
		break;
	}

	int size = 8 - str.GetLength();
	for(int i = 0; i < size; i++)
		str += " ";
	str = str.MakeReverse();

	return str;
}

CString CDateStr::GetMonthStr(void)
{
	if(m_years == 0)
		return "";
	int idx = m_month;
	CYearTypesAndCycles ytac(m_years);
	bool bLeap = ytac.IsLeapYear();
	if(idx == 0 || (bLeap == false && idx == 13))
		return "";

	CString str;
	char tishray[5] = {233,248,249,250,0};
	char heshvan[5] = {239,229,249,231,0};
	char kislev[5] = {229,236,241,235,0};
	char tevet[4] = {250,225,232,0};
	char shvat[4] = {232,225,249,0};
	char adar[4] = {248,227,224,0};
	char adar1[6] = {224,32,248,227,224,0};
	char adar2[6] = {225,32,248,227,224,0};
	char nisan[5] = {239,241,233,240,0};
	char iyar[5] = {248,233,233,224,0};
	char sivan[5] = {239,229,233,241,0};
	char tamoz[5] = {230,229,238,250,0};
	char av[3] = {225,224,0};
	char elul[5] = {236,229,236,224,0};

	char *mon[9] = {adar, adar1, adar2, nisan, iyar, sivan,
	tamoz, av, elul};

	int nAdd = (bLeap == false)? 0:1;
	int newIdx = idx - nAdd - 4;
	switch(idx)
	{
	case 1:
		str = tishray;
		break;
	case 2:
		str = heshvan;
		break;
	case 3:
		str = kislev;
		break;
	case 4:
		str = tevet;
		break;
	case 5:
		str = shvat;
		break;
	case 6:
		str = mon[nAdd];
		break;
	case 7:
		str = mon[newIdx];
		break;
	case 8:
		str = mon[newIdx];
		break;
	case 9:
		str = mon[newIdx];
		break;
	case 10:
		str = mon[newIdx];
		break;
	case 11:
		str = mon[newIdx];
		break;
	case 12:
		str = mon[newIdx];
		break;
	case 13:
		str = mon[newIdx];
		break;
	}

	int size = 5 - str.GetLength();
	for(int i = 0; i < size; i++)
		str += " ";

	return str;
}

CString CDateStr::GetMDayStr(void)
{
	if(m_MDays.Days < 1 || m_MDays.Days > 30)
		return "";
	char letter[13] = 
	{224,225,226,227,228,229,
	230,231,232,233,235,236,0};

	CString str;
	int asarot = m_MDays.Days / 10;
	int yamim = m_MDays.Days % 10;

	if(asarot == 1 && (yamim == 5 || yamim == 6))
	{
		str += letter[yamim];
		str += letter[8];
		return str;
	}

	if(yamim)
	{
		str += letter[yamim - 1];
	}

	if(asarot)
	{
		str += letter[8 + asarot];
	}

	if(str.GetLength() == 1)
		str += " ";
	

	return str;
}

CString CDateStr::GetHourMinuts(void)
{
	CString s;
	s.Format("%.2d:%.2d", m_MDays.Hours, m_MDays.Halakim / 18);
	return s;
}

CString CDateStr::ShahaStr(void)
{
	char sHour[5] = {32,228,242,249,0};
	return CString(sHour);
}

CString CDateStr::GetDateAndMinuts(void)
{
	CString str = GetWeekDay() + "   " +
		GetHourMinuts() + ShahaStr() + " " + GetMDayStr()
		+ " " + GetMonthStr() + " "
		+ GetYearStr();
	return str;
}

CString CDateStr::GetWeekDay(void)
{
	char sYom[5] = {32,237,229,233,0};
	char sYomshvoa[8] = {230,224,225,226,227,228,229,0};
	CString s;
	s = sYomshvoa[m_wday];
	s += sYom;
	return s;
}

void CDateStr::operator=(const CTimeUnit& ob)
{
	m_MDays = ob;
	CDaysPast dp(1);
	CYMDs ymd = dp + m_MDays.Days;
	dp = ymd;
	m_years = ymd.Years;
	m_month = ymd.Months;
	m_wday = dp.WeekDay();
	//m_wday = (m_wday +2) % 7;
	m_MDays.Days = ymd.MDays;
}
