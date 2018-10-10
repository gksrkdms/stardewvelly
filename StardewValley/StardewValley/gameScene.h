#pragma once
#include "scene.h"
class inven;
class player;
//class Map;

class gameScene : public scene
{
private:
	image*	m_pBG;
	inven*	m_pInven;

	player*	m_pPlayer;
	//Map*	m_pMap;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	gameScene();
	~gameScene();
};

