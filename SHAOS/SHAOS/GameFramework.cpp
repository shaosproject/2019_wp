#include "pch.h"
#include "GameFramework.h"
CGameFramework::CGameFramework()
{
}


CGameFramework::~CGameFramework()
{
}

void CGameFramework::Create(HWND hwnd, HWND htitlewnd, HINSTANCE hInst)
{
	mhInst = hInst;
	mhWnd = hwnd;
	mhhTitleWnd = htitlewnd;

	// 실패시 null을 리턴 
	HBITMAP hMap = (HBITMAP)LoadImage(NULL, L"Resource/map.bmp", IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


	pworld = new CWorld(hwnd, hMap);

}

void CGameFramework::Relese()
{
	delete pworld;
}

void CGameFramework::Update()
{
}

void CGameFramework::MSG_Mouse(UINT message, WPARAM wParam, LPARAM lParam)
{
	
}

void CGameFramework::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CGameFramework::Draw(HDC hdc)
{
	if (pworld) pworld->Draw(hdc);
}
