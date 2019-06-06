#include "pch.h"
#include "CEllip.h"


CEllip::CEllip(POINTFLOAT initPos, TEAM team, CGameObject* enemylist)
	: CUnit(initPos, team, enemylist)
{
	mrcRng = { (LONG)mptpos.x - ELLIP_RADIUS, (LONG)mptpos.y - ELLIP_RADIUS,
		(LONG)mptpos.x + ELLIP_RADIUS, (LONG)mptpos.y + ELLIP_RADIUS };

	mhp = new CHp(ELLIP_MAXHP);
	if (team == TEAM::USER) {
		mrchpbar = { mrcRng.left - 7, mrcRng.top, mrcRng.left - 4, mrcRng.bottom };
	}
	else {
		mrchpbar = { mrcRng.right + 4, mrcRng.top, mrcRng.right + 7, mrcRng.bottom };
	}

}


CEllip::~CEllip()
{
	delete mhp;
}

void CEllip::Draw(HDC hdc)
{
	Ellipse(hdc, mrcRng.left, mrcRng.top, mrcRng.right, mrcRng.bottom);
}

void CEllip::Update()
{
}

INT CEllip::GetObjRadius()
{
	return ELLIP_RADIUS;
}
