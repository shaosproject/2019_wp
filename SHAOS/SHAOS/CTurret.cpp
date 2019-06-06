#include "pch.h"
#include "CTurret.h"


CTurret::CTurret(POINTFLOAT initPos) : CGameObject(initPos)
{
	mrcRng = { (LONG)initPos.x - TURRET_RADIUS ,(LONG)initPos.y - TURRET_RADIUS,
		(LONG)initPos.x + TURRET_RADIUS, (LONG)initPos.y + TURRET_RADIUS };

	mrchpbar = { mrcRng.left, mrcRng.top - 7, mrcRng.right, mrcRng.top - 4 };
	mhp = new CHp(TOWER_MAXHP);
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

