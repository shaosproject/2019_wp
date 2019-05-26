#pragma once
class CWorld
{
	HBITMAP mhMapBit;
	BITMAP mMapBit;



public:
	CWorld();
	~CWorld();

	void Draw(HDC);
};

