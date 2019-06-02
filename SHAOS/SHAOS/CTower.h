#pragma once
#include "CBuilding.h"

class CTower : public CBuilding
{
public:
	CTower(POINTFLOAT initPos);
	~CTower();
	virtual void Draw(HDC hdc);
};