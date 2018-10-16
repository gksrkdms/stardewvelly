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

	virtual HRESULT init();
	virtual HRESULT init(int x, int y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
};

