#include "pch.h"
#include "CUser.h"
#include "CPlayer.h"


CUser::CUser()
{
	//tmp
	POINTFLOAT initPos = { 100,100 };
	//
	mPlayer = new CPlayer(initPos);
}


CUser::~CUser()
{
	delete mPlayer;
}

void CUser::Draw(HDC hdc)
{
	mPlayer->Draw(hdc);
}

POINTFLOAT CUser::GetPlayerPos()
{
	return mPlayer->GetPos();
}
