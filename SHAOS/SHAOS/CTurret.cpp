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
		
		return;
	}

	HBRUSH hTROLDBRUSH = (HBRUSH)SelectObject(hdc, hTRBRUSH);
	RoundRect(hdc, mrcRng.left,mrcRng.top, mrcRng.right,mrcRng.bottom,
		TURRET_RADIUS/5*4, TURRET_RADIUS/5*4);
	SelectObject(hdc, hTROLDBRUSH);
}

void CTurret::Update()
{
	// hp바 업데이트
	mrchpbar.top = mrcRng.bottom - GETHPBAR(mhp->GetHp(), TURRET_RADIUS * 2, TURRET_MAXHP);
	
	// 적이 공격범위 안에 들어왔나 확인



	if (ideatheffecttime) ideatheffecttime -= FRAMETIME;
}

void CTurret::FindTarget()
{

}

void CTurret::Attack()
{
	CGameObject* tmp = nullptr;

	while (tmp != menemylist) {
		if (!tmp) tmp = menemylist;
	
		if (PtInRect(&tmp->GetRng(),(POINT&)tmp->GetPos())) {
			ptarget = tmp;
			return;
		}
		tmp = tmp->next;
	}
	if (!ptarget) return;

	if (pbullet) pbullet = pbullet->Move();
	else pbullet = new Bullet(&mptpos, ptarget, TURRET_BULLETDAMAGE);

	if (ptarget->IsDead()) ptarget = nullptr;
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

