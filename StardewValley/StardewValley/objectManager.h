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

	list<mapObject*> m_listObjTree;
	list<mapObject*>::iterator m_iterObjTree;

	list<mapObject*> m_listObjCrop;
	list<mapObject*>::iterator m_iterObjCrop;

	// vector로 npc세팅
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
	void Treerender(HDC hdc);
	void Npcrender(HDC hdc);

	void setTree(int x, int y, int id, int index); // 나무 set
	void setCrop(int x, int y, int id, int index); // 작물 set
	void setNpc(int x, int y, int id, int index); // Npc set

	int harvest(int index);	// 수확
	void deleteObj(int index); // 오브젝트 삭제

	list<mapObject*> getObject() { return m_listObj; }

	void setWaterFarm(int index);

	void getPlayer(player* player);
};

