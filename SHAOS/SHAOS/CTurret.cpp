#include "pch.h"
#include "CTurret.h"
#include "Bullet.h"

CTurret::CTurret(POINTFLOAT initPos, TEAM team, CGameObject* enemylist)
	: CGameObject(initPos, team, enemylist)
{
	mrcRng = { (LONG)initPos.x - TURRET_RADIUS ,(LONG)initPos.y - TURRET_RADIUS,
		(LONG)initPos.x + TURRET_RADIUS, (LONG)initPos.y + TURRET_RADIUS };


	mhp = new CHp(TURRET_MAXHP);
	mrchpbar = { mrcRng.right + 4, mrcRng.top, mrcRng.right + 7, mrcRng.bottom };

	iattackcooltime = 0;
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

	if (ideatheffecttime) {
		// ���� ����Ʈ �׸���
		// Ÿ���� ���� ������� ���ϸ鼭 
		//RoundRect(hdc, mrcRng.left, mrcRng.top, mrcRng.right, mrcRng.bottom,
		//	TURRET_RADIUS / 5 * 4, TURRET_RADIUS / 5 * 4);


		INT tmp1 = ideatheffecttime / FRAMETIME;
		INT tmp2 = TURRET_EFFECTTIME_DEATH / FRAMETIME;

		INT d = (INT)(TURRET_RADIUS/2 * tmp1 / tmp2);
		if (tmp1 % 20>=0&&tmp1%20<4)
			Ellipse(hdc, (mptpos.x-35)-d, (mptpos.y - 35)-d, (mptpos.x - 35)+d, (mptpos.y - 35)+d);
		if (tmp1 % 20 >=4&&tmp1 % 20 < 8)
		Ellipse(hdc, (mptpos.x + 35) - d, (mptpos.y - 35) - d, (mptpos.x + 35) + d, (mptpos.y - 35) + d);
		if (tmp1 % 20 >= 8 && tmp1 % 20 < 12)
		Ellipse(hdc, (mptpos.x + 35) - d, (mptpos.y +35) - d, (mptpos.x + 35) + d, (mptpos.y + 35) + d);
		if (tmp1 % 20 >= 12 && tmp1 % 20 < 16)
		Ellipse(hdc, (mptpos.x - 35) - d, (mptpos.y + 35) - d, (mptpos.x - 35) + d, (mptpos.y + 35) + d);		
		if (tmp1 % 20 >= 16 && tmp1 % 20 <20 )
		Ellipse(hdc, mptpos.x  - d, mptpos.y  - d,mptpos.x  + d, mptpos.y  + d);



		return;
	}

	
	HBRUSH hOld = (HBRUSH)SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
	HPEN hOldpen;
	(ptarget == menemylist->next) ? 
		hOldpen = (HPEN)SelectObject(hdc, hREDPEN)
		: hOldpen = (HPEN)SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));

	// ���� ���� �׸���...
	Ellipse(hdc, mptpos.x - TURRET_ATTACK_RANGE, mptpos.y - TURRET_ATTACK_RANGE,
		mptpos.x + TURRET_ATTACK_RANGE, mptpos.y + TURRET_ATTACK_RANGE);

	SelectObject(hdc, hOldpen);

	SelectObject(hdc, hTRBRUSH);
	RoundRect(hdc, mrcRng.left,mrcRng.top, mrcRng.right,mrcRng.bottom,
		TURRET_RADIUS/5*4, TURRET_RADIUS/5*4);
	SelectObject(hdc, hOld);


	if (pbullet) pbullet->Draw(hdc);
}

void CTurret::Update()
{
	if (mdeath) {
		if(ideatheffecttime > FRAMETIME) ideatheffecttime -= FRAMETIME;
		return;
	}

	// hp�� ������Ʈ
	mrchpbar.top = mrcRng.bottom - GETHPBAR(mhp->GetHp(), TURRET_RADIUS * 2, TURRET_MAXHP);


	ptarget = FindTarget();
	if (ptarget == nullptr) {
		iattackcooltime = 0;
	}

	if (!iattackcooltime) {
		if (ptarget && !pbullet) {
			Attack();
			iattackcooltime = FRAMETIME * 100;
		}
	}
	else {
		iattackcooltime -= FRAMETIME;
	}

	if (pbullet) pbullet = pbullet->Move();


}

CGameObject* CTurret::FindTarget()
{
	// ���� ������ ���� ���� �����ϴ� �˰���
	CGameObject* tmp = menemylist->next->next;	//���� ���� �˻�
	while (tmp != menemylist) {
		if (tmp->IsDead()) {
			tmp = tmp->next;
			continue;
		}

		INT range = TURRET_ATTACK_RANGE + tmp->GetObjRadius();
		if (IsInRange(this, tmp, range)) {
			return tmp;					// ���� �Ƶ� Ÿ���� ������ ����
		}
		tmp = tmp->next;
	}

	INT range = TURRET_ATTACK_RANGE + PLAYER_RADIUS;
	if (IsInRange(this, menemylist->next, range)) {
		return menemylist->next;
	}

	return nullptr;
}




void CTurret::Attack()
{
	if (ptarget == menemylist->next) // �÷��̾��̸�
	{
		pbullet = new Bullet(&mptpos, ptarget, TURRET_BULLETDAMAGE*4);
	}
	else pbullet = new Bullet(&mptpos, ptarget, TURRET_BULLETDAMAGE);
}

void CTurret::SelectedDraw(HDC hdc, HBRUSH hbr)
{
	HBRUSH hOld = (HBRUSH)SelectObject(hdc, hbr);

	RoundRect(hdc, mrcRng.left - 3, mrcRng.top - 3,
		mrcRng.right + 4, mrcRng.bottom + 4,
		TURRET_RADIUS / 5 * 3, TURRET_RADIUS / 5 * 3);

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

