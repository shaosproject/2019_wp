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

	pattacktarget = menemylist;
}

CRect::~CRect()
{
	delete mhp;
}

void CRect::Draw(HDC hdc)
{
	Rectangle(hdc, mrcRng.left, mrcRng.top,
		mrcRng.right, mrcRng.bottom);
}

void CRect::SelectedDraw(HDC hdc)
{
	HBRUSH hOld = (HBRUSH)SelectObject(hdc, hSELECTEDBRUSH);
	Rectangle(hdc, mrcRng.left - 2, mrcRng.top - 2,
		mrcRng.right + 2, mrcRng.bottom + 2);
	SelectObject(hdc, hOld);
}

void CRect::Update()
{
	// 공격할 대상 정하기
	SetTarget();

	if (moveOn) Move();


}

void CRect::Move()
{

	float projX = pattacktarget->GetPos().x - mptpos.x;
	float projY = pattacktarget->GetPos().y - mptpos.y;
	
	
	float distance = sqrt(projX * projX + projY * projY);

	if (distance < 100) moveOn = FALSE;	// 적절한 범위에서 멈추기

	float nomalizedX = projX / distance;
	float nomalizedY = projY / distance;

	POINTFLOAT movevector = { nomalizedX * UNIT_SPEED,nomalizedY * UNIT_SPEED };


	// 공격 대상을 향해서 이동
	mptpos.x += movevector.x;
	mptpos.y += movevector.y;



	// 영역 이동
	mrcRng = {
		(LONG)mptpos.x - RECT_RADIUS, (LONG)mptpos.y - RECT_RADIUS,
		(LONG)mptpos.x + RECT_RADIUS, (LONG)mptpos.y + RECT_RADIUS
	};

	//hp바 이동

	if (team == TEAM::USER) {
		mrchpbar = { mrcRng.left - 7, mrcRng.top, mrcRng.left - 4, mrcRng.bottom };
	}
	else {
		mrchpbar = { mrcRng.right + 4, mrcRng.top, mrcRng.right + 7, mrcRng.bottom };
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
		}

		tmp = tmp->next;
	}
}

void CRect::SetTarget()
{
	CGameObject* tmp = nullptr;
	while (tmp != menemylist) {
		if (!tmp) tmp = menemylist;
		//UNIT_RECOGRNGRADIUS

		float projX = tmp->GetPos().x - mptpos.x;
		float projY = tmp->GetPos().y - mptpos.y;

		float distance = sqrt(projX * projX + projY * projY);

		if (distance < UNIT_RECOGRNGRADIUS) {
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
