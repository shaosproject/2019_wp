#pragma once
#include "CTeam.h"

class CUser : public CTeam
{
	CPlayer* mPlayer;


public:
	CUser();
	~CUser();

	void Update();
	void Draw(HDC hdc);

	POINTFLOAT GetPlayerPos();
};

