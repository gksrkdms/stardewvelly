#pragma once
#include "progressBar.h"
class progressBarHp : public progressBar
{
public:
	HRESULT init(float x, float y, float width, float height);
	void release();
	void update();
	void render(HDC hdc);

	void setGauge(float currGauge, float maxGauge);

	progressBarHp();
	~progressBarHp();
};

