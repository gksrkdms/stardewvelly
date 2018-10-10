#include "stdafx.h"
#include "mainGame.h"
#include "mapTool.h"
#include "startScene.h"
#include "gameScene.h"

#include "mapManager.h"

//HWND hButtonOpenFileDialog;
//HWND hEditFileToBeOpened;
//OPENFILENAME OFN;
//const UINT nFileNameMaxLen = 512;
//char szFileName[nFileNameMaxLen];
//TCHAR szFileName2[256] = _T("");

//ぞしぞしぞし
//せせせせ

void mainGame::setBackBuffer()
{
	m_pBackBuffer = new image;
	m_pBackBuffer->init(WINSIZEX, WINSIZEY);
}

HRESULT mainGame::init()
{
	hdc = GetDC(g_hWnd);

	KEYMANAGER->init();
	IMAGEMANAGER->init();
	TIMEMANAGER->init();
	SCENEMANAGER->init();

	setBackBuffer();

	// 琶推廃 軒社什 耕軒 稽球
	imgload();

	// Maptool
	m_pMap = new mapTool;
	SCENEMANAGER->addScene("maptool", m_pMap);

	m_pMapmgr = new mapManager;
	SCENEMANAGER->addScene("mgr", m_pMapmgr);

	m_pStartScene = new startScene;
	SCENEMANAGER->addScene("startScene", m_pStartScene);

	m_pGameScene = new gameScene;
	SCENEMANAGER->addScene("gameScene", m_pGameScene);

	SCENEMANAGER->changeScene("startScene");
	

	return S_OK;
}

void mainGame::release()
{
	SAFE_DELETE(m_pBackBuffer);

	ReleaseDC(g_hWnd, hdc);

	DATAMANAGER->release();
	KEYMANAGER->release();
	IMAGEMANAGER->release();
	TIMEMANAGER->release();
	SCENEMANAGER->release();

	DATAMANAGER->releaseSingleton();
	KEYMANAGER->releaseSingleton();
	IMAGEMANAGER->releaseSingleton();
	TIMEMANAGER->releaseSingleton();
	SCENEMANAGER->releaseSingleton();

}

LRESULT mainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	if (SCENEMANAGER->getSceneName() == "maptool")
	{
		return m_pMap->MainProc(hWnd, iMessage, wParam, lParam);
	}

	else
	{
		switch (iMessage)
		{
		case WM_CREATE:
			g_wndCount++;
			break;

		case WM_LBUTTONDOWN:

			break;

		case WM_MOUSEMOVE:
			g_ptMouse.x = LOWORD(lParam);
			g_ptMouse.y = HIWORD(lParam);

			//if (click)
			//{
			//	GetWindowRect(g_hWnd, &rc);
			//	rc.left += LOWORD(lParam) - g_ptMouse.x;
			//	rc.top += HIWORD(lParam) - g_ptMouse.y;
			//	g_ptMouse.x = LOWORD(lParam);
			//	g_ptMouse.y = HIWORD(lParam);
			//}				
			break;

		case WM_LBUTTONUP:
			break;

		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				break;
			}
			return 0;

		case WM_INITDIALOG:
			break;

		case WM_PRINT:
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

}

LRESULT mainGame::ChildMapSampleProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return m_pMap->ChildMapSampleProc(hWnd, iMessage, wParam, lParam);
}

LRESULT mainGame::ChildMapSampleTopProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return m_pMap->ChildMapSampleTopProc(hWnd, iMessage, wParam, lParam);
}

void mainGame::update()
{
	InvalidateRect(g_hWnd, NULL, false);

	SCENEMANAGER->update();
}

void mainGame::render()
{
	HDC backDC = m_pBackBuffer->getMemDC();

	SCENEMANAGER->render(backDC);

	m_pBackBuffer->render(hdc, 0, 0);
}

