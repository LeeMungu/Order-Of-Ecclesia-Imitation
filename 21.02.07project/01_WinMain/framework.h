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
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "DefineHeader.h"
#include "Figure.h"
#include "Random.h"
#include "Input.h"
#include "Math.h"
#include "ImageManager.h"

extern POINT _mousePosition;	//마우스 좌표
extern HWND	_hWnd;
extern HINSTANCE	_hInstance;


