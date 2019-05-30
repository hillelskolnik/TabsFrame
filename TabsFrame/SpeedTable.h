#pragma once
#include "..\timespeed\basicunit.h"

static const CYMDs g_IkarRefael = {5490,7,2};

static const CYMDs g_IkarRambam = {4938,8,3};

class CSpeedTable
{
public:
	CSpeedTable(void);
public:
	~CSpeedTable(void);
public:
	CCircleSpeed emzaShemesh;
	CCircleSpeed govaShemesh;
	CCircleSpeed emzaYareach;
	CCircleSpeed maslulYareach;
	CCircleSpeed emzaRosh;
};

static CSpeedTable g_table;

class CIkaryRefael
{
public:
	CIkaryRefael(void);
public:
	~CIkaryRefael(void);
public:
	CCircleSpeed emzaShemesh;
	CCircleSpeed govaShemesh;
	CCircleSpeed emzaYareach;
	CCircleSpeed maslulYareach;
	CCircleSpeed emzaRosh;
};

static CIkaryRefael g_IkaryRefael;

