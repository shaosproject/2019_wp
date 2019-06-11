#pragma once
#include "CGameObject.h"

#define TOWER_EFFECTTIME_DEATH (FRAMETIME * 100)
const HBRUSH hUSERTOWERCIRCLEBRUSH = CreateSolidBrush(RGB(0, 0, 92));
const HBRUSH hENEMYTOWERCIRCLEBRUSH = CreateSolidBrush(RGB(92, 0, 0));

class CTower : public CGameObject
{
	POINT triangle1[3];
	POINT triangle2[3];

	HBRUSH hTriBrush;

public:
	CTower(POINTFLOAT initPos, TEAM team, CGameObject* enemylist);
	~CTower();
	virtual void Update();
	virtual void Draw(HDC hdc);

	void SelectedDraw(HDC, HBRUSH);


	virtual INT		GetObjRadius();
	virtual void	Death();
	INT				GetTowerHp();
};