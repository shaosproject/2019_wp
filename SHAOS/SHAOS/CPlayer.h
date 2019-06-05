#pragma once
#include "CGameObject.h"

class CPlayer : public CGameObject
{
	BOOL R_On, L_On, U_On, D_On;
	BOOL pressQ;
	UINT returntime;	// 귀환 캐스팅 시간

	const INT iAoERadius;
public:
	CPlayer(POINTFLOAT ainitPos);
	~CPlayer();

	void Player_Attack();

	void Player_Message(UINT message, WPARAM wParam);

	void Move();
	void ReturnHome();

	virtual void Draw(HDC hdc);
	virtual void Update();

	POINTFLOAT Player_Vector();
	void SetPos(INT x, INT y);
};