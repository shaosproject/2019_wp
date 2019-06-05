#include "pch.h"
#include "CTurret.h"


CTurret::CTurret(POINTFLOAT initPos) : CGameObject(initPos)
{
	mrchpbar = { mrcRng.left, mrcRng.top - 7, mrcRng.right, mrcRng.top - 4 };

}


CTurret::~CTurret()
{
}

RECT* CTurret::Turret_Rect()
{
	mrcRng = { (LONG)mptpos.x - TURRET_RADIUS ,(LONG)mptpos.y - TURRET_RADIUS ,(LONG)mptpos.x + TURRET_RADIUS ,(LONG)mptpos.y + TURRET_RADIUS };
	return &mrcRng;
}
void CTurret::Draw(HDC hdc)
{
	FillRect(hdc, Turret_Rect(), (HBRUSH)GetStockObject(WHITE_BRUSH));
	//RoundRect(hdc, mrcRng.left,mrcRng.top, mrcRng.right,mrcRng.bottom, TURRET_RADIUS, TURRET_RADIUS);
}