void mainGame::imgload()
{
	// 展析己img
	// background
	IMAGEMANAGER->addImage("maptoolui", "image/maptool/minimap.bmp", 330, 330,true, RGB(255,0,255));
	IMAGEMANAGER->addImage("earthAll", "image/maptool/tile20-20.bmp", 320, 320, 20,20,true, RGB(255, 255, 255));
	// object
	IMAGEMANAGER->addImage("earthObj", "image/maptool/熱宜蟹巷obj.bmp", 48, 48,3,3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town", "image/maptool/原聖神崎詮闘.bmp", 720, 528,45,33, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("floor", "image/maptool/舌毒.bmp", 256, 160,16,10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town_Shop", "image/maptool/town.bmp", 320, 320,20,20, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("town_Nomal", "image/maptool/town_nomal.bmp", 320, 320,20,20, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("object3", "image/maptool/object3.bmp", 320, 320,20,20, true, RGB(255, 255, 255));
	
	IMAGEMANAGER->addImage("objtree", "image/maptool/object/objtree.bmp", 176, 654,11,41, true, RGB(255, 255, 255));
	
	
	
	// background
	IMAGEMANAGER->addImage("whitebackground", "image/background.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("dark", "image/dark.bmp", WINSIZEX, WINSIZEY);

	// 展戚堂
	IMAGEMANAGER->addImage("title_001", "image/Stardew Valley/title/title_001.bmp", 400 * 2, 183 * 2, true, RGB(255, 0, 255));	// 什展朽豪軒
	IMAGEMANAGER->addImage("title_002", "image/Stardew Valley/title/title_002.bmp", 888, 348, 4, 2, true, RGB(255, 0, 255));	// 五敢
	IMAGEMANAGER->addImage("title_003", "image/Stardew Valley/title/title_003.bmp", 400, 183, 1, 2, true, RGB(255, 0, 255));	// 及稽亜奄
	IMAGEMANAGER->addImage("title_004", "image/Stardew Valley/title/title_004.bmp", 123, 55, true, RGB(255, 0, 255));	// 姥硯 1
	IMAGEMANAGER->addImage("title_005", "image/Stardew Valley/title/title_005.bmp", 64, 35, true, RGB(255, 0, 255));	// 姥硯 2
	IMAGEMANAGER->addImage("title_006", "image/Stardew Valley/title/title_006.bmp", WINSIZEX, WINSIZEY);	// 拷益虞錘球

	// ui
	IMAGEMANAGER->addImage("inven_001", "image/Stardew Valley/ui/inven_001.bmp", 768, 68, false, 0);
	IMAGEMANAGER->addImage("inven_002", "image/Stardew Valley/ui/inven_002.bmp", 768, 68, false, 0);
	IMAGEMANAGER->addImage("inven_003", "image/Stardew Valley/ui/inven_003.bmp", 848, 580, false, 0);
	IMAGEMANAGER->addImage("quickbar", "image/Stardew Valley/ui/quickbar.bmp", 800, 96, true, (255, 0, 255));
	IMAGEMANAGER->addImage("focustile_001", "image/Stardew Valley/ui/focustile_001.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("focustile_002", "image/Stardew Valley/ui/focustile_002.bmp", 32, 16, 2, 1, false, 0);
	IMAGEMANAGER->addImage("shop_make", "image/Stardew Valley/ui/shop_make.bmp", 824, 252, false, 0);
	IMAGEMANAGER->addImage("shop_window", "image/Stardew Valley/ui/shop_window.bmp", 1080, 460, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("show_list", "image/Stardew Valley/ui/show_list.bmp", 1032, 94, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("barnumber", "image/Stardew Valley/ui/barnumber.bmp", 72, 11, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("leftarrow", "image/Stardew Valley/ui/leftarrow.bmp", 44, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rightarrow", "image/Stardew Valley/ui/rightarrow.bmp", 44, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("textBox", "image/Stardew Valley/ui/textBox.bmp", 309, 284, false, 0);
	IMAGEMANAGER->addImage("recovery_energy", "image/Stardew Valley/ui/recovery_energy.bmp", 50, 34, false, 0);
	IMAGEMANAGER->addImage("recovery_hp", "image/Stardew Valley/ui/recovery_hp.bmp", 50, 34, false, 0);
	IMAGEMANAGER->addImage("shop_textBox", "image/Stardew Valley/ui/shop_textBox.bmp", 209, 100, true, RGB(255, 0, 255));

	// 巴傾戚嬢
	IMAGEMANAGER->addImage("player_axe", "image/Stardew Valley/player/player_axe.bmp", 640, 768, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_fishing", "image/Stardew Valley/player/player_fishing.bmp", 768, 768, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_handup", "image/Stardew Valley/player/player_handup.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_idle", "image/Stardew Valley/player/player_idle.bmp", 400, 640, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_mine", "image/Stardew Valley/player/player_mine.bmp", 510, 768, 3, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_not", "image/Stardew Valley/player/player_not.bmp", 510, 768, 3, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_spade", "image/Stardew Valley/player/player_spade.bmp", 600, 768, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_sword", "image/Stardew Valley/player/player_sword.bmp", 576, 768, 3, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_water", "image/Stardew Valley/player/player_water.bmp", 340, 768, 2, 4, true, RGB(255, 0, 255));

	// 焼戚奴
	// 亀姥嫌
	IMAGEMANAGER->addImage("item_001", "image/Stardew Valley/item/item_001.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_002", "image/Stardew Valley/item/item_002.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_003", "image/Stardew Valley/item/item_003.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_004", "image/Stardew Valley/item/item_004.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_005", "image/Stardew Valley/item/item_005.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_006", "image/Stardew Valley/item/item_006.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_007", "image/Stardew Valley/item/item_007.bmp", 16, 16, true, RGB(255, 0, 255));

	// 松粧嫌
	IMAGEMANAGER->addImage("item_101", "image/Stardew Valley/item/item_101.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_102", "image/Stardew Valley/item/item_102.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_103", "image/Stardew Valley/item/item_103.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_104", "image/Stardew Valley/item/item_104.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_105", "image/Stardew Valley/item/item_105.bmp", 16, 16, true, RGB(255, 0, 255));

	// 呪溌焼戚奴
	IMAGEMANAGER->addImage("item_201", "image/Stardew Valley/item/item_201.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_202", "image/Stardew Valley/item/item_202.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_203", "image/Stardew Valley/item/item_203.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_204", "image/Stardew Valley/item/item_204.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_205", "image/Stardew Valley/item/item_205.bmp", 16, 16, true, RGB(255, 0, 255));

	// 階獣淫恵 戚耕走
	IMAGEMANAGER->addImage("i_GaroBar", "image/Stardew Valley/fishing/亜稽郊.bmp", 200, 48, true, RGB(255, 0, 255));   // 据掘紫戚綜 50,12 
	IMAGEMANAGER->addImage("i_Max", "image/Stardew Valley/fishing/呼什.bmp", 116, 48, true, RGB(255, 0, 255)); //据紫戚綜 58,24 
	IMAGEMANAGER->addImage("i_Zzi", "image/Stardew Valley/fishing/卓.bmp", 120, 40, 3, 1, true, RGB(255, 0, 255)); //据紫戚綜 30,10 
	IMAGEMANAGER->addImage("i_Player", "image/Stardew Valley/fishing/player.bmp", 400, 640, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("i_PlayerFishing", "image/Stardew Valley/fishing/巴傾戚嬢階獣.bmp", 768, 768, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("i_Feel", "image/Stardew Valley/fishing/汗界妊.bmp", 30, 45, true, RGB(255, 0, 255)); //据紫戚綜 10,15 
	IMAGEMANAGER->addImage("i_Hit", "image/Stardew Valley/fishing/備闘.bmp", 148, 64, true, RGB(255, 0, 255)); //据紫戚綜 74,32 
	IMAGEMANAGER->addImage("i_SeroBar", "image/Stardew Valley/fishing/室稽郊.bmp", 160, 500, true, RGB(255, 0, 255)); //据紫戚綜 39,150  
	IMAGEMANAGER->addImage("i_WhitebarL", "image/Stardew Valley/fishing/避燃識図是.bmp", 210, 550, true, RGB(255, 0, 255)); //据紫戚綜 52,185 
	IMAGEMANAGER->addImage("i_WhitebarR", "image/Stardew Valley/fishing/避燃識神焼.bmp", 210, 550, true, RGB(255, 0, 255)); //据紫戚綜 52,185  
	IMAGEMANAGER->addImage("i_GreenBar", "image/Stardew Valley/fishing/段系郊幻窮暗.bmp", 37, 77, true, RGB(255, 0, 255)); // 9,9 
	IMAGEMANAGER->addImage("i_moveFish", "image/Stardew Valley/fishing/弘壱奄.bmp", 37, 37, true, RGB(255, 0, 255)); // 19 19
	IMAGEMANAGER->addImage("i_moveChoo", "image/Stardew Valley/fishing/蓄姶奄.bmp", 168, 55, 4, 1, true, RGB(255, 0, 255));// 72 21 
	IMAGEMANAGER->addImage("i_GetFish", "image/Stardew Valley/fishing/榎斎嬢.bmp", 102, 51, 2, 1, true, RGB(255, 0, 255));// 34 17  
}


mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}
