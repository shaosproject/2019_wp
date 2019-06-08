#include "pch.h"
#include "CRect.h"
#include "CHp.h"

CRect::CRect(POINTFLOAT ainitPos, TEAM team, CGameObject* enemylist)
	: CUnit(ainitPos, team, enemylist)
{
	mrcRng = { (LONG)mptpos.x - RECT_RADIUS, (LONG)mptpos.y - RECT_RADIUS,
		(LONG)mptpos.x + RECT_RADIUS, (LONG)mptpos.y + RECT_RADIUS };

	mhp = new CHp(RECT_MAXHP);
	if (team == TEAM::USER) {
		mrchpbar = { mrcRng.left - 7, mrcRng.top, mrcRng.left - 4, mrcRng.bottom };
	}
	else {
		mrchpbar = { mrcRng.right + 4, mrcRng.top, mrcRng.right + 7, mrcRng.bottom };
	}
}

CRect::~CRect()
{
	delete mhp;
}

void CRect::Draw(HDC hdc)
{
	Rectangle(hdc, mrcRng.left, mrcRng.top, mrcRng.right, mrcRng.bottom);
}

void CRect::Update()
{
}

void CRect::Attack()
{
	CGameObject* tmp = nullptr;
	while (tmp != menemylist) {
		if (!tmp) tmp = menemylist;

		float dx = mptpos.x - tmp->GetPos().x;
		float dy = mptpos.y - tmp->GetPos().y;

		float center_d = dx * dx + dy * dy;
		float range = iattakradius + tmp->GetObjRadius();
		if (center_d <= range * range) {
			tmp->PutDamage(PLAYER_AOEDAMAGE);
		}

		tmp = tmp->next;
	}
}

INT CRect::GetObjRadius()
{
	return RECT_RADIUS;
}
