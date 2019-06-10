#include "pch.h"
#include "GameFramework.h"
CGameFramework::CGameFramework()
{
	msound = new CSound;
	msound->SoundSystem();

}
CGameFramework::~CGameFramework()
{
	msound->SoundStop(2);
}

void CGameFramework::Create(HWND hwnd, HWND htitlewnd, HINSTANCE hInst)
{

	msound->MyPlaySound(0, 1);//타이틀화면닫히고나서 부모창이 켜질때
	mhInst = hInst;
	mhWnd = hwnd;
	mhhTitleWnd = htitlewnd;

	pworld = new CWorld(hwnd);

	// 사운드 변수 넘겨주기
	pworld->SetSound(msound);

	HDC hdc = GetDC(hwnd);
	memdc = CreateCompatibleDC(hdc);
	ReleaseDC(hwnd, hdc);

	hpausebutton = (HBITMAP)LoadImage(NULL, L"Resource/button_pause.bmp", IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
}

void CGameFramework::Relese()
{
	msound->SoundStop(1); //부모창이 닫히고 타이틀창이 켜질때
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
	POINT mousepos = { LOWORD(lParam),HIWORD(lParam) };
	if (PtInRect(&BUTTONPAUSE_RNG, mousepos)) {
		if(message == WM_LBUTTONUP)
			DialogBox(mhInst, MAKEINTRESOURCE(IDD_DIALOGPAUSE), mhWnd, (DLGPROC)DialogProc);
		return;
	}
	else {
		if (pworld) pworld->MSG_Mouse(message, mousepos);
	}

}



void CGameFramework::Draw(HDC hdc)
{
	if (pworld) {
		pworld->Draw(hdc);

		// UI그리기
		HBITMAP hOld = (HBITMAP)SelectObject(memdc, hpausebutton);
		BitBlt(hdc, BUTTONPAUSE_RNG.left, BUTTONPAUSE_RNG.top, PAUSEBUTTONSIZE, PAUSEBUTTONSIZE,
			memdc, 0, 0, SRCCOPY);

		// 플레이어 정보에 관한 UI
		INT p_hp, p_ctshoot, p_ctAoE, p_ctshield, p_ctreturn;
		pworld->UI_GetPlayerInfo(&p_hp, &p_ctshoot, &p_ctAoE, &p_ctshield, &p_ctreturn);

		RECT UI_Rect = { 20,20,80,680 };
		FillRect(hdc, &UI_Rect , (HBRUSH)GetStockObject(WHITE_BRUSH));

		Rectangle(hdc, 30, 30, 70, 220);
		Rectangle(hdc, 30, 255, 70, 445);
		Rectangle(hdc, 30, 480, 70 ,520);
		Rectangle(hdc, 30, 530, 70, 570);
		Rectangle(hdc, 30, 580, 70, 620);
		Rectangle(hdc, 30, 630, 70, 670);


		if (pworld->IsEnding() != 0) {
			// 여기다가 엔딩장면 그려라~~

			RECT endRect = {0,200,1200,500};
			FillRect(hdc,&endRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
			HFONT myFont = CreateFont(100, 0, 0, 0, 10, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"궁서체");
			HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
			SetTextColor(hdc, RGB(255, 255, 0));
			SetBkMode(hdc, TRANSPARENT);

			switch (pworld->IsEnding()) {
			case 1:
				TextOut(hdc, 400, 300, L"VICTORY!", lstrlen(L"VICTORY!"));
				break;
			case 2:
				TextOut(hdc, 400, 300, L"  LOSE!", lstrlen(L"  LOSE!"));
				break;
			}

			SelectObject(hdc, oldFont);
			DeleteObject(myFont);
		}
	}

}


