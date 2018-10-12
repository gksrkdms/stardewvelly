#pragma once
#include "singletonBase.h"

//�ð� �̹��� ����
#define CLOCK_SCALAR 4

// ���ӽð������� �ѽð��϶� ���ǽð����� �������� ȯ���� ��
#define CONVER_HOUR 60

enum WEEK {
	MON, TUE, WED, THUR, FRI, SAT, SUN
};

class gametime:public singletonBase<gametime>
{
private:
	image * m_pdark; // �� ����
	image * m_pClock; // �ð�
	image * m_pMinutehand; // ��ħ

	WEEK m_week;

	int m_alpha; // ���ķ��� ���İ�
	int m_zulaTime; // ���� ��ü�ð�
	float m_nMinAngle; // ��ħ ����

	int m_hour;
	int m_min;
	int m_day; // ��
	int m_month; // ��
	   
	bool m_isAction; // hour ���� �ѹ��� ����ǰ� �Ϸ��� ����
	bool m_isCount; // 10min count
	bool m_isNight; // ������ Ȯ��

	int m_nPrintMin;

public:
	gametime();
	~gametime();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
};

