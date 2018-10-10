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
	if (m_nX > MAPSIZEX - WINSIZEX) m_nX = MAPSIZEX - WINSIZEX;
	if (m_nY < 0) m_nY = 0;
	if (m_nY > MAPSIZEY - WINSIZEY) m_nY = MAPSIZEY - WINSIZEY;
}

void camera::render(HDC hdc)
{
}

void camera::setFocus(player * play)
{
	m_nX = play->getX() - WINSIZEX / 2;
	m_nY = play->getY() - WINSIZEY / 2;
	if (play->getX() < 0) play->setX(0);
	if (play->getX() > MAPSIZEX - play->getSizeX()) play->setX(MAPSIZEX - play->getSizeX());
	if (play->getY() < 0) play->setY(0);
	if (play->getY() > MAPSIZEY - play->getSizeY()) play->setY(MAPSIZEY - play->getSizeY());
}

void camera::setX(int x)
{
	m_nX = x;
	if (m_nX < 0) m_nX = 0;
	if (m_nX > MAPSIZEX - WINSIZEX) m_nX = MAPSIZEX - WINSIZEX;
}

void camera::setY(int y)
{
	m_nY = y;
	if (m_nY < 0) m_nY = 0;
	if (m_nY > MAPSIZEY - WINSIZEY) m_nX = MAPSIZEY - WINSIZEY;
}

camera::camera() :
	m_nX(0),
	m_nY(0)
{
}


camera::~camera()
{
}
