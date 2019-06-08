#include "pch.h"
#include "CGameObject.h"
#include "CHp.h"


CGameObject::CGameObject(POINTFLOAT ainitPos, TEAM ateam, CGameObject* aenemylist)
	: mptpos(ainitPos) , team(ateam), menemylist(aenemylist)
{
	mdeath = FALSE;
	ideatheffecttime = 0;
}


CGameObject::~CGameObject()
{
}

void CGameObject::DrawHP(HDC hdc)
{
	if (mdeath) return;
	FillRect(hdc, &mrchpbar, hHPBRUSH);
}

POINTFLOAT CGameObject::GetPos() const
{
	return mptpos;
}

RECT CGameObject::GetRng() const
{
	return mrcRng;
}


void CGameObject::PutDamage(INT damage)
{
	// mhp가 0이면 true리턴
	if (mhp->SubHp(damage)) {
		mdeath = TRUE;
		Death();
	}
}

BOOL CGameObject::IsDead() const
{
	return mdeath;
}
