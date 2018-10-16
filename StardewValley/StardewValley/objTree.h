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
	virtual HRESULT init(int x, int y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void getPlayer(player* player) { m_player = player; }
	
};

