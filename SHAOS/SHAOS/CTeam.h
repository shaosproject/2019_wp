#pragma once
#include "CTower.h"

class CUnit;
class CTeam
{
protected:
	CUnit* mUnitList;
	CTower* mTower;
public:
	CTeam();
	virtual ~CTeam();

};

