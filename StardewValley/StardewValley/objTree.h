#pragma once
#include "mapObject.h"

class animation;

class objTree : public mapObject
{
private:
	image* m_ptree;

	RECT m_pPlayer;
	RECT m_pTree;
	RECT m_rcTemp;

	bool m_isOverlap;
	

public:
	objTree();
	~objTree();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void update(int x, int y);
	virtual void render(HDC hdc);
	virtual void render(HDC hdc, int x, int y);

	virtual void getPlayer(player* player) { m_player = player; }
	
	virtual void objectPosition(int x, int y);
};

