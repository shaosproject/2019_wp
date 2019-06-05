#include "pch.h"
#include "CEnemy.h"
#include "CTurret.h"

CEnemy::CEnemy()
{
	mTower = new CTower(ENEMYTOWER_POS);
	this->AddMyObjList(mTower);
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
