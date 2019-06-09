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

	CUnit* unit1 = new CRect(ptUnitSponPos1, TEAM::ENEMY, p_opponentobjlist);
	this->AddMyObjList(unit1);

	CUnit* unit2 = new CRect(ptUnitSponPos2, TEAM::ENEMY, p_opponentobjlist);
	this->AddMyObjList(unit2);

}

void CEnemy::Update()
{
	CGameObject* tmp = p_myobjlist;
	for (int i = 0; i < imyobjnum; i++) {

		tmp->Update();

		if (tmp->IsDelete()) {
			if (tmp == p_myobjlist) {
				GameOver();
				return;
			}
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

void CEnemy::GameOver()
{

}
