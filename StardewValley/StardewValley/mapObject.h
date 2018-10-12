#pragma once

class mapObject
{
protected:
	int m_nFrameX;
	int m_nFrameY;
	int m_nStrength;

public:
	mapObject();
	virtual ~mapObject();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
};

