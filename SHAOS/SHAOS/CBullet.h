#pragma once

class CBullet
{
	POINTFLOAT bulPos;
	FLOAT d;
	POINTFLOAT* enemyPos;
public:
	CBullet();

	CBullet(POINTFLOAT FstPos, POINTFLOAT* enemy);

	~CBullet();

	void Bullet_Move();

};