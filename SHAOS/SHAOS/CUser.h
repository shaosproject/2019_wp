#pragma once
#include "CTeam.h"
#include "CPlayer.h"

class CUser : public CTeam
{
	CPlayer mPlayer;


public:
	CUser();
	~CUser();

	void Update();
	void Draw(HDC hdc);
};

