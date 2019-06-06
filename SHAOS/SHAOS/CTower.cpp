#include "pch.h"
#include "CTower.h"


CTower::CTower(POINTFLOAT initPos, TEAM team, CGameObject* enemylist)
	: CGameObject(initPos, team, enemylist)
{
	mrcRng = { (LONG)TOWER_LEFT(initPos.x), (LONG)TOWER_TOP,
		(LONG)TOWER_RIGHT(initPos.x), (LONG)TOWER_BOTTOM };


	mhp = new CHp(TOWER_MAXHP);
	if (team == TEAM::USER) {
		mrchpbar = { mrcRng.left - 7, mrcRng.top, mrcRng.left - 4, mrcRng.bottom };
	}
	else {
		mrchpbar = { mrcRng.right + 4, mrcRng.top, mrcRng.right + 7, mrcRng.bottom };
	}
}


CTower::~CTower()
{
	delete mhp;
}


void CTower::Draw(HDC hdc)
{
	//HBRUSH hNew, hOld;
	//hNew = CreateSolidBrush(RGB(25, 25, 112));
	//hOld = (HBRUSH)SelectObject(hdc, hNew);

	Rectangle(hdc, mrcRng.left, mrcRng.top, mrcRng.right, mrcRng.bottom);
	//DeleteObject(SelectObject(hdc, hOld));
}

INT CTower::GetObjRadius()
{
	// 충돌체크 어떻게 하지.... 곤란하다
	return 0;
}

void CTower::Death()
{
	// 게임 끝~~~
}
