#pragma once
#include "Bullet.h"
#define BULLET_SPEED 1
#define BULLET_RAD 3

class CGameObject;
class Bullet
{
	POINTFLOAT ptbulletpos;
	CGameObject* ptargetobj;
	
	const INT idamage;

public:
	Bullet(const POINTFLOAT* initPos, CGameObject* target, INT damage);
	~Bullet();
	void Move();
	void Draw(HDC hdc);
};