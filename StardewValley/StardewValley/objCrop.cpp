#include "stdafx.h"
#include "objCrop.h"
#include "player.h"

objCrop::objCrop()
{
}


objCrop::~objCrop()
{
}

HRESULT objCrop::init()
{
	m_pObject = IMAGEMANAGER->findImage("crops");

	m_nFrameX = 0;
	m_nFrameY = 0;
	m_isOnce = false;

	return S_OK;
}

HRESULT objCrop::init(int x, int y, int id, int index)
{
	m_pObject = IMAGEMANAGER->findImage("crops");

	m_nObjID = id;

	switch (m_nObjID)
	{
	case 101:
		m_pObject = IMAGEMANAGER->findImage("crops");
		m_cropKind = STRAWBERRY;
		break;

	case 102:
		m_pObject = IMAGEMANAGER->findImage("crops");
		m_cropKind = CARROT;
		break;

	default:
		break;
	}

	m_nObjX = x;
	m_nObjY = y;
	m_rcObjet = RectMake(x, y - m_pObject->getFrameHeight()*GAME_SCALAR, m_pObject->getFrameWidth()*GAME_SCALAR, m_pObject->getFrameHeight()*GAME_SCALAR);

	m_nFrameX = 0;
	m_nFrameY = 0;
	m_isOnce = false;

	//m_isOverlap = false;
	return S_OK;
}

void objCrop::release()
{
}

void objCrop::update()
{
	//m_rcObjetc = RectMake(m_nObjX - m_pCrop->getFrameWidth()*1.5 - CAMERA->getX(), m_nObjY - m_pCrop->getFrameHeight()*GAME_SCALAR - CAMERA->getY(), m_pCrop->getFrameWidth()*GAME_SCALAR, m_pCrop->getFrameHeight()*GAME_SCALAR);
	m_rcObjet = RectMake(m_nObjX - CAMERA->getX(), m_nObjY - m_pObject->getFrameHeight()*GAME_SCALAR - CAMERA->getY(), m_pObject->getFrameWidth()*GAME_SCALAR, m_pObject->getFrameHeight()*GAME_SCALAR);

	switch (m_cropKind)
	{
	case STRAWBERRY:
		break;
	case CARROT:
		break;
	default:
		break;
	}

	if (PLAYTIMEMANAGER->getMin() % 5 == 0 && !m_isOnce)
	{
		m_isOnce = true;
		m_nFrameX++;
		m_pObject->setFrameX(m_nFrameX);
		if (m_nFrameX > 5)
		{
			m_nFrameX = 5;
		}
	}
	else if (PLAYTIMEMANAGER->getMin() % 5 != 0)
		m_isOnce = false;
	

	
}

void objCrop::render(HDC hdc)
{
	//m_pCrop->frameRender(hdc, x, y - m_pCrop->getFrameHeight()*GAME_SCALAR, m_nFrameX, m_nFrameY, GAME_SCALAR);
	m_pObject->frameRender(hdc, m_nObjX - CAMERA->getX(), m_nObjY - m_pObject->getFrameHeight()*GAME_SCALAR - CAMERA->getY(), m_nFrameX, m_nFrameY, GAME_SCALAR);

}

