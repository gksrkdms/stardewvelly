#pragma once
#include "scene.h"
class inven;
class player;
class mapManager;

class gameScene : public scene
{
private:
	image*	m_pBG;
	inven*	m_pInven;

	player*	m_pPlayer;
	mapManager*	m_pMapManager;

public:
	void addSound();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	gameScene();
	~gameScene();
};

