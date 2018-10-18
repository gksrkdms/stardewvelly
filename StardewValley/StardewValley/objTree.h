#pragma once
#include "mapObject.h"

class animation;

enum TREE_TYPE {
	TREE_1, TREE_2
};

class objTree : public mapObject
{
private:
	image* m_ptree;
	
	bool m_isOverlap;
	TREE_TYPE m_treeType;
public:
	objTree();
	~objTree();

	virtual HRESULT init();
	virtual HRESULT init(int x, int y, int id, int index);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void getPlayer(player* player) { m_player = player; }
	
};

