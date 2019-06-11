#include "pch.h"
#include "CTri.h"


CTri::CTri(POINTFLOAT initPos, TEAM team, CGameObject* enemylist)
	: CUnit(initPos, team, enemylist)
{
	mrcRng = { (LONG)mptpos.x - TRI_INNERCIRCLERADIUS, (LONG)mptpos.y - TRI_INNERCIRCLERADIUS,
		(LONG)mptpos.x + TRI_INNERCIRCLERADIUS, (LONG)mptpos.y + TRI_INNERCIRCLERADIUS };
	
	
	mhp = new CHp(TRI_MAXHP);
	mrchpbar = { mrcRng.right + 4, mrcRng.top - TRI_INNERCIRCLERADIUS,
		mrcRng.right + 7, mrcRng.bottom + TRI_INNERCIRCLERADIUS };


	pattacktarget = menemylist->next;

	halfedge = sqrt(3) * TRI_INNERCIRCLERADIUS;
	iattakradius = TRI_INNERCIRCLERADIUS * 2;		//�ܽ��� ������

	iattackcooltime = 0;
}


CTri::~CTri()
{
	delete mhp;
}

void CTri::Draw(HDC hdc)
{
	POINT vertax[3];
	vertax[0] = { (LONG)(mptpos.x - 2 * TRI_INNERCIRCLERADIUS) , (LONG)mptpos.y };
	vertax[1] = { mrcRng.right, (LONG)(mptpos.y - halfedge) };
	vertax[2] = { mrcRng.right, (LONG)(mptpos.y + halfedge) };


	if (ideatheffecttime) {
		// �׾��� �� ����Ʈ
		INT tmp = ideatheffecttime / FRAMETIME;
		if (tmp % 20 > 10) {
			Polygon(hdc, vertax, 3);
		}
		return;
	}

	Polygon(hdc, vertax, 3);

	if (iattackcooltime >= FRAMETIME * 25) {
		// ���� ����Ʈ �׸���
		Ellipse(hdc, mrcRng.left, mrcRng.top, mrcRng.right, mrcRng.bottom);
	}
}

void CTri::SelectedDraw(HDC hdc, HBRUSH hbr)
{
	HBRUSH hOld = (HBRUSH)SelectObject(hdc, hbr);
	POINT vertax[3];
	vertax[0] = { (LONG)(mptpos.x - 2 * TRI_INNERCIRCLERADIUS) - 4 , (LONG)mptpos.y };
	vertax[1] = { mrcRng.right + 2, (LONG)(mptpos.y - halfedge) - 3 };
	vertax[2] = { mrcRng.right + 2, (LONG)(mptpos.y + halfedge) + 3 };

	Polygon(hdc, vertax, 3);
	SelectObject(hdc, hOld);
}

void CTri::Move()
{
	POINTFLOAT movevector;

	// Ÿ�ٰ� �Ÿ� ���ϱ�
	float projX = pattacktarget->GetPos().x - mptpos.x;
	float projY = pattacktarget->GetPos().y - mptpos.y;

	float distance = sqrt(projX * projX + projY * projY);
	INT stopdistance = pattacktarget->GetObjRadius() + iattakradius;

	// movevector ���ϴ� ��
	if (distance > stopdistance) {
		float nomalizedX = projX / distance;
		float nomalizedY = projY / distance;

		movevector = { nomalizedX,nomalizedY };
		attackOn = FALSE;
	}
	else {
		movevector = { 0,0 };
		attackOn = TRUE;
	}

	mptpos.x += movevector.x;
	mptpos.y += movevector.y;

	mrcRng = {
		(LONG)mptpos.x - TRI_INNERCIRCLERADIUS, (LONG)mptpos.y - TRI_INNERCIRCLERADIUS,
		(LONG)mptpos.x + TRI_INNERCIRCLERADIUS, (LONG)mptpos.y + TRI_INNERCIRCLERADIUS
	};



	mrchpbar = { mrcRng.right + 4,
	mrcRng.bottom + TRI_INNERCIRCLERADIUS - (INT)GETHPBAR(mhp->GetHp(), TRI_INNERCIRCLERADIUS * 4, TRI_MAXHP),
	mrcRng.right + 7,
	mrcRng.bottom + TRI_INNERCIRCLERADIUS };

}

void CTri::Attack()
{
	if (!attackOn) return;
	pattacktarget->PutDamage(TRI_ATTACKDAMAGE);
	iattackcooltime = FRAMETIME * 30;
}

void CTri::Update()
{

	if (ideatheffecttime) {
		ideatheffecttime -= FRAMETIME;
		return;
	}

	//Ÿ�� ����
	if (menemylist->next->IsDead()) {
		pattacktarget = menemylist;
	}
	else pattacktarget = menemylist->next;

	Move();

	//����
	if (iattackcooltime)
		iattackcooltime -= FRAMETIME;
	else {

		Attack();

	}

}

INT CTri::GetObjRadius()
{
	return TRI_INNERCIRCLERADIUS;
}
