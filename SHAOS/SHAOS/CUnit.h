#pragma once
#include "CGameObject.h"

class CUnit : public CGameObject
{
public:
	CUnit();
	~CUnit();

	virtual void Draw(HDC hdc) = 0;
};

