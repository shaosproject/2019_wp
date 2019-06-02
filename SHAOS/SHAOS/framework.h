#pragma once

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

#define CLIENT_WIDTH 1200
#define CLIENT_HEIGHT 700

#define IDC_BUTTON_START 100
#define IDC_BUTTON_HELP 101
#define IDC_BUTTON_EXIT 102

#pragma region ABOUT_WORLD
#define MAX_VIEWX 3900
#define MIN_VIEWX 600
#define SET_VIEWX(plyx) ((plyx)<(MIN_VIEWX)?(MIN_VIEWX):((plyx)>(MAX_VIEWX)?(MAX_VIEWX):(plyx)))
#pragma endregion


#pragma region ABOUT_PLAYER
#define PLAYER_RADIUS 15
#define PLAYER_SPEED 3
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
#pragma endregion

#pragma region ABOUT_BUILDING
const POINTFLOAT USERTOWER_POS = { 325,350 };
const POINTFLOAT ENEMYTOWER_POS = { 4175,350 };

#define TOWER_TOP 270
#define TOWER_BOTTOM 430
#define TOWER_LEFT(x) x - 70
#define TOWER_RIGHT(x) x + 70

#define TURRET_RADIUS 30
#pragma endregion


#pragma region ABOUT_RECT
#define RECT_RADIUS 10
#define RECT_HP 100
#pragma endregion

#define MIN 0
#define MAX 200
