#pragma once
#include "CGameObject.h"
#define SHIELD_RAD 20
#define ADDHP 2
const HBRUSH hRTBRUSH= CreateSolidBrush(RGB(60, 100, 250));

class CPlayer : public CGameObject
{
	BOOL R_On, L_On, U_On, D_On;
	BOOL pressQ, pressV;
	UINT returntime,shieldtime,rtbartime;
	const INT iAoERadius;

public:
	CPlayer(POINTFLOAT ainitPos);
	~CPlayer();

	void Player_Attack();

	void Player_Message(UINT message, WPARAM wParam);

	void Move();
	void ReturnHome_Sh();
	void ReturnHome();

	virtual void Draw(HDC hdc);
	virtual void Update();

	POINTFLOAT Player_Vector();
	void SetPos(INT x, INT y);
};