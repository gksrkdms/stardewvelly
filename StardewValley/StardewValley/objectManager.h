#pragma once
#include <list>
#include <vector>
#include "singletonBase.h"

class mapObject;
class player;

class objectManager:public singletonBase<objectManager>
{
private:
	list<mapObject*> m_listObj;
	list<mapObject*>::iterator m_iterObj;

	vector<mapObject*> m_listObjNpc;
	vector<mapObject*>::iterator m_iterObjNpc;

	player* m_player;
	//mapObject* m_pObjTree;
	//mapObject* m_pObjectCrop;

public:
	objectManager();
	~objectManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void Npcrender(HDC hdc);

	void setTree(int x, int y, int id); // ���� set
	void setCrop(int x, int y, int id); // �۹� set
	void setNpc(int x, int y, int id); // Npc set

	void deleteTree(int x, int y); // ���� ����
	void deleteCrop(int x, int y); // �۹� ����

	void getPlayer(player* player);
};

