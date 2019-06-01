#include "pch.h"
#include "CRect.h"
#include "CHp.h"

CRect::CRect(POINTFLOAT ainitPos) : CUnit(ainitPos)
{
	mrcRng = { mptpos.x - RECT_RADIUS, mptpos.y - RECT_RADIUS,
	mptpos.x + RECT_RADIUS, mptpos.y + RECT_RADIUS };

	mhp = new CHp(RECT_HP);
}


CRect::~CRect()
{
}

void CRect::Draw(HDC hdc)
{
	Rectangle(hdc, mrcRng.left, mrcRng.top, mrcRng.right, mrcRng.bottom);
}

void CRect::Attack(CGameObject** opponentobj, INT opponentNum)
{
	// ����� ������Ʈ�� �����ϰ� �ִ� ��带 �޾ƿͼ� �ϳ��ϳ� �˻��Ѵ�.

}
