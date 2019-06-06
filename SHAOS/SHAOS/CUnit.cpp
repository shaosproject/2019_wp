#include "pch.h"
#include "CUnit.h"


CUnit::CUnit(POINTFLOAT ainitPos, TEAM team, CGameObject* enemylist)
	: CGameObject(ainitPos, team, enemylist)
{
}


CUnit::~CUnit()
{
}

void CUnit::Draw(HDC hdc)
{
}

void CUnit::Death()
{
	// 유닛이 죽는 건 공통적으로 작성할 수 있지 않을까..?
}
