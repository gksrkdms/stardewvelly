#include "stdafx.h"
#include "gameScene.h"
#include "player.h"
#include "mapManager.h"

HRESULT gameScene::init()
{
	m_pBG = IMAGEMANAGER->addImage("background", "image/background.bmp", MAPSIZEX, MAPSIZEY, true, RGB(255, 0, 255));
	CAMERA->init();
	m_pPlayer = new player;
	m_pPlayer->init();
	m_pMapManager = new mapManager;
	m_pMapManager->init();
	m_pMapManager->loadMap("image/1111.map");
	m_pPlayer->getMap(m_pMapManager);

	//게임시간
	PLAYTIMEMANAGER->init();

	return S_OK;
}

void gameScene::release()
{
	CAMERA->release();
	CAMERA->releaseSingleton();
	m_pPlayer->release();
	delete m_pPlayer;
	m_pMapManager->release();
	delete m_pMapManager;
	RemoveFontResource("font/모리스체.ttf");

}

void gameScene::update()
{
	m_pPlayer->update();
	m_pMapManager->update();
	CAMERA->setFocus(m_pPlayer);
	CAMERA->update();

	PLAYTIMEMANAGER->update();

}

void gameScene::render(HDC hdc)
{
	AddFontResourceA("font/모리스체.ttf");
	HFONT myFont = CreateFont(21, 0, 0, 0, 800, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "모리스9");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);

	//m_pBG->render(hdc, 0, 0, CAMERA->getX(), CAMERA->getY(), WINSIZEX, WINSIZEY);
	m_pMapManager->render(hdc);
	PLAYTIMEMANAGER->render(hdc);
	m_pPlayer->render(hdc);

	TIMEMANAGER->render(hdc);

	m_pPlayer->numRender(hdc, 1122, 205);
	
	char str[128];
	sprintf_s(str, 128, "카메라x : %d", CAMERA->getX());
	TextOut(hdc, 50, 100, str, strlen(str));
	sprintf_s(str, 128, "카메라y : %d", CAMERA->getY());
	TextOut(hdc, 50, 150, str, strlen(str));

	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}
