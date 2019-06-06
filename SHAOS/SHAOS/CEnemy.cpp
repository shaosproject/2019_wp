#include "pch.h"
#include "CEnemy.h"
#include "CTurret.h"

CEnemy::CEnemy()
{
	mTower = new CTower(ENEMYTOWER_POS);
	this->AddMyObjList(mTower);

	mTurret1 = new CTurret(TURRET1_POS);
	this->AddMyObjList(mTurret1);

	mTurret2 = new CTurret(TURRET2_POS);
	this->AddMyObjList(mTurret2);
	
	mTurret3 = new CTurret(TURRET3_POS);
	this->AddMyObjList(mTurret3);
	
	mTurret4 = new CTurret(TURRET4_POS);
	this->AddMyObjList(mTurret4);
}


CEnemy::~CEnemy()
{
}

void CEnemy::Draw(HDC hdc)
{
	CGameObject* tmp = p_myobj;
	for (int i = 0; i < imyobjnum; i++) {
		tmp->Draw(hdc);
		tmp = tmp->next;
	}
}
