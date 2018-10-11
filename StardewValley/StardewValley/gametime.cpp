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

	m_hour = 6;
	m_min = 0;
	m_zulaTime = 0;
	m_isAction = false;
	m_isCount = true;
	m_alpha = 0;
	m_convertHour = 60;
	m_day = 1;
	m_month = 1;

	m_nClockScalar = 3;

	return S_OK;
}

void gametime::release()
{
}

void gametime::update()
{
	m_zulaTime = (int)TIMEMANAGER->getZulaTime();

	//�ð�
	if (m_zulaTime % m_convertHour == 0 && !m_isAction && m_zulaTime != 0)
	{
		m_isAction = true;
		m_hour = m_hour + 1;
		m_min = 0;
	}
	//��
	else if (m_zulaTime % m_convertHour != 0)
	{
		if (m_isAction)
			m_isAction = false;
		m_min = m_zulaTime % m_convertHour;
	}

	// ���� 8�� ���Ŀ� ��ο���
	if (m_hour >= 20)
	{
		m_alpha = 100;

		// 10�� ������ �ڸ�, 10�и��� ��ο���
		if (m_min % 10 == 0 && m_isCount)
		{
			m_isCount = false;
			m_alpha = m_alpha + 5;
		}
		else if (m_min % 10 != 0)
		{
			if (!m_isCount)
				m_isCount = true;
		}
	}

	// ��¥
	if (m_hour > 24)
	{
		m_hour = 1;
		m_day = m_day + 1;

		//��
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

	// �ð� ����
	if(m_pClock)
		m_pClock->render(hdc, WINSIZEX - m_pClock->getWidth()*m_nClockScalar-10, 20, m_nClockScalar);
		m_pMinutehand->render(hdc, WINSIZEX - m_pClock->getWidth()*m_nClockScalar+40, 20, m_nClockScalar);

	TIMEMANAGER->render(hdc);

	//�׸��߰�

	char str[256];
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0, 0, 0));

	sprintf_s(str, 256, "time : %f", TIMEMANAGER->getZulaTime());
	TextOut(hdc, 0, 150, str, strlen(str));

	sprintf_s(str, 256, "zulatime : %f", m_zulaTime);
	TextOut(hdc, 0, 200, str, strlen(str));

	sprintf_s(str, 256, "%d : ", m_hour);
	TextOut(hdc, WINSIZEX - m_pClock->getWidth()*m_nClockScalar + 120, 110, str, strlen(str));

	sprintf_s(str, 256, "%d", m_min);
	TextOut(hdc, WINSIZEX - m_pClock->getWidth()*m_nClockScalar + 150, 110, str, strlen(str));

	sprintf_s(str, 256, "day : %d", m_day);
	TextOut(hdc, 400, 250, str, strlen(str));
}
