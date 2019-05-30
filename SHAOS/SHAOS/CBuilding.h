#pragma once
#include "CGameObject.h"
class CBuilding : public CGameObject
{
protected:

public:
	CBuilding();
	~CBuilding();
	virtual void Draw() = 0;
};