#pragma once
#include "mapObject.h"

enum CropKINDS
{
	STRAWBERRY,
	CARROT
};

class item;

class objCrop : public mapObject
{
private:
	image * m_pCrop;
	item* m_pitem;

public:
	objCrop();
	~objCrop();

	HRESULT init(int seedNum, int tileIndex, int posX, int posY);
	virtual void release();
	virtual void update(int x, int y);
	virtual void render(HDC hdc);
	virtual void render(HDC hdc, int x, int y);
};

