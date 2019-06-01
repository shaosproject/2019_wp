#pragma once
#include "CUnit.h"
class CRect : public CUnit
{
	const INT attackRng = RECT_RADIUS + 5;

public:
	CRect(POINTFLOAT ainitPos);
	~CRect();
	virtual void Draw(HDC hdc);

	
	void Attack(CGameObject**, INT opponentNum);
};

