// LostCastle.cpp: 응용 프로그램의 진입점을 정의합니다.
//
#include "stdafx.h"
#include "StardewValley.h"
#include "mainGame.h"

HINSTANCE	g_hInstance;	// 프로그램 인스턴스 핸들
HINSTANCE	g_hInstance2;	// 프로그램 인스턴스 핸들
HWND		g_hWnd;			// 윈도우 핸들
LPTSTR		g_lpszClass = (LPTSTR)TEXT("Stardew Valley");
char		g_szText[128] = "";
POINT		g_ptMouse = { 0, 0 };
mainGame	g_mainGame;


HWND g_hMapTool;
HWND g_hWndChildSample;

int g_wndCount =0;

RECT g_rc;

// 사운드 볼륨
SOUND_VOLUME g_soundVolume;
// save data
SAVE_DATA	g_saveData;
MAP_SIZE	g_mapSize;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildMapSampleProc(HWND, UINT, WPARAM, LPARAM);

HCURSOR g_hCursor;
HCURSOR g_hPrevCursor;

WNDCLASS wndClass;


void SetWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstacne,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	g_hInstance = _hInstance;

	MSG message;

	//WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;		// 클래스 여분 메모리
	wndClass.cbWndExtra = 0;		// 윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(NULL);	// 백그라운드 색상
	wndClass.hCursor = LoadCursor(g_hInstance, MAKEINTRESOURCE(IDC_CURSOR1));	// 커서				// 커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// 아이콘
	wndClass.hInstance = _hInstance;								// 인스턴스 핸들
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						// 윈도우 프로시저
	wndClass.lpszClassName = g_lpszClass;							// 클래스 이름
	wndClass.lpszMenuName =NULL;		// 메뉴 이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						// 윈도우 스타일
	RegisterClass(&wndClass); // 윈도우 클래스 등록
	
	// 윈도우 생성
	g_hWnd = CreateWindow(g_lpszClass,
		g_lpszClass,
		WINSTYLE,
		WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY,
		NULL,
		(HMENU)NULL,
		_hInstance,
		NULL);

	// 화면 작업 사이즈 영역 계산
	SetWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
	//#endif

	// 윈도우 출력
	ShowWindow(g_hWnd, nCmdShow);

	//child maptool sampleimg
	wndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);	// 백그라운드 색상
	wndClass.lpfnWndProc = (WNDPROC)ChildMapSampleProc;						// 윈도우 프로시저
	wndClass.lpszClassName = (LPTSTR)TEXT("MapSample");							// 클래스 이름
	RegisterClass(&wndClass);

	if (FAILED(g_mainGame.init()))
	{
		return 0;
	}

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)	break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.0f);

			g_mainGame.update();
			g_mainGame.render();
		}
	}

	g_mainGame.release();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}

LRESULT CALLBACK ChildMapSampleProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.ChildMapSampleProc(hWnd, iMessage, wParam, lParam);
}

void SetWindowSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(g_hWnd, NULL,
		x, y,
		(rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}