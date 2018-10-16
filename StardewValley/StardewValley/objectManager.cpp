#include "stdafx.h"
#include "objectManager.h"

#include "objTree.h"
#include "objCrop.h"

objectManager::objectManager()
{
}


objectManager::~objectManager()
{
}

HRESULT objectManager::init()
{
	return S_OK;
}

void objectManager::release()
{
}

void objectManager::update()
{
	for (m_iterObjTree = m_listObjTree.begin(); m_iterObjTree != m_listObjTree.end(); m_iterObjTree++)
	{
		(*m_iterObjTree)->update();
	}
}

void objectManager::updateTree(int x, int y)
{
	for (m_iterObjTree = m_listObjTree.begin(); m_iterObjTree != m_listObjTree.end(); m_iterObjTree++)
	{
		(*m_iterObjTree)->update();
		(*m_iterObjTree)->objectPosition(x, y);

	}
}

void objectManager::render(HDC hdc)
{
	for (m_iterObjTree = m_listObjTree.begin(); m_iterObjTree != m_listObjTree.end(); m_iterObjTree++)
	{
		(*m_iterObjTree)->render(hdc);
	}
}

void objectManager::render(HDC hdc, int x, int y)
{
	for (m_iterObjTree = m_listObjTree.begin(); m_iterObjTree != m_listObjTree.end(); m_iterObjTree++)
	{
		(*m_iterObjTree)->render(hdc,x,y);
	}
}

void objectManager::setTree(int x, int y)
{
	mapObject* m_pObjTree;
	m_pObjTree = new objTree;
	m_pObjTree->init();
	m_pObjTree->objectPosition(x,y);
	m_listObjTree.push_back(m_pObjTree);
}

void objectManager::getPlayer(player * player)
{
	for (m_iterObjTree = m_listObjTree.begin(); m_iterObjTree != m_listObjTree.end(); m_iterObjTree++)
	{
		(*m_iterObjTree)->getPlayer(player);
	}
}
