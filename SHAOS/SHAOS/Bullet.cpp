#include "pch.h"
#include "Bullet.h"
#include "CGameObject.h"

Bullet::Bullet(const POINTFLOAT* initPos, CGameObject* target, INT damage)
	: ptbulletpos(*initPos), ptargetobj(target) , idamage(damage)
{
}
Bullet::~Bullet()
{
}

Bullet* Bullet::Move()
{
	if (ptargetobj->IsDead()) {
		this->~Bullet();
		return nullptr;
	}
	float projX = ptargetobj->GetPos().x - ptbulletpos.x;
	float projY = ptargetobj->GetPos().y - ptbulletpos.y;

	float distance = sqrt(projX * projX + projY * projY);

	// �Ѿ��� ��ǥ ������Ʈ�� �ȿ� ���� �Ҹ�
	if (distance < ptargetobj->GetObjRadius()) {
		// ����� hp���
		ptargetobj->PutDamage(idamage);

		this->~Bullet();
		return nullptr;
	}

	float nomalizedX = projX / distance;
	float nomalizedY = projY / distance;

	ptbulletpos.x += nomalizedX * BULLET_SPEED;
	ptbulletpos.y += nomalizedY * BULLET_SPEED;

	return this;
}

void Bullet::Draw(HDC hdc)
{
	Ellipse(hdc, ptbulletpos.x - BULLET_RADIUS, ptbulletpos.y - BULLET_RADIUS,
		ptbulletpos.x + BULLET_RADIUS, ptbulletpos.y + BULLET_RADIUS);
}