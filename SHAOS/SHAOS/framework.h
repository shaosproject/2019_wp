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
#define PLAYER_RADIUS 10
const POINTFLOAT DIRVECTOR_LEFT = { -3,0 };
const POINTFLOAT DIRVECTOR_RIGHT = { 3,0 };
const POINTFLOAT DIRVECTOR_TOP = { 0,-3 };
const POINTFLOAT DIRVECTOR_BOTTOM = { 0,3 };
const POINTFLOAT DIRVECTOR_LT = { -2,-2 };
const POINTFLOAT DIRVECTOR_LB = { -2,2 };
const POINTFLOAT DIRVECTOR_RT = { 2,-2 };
const POINTFLOAT DIRVECTOR_RB = { 2,2 };
const POINTFLOAT DIRVECTOR_STOP = { 0,0 };
#pragma endregion

#define TURRET_RADIUS 30


#pragma region ABOUT_RECT
#define RECT_RADIUS 10
#define RECT_HP 100
#pragma endregion

#define MIN 0
#define MAX 200
