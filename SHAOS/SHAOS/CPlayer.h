#pragma once
#include "CGameObject.h"

class CPlayer : public CGameObject
{
	BOOL R_On, L_On, U_On, D_On;

public:
	CPlayer(POINTFLOAT ainitPos);
	~CPlayer();

	void Player_Attack();

	void Player_Message(UINT message, WPARAM wParam);

	void Move();

	virtual void Draw(HDC hdc);
	virtual void Update();

	POINTFLOAT Player_Vector();
};