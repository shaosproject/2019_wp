#pragma once
#include "Bullet.h"
#define TARGET_DISTANCE 50
#define BULLET_SPEED 3
#define BULLET_RAD 3
class Bullet
{
	POINTFLOAT bulpos;
	POINTFLOAT* enempos;
	POINTFLOAT* objpos;
	FLOAT d;
	BOOL bulOn,bulstart;
public:
	Bullet(POINTFLOAT pos, POINTFLOAT* epos, POINTFLOAT* opos);
	~Bullet();
	void Target_check();
	void Move();
	void Draw(HDC hdc);
};