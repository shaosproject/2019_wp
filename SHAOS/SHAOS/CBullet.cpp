#include "CBullet.h"
#include "pch.h"
#include "CGameObject.h"



CBullet::CBullet(POINTFLOAT initPos, CGameObject* target)
	: ptbulpos(initPos), ptargetobj(target)
{
}

CBullet::~CBullet()
{
}

void CBullet::Bullet_Move()
{
	//d = sqrt((bulPos.x - enemyPos.x) * (bulPos.x - enemyPos.x) + (bulPos.y - enemyPos.y) * (bulPos.y - enemyPos.y));
	//if (d < MAX)
	//{	
	//	bulPos.x = (bulPos.x - enemyPos.x) * 2 / d + bulPos.x;
	//	bulPos.y = (bulPos.y - enemyPos.y) * 2 / d + bulPos.y;
	//}
}