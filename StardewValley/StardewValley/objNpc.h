#pragma once
#include "mapObject.h"
class objNpc :
	public mapObject
{
public:
	objNpc();
	~objNpc();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void render(HDC hdc, int x, int y);
};

