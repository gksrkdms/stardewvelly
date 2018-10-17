#include "stdafx.h"
#include "mainGame.h"
#include "startScene.h"
#include "gameScene.h"
#include "mapTool.h"

void mainGame::setBackBuffer()
{
	m_pBackBuffer = new image;
	m_pBackBuffer->init(WINSIZEX, WINSIZEY);
}

HRESULT mainGame::init()
{
	hdc = GetDC(g_hWnd);

	g_soundVolume.bgm = 0.4f;
	g_soundVolume.effect = 1.0f;

	KEYMANAGER->init();
	IMAGEMANAGER->init();
	TIMEMANAGER->init();
	SCENEMANAGER->init();
	SOUNDMANAGER->init();
	//EFFECTMANAGER->init();

	setBackBuffer();


	//EFFECTMANAGER->addEffect("water_drop", "image/Stardew Valley/water_bottom.bmp", 640, 64, 64, 64, 8, 3);
	//EFFECTMANAGER->addEffect("water_drop2", "image/Stardew Valley/water_top.bmp", 192, 64, 64, 64, 5, 3);
	//EFFECTMANAGER->addEffect("recovery", "image/Stardew Valley/recovery.bmp", 448, 64, 64, 64, 10, 3);
	//EFFECTMANAGER->addEffect("need_water", "image/Stardew Valley/water_zero.bmp", 256, 64, 64, 64, 4, 3);

	// 필요한 리소스 미리 로드
	imgload();
	addsound();

	m_pMap = new mapTool;
	SCENEMANAGER->addScene("maptool", m_pMap);

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

	SOUNDMANAGER->release();
	DATAMANAGER->release();
	KEYMANAGER->release();
	IMAGEMANAGER->release();
	TIMEMANAGER->release();
	SCENEMANAGER->release();
	PLAYTIMEMANAGER->release();
	SOUNDMANAGER->release();
	//EFFECTMANAGER->release();
	
	DATAMANAGER->releaseSingleton();
	KEYMANAGER->releaseSingleton();
	IMAGEMANAGER->releaseSingleton();
	TIMEMANAGER->releaseSingleton();
	SCENEMANAGER->releaseSingleton();
	PLAYTIMEMANAGER->releaseSingleton();
	SOUNDMANAGER->releaseSingleton();
	//EFFECTMANAGER->releaseSingleton();
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
			break;

		case WM_LBUTTONDOWN:
			break;

		case WM_MOUSEMOVE:
			g_ptMouse.x = LOWORD(lParam);
			g_ptMouse.y = HIWORD(lParam);	
			break;

		case WM_LBUTTONUP:
			break;

		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			}
			return 0;

		case WM_INITDIALOG:
			break;

		case WM_PRINT:
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hWnd, iMessage, wParam, lParam);
	}	

}

LRESULT mainGame::ChildMapSampleProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return m_pMap->ChildMapSampleProc(hWnd, iMessage, wParam, lParam);
}

void mainGame::update()
{
	InvalidateRect(g_hWnd, NULL, false);
	SCENEMANAGER->update();
	//EFFECTMANAGER->update();
	
}

void mainGame::render()
{

	HDC backDC = m_pBackBuffer->getMemDC();
	SCENEMANAGER->render(backDC);
	m_pBackBuffer->render(hdc, 0, 0);
	
}

