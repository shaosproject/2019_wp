#pragma once
#include "CGameObject.h"


class Bullet;
class CPlayer : public CGameObject
{
	BOOL R_On, L_On, U_On, D_On;
	BOOL pressQ, onshield;

	UINT returntime, shieldtime;


	UINT cooltime_Return;
	UINT cooltime_Shield;
	UINT cooltime_AoE;
	UINT cooltime_Shoot;

	CGameObject* ptarget;
	Bullet* pbullet;
	const INT iAoERadius;


public:
	CPlayer(POINTFLOAT ainitPos, TEAM team, CGameObject* enemylist);
	~CPlayer();

	virtual void Draw(HDC hdc);
	virtual void Update();

	void MSG_Key(UINT message, WPARAM wParam);
	void MSG_MouseMove(POINT mousepos);
	void MSG_MouseUp(POINT mousepos);
	void MSG_MouseDown(POINT mousepos);

	void Move();
	void ActiveShield();
	void ReturnHome();


	POINTFLOAT Player_Vector();
	void SetPos(INT x, INT y);
	void Attack();


	virtual INT		GetObjRadius();
	virtual void	Death() {};

};