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
	CUnit(POINTFLOAT ainitPos);
	~CUnit();

	virtual void Draw(HDC hdc) = 0;
	virtual void Update() = 0;

};

