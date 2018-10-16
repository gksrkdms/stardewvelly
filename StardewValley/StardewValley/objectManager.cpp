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
	for (m_iterObjTree = m_listObjTree.begin(); m_iterObjTree != m_listObjTree.end(); m_iterObjTree++)
	{
		delete (*m_iterObjTree);
	}
	m_listObjTree.clear();
}

void objectManager::update()
{
	for (m_iterObjTree = m_listObjTree.begin(); m_iterObjTree != m_listObjTree.end(); m_iterObjTree++)
	{
		(*m_iterObjTree)->update();
	}
}

void objectManager::render(HDC hdc)
{
	for (m_iterObjTree = m_listObjTree.begin(); m_iterObjTree != m_listObjTree.end(); m_iterObjTree++)
	{
		(*m_iterObjTree)->render(hdc);
	}
}

void objectManager::setTree(int x, int y, int id)
{
	mapObject* m_pObjTree;
	m_pObjTree = new objTree;
	m_pObjTree->init(x,y, id);
	m_listObjTree.push_back(m_pObjTree);
}

void objectManager::setCrop(int x, int y, int id)
{
}

void objectManager::setNpc(int x, int y, int id)
{
}

void objectManager::getPlayer(player * player)
{
	for (m_iterObjTree = m_listObjTree.begin(); m_iterObjTree != m_listObjTree.end(); m_iterObjTree++)
	{
		(*m_iterObjTree)->getPlayer(player);
	}
}
