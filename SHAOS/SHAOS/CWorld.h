#pragma once
#include "CUser.h"
#include "CEnemy.h"

class CWorld
{
	HBITMAP hbackgroundbmp;		//map.bmp �ڵ�
	BITMAP bgbmp;

	HDC hUpdateDC;
	HDC hBackgroundDC;

	HBITMAP hbackgroundsizebmp;
	HBITMAP hbackgroundOld, hupdateOld;
	RECT rcClient;

	CUser* pUserTeam{ nullptr };
	CEnemy* pEnemyTeam{ nullptr };
	
	INT iViewX;

public:
	CWorld(HWND hwnd);
	~CWorld();

	
	void MSG_Mouse(UINT, WPARAM, LPARAM);
	void MSG_Key(UINT, WPARAM, LPARAM);

	void Update();

	void Draw(HDC);
};

