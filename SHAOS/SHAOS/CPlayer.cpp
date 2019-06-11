#include "pch.h"
#include "CPlayer.h"
#include "CHp.h"
#include "Bullet.h"
#include "Sound.h"
CPlayer::CPlayer(POINTFLOAT ainitPos, TEAM team, CGameObject* enemylist)
	: CGameObject(ainitPos, team, enemylist), iAoERadius(PLAYER_RADIUS * 5)
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
	onshield = FALSE;
	pressQ = FALSE;

	activetime_shield = 0;
	castingtime_return = 0;


	effecttime_Shoot = 0;
	effecttime_AoE = 0;
	effecttime_Return = 0;



	cooltime_Shoot = 0;
	cooltime_AoE = 0;
	cooltime_Shield = 0;
	cooltime_Return = 0;
	cooltime_Death = 0;

	//공격
	iattackcooltime = FRAMETIME * 50;
	ptarget = nullptr;
	pbullet = nullptr;

	msound = new CSound;
	
	for (int i = 0; i < 7; i++) {
		shootattackrange[i] = { 0,0 };
	}
	immotal = FALSE;
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
		case VK_F1:
			(immotal) ? immotal = FALSE : immotal = TRUE;
			break;
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
			}
			break;
		case VK_SPACE:
			if (!cooltime_AoE) {
				Skill_AreaOfEffect();
			}
			break;
		case 'Q':
			if (!pressQ && !cooltime_Return) {
				pressQ = TRUE;
				ReturnHome();				
			}
			break;
		case 'V':
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
			pressSft = FALSE;
			break;
		case 'Q':
			if (pressQ) {
				pressQ = FALSE;
				castingtime_return = 0;
			}
			break;
		}
		break;
	}
}


void CPlayer::MSG_MouseMove(POINT mousepos)
{
	worldmousepos = mousepos;

}

void CPlayer::MSG_MouseUp(POINT mousepos)
{
}
void CPlayer::MSG_MouseDown(POINT mousepos)
{
	if (pressSft) {
		Skill_Shoot();
		pressSft = FALSE;
		return;
	}

	CGameObject* tmp = nullptr;
	while (tmp != menemylist) {
		if (!tmp) tmp = menemylist;

		if (tmp->IsDead()) {
			tmp = tmp->next;
			continue;
		}
		if (PtInRect(&tmp->GetRng(), mousepos)) {
			float dx = mptpos.x - tmp->GetPos().x;
			float dy = mptpos.y - tmp->GetPos().y;

			float center_d = dx * dx + dy * dy;
			float range = PLAYER_ATTACK_RANGE + tmp->GetObjRadius();
			if (center_d <= range * range) {
				ptarget = tmp;
				return;
			}
		}
		tmp = tmp->next;
	}
}



void CPlayer::Move() {
	if (pressSft) return;
	if (effecttime_Return) return;
	if (pressQ) {
		if (R_On || L_On || U_On || D_On) {
			pressQ = FALSE;
			castingtime_return = 0;
		}

	}


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
	effecttime_AoE = PLAYER_EFFECTTIME_AOE;

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
	effecttime_Shoot = FRAMETIME * 50;

	float dx = worldmousepos.x - mptpos.x;
	float dy = worldmousepos.y - mptpos.y;

	float sizeofvector = sqrt(dx * dx + dy * dy);
	
	float standardx = dx / sizeofvector * 25;
	float standardy = dy / sizeofvector * 25;
	// 노말라이즈 구했고 사각형 7개 구하기


	for (int i = 0; i < 7; i++) {
		POINT centerpos = { (INT)(mptpos.x + standardx * (i + 1)),
			(INT)(mptpos.y + standardy * (i + 1)) };

		shootattackrange[i] = {
			centerpos.x - 25, centerpos.y - 25,
			centerpos.x + 25, centerpos.y + 25
		};

	}

	CGameObject* tmp = nullptr;
	while (tmp != menemylist) {
		if (!tmp) tmp = menemylist;

		RECT lprcDest;
		if (IntersectRect(&lprcDest, &shootattackrange[0], &tmp->GetRng()) ||
			IntersectRect(&lprcDest, &shootattackrange[1], &tmp->GetRng()) ||
			IntersectRect(&lprcDest, &shootattackrange[2], &tmp->GetRng()) ||
			IntersectRect(&lprcDest, &shootattackrange[3], &tmp->GetRng()) ||
			IntersectRect(&lprcDest, &shootattackrange[4], &tmp->GetRng()) ||
			IntersectRect(&lprcDest, &shootattackrange[5], &tmp->GetRng()) ||
			IntersectRect(&lprcDest, &shootattackrange[6], &tmp->GetRng())) {
			tmp->PutDamage(PLAYER_SHOOTDAMAGE);
		}

		tmp = tmp->next;
	}

}

