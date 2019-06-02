#pragma once
#include "CTeam.h"
class CPlayer;
class CUser : public CTeam
{
	// gameobjlist에 타워, 플레이어, 유닛 순으로 연결
	CTower* mTower;
	CPlayer* mPlayer;
	CUnit* mUnithead;
public:
	CUser();
	~CUser();

	void Update();
	void MSG_Key(UINT message, WPARAM wParam);
	void Draw(HDC hdc);

	POINTFLOAT GetPlayerPos();
};

