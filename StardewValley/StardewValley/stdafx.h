// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
#include <map>

using namespace std;

typedef struct tagSaveData
{
	int	selected_player_id;
	int maxHP;
	int score;
} SAVE_DATA;

typedef struct soundVolume
{
	float bgm;
	float effect;
} SOUND_VOLUME;

typedef struct tagFloatPoint
{
	float x;
	float y;

	tagFloatPoint() { x = 0; y = 0; }
	//tagFloatPoint(float _x, float _y) { x = _x; y = _y; }
} FPOINT;
typedef struct mapSize
{
	int mapSizeX;
	int mapSizeY;
}MAP_SIZE;


#define PRIVATESYNTHESIZE(varType, varName, funcName)\
private: varType varName;\
public: varType get##funcName() { return varName; }\
public: void set##funcName(varType var) { varName = var; }

#define SYNTHESIZE(varType, varName, funcName)\
protected: varType varName;\
public: varType get##funcName() { return varName; }\
public: void set##funcName(varType var) { varName = var; }

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "camera.h"
#include "DataManager.h"
#include "txtData.h"
#include "timeManager.h"
#include "keyManager.h"
#include "imageManager.h"
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "sceneManager.h"
#include "utils.h"
#include "mapCamera.h"
#include "gametime.h"
#include "soundManager.h"
//#include "effectManager.h"
#include "objectManager.h"
#include "resource.h"

//파일 경로 수정
#include <shlwapi.h> 
#pragma comment(lib, "shlwapi")

//#define FULL_SCREEN
#define MAP_TOOL // FULL_SCREEN, WINDOW_SCREEN, MAP_TOOL 선택

#ifdef FULL_SCREEN
#define	WINSTYLE	WS_POPUPWINDOW | WS_MAXIMIZE
#define WINSTARTX 0
#define WINSTARTY 0
#define WINSIZEX GetSystemMetrics(SM_CXSCREEN)
#define WINSIZEY GetSystemMetrics(SM_CYSCREEN)

#elif defined MAP_TOOL
#define	WINSTYLE	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX |WS_CLIPCHILDREN
#define WINSTARTX	50
#define WINSTARTY	50
#define WINSIZEX	1280
#define WINSIZEY	800

//WINDOW_SCREEN
#else
#define	WINSTYLE	WS_OVERLAPPEDWINDOW
#define WINSTARTX 50
#define WINSTARTY 50
#define WINSIZEX 600
#define WINSIZEY 800

#endif

#define PI 3.141592f
//#define MAPSIZEX 3200
//#define MAPSIZEY 3200
#define GAME_SCALAR 4

#define SAFE_DELETE(p)	{ if (p) delete p; p = NULL; }
#define SAFE_DELETE_ARRAY(p)	{ if (p) delete[] p; p = NULL; }

#define RANDOM randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define DATAMANAGER DataManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define PLAYTIMEMANAGER gametime::getSingleton()
#define CAMERA camera::getSingleton()
#define CAMERAMANAGER mapCamera::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
//#define EFFECTMANAGER effectManager::getSingleton()
#define OBJMANAGER objectManager::getSingleton()

extern HINSTANCE	g_hInstance;
extern HWND			g_hWnd;
extern SAVE_DATA	g_saveData;
extern MAP_SIZE		g_mapSize;
extern SOUND_VOLUME g_soundVolume;
extern POINT		g_ptMouse;

extern HWND			g_hMapTool;
extern HWND			g_hWndChildSample;
extern HWND			g_hWndChildSampleTop;

extern int g_wndCount;
extern RECT g_rc;

extern HCURSOR g_hCursor;
extern HCURSOR g_hPrevCursor;
extern WNDCLASS wndClass;