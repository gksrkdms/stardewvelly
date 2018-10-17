#include "stdafx.h"
#include "objCrop.h"
#include "item.h"

objCrop::objCrop()
{
}


objCrop::~objCrop()
{
}

HRESULT objCrop::init(int seedNum, int tileIndex, int posX, int posY)
{
	m_pCrop = IMAGEMANAGER->findImage("crops");

	m_nScalar = 4;
	m_nFrameX = 0;
	m_nX = posX;
	m_nY = posY;
	switch (seedNum)
	{
	case 101:
		m_nFrameY = 0;
		m_nCropId = 201;
		break;
	case 102:
		m_nFrameY = 1;
		m_nCropId = 202;
		break;
	}
	m_nTileIndex = tileIndex;
	m_isOnce = false;
	isWater = false;
	isHarvest = false;

	return S_OK;
}

void objCrop::release()
{
}

void objCrop::update(int x, int y)
{
	if (isWater)
	{
		//switch (m_pitem->getItemId())
		//{
		//case 101:
		//	break;

		//default:
		//	break;
		//}

		if (PLAYTIMEMANAGER->getMin() % 2 == 0 && !m_isOnce)
		{
			m_isOnce = true;
			m_nFrameX++;
			m_pCrop->setFrameX(m_nFrameX);
			if (m_nFrameX > 5)
			{
				m_nFrameX = 5;
				int a = 19;
				isHarvest = true;
			}
		}
		else if (PLAYTIMEMANAGER->getMin() % 2 != 0)
			m_isOnce = false;
	}
	m_nX = x;
	m_nY = y;
}

void objCrop::render(HDC hdc)
{
	m_pCrop->frameRender(hdc, m_nX , m_nY - m_pCrop->getFrameHeight() * 2, m_nFrameX, m_nFrameY, m_nScalar);
}

void objCrop::render(HDC hdc, int x, int y)
{
	//m_pCrop->frameRender(hdc, x, y - m_pCrop->getFrameHeight()*m_nScalar, m_nFrameX, m_nFrameY, m_nScalar);
	//m_pCrop->frameRender(hdc, x - m_pCrop->getFrameWidth()*1.5, y - m_pCrop->getFrameHeight()*m_nScalar, m_nFrameX, m_nFrameY, m_nScalar);

}
