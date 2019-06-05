#pragma once
#include "CGameObject.h"

class CTurret : public CGameObject
{
public:
	CTurret(POINTFLOAT initPos);
	~CTurret();
	RECT* Turret_Rect();
	virtual void Draw(HDC hdc);
	virtual void Update() {};

};

