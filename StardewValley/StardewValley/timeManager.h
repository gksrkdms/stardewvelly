#pragma once
#include "singletonBase.h"
#include "timer.h"
//class timer;

class timeManager : public singletonBase<timeManager>
{
private:
	timer * m_timer;

public:
	HRESULT init();
	void release();
	
	void update(float lockFPS = 0.0f);
	void render(HDC hdc);

	inline float getElapsedTime() { return m_timer->getElapsedTime(); }

	inline void setZulaTime(float zulatime) { m_timer->setZulaTime(zulatime); }
	inline float getZulaTime() { return m_timer->getZulaTime(); }

	timeManager();
	~timeManager();
};

