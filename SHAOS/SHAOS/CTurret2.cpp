#include "pch.h"
#include "CTurret2.h"


CTurret2::CTurret2(POINTFLOAT initPos, TEAM team, CGameObject* enemylist)
	: CGameObject(initPos, team, enemylist)
{
	mrcRng = { (LONG)initPos.x - TURRET_RADIUS ,(LONG)initPos.y - TURRET_RADIUS,
	(LONG)initPos.x + TURRET_RADIUS, (LONG)initPos.y + TURRET_RADIUS };


	mhp = new CHp(TOWER_MAXHP);
	mrchpbar = { mrcRng.right + 4, mrcRng.top, mrcRng.right + 7, mrcRng.bottom };


	iattackcooltime = 0;
	ideatheffecttime = 0;

	attackOn = FALSE;
	ptarget = nullptr;
	attakpoint = { 0,0 };

}


CTurret2::~CTurret2()
{
	delete mhp;
}

void CTurret2::Draw(HDC hdc)
{
	if (ideatheffecttime) {
		// ���� ����Ʈ �׸���
		// Ÿ���� ���� ������� ���ϸ鼭 
		RoundRect(hdc, mrcRng.left, mrcRng.top, mrcRng.right, mrcRng.bottom,
			TURRET_RADIUS / 5 * 4, TURRET_RADIUS / 5 * 4);


		INT tmp1 = ideatheffecttime / FRAMETIME;
		INT tmp2 = TURRET_EFFECTTIME_DEATH / FRAMETIME;

		INT d = (INT)(TURRET_RADIUS / 2 * tmp1 / tmp2);
		if (tmp1 % 20 >= 0 && tmp1 % 20 < 4)
			Ellipse(hdc, (mptpos.x - 35) - d, (mptpos.y - 35) - d, (mptpos.x - 35) + d, (mptpos.y - 35) + d);
		if (tmp1 % 20 >= 4 && tmp1 % 20 < 8)
			Ellipse(hdc, (mptpos.x + 35) - d, (mptpos.y - 35) - d, (mptpos.x + 35) + d, (mptpos.y - 35) + d);
		if (tmp1 % 20 >= 8 && tmp1 % 20 < 12)
			Ellipse(hdc, (mptpos.x + 35) - d, (mptpos.y + 35) - d, (mptpos.x + 35) + d, (mptpos.y + 35) + d);
		if (tmp1 % 20 >= 12 && tmp1 % 20 < 16)
			Ellipse(hdc, (mptpos.x - 35) - d, (mptpos.y + 35) - d, (mptpos.x - 35) + d, (mptpos.y + 35) + d);
		if (tmp1 % 20 >= 16 && tmp1 % 20 < 20)
			Ellipse(hdc, mptpos.x - d, mptpos.y - d, mptpos.x + d, mptpos.y + d);



		return;
	}


	HBRUSH hOld = (HBRUSH)SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
	HPEN hOldpen;
	(ptarget == menemylist->next) ?
		hOldpen = (HPEN)SelectObject(hdc, hREDPEN)
		: hOldpen = (HPEN)SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));

	Ellipse(hdc, mptpos.x - TURRET_ATTACK_RANGE, mptpos.y - TURRET_ATTACK_RANGE,
		mptpos.x + TURRET_ATTACK_RANGE, mptpos.y + TURRET_ATTACK_RANGE);

	SelectObject(hdc, hOldpen);

	SelectObject(hdc, hTRBRUSH);
	RoundRect(hdc, mrcRng.left, mrcRng.top, mrcRng.right, mrcRng.bottom,
		TURRET_RADIUS / 5 * 4, TURRET_RADIUS / 5 * 4);
	SelectObject(hdc, hOld);

	if (attackOn) {

		// ���� ����Ʈ �׸���
		Ellipse(hdc, mptpos.x - 10, mptpos.y - 10,
			mptpos.x + 10, mptpos.y + 10);


	}
}

void CTurret2::Update()
{
	if (mdeath) {
		if (ideatheffecttime > FRAMETIME) ideatheffecttime -= FRAMETIME;
		return;
	}
	mrchpbar.top = mrcRng.bottom - GETHPBAR(mhp->GetHp(), TURRET_RADIUS * 2, TURRET_MAXHP);

	// Ÿ�� ã��
	ptarget = FindTarget();

	if (ptarget && !attackOn) {
		AttackStart();
	}
	if (iattackcooltime) {
		iattackcooltime -= FRAMETIME;
		if (!iattackcooltime) {
			AttackEnd();
		}
	}

}

CGameObject* CTurret2::FindTarget()
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

void CTurret2::AttackStart()
{
	attackOn = TRUE;
	iattackcooltime = FRAMETIME * 100;
	if (ptarget == menemylist->next) {
		attackdamage = 50;
	}
	else attackdamage = 20;

	attakpoint = ptarget->GetPos();
}

void CTurret2::AttackEnd()
{
	attackOn = FALSE;

	// ������ �ֱ�
	CGameObject* tmp = menemylist->next;
	while (tmp != menemylist) {

		if (tmp->IsDead()) {
			tmp = tmp->next;
			continue;
		}

		float dx = attakpoint.x - tmp->GetPos().x;
		float dy = attakpoint.y - tmp->GetPos().y;

		float center_d = dx * dx + dy * dy;
		float range = TURRET2_ATTAKRANGE + tmp->GetObjRadius();

		if (center_d <= range * range) {
			tmp->PutDamage(attackdamage);
		}

		tmp = tmp->next;
	}

}



void CTurret2::SelectedDraw(HDC hdc, HBRUSH hbr)
{
	HBRUSH hOld = (HBRUSH)SelectObject(hdc, hbr);

	RoundRect(hdc, mrcRng.left - 4, mrcRng.top - 4,
		mrcRng.right + 4, mrcRng.bottom + 4,
		TURRET_RADIUS / 5 * 4, TURRET_RADIUS / 5 * 4);

	SelectObject(hdc, hOld);

}

INT CTurret2::GetObjRadius()
{
	return TURRET_RADIUS;
}

void CTurret2::Death()
{
	ideatheffecttime = TURRET_EFFECTTIME_DEATH;

}
