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

	m_rcObjet = RectMake(0, 0, m_ptree->getFrameWidth(), m_ptree->getFrameHeight());

	m_nFrameX =0;
	m_nFrameY=0;
	m_isOnce = false;
	
	m_isOverlap = false;
	return S_OK;
}

HRESULT objTree::init(int x, int y, int id, int index)
{
	//m_ptree = IMAGEMANAGER->findImage("objtree2");

	m_nObjX = x;
	m_nObjY = y;

	m_nObjID =id;
	m_nIndex = index;

	switch (m_nObjID)
	{
	case 0:
		m_pObject = IMAGEMANAGER->findImage("objtree2");
		m_treeType = TREE_1;
		m_nFrameX = 0;
		m_nFrameY = 0;
		break;

	case 1:
		m_pObject = IMAGEMANAGER->findImage("objtree2");
		m_treeType = TREE_2;
		m_nFrameX = 0;
		m_nFrameY = 1;
		break;


	default:
		break;
	}
	m_isLayerFirst = false;

	m_isOnce = false;

	m_isOverlap = false;
	isHarvest = false;

	//m_rcObjet = RectMake(x - m_pObject->getFrameWidth()*1.5, y - m_pObject->getFrameHeight()*GAME_SCALAR, m_pObject->getFrameWidth()*GAME_SCALAR, m_pObject->getFrameHeight()*GAME_SCALAR);
	m_rcObjet = RectMake(x - m_pObject->getFrameWidth()*1.5, y - m_pObject->getFrameHeight()*GAME_SCALAR, m_pObject->getFrameWidth()*GAME_SCALAR, m_pObject->getFrameHeight()*GAME_SCALAR);
	return S_OK;
}
 
void objTree::release()
{
}

void objTree::update()
{
	//if (m_ptree)
	//{		
	//	if (PLAYTIMEMANAGER->getMin() % 5 == 0 && !m_isOnce)
	//	{
	//		m_isOnce = true;
	//		m_nFrameX++;
	//		m_ptree->setFrameX(m_nFrameX);
	//		if (m_nFrameX > 4)
	//		{
	//			m_nFrameX = 4;
	//		}
	//	}
	//	else if (PLAYTIMEMANAGER->getMin() % 5 != 0)
	//		m_isOnce = false;
	//}

	switch (m_treeType)
	{
	case TREE_1:
	{
		if (PLAYTIMEMANAGER->getMin() % 5 == 0 && !m_isOnce)
		{
			m_isOnce = true;
			m_nFrameX++;
			m_pObject->setFrameX(m_nFrameX);
			if (m_nFrameX > 4)
			{
				m_nFrameX = 4;
			}
		}
		else if (PLAYTIMEMANAGER->getMin() % 5 != 0)
			m_isOnce = false;
		break;
	}
	case TREE_2:
	{
		if (PLAYTIMEMANAGER->getMin() % 10 == 0 && !m_isOnce)
		{
			m_isOnce = true;
			m_nFrameX++;
			m_pObject->setFrameX(m_nFrameX);
			if (m_nFrameX > 4)
			{
				m_nFrameX = 4;
			}
		}
		else if (PLAYTIMEMANAGER->getMin() % 10 != 0)
			m_isOnce = false;
		break;
	}

	default:
		break;
	}

	//m_rcObjet = RectMake(m_nObjX - m_pObject->getFrameWidth()*1.5 - CAMERA->getX(), m_nObjY - m_pObject->getFrameHeight()*GAME_SCALAR - CAMERA->getY(), m_pObject->getFrameWidth()*GAME_SCALAR, m_pObject->getFrameHeight()*GAME_SCALAR);
	m_rcObjet = RectMake(m_nObjX - m_pObject->getFrameWidth()*1.5 - CAMERA->getX(), m_nObjY - m_pObject->getFrameHeight()*GAME_SCALAR - CAMERA->getY(), m_pObject->getFrameWidth()*GAME_SCALAR, m_pObject->getFrameHeight()*GAME_SCALAR);

	m_player->getPlayerRc();

	if (IntersectRect(&m_rcTemp, &m_rcObjet, &m_player->getPlayerRc()))
	{
		m_isOverlap = true;
	}
	
	else
	{
		m_isOverlap = false;
	}




}

void objTree::render(HDC hdc)
{
	//MakeRect(hdc, m_rcObjet);
	if (m_isOverlap)
		m_pObject->alphaFrameRenderM(hdc, m_nObjX - m_pObject->getFrameWidth()*1.5 - CAMERA->getX(), m_nObjY - m_pObject->getFrameHeight()*GAME_SCALAR - CAMERA->getY(), m_nFrameX, m_nFrameY, 50, GAME_SCALAR);

	else
		m_pObject->frameRender(hdc, m_nObjX - m_pObject->getFrameWidth()*1.5 - CAMERA->getX(), m_nObjY - m_pObject->getFrameHeight()*GAME_SCALAR -CAMERA->getY(), m_nFrameX, m_nFrameY, GAME_SCALAR);
}
