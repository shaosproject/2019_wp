#include "pch.h"
#include "CWorld.h"



CWorld::CWorld(HWND hwnd, HBITMAP hMap) :mhMapBit(hMap)
{
	// ��Ʈ�� ���� ����
	GetObject(hMap, sizeof(BITMAP), &mMapBit);
	GetClientRect(hwnd, &rcClient);

	
	// ��� dc�� ���� �÷� ������ ������ dc����
	HDC tmpdc = GetDC(hwnd);

	hUpdateDC = CreateCompatibleDC(tmpdc);
	hMapDC = CreateCompatibleDC(tmpdc);
	
	ReleaseDC(hwnd, tmpdc);


	// hMapDC�� �� �̹����� ����
	hMapOld = (HBITMAP)SelectObject(hMapDC, hMap);
	
	
	// �� �Ҵ�ޱ�
	pUserTeam = new CTeam;
	pEnemyTeam = new CTeam;

}


CWorld::~CWorld()
{
	delete pUserTeam;
	delete pEnemyTeam;

}

void CWorld::Draw(HDC clientDC)
{
	// hdc = ui�߰��ϱ� ��, ���dc�� ���� ũ���� dc

	HBITMAP htmp = CreateCompatibleBitmap(hMapDC, mMapBit.bmWidth, mMapBit.bmHeight);
	SelectObject(hUpdateDC, htmp);
	BitBlt(hUpdateDC, 0, 0, mMapBit.bmWidth, mMapBit.bmHeight,
		hMapDC, 0, 0, SRCCOPY);

	BitBlt(clientDC, 0, 0, rcClient.right, rcClient.bottom,
		hUpdateDC, 0, 0, SRCCOPY);
}
