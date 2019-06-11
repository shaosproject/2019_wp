#pragma once
#include "CUnit.h"
class CTri : public CUnit
{
	INT iattakradius;
	float halfedge;
public:
	CTri(POINTFLOAT initPos, TEAM team, CGameObject* enemylist);
	~CTri();

	virtual void Update();
	virtual void Draw(HDC hdc);

	virtual void SelectedDraw(HDC, HBRUSH);

	void Move();
	void Attack();

	virtual INT	GetObjRadius();
};

