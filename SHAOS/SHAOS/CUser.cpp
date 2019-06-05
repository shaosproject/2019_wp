#include "pch.h"
#include "CUser.h"
#include "CPlayer.h"
#include "CRect.h"
#include "CEllip.h"

CUser::CUser()
{
	//tmp
	POINTFLOAT initPos = { 100,100 };
	//
	mTower = new CTower(USERTOWER_POS);
	this->AddMyObjList(mTower);

	mPlayer = new CPlayer(initPos);
	this->AddMyObjList(mPlayer);

	mUnithead = new CRect({ 500, 350 });
	this->AddMyObjList(mUnithead);

}

CUser::~CUser()
{
}

void CUser::Update()
{
	mPlayer->Update();
}

void CUser::MSG_Key(UINT message, WPARAM wParam)
{
	mPlayer->Player_Message(message, wParam);
}

void CUser::Draw(HDC hdc)
{
	CGameObject* tmp = p_myobj;
	for (int i = 0; i < imyobjnum; i++) {
		tmp->Draw(hdc);
		tmp->DrawHP(hdc);
		tmp = tmp->next;
	}
}

POINTFLOAT CUser::GetPlayerPos()
{
	return mPlayer->GetPos();
}
