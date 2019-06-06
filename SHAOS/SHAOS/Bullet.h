#pragma once
#include "Bullet.h"
#define BULLET_SPEED 3
#define BULLET_RAD 3

class CGameObject;
class Bullet
{
	POINTFLOAT ptbulletpos;
	CGameObject* ptargetobj;
	
	FLOAT d;

public:
	Bullet(const POINTFLOAT* initPos, CGameObject* target);
	~Bullet();
	void Move();
	void Draw(HDC hdc);
};