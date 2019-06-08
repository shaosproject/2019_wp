#pragma once
#include "CGameObject.h"

class CTower : public CGameObject
{
	POINT triangle1[3];
	POINT triangle2[3];

public:
	CTower(POINTFLOAT initPos, TEAM team, CGameObject* enemylist);
	~CTower();
	virtual void Update();
	virtual void Draw(HDC hdc);

	void SelectedDraw(HDC hdc);


	virtual INT		GetObjRadius();
	virtual void	Death();

};