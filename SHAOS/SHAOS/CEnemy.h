#pragma once
#include "CTeam.h"

class CTurret;

class CEnemy : public CTeam
{
	// gameobjlist�� Ÿ��, ��ž, ���� ������ ����
	CTower* mTower;
	CTurret* mTurret1, * mTurret2,* mTurret3,* mTurret4;

	const POINTFLOAT ptUnitSponPos1 = { 3200, 200 };
	const POINTFLOAT ptUnitSponPos2 = { 3200, 500 };


public:
	CEnemy();
	~CEnemy();

	void SetInitObj();

	void Update();

	void Draw(HDC hdc);

	void UnitGen();

};