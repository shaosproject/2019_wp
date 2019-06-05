#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(POINTFLOAT pos, POINTFLOAT* epos,POINTFLOAT* opos):bulpos(pos),enempos(epos),objpos(opos)
{
	bulOn = TRUE;
	bulstart = FALSE;
}
Bullet::~Bullet()
{
}
void Bullet::Target_check()
{
	d = sqrt((objpos->x - enempos->x) * (objpos->x - enempos->x) 
		+ (objpos->y - enempos->y) * (objpos->y - enempos->y));

	if (bulstart)
	{
		bulOn = FALSE;
		bulpos.x = objpos->x;
		bulpos.y = objpos->y;
	}
}
void Bullet::Move()
{	
	if (bulOn)
	{
		if (d <= TARGET_DISTANCE)
		{
			bulpos.x = (enempos->x - bulpos.x) * BULLET_SPEED + bulpos.x;
			bulpos.y = (enempos->y - bulpos.y) * BULLET_SPEED + bulpos.y;

		if (bulpos.x == enempos->x && bulpos.y == objpos->y)
			bulstart = TRUE;
	}
}

void Bullet::Draw(HDC hdc)
{

	Ellipse(hdc, bulpos.x - BULLET_RAD, bulpos.y - BULLET_RAD, bulpos.x + BULLET_RAD, bulpos.y + BULLET_RAD);
}