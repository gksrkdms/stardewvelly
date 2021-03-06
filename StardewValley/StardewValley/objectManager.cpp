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

void objectManager::Treerender(HDC hdc)
{
	for (m_iterObjTree = m_listObjTree.begin(); m_iterObjTree != m_listObjTree.end(); m_iterObjTree++)
	{
		(*m_iterObjTree)->render(hdc);
	}
}

void objectManager::Npcrender(HDC hdc)
{
	for (m_iterObjNpc = m_listObjNpc.begin(); m_iterObjNpc != m_listObjNpc.end(); m_iterObjNpc++)
	{
		(*m_iterObjNpc)->render(hdc);
	}
}

void objectManager::setTree(int x, int y, int id, int index)
{
	mapObject* m_pObjTree;
	m_pObjTree = new objTree;
	m_pObjTree->init(x,y, id, index);
	m_listObj.push_back(m_pObjTree);
}

void objectManager::setCrop(int x, int y, int id, int index)
{
	mapObject* m_pObjectCrop;
	m_pObjectCrop = new objCrop;
	m_pObjectCrop->init(x, y, id, index);
	m_listObj.push_back(m_pObjectCrop);
}

void objectManager::setNpc(int x, int y, int id, int index)
{
	mapObject* m_pObjectNpc;
	m_pObjectNpc = new objNpc;
	m_pObjectNpc->init(x, y, id, index);
	m_listObjNpc.push_back(m_pObjectNpc);
}

void objectManager::setCropXY(int x, int y, int index)
{
	for (m_iterObj = m_listObj.begin(); m_iterObj != m_listObj.end(); m_iterObj++)
	{
		if ((*m_iterObj)->getIndex() == index)
		{
			(*m_iterObj)->setXY(x, y);
		}
	}
}

int objectManager::harvest(int index)
{
	for (m_iterObj = m_listObj.begin(); m_iterObj != m_listObj.end(); m_iterObj++)
	{
		if ((*m_iterObj)->getIndex() == index)
		{
			return (*m_iterObj)->getHarvestId();
		}
	}
}

int objectManager::getCropRemain(int index)
{
	for (m_iterObj = m_listObj.begin(); m_iterObj != m_listObj.end(); m_iterObj++)
	{
		if ((*m_iterObj)->getIndex() == index)
		{
			return (*m_iterObj)->getNum();
		}
	}
}

void objectManager::setCropRemain(int index)
{
	for (m_iterObj = m_listObj.begin(); m_iterObj != m_listObj.end(); m_iterObj++)
	{
		if ((*m_iterObj)->getIndex() == index)
		{
			(*m_iterObj)->setNum((*m_iterObj)->getNum() - 1);
			(*m_iterObj)->setFrameX((*m_iterObj)->getFrameX() - 3);
			(*m_iterObj)->setHarvest(false);
		}
	}
}

void objectManager::deleteObj(int index)
{
	for (m_iterObj = m_listObj.begin(); m_iterObj != m_listObj.end();)
	{
		if ((*m_iterObj)->getIndex() == index)
		{
			delete (*m_iterObj);
			m_listObj.erase(m_iterObj++); break;
		}
		
		else
			m_iterObj++;
	}
	
}

void objectManager::setWaterFarm(int index)
{
	for (m_iterObj = m_listObj.begin(); m_iterObj != m_listObj.end(); m_iterObj++)
	{
		if ((*m_iterObj)->getIndex() == index)
			(*m_iterObj)->setWaterTile(true);
	}
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
