#pragma once
#include "CGameObject.h"

#define PLAYER_EFFECTTIME_AOE FRAMETIME * 10
#define PLAYER_EFFECTTIME_DEATH FRAMETIME* 500
#define PLAYER_SHOOT_LENGTH 200


const HPEN hPLAYERSHOOTPEN = 
	CreatePen(PS_SOLID, 30, RGB(0, 200, 200));

class Bullet;
class Sound;
class CPlayer : public CGameObject
{
	BOOL R_On, L_On, U_On, D_On;
	BOOL pressQ, pressSft, onshield;


	UINT iaoeeffecttime;
	UINT returntime, shieldtime;
	
	const INT iAoERadius;

	UINT cooltime_Shoot;
	UINT cooltime_AoE;
	UINT cooltime_Shield;
	UINT cooltime_Return;
	UINT cooltime_Death;

	CGameObject*	ptarget;
	Bullet*			pbullet;

	POINT worldmousepos;

public:
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
};