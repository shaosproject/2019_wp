#include "pch.h"
#include "CTower.h"


CTower::CTower(POINTFLOAT initPos, TEAM team, CGameObject* enemylist)
	: CGameObject(initPos, team, enemylist)
{
	mrcRng = { (LONG)(mptpos.x - TOWER_CENTER2VERTAX),
		(LONG)(mptpos.y - TOWER_CENTER2VERTAX),
		(LONG)(mptpos.x + TOWER_CENTER2VERTAX),
		(LONG)(mptpos.y + TOWER_CENTER2VERTAX)
	};

	// ���� �׸��� �ﰢ��
	triangle1[0] = { (LONG)mptpos.x, (LONG)(mptpos.y + TOWER_CENTER2VERTAX) };
	triangle1[1] = { (LONG)(mptpos.x - TOWER_HALFSIDE),(LONG)(mptpos.y - TOWER_CENTER2SIDE) };
	triangle1[2] = { (LONG)(mptpos.x + TOWER_HALFSIDE),(LONG)(mptpos.y - TOWER_CENTER2SIDE) };
	// ���߿� �׸��� �ﰢ��
	triangle2[0] = { (LONG)mptpos.x, (LONG)(mptpos.y - TOWER_CENTER2VERTAX) };
	triangle2[1] = { (LONG)(mptpos.x - TOWER_HALFSIDE),(LONG)(mptpos.y + TOWER_CENTER2SIDE) };
	triangle2[2] = { (LONG)(mptpos.x + TOWER_HALFSIDE),(LONG)(mptpos.y + TOWER_CENTER2SIDE) };

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
	Ellipse(hdc, mrcRng.left, mrcRng.top, mrcRng.right, mrcRng.bottom);
	Polygon(hdc, triangle1, 3);
	Polygon(hdc, triangle2, 3);

}

INT CTower::GetObjRadius()
{
	// �浹üũ ��� ����.... ����ϴ�
	return 0;
}

void CTower::Death()
{
	// ���� ��~~~
}
