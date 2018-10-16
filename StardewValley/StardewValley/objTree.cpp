#include "stdafx.h"
#include "objTree.h"

#include "animation.h"
#include "player.h"

objTree::objTree()
{
}


objTree::~objTree()
{
}

HRESULT objTree::init()
{
	m_ptree = IMAGEMANAGER->findImage("objtree2");

	m_pTree = RectMake(0, 0, m_ptree->getFrameWidth(), m_ptree->getFrameHeight());

	m_nFrameX =0;
	m_nFrameY=0;
	m_isOnce = false;
	
	m_isOverlap = false;
	return S_OK;
}

HRESULT objTree::init(int x, int y)
{
	m_ptree = IMAGEMANAGER->findImage("objtree2");

	m_nObjX = x;
	m_nObjY = y;
	m_pTree = RectMake(x - m_ptree->getFrameWidth()*1.5, y - m_ptree->getFrameHeight()*GAME_SCALAR, m_ptree->getFrameWidth()*GAME_SCALAR, m_ptree->getFrameHeight()*GAME_SCALAR);

	m_nFrameX = 0;
	m_nFrameY = 0;
	m_isOnce = false;

	m_isOverlap = false;

	return S_OK;
}
 
void objTree::release()
{
}

void objTree::update()
{
	if (m_ptree)
	{		
		if (PLAYTIMEMANAGER->getMin() % 5 == 0 && !m_isOnce)
		{
			m_isOnce = true;
			m_nFrameX++;
			m_ptree->setFrameX(m_nFrameX);
			if (m_nFrameX > 4)
			{
				m_nFrameX = 4;
			}
		}
		else if (PLAYTIMEMANAGER->getMin() % 5 != 0)
			m_isOnce = false;

	}
	m_pTree;

	m_pTree = RectMake(m_nObjX - m_ptree->getFrameWidth()*1.5 - CAMERA->getX(), m_nObjY - m_ptree->getFrameHeight()*GAME_SCALAR - CAMERA->getY(), m_ptree->getFrameWidth()*GAME_SCALAR, m_ptree->getFrameHeight()*GAME_SCALAR);

	m_player->getPlayerRc();

	if (IntersectRect(&m_rcTemp, &m_pTree, &m_player->getPlayerRc()))
		m_isOverlap = true;
	
	else
		m_isOverlap = false;


}

void objTree::render(HDC hdc)
{
	//MakeRect(hdc, m_pTree);
	if (m_isOverlap)
		m_ptree->alphaFrameRenderM(hdc, m_nObjX - m_ptree->getFrameWidth()*1.5 - CAMERA->getX(), m_nObjY - m_ptree->getFrameHeight()*GAME_SCALAR - CAMERA->getY(), m_nFrameX, m_nFrameY, 50, GAME_SCALAR);

	else
		m_ptree->frameRender(hdc, m_nObjX - m_ptree->getFrameWidth()*1.5 - CAMERA->getX(), m_nObjY - m_ptree->getFrameHeight()*GAME_SCALAR -CAMERA->getY(), m_nFrameX, m_nFrameY, GAME_SCALAR);

}
