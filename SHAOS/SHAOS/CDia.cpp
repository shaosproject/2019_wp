#include "pch.h"
#include "CDia.h"


CDia::CDia(POINTFLOAT initPos, TEAM team, CGameObject* enemylist)
	: CUnit(initPos, team, enemylist)
{
	mrcRng = { (LONG)mptpos.x - DIA_SHORTRADIUS, (LONG)mptpos.y - DIA_SHORTRADIUS,
	(LONG)mptpos.x + DIA_SHORTRADIUS, (LONG)mptpos.y + DIA_SHORTRADIUS };

	mhp = new CHp(DIA_MAXHP);
	mrchpbar = { mrcRng.right + 4, mrcRng.top, mrcRng.right + 7, mrcRng.bottom };

	pattacktarget = menemylist;	// 타겟은 상대편 타워
}


CDia::~CDia()
{
	delete mhp;
}

void CDia::Draw(HDC hdc)
{
	POINT vertax[4];
	vertax[0] = { (LONG)mptpos.x, mrcRng.top };
	vertax[1] = { mrcRng.right + 5, (LONG)mptpos.y };
	vertax[2] = { (LONG)mptpos.x, mrcRng.bottom };
	vertax[3] = { mrcRng.left - 5, (LONG)mptpos.y };

	Polygon(hdc, vertax, 4);


}

void CDia::SelectedDraw(HDC hdc, HBRUSH hbr)
{
	POINT vertax[4];
	vertax[0] = { (LONG)mptpos.x, mrcRng.top - 3 };
	vertax[1] = { mrcRng.right + 8, (LONG)mptpos.y };
	vertax[2] = { (LONG)mptpos.x, mrcRng.bottom + 3 };
	vertax[3] = { mrcRng.left - 8, (LONG)mptpos.y };


	HBRUSH hOld = (HBRUSH)SelectObject(hdc, hbr);
	Polygon(hdc, vertax, 4);
	SelectObject(hdc, hOld);
}

void CDia::Move()
{
	if (mptpos.x > MAPSIZE_WIDTH / 2) {
		mptpos.x -= 2;
	}
	else {
		// 타워를 향해서 이동
		// 이동 알고리즘을 다르게 해야지 안 겹친다

	}


	mrcRng = { (LONG)mptpos.x - DIA_SHORTRADIUS, (LONG)mptpos.y - DIA_SHORTRADIUS,
	(LONG)mptpos.x + DIA_SHORTRADIUS, (LONG)mptpos.y + DIA_SHORTRADIUS };


	mrchpbar = {
	mrcRng.right + 4,
	mrcRng.bottom - (INT)GETHPBAR(mhp->GetHp(), DIA_SHORTRADIUS * 2, DIA_MAXHP),
	mrcRng.right + 7,
	mrcRng.bottom };

}

void CDia::Update()
{
	Move();
}

INT CDia::GetObjRadius()
{
	return DIA_SHORTRADIUS;
}

void CDia::Death()
{
	ideatheffecttime = FRAMETIME * 50;
}
