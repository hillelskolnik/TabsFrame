#include "StdAfx.h"
#include "Person.h"
#include "Perek2DBase.h"


enum
{
	head = 100
	,neck
	,shoulder
	,body
	,rightHand
	,leftHand
	,rightShoe
	,leftShoe
};

CPerson::CPerson(C3DScreen& treedscreen)
:m_3dscreen(treedscreen)
{
}

CPerson::~CPerson(void)
{
}

void CPerson::Create(void)
{
	int bodyHeight = 50;
	int shoeHieght = 3;
	int shoulderHieght = 6;
	int neckHieght = 2;
	int headHieght = 15;
	m_3dscreen.BeginObject(body);
	m_3dscreen.CreateCylinderObject(20,35,bodyHeight,RGB(234,240,246));
	m_3dscreen.ShiftObjectCenter(bodyHeight/2+shoeHieght, axis_y, true);

	m_3dscreen.BeginObject(shoulder);
	m_3dscreen.CreateCylinderObject(8,20,shoulderHieght,RGB(234,240,246));
	m_3dscreen.ShiftObjectCenter(
		bodyHeight+shoeHieght + shoulderHieght/2, 
		axis_y, true);

	m_3dscreen.BeginObject(neck);
	m_3dscreen.CreateCylinderObject(8,8,neckHieght,RGB(234,240,246));
	m_3dscreen.ShiftObjectCenter(
		bodyHeight+shoeHieght + shoulderHieght
		+ neckHieght/2, 
		axis_y, true);

	m_3dscreen.BeginObject(rightHand);
	m_3dscreen.CreateCylinderObject(10,8,30,RGB(200,224,246));
	m_3dscreen.ShiftObjectCenter(-15, axis_y, true);
	m_3dscreen.TurnObjectCenter(-60, axis_z, true);
	m_3dscreen.TurnShape(-60, axis_z, false, true);
	m_3dscreen.ShiftObjectCenter(
		bodyHeight+shoeHieght, axis_y, true);
	m_3dscreen.ShiftObjectCenter(-4, axis_x, true);

	m_3dscreen.BeginObject(leftHand);
	m_3dscreen.CreateCylinderObject(10,8,30,RGB(200,224,246));
	m_3dscreen.ShiftObjectCenter(-15, axis_y, true);
	m_3dscreen.TurnObjectCenter(60, axis_z, true);
	m_3dscreen.TurnShape(60, axis_z, false, true);
	m_3dscreen.ShiftObjectCenter(
		bodyHeight+shoeHieght, axis_y, true);
	m_3dscreen.ShiftObjectCenter(4, axis_x, true);

	int steps = CPerek2DBase::DiameterSteps(headHieght);
	int thth = steps *3/4;
	m_3dscreen.BeginObject(head);
	m_3dscreen.CreateSphereObject(headHieght, RGB(255,155,64));
	m_3dscreen.ShiftObjectCenter(
		bodyHeight+shoeHieght + shoulderHieght
		+ neckHieght + headHieght/2, 
		axis_y, true);
	m_3dscreen.FillRect(thth -5, steps/4 - 3,2,1,0);
	m_3dscreen.FillRect(thth +5, steps/4 - 3,2,1,0);
	m_3dscreen.FillRect(thth , steps/4 - 0,1,2,RGB(192,100,41));
	m_3dscreen.FillRect(thth -1 , steps/4 + 3 ,3,1,RGB(192,100,41));
	m_3dscreen.FillRect(0 , 0 ,steps,steps/8,RGB(128,64,64));
	m_3dscreen.TurnShape(-5, axis_x, false, true);

	m_3dscreen.BeginObject(rightShoe);
	m_3dscreen.CreateCylinderObject(4,shoeHieght*2,20,RGB(128,64,64),
		180.0);
	m_3dscreen.ShiftObjectCenter(10, axis_y, true);
	m_3dscreen.ShiftObjectCenter(-10, axis_X, true);
	m_3dscreen.TurnObjectCenter(90, axis_x, true);
	m_3dscreen.TurnShape(90, axis_x, false, true);
	m_3dscreen.ShiftObjectCenter(1, axis_y, true);

	m_3dscreen.BeginObject(leftShoe);
	m_3dscreen.CreateCylinderObject(4,shoeHieght*2,20,RGB(128,64,64),
		180.0);
	m_3dscreen.ShiftObjectCenter(10, axis_y, true);
	m_3dscreen.ShiftObjectCenter(10, axis_X, true);
	m_3dscreen.TurnObjectCenter(90, axis_x, true);
	m_3dscreen.TurnShape(90, axis_x, false, true);
	m_3dscreen.ShiftObjectCenter(1, axis_y, true);

}

