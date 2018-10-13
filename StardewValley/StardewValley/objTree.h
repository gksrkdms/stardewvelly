#pragma once
#include "mapObject.h"

class animation;

class objTree : public mapObject
{
private:
	image* m_ptree;
	animation *	m_pAni;			// 나무 프레임랜더
	
public:
	objTree();
	~objTree();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
};

