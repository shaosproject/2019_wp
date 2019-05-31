#pragma once
#include "CTeam.h"
class CWorld
{
	HBITMAP hbackgroundbmp;		//map.bmp วฺต้
	BITMAP bgbmp;

	HDC hUpdateDC;
	HDC hBackgroundDC;

	HBITMAP hbackgroundsizebmp;
	HBITMAP hbackgroundOld, hupdateOld;
	RECT rcClient;

	CTeam* pUserTeam{ nullptr };
	CTeam* pEnemyTeam{ nullptr };


public:
	CWorld(HWND hwnd);
	~CWorld();

	
	void MSG_Mouse(UINT, WPARAM, LPARAM);
	void MSG_Key(UINT, WPARAM, LPARAM);



	void Draw(HDC);
};

