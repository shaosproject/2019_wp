#include "pch.h"
#include "CTurret.h"


CTurret::CTurret(POINTFLOAT initPos, TEAM team, CGameObject* enemylist)
	: CGameObject(initPos, team, enemylist)
{
	mrcRng = { (LONG)initPos.x - TURRET_RADIUS ,(LONG)initPos.y - TURRET_RADIUS,
		(LONG)initPos.x + TURRET_RADIUS, (LONG)initPos.y + TURRET_RADIUS };


	mhp = new CHp(TOWER_MAXHP);
	mrchpbar = { mrcRng.right + 4, mrcRng.top, mrcRng.right + 7, mrcRng.bottom };
}


CTurret::~CTurret()
{
	delete mhp;
}

void CTurret::Draw(HDC hdc)
{
	//FillRect(hdc, &mrcRng, (HBRUSH)GetStockObject(WHITE_BRUSH));
	RoundRect(hdc, mrcRng.left,mrcRng.top, mrcRng.right,mrcRng.bottom,
		TURRET_RADIUS/5*4, TURRET_RADIUS/5*4);
}

void CTurret::Update()
{
	// hp바 업데이트
	mrchpbar.top = mrcRng.bottom - GETHPBAR(mhp->GetHp(), TURRET_RADIUS * 2, PLAYER_MAXHP);
}

void CTurret::SelectedDraw(HDC hdc)
{
	HBRUSH hOld = (HBRUSH)SelectObject(hdc, hSELECTEDBRUSH);
	RoundRect(hdc, mrcRng.left - 4, mrcRng.top - 4,
		mrcRng.right + 4, mrcRng.bottom + 4,
		TURRET_RADIUS / 5 * 4, TURRET_RADIUS / 5 * 4);
	SelectObject(hdc, hOld);
}

INT CTurret::GetObjRadius()
{
	return TURRET_RADIUS;
}

void CTurret::Death()
{
	// 1. 리스트에서 빼줘야함(동적할당 헤제)

	this->prev->next = this->next;
	this->next->prev = this->prev;

	mdeath = TRUE;
	//delete this; -> 여기서 죽이면 안 된다 나중에 모든 처리가 끝나고 나서...
	// 2. 죽는 이펙트
}

