#pragma once
#include "CHp.h"

class CGameObject
{
protected:
	POINTFLOAT		mptpos;
	RECT			mrcRng;

	CHp*			mhp{ nullptr };
	RECT			mrchpbar;

	INT				mattacktime;

	CGameObject* menemylist{ nullptr };

	TEAM team;
public:
	CGameObject* next{ nullptr };
	CGameObject* prev{ nullptr };

	CGameObject(POINTFLOAT ainitPos, TEAM ateam ,CGameObject* aenemylist);
	virtual ~CGameObject();

	virtual void Draw(HDC) = 0;
	virtual void Update() = 0;
	void DrawHP(HDC);



	POINTFLOAT		GetPos() const;
	RECT			GetRng() const; // ? �ʿ��ұ�?
	
	virtual INT		GetObjRadius() = 0;

	void PutDamage(INT damage);

	virtual void Death() = 0;
};