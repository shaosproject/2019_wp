#pragma once
#include "CTeam.h"
const POINTFLOAT TURRET1_POS = { 1850,350 };
const POINTFLOAT TURRET2_POS = { 2315,80 };
const POINTFLOAT TURRET3_POS = { 2315,620 };
const POINTFLOAT TURRET4_POS = { 2775,350 };

class CTurret;

class CEnemy : public CTeam
{
	// gameobjlist�� Ÿ��, ��ž, ���� ������ ����
	CTower* mTower;
	CUnit* mUnithead;
	CTurret* mTurret1, * mTurret2,* mTurret3,* mTurret4;


public:
	CEnemy();
	~CEnemy();

	virtual void SetOpponentObj(CGameObject* objlist);

	void Update();

	void Draw(HDC hdc);
};