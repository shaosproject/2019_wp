#include "pch.h"
#include "CEllip.h"
#include "Bullet.h"

CEllip::CEllip(POINTFLOAT initPos, TEAM team, CGameObject* enemylist)
	: CUnit(initPos, team, enemylist)
{
	mrcRng = { (LONG)mptpos.x - ELLIP_RADIUS, (LONG)mptpos.y - ELLIP_RADIUS,
		(LONG)mptpos.x + ELLIP_RADIUS, (LONG)mptpos.y + ELLIP_RADIUS };

	mhp = new CHp(ELLIP_MAXHP);
	if (team == TEAM::USER) {
		mrchpbar = { mrcRng.left - 7, mrcRng.top, mrcRng.left - 4, mrcRng.bottom };
	}
	else {
		mrchpbar = { mrcRng.right + 4, mrcRng.top, mrcRng.right + 7, mrcRng.bottom };
	}

	iattackcooltime = 0;
	pattacktarget = menemylist;

	ideatheffecttime = 0;
}


CEllip::~CEllip()
{
	delete mhp;
}

void CEllip::Draw(HDC hdc)
{
	Ellipse(hdc, mptpos.x - iattakradius, mptpos.y - iattakradius,
		mptpos.x + iattakradius, mptpos.y+- iattakradius);



	if (ideatheffecttime) {
		// �׾��� �� ����Ʈ
		INT tmp = ideatheffecttime / FRAMETIME;
		if (tmp % 20 > 10) {
			Ellipse(hdc, mrcRng.left, mrcRng.top,
				mrcRng.right, mrcRng.bottom);
		}
		return;
	}


	Ellipse(hdc, mrcRng.left, mrcRng.top,
		mrcRng.right, mrcRng.bottom);

	if (pbullet) pbullet->Draw(hdc);
}

void CEllip::SelectedDraw(HDC hdc, HBRUSH hbr)
{
	HBRUSH hOld = (HBRUSH)SelectObject(hdc, hbr);
	Ellipse(hdc, mrcRng.left - 2, mrcRng.top - 2,
		mrcRng.right + 2, mrcRng.bottom + 2);
	SelectObject(hdc, hOld);
}

void CEllip::Update()
{
	if (ideatheffecttime) {
		ideatheffecttime -= FRAMETIME;
		return;
	}

	// ������ ��� ���ϱ�
	SetTarget();
	if (pattacktarget->IsDead()) {
		pattacktarget = menemylist;
	}

	
	Move();


	if (iattackcooltime)
		iattackcooltime -= FRAMETIME;
	else {
		if (Attack())
			iattackcooltime = FRAMETIME * 50;
	}
	if (pbullet) pbullet = pbullet->Move();


}

void CEllip::Move()
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
	}
	else movevector = { 0,0 };


	mptpos.x += movevector.x;
	mptpos.y += movevector.y;

	mrcRng = {
	(LONG)mptpos.x - ELLIP_RADIUS, (LONG)mptpos.y - ELLIP_RADIUS,
	(LONG)mptpos.x + ELLIP_RADIUS, (LONG)mptpos.y + ELLIP_RADIUS
	};

	//hp�� �̵�
	if (team == TEAM::USER) {
		mrchpbar = {
			mrcRng.left - 7,
			mrcRng.bottom - (INT)GETHPBAR(mhp->GetHp(), ELLIP_RADIUS * 2, ELLIP_MAXHP),
			mrcRng.left - 4,
			mrcRng.bottom
		};
	}
	else {
		mrchpbar = { mrcRng.right + 4,
			mrcRng.bottom - (INT)GETHPBAR(mhp->GetHp(), ELLIP_RADIUS * 2, ELLIP_MAXHP),
			mrcRng.right + 7,
			mrcRng.bottom };
	}


}

BOOL CEllip::Attack()
{
	// Ÿ�ٰ��� �Ÿ��� ���ݹ��� �̳��� ���� 
	INT range = pattacktarget->GetObjRadius() + iattakradius;
	if (IsInRange(this, pattacktarget, range)) {
		pbullet = new Bullet(&mptpos, pattacktarget, ELLIP_BULLETDAMAGE);
		return TRUE;
	}
	return FALSE;

}

void CEllip::SetTarget()
{
	CGameObject* tmp = nullptr;
	while (tmp != menemylist) {
		if (!tmp) tmp = menemylist;

		//�׾����� Ÿ���� �� �� ����
		if (tmp->IsDead()) {
			tmp = tmp->next;
			continue;
		}

		INT range = UNIT_RECOGRNGRADIUS + RECT_RADIUS;
		if (IsInRange(this, tmp, range)) {
			pattacktarget = tmp;
		}

		tmp = tmp->next;
	}

}

INT CEllip::GetObjRadius()
{
	return ELLIP_RADIUS;
}
