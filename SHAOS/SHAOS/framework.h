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

const RECT BUTTONPAUSE_RNG = { CLIENT_WIDTH - 50, 10,CLIENT_WIDTH - 10, 50 };
#define PAUSEBUTTONSIZE 40
#define SKILLICONSIZE 40



const HBRUSH hUIBARBRUSH = CreateSolidBrush(RGB(102, 153, 204));
const HPEN hENDINGWHITEPEN = CreatePen(PS_SOLID, 10, RGB(255, 255, 255));
enum class TEAM {
	USER, ENEMY
};


#pragma region ABOUT_WORLD

#define MAPSIZE_WIDTH 3700
#define MAPSIZE_HEIGHT 700

const RECT USERRNG = { 0,0,650,700 };
//const RECT WALL_LT = { 650,0,750,270 };
//const RECT WALL_LB = { 650,430,750,700 };
//const RECT WALL_RT = { 2950,0,3050,270 };
//const RECT WALL_RB = { 2950,430,3050,700 };

#define MIN_VIEWX 600
#define MAX_VIEWX MAPSIZE_WIDTH - MIN_VIEWX
#define SET_VIEWX(plyx) ((plyx)<(MIN_VIEWX)?(MIN_VIEWX):((plyx)>(MAX_VIEWX)?(MAX_VIEWX):(plyx)))

#pragma endregion



#pragma region ABOUT_PLAYER
const POINT PLAYER_DEFAULT_POSITION = { 500,350 };

#define PLAYER_RADIUS 15
#define PLAYER_SPEED 3
#define PLAYER_ROOTSPEED (PLAYER_SPEED/1.4)
#define	PLAYER_CENTER2VERTAX 30*1.7
#define PLAYER_HALFSIDE 30 * 1.5
#define PLAYER_CENTER2SIDE 15 * 1.7

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
#define MAX_CLIENTX (MAPSIZE_WIDTH - PLAYER_RADIUS)
#define MIN_CLIENTX PLAYER_RADIUS
#define MAX_CLIENTY (MAPSIZE_HEIGHT - PLAYER_RADIUS)
#define MIN_CLIENTY PLAYER_RADIUS
#define PLAY_CLIENTX(pcx) ((pcx)<MIN_CLIENTX?MIN_CLIENTX:((pcx>MAX_CLIENTX)?MAX_CLIENTX:pcx))
#define PLAY_CLIENTY(pcy) ((pcy)<MIN_CLIENTY?MIN_CLIENTY:((pcy>MAX_CLIENTY)?MAX_CLIENTY:pcy))

const HBRUSH hRTBRUSH = CreateSolidBrush(RGB(60, 100, 250));
const HBRUSH hIAOEBRUSH= CreateSolidBrush(RGB(255, 69, 0));
const HBRUSH hIAOEBRUSH2 = CreateSolidBrush(RGB(255, 0, 0));
const HBRUSH hSDBRUSH = CreateSolidBrush(RGB(0, 200, 200));

#define COOLTIME_SHOOT		(FRAMETIME * 300)
#define COOLTIME_AOE		(FRAMETIME * 500)
#define COOLTIME_SHIELD		(FRAMETIME * 200)
#define COOLTIME_RETURN		(FRAMETIME * 2000)
#define CASTINGTIME_RETURN	(FRAMETIME * 100)
#define ACTIVETIME_SHIELD	(FRAMETIME * 100)

#define PLAYER_BULLETDAMAGE 10
#define PLAYER_AOEDAMAGE 40
#define PLAYER_ATTACK_RANGE 200
#define SHIELD_RAD 20

const HBRUSH hSELECTEDBRUSH = CreateSolidBrush(RGB(255, 0, 0));
const HBRUSH hINRANGEBRUSH = CreateSolidBrush(RGB(0, 255, 0));

#define PLAYER_EFFECTTIME_AOE (FRAMETIME * 15)
#define PLAYER_EFFECTTIME_DEATH (FRAMETIME* 500)
#define PLAYER_SHOOT_LENGTH 200
#define PLAYER_SHOOTDAMAGE 70

const HPEN hPLAYERSHOOTPEN = CreatePen(PS_SOLID, 50, RGB(255, 255, 51));
const HBRUSH hPLAYERSHOOTCIRBRUSH = CreateSolidBrush(RGB(255, 255, 51));
const HBRUSH hPLAYERSHOOTRECTBRUSH = CreateSolidBrush(RGB(255, 204, 0));

#pragma endregion




#pragma region ABOUT_BUILDING
const POINTFLOAT USERTOWER_POS = { 325,350 };
const POINTFLOAT ENEMYTOWER_POS = { 3375,350 };

