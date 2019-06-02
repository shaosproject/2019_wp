#pragma once
class CHp;


class CGameObject
{
protected:
	POINTFLOAT		mptpos;
	RECT			mrcRng;
	CHp*			mhp{ nullptr };

public:
	CGameObject* next{ nullptr };
	CGameObject* prev{ nullptr };

	CGameObject(POINTFLOAT ainitPos);
	virtual ~CGameObject();
	virtual void Draw(HDC) = 0;
	POINTFLOAT GetPos();
};