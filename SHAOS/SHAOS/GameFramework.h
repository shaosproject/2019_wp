#pragma once
#include "CWorld.h"
#include "resource.h"
class CGameFramework
{
	HINSTANCE		mhInst;
	HWND			mhWnd;
	HWND			mhhTitleWnd;

	// 월드한테 좌표를 넘길 때 어디서 넘기지...
	CWorld* pworld{ nullptr };


public:
	CGameFramework();
	~CGameFramework();

	void Create(HWND hwnd, HWND htitlewnd, HINSTANCE hInst);//Init

	void Relese();

	void Update();

	void MSG_Key(UINT message, WPARAM wParam, LPARAM lParam);
	void MSG_Mouse(UINT message, WPARAM wParam, LPARAM lParam);

	void Draw(HDC hdc);

};
