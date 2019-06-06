#include "pch.h"
#include "CEnemy.h"
#include "CTurret.h"

CEnemy::CEnemy()
{
	mTower = new CTower(ENEMYTOWER_POS, TEAM::ENEMY, p_opponentobj);
	this->AddMyObjList(mTower);

	mTurret1 = new CTurret(TURRET1_POS, TEAM::ENEMY, p_opponentobj);
	this->AddMyObjList(mTurret1);

	mTurret2 = new CTurret(TURRET2_POS, TEAM::ENEMY, p_opponentobj);
	this->AddMyObjList(mTurret2);
	
	mTurret3 = new CTurret(TURRET3_POS, TEAM::ENEMY, p_opponentobj);
	this->AddMyObjList(mTurret3);
	
	mTurret4 = new CTurret(TURRET4_POS, TEAM::ENEMY, p_opponentobj);
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
		tmp->DrawHP(hdc);
		tmp = tmp->next;
	}
}
