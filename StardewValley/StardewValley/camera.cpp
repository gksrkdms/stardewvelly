#include "stdafx.h"
#include "camera.h"
#include "player.h"


HRESULT camera::init()
{
	return S_OK;
}

void camera::release()
{
}

void camera::update()
{
	if (m_nX < 0) m_nX = 0;
	if (m_nX > g_mapSize.mapSizeX - WINSIZEX) m_nX = g_mapSize.mapSizeX - WINSIZEX;
	if (m_nY < 0) m_nY = 0;
	if (m_nY > g_mapSize.mapSizeY - WINSIZEY) m_nY = g_mapSize.mapSizeY - WINSIZEY;
}

void camera::render(HDC hdc)
{
}

void camera::setFocus(player * play)
{
	m_nX = play->getX() - WINSIZEX / 2;
	m_nY = play->getY() - WINSIZEY / 2;
	if (play->getX() < 0) play->setX(0);
	if (play->getX() > g_mapSize.mapSizeX - play->getSizeX() - 80) play->setX(g_mapSize.mapSizeX - play->getSizeX() - 80);
	if (play->getY() < 0) play->setY(0);
	if (play->getY() > g_mapSize.mapSizeY - play->getSizeY() - 100) play->setY(g_mapSize.mapSizeY - play->getSizeY() - 100);
}

void camera::setX(int x)
{
	m_nX = x;
	if (m_nX < 0) m_nX = 0;
	if (m_nX > g_mapSize.mapSizeX - WINSIZEX) m_nX = g_mapSize.mapSizeX - WINSIZEX;
}

void camera::setY(int y)
{
	m_nY = y;
	if (m_nY < 0) m_nY = 0;
	if (m_nY > g_mapSize.mapSizeX - WINSIZEY) m_nX = g_mapSize.mapSizeX - WINSIZEY;
}

camera::camera() :
	m_nX(0),
	m_nY(0)
{
}


camera::~camera()
{
}
