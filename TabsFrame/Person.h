#pragma once
#include "..\scaleveiw\3dscreen.h"

class CPerson
{
public:
	CPerson(C3DScreen& treedscreen);
public:
	virtual ~CPerson(void);
protected:
	C3DScreen& m_3dscreen;
public:
	void Create(void);
public:
	void Turn(double angle, Axis ax, bool bLastTurn = true);
public:
	void Hide(void);
public:
	void Reset(void);
public:
	void Shift(double shift, Axis ax, bool bLastTurn = true);
public:
	void Shrink(double vec);
};
