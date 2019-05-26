#pragma once
#include "CWorld.h"
class CGameFramework
{
	HINSTANCE		mhInst;
	HWND			mhWnd;
	HWND			mhhTitleWnd;

	// �������� ��ǥ�� �ѱ� �� ��� �ѱ���...
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
