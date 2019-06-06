#include "pch.h"
#include "CDia.h"


CDia::CDia(POINTFLOAT initPos) : CUnit(initPos)
{
	mrcRng = { (LONG)mptpos.x - DIA_SHORTRADIUS, (LONG)mptpos.y - DIA_SHORTRADIUS,
	(LONG)mptpos.x + DIA_SHORTRADIUS, (LONG)mptpos.y + DIA_SHORTRADIUS };

	mhp = new CHp(DIA_MAXHP);
	mrchpbar = { mrcRng.left, mrcRng.top - 7, mrcRng.right, mrcRng.top - 4 };

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

void CDia::Update()
{
}
