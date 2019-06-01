#pragma once
#include "CGameObject.h"
class CBullet
{
	POINTFLOAT ptbulpos;
	CGameObject* ptargetobj;

	FLOAT d;
public:
	CBullet(POINTFLOAT initPos, CGameObject* target);
	~CBullet();

	void Bullet_Move();

};