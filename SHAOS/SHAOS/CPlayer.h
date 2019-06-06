#pragma once
#include "CGameObject.h"


#define SHIELD_RAD 20
const HBRUSH hRTBRUSH= CreateSolidBrush(RGB(60, 100, 250));

#define COOLTIME_SHIELD FRAMETIME*100
#define COOLTIME_AOE FRAMETIME*100
#define COOLTIME_SHOOT FRAMETIME*100
#define CASTINGTIME_RETURN FRAMETIME * 150
#define ACTIVETIME_SHIELD FRAMETIME * 50

class CPlayer : public CGameObject
{
	BOOL R_On, L_On, U_On, D_On;
	BOOL pressQ, onshield;

	UINT returntime, shieldtime;


	UINT cooltime_Return;
	UINT cooltime_Shield;
	UINT cooltime_AoE;
	UINT cooltime_Shoot;


	const INT iAoERadius;

public:
	CPlayer(POINTFLOAT ainitPos);
	~CPlayer();

	void Player_Attack();

	void Player_Message(UINT message, WPARAM wParam);

	void Move();
	void ActiveShield();
	void ReturnHome();

	virtual void Draw(HDC hdc);
	virtual void Update();

	POINTFLOAT Player_Vector();
	void SetPos(INT x, INT y);


	virtual INT		GetObjRadius();
};