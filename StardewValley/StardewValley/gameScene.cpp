#include "stdafx.h"
#include "gameScene.h"
#include "player.h"
#include "mapManager.h"



HRESULT gameScene::init()
{
	addSound();
	m_pBG = IMAGEMANAGER->addImage("background", "image/background.bmp", MAPSIZEX, MAPSIZEY, true, RGB(255, 0, 255));
	CAMERA->init();
	m_pPlayer = new player;
	m_pPlayer->init();
	m_pMapManager = new mapManager;
	m_pMapManager->init();
	m_pMapManager->loadMap("image/test.map");
	m_pPlayer->getMap(m_pMapManager);

	//게임시간
	PLAYTIMEMANAGER->init();

	//배경음
	SOUNDMANAGER->play("sound/CloudCountry.mp3", g_soundVolume.bgm);

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
void gameScene::addSound()
{
	// 인벤옮기고 손떨어지게하는거
	SOUNDMANAGER->addSound("sound/effect/changeitem.wav", false, false);
	// 인벤 열기 닫기
	SOUNDMANAGER->addSound("sound/effect/인벤토리.wav", false, false);
	//상점 페이지넘기기
	SOUNDMANAGER->addSound("sound/effect/선택음1.wav", false, false);
	//상점 물건사고파는소리
	SOUNDMANAGER->addSound("sound/effect/돈소리.wav", false, false);





	//음식먹기
	SOUNDMANAGER->addSound("sound/effect/아삭소리2.wav", false, false);


}
gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}
