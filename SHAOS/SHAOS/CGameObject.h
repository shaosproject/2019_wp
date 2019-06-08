#pragma once
#include "CHp.h"

class CGameObject
{
protected:
	POINTFLOAT		mptpos;
	RECT			mrcRng;

	CHp*			mhp{ nullptr };
	RECT			mrchpbar;
	BOOL			mdeath;

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

	virtual void SelectedDraw(HDC) {};


	POINTFLOAT		GetPos() const;
	RECT			GetRng() const; // ? 필요할까?
	
	virtual INT		GetObjRadius() = 0;

	BOOL PutDamage(INT damage);

	virtual void	Death() = 0;
	BOOL			IsDead() const;
};