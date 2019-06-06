#include "pch.h"
#include "CGameObject.h"
#include "CHp.h"


CGameObject::CGameObject(POINTFLOAT ainitPos) : mptpos(ainitPos)
{
}


CGameObject::~CGameObject()
{
}

void CGameObject::DrawHP(HDC hdc)
{
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
	// ���� üũ
	mhp->SubHp(damage);
}
