#include "pch.h"
#include "CEllip.h"


CEllip::CEllip(POINTFLOAT initPos) : CUnit(initPos)
{
	mrcRng = { (LONG)mptpos.x - ELLIP_RADIUS, (LONG)mptpos.y - ELLIP_RADIUS,
		(LONG)mptpos.x + ELLIP_RADIUS, (LONG)mptpos.y + ELLIP_RADIUS };

	mhp = new CHp(ELLIP_MAXHP);
	mrchpbar = { mrcRng.left, mrcRng.top - 7, mrcRng.right, mrcRng.top - 4 };

}


CEllip::~CEllip()
{
	delete mhp;
}

void CEllip::Draw(HDC hdc)
{
	Ellipse(hdc, mrcRng.left, mrcRng.top, mrcRng.right, mrcRng.bottom);
}

void CEllip::Update()
{
}
