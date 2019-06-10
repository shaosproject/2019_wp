#pragma once
#include "CUnit.h"

#define DIA_SPEED 2

class CDia : public CUnit
{

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

