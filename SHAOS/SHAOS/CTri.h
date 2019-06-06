#pragma once
#include "CUnit.h"
class CTri : public CUnit
{
public:
	CTri(POINTFLOAT initPos);
	~CTri();
	virtual void Draw(HDC hdc);
	virtual void Update();

};

