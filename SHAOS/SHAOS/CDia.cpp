#include "pch.h"
#include "CDia.h"


CDia::CDia(POINTFLOAT initPos, TEAM team, CGameObject* enemylist)
	: CUnit(initPos, team, enemylist)
{
	mrcRng = { (LONG)mptpos.x - DIA_SHORTRADIUS, (LONG)mptpos.y - DIA_SHORTRADIUS,
	(LONG)mptpos.x + DIA_SHORTRADIUS, (LONG)mptpos.y + DIA_SHORTRADIUS };

	mhp = new CHp(DIA_MAXHP);
	mrchpbar = { mrcRng.right + 12, mrcRng.top, mrcRng.right + 15, mrcRng.bottom };

	pattacktarget = menemylist;	// Ÿ���� ����� Ÿ��

	iattackcooltime = 0;
	ideatheffecttime = 0;
}


CDia::~CDia()
{
	delete mhp;
}

void CDia::Draw(HDC hdc)
{
	if (ideatheffecttime) {
		//���� ����Ʈ
		INT tmp = ideatheffecttime / FRAMETIME;
		if (tmp % 20 > 10) {
			POINT vertax[4];
			vertax[0] = { (LONG)mptpos.x, mrcRng.top };
			vertax[1] = { mrcRng.right + 10, (LONG)mptpos.y };
			vertax[2] = { (LONG)mptpos.x, mrcRng.bottom };
			vertax[3] = { mrcRng.left - 10, (LONG)mptpos.y };

			Polygon(hdc, vertax, 4);
		}
		return;
	}


	POINT vertax[4];
	vertax[0] = { (LONG)mptpos.x, mrcRng.top };
	vertax[1] = { mrcRng.right + 10, (LONG)mptpos.y };
	vertax[2] = { (LONG)mptpos.x, mrcRng.bottom };
	vertax[3] = { mrcRng.left - 10, (LONG)mptpos.y };

	Polygon(hdc, vertax, 4);

	if (iattackcooltime >= FRAMETIME * 45) {
		// ���� ����Ʈ
		Rectangle(hdc, mptpos.x - 5, mptpos.y - 5,
			mptpos.x + 5, mptpos.y + 5);
	}

}

void CDia::SelectedDraw(HDC hdc, HBRUSH hbr)
{
	POINT vertax[4];
	vertax[0] = { (LONG)mptpos.x, mrcRng.top - 3 };
	vertax[1] = { mrcRng.right + 13, (LONG)mptpos.y };
	vertax[2] = { (LONG)mptpos.x, mrcRng.bottom + 3 };
	vertax[3] = { mrcRng.left - 13, (LONG)mptpos.y };


	HBRUSH hOld = (HBRUSH)SelectObject(hdc, hbr);
	Polygon(hdc, vertax, 4);
	SelectObject(hdc, hOld);
}

void CDia::Move()
{
	POINTFLOAT movevector;
	if (mptpos.x > MAPSIZE_WIDTH / 2) {
		movevector = { -DIA_SPEED,0 };
	}
	else if (mptpos.x > MAPSIZE_WIDTH/6 && mptpos.x <= MAPSIZE_WIDTH / 2) {
		float movey;
		if (mptpos.y > MAPSIZE_HEIGHT / 2 && mptpos.y < MAPSIZE_HEIGHT - 50) movey = 1;
		else if(mptpos.y < MAPSIZE_HEIGHT / 2 && mptpos.y > 50) movey = -DIA_SPEED;
		else movey = 0;
		movevector = { -DIA_SPEED, movey };
	}
	else {
		float projX = pattacktarget->GetPos().x - mptpos.x;
		float projY = pattacktarget->GetPos().y - mptpos.y;
	
	
		float distance = sqrt(projX * projX + projY * projY);
	
		(distance < pattacktarget->GetObjRadius() + DIA_SHORTRADIUS) 
			? moveOn = FALSE : moveOn = TRUE;	// ������ �������� ���߱�
	
		if (!moveOn) {
			movevector = { 0,0 };
			if (!attackOn) attackOn = TRUE;
		}
		else {
			float nomalizedX = projX / distance;
			float nomalizedY = projY / distance;

			movevector = { nomalizedX * DIA_SPEED,nomalizedY * DIA_SPEED };
		}
	}

	// ���� ����� ���ؼ� �̵�
	mptpos.x += movevector.x;
	mptpos.y += movevector.y;

	mrcRng = { (LONG)mptpos.x - DIA_SHORTRADIUS, (LONG)mptpos.y - DIA_SHORTRADIUS,
	(LONG)mptpos.x + DIA_SHORTRADIUS, (LONG)mptpos.y + DIA_SHORTRADIUS };


	mrchpbar = {
	mrcRng.right + 12,
	mrcRng.bottom - (INT)GETHPBAR(mhp->GetHp(), (DIA_SHORTRADIUS * 2), DIA_MAXHP),
	mrcRng.right + 15,
	mrcRng.bottom
	};

	mrchpbar.left = mrcRng.right + 12;
	mrchpbar.top = mrcRng.bottom - (INT)GETHPBAR(mhp->GetHp(), (DIA_SHORTRADIUS * 2), DIA_MAXHP);
	mrchpbar.right = mrcRng.right + 15;
	mrchpbar.bottom = mrcRng.bottom;

}

void CDia::Attack()
{
	// Ÿ���� �տ� ���� ��
	pattacktarget->PutDamage(DIA_ATTACKDAMAGE);
	
}

void CDia::Update()
{
	if (ideatheffecttime) {
		ideatheffecttime -= FRAMETIME;
		return;
	}


	Move();


	if (iattackcooltime)
		iattackcooltime -= FRAMETIME;
	else {
		if (attackOn) {
			Attack();
			iattackcooltime = FRAMETIME * 50;
		}
	}


}

INT CDia::GetObjRadius()
{
	return DIA_SHORTRADIUS;
}

void CDia::Death()
{
	ideatheffecttime = FRAMETIME * 50;
}
