#include "pch.h"
#include "CGameObject.h"
#include "CHp.h"
#include "Sound.h"

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
	// mhp�� 0�̸� true����
	if (mhp->SubHp(damage)) {
		if(!mdeath) Death();
		mdeath = TRUE;
	}
}

BOOL CGameObject::IsDead() const
{
	return mdeath;
}

BOOL CGameObject::IsDelete() const
{
	if (mdeath && !ideatheffecttime) return TRUE;
	return FALSE;
}


BOOL IsInRange(CGameObject* me, CGameObject* obj, INT range) {
	float dx = me->GetPos().x - obj->GetPos().x;
	float dy = me->GetPos().y - obj->GetPos().y;

	float center_d = dx * dx + dy * dy;
	float tmp = range * range;
	if (center_d <= tmp) return TRUE;
	else return FALSE;
}