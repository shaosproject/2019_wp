#pragma once
#include "CGameObject.h"

#define UNIT_RECOGRNGRADIUS 300
#define UNIT_EFFECTTIME_DEATH (FRAMETIME*50)

class CTower;

class CUnit : public CGameObject
{
protected:
	BOOL moveOn;
	POINTFLOAT ptenemytowerpos;
	CGameObject* pattacktarget;

public:
	CUnit(POINTFLOAT ainitPos, TEAM team, CGameObject* enemylist);
	~CUnit();

	virtual void Draw(HDC hdc) = 0;
	virtual void Update() = 0;

	virtual INT GetObjRadius() = 0;
	virtual void Death();
};

