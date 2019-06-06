#pragma once
#include "CTeam.h"
const POINTFLOAT TURRET1_POS = { 1850,350 };
const POINTFLOAT TURRET2_POS = { 2315,70 };
const POINTFLOAT TURRET3_POS = { 2315,630 };
const POINTFLOAT TURRET4_POS = { 2775,350 };

class CTurret;
class CEnemy : public CTeam
{
	// gameobjlist에 타워, 포탑, 유닛 순으로 연결
	CTower* mTower;
	CUnit* mUnithead;
	CTurret* mTurret1, * mTurret2,* mTurret3,* mTurret4;
public:
	CEnemy();
	~CEnemy();

	void Draw(HDC hdc);
};