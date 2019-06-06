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
