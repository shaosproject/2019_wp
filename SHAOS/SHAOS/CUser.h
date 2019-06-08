#pragma once
#include "CTeam.h"


const POINTFLOAT PLAYER_INITPOS = { 100,100 };

class CPlayer;
class CUser : public CTeam
{
	// gameobjlist에 타워, 플레이어, 유닛 순으로 연결
	CTower* mTower;
	CPlayer* mPlayer;

	const POINTFLOAT ptUnitSponPos = { 500, 350 };

public:
	CUser();
	~CUser();
	
	void SetInitObj();

	void Update();
	void Draw(HDC hdc);
	void MSG_Key(UINT message, WPARAM wParam);
	void MSG_Mouse(UINT message, POINT mousepos);

	void UnitGen();

	POINTFLOAT GetPlayerPos();
};

