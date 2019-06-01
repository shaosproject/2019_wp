#include "pch.h"
#include "CGameObject.h"
#include "CHp.h"


CGameObject::CGameObject(POINTFLOAT ainitPos) : mptpos(ainitPos)
{
}


CGameObject::~CGameObject()
{
}

POINTFLOAT CGameObject::GetPos()
{
	return mptpos;
}
