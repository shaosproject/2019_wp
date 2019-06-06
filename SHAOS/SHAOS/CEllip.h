#pragma once
#include "CUnit.h"
class CEllip : public CUnit
{
public:
	CEllip(POINTFLOAT initPos, TEAM team, CGameObject* enemylist);
	~CEllip();
	virtual void Draw(HDC hdc);
	virtual void Update();

	virtual INT		GetObjRadius();
	virtual void Death() {};

};