void CPerson::Turn(double angle, Axis ax, bool bLastTurn)
{
	m_3dscreen.BeginObject(body);
	m_3dscreen.TurnObjectCenter(angle, ax);
	m_3dscreen.TurnShape(angle, ax, bLastTurn);
	if(bLastTurn)
		m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(shoulder);
	m_3dscreen.TurnObjectCenter(angle, ax);
	m_3dscreen.TurnShape(angle, ax, bLastTurn);
	if(bLastTurn)
		m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(neck);
	m_3dscreen.TurnObjectCenter(angle, ax);
	m_3dscreen.TurnShape(angle, ax, bLastTurn);
	if(bLastTurn)
		m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(head);
	m_3dscreen.TurnObjectCenter(angle, ax);
	m_3dscreen.TurnShape(angle, ax, bLastTurn);
	if(bLastTurn)
		m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(rightShoe);
	m_3dscreen.TurnObjectCenter(angle, ax);
	m_3dscreen.TurnShape(angle, ax, bLastTurn);
	if(bLastTurn)
		m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(leftShoe);
	m_3dscreen.TurnObjectCenter(angle, ax);
	m_3dscreen.TurnShape(angle, ax, bLastTurn);
	if(bLastTurn)
		m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(rightHand);
	m_3dscreen.TurnObjectCenter(angle, ax);
	m_3dscreen.TurnShape(angle, ax, bLastTurn);
	if(bLastTurn)
		m_3dscreen.Translate3Dto2D();

	m_3dscreen.BeginObject(leftHand);
	m_3dscreen.TurnObjectCenter(angle, ax);
	m_3dscreen.TurnShape(angle, ax, bLastTurn);
	if(bLastTurn)
		m_3dscreen.Translate3Dto2D();

}

void CPerson::Hide(void)
{
	m_3dscreen.BeginObject(body);
	m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(shoulder);
	m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(neck);
	m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(head);
	m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(rightShoe);
	m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(leftShoe);
	m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(rightHand);
	m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

	m_3dscreen.BeginObject(leftHand);
	m_3dscreen.Translate3Dto2D(FALSE, 0, OB_PAUSE);

}

void CPerson::Reset(void)
{
	m_3dscreen.BeginObject(body);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();
	
	m_3dscreen.BeginObject(shoulder);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();

	m_3dscreen.BeginObject(neck);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();

	m_3dscreen.BeginObject(head);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();

	m_3dscreen.BeginObject(rightShoe);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();

	m_3dscreen.BeginObject(leftShoe);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();

	m_3dscreen.BeginObject(rightHand);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();

	m_3dscreen.BeginObject(leftHand);
	m_3dscreen.ResetTranslation();
	m_3dscreen.ResetShift();

}

void CPerson::Shift(double shift, Axis ax, bool bLastTurn)
{
	m_3dscreen.BeginObject(body);
	m_3dscreen.ShiftObjectCenter(shift, ax);
	if(bLastTurn)
	{
		m_3dscreen.TurnShape(0.0, ax);
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(shoulder);
	m_3dscreen.ShiftObjectCenter(shift, ax);
	if(bLastTurn)
	{
		m_3dscreen.TurnShape(0.0, ax);
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(neck);
	m_3dscreen.ShiftObjectCenter(shift, ax);
	if(bLastTurn)
	{
		m_3dscreen.TurnShape(0.0, ax);
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(head);
	m_3dscreen.ShiftObjectCenter(shift, ax);
	if(bLastTurn)
	{
		m_3dscreen.TurnShape(0.0, ax);
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(rightShoe);
	m_3dscreen.ShiftObjectCenter(shift, ax);
	if(bLastTurn)
	{
		m_3dscreen.TurnShape(0.0, ax);
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(leftShoe);
	m_3dscreen.ShiftObjectCenter(shift, ax);
	if(bLastTurn)
	{
		m_3dscreen.TurnShape(0.0, ax);
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(rightHand);
	m_3dscreen.ShiftObjectCenter(shift, ax);
	if(bLastTurn)
	{
		m_3dscreen.TurnShape(0.0, ax);
		m_3dscreen.Translate3Dto2D();
	}

	m_3dscreen.BeginObject(leftHand);
	m_3dscreen.ShiftObjectCenter(shift, ax);
	if(bLastTurn)
	{
		m_3dscreen.TurnShape(0.0, ax);
		m_3dscreen.Translate3Dto2D();
	}
}

void CPerson::Shrink(double vec)
{
	m_3dscreen.BeginObject(body);
	m_3dscreen.FillRect(0,0,(int)300, 300, 0
		,fr_shrink , vec);

	m_3dscreen.BeginObject(shoulder);
	m_3dscreen.FillRect(0,0,(int)300, 300, 0
		,fr_shrink , vec);

	m_3dscreen.BeginObject(neck);
	m_3dscreen.FillRect(0,0,(int)300, 300, 0
		,fr_shrink , vec);

	m_3dscreen.BeginObject(head);
	m_3dscreen.FillRect(0,0,(int)300, 300, 0
		,fr_shrink , vec);

	m_3dscreen.BeginObject(rightShoe);
	m_3dscreen.FillRect(0,0,(int)300, 300, 0
		,fr_shrink , vec);

	m_3dscreen.BeginObject(leftShoe);
	m_3dscreen.FillRect(0,0,(int)300, 300, 0
		,fr_shrink , vec);

	m_3dscreen.BeginObject(rightHand);
	m_3dscreen.FillRect(0,0,(int)300, 300, 0
		,fr_shrink , vec);

	m_3dscreen.BeginObject(leftHand);
	m_3dscreen.FillRect(0,0,(int)300, 300, 0
		,fr_shrink , vec);

}
