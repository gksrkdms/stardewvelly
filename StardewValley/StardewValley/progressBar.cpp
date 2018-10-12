#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(float x, float y, float width, float height)
{
	m_fX = x;
	m_fY = y;

	//m_rc = RectMake(m_fX, m_fY, m_fWidth, height);

	m_isPlayer = true;

	return S_OK;
}

HRESULT progressBar::init()
{


	//m_rc = RectMake(m_fX, m_fY, m_fWidth, height);

	m_isPlayer = false;

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
	

}

void progressBar::setGauge(float currGauge, float maxGauge)
{
	m_fgauge = ((currGauge / maxGauge) * m_imgBottom->getHeight());
	m_nLenght = 110 * (currGauge / maxGauge);
}

progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}
