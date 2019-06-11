#pragma once
#include "CGameObject.h"

#define PLAYER_EFFECTTIME_AOE (FRAMETIME * 10)
#define PLAYER_EFFECTTIME_DEATH (FRAMETIME* 500)
#define PLAYER_SHOOT_LENGTH 200
#define PLAYER_SHOOTDAMAGE 20

const HPEN hPLAYERSHOOTPEN = 
	CreatePen(PS_SOLID, 50, RGB(0, 200, 200));

class Bullet;
class Sound;
class CPlayer : public CGameObject
{
	BOOL R_On, L_On, U_On, D_On;
	BOOL pressQ, pressSft, onshield;


	UINT effecttime_AoE;
	UINT effecttime_Shoot;
	UINT effecttime_Return;

	UINT castingtime_return;
	UINT activetime_shield;
	
	const INT iAoERadius;

	UINT cooltime_Shoot;
	UINT cooltime_AoE;
	UINT cooltime_Shield;
	UINT cooltime_Return;
	UINT cooltime_Death;

	POINT triangle1[3];
	POINT triangle2[3];

	CGameObject*	ptarget;
	Bullet*			pbullet;

	POINT worldmousepos;

	RECT shootattackrange[7];
	BOOL immotal;
public:
	CSound* msound{ nullptr };
	CPlayer(POINTFLOAT ainitPos, TEAM team, CGameObject* enemylist);
	~CPlayer();

	virtual void		Draw(HDC hdc);
	virtual void		Update();

	void				MSG_Key(UINT message, WPARAM wParam);
	void				MSG_MouseMove(POINT mousepos);
	void				MSG_MouseUp(POINT mousepos);
	void				MSG_MouseDown(POINT mousepos);

	void				Move();
	BOOL				Attack();


	void				Skill_Shoot();
	void				Skill_AreaOfEffect();
	void				ActiveShield();
	void				ReturnHome();



	virtual INT			GetObjRadius();
	virtual void		Death();

	POINTFLOAT			Player_Vector();
	void				SetPos(POINT setpos);
	void				UI_GetPlayerInfo(INT* ahp, INT* ct_shoot, INT* ct_AoE, INT* ct_shield, INT* ct_return);
	void				PutDamage(INT damage);
};