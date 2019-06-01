#pragma once
class CHp;
class CGameObject
{
protected:
	POINTFLOAT		mptpos;
	RECT			mrcRng;
	CHp*			mhp{ nullptr };
public:
	CGameObject(POINTFLOAT ainitPos);
	virtual ~CGameObject();

	POINTFLOAT GetPos();
};