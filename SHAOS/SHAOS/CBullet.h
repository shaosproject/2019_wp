#pragma once
class CGameObject;
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