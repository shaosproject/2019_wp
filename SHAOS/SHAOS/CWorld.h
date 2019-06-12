#pragma once
#include "CUser.h"
#include "CEnemy.h"

class CWorld
{
	HBITMAP hbackgroundbmp;		//map.bmp �ڵ�

	HDC hUpdateDC;
	HDC hBackgroundDC;

	HBITMAP hbackgroundsizebmp;
	HBITMAP hbackgroundOld, hupdateOld;
	RECT rcClient;


	CUser* pUserTeam{ nullptr };
	CEnemy* pEnemyTeam{ nullptr };

	INT iViewX;
	

	INT gamestate;	//0:���� 1:���� �� 2: ���� ��
	CSound* sound{ nullptr };
public:
	CWorld(HWND hwnd);
	~CWorld();

	
	void MSG_Mouse(UINT, POINT);
	void MSG_Key(UINT, WPARAM, LPARAM);

	void Update();
	
	void Draw(HDC);

	void SetSound(CSound*);

	void GetUIInfo(INT* ahp, INT* ct_shoot, INT* ct_AoE,
		INT* ct_shield, INT* ct_return, INT* towerhp, INT* ct_death);

	INT IsEnding();

	void OffPlayerMove();
};

