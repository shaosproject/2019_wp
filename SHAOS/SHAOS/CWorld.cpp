#include "pch.h"
#include "CWorld.h"



CWorld::CWorld(HWND hwnd)
{
	hbackgroundbmp = (HBITMAP)LoadImage(NULL, L"Resource/map.bmp", IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetClientRect(hwnd, &rcClient);
	
	// ��� dc�� ���� ��������
	HDC tmpdc = GetDC(hwnd);
	hUpdateDC = CreateCompatibleDC(tmpdc);
	hBackgroundDC = CreateCompatibleDC(tmpdc);
	hbackgroundsizebmp = CreateCompatibleBitmap(tmpdc, MAPSIZE_WIDTH, MAPSIZE_HEIGHT);
	ReleaseDC(hwnd, tmpdc);


	// hMapDC�� �� �̹����� ����
	hbackgroundOld = (HBITMAP)SelectObject(hBackgroundDC, hbackgroundbmp);
	hupdateOld = (HBITMAP)SelectObject(hUpdateDC, hbackgroundsizebmp);


	// �� �Ҵ�ޱ�
	pUserTeam = new CUser;
	pEnemyTeam = new CEnemy;

	// ����� ��ü ����Ʈ ����
	pUserTeam->SetOpponentObj(pEnemyTeam->GetMyObjList());
	pEnemyTeam->SetOpponentObj(pUserTeam->GetMyObjList());

	// �ʱ� ������Ʈ �Ҵ�
	pUserTeam->SetInitObj();
	pEnemyTeam->SetInitObj();

	gamestate = 0;	// ������
}


CWorld::~CWorld()
{
	// ��Ʈ�� ����
	DeleteObject(SelectObject(hUpdateDC, hbackgroundsizebmp));	// ��ȭ�� ����
	DeleteObject(SelectObject(hBackgroundDC, hbackgroundOld));	// ��� ����

	// dc ����
	DeleteDC(hUpdateDC);
	DeleteDC(hBackgroundDC);


	// �� ����
	delete pUserTeam;
	delete pEnemyTeam;

}

void CWorld::MSG_Mouse(UINT message, POINT clientmousepos)
{
	POINT worldmousepos =
	{ clientmousepos.x + iViewX - MIN_VIEWX,clientmousepos.y };

	pUserTeam->MSG_Mouse(message, worldmousepos);

}

void CWorld::MSG_Key(UINT message, WPARAM wParam, LPARAM lParam)
{
	pUserTeam->MSG_Key(message, wParam);
}

void CWorld::Update()
{
	if (pUserTeam->gameover) {
		if (gamestate == 0); // ���� �ֱ� 
		gamestate = 2;
		return;
	}
	if (pEnemyTeam->gameover) {
		if (gamestate == 0); // ���� �ֱ� 
		gamestate = 1;
		return;
	}

	pUserTeam->Update();
	pEnemyTeam->Update();
	iViewX = (INT)SET_VIEWX(pUserTeam->GetPlayerPos().x);	
}

void CWorld::Draw(HDC clientDC)
{
	BitBlt(hUpdateDC, 0, 0, MAPSIZE_WIDTH, MAPSIZE_HEIGHT,
		hBackgroundDC, 0, 0, SRCCOPY);


	// ��ü �׸���
	pUserTeam->Draw(hUpdateDC);
	pEnemyTeam->Draw(hUpdateDC);
	//----


	BitBlt(clientDC, 0, 0, rcClient.right, rcClient.bottom,
		hUpdateDC, iViewX - MIN_VIEWX, 0, SRCCOPY);
}

void CWorld::SetSound(CSound* sound)
{
	pUserTeam->SetSound(sound);
}

void CWorld::GetUIInfo(INT* ahp, INT* ct_shoot, INT* ct_AoE,
	INT* ct_shield, INT* ct_return, INT* towerhp)
{
	pUserTeam->GetUIInfo(ahp, ct_shoot, ct_AoE, ct_shield, ct_return, towerhp);
}

INT CWorld::IsEnding()
{
	return gamestate;
}
