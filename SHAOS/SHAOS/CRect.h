#pragma once
#include "CUnit.h"
#include "CTower.h"
#define RECT_DAMAGE 10
#define UNIT_SPEED 1

#define RECT_EFFECTTIME_DEATH FRAMETIME*50

class CRect : public CUnit
{
	const INT iattakradius = RECT_RADIUS + 5;

public:
	CRect(POINTFLOAT ainitPos, TEAM team, CGameObject* enemylist);
	~CRect();
	virtual void Update();
	virtual void Draw(HDC hdc);
	
	virtual void SelectedDraw(HDC hdc);


	void Move();
	void Attack();
	void SetTarget();

	virtual INT		GetObjRadius();
	virtual void	Death();

};

