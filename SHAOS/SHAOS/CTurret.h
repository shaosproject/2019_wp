#pragma once
#include "CGameObject.h"

#define TURRET_EFFECTTIME_DEATH FRAMETIME * 50
#define TOWER_ATTACK_RANGE 300

const HPEN hREDPEN = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));


class Bullet;
class CTurret : public CGameObject
{
	CGameObject* ptarget;
	Bullet* pbullet;

public:
	CTurret(POINTFLOAT initPos, TEAM team, CGameObject* enemylist);
	~CTurret();
	virtual void Draw(HDC hdc);
	virtual void Update();

	CGameObject* FindTarget();
	void Attack();

	virtual void SelectedDraw(HDC, HBRUSH);

	virtual INT		GetObjRadius();
	virtual void	Death();
};

