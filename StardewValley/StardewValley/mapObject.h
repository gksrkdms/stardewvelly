#pragma once
class mapObject
{
public:
	mapObject();
	virtual ~mapObject();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
};

