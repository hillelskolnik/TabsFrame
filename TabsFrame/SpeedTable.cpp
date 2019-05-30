#include "StdAfx.h"
#include "SpeedTable.h"

CSpeedTable::CSpeedTable(void)
: emzaShemesh(0,59,8,19,48)
//: emzaShemesh(0,59,8,20,50,50,50)
, govaShemesh(0,0,0,9)
, emzaYareach(13,10,35,1,48)
, maslulYareach(13,3,53,55,48)
, emzaRosh(0,3,10,37,48)
{
}

CSpeedTable::~CSpeedTable(void)
{
}

CIkaryRefael::CIkaryRefael(void)
: emzaShemesh(356,53,15)
, govaShemesh(97,56,48)
, emzaYareach(4,29,26)
, maslulYareach(278,6,56)
, emzaRosh(57,45,2)
{
}

CIkaryRefael::~CIkaryRefael(void)
{
}
