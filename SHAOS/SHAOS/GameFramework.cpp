#include "pch.h"
#include "GameFramework.h"
CGameFramework::CGameFramework()
{
}
CGameFramework::~CGameFramework()
{
	PlaySound(0, NULL, 0);
}

void CGameFramework::Create(HWND hwnd, HWND htitlewnd, HINSTANCE hInst)
{
	PlaySound(L"Game_BGM.wav", NULL, SND_ASYNC | SND_LOOP);//타이틀화면닫히고나서 부모창이 켜질때
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
	PlaySound(0, NULL, 0); //부모창이 닫히고 타이틀창이 켜질때
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

		// UI그리기
		HBITMAP hOld = (HBITMAP)SelectObject(memdc, hpausebutton);
		BitBlt(hdc, BUTTONPAUSE_RNG.left, BUTTONPAUSE_RNG.top, PAUSEBUTTONSIZE, PAUSEBUTTONSIZE,
			memdc, 0, 0, SRCCOPY);
	}
}


