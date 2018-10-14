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

	m_nScalar = 4;
	m_nFrameX =0;
	m_nFrameY=0;
	m_isOnce = false;
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
}

void objTree::render(HDC hdc)
{

}

void objTree::render(HDC hdc, int x, int y)
{
	//m_ptree->frameRender(hdc, x - m_ptree->getFrameWidth()*3, y - m_ptree->getFrameHeight()*m_nScalar, m_nFrameX, m_nFrameY, m_nScalar);
	m_ptree->frameRender(hdc, x - m_ptree->getFrameWidth()*1.5, y - m_ptree->getFrameHeight()*m_nScalar, m_nFrameX, m_nFrameY, m_nScalar);
}
