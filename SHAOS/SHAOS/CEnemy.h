#pragma once
#include "CTeam.h"

class CTurret;

class CEnemy : public CTeam
{
	// gameobjlist�� Ÿ��, ��ž, ���� ������ ����
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