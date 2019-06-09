#include "pch.h"
#include "CEllip.h"
#include "Bullet.h"

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
	ptarget = nullptr;
}


CEllip::~CEllip()
{
	delete mhp;
}

void CEllip::Draw(HDC hdc)
{
	Ellipse(hdc, mrcRng.left, mrcRng.top,
		mrcRng.right, mrcRng.bottom);
}

void CEllip::SelectedDraw(HDC hdc, HBRUSH hbr)
{
	HBRUSH hOld = (HBRUSH)SelectObject(hdc, hbr);
	Ellipse(hdc, mrcRng.left - 2, mrcRng.top - 2,
		mrcRng.right + 2, mrcRng.bottom + 2);
	SelectObject(hdc, hOld);
}

void CEllip::Update()
{

}

void CEllip::Attack()
{
	if (!ptarget) return;

	if (pbullet) pbullet = pbullet->Move();
	else pbullet = new Bullet(&mptpos, ptarget, ELLIP_BULLETDAMAGE);

	if (ptarget->IsDead()) ptarget = nullptr;

}

INT CEllip::GetObjRadius()
{
	return ELLIP_RADIUS;
}
