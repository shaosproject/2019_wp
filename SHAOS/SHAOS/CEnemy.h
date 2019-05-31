#pragma once
#include "CTeam.h"
class CEnemy : public CTeam
{
public:
	CEnemy();
	~CEnemy();

	void Draw(HDC hdc);
};