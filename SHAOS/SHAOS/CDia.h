#pragma once
#include "CUnit.h"
class CDia : public CUnit
{
public:
	CDia();
	~CDia();
	virtual void Draw(HDC hdc);
	virtual void Update();

};

