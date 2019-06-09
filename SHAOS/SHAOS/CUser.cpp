#include "pch.h"
#include "CUser.h"
#include "CPlayer.h"

#include "CRect.h"
#include "CEllip.h"

CUser::CUser()
{
	mTower = new CTower(USERTOWER_POS, TEAM::USER, nullptr);
	p_myobjlist = mTower;
	p_myobjlist->next = p_myobjlist->prev = p_myobjlist;

	iunitgentime = FRAMETIME * 500;
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

}

void CUser::Update()
{
	if (gameover) return;

	// ���� ��
	if (iunitgentime) iunitgentime -= FRAMETIME;
	else {
		if (this->imyobjnum < 10) {
			UnitGen();
			iunitgentime = FRAMETIME * 300;
		}
	}

	// �׿����� ������Ʈ
	CGameObject* tmp = p_myobjlist;
	for (int i = 0; i < imyobjnum; i++) {

		tmp->Update();

		if (tmp->IsDelete()) {
			if (tmp == p_myobjlist) {
				gameover = TRUE;
				continue;
			}

			CGameObject* delp = tmp;
			tmp = tmp->next;
			DeleteInList(delp);
			continue;
		}

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
	CUnit* unit1 = new CRect(ptUnitSponPos1, TEAM::USER, p_opponentobjlist);
	this->AddMyObjList(unit1);

	CUnit* unit2 = new CRect(ptUnitSponPos2, TEAM::USER, p_opponentobjlist);
	this->AddMyObjList(unit2);

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
