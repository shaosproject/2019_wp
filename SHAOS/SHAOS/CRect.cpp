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
	// 상대편 오브젝트를 연결하고 있는 헤드를 받아와서 하나하나 검사한다.

}
