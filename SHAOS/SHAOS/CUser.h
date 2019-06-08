#pragma once
#include "CTeam.h"


class CPlayer;
class CUser : public CTeam
{
	// gameobjlist�� Ÿ��, �÷��̾�, ���� ������ ����
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

