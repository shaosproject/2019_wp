#include "pch.h"
#include "CWorld.h"



CWorld::CWorld(HWND hwnd)
{
	hbackgroundbmp = (HBITMAP)LoadImage(NULL, L"Resource/map.bmp", IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hbackgroundbmp, sizeof(BITMAP), &bgbmp);
	GetClientRect(hwnd, &rcClient);
	
	// ��� dc�� ���� ��������
	HDC tmpdc = GetDC(hwnd);
	hUpdateDC = CreateCompatibleDC(tmpdc);
	hBackgroundDC = CreateCompatibleDC(tmpdc);
	hbackgroundsizebmp = CreateCompatibleBitmap(tmpdc, bgbmp.bmWidth, bgbmp.bmHeight);
	ReleaseDC(hwnd, tmpdc);


	// hMapDC�� �� �̹����� ����
	hbackgroundOld = (HBITMAP)SelectObject(hBackgroundDC, hbackgroundbmp);
	hupdateOld = (HBITMAP)SelectObject(hUpdateDC, hbackgroundsizebmp);

	// �� �Ҵ�ޱ�
	pUserTeam = new CUser;
	pEnemyTeam = new CEnemy;

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

void CWorld::MSG_Mouse(UINT message, WPARAM wParam, LPARAM lParam)
{

}

void CWorld::MSG_Key(UINT message, WPARAM wParam, LPARAM lParam)
{
	pUserTeam->MSG_Key(message, wParam);
}

void CWorld::Update()
{
	iViewX = (INT)SET_VIEWX(pUserTeam->GetPlayerPos().x);	
	pUserTeam->Update();
}

void CWorld::Draw(HDC clientDC)
{

	BitBlt(hUpdateDC, 0, 0, bgbmp.bmWidth, bgbmp.bmHeight,
		hBackgroundDC, 0, 0, SRCCOPY);
	
	// ��ü �׸���
	
	pUserTeam->Draw(hUpdateDC);
	
	//----
	// �÷��̾��� ��ǥ ���� ����
	
	BitBlt(clientDC, 0, 0, rcClient.right, rcClient.bottom,
		hUpdateDC, iViewX - MIN_VIEWX, 0, SRCCOPY);
}
