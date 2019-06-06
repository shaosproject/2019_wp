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
	RoundRect(hdc, mrcRng.left,mrcRng.top, mrcRng.right,mrcRng.bottom, TURRET_RADIUS/5*4, TURRET_RADIUS/5*4);
}

INT CTurret::GetObjRadius()
{
	return TURRET_RADIUS;
}

