#include "pch.h"
#include "CEnemy.h"
#include "CTurret.h"

#include "CRect.h"
#include "CEllip.h"
#include "CDia.h"
#include "CTri.h"

CEnemy::CEnemy()
{
	mTower = new CTower(ENEMYTOWER_POS, TEAM::ENEMY, nullptr);
	p_myobjlist = mTower;
	p_myobjlist->next = p_myobjlist->prev = p_myobjlist;

}


CEnemy::~CEnemy()
{
}

void CEnemy::SetInitObj()
{
	mTurret1 = new CTurret(TURRET1_POS, TEAM::ENEMY, p_opponentobjlist);
	this->AddMyObjList(mTurret1);

	mTurret2 = new CTurret(TURRET2_POS, TEAM::ENEMY, p_opponentobjlist);
	this->AddMyObjList(mTurret2);

	mTurret3 = new CTurret(TURRET3_POS, TEAM::ENEMY, p_opponentobjlist);
	this->AddMyObjList(mTurret3);

	mTurret4 = new CTurret(TURRET4_POS, TEAM::ENEMY, p_opponentobjlist);
	this->AddMyObjList(mTurret4);

	CUnit* unit = new CRect(ptUnitSponPos, TEAM::ENEMY, p_opponentobjlist);
	this->AddMyObjList(unit);


}

void CEnemy::Update()
{
	CGameObject* tmp = p_myobjlist;
	for (int i = 0; i < imyobjnum; i++) {
		tmp->Update();
		if (tmp->IsDelete()) {
			CGameObject* delp = tmp;
			tmp = tmp->next;
			DeleteInList(delp);
			continue;
		}
		tmp = tmp->next;
	}

}

void CEnemy::Draw(HDC hdc)
{
	CGameObject* tmp = p_myobjlist;
	for (int i = 0; i < imyobjnum; i++) {
		tmp->Draw(hdc);
		tmp->DrawHP(hdc);
		tmp = tmp->next;
	}
}

void CEnemy::UnitGen()
{
}
