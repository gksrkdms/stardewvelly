#include "stdafx.h"
#include "progressBarHp.h"


HRESULT progressBarHp::init(float x, float y, float width, float height)
{
	m_fX = x;
	m_fY = y;
	m_fHeight = height;

	m_imgTop = IMAGEMANAGER->findImage("hp_energy_top");

	return S_OK;
}

void progressBarHp::release()
{
}

void progressBarHp::update()
{
}

void progressBarHp::render(HDC hdc)
{
	IMAGEMANAGER->findImage("hp_energy_top")->render(hdc, m_fX + 4, m_fY + 4 + (m_imgTop->getHeight() - m_fHeight),
		0, 0, m_imgTop->getWidth(), m_imgTop->getHeight() - (m_imgTop->getHeight() - m_fHeight));
}

void progressBarHp::setGauge(float currGauge, float maxGauge)
{
	m_fHeight = (currGauge / maxGauge) * m_imgTop->getHeight();
}

progressBarHp::progressBarHp()
{
}


progressBarHp::~progressBarHp()
{
}
