#include "stdafx.h"
#include "mapObject.h"

mapObject::mapObject()
{
}


mapObject::~mapObject()
{
}

HRESULT mapObject::init()
{
	return S_OK;
}

HRESULT mapObject::init(int x, int y, int id, int index)
{
	return S_OK;
}

void mapObject::release()
{
}

void mapObject::update()
{
}

void mapObject::render(HDC hdc)
{
}

void mapObject::setXY(int x, int y)
{
}
