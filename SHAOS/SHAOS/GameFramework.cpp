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

	pworld = new CWorld;
}

void CGameFramework::Relese()
{
	delete pworld;
}

void CGameFramework::Update()
{
}

void CGameFramework::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CGameFramework::Draw(HDC hdc)
{

}
