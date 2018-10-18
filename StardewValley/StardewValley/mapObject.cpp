#include "stdafx.h"
#include "mapObject.h"


mapObject::mapObject()
{
}


mapObject::~mapObject()
{
}

HRESULT mapObject::init(int seedNum, int tileIndex, int posX, int posY)
{
	return S_OK;
}

void mapObject::release()
{
}

void mapObject::update(int x, int y)
{
}

void mapObject::render(HDC hdc)
{
}

void mapObject::render(HDC hdc, int x, int y)
{
}
