#include "stdafx.h"
#include "objTree.h"

#include "animation.h"

objTree::objTree()
{
}


objTree::~objTree()
{
}

HRESULT objTree::init()
{
	m_ptree = IMAGEMANAGER->findImage("objtree2");
	//m_pAni = new animation;
	//m_pAni->init(m_ptree->getWidth(), m_ptree->getHeight(), m_ptree->getFrameWidth(), m_ptree->getFrameHeight());
	//m_pAni->setPlayFrame(0, 5, true, true);
	//m_pAni->start();
	//m_pAni->setFPS(1);

	m_nScalar = 4;
	m_nFrameX =0;
	m_nFrameY=0;
	m_isOnce = false;
	return S_OK;
}
 
void objTree::release()
{
	//delete m_pAni;
}

void objTree::update()
{
	//m_pAni->frameUpdate(TIMEMANAGER->getElapsedTime());


	//m_nFrameX;
	//m_nFrameY;

	if (m_ptree)
	{		
		//PLAYTIMEMANAGER->getMin();
		if (PLAYTIMEMANAGER->getMin() % 5 == 0 && !m_isOnce)
		{
			m_isOnce = true;
			m_nFrameX++;
			m_ptree->setFrameX(m_nFrameX);
			//if (m_nFrameX > m_ptree->getMaxFrameX())
			if (m_nFrameX > 4)
			{
				m_nFrameX = 4;
			}
		}
		else if (PLAYTIMEMANAGER->getMin() % 5 != 0)
			m_isOnce = false;

	}
}

void objTree::render(HDC hdc)
{
	//m_ptree->render(hdc, 0, 45);
	//m_ptree->aniRender(hdc, 200, 50, m_pAni, 1);
}

void objTree::render(HDC hdc, int x, int y)
{
	//m_ptree->render(hdc, 0, 45);
	//m_ptree->aniRender(hdc, x, y, m_pAni, 4);

	//m_ptree->frameRender(hdc, x - m_ptree->getFrameWidth()*3, y - m_ptree->getFrameHeight()*m_nScalar, m_nFrameX, m_nFrameY, m_nScalar);
	m_ptree->frameRender(hdc, x - m_ptree->getFrameWidth()*1.5, y - m_ptree->getFrameHeight()*m_nScalar, m_nFrameX, m_nFrameY, m_nScalar);
}
