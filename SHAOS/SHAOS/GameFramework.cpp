#include "pch.h"
#include "GameFramework.h"
CGameFramework::CGameFramework()
{
	msound = new CSound;
	msound->SoundSystem();

}
CGameFramework::~CGameFramework()
{
	msound->SoundStop(1);
}

void CGameFramework::Create(HWND hwnd, HWND htitlewnd, HINSTANCE hInst)
{

	msound->MyPlaySound(0, 0);//Ÿ��Ʋȭ��������� �θ�â�� ������
	mhInst = hInst;
	mhWnd = hwnd;
	mhhTitleWnd = htitlewnd;

	pworld = new CWorld(hwnd);

	HDC hdc = GetDC(hwnd);
	memdc = CreateCompatibleDC(hdc);
	ReleaseDC(hwnd, hdc);

	hpausebutton = (HBITMAP)LoadImage(NULL, L"Resource/button_pause.bmp", IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
}

void CGameFramework::Relese()
{
	msound->SoundStop(0); //�θ�â�� ������ Ÿ��Ʋâ�� ������
	DeleteObject(hpausebutton);
	DeleteDC(memdc);
	delete pworld;
	pworld = nullptr;
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
	if (message == WM_LBUTTONUP) {
		POINT mousepos = { LOWORD(lParam),HIWORD(lParam) };
		if (PtInRect(&BUTTONPAUSE_RNG, mousepos)) {
			DialogBox(mhInst, MAKEINTRESOURCE(IDD_DIALOGPAUSE), mhWnd, (DLGPROC)DialogProc);
			return;
		}
	}
	if (pworld) pworld->MSG_Mouse(message, wParam, lParam);
}



void CGameFramework::Draw(HDC hdc)
{
	if (pworld) {
		pworld->Draw(hdc);

		// UI�׸���
		HBITMAP hOld = (HBITMAP)SelectObject(memdc, hpausebutton);
		BitBlt(hdc, BUTTONPAUSE_RNG.left, BUTTONPAUSE_RNG.top, PAUSEBUTTONSIZE, PAUSEBUTTONSIZE,
			memdc, 0, 0, SRCCOPY);
	}
}


