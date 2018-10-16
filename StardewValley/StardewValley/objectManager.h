#pragma once
#include <list>

class mapObject;
class player;

class objectManager
{
private:
	list<mapObject*> m_listObjTree;
	list<mapObject*>::iterator m_iterObjTree;

	player* m_player;
	mapObject* m_pObjTree;
	mapObject* m_pObjectCrop;
public:
	objectManager();
	~objectManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setTree(int x, int y);

	void getPlayer(player* player);
};

