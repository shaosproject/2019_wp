#pragma once
#include "CTeam.h"
class CPlayer;
class CUser : public CTeam
{
	// gameobjlist에 타워, 플레이어, 유닛 순으로 연결
	CTower* mTower;
	CPlayer* mPlayer;
	CUnit* mUnithead;

	const POINT ptUnitSponPos = { 500, 350 };

public:
	CUser();
	~CUser();
	
	virtual void SetOpponentObj(CGameObject* objlist);

	void Update();
	void MSG_Key(UINT message, WPARAM wParam);
	void MSG_Mouse(UINT message, POINT mousepos);
	void Draw(HDC hdc);

	POINTFLOAT GetPlayerPos();
};

