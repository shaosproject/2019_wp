#include "pch.h"
#include "CPlayer.h"
#include "CHp.h"
#include "Bullet.h"

CPlayer::CPlayer(POINTFLOAT ainitPos, TEAM team, CGameObject* enemylist)
	: CGameObject(ainitPos, team, enemylist), iAoERadius(PLAYER_RADIUS * 4)
{
	// 충돌체크용 플레이어 영역 설정해주기
	mrcRng = { (LONG)mptpos.x - PLAYER_RADIUS,(LONG)mptpos.y - PLAYER_RADIUS,
		(LONG)mptpos.x + PLAYER_RADIUS, (LONG)mptpos.y + PLAYER_RADIUS };

	// hp 관련 초기화
	mhp = new CHp(PLAYER_MAXHP);
	mrchpbar = { mrcRng.left - 7, mrcRng.top, mrcRng.left - 4, mrcRng.bottom };

	// 이동
	R_On = FALSE;
	L_On = FALSE;
	U_On = FALSE;
	D_On = FALSE;

	// 스킬
	pressSft = FALSE;

	AoEdrawtime = 0;

	pressQ = FALSE;
	returntime = 0;

	onshield = FALSE;
	shieldtime = 0;

	cooltime_Shield = 0;
	cooltime_AoE = 0;
	cooltime_Shoot = 0;

	//공격
	ptarget = nullptr;
	pbullet = nullptr;

}


CPlayer::~CPlayer()
{
	// hp 해제 
	delete mhp;
	if (pbullet) delete pbullet;
}


void CPlayer::MSG_Key(UINT message, WPARAM wParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A':
			L_On = TRUE;
			break;
		case 'D':
			R_On = TRUE;
			break;
		case 'S':
			D_On = TRUE;
			break;
		case 'W':
			U_On = TRUE;
			break;
		case VK_SHIFT:
			if (!cooltime_Shoot && !pressSft) {
				pressSft = TRUE;
				Skill_Shoot();
			}
			break;
		case VK_SPACE:
			if (!cooltime_AoE) {
				Skill_AreaOfEffect();
			}
			break;
		case 'Q':
			// 쿨타임 조건 추가해야 함
			if (!pressQ && !cooltime_Return) {
				pressQ = TRUE;
				ReturnHome();
			}
			break;
		case 'V':
			// 쉴드 쿨타임이 없을 때 = 0일 때
			if (!cooltime_Shield) {
				ActiveShield();
			}
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case 'A':
			L_On = FALSE;
			break;
		case 'D':
			R_On = FALSE;
			break;
		case 'S':
			D_On = FALSE;
			break;
		case 'W':
			U_On = FALSE;
			break;
		case VK_SHIFT:
			pressSft = TRUE;
			break;

		case 'Q':
			if (pressQ) {
				pressQ = FALSE;
				returntime = 0;
			}
			break;
		}
		break;
	}
}


void CPlayer::MSG_MouseMove(POINT mousepos)
{
}
void CPlayer::MSG_MouseUp(POINT mousepos)
{
}
void CPlayer::MSG_MouseDown(POINT mousepos)
{
	CGameObject* tmp = nullptr;

	while (tmp != menemylist) {
		if (!tmp) tmp = menemylist;

		if (PtInRect(&tmp->GetRng(), mousepos)) {
			ptarget = tmp;
			return;
		}

		tmp = tmp->next;
	}
 }



void CPlayer::Move() {
	// 플레이어 중심점 좌표
	POINTFLOAT dirvector = this->Player_Vector();

	POINTFLOAT nextpos = {mptpos.x + dirvector.x,mptpos.y + dirvector.y};

	FLOAT etd = sqrt((ENEMYTOWER_POS.x - nextpos.x) * (ENEMYTOWER_POS.x - nextpos.x) +
		(ENEMYTOWER_POS.y - nextpos.y) * (ENEMYTOWER_POS.y - nextpos.y));
	
	if (etd <= TOWER_CENTER2VERTAX + PLAYER_RADIUS)
		return;

	FLOAT utd = sqrt((USERTOWER_POS.x - nextpos.x) * (USERTOWER_POS.x - nextpos.x) +
		(USERTOWER_POS.y - nextpos.y) * (USERTOWER_POS.y - nextpos.y));

	if (utd <= TOWER_CENTER2VERTAX + PLAYER_RADIUS)
		return;

	mptpos.x = PLAY_CLIENTX(mptpos.x + dirvector.x);
	mptpos.y = PLAY_CLIENTY(mptpos.y + dirvector.y);

	// 플레이어 영역
	mrcRng = { (LONG)mptpos.x - PLAYER_RADIUS,(LONG)mptpos.y - PLAYER_RADIUS,
		(LONG)mptpos.x + PLAYER_RADIUS, (LONG)mptpos.y + PLAYER_RADIUS };

}

void CPlayer::Skill_AreaOfEffect()
{
	cooltime_AoE = COOLTIME_AOE;

	// 이펙트 신호 주기
	AoEdrawtime = DRAWTIME_AOE;

	// 충돌체크해서 데미지 주기
	CGameObject* tmp = nullptr;
	while (tmp != menemylist) {
		if (!tmp) tmp = menemylist;
		
		// 두 원의 중심의 거리가 두 원의 반지름의 합보다 작은 경우 충돌
		float dx = mptpos.x - tmp->GetPos().x;
		float dy = mptpos.y - tmp->GetPos().y;

		float center_d = dx * dx + dy * dy;
		float range = iAoERadius + tmp->GetObjRadius();
		if (center_d <= range*range) {
			tmp->PutDamage(PLAYER_AOEDAMAGE);
		}

		tmp = tmp->next;
	}
}

void CPlayer::Skill_Shoot()
{
	cooltime_Shoot = COOLTIME_SHOOT;

}

