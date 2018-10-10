#pragma once
#include "singletonBase.h"
class player;
class camera : public singletonBase<camera>
{
private:
	int	m_nX;
	int	m_nY;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setFocus(player* play);

	int getX() { return m_nX; }
	int getY() { return m_nY; }

	void setX(int x);
	void setY(int y);

	camera();
	~camera();
};

