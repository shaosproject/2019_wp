#include "pch.h"
#include "CRect.h"
#include "CHp.h"

CRect::CRect(POINTFLOAT ainitPos, TEAM team, CGameObject* enemylist)
	: CUnit(ainitPos, team, enemylist)
{
	mrcRng = { (LONG)mptpos.x - RECT_RADIUS, (LONG)mptpos.y - RECT_RADIUS,
		(LONG)mptpos.x + RECT_RADIUS, (LONG)mptpos.y + RECT_RADIUS };

	mhp = new CHp(RECT_MAXHP);
	if (team == TEAM::USER) {
		mrchpbar = { mrcRng.left - 7, mrcRng.top, mrcRng.left - 4, mrcRng.bottom };
	}
	else {
		mrchpbar = { mrcRng.right + 4, mrcRng.top, mrcRng.right + 7, mrcRng.bottom };
	}

	iattackcooltime = FRAMETIME * 50;

	pattacktarget = menemylist;
	ideatheffecttime = 0;
}

CRect::~CRect()
{
	delete mhp;
}

void CRect::Draw(HDC hdc)
{
	if (iattackcooltime >= FRAMETIME * 45) {
		// ���� ����Ʈ (5������)
		Ellipse(hdc, mptpos.x - iattakradius, mptpos.y - iattakradius,
			mptpos.x + iattakradius, mptpos.y + iattakradius);
	}


	Rectangle(hdc, mrcRng.left, mrcRng.top,
		mrcRng.right, mrcRng.bottom);

	if (mdeath) {
		// �׾��� �� ����Ʈ
		Ellipse(hdc, mrcRng.left, mrcRng.top,
			mrcRng.right, mrcRng.bottom);
	}
}

void CRect::SelectedDraw(HDC hdc, HBRUSH hbr)
{
	HBRUSH hOld = (HBRUSH)SelectObject(hdc, hbr);
	Rectangle(hdc, mrcRng.left - 2, mrcRng.top - 2,
		mrcRng.right + 2, mrcRng.bottom + 2);
	SelectObject(hdc, hOld);
}

void CRect::Update()
{
	// ����
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


	if(iattackcooltime)
		iattackcooltime -= FRAMETIME;
	else {
		Attack();
		iattackcooltime = FRAMETIME * 50;
	}



}

void CRect::Move()
{

	float projX = pattacktarget->GetPos().x - mptpos.x;
	float projY = pattacktarget->GetPos().y - mptpos.y;
	
	
	float distance = sqrt(projX * projX + projY * projY);

	(distance < pattacktarget->GetObjRadius() + iattakradius) ? moveOn = FALSE : moveOn = TRUE;	// ������ �������� ���߱�

	if (!moveOn) return;

	float nomalizedX = projX / distance;
	float nomalizedY = projY / distance;

	POINTFLOAT movevector = { nomalizedX * UNIT_SPEED,nomalizedY * UNIT_SPEED };


	// ���� ����� ���ؼ� �̵�
	mptpos.x += movevector.x;
	mptpos.y += movevector.y;



	// ���� �̵�
	mrcRng = {
		(LONG)mptpos.x - RECT_RADIUS, (LONG)mptpos.y - RECT_RADIUS,
		(LONG)mptpos.x + RECT_RADIUS, (LONG)mptpos.y + RECT_RADIUS
	};

	//hp�� �̵�

	if (team == TEAM::USER) {
		mrchpbar = {
			mrcRng.left - 7,
			mrcRng.bottom - (INT)GETHPBAR(mhp->GetHp(), RECT_RADIUS * 2, RECT_MAXHP),
			mrcRng.left - 4,
			mrcRng.bottom
		};
	}
	else {
		mrchpbar = { mrcRng.right + 4,
			mrcRng.bottom - (INT)GETHPBAR(mhp->GetHp(), RECT_RADIUS * 2, RECT_MAXHP),
			mrcRng.right + 7,
			mrcRng.bottom };
	}


}

void CRect::Attack()
{
	CGameObject* tmp = nullptr;
	while (tmp != menemylist) {
		if (!tmp) tmp = menemylist;

		float dx = mptpos.x - tmp->GetPos().x;
		float dy = mptpos.y - tmp->GetPos().y;

		float center_d = dx * dx + dy * dy;
		float range = iattakradius + tmp->GetObjRadius();
		if (center_d <= range * range) {
			tmp->PutDamage(RECT_DAMAGE);
			if (tmp->IsDead()) {
				pattacktarget = menemylist;
			}
		}

		tmp = tmp->next;
	}
}

void CRect::SetTarget()
{
	CGameObject* tmp = nullptr;
	while (tmp != menemylist) {
		if (!tmp) tmp = menemylist;

		//�׾����� Ÿ���� �� �� ����
		if (tmp->IsDead()) {
			tmp = tmp->next;
			continue;
		}

		float projX = tmp->GetPos().x - mptpos.x;
		float projY = tmp->GetPos().y - mptpos.y;

		float distance = sqrt(projX * projX + projY * projY);

		if (distance <= UNIT_RECOGRNGRADIUS + RECT_RADIUS) {
			pattacktarget = tmp;
			return;
		}

		tmp = tmp->next;
	}


}

INT CRect::GetObjRadius()
{
	return RECT_RADIUS;
}

void CRect::Death()
{
	ideatheffecttime = RECT_EFFECTTIME_DEATH;
}
