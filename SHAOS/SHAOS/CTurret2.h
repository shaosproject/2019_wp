#pragma once
#include "CGameObject.h"

class CTurret2 : public CGameObject
{

	CGameObject* ptarget;
public:
	CTurret2(POINTFLOAT initPos, TEAM team, CGameObject* enemylist);
	~CTurret2();

	virtual void Draw(HDC hdc);
	virtual void Update();

	CGameObject* FindTarget();
	void Attack();

	virtual void SelectedDraw(HDC, HBRUSH);

	virtual INT		GetObjRadius();
	virtual void	Death();

};

