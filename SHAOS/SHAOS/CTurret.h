
#pragma once
#include "CBuilding.h"

class CTurret : public CBuilding
{
	LONG* mpos;
public:
	CTurret();
	~CTurret();
	void Turret_Attack();
	RECT* Turret_Rect();
	virtual void Draw(HDC hdc);
};

