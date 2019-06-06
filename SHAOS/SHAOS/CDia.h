#pragma once
#include "CUnit.h"
class CDia : public CUnit
{
public:
	CDia(POINTFLOAT initPos, TEAM team, CGameObject* enemylist);
	~CDia();
	virtual void Draw(HDC hdc);
	virtual void Update();

	virtual INT		GetObjRadius();
};

