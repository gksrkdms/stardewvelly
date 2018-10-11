#include "stdafx.h"
#include "gametime.h"


gametime::gametime()
{
}


gametime::~gametime()
{
}

HRESULT gametime::init()
{
	m_pdark = IMAGEMANAGER->findImage("dark");
	m_pClock = IMAGEMANAGER->findImage("clock");
	m_pMinutehand = IMAGEMANAGER->findImage("minutehand");
	TIMEMANAGER->setZulaTime(0);

	m_hour = 19;
	m_min = 0;
	m_zulaTime = 0;
	m_isAction = false;
	m_isCount = true;
	m_alpha = 0;
	m_nConvertHour = 60;
	m_day = 1;
	m_month = 1;
	m_isNight = false;

	return S_OK;
}

void gametime::release()
{
}

void gametime::update()
{
	m_zulaTime = (int)TIMEMANAGER->getZulaTime();

	//시간
	if (m_zulaTime % m_nConvertHour == 0 && !m_isAction && m_zulaTime != 0)
	{
		m_isAction = true;
		m_hour = m_hour + 1;
		m_min = 0;
	}
	//분
	else if (m_zulaTime % m_nConvertHour != 0)
	{
		if (m_isAction)
			m_isAction = false;
		m_min = m_zulaTime % m_nConvertHour;
	}

	// 오후 8시 이후에 어두워짐
	if (m_hour >= 20)
	{
		if (!m_isNight)
		{
			m_alpha = 100;
			m_isNight = true;
		}

		// 10분 단위로 자름, 10분마다 어두워짐
		if (m_min % 10 == 0 && m_isCount)
		{
			m_isCount = false;
			m_alpha = m_alpha + 5;

			if (m_alpha >= 200)
				m_alpha = 200;
		}
		else if (m_min % 10 != 0)
		{
			if (!m_isCount)
				m_isCount = true;
		}
	}

	// 날짜
	if (m_hour >= 24)
	{
		m_hour = 0;
		m_day = m_day + 1;

		//달
		if (m_day > 28)
		{
			m_day = 1;
			m_month = m_month + 1;
			if (m_month > 12)
			{
				m_day = 1;
				m_month = 1;
			}
		}
	}

	//아침
	if (m_hour == 6)
	{
		m_alpha = 0;
		m_isNight = false;
	}

	//요일
	switch (m_day % 7)
	{
	case 0:
		m_week = SUN;
		break;

	case 1:
		m_week = MON;

		break;

	case 2:
		m_week = TUE;

		break;

	case 3:
		m_week = WED;

		break;

	case 4:
		m_week = THUR;

		break;

	case 5:
		m_week = FRI;

		break;

	case 6:
		m_week = SAT;
		break;

	default:
		break;
	}
}

void gametime::render(HDC hdc)
{
	if (m_pdark)
		m_pdark->alphaRender(hdc, 0, 0, m_alpha);

	// 시계 랜더
	if(m_pClock)
		m_pClock->render(hdc, WINSIZEX - m_pClock->getWidth()*CLOCK_SCALAR -10, 20, CLOCK_SCALAR);
		m_pMinutehand->render(hdc, WINSIZEX - m_pClock->getWidth()*CLOCK_SCALAR +40, 20, CLOCK_SCALAR);

	TIMEMANAGER->render(hdc);

	//그림추가

	char str[256];
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0, 0, 0));

	sprintf_s(str, 256, "time : %f", TIMEMANAGER->getZulaTime());
	TextOut(hdc, 0, 150, str, strlen(str));

	sprintf_s(str, 256, "zulatime : %f", m_zulaTime);
	TextOut(hdc, 0, 200, str, strlen(str));

	sprintf_s(str, 256, "%d : ", m_hour);
	TextOut(hdc, WINSIZEX - m_pClock->getWidth()*CLOCK_SCALAR + 120, 110, str, strlen(str));

	sprintf_s(str, 256, "%d", m_min);
	TextOut(hdc, WINSIZEX - m_pClock->getWidth()*CLOCK_SCALAR + 150, 110, str, strlen(str));

	sprintf_s(str, 256, "day : %d", m_day);
	TextOut(hdc, 400, 250, str, strlen(str));
}
