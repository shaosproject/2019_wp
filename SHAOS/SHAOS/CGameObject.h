#pragma once
class CHp;
class CGameObject
{
protected:
	POINTFLOAT		mptpos;
	RECT			mrcRng;
	CHp				*mhp;
public:
	CGameObject();
	virtual ~CGameObject();


};