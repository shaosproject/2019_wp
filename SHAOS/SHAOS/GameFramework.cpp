#include "pch.h"
#include "GameFramework.h"
CGameFramework::CGameFramework()
{
	msound = new CSound;
	msound->SoundSystem();
}
CGameFramework::~CGameFramework()
{
}

void CGameFramework::Create(HWND hwnd, HWND htitlewnd, HINSTANCE hInst)
{
	msound->MyPlaySound(1, 2);//타이틀화면닫히고나서 부모창이 켜질때
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
	msound->SoundStop(2); //부모창이 닫히고 타이틀창이 켜질때
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

		// UI 정보 가져오기
		INT p_hp, p_ctshoot, p_ctAoE, p_ctshield, p_ctreturn, t_hp;
		pworld->GetUIInfo(&p_hp, &p_ctshoot, &p_ctAoE, &p_ctshield, &p_ctreturn, &t_hp);

		RECT UI_Rect = { 20,20,80,680 };
		FillRect(hdc, &UI_Rect , (HBRUSH)GetStockObject(WHITE_BRUSH));
		
		RECT hp_rect1 = { 30, 30, 70,220 };
		RECT thp_rect1 = { 30, 255, 70, 445};
		
		RECT hp_rect2 = { 30, 220 - p_hp * 190/ PLAYER_MAXHP, 70, 220 };
		RECT thp_rect2 = { 30, 445 - t_hp * 190 / TOWER_MAXHP, 70, 445  };



		FillRect(hdc, &hp_rect2, (HBRUSH)GetStockObject(GRAY_BRUSH));
		FillRect(hdc, &thp_rect2, (HBRUSH)GetStockObject(GRAY_BRUSH));

		FrameRect(hdc, &hp_rect1, (HBRUSH)GetStockObject(BLACK_BRUSH));
		FrameRect(hdc, &thp_rect1, (HBRUSH)GetStockObject(BLACK_BRUSH));


		Rectangle(hdc, 30, 480, 70 ,520);
		Rectangle(hdc, 30, 530, 70, 570);
		Rectangle(hdc, 30, 580, 70, 620);
		Rectangle(hdc, 30, 630, 70, 670);

		TextOut(hdc, 40, 230, L"HP", strlen("HP"));
		TextOut(hdc, 40, 455, L"HP", strlen("HP"));
		RECT Text = {40,230,50,300 };
		//DrawText(hdc,L"PLAYER", strlen("PLAYER"), &Text, DT_WORDBREAK | DT_VCENTER);
		

		// 광역기 쿨타임 가져오니까 화면 흔들림효과 넣을 수 있을 듯

		if (pworld->IsEnding() != 0) {
			// 여기다가 엔딩장면 그려라~~
			//msound->SoundStop(1);
			msound->SoundStop(2);


			RECT endRect = {0,200,1200,500};
			FillRect(hdc,&endRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
			HFONT myFont = CreateFont(100, 0, 0, 0, 10, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"궁서체");
			HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
			SetTextColor(hdc, RGB(255, 255, 0));
			SetBkMode(hdc, TRANSPARENT);

			switch (pworld->IsEnding()) {
			case 1:
				//msound->SoundStop(2);
				msound->MyPlaySound(6, 4);
				TextOut(hdc, 400, 300, L"VICTORY!", lstrlen(L"VICTORY!"));
				break;
			case 2:
				//msound->SoundStop(2);
				msound->MyPlaySound(5, 4);
				TextOut(hdc, 400, 300, L"  LOSE!", lstrlen(L"  LOSE!"));
				break;
			}

			SelectObject(hdc, oldFont);
			DeleteObject(myFont);
		}
	}

}


