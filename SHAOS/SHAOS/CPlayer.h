#pragma once
#include "CMoveUnit.h"


class CPlayer : public CMoveUnit
{
	BOOL R_On, L_On, U_On, D_On;
public:
	CPlayer();
	~CPlayer();

	void Player_Attack();

	void Player_Message(UINT message, WPARAM wParam);

	void Move(POINTFLOAT vector);

	virtual void Draw(HDC hdc);

	POINTFLOAT Player_Vector();
};