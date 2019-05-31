#pragma once
#include "CBuilding.h"

class CTower : public CBuilding
{
public:
	CTower();
	~CTower();
	virtual void Draw(HDC hdc);
};

