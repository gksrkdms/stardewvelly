#pragma once
#include "singletonBase.h"

enum WEEK {
	MON, TUE, WED, THUR, FRI, SAT, SUN
};

class gametime:public singletonBase<gametime>
{
private:
	image * m_pdark;

	WEEK m_week;

	int m_alpha;
	//float m_zulaTime;
	int m_zulaTime;

	int m_hour;
	int m_min;

	bool m_isAction; // hour 덧셈 한번만 실행되게 하려고 넣음
	bool m_isCount; // 10min count

	int m_convertHour; // 게임시간단위로 한시간일때 현실시간으로 몇초인지 환산한 값

	int m_day; // 날
	int m_month; // 달

public:
	gametime();
	~gametime();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
};

