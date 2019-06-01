#include "pch.h"
#include "CPlayer.h"
#include "CHp.h"

CPlayer::CPlayer(POINTFLOAT ainitPos) : CGameObject(ainitPos)
{
	// 충돌체크용 플레이어 영역 설정해주기
	mrcRng = { mptpos.x - PLAYER_RADIUS, mptpos.y - PLAYER_RADIUS, 
		mptpos.x + PLAYER_RADIUS, mptpos.y + PLAYER_RADIUS };

	// hp 할당
	mhp = new CHp(100);

	R_On = FALSE;
	L_On = FALSE;
	U_On = FALSE;
	D_On = FALSE;
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
		}
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
		}
	}
}
void CPlayer::Move(POINTFLOAT vector) {
	mptpos.x += Player_Vector().x;
	mptpos.y += Player_Vector().y;
}

POINTFLOAT CPlayer::Player_Vector()
{
	if (R_On && U_On)
		return { 2,2 };
	if (R_On && D_On)
		return { 2,-2 };
	if (D_On && L_On)
		return { -2,-2 };
	if (U_On && L_On)
		return{ -2,2 };
	if (R_On)
		return { 3,0 };
	if (L_On)
		return { -3,0 };
	if (U_On)
		return { 0,-3 };
	if (D_On)
		return { 0,3 };

}
void CPlayer::Draw(HDC hdc)
{
	FLOAT TriHeight = PLAYER_RADIUS / 2 * sqrt(3);
	POINTFLOAT pt[6];
	pt[0] = { mptpos.x - PLAYER_RADIUS, mptpos.y };
	pt[1] = { mptpos.x - (PLAYER_RADIUS / 2), mptpos.y - TriHeight };
	pt[2] = { mptpos.x + (PLAYER_RADIUS / 2), mptpos.y - TriHeight };
	pt[3] = { mptpos.x + PLAYER_RADIUS, mptpos.y };
	pt[4] = { mptpos.x + (PLAYER_RADIUS / 2), mptpos.y + TriHeight };
	pt[5] = { mptpos.x - (PLAYER_RADIUS / 2), mptpos.y + TriHeight };
	Polygon(hdc, (POINT*)pt, 6);
}
