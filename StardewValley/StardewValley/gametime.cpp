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
	m_day = 1;
	m_month = 1;
	m_isNight = false;
	m_nMinAngle = 180;
	m_nPrintMin = 0;

	return S_OK;
}

void gametime::release()
{
}

void gametime::update()
{
	m_zulaTime = (int)TIMEMANAGER->getZulaTime();

	//시간
	if (m_zulaTime % CONVER_HOUR == 0 && !m_isAction && m_zulaTime != 0)
	{
		m_isAction = true;
		m_hour = m_hour + 1;
		m_min = 0;
		m_nPrintMin = 0;
	}

	//분
	else if (m_zulaTime % CONVER_HOUR != 0)
	{
		if (m_isAction)
			m_isAction = false;
		m_min = m_zulaTime % CONVER_HOUR;

		m_nPrintMin = 10*(m_min / 10);
	}

	// 오후 8시 이후에 어두워짐
	if (m_hour >= 20)
	{
		if (!m_isNight)
		{
			m_alpha = 100;
			m_isNight = true;
		}
	}

	// 10분 단위로 자름, 10분마다 어두워짐
	if (m_min % 10 == 0 && m_isCount)
	{
		m_isCount = false;
		m_nMinAngle = m_nMinAngle + 1.5;

		if (m_isNight)
		{
			m_alpha = m_alpha + 5;

			if (m_alpha >= 200)
				m_alpha = 200;
		}

	}
	else if (m_min % 10 != 0)
	{
		if (!m_isCount)
			m_isCount = true;
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

	//새벽 3시면 강제로 다음날됨
	if (m_hour == 3)
	{
		m_hour = 6;
	}

	//아침
	if (m_hour == 6)
	{
		m_alpha = 0;
		m_isNight = false;
		m_nMinAngle = 180;
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
		m_pClock->render(hdc, WINSIZEX - m_pClock->getWidth()*GAME_SCALAR -10, 20, GAME_SCALAR);
		m_pMinutehand->rotateRender(hdc, m_nMinAngle, WINSIZEX - m_pClock->getWidth()*GAME_SCALAR -20, -26, GAME_SCALAR);
	//m_pMinutehand->rotateRender(hdc, 0, WINSIZEX - m_pClock->getWidth()*CLOCK_SCALAR + 40, 20+ m_pClock->getHeight(), CLOCK_SCALAR);
		//m_pMinutehand->render(hdc, WINSIZEX - m_pClock->getWidth()*CLOCK_SCALAR +40, 20, CLOCK_SCALAR);

	TIMEMANAGER->render(hdc);

	//그림추가

	char str[256];
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0, 0, 0));
	HFONT myFont = CreateFont(25, 0, 0, 0, 800, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "모리스9");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	switch (m_week)
	{
	case MON:
		TextOut(hdc, WINSIZEX - m_pClock->getWidth()*GAME_SCALAR + 130, 45, "월요일.", strlen("월요일."));
		break;
	case TUE:
		TextOut(hdc, WINSIZEX - m_pClock->getWidth()*GAME_SCALAR + 130, 45, "화요일.", strlen("화요일."));
		break;
	case WED:
		TextOut(hdc, WINSIZEX - m_pClock->getWidth()*GAME_SCALAR + 130, 45, "수요일.", strlen("수요일."));
		break;
	case THUR:
		TextOut(hdc, WINSIZEX - m_pClock->getWidth()*GAME_SCALAR + 130, 45, "목요일.", strlen("목요일."));
		break;
	case FRI:
		TextOut(hdc, WINSIZEX - m_pClock->getWidth()*GAME_SCALAR + 130, 45, "금요일.", strlen("금요일."));
		break;
	case SAT:
		TextOut(hdc, WINSIZEX - m_pClock->getWidth()*GAME_SCALAR + 130, 45, "토요일.", strlen("토요일."));
		break;
	case SUN:
		TextOut(hdc, WINSIZEX - m_pClock->getWidth()*GAME_SCALAR + 130, 45, "일요일.", strlen("일요일."));
		break;
	default:
		break;
	}


	/*sprintf_s(str, 256, "%s", m_zulaTime);
	TextOut(hdc, 0, 200, str, strlen(str));*/

	//sprintf_s(str, 256, "시간은영어로 time : %f", TIMEMANAGER->getZulaTime());
	//TextOut(hdc, 0, 150, str, strlen(str));

	//sprintf_s(str, 256, "zulatime : %f", m_zulaTime);
	//TextOut(hdc, 0, 200, str, strlen(str));

	sprintf_s(str, 256, "%d : ", m_hour);
	TextOut(hdc, WINSIZEX - m_pClock->getWidth()*GAME_SCALAR + 150, 135, str, strlen(str));

	sprintf_s(str, 256, "%d", m_nPrintMin);
	TextOut(hdc, WINSIZEX - m_pClock->getWidth()*GAME_SCALAR + 190, 135, str, strlen(str));

	SelectObject(hdc, oldFont);
	DeleteObject(myFont);

	sprintf_s(str, 256, "%d", m_day);
	TextOut(hdc, WINSIZEX - m_pClock->getWidth()*GAME_SCALAR + 215, 50, str, strlen(str));

}
