#pragma once
#include "CTeam.h"

class CTurret;

class CEnemy : public CTeam
{
	// gameobjlist에 타워, 포탑, 유닛 순으로 연결
	CTower* mTower;
	CTurret* mTurret1, * mTurret2,* mTurret3,* mTurret4;

	const POINTFLOAT ptUnitSponPos = { 3200, 350 };


public:
	CEnemy();
	~CEnemy();

	void SetInitObj();

	void Update();

	void Draw(HDC hdc);

	void UnitGen();

};