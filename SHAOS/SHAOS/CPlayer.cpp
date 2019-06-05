#include "pch.h"
#include "CPlayer.h"
#include "CHp.h"

CPlayer::CPlayer(POINTFLOAT ainitPos) : CGameObject(ainitPos), iAoERadius(PLAYER_RADIUS * 2)
{
	// 충돌체크용 플레이어 영역 설정해주기
	mrcRng = { (LONG)mptpos.x - PLAYER_RADIUS,(LONG)mptpos.y - PLAYER_RADIUS,
		(LONG)mptpos.x + PLAYER_RADIUS, (LONG)mptpos.y + PLAYER_RADIUS };

	// hp 관련 초기화
	mhp = new CHp(PLAYER_MAXHP);
	mrchpbar = { mrcRng.left, mrcRng.top - 7, mrcRng.right, mrcRng.top - 4 };


	R_On = FALSE;
	L_On = FALSE;
	U_On = FALSE;
	D_On = FALSE;

	pressQ = FALSE;
	returntime = 0;
}


CPlayer::~CPlayer()
{
	// hp 해제
	delete mhp;
}

void CPlayer::Player_Attack()
{}
void CPlayer::Player_Message(UINT message, WPARAM wParam)
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
		case 'Q':
			if (!pressQ) {
				pressQ = TRUE;
				ReturnHome();
			}
			break;
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
void CPlayer::Move() {
	// 플레이어 중심점 좌표
	POINTFLOAT dirvector = this->Player_Vector();	
	mptpos.x = PLAY_CLIENTX(mptpos.x + dirvector.x);
	mptpos.y = PLAY_CLIENTY(mptpos.y + dirvector.y);

	// 플레이어 영역
	mrcRng = { (LONG)mptpos.x - PLAYER_RADIUS,(LONG)mptpos.y - PLAYER_RADIUS,
		(LONG)mptpos.x + PLAYER_RADIUS, (LONG)mptpos.y + PLAYER_RADIUS };

}

void CPlayer::ReturnHome()
{
	returntime = FRAMETIME * 50;
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
void CPlayer::Draw(HDC hdc)
{
	if (pressQ) {
		// 귀환할 때 어떤 그리기를 할 것인지
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
	Ellipse(hdc, mptpos.x - PLAY_ELLIPSE_RAD, mptpos.y - PLAY_ELLIPSE_RAD, mptpos.x + PLAY_ELLIPSE_RAD, mptpos.y + PLAY_ELLIPSE_RAD);
}

void CPlayer::Update()
{
	// 플레이어 움직임
	Move();

	// hpbar
	mrchpbar.left = mrcRng.left;
	mrchpbar.top = mrcRng.top - 5;
	mrchpbar.right = mrcRng.left + GETHPBAR(mhp->GetHp(), PLAYER_RADIUS * 2, PLAYER_MAXHP);
	mrchpbar.bottom = mrcRng.top - 2;

	// 귀환 시간 확인
	if (pressQ) {
		if (returntime == 0) {
			SetPos(100, 100);
			pressQ = FALSE;
		}
		returntime -= FRAMETIME;
	}

}
