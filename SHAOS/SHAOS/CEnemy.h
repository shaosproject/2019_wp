#pragma once
#include "CTeam.h"
class CTurret;
class CEnemy : public CTeam
{
	// gameobjlist에 타워, 포탑, 유닛 순으로 연결
	CTower* mTower;
	CTurret* mPlayer;
	CUnit* mUnithead;
public:
	CEnemy();
	~CEnemy();

	void Draw(HDC hdc);
};