#pragma once
#include "CGameObject.h"
enum class Move {
	DFTMOVE, TARGETMOVE, NONE
};

class CUnit : public CGameObject
{
protected:
	Move priority = Move::DFTMOVE;



public:
	CUnit(POINTFLOAT ainitPos, TEAM team, CGameObject* enemylist);
	~CUnit();

	virtual void Draw(HDC hdc) = 0;
	virtual void Update() = 0;

	virtual INT GetObjRadius() = 0;
	virtual void Death();
};

