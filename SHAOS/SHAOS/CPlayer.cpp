#include "pch.h"
#include "CPlayer.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
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
