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



	pworld = new CWorld(hwnd);

}

void CGameFramework::Relese()
{
	delete pworld;
}

void CGameFramework::Update()
{
	if (pworld) pworld->Update();
}

void CGameFramework::MSG_Key(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (pworld) pworld->MSG_Key(message, wParam, lParam);
}

void CGameFramework::MSG_Mouse(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (pworld) pworld->MSG_Mouse(message, wParam, lParam);
}

void CGameFramework::Draw(HDC hdc)
{
	if (pworld) pworld->Draw(hdc);
}