void CPlayer::ReturnHome()
{
	returntime = CASTINGTIME_RETURN;
}

void CPlayer::ActiveShield()
{
	onshield = TRUE;
	shieldtime = ACTIVETIME_SHIELD;
	cooltime_Shield = COOLTIME_SHIELD;
}

POINTFLOAT CPlayer::Player_Vector()
{
	if (R_On && U_On)
		return DIRVECTOR_RT;
	if (R_On && D_On)
		return DIRVECTOR_RB;
	if (D_On && L_On)
		return DIRVECTOR_LB;
	if (U_On && L_On)
		return DIRVECTOR_LT;
	if (R_On)
		return DIRVECTOR_RIGHT;
	if (L_On)
		return DIRVECTOR_LEFT;
	if (U_On)
		return DIRVECTOR_TOP;
	if (D_On)
		return DIRVECTOR_BOTTOM;
	return DIRVECTOR_STOP;
}


void CPlayer::SetPos(INT x, INT y)
{
	mptpos.x = x;
	mptpos.y = y;
}
INT CPlayer::GetObjRadius()
{
	return PLAYER_RADIUS;
}
void CPlayer::Attack()
{
	if (!ptarget) return;

	if (pbullet) pbullet = pbullet->Move();
	else pbullet = new Bullet(&mptpos, ptarget, PLAYER_BULLETDAMAGE);

	if (ptarget->IsDead()) ptarget = nullptr;
}

void CPlayer::Draw(HDC hdc)
{
	if (pressSft) {

	}

	if (AoEdrawtime) {
		// 광역기 이펙트 그리기

		Ellipse(hdc, mptpos.x - iAoERadius, mptpos.y - iAoERadius,
			mptpos.x + iAoERadius, mptpos.y + iAoERadius);
	}


	if (pressQ) {
		// 파란색 바 그리기
		RECT rcrtbarRng = { mrcRng.left - 10, mrcRng.bottom + 2,
			mrcRng.right + 10, mrcRng.bottom + 7 };
		FillRect(hdc, &rcrtbarRng, hRTBRUSH);

		// 검은 바 그리기
		INT width = rcrtbarRng.right - rcrtbarRng.left;
		INT crt = returntime / FRAMETIME;
		INT max = CASTINGTIME_RETURN / FRAMETIME;
		INT leftposX = rcrtbarRng.right - ((crt * width) / max);
		RECT rcemptybar = {
			leftposX,
			rcrtbarRng.top + 1,
			rcrtbarRng.right,
			rcrtbarRng.bottom - 1
		};
		FillRect(hdc, &rcemptybar, (HBRUSH)GetStockObject(BLACK_BRUSH));

	};

	if (onshield) {
		Ellipse(hdc, mptpos.x - SHIELD_RAD, mptpos.y - SHIELD_RAD,
			mptpos.x + SHIELD_RAD, mptpos.y + SHIELD_RAD);
	}

	FLOAT TriHeight = PLAYER_RADIUS / 2 * sqrt(3);
	POINT pt[6];
	pt[0] = { (LONG)mptpos.x - PLAYER_RADIUS, (LONG)mptpos.y };
	pt[1] = { (LONG)mptpos.x - (PLAYER_RADIUS / 2), (LONG)(mptpos.y - TriHeight) };
	pt[2] = { (LONG)mptpos.x + (PLAYER_RADIUS / 2), (LONG)(mptpos.y - TriHeight) };
	pt[3] = { (LONG)mptpos.x + PLAYER_RADIUS, (LONG)mptpos.y };
	pt[4] = { (LONG)mptpos.x + (PLAYER_RADIUS / 2), (LONG)(mptpos.y + TriHeight) };
	pt[5] = { (LONG)mptpos.x - (PLAYER_RADIUS / 2), (LONG)(mptpos.y + TriHeight) };
	Polygon(hdc, pt, 6);
	Ellipse(hdc, mptpos.x - PLAY_ELLIPSE_RAD, mptpos.y - PLAY_ELLIPSE_RAD, 
		mptpos.x + PLAY_ELLIPSE_RAD, mptpos.y + PLAY_ELLIPSE_RAD);

	// 총알
	if (pbullet) {
		pbullet->Draw(hdc);
	}
	if (ptarget) {
		ptarget->SelectedDraw(hdc);
	}
}

void CPlayer::Update()
{

	// 플레이어 움직임
	Move();

	// 기지에 있으면 체력 회복
	if (mrcRng.left <= 650) {
		mhp->AddHp(RECOVERAMOUNT);
	}

	// hpbar 
	mrchpbar.left = mrcRng.left - 7;
	mrchpbar.top = mrcRng.bottom - GETHPBAR(mhp->GetHp(), PLAYER_RADIUS * 2, PLAYER_MAXHP);
	mrchpbar.right = mrcRng.left - 4;
	mrchpbar.bottom = mrcRng.bottom;

	Attack();

	if (AoEdrawtime) AoEdrawtime -= FRAMETIME;

	if (pressQ) {
		if (returntime == 0) 
		{
			SetPos(100, 100);
			pressQ = FALSE;
			cooltime_Return = COOLTIME_RETURN;
		}
		returntime -= FRAMETIME;
	}

	if (onshield) {
		if (shieldtime == 0) {
			onshield = FALSE;
		}
		shieldtime -= FRAMETIME;
	}

	// 쿨타임이 0이 아닐 때 감소
	if (cooltime_Shoot) cooltime_Shoot -= FRAMETIME;
	if (cooltime_AoE) cooltime_AoE -= FRAMETIME;
	if (cooltime_Shield) cooltime_Shield -= FRAMETIME;
	if (cooltime_Return) cooltime_Return -= FRAMETIME;

}
