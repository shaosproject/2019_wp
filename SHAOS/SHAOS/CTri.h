#pragma once
#include "CUnit.h"
class CTri : public CUnit
{
public:
	CTri(POINTFLOAT initPos, TEAM team, CGameObject* enemylist);
	~CTri();
	virtual void Draw(HDC hdc);
	virtual void Update();

	virtual INT	GetObjRadius();
};

