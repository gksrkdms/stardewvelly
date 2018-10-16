#pragma once
#include <list>

class mapObject;
class player;

class objectManager
{
private:
	list<mapObject*> m_listObjTree;
	list<mapObject*>::iterator m_iterObjTree;
		
	list<mapObject*> m_listObjCrop;
	list<mapObject*>::iterator m_iterObjCrop;

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

	void setTree(int x, int y, int id); // 나무 set
	void setCrop(int x, int y, int id); // 작물 set
	void setNpc(int x, int y, int id); // Npc set

	void getPlayer(player* player);
};

