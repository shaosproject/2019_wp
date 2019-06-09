#pragma once
#include "CUnit.h"
 
class Bullet;
class CEllip : public CUnit
{
	CGameObject* ptarget;
	Bullet* pbullet;
public:
	CEllip(POINTFLOAT initPos, TEAM team, CGameObject* enemylist);
	~CEllip();
	virtual void Update();
	virtual void Draw(HDC hdc);

	virtual void SelectedDraw(HDC, HBRUSH);

	void Move();
	void Attack();

	virtual INT		GetObjRadius();
	virtual void Death() {};

};

