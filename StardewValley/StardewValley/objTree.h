#pragma once
#include "mapObject.h"

class objTree : public mapObject
{
private:
	image* m_ptree;


public:
	objTree();
	~objTree();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
};

