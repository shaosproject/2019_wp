#include "pch.h"
#include "CUser.h"
#include "CPlayer.h"
#include "CRect.h"
#include "CEllip.h"
//#include "CDia.h"
//#include "CTri.h"

CUser::CUser()
{
	mTower = new CTower(USERTOWER_POS, TEAM::USER, nullptr);
	p_myobjlist = mTower;
	p_myobjlist->next = p_myobjlist->prev = p_myobjlist;

	iunitgentime = FRAMETIME * 100;
}

CUser::~CUser()
{
}

void CUser::SetOpponentObj(CGameObject* objlist)
{
	p_opponentobjlist = objlist;


	//tmp
	POINTFLOAT initPos = { 100,100 };
	//
	mPlayer = new CPlayer(initPos, TEAM::USER, p_opponentobjlist);
	this->AddMyObjList(mPlayer);

	mUnithead = new CRect({ 500, 350 }, TEAM::USER, p_opponentobjlist);
	this->AddMyObjList(mUnithead);

}

void CUser::Update()
{
	if (iunitgentime) iunitgentime -= FRAMETIME;
	else {
		UnitGen();
		iunitgentime = FRAMETIME * 100;
	}
	mPlayer->Update();
}

void CUser::MSG_Key(UINT message, WPARAM wParam)
{
	mPlayer->MSG_Key(message, wParam);
}

void CUser::MSG_Mouse(UINT message, POINT mousepos)
{
	// 상대편 obj 영역들을 검사해서 마우스 좌표에 있으면
	// 플레이어에게 신호를 보냄

	switch (message) {
	case WM_LBUTTONUP:
		mPlayer->MSG_MouseUp(mousepos);
		break;
	case WM_LBUTTONDOWN:
		mPlayer->MSG_MouseDown(mousepos);
		break;
	case WM_MOUSEMOVE:
		mPlayer->MSG_MouseMove(mousepos);
		break;

	}
}

void CUser::UnitGen()
{
}

void CUser::Draw(HDC hdc)
{
	CGameObject* tmp = p_myobjlist;
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
