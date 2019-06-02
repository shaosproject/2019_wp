
#pragma once
#include "CBuilding.h"

class CTurret : public CBuilding
{
public:
	CTurret(POINTFLOAT initPos);
	~CTurret();
	void Turret_Attack();
	RECT* Turret_Rect();
	virtual void Draw(HDC hdc);
};

