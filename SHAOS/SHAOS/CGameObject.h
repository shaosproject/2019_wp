#pragma once
class CHp;
class CGameObject
{
protected:
	POINTFLOAT		mptos;
	RECT			mrcRng;
	CHp				*mhp;
public:
	CGameObject();
	virtual ~CGameObject();


};