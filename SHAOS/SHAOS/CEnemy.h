#pragma once
#include "CTeam.h"
class CTurret;
class CEnemy : public CTeam
{
	// gameobjlist�� Ÿ��, ��ž, ���� ������ ����
	CTower* mTower;
	CUnit* mUnithead;
	CTurret* mTurret;
public:
	CEnemy();
	~CEnemy();

	void Draw(HDC hdc);
};