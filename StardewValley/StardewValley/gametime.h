#pragma once
#include "singletonBase.h"

//시계 이미지 배율
#define CLOCK_SCALAR 4

// 게임시간단위로 한시간일때 현실시간으로 몇초인지 환산한 값
#define CONVER_HOUR 60

enum WEEK {
	MON, TUE, WED, THUR, FRI, SAT, SUN
};

class gametime:public singletonBase<gametime>
{
private:
	image * m_pdark; // 밤 랜더
	image * m_pClock; // 시계
	image * m_pMinutehand; // 분침

	WEEK m_week;

	int m_alpha; // 알파랜더 알파값
	int m_zulaTime; // 게임 전체시간
	float m_nMinAngle; // 분침 각도

	int m_hour;
	int m_min;
	int m_day; // 날
	int m_month; // 달
	   
	bool m_isAction; // hour 덧셈 한번만 실행되게 하려고 넣음
	bool m_isCount; // 10min count
	bool m_isNight; // 밤인지 확인

	int m_nPrintMin;

public:
	gametime();
	~gametime();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
};

