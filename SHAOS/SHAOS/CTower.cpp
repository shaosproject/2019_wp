#include "pch.h"
#include "CTower.h"


CTower::CTower(POINTFLOAT initPos) : CBuilding(initPos)
{
	mrcRng = { (LONG)TOWER_LEFT(initPos.x), (LONG)TOWER_TOP,
		(LONG)TOWER_RIGHT(initPos.x), (LONG)TOWER_BOTTOM };
}


CTower::~CTower()
{
}


void CTower::Draw(HDC hdc)
{
	Rectangle(hdc, mrcRng.left, mrcRng.top, mrcRng.right, mrcRng.bottom);
}
