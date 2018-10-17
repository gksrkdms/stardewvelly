#include "stdafx.h"
#include "objectManager.h"

#include "objTree.h"
#include "objCrop.h"
#include "objNpc.h"

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
	for (m_iterObj = m_listObj.begin(); m_iterObj != m_listObj.end(); m_iterObj++)
	{
		delete (*m_iterObj);
	}
	m_listObj.clear();

	for (m_iterObjNpc = m_listObjNpc.begin(); m_iterObjNpc != m_listObjNpc.end(); m_iterObjNpc++)
	{
		delete (*m_iterObjNpc);
	}
	m_listObjNpc.clear();
}

void objectManager::update()
{
	for (m_iterObj = m_listObj.begin(); m_iterObj != m_listObj.end(); m_iterObj++)
	{
		(*m_iterObj)->update();
	}

	for (m_iterObjNpc = m_listObjNpc.begin(); m_iterObjNpc != m_listObjNpc.end(); m_iterObjNpc++)
	{
		(*m_iterObjNpc)->update();
	}
}

void objectManager::render(HDC hdc)
{
	for (m_iterObj = m_listObj.begin(); m_iterObj != m_listObj.end(); m_iterObj++)
	{
		(*m_iterObj)->render(hdc);
	}
}

void objectManager::Npcrender(HDC hdc)
{
	for (m_iterObjNpc = m_listObjNpc.begin(); m_iterObjNpc != m_listObjNpc.end(); m_iterObjNpc++)
	{
		(*m_iterObjNpc)->render(hdc);
	}
}

void objectManager::setTree(int x, int y, int id)
{
	mapObject* m_pObjTree;
	m_pObjTree = new objTree;
	m_pObjTree->init(x,y, id);
	m_listObj.push_back(m_pObjTree);
}

void objectManager::setCrop(int x, int y, int id)
{
	mapObject* m_pObjectCrop;
	m_pObjectCrop = new objCrop;
	m_pObjectCrop->init(x, y, id);
	m_listObj.push_back(m_pObjectCrop);
}

void objectManager::setNpc(int x, int y, int id)
{
	mapObject* m_pObjectNpc;
	m_pObjectNpc = new objNpc;
	m_pObjectNpc->init(x, y, id);
	m_listObjNpc.push_back(m_pObjectNpc);
}

void objectManager::deleteTree(int x, int y)
{
	for (m_iterObj = m_listObj.begin(); m_iterObj != m_listObj.end();)
	{
		if (((*m_iterObj)->getX() <= x + 2 || (*m_iterObj)->getX() >= x -2) && (*m_iterObj)->getY() == y)
		{
			m_listObj.erase(m_iterObj++);
		}

		else if((*m_iterObj)->getX() == x && ((*m_iterObj)->getY() <= y +2 || (*m_iterObj)->getY() >= y-2))
		{
			m_listObj.erase(m_iterObj++);
		}

		else
			m_iterObj++;
	}
	
}

void objectManager::deleteCrop(int x, int y)
{
}

void objectManager::getPlayer(player * player)
{
	for (m_iterObj = m_listObj.begin(); m_iterObj != m_listObj.end(); m_iterObj++)
	{
		(*m_iterObj)->getPlayer(player);
	}

	for (m_iterObjNpc = m_listObjNpc.begin(); m_iterObjNpc != m_listObjNpc.end(); m_iterObjNpc++)
	{
		(*m_iterObjNpc)->getPlayer(player);
	}
}
