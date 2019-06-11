#pragma once
#include "CUnit.h"

#define DIA_SPEED 4
#define DIA_ATTACKDAMAGE 10
const HBRUSH hDIAATTACKBRUSH = CreateSolidBrush(RGB(75, 255, 150));

class CDia : public CUnit
{
	BOOL attackOn;
public:
	CDia(POINTFLOAT initPos, TEAM team, CGameObject* enemylist);
	~CDia();


	virtual void Update();
	virtual void Draw(HDC hdc);

	virtual void SelectedDraw(HDC, HBRUSH);

	void Move();
	void Attack();

	virtual INT		GetObjRadius();
	virtual void	Death();

};

