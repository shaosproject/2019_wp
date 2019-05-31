#pragma once

class CTower;
class CUnit;
class CTeam
{
protected:
	CUnit* mUnitList{ nullptr };
	CTower* mTower;
public:
	CTeam();
	virtual ~CTeam();

	void Draw(HDC hdc);
};

