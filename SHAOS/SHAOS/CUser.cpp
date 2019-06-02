#include "pch.h"
#include "CUser.h"
#include "CTower.h"
#include "CPlayer.h"
#include "CUnit.h"

CUser::CUser()
{
	//tmp
	POINTFLOAT initPos = { 100,100 };
	//

	mPlayer = new CPlayer(initPos);
	this->AddMyObjList(mPlayer);
}


CUser::~CUser()
{
}

void CUser::Update()
{
	mPlayer->Move(mPlayer->Player_Vector());
}

void CUser::MSG_Key(UINT message, WPARAM wParam)
{
	mPlayer->Player_Message(message, wParam);
}

void CUser::Draw(HDC hdc)
{
	mPlayer->Draw(hdc);
}

POINTFLOAT CUser::GetPlayerPos()
{
	return mPlayer->GetPos();
}
