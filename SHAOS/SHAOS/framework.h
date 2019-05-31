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
#include <math.h>

#define CLIENT_WIDTH 1200
#define CLIENT_HEIGHT 700

#define IDC_BUTTON_START 100
#define IDC_BUTTON_HELP 101
#define IDC_BUTTON_EXIT 102

#define PLAYER_RADIUS 10
#define TURRET_RADIUS 30

#define  PLAYER_SPEED 2

#define MIN 0
#define MAX 200