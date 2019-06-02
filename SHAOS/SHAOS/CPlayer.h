#pragma once
#include "CGameObject.h"
#define PLAY_ELLIPSE_RAD 3

#define MAX_CLIENTX 4490
#define MIN_CLIENTX 10
#define MAX_CLIENTY 690
#define MIN_CLIENTY 10
#define PLAY_CLIENTX(pcx) ((pcx)<MIN_CLIENTX?MIN_CLIENTX:((pcx>MAX_CLIENTX)?MAX_CLIENTX:pcx))
#define PLAY_CLIENTY(pcy) ((pcy)<MIN_CLIENTY?MIN_CLIENTY:((pcy>MAX_CLIENTY)?MAX_CLIENTY:pcy))
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

	POINTFLOAT Player_Vector();
};