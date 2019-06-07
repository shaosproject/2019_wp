#pragma once
#include "CGameObject.h"

class CTurret : public CGameObject
{
public:
	CTurret(POINTFLOAT initPos, TEAM team, CGameObject* enemylist);
	~CTurret();
	virtual void Draw(HDC hdc);
	virtual void Update();

	void SelectedDraw(HDC hdc);

	virtual INT		GetObjRadius();
	virtual void	Death();
};

