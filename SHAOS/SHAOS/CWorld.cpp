#include "pch.h"
#include "CWorld.h"



CWorld::CWorld(HWND hwnd)
{
	hbackgroundbmp = (HBITMAP)LoadImage(NULL, L"Resource/map.bmp", IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetClientRect(hwnd, &rcClient);
	
	// 출력 dc의 성질 가져오기
	HDC tmpdc = GetDC(hwnd);
	hUpdateDC = CreateCompatibleDC(tmpdc);
	hBackgroundDC = CreateCompatibleDC(tmpdc);
	hbackgroundsizebmp = CreateCompatibleBitmap(tmpdc, MAPSIZE_WIDTH, MAPSIZE_HEIGHT);
	ReleaseDC(hwnd, tmpdc);


	// hMapDC는 맵 이미지를 선택
	hbackgroundOld = (HBITMAP)SelectObject(hBackgroundDC, hbackgroundbmp);
	hupdateOld = (HBITMAP)SelectObject(hUpdateDC, hbackgroundsizebmp);


	// 팀 할당받기
	pUserTeam = new CUser;
	pEnemyTeam = new CEnemy;

	// 상대편 객체 리스트 설정
	pUserTeam->SetOpponentObj(pEnemyTeam->GetMyObjList());
	pEnemyTeam->SetOpponentObj(pUserTeam->GetMyObjList());

	// 초기 오브젝트 할당
	pUserTeam->SetInitObj();
	pEnemyTeam->SetInitObj();

	gamestate = 0;	// 진행중
}


CWorld::~CWorld()
{
	// 비트맵 삭제
	DeleteObject(SelectObject(hUpdateDC, hbackgroundsizebmp));	// 도화지 삭제
	DeleteObject(SelectObject(hBackgroundDC, hbackgroundOld));	// 배경 삭제

	// dc 삭제
	DeleteDC(hUpdateDC);
	DeleteDC(hBackgroundDC);


	// 팀 해제
	delete pUserTeam;
	delete pEnemyTeam;

}

void CWorld::MSG_Mouse(UINT message, POINT clientmousepos)
{
	POINT worldmousepos =
	{ clientmousepos.x + iViewX - MIN_VIEWX,clientmousepos.y };

	pUserTeam->MSG_Mouse(message, worldmousepos);

}

void CWorld::MSG_Key(UINT message, WPARAM wParam, LPARAM lParam)
{
	pUserTeam->MSG_Key(message, wParam);
}

void CWorld::Update()
{
	if (pUserTeam->gameover) {
		if (gamestate == 0); // 사운드 넣기 
		gamestate = 2;
		return;
	}
	if (pEnemyTeam->gameover) {
		if (gamestate == 0); // 사운드 넣기 
		gamestate = 1;
		return;
	}

	pUserTeam->Update();
	pEnemyTeam->Update();
	iViewX = (INT)SET_VIEWX(pUserTeam->GetPlayerPos().x);	
}

void CWorld::Draw(HDC clientDC)
{
	BitBlt(hUpdateDC, 0, 0, MAPSIZE_WIDTH, MAPSIZE_HEIGHT,
		hBackgroundDC, 0, 0, SRCCOPY);


	// 객체 그리기
	pUserTeam->Draw(hUpdateDC);
	pEnemyTeam->Draw(hUpdateDC);
	//----


	BitBlt(clientDC, 0, 0, rcClient.right, rcClient.bottom,
		hUpdateDC, iViewX - MIN_VIEWX, 0, SRCCOPY);
}

void CWorld::SetSound(CSound* sound)
{
	pUserTeam->SetSound(sound);
}

void CWorld::GetUIInfo(INT* ahp, INT* ct_shoot, INT* ct_AoE,
	INT* ct_shield, INT* ct_return, INT* towerhp)
{
	pUserTeam->GetUIInfo(ahp, ct_shoot, ct_AoE, ct_shield, ct_return, towerhp);
}

INT CWorld::IsEnding()
{
	return gamestate;
}
