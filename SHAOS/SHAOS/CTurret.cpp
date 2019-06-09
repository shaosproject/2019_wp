#include "pch.h"
#include "CTurret.h"
#include "Bullet.h"

CTurret::CTurret(POINTFLOAT initPos, TEAM team, CGameObject* enemylist)
	: CGameObject(initPos, team, enemylist)
{
	mrcRng = { (LONG)initPos.x - TURRET_RADIUS ,(LONG)initPos.y - TURRET_RADIUS,
		(LONG)initPos.x + TURRET_RADIUS, (LONG)initPos.y + TURRET_RADIUS };


	mhp = new CHp(TOWER_MAXHP);
	mrchpbar = { mrcRng.right + 4, mrcRng.top, mrcRng.right + 7, mrcRng.bottom };

	iattackcooltime = FRAMETIME * 100;
	ptarget = nullptr;
	pbullet = nullptr;

	ideatheffecttime = 0;
}


CTurret::~CTurret()
{
	delete mhp;
	if (pbullet) delete pbullet;
}

void CTurret::Draw(HDC hdc)
{
	Ellipse(hdc, mptpos.x - TOWER_ATTACK_RANGE, mptpos.y - TOWER_ATTACK_RANGE,
		mptpos.x + TOWER_ATTACK_RANGE, mptpos.y + TOWER_ATTACK_RANGE);

	if (ideatheffecttime) {
		// ���� ����Ʈ �׸���
		
		return;
	}

	HBRUSH hTROLDBRUSH = (HBRUSH)SelectObject(hdc, hTRBRUSH);
	RoundRect(hdc, mrcRng.left,mrcRng.top, mrcRng.right,mrcRng.bottom,
		TURRET_RADIUS/5*4, TURRET_RADIUS/5*4);
	SelectObject(hdc, hTROLDBRUSH);

	if (pbullet) pbullet->Draw(hdc);
}

void CTurret::Update()
{
	// hp�� ������Ʈ
	mrchpbar.top = mrcRng.bottom - GETHPBAR(mhp->GetHp(), TURRET_RADIUS * 2, TURRET_MAXHP);
	


	// ���� -> ��Ÿ�� �����ϴ°� ������ �� ���....
	ptarget = FindTarget();
	if (iattackcooltime) {
		iattackcooltime -= FRAMETIME;
		if (!iattackcooltime) {
			if (ptarget && !pbullet) Attack();	// �Ѿ� �����
			iattackcooltime = FRAMETIME * 100;
		}
	}
	if (pbullet) pbullet = pbullet->Move();


	if (ideatheffecttime) ideatheffecttime -= FRAMETIME;
}

CGameObject* CTurret::FindTarget()
{
	// ���� ������ ���� ���� �����ϴ� �˰���
	CGameObject* tmp = menemylist->next;	//���� ���� �˻�
	while (tmp != menemylist) {
		if (tmp->IsDead()) {
			tmp = tmp->next;
			continue;
		}

		INT range = TOWER_ATTACK_RANGE + tmp->GetObjRadius();
		if (IsInRange(this, tmp, range)) {
			return tmp;					// ���� �Ƶ� Ÿ���� ������ ����
		}
		tmp = tmp->next;
	}

	//tmp = menemylist->next;				// �÷��̾� �˻�
	//INT range = TOWER_ATTACK_RANGE + PLAYER_RADIUS;
	//if (IsInRange(this, tmp, range)) {
	//	ptarget = tmp;
	//	return TRUE;
	//}

	return nullptr;
}




void CTurret::Attack()
{
	if (ptarget == menemylist->next) // �÷��̾��̸�
	{
		pbullet = new Bullet(&mptpos, ptarget, TURRET_BULLETDAMAGE*5);
	}
	else pbullet = new Bullet(&mptpos, ptarget, TURRET_BULLETDAMAGE);
}

void CTurret::SelectedDraw(HDC hdc, HBRUSH hbr)
{
	HBRUSH hOld = (HBRUSH)SelectObject(hdc, hbr);

	RoundRect(hdc, mrcRng.left - 4, mrcRng.top - 4,
		mrcRng.right + 4, mrcRng.bottom + 4,
		TURRET_RADIUS / 5 * 4, TURRET_RADIUS / 5 * 4);

	SelectObject(hdc, hOld);
}

INT CTurret::GetObjRadius()
{
	return TURRET_RADIUS;
}

void CTurret::Death()
{
	ideatheffecttime = TURRET_EFFECTTIME_DEATH;
}

