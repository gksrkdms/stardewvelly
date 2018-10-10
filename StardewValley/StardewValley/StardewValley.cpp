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
HWND g_hWndChildSampleTop;

int g_wndCount =0;

RECT g_rc;
//bool click = false;
//
//int startX = 0;
//int startY = 0;
//int endX = 0;
//int endY = 0;

// save data
SAVE_DATA	g_saveData;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK PopupMapProc(HWND, UINT, WPARAM, LPARAM); // popupwindow
LRESULT CALLBACK ChildMapSampleProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildMapSampleTopProc(HWND, UINT, WPARAM, LPARAM); // 위 이미지

void SetWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstacne,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	g_hInstance = _hInstance;

	MSG message;

	WNDCLASS wndClass;
	WNDCLASS wndClass2;

	wndClass.cbClsExtra = 0;		// 클래스 여분 메모리
	wndClass.cbWndExtra = 0;		// 윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(NULL);	// 백그라운드 색상
	wndClass.hCursor = LoadCursor(g_hInstance, MAKEINTRESOURCE(IDC_CURSOR1));					// 커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// 아이콘
	wndClass.hInstance = _hInstance;								// 인스턴스 핸들
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						// 윈도우 프로시저
	wndClass.lpszClassName = g_lpszClass;							// 클래스 이름
	wndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MAPTILE);		// 메뉴 이름
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
	
	//popupwindow
	wndClass2 = wndClass;
	wndClass2.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);	// 백그라운드 색상
	wndClass2.lpfnWndProc = (WNDPROC)PopupMapProc;						// 윈도우 프로시저
	wndClass2.lpszClassName = (LPTSTR)TEXT("MapTool");							// 클래스 이름
	RegisterClass(&wndClass2);
	
	//ShowWindow(g_hMapTool, nCmdShow);
	//g_hWnd = g_hMap;

	//child maptool sampleimg
	//wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_PEN);	// 백그라운드 색상
	wndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);	// 백그라운드 색상
	wndClass.lpfnWndProc = (WNDPROC)ChildMapSampleProc;						// 윈도우 프로시저
	wndClass.lpszClassName = (LPTSTR)TEXT("MapSample");							// 클래스 이름
	RegisterClass(&wndClass);

	wndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);	// 백그라운드 색상
	wndClass.lpfnWndProc = (WNDPROC)ChildMapSampleTopProc;						// 윈도우 프로시저
	wndClass.lpszClassName = (LPTSTR)TEXT("TopMapSample");							// 클래스 이름
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

LRESULT CALLBACK PopupMapProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	//TCHAR *mes = TEXT("dd");

	switch (iMessage)
	{
	case WM_CREATE:
		g_wndCount++;
		return 0;

	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			break;

		case VK_ESCAPE:
			break;
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 0, 0, "dd", 2);
		break;

	case WM_INITDIALOG:
		break;

		//case WM_COMMAND:
		//{
		//	switch (LOWORD(wParam))
		//	{
		//		//save
		//	case 0:
		//		OPENFILENAME ofn;

		//		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		//		ofn.lStructSize = sizeof(OPENFILENAME);
		//		ofn.hwndOwner = hWnd;
		//		ofn.lpstrFilter = _T("Map Files(*.map)\0*.map\0All Files (*.*)\0*.*\0");
		//		ofn.lpstrFile = szFileName;
		//		ofn.nMaxFile = nFileNameMaxLen;
		//		ofn.lpstrDefExt = "map";
		//		//ofn.nFilterIndex = 1;
		//		//ofn.lpstrFileTitle = szFileName;
		//		//ofn.nMaxFileTitle = 0;
		//		//ofn.lpstrInitialDir = NULL;
		//		ofn.Flags = OFN_OVERWRITEPROMPT;
		//		GetSaveFileName(&ofn);

		//		//if (0 != GetOpenFileName(&OFN))
		//		//{
		//		//}
		//		
		//		m_pTileMap->saveMap(szFileName);
		//		//MessageBox(g_hWnd, TEXT("dd"), TEXT("ddkkk"), MB_OK);
		//		break;

		//		// load
		//	case 1:

		//		memset(&OFN, 0, sizeof(OPENFILENAME));
		//		OFN.lStructSize = sizeof(OPENFILENAME);
		//		OFN.hwndOwner = hWnd;
		//		OFN.lpstrFilter = "Map Files(*.map)\0*.map\0All Files (*.*)\0*.*\0";
		//		OFN.lpstrFile = szFileName;
		//		OFN.nMaxFile = nFileNameMaxLen;

		//		if (0 != GetOpenFileName(&OFN))
		//		{
		//			SetWindowText(hEditFileToBeOpened, OFN.lpstrFile);
		//			m_pTileMap->loadMap(OFN.lpstrFile);
		//		}
		//		return TRUE;

		//		break;

		//		// terrain
		//	case 2:
		//		m_pTileMap->setObject(false);
		//		break;

		//		// object
		//	case 3:
		//		m_pTileMap->setObject(true);
		//		break;

		//		// eraser
		//	case 4:
		//		m_pTileMap->objectEraser();
		//		break;
		//	}
		//	break;
		//}

	case WM_DESTROY:
		g_wndCount--;
		if (g_wndCount == 0)
		{
			PostQuitMessage(0);
		}
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

LRESULT CALLBACK ChildMapSampleProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.ChildMapSampleProc(hWnd, iMessage, wParam, lParam);
}

LRESULT CALLBACK ChildMapSampleTopProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.ChildMapSampleTopProc(hWnd, iMessage, wParam, lParam);
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