void mainGame::imgload()
{
	// 타일맵img
	// background
	IMAGEMANAGER->addImage("maptoolui", "image/maptool/minimap.bmp", 330, 330,true, RGB(255,0,255));
	IMAGEMANAGER->addImage("earthAll", "image/maptool/tile20-20.bmp", 320, 320, 20,20,true, RGB(255, 255, 255));
	// object
	IMAGEMANAGER->addImage("earthObj", "image/maptool/풀돌나무obj.bmp", 48, 48,3,3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town", "image/maptool/마을오브젝트.bmp", 720, 528,45,33, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("floor", "image/maptool/장판.bmp", 256, 160,16,10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town_Shop", "image/maptool/town.bmp", 320, 320,20,20, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("town_Nomal", "image/maptool/town_nomal.bmp", 320, 320,20,20, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("object3", "image/maptool/object3.bmp", 320, 320,20,20, true, RGB(255, 255, 255));
	
	IMAGEMANAGER->addImage("objtree", "image/maptool/object/objtree.bmp", 176, 654,11,41, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("objtree2", "image/maptool/object/environment_003.bmp", 432, 560,9,7, true, RGB(255, 0, 255));
	
	// 충돌범위
	IMAGEMANAGER->addImage("mapCollision", "image/maptool/collision.bmp", 16, 16, true, RGB(255, 0, 255));
	
	// background
	IMAGEMANAGER->addImage("whitebackground", "image/background.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("dark", "image/dark.bmp", WINSIZEX, WINSIZEY); //밤, 네이비
	IMAGEMANAGER->addImage("black", "image/black.bmp", WINSIZEX, WINSIZEY); // 블랙

	// 타이틀
	IMAGEMANAGER->addImage("title_001", "image/Stardew Valley/title/title_001.bmp", 400, 183, true, RGB(255, 0, 255));	// 스타듀밸리
	IMAGEMANAGER->addImage("title_002", "image/Stardew Valley/title/title_002.bmp", 888, 348, 4, 2, true, RGB(255, 0, 255));	// 메뉴
	IMAGEMANAGER->addImage("title_003", "image/Stardew Valley/title/title_003.bmp", 400, 183, 1, 2, true, RGB(255, 0, 255));	// 뒤로가기
	IMAGEMANAGER->addImage("title_004", "image/Stardew Valley/title/title_004.bmp", 123, 55, true, RGB(255, 0, 255));	// 구름 1
	IMAGEMANAGER->addImage("title_005", "image/Stardew Valley/title/title_005.bmp", 64, 35, true, RGB(255, 0, 255));	// 구름 2
	IMAGEMANAGER->addImage("title_006", "image/Stardew Valley/title/title_006.bmp", WINSIZEX, WINSIZEY);	// 백그라운드

	// ui
	IMAGEMANAGER->addImage("inven_001", "image/Stardew Valley/ui/inven_001.bmp", 768, 68, false, 0);
	IMAGEMANAGER->addImage("inven_002", "image/Stardew Valley/ui/inven_002.bmp", 768, 68, false, 0);
	IMAGEMANAGER->addImage("inven_003", "image/Stardew Valley/ui/inven_003.bmp", 848, 272, false, 0);
	IMAGEMANAGER->addImage("inven_004", "image/Stardew Valley/ui/inven_004.bmp", 848, 580, false, 0);
	IMAGEMANAGER->addImage("quickbar", "image/Stardew Valley/ui/quickbar.bmp", 800, 96, true, (255, 0, 255));
	IMAGEMANAGER->addImage("focustile_001", "image/Stardew Valley/ui/focustile_001.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("focustile_002", "image/Stardew Valley/ui/focustile_002.bmp", 32, 16, 2, 1, true, RGB(255,0,255));
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
	IMAGEMANAGER->addImage("menu_textBox", "image/Stardew Valley/ui/menu_textBox.bmp", 73, 60, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("goldnumber", "image/Stardew Valley/ui/goldnumber.bmp", 200, 28, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp_EnergyBar", "image/Stardew Valley/ui/hp_energy.bmp", 104, 224, true, RGB(255, 0, 255)); // @체력에너지 이미지
	IMAGEMANAGER->addImage("hp_energy_top", "image/Stardew Valley/ui/hp_energy_top.bmp", 24, 168, true, RGB(255, 0, 255)); // @체력에너지 이미지

	IMAGEMANAGER->addImage("sort", "image/Stardew Valley/ui/sort.bmp", 65, 65, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("trash_can", "image/Stardew Valley/ui/trash_can.bmp", 16, 26, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("trash_head", "image/Stardew Valley/ui/trash_head.bmp", 18, 20, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("dmg", "image/Stardew Valley/ui/dmg.bmp", 44, 44, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("goldui", "image/Stardew Valley/ui/goldui.bmp", 260, 68, true, RGB(255,0,255));
	
	// 시계
	IMAGEMANAGER->addImage("minutehand", "image/Stardew Valley/ui/clock.bmp", 48, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("clock", "image/Stardew Valley/ui/clock1.bmp", 72, 57, true, RGB(255, 0, 255));
	
	// icon
	IMAGEMANAGER->addImage("icon1", "image/Stardew Valley/ui/icon1.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon2", "image/Stardew Valley/ui/icon2.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon3", "image/Stardew Valley/ui/icon3.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon4", "image/Stardew Valley/ui/icon4.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon5", "image/Stardew Valley/ui/icon5.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon6", "image/Stardew Valley/ui/icon6.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon7", "image/Stardew Valley/ui/icon7.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon8", "image/Stardew Valley/ui/icon8.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon9", "image/Stardew Valley/ui/icon9.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon10", "image/Stardew Valley/ui/icon10.bmp", 16, 16, true, RGB(255, 0, 255));

	// 플레이어
	IMAGEMANAGER->addImage("player_axe", "image/Stardew Valley/player/player_axe.bmp", 640, 768, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_fishing", "image/Stardew Valley/player/player_fishing.bmp", 768, 768, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_handup", "image/Stardew Valley/player/player_handup.bmp", 960, 768, 5, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_idle", "image/Stardew Valley/player/player_idle.bmp", 400, 640, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_mine", "image/Stardew Valley/player/player_mine.bmp", 510, 768, 3, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_not", "image/Stardew Valley/player/player_not.bmp", 510, 768, 3, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_spade", "image/Stardew Valley/player/player_spade.bmp", 600, 768, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_sword", "image/Stardew Valley/player/player_sword.bmp", 576, 768, 3, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_water", "image/Stardew Valley/player/player_water.bmp", 340, 768, 2, 4, true, RGB(255, 0, 255));

	// 아이템
	// 도구류
	IMAGEMANAGER->addImage("item_001", "image/Stardew Valley/item/item_001.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_002", "image/Stardew Valley/item/item_002.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_003", "image/Stardew Valley/item/item_003.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_004", "image/Stardew Valley/item/item_004.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_005", "image/Stardew Valley/item/item_005.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_006", "image/Stardew Valley/item/item_006.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_007", "image/Stardew Valley/item/item_007.bmp", 16, 16, true, RGB(255, 0, 255));

	// 씨앗류
	IMAGEMANAGER->addImage("item_101", "image/Stardew Valley/item/item_101.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_102", "image/Stardew Valley/item/item_102.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_103", "image/Stardew Valley/item/item_103.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_104", "image/Stardew Valley/item/item_104.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_105", "image/Stardew Valley/item/item_105.bmp", 16, 16, true, RGB(255, 0, 255));

	// 수확아이템
	IMAGEMANAGER->addImage("item_201", "image/Stardew Valley/item/item_201.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_202", "image/Stardew Valley/item/item_202.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_203", "image/Stardew Valley/item/item_203.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_204", "image/Stardew Valley/item/item_204.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_205", "image/Stardew Valley/item/item_205.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_206", "image/Stardew Valley/item/item_206.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_207", "image/Stardew Valley/item/item_207.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_208", "image/Stardew Valley/item/item_208.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_209", "image/Stardew Valley/item/item_209.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_210", "image/Stardew Valley/item/item_210.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_211", "image/Stardew Valley/item/item_211.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_212", "image/Stardew Valley/item/item_212.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_213", "image/Stardew Valley/item/item_213.bmp", 16, 16, true, RGB(255, 0, 255));

	// crops
	IMAGEMANAGER->addImage("crops", "image/Stardew Valley/crop/crops.bmp", 256, 669,16,20, true, RGB(255, 0, 255));

	//추가아이템 나중에정리할것
	IMAGEMANAGER->addImage("item_214", "image/Stardew Valley/item/item_214.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_215", "image/Stardew Valley/item/item_215.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_219", "image/Stardew Valley/item/item_219.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_220", "image/Stardew Valley/item/item_220.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_221", "image/Stardew Valley/item/item_221.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_301", "image/Stardew Valley/item/item_301.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_302", "image/Stardew Valley/item/item_302.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_303", "image/Stardew Valley/item/item_303.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_501", "image/Stardew Valley/item/item_501.bmp", 16, 16, true, RGB(255, 0, 255));

}

void mainGame::addsound()
{
	// start scene
	SOUNDMANAGER->addSound("sound/StardewValleyOverture.mp3", true, true);
	SOUNDMANAGER->addSound("sound/effect/첨클릭.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/startbutton.wav", false, false);

	//gameScene
	SOUNDMANAGER->addSound("sound/CloudCountry.mp3", true, true);


}






mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}
