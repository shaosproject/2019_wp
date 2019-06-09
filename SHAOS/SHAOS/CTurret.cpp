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
		// 죽음 이펙트 그리기
		
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
	// hp바 업데이트
	mrchpbar.top = mrcRng.bottom - GETHPBAR(mhp->GetHp(), TURRET_RADIUS * 2, TURRET_MAXHP);
	


	// 공격 -> 쿨타임 설정하는거 마음에 안 든다....
	ptarget = FindTarget();
	if (iattackcooltime) {
		iattackcooltime -= FRAMETIME;
		if (!iattackcooltime) {
			if (ptarget && !pbullet) Attack();	// 총알 만들기
			iattackcooltime = FRAMETIME * 100;
		}
	}
	if (pbullet) pbullet = pbullet->Move();


	if (ideatheffecttime) ideatheffecttime -= FRAMETIME;
}

CGameObject* CTurret::FindTarget()
{
	// 먼저 생성된 유닛 먼저 공격하는 알고리즘
	CGameObject* tmp = menemylist->next;	//유닛 먼저 검사
	while (tmp != menemylist) {
		if (tmp->IsDead()) {
			tmp = tmp->next;
			continue;
		}

		INT range = TOWER_ATTACK_RANGE + tmp->GetObjRadius();
		if (IsInRange(this, tmp, range)) {
			return tmp;					// 뭐가 됐든 타겟이 있으면 리턴
		}
		tmp = tmp->next;
	}

	//tmp = menemylist->next;				// 플레이어 검사
	//INT range = TOWER_ATTACK_RANGE + PLAYER_RADIUS;
	//if (IsInRange(this, tmp, range)) {
	//	ptarget = tmp;
	//	return TRUE;
	//}

	return nullptr;
}




void CTurret::Attack()
{
	if (ptarget == menemylist->next) // 플레이어이면
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

