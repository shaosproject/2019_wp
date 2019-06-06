#pragma once
#include "CTeam.h"
class CPlayer;
class CUser : public CTeam
{
	// gameobjlist�� Ÿ��, �÷��̾�, ���� ������ ����
	CTower* mTower;
	CPlayer* mPlayer;
	CUnit* mUnithead;

	const POINT ptUnitSponPos = { 500, 350 };

public:
	CUser();
	~CUser();

	void Update();
	void MSG_Key(UINT message, WPARAM wParam);
	void Draw(HDC hdc);

	POINTFLOAT GetPlayerPos();
};

