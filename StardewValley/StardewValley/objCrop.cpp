#include "stdafx.h"
#include "objCrop.h"
#include "item.h"

objCrop::objCrop()
{
}


objCrop::~objCrop()
{
}

HRESULT objCrop::init()
{
	m_pCrop = IMAGEMANAGER->findImage("crops");

	m_nFrameX = 0;
	m_nFrameY = 0;
	m_isOnce = false;

	return S_OK;
}

void objCrop::release()
{
}

void objCrop::update()
{
	if (m_pCrop)
	{
		//switch (m_pitem->getItemId())
		//{
		//case 101:
		//	break;

		//default:
		//	break;
		//}

		if (PLAYTIMEMANAGER->getMin() % 5 == 0 && !m_isOnce)
		{
			m_isOnce = true;
			m_nFrameX++;
			m_pCrop->setFrameX(m_nFrameX);
			if (m_nFrameX > 5)
			{
				m_nFrameX = 5;
			}
		}
		else if (PLAYTIMEMANAGER->getMin() % 5 != 0)
			m_isOnce = false;
	}
}

void objCrop::render(HDC hdc)
{

}

void objCrop::render(HDC hdc, int x, int y)
{
	m_pCrop->frameRender(hdc, x, y - m_pCrop->getFrameHeight()*GAME_SCALAR, m_nFrameX, m_nFrameY, GAME_SCALAR);
	//m_pCrop->frameRender(hdc, x - m_pCrop->getFrameWidth()*1.5, y - m_pCrop->getFrameHeight()*m_nScalar, m_nFrameX, m_nFrameY, m_nScalar);

}
