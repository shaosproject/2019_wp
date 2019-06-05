#pragma once
#include "CUnit.h"
class CEllip : public CUnit
{
public:
	CEllip();
	~CEllip();
	virtual void Draw(HDC hdc);
	virtual void Update();

};

