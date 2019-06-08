#pragma once
#include "CWorld.h"
#include "resource.h"
//#include "Sound.h"
void	CALLBACK	TimerProc(HWND, UINT, UINT, DWORD);
BOOL	CALLBACK    DialogProc(HWND, UINT, WPARAM, LPARAM);

class CGameFramework
{
	HINSTANCE		mhInst;
	HWND			mhWnd;
	HWND			mhhTitleWnd;



	HDC				memdc;
	HBITMAP			hpausebutton;

	// �������� ��ǥ�� �ѱ� �� ��� �ѱ���...
	CWorld* pworld{ nullptr };


public:
	//CSound* msound;
	CGameFramework();
	~CGameFramework();

	void Create(HWND hwnd, HWND htitlewnd, HINSTANCE hInst);//Init

	void Relese();

	void Update();

	void MSG_Key(UINT message, WPARAM wParam, LPARAM lParam);
	void MSG_Mouse(UINT message, WPARAM wParam, LPARAM lParam);

	void Draw(HDC hdc);

};
