#pragma once
#include "CTeam.h"
class CWorld
{
	HBITMAP mhMapBit;		//map.bmp �ڵ�
	BITMAP mMapBit;			//map.bmp ����
	HDC hUpdateDC;
	HDC hMapDC;
	HBITMAP hMapOld, hUdtOld;
	RECT rcClient;

	CTeam* pUserTeam{ nullptr };
	CTeam* pEnemyTeam{ nullptr };


public:
	CWorld(HWND hwnd, HBITMAP hMap);
	~CWorld();

	void Draw(HDC);
	void MSG_Mouse();
	void MSG_Key();
};

