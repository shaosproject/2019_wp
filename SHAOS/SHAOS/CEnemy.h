#pragma once
#include "CTeam.h"
class CTurret;
class CEnemy : public CTeam
{
	// gameobjlist�� Ÿ��, ��ž, ���� ������ ����
	CTower* mTower;
	CTurret* mPlayer;
	CUnit* mUnithead;
public:
	CEnemy();
	~CEnemy();

	void Draw(HDC hdc);
};