void CPlayer::ReturnHome()
{
	castingtime_return = CASTINGTIME_RETURN;
}

void CPlayer::ActiveShield()
{
	onshield = TRUE;
	activetime_shield = ACTIVETIME_SHIELD;
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


void CPlayer::SetPos(POINT setpos)
{
	mptpos.x = (INT)setpos.x;
	mptpos.y = (INT)setpos.y;
}
void CPlayer::UI_GetPlayerInfo(INT* ahp, INT* ct_shoot, INT* ct_AoE,
	INT* ct_shield, INT* ct_return, INT* ct_death)
{
	*ahp = mhp->GetHp();
	*ct_shoot = cooltime_Shoot;
	*ct_AoE = cooltime_AoE;
	*ct_shield = cooltime_Shield;
	*ct_return = cooltime_Return;
	*ct_death = cooltime_Death;

}
void CPlayer::PutDamage(INT damage)
{
	if (immotal) return;
	if (effecttime_Return) return;
	// 귀환 취소
	if (pressQ) {
		pressQ = FALSE;
		castingtime_return = 0;
		cooltime_Return = FRAMETIME * 20;
	}
	

	// 쉴드가 켜져있을 때 데미지가 1/2만 들어가게
	if (onshield) damage /= 2;

	if (mhp->SubHp(damage)) {
		mdeath = TRUE;
		Death();
	}
}
INT CPlayer::GetObjRadius()
{
	return PLAYER_RADIUS;
}
BOOL CPlayer::Attack()
{
	if (!ptarget) return FALSE;
	pbullet = new Bullet(&mptpos, ptarget, PLAYER_BULLETDAMAGE);
	msound->MyPlaySound(2, 3);
	return TRUE;
}

void CPlayer::Draw(HDC hdc)
{

	if (mdeath) {
		// 죽었을 때 이펙트 그리기

		return;
	}


	if (pressSft) {
		// shoot의 공격경로 그리기
		// 방향벡터를 노말라이즈해서 길이만큼 곱한다

		float dx = worldmousepos.x - mptpos.x;
		float dy = worldmousepos.y - mptpos.y;

		float sizeofvector = sqrt(dx * dx + dy * dy);

		float nomalizedx = dx / sizeofvector;
		float nomalizedy = dy / sizeofvector;

		POINTFLOAT ptdraw = {
			mptpos.x + nomalizedx * PLAYER_SHOOT_LENGTH,
			mptpos.y + nomalizedy * PLAYER_SHOOT_LENGTH
		};

		HPEN hOld = (HPEN)SelectObject(hdc, hPLAYERSHOOTPEN);
		MoveToEx(hdc, mptpos.x, mptpos.y, nullptr);
		LineTo(hdc, ptdraw.x, ptdraw.y);
		SelectObject(hdc, hOld);
	}

	if (effecttime_Shoot) {
		//for (int i = 0; i < 7; i++) {
			// Shoot 이펙트 그리기
			//float efs = effecttime_Shoot / FRAMETIME / 7;
			//if (efs >= 7)
			//{
			//}
			//else if (efs >= 6)
			//{
			//	FillRect(hdc, &shootattackrange[0], (HBRUSH)GetStockObject(DKGRAY_BRUSH));
			//}
			//else if(efs >=5)
			//{
			//	FillRect(hdc, &shootattackrange[1], (HBRUSH)GetStockObject(DKGRAY_BRUSH));
			//}			
			//else if (efs >= 4)
			//{
			//	FillRect(hdc, &shootattackrange[2], (HBRUSH)GetStockObject(GRAY_BRUSH));
			//}			
			//else if (efs >= 3)
			//{
			//	FillRect(hdc, &shootattackrange[3], (HBRUSH)GetStockObject(GRAY_BRUSH));
			//}			
			//else if (efs >= 2)
			//{
			//	FillRect(hdc, &shootattackrange[4], (HBRUSH)GetStockObject(LTGRAY_BRUSH));
			//}			
			//else if (efs >= 1)
			//{
			//	FillRect(hdc, &shootattackrange[5], (HBRUSH)GetStockObject(LTGRAY_BRUSH));
			//}			
			//else if (efs >= 0)
			//{
			//	FillRect(hdc, &shootattackrange[6], (HBRUSH)GetStockObject(WHITE_BRUSH));
			//}

		float tmp1 = effecttime_Shoot / FRAMETIME;
	

		    if (tmp1 > 48)
			Ellipse(hdc, shootattackrange[0].left - 10, shootattackrange[0].bottom - 10,
				shootattackrange[0].left + 10, shootattackrange[0].bottom + 10);
			else if (tmp1>46)
				Ellipse(hdc, shootattackrange[0].left - 10, shootattackrange[0].top - 10,
					shootattackrange[0].left + 10, shootattackrange[0].top + 10);
			else if (tmp1 > 44)
				Ellipse(hdc, shootattackrange[0].right - 10, shootattackrange[0].top - 10,
					shootattackrange[0].right + 10, shootattackrange[0].top + 10);
			else if (tmp1 > 42)
				Ellipse(hdc, shootattackrange[0].right - 10, shootattackrange[0].bottom - 10,
					shootattackrange[0].right + 10, shootattackrange[0].bottom + 10);
			else if (tmp1 > 40)
				Ellipse(hdc, shootattackrange[1].left - 10, shootattackrange[1].bottom - 10,
					shootattackrange[1].left + 10, shootattackrange[1].bottom + 10);
			else if (tmp1 > 38)
				Ellipse(hdc, shootattackrange[1].left - 10, shootattackrange[1].top - 10,
					shootattackrange[1].left + 10, shootattackrange[1].top + 10);
			else if (tmp1 > 36)
				Ellipse(hdc, shootattackrange[1].right - 10, shootattackrange[1].top - 10,
					shootattackrange[1].right + 10, shootattackrange[1].top + 10);
			else if (tmp1 > 34)
				Ellipse(hdc, shootattackrange[1].right - 10, shootattackrange[1].bottom - 10,
					shootattackrange[1].right + 10, shootattackrange[1].bottom + 10);

			else if (tmp1 > 32)
				Ellipse(hdc, shootattackrange[2].left - 10, shootattackrange[2].bottom - 10,
					shootattackrange[2].left + 10, shootattackrange[2].bottom + 10);
			else if (tmp1 > 30)
				Ellipse(hdc, shootattackrange[2].left - 10, shootattackrange[2].top - 10,
					shootattackrange[2].left + 10, shootattackrange[2].top + 10);
			else if (tmp1 > 28)
				Ellipse(hdc, shootattackrange[2].right - 10, shootattackrange[2].top - 10,
					shootattackrange[2].right + 10, shootattackrange[2].top + 10);
			else if (tmp1 > 26)
				Ellipse(hdc, shootattackrange[2].right - 10, shootattackrange[2].bottom - 10,
					shootattackrange[2].right + 10, shootattackrange[2].bottom + 10);

			else if (tmp1 > 24)
				Ellipse(hdc, shootattackrange[3].left - 10, shootattackrange[3].bottom - 10,
					shootattackrange[3].left + 10, shootattackrange[3].bottom + 10);
			else if (tmp1 > 26)
				Ellipse(hdc, shootattackrange[3].left - 10, shootattackrange[3].top - 10,
					shootattackrange[3].left + 10, shootattackrange[3].top + 10);
			else if (tmp1 > 24)
				Ellipse(hdc, shootattackrange[3].right - 10, shootattackrange[3].top - 10,
					shootattackrange[3].right + 10, shootattackrange[3].top + 10);
			else if (tmp1 > 22)
				Ellipse(hdc, shootattackrange[3].right - 10, shootattackrange[3].bottom - 10,
					shootattackrange[3].right + 10, shootattackrange[3].bottom + 10);

			else if (tmp1 > 20)
				Ellipse(hdc, shootattackrange[4].left - 10, shootattackrange[4].bottom - 10,
					shootattackrange[4].left + 10, shootattackrange[4].bottom + 10);
			else if (tmp1 > 18)
				Ellipse(hdc, shootattackrange[4].left - 10, shootattackrange[4].top - 10,
					shootattackrange[4].left + 10, shootattackrange[4].top + 10);
			else if (tmp1 > 16)
				Ellipse(hdc, shootattackrange[4].right - 10, shootattackrange[4].top - 10,
					shootattackrange[4].right + 10, shootattackrange[4].top + 10);
			else if (tmp1 > 14)
				Ellipse(hdc, shootattackrange[4].right - 10, shootattackrange[4].bottom - 10,
					shootattackrange[4].right + 10, shootattackrange[4].bottom + 10);

			else if (tmp1 > 12)
				Ellipse(hdc, shootattackrange[5].left - 10, shootattackrange[5].bottom - 10,
					shootattackrange[5].left + 10, shootattackrange[5].bottom + 10);
			else if (tmp1 > 10)
				Ellipse(hdc, shootattackrange[5].left - 10, shootattackrange[5].top - 10,
					shootattackrange[5].left + 10, shootattackrange[5].top + 10);
			else if (tmp1 > 8)
				Ellipse(hdc, shootattackrange[5].right - 10, shootattackrange[5].top - 10,
					shootattackrange[5].right + 10, shootattackrange[5].top + 10);
			else if (tmp1 > 6)
				Ellipse(hdc, shootattackrange[5].right - 10, shootattackrange[5].bottom - 10,
					shootattackrange[5].right + 10, shootattackrange[5].bottom + 10);

			else if (tmp1 > 4)
				Ellipse(hdc, shootattackrange[6].left - 10, shootattackrange[6].bottom - 10,
					shootattackrange[6].left + 10, shootattackrange[6].bottom + 10);
			else if (tmp1 > 3)
				Ellipse(hdc, shootattackrange[6].left - 10, shootattackrange[6].top - 10,
					shootattackrange[6].left + 10, shootattackrange[6].top + 10);
			else if (tmp1 > 2)
				Ellipse(hdc, shootattackrange[6].right - 10, shootattackrange[6].top - 10,
					shootattackrange[6].right + 10, shootattackrange[6].top + 10);
			else if (tmp1 > 1)
				Ellipse(hdc, shootattackrange[6].right - 10, shootattackrange[6].bottom - 10,
					shootattackrange[6].right + 10, shootattackrange[6].bottom + 10);
	}


	if (effecttime_AoE) {
		// 광역기 이펙트 그리기

		//float tmp1 = iaoeeffecttime / FRAMETIME;
		//float tmp2 = PLAYER_EFFECTTIME_AOE / FRAMETIME;
		//
		//INT d = (INT)(iAoERadius * tmp1 / tmp2);
		//
		//
		//HBRUSH hOld = (HBRUSH)SelectObject(hdc, hIAOEBRUSH);
		//
		//Ellipse(hdc, mptpos.x - d, mptpos.y - d,
		//	mptpos.x + d, mptpos.y + d);
		//
		//SelectObject(hdc, hOld);

		HBRUSH hOld = (HBRUSH)SelectObject(hdc, hIAOEBRUSH);
		POINT iAoe[8] = { {mrcRng.left, mrcRng.top},{mptpos.x,mptpos.y - iAoERadius},{mrcRng.right, mrcRng.top}
			,{mptpos.x + iAoERadius,mptpos.y},{mrcRng.right, mrcRng.bottom}
			,{mptpos.x , mptpos.y+ iAoERadius},{mrcRng.left, mrcRng.bottom}
			,{mptpos.x- iAoERadius,mptpos.y} };
		//Ellipse(hdc, mptpos.x - iAoERadius, mptpos.y - iAoERadius, mptpos.x + iAoERadius, mptpos.y + iAoERadius);
		Polygon(hdc,iAoe, 8);
		SelectObject(hdc, hOld);
	}

	if (onshield) {

		
		HBRUSH hOld = (HBRUSH)SelectObject(hdc, hSDBRUSH);

		Ellipse(hdc, mptpos.x - SHIELD_RAD, mptpos.y - SHIELD_RAD,
			mptpos.x + SHIELD_RAD, mptpos.y + SHIELD_RAD);

		SelectObject(hdc, hOld);

	}


	if (pressQ) {
		// 파란색 바 그리기
		RECT rcrtbarRng = { mrcRng.left - 10, mrcRng.bottom + 2,
			mrcRng.right + 10, mrcRng.bottom + 7 };
		FillRect(hdc, &rcrtbarRng, hRTBRUSH);

		// 검은 바 그리기
		INT width = rcrtbarRng.right - rcrtbarRng.left;
		INT crt = castingtime_return / FRAMETIME;
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

	if (effecttime_Return) {
		// 귀환 이펙트 그리기
		mrcRng = { (LONG)(mptpos.x - PLAYER_CENTER2VERTAX),
		(LONG)(mptpos.y - PLAYER_CENTER2VERTAX),
		(LONG)(mptpos.x + PLAYER_CENTER2VERTAX),
		(LONG)(mptpos.y + PLAYER_CENTER2VERTAX)
		};
	// 먼저 그리는 삼각형
		Ellipse(hdc, mrcRng.left, mrcRng.top, mrcRng.right, mrcRng.bottom);

		triangle1[0] = { (LONG)mptpos.x, (LONG)(mptpos.y + PLAYER_CENTER2VERTAX) };
		triangle1[1] = { (LONG)(mptpos.x - PLAYER_HALFSIDE),(LONG)(mptpos.y - PLAYER_CENTER2SIDE) };
		triangle1[2] = { (LONG)(mptpos.x + PLAYER_HALFSIDE),(LONG)(mptpos.y - PLAYER_CENTER2SIDE) };
		// 나중에 그리는 삼각형
		triangle2[0] = { (LONG)mptpos.x, (LONG)(mptpos.y - PLAYER_CENTER2VERTAX) };
		triangle2[1] = { (LONG)(mptpos.x - PLAYER_HALFSIDE),(LONG)(mptpos.y + PLAYER_CENTER2SIDE) };
		triangle2[2] = { (LONG)(mptpos.x + PLAYER_HALFSIDE),(LONG)(mptpos.y + PLAYER_CENTER2SIDE) };

		HBRUSH hOld = (HBRUSH)SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));

		Polygon(hdc, triangle1, 3);
		Polygon(hdc, triangle2, 3);

		SelectObject(hdc, hOld);
		
		
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


	// hpbar 
	mrchpbar.left = mrcRng.left - 7;
	mrchpbar.top = mrcRng.bottom - GETHPBAR(mhp->GetHp(), PLAYER_RADIUS * 2, PLAYER_MAXHP);
	mrchpbar.right = mrcRng.left - 4;
	mrchpbar.bottom = mrcRng.bottom;



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
		float range = PLAYER_ATTACK_RANGE + tmp->GetObjRadius();
		if (center_d <= range * range) {
			tmp->SelectedDraw(hdc, hINRANGEBRUSH);
		}

		tmp = tmp->next;
	}


	// 총알
	if (pbullet) {
		//msound->MyPlaySound(2, 3);
		pbullet->Draw(hdc);
	}
	if (ptarget) {

		if (ptarget->IsDead()) ptarget = nullptr;			// 다른 유닛에 의해 죽었을 때
		else ptarget->SelectedDraw(hdc, hSELECTEDBRUSH);

	}
}


void CPlayer::Update()
{

	// 죽음
	if (ideatheffecttime) {
		ideatheffecttime -= FRAMETIME;
		if (!ideatheffecttime) {
			SetPos(PLAYER_DEFAULT_POSITION);
			mhp->SetHp(PLAYER_MAXHP);
			mdeath = FALSE;
		}
		return;	// 죽었으면 업데이트 멈추기
	}


	// 플레이어 움직임
	Move();

	// 기지에 있으면 체력 회복
	if (mrcRng.left <= 650) {
		mhp->AddHp(RECOVERAMOUNT);
	}


	if (effecttime_Shoot) effecttime_Shoot -= FRAMETIME;
	if (effecttime_AoE) effecttime_AoE -= FRAMETIME;

	if (effecttime_Return) {
		effecttime_Return -= FRAMETIME;
		if (!effecttime_Return)
		{
			//msound->MyPlaySound(3, 3);
			SetPos(PLAYER_DEFAULT_POSITION);
		}
	}

	if (pressQ) {
		//if(returntime==FRAMETIME*20)
		//	msound->MyPlaySound(3, 4);
		if (castingtime_return == 0)
		{
			cooltime_Return = COOLTIME_RETURN;
			effecttime_Return = FRAMETIME * 50;
			msound->MyPlaySound(3, 3);
			pressQ = FALSE;
		}
		castingtime_return -= FRAMETIME;
	}

	if (onshield) {
		if (activetime_shield == 0) {
			onshield = FALSE;
		}
		activetime_shield -= FRAMETIME;
	}


	// 쿨타임이 0이 아닐 때 감소
	if (cooltime_Shoot) {
		cooltime_Shoot -= FRAMETIME;
		if (!cooltime_Shoot) {
			msound->MyPlaySound(4, 3);
			// 쿨타임 끝~
		}
	}
	if (cooltime_AoE) {
		cooltime_AoE -= FRAMETIME;
		if (!cooltime_AoE) {
			msound->MyPlaySound(4, 3);
		}
	}
	if (cooltime_Shield)
	{
		cooltime_Shield -= FRAMETIME;
		if (!cooltime_Shield) {
			msound->MyPlaySound(4, 3);
		}
	}
	if (cooltime_Return)
	{
		cooltime_Return -= FRAMETIME;
		if (!cooltime_Return) {
			msound->MyPlaySound(4, 3);
		}
	}
			

	if (iattackcooltime)
		iattackcooltime -= FRAMETIME;
	else {
		if (Attack())
			iattackcooltime = FRAMETIME * 50;
	}

	if (pbullet) pbullet = pbullet->Move();

	if (ptarget) {
		if (ptarget->IsDead()) {		// 내 공격으로 죽었을 때
			ptarget = nullptr;
			return;
		}

		// 플레이어 공격 범위에서 벗어났을 때
		float dx = mptpos.x - ptarget->GetPos().x;
		float dy = mptpos.y - ptarget->GetPos().y;

		float center_d = dx * dx + dy * dy;
		float range = PLAYER_ATTACK_RANGE + ptarget->GetObjRadius();
		if (center_d > range * range) {
			ptarget = nullptr;
			return;
		}

	}
	return;
}

void CPlayer::Death()
{
	ideatheffecttime = PLAYER_EFFECTTIME_DEATH;
}
