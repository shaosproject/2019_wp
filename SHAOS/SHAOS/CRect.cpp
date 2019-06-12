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
	if (ideatheffecttime) {
		// �׾��� �� ����Ʈ
		INT tmp = ideatheffecttime / FRAMETIME;
		if (tmp % 20 > 10) {
			Rectangle(hdc, mrcRng.left, mrcRng.top,
				mrcRng.right, mrcRng.bottom);
		}
		return;
	}

	if (iattackcooltime >= FRAMETIME * 45) {
		// ���� ����Ʈ (5������)
		float rad = 3.14 / 180;
		float cos75 = cos(rad * 75);
		float sin75 = sin(rad * 75);
		float Cos = RECT_RADIUS * cos75 * 1.4;
		float Sin = RECT_RADIUS * sin75 * 1.4;
		POINT rectpoint[4] = { 0 };
		
		switch (iattackcooltime) {
		case FRAMETIME * 50:
		case FRAMETIME * 49:
			rectpoint[0] = { (LONG)(mptpos.x + Sin),(LONG)(mptpos.y + Cos) };
			rectpoint[1] = { (LONG)(mptpos.x + Cos),(LONG)(mptpos.y - Sin) };
			rectpoint[2] = { (LONG)(mptpos.x - Sin),(LONG)(mptpos.y - Cos) };
			rectpoint[3] = { (LONG)(mptpos.x - Cos),(LONG)(mptpos.y + Sin) };
			break;
		case FRAMETIME * 48:
		case FRAMETIME * 47:
			rectpoint[0] = { (LONG)(mptpos.x + RECT_RADIUS * 1.4),(LONG)mptpos.y };
			rectpoint[1] = { (LONG)mptpos.x,(LONG)(mptpos.y - RECT_RADIUS * 1.4) };
			rectpoint[2] = { (LONG)(mptpos.x - RECT_RADIUS * 1.4),(LONG)mptpos.y };
			rectpoint[3] = { (LONG)mptpos.x,(LONG)(mptpos.y + RECT_RADIUS * 1.4) };
			break;
		case FRAMETIME * 46:
		case FRAMETIME * 45:
			rectpoint[0] = { (LONG)(mptpos.x + Cos),(LONG)(mptpos.y + Sin) };
			rectpoint[1] = { (LONG)(mptpos.x + Sin),(LONG)(mptpos.y - Cos) };
			rectpoint[2] = { (LONG)(mptpos.x - Cos),(LONG)(mptpos.y - Sin) };
			rectpoint[3] = { (LONG)(mptpos.x - Sin),(LONG)(mptpos.y + Cos) };
			break;
		}
		
		Polygon(hdc, rectpoint, 4);
	}

	else Rectangle(hdc, mrcRng.left, mrcRng.top, mrcRng.right, mrcRng.bottom);
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
	else Attack();



}

void CRect::Move()
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

		if (tmp->IsDead()) {
			tmp = tmp->next;
			continue;
		}

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

	iattackcooltime = FRAMETIME * 50;
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

		INT range = UNIT_RECOGRNGRADIUS + RECT_RADIUS;
		if (IsInRange(this, tmp, range)) {
			pattacktarget = tmp;
		}

		tmp = tmp->next;
	}

}

INT CRect::GetObjRadius()
{
	return RECT_RADIUS;
}
