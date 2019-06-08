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

	iunitgentime = FRAMETIME * 200;
}

CUser::~CUser()
{
}

void CUser::SetInitObj()
{
	POINTFLOAT tmp = {
		(INT)PLAYER_DEFAULT_POSITION.x,
		(INT)PLAYER_DEFAULT_POSITION.y
	};
	
	mPlayer = new CPlayer(tmp, TEAM::USER, p_opponentobjlist);
	this->AddMyObjList(mPlayer);

	CUnit* unit = new CRect(ptUnitSponPos, TEAM::USER, p_opponentobjlist);
	this->AddMyObjList(unit);

}

void CUser::Update()
{
	// ���� ��
	if (iunitgentime) iunitgentime -= FRAMETIME;
	else {
		if (this->imyobjnum < 6) {
			UnitGen();
			iunitgentime = FRAMETIME * 200;
		}
	}

	// �׿����� ������Ʈ
	CGameObject* tmp = nullptr;
	while (tmp != p_myobjlist) {
		if (!tmp) tmp = p_myobjlist;
		
		tmp->Update();

		tmp = tmp->next;
	}
}

void CUser::MSG_Key(UINT message, WPARAM wParam)
{
	mPlayer->MSG_Key(message, wParam);
}

void CUser::MSG_Mouse(UINT message, POINT mousepos)
{
	// ����� obj �������� �˻��ؼ� ���콺 ��ǥ�� ������
	// �÷��̾�� ��ȣ�� ����

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
	CUnit* unit = new CRect(ptUnitSponPos, TEAM::USER, p_opponentobjlist);
	this->AddMyObjList(unit);

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
