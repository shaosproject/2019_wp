#pragma once
#include "CUnit.h"
#include "CTower.h"

class CRect : public CUnit
{
	const INT iattakradius = RECT_RADIUS + 5;

public:
	CRect(POINTFLOAT ainitPos, TEAM team, CGameObject* enemylist);
	~CRect();
	virtual void Draw(HDC hdc);
	virtual void Update();
	
	void Move();
	void Attack();


	virtual INT		GetObjRadius();
	virtual void Death() {};

};

