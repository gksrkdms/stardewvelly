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

	bool m_isAction; // hour ���� �ѹ��� ����ǰ� �Ϸ��� ����
	bool m_isCount; // 10min count

	int m_convertHour; // ���ӽð������� �ѽð��϶� ���ǽð����� �������� ȯ���� ��

	int m_day; // ��
	int m_month; // ��

public:
	gametime();
	~gametime();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
};

