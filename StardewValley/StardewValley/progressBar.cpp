#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(float x, float y, float width, float height)
{
	m_fX = x;
	m_fY = y;
	m_fWidth = width;

	m_imgBottom = IMAGEMANAGER->addImage("watergauge_bottom", "image/Stardew Valley/ui/watergauge_bottom.bmp", 56, 20, true, RGB(255, 0, 255));
	m_imgTop = IMAGEMANAGER->addImage("watergauge_top", "image/Stardew Valley/ui/watergauge_top.bmp", 48, 8, true, RGB(255, 0, 255));

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
}

void progressBar::render(HDC hdc)
{
	IMAGEMANAGER->findImage("watergauge_bottom")->render(hdc, m_fX, m_fY);
	IMAGEMANAGER->findImage("watergauge_top")->render(hdc, m_fX + 4, m_fY + 4,
		0, 0, m_fWidth, m_imgTop->getHeight());
}

void progressBar::alphaRender(HDC hdc)
{
	IMAGEMANAGER->findImage("watergauge_bottom")->alphaRender(hdc, m_fX, m_fY, 150);
	IMAGEMANAGER->findImage("watergauge_top")->alphaRender(hdc, m_fX + 4, m_fY + 4,
		0, 0, m_fWidth, m_imgTop->getHeight(), 150);
}

void progressBar::setGauge(float currGauge, float maxGauge)
{
	m_fWidth = (currGauge / maxGauge) * m_imgTop->getWidth();
}

progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}
