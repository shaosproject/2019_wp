#pragma once
#include "CGameObject.h"



#define PLAYER_EFFECTTIME_AOE FRAMETIME * 10
#define PLAYER_EFFECTTIME_DEATH FRAMETIME* 500

class Bullet;
class CPlayer : public CGameObject
{
	BOOL R_On, L_On, U_On, D_On;
	BOOL pressQ, pressSft, onshield;


	UINT iaoeeffecttime;
	UINT returntime, shieldtime;
	

	UINT cooltime_Shoot;
	UINT cooltime_AoE;
	UINT cooltime_Shield;
	UINT cooltime_Return;
	UINT cooltime_Death;

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
	void Skill_AreaOfEffect();
	void Skill_Shoot();
	void ActiveShield();
	void ReturnHome();


	POINTFLOAT Player_Vector();
	void SetPos(POINT setpos);
	void Attack();


	virtual INT		GetObjRadius();
	virtual void	Death();

};