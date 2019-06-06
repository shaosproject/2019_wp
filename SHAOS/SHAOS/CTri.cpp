#include "pch.h"
#include "CTri.h"


CTri::CTri(POINTFLOAT initPos, TEAM team, CGameObject* enemylist)
	: CUnit(initPos, team, enemylist)
{
	mrcRng = { (LONG)mptpos.x - TRI_INNERCIRCLERADIUS, (LONG)mptpos.y - TRI_INNERCIRCLERADIUS,
		(LONG)mptpos.x + TRI_INNERCIRCLERADIUS, (LONG)mptpos.y + TRI_INNERCIRCLERADIUS };
	
	
	mhp = new CHp(TRI_MAXHP);
	mrchpbar = { mrcRng.right + 4, mrcRng.top, mrcRng.right + 7, mrcRng.bottom };
}


CTri::~CTri()
{
	delete mhp;
}

void CTri::Draw(HDC hdc)
{
	float halfedge = sqrt(3) * TRI_INNERCIRCLERADIUS;
	POINT vertax[3];
	vertax[0] = { (LONG)mptpos.x, (LONG)mptpos.y - 2 * TRI_INNERCIRCLERADIUS };
	vertax[1] = { (LONG)(mptpos.x + halfedge), mrcRng.bottom };
	vertax[2] = { (LONG)(mptpos.x - halfedge), mrcRng.bottom };

	Polygon(hdc, vertax, 3);
}

void CTri::Update()
{
}

INT CTri::GetObjRadius()
{
	return TRI_INNERCIRCLERADIUS;
}
