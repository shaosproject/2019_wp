#pragma once
#include "CGameObject.h"

class CTower : public CGameObject
{
	POINT triangle1[3];
	POINT triangle2[3];

public:
	CTower(POINTFLOAT initPos, TEAM team, CGameObject* enemylist);
	~CTower();
	virtual void Draw(HDC hdc);
	virtual void Update() {};

	virtual INT		GetObjRadius();
	virtual void	Death();

};