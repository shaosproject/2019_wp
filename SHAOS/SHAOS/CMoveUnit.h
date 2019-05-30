#pragma once
#include "CGameObject.h"
class CMoveUnit : public CGameObject
{
protected:

public:
	CMoveUnit();
	~CMoveUnit();

	virtual void Move() = 0;
	virtual void Draw() = 0;
};