#define TOWER_RADIUS 65
#define TOWER_HALFSIDE TOWER_RADIUS * 1.5
#define TOWER_CENTER2VERTAX TOWER_RADIUS * 1.7
#define TOWER_CENTER2SIDE TOWER_CENTER2VERTAX / 2

#define TOWER_EFFECTTIME_DEATH (FRAMETIME * 150)

const HBRUSH hTWBRUSH = CreateSolidBrush(RGB(255, 255, 255));
const HBRUSH hUSERTOWERCIRCLEBRUSH = CreateSolidBrush(RGB(0, 0, 92));
const HBRUSH hENEMYTOWERCIRCLEBRUSH = CreateSolidBrush(RGB(92, 0, 0));


const POINTFLOAT TURRET1_POS = { 1850,350 };
const POINTFLOAT TURRET2_POS = { 2315,80 };
const POINTFLOAT TURRET3_POS = { 2315,620 };
const POINTFLOAT TURRET4_POS = { 2775,350 };
#define TURRET_RADIUS 70

const RECT rcTURRET1 = {
	TURRET1_POS.x - TURRET_RADIUS,
	TURRET1_POS.y - TURRET_RADIUS,
	TURRET1_POS.x + TURRET_RADIUS,
	TURRET1_POS.y + TURRET_RADIUS
};
const RECT rcTURRET2 = {
	TURRET2_POS.x - TURRET_RADIUS,
	TURRET2_POS.y - TURRET_RADIUS,
	TURRET2_POS.x + TURRET_RADIUS,
	TURRET2_POS.y + TURRET_RADIUS
}; 
const RECT rcTURRET3 = {
	TURRET3_POS.x - TURRET_RADIUS,
	TURRET3_POS.y - TURRET_RADIUS,
	TURRET3_POS.x + TURRET_RADIUS,
	TURRET3_POS.y + TURRET_RADIUS
}; 
const RECT rcTURRET4 = {
	TURRET4_POS.x - TURRET_RADIUS,
	TURRET4_POS.y - TURRET_RADIUS,
	TURRET4_POS.x + TURRET_RADIUS,
	TURRET4_POS.y + TURRET_RADIUS
};

#define TURRET_BULLETDAMAGE 25
#define TURRET_ATTACK_RANGE 350
#define TURRET_EFFECTTIME_DEATH (FRAMETIME * 50)

const HBRUSH hTRBRUSH = CreateSolidBrush(RGB(139, 26, 26));
//const HBRUSH hTRBRUSH2 = CreateSolidBrush(RGB(255, 220, 200));
//const HBRUSH hTRBRUSH3 = CreateSolidBrush(RGB(255, 220, 200));
//const HBRUSH hTRBRUSH4 = CreateSolidBrush(RGB(255, 220, 200));
const HPEN hREDPEN = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));



#pragma endregion


#pragma region ABOUT_UNIT
const HBRUSH hUSERUNITBRUSH = CreateSolidBrush(RGB(153, 217, 231));
const HBRUSH hENEMYUNITBRUSH = CreateSolidBrush(RGB(255, 174, 201));

#define UNIT_RECOGRNGRADIUS 300
#define UNIT_EFFECTTIME_DEATH (FRAMETIME*50)

#define RECT_RADIUS 10
#define ELLIP_RADIUS 10
#define DIA_SHORTRADIUS 8
#define TRI_INNERCIRCLERADIUS 10

#define RECT_DAMAGE 15
#define ELLIP_BULLETDAMAGE 10
#define DIA_ATTACKDAMAGE 30
#define TRI_ATTACKDAMAGE 30

#define DIA_SPEED 2


const HBRUSH hDIAATTACKBRUSH = CreateSolidBrush(RGB(75, 255, 150));
const HBRUSH hTIRATTACBRUSH = CreateSolidBrush(RGB(100, 100, 230));
#pragma endregion

#pragma region ABOUT_HP

#define GETHPBAR(crthp, objwidth, maxhp) (crthp * objwidth) / maxhp
const HBRUSH hHPBRUSH = CreateSolidBrush(RGB(60, 255, 30));

#define RECOVERAMOUNT 1

#define TOWER_MAXHP 1500
#define PLAYER_MAXHP 300
#define TURRET_MAXHP 700

#define RECT_MAXHP 150
#define ELLIP_MAXHP 200
#define DIA_MAXHP 100
#define TRI_MAXHP 300

#pragma endregion

#define BULLET_SPEED 15
#define BULLET_RADIUS 3
