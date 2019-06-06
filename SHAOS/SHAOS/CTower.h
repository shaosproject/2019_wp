#pragma once
#include "CGameObject.h"

class CTower : public CGameObject
{
public:
	CTower(POINTFLOAT initPos);
	~CTower();
	virtual void Draw(HDC hdc);
	virtual void Update() {};

	virtual INT		GetObjRadius();
};