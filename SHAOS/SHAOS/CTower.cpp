#include "pch.h"
#include "CTower.h"


CTower::CTower(POINTFLOAT initPos) : CGameObject(initPos)
{
	mrcRng = { (LONG)TOWER_LEFT(initPos.x), (LONG)TOWER_TOP,
		(LONG)TOWER_RIGHT(initPos.x), (LONG)TOWER_BOTTOM };

	mhp = new CHp(TOWER_MAXHP);
	mrchpbar = {mrcRng.left, mrcRng.top - 7, mrcRng.right, mrcRng.top - 4};
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
