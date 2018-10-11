#pragma once
#include "singletonBase.h"

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

	int m_hour;
	int m_min;
	int m_day; // ��
	int m_month; // ��

	bool m_isAction; // hour ���� �ѹ��� ����ǰ� �Ϸ��� ����
	bool m_isCount; // 10min count

	int m_convertHour; // ���ӽð������� �ѽð��϶� ���ǽð����� �������� ȯ���� ��
	
	int m_nClockScalar; // �ð� ũ�� ����

public:
	gametime();
	~gametime();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
};

