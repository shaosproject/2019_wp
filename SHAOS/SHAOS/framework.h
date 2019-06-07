﻿#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cmath>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define CLIENT_WIDTH 1200
#define CLIENT_HEIGHT 700

#define FRAMETIME 16

#define IDC_BUTTON_START 100
#define IDC_BUTTON_HELP 101
#define IDC_BUTTON_EXIT 102

#define PAUSEBUTTONSIZE 40
const RECT BUTTONPAUSE_RNG = { CLIENT_WIDTH - 50, 10,CLIENT_WIDTH - 10, 50 };

enum class TEAM {
	USER, ENEMY
};


#pragma region ABOUT_WORLD

#define MAPSIZE_WIDTH 3700
#define MAPSIZE_HEIGHT 700

const RECT USERRNG = { 0,0,650,700 };
const RECT WALL_LT = { 650,0,750,270 };
const RECT WALL_LB = { 650,430,750,700 };
const RECT WALL_RT = { 2950,0,3050,270 };
const RECT WALL_RB = { 2950,430,3050,700 };

#define MIN_VIEWX 600
#define MAX_VIEWX MAPSIZE_WIDTH - MIN_VIEWX
#define SET_VIEWX(plyx) ((plyx)<(MIN_VIEWX)?(MIN_VIEWX):((plyx)>(MAX_VIEWX)?(MAX_VIEWX):(plyx)))

#pragma endregion



#pragma region ABOUT_PLAYER
#define PLAYER_RADIUS 15
#define PLAYER_SPEED 4
#define PLAYER_ROOTSPEED PLAYER_SPEED/1.4

const POINTFLOAT DIRVECTOR_LEFT = { -PLAYER_SPEED,0 };
const POINTFLOAT DIRVECTOR_RIGHT = { PLAYER_SPEED,0 };
const POINTFLOAT DIRVECTOR_TOP = { 0,-PLAYER_SPEED };
const POINTFLOAT DIRVECTOR_BOTTOM = { 0,PLAYER_SPEED };
const POINTFLOAT DIRVECTOR_LT = { -PLAYER_ROOTSPEED,-PLAYER_ROOTSPEED };
const POINTFLOAT DIRVECTOR_LB = { -PLAYER_ROOTSPEED,PLAYER_ROOTSPEED };
const POINTFLOAT DIRVECTOR_RT = { PLAYER_ROOTSPEED,-PLAYER_ROOTSPEED };
const POINTFLOAT DIRVECTOR_RB = { PLAYER_ROOTSPEED,PLAYER_ROOTSPEED };
const POINTFLOAT DIRVECTOR_STOP = { 0,0 };

#define PLAY_ELLIPSE_RAD 3
#define MAX_CLIENTX MAPSIZE_WIDTH - PLAYER_RADIUS
#define MIN_CLIENTX PLAYER_RADIUS
#define MAX_CLIENTY MAPSIZE_HEIGHT - PLAYER_RADIUS
#define MIN_CLIENTY PLAYER_RADIUS
#define PLAY_CLIENTX(pcx) ((pcx)<MIN_CLIENTX?MIN_CLIENTX:((pcx>MAX_CLIENTX)?MAX_CLIENTX:pcx))
#define PLAY_CLIENTY(pcy) ((pcy)<MIN_CLIENTY?MIN_CLIENTY:((pcy>MAX_CLIENTY)?MAX_CLIENTY:pcy))

#define SHIELD_RAD 20
const HBRUSH hRTBRUSH = CreateSolidBrush(RGB(60, 100, 250));


#define COOLTIME_SHOOT		FRAMETIME * 100
#define COOLTIME_AOE		FRAMETIME * 100
#define COOLTIME_SHIELD		FRAMETIME * 100
#define COOLTIME_RETURN		FRAMETIME * 100
#define CASTINGTIME_RETURN	FRAMETIME * 150
#define ACTIVETIME_SHIELD	FRAMETIME * 50

#define PLAYER_BULLETDAMAGE 10
#define PLAYER_AOEDAMAGE 10
#define PLAYER_ATTACK_RANGE 150

const HBRUSH hSELECTEDBRUSH = CreateSolidBrush(RGB(255, 0, 0));

#pragma endregion




#pragma region ABOUT_BUILDING
const POINTFLOAT USERTOWER_POS = { 325,350 };
const POINTFLOAT ENEMYTOWER_POS = { 3375,350 };

#define TOWER_TOP 270
#define TOWER_BOTTOM 430
#define TOWER_LEFT(x) x - 70
#define TOWER_RIGHT(x) x + 70

#define TURRET_RADIUS 70
#pragma endregion


#pragma region ABOUT_UNIT
#define RECT_RADIUS 10
#define ELLIP_RADIUS 10
#define DIA_SHORTRADIUS 10
#define TRI_INNERCIRCLERADIUS 10
#pragma endregion


#define MIN 0
#define MAX 200

#pragma region ABOUT_HP

#define GETHPBAR(crthp, objwidth, maxhp) (crthp * objwidth) / maxhp
const HBRUSH hHPBRUSH = CreateSolidBrush(RGB(60, 255, 30));

#define RECOVERAMOUNT 1

#define TOWER_MAXHP 100
#define PLAYER_MAXHP 100
#define TURRET_MAXHP 100
#define RECT_MAXHP 100
#define ELLIP_MAXHP 100
#define DIA_MAXHP 100
#define TRI_MAXHP 100

#pragma endregion
