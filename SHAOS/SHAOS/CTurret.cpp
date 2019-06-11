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
		// 죽음 이펙트 그리기
		// 타워의 색이 흰색으로 변하면서 
		RoundRect(hdc, mrcRng.left, mrcRng.top, mrcRng.right, mrcRng.bottom,
			TURRET_RADIUS / 5 * 4, TURRET_RADIUS / 5 * 4);


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

	// 공격 범위 그리기...
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

	// hp바 업데이트
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
	// 먼저 생성된 유닛 먼저 공격하는 알고리즘
	CGameObject* tmp = menemylist->next->next;	//유닛 먼저 검사
	while (tmp != menemylist) {
		if (tmp->IsDead()) {
			tmp = tmp->next;
			continue;
		}

		INT range = TURRET_ATTACK_RANGE + tmp->GetObjRadius();
		if (IsInRange(this, tmp, range)) {
			return tmp;					// 뭐가 됐든 타겟이 있으면 리턴
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

