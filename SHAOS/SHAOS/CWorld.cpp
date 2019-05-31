#include "pch.h"
#include "CWorld.h"



CWorld::CWorld(HWND hwnd, HBITMAP hMap) :mhMapBit(hMap)
{
	// 비트맵 정보 저장
	GetObject(hMap, sizeof(BITMAP), &mMapBit);
	GetClientRect(hwnd, &rcClient);

	
	// 출력 dc와 같은 컬러 포맷을 가지는 dc생성
	HDC tmpdc = GetDC(hwnd);

	hUpdateDC = CreateCompatibleDC(tmpdc);
	hMapDC = CreateCompatibleDC(tmpdc);
	
	ReleaseDC(hwnd, tmpdc);


	// hMapDC는 맵 이미지를 선택
	hMapOld = (HBITMAP)SelectObject(hMapDC, hMap);
	
	
	// 팀 할당받기
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
	// hdc = ui추가하기 전, 출력dc와 같은 크기의 dc

	HBITMAP htmp = CreateCompatibleBitmap(hMapDC, mMapBit.bmWidth, mMapBit.bmHeight);
	SelectObject(hUpdateDC, htmp);
	BitBlt(hUpdateDC, 0, 0, mMapBit.bmWidth, mMapBit.bmHeight,
		hMapDC, 0, 0, SRCCOPY);

	BitBlt(clientDC, 0, 0, rcClient.right, rcClient.bottom,
		hUpdateDC, 0, 0, SRCCOPY);
}
