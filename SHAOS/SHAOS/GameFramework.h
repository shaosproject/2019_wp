#pragma once
#include "CWorld.h"
class CGameFramework
{
	HINSTANCE		mhInst;
	HWND			mhWnd;
	HWND			mhhTitleWnd;

	// 월드한테 좌표를 넘길 때 어디서 넘기지...
	CWorld			*pworld;


public:
	CGameFramework();
	~CGameFramework();

	void Create(HWND hwnd, HWND htitlewnd, HINSTANCE hInst);//Init

	void Relese();

	void Update();

	void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Draw(HDC hdc);

};
