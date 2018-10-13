#pragma once

class mapObject
{
protected:
	//int m_nFrameX;
	//int m_nFrameY;
	int m_nStrength; // ����
	bool m_isOnce; // �ð����� �ѹ��� üũ�ϱ� ���ؼ� ���
	int m_nScalar; //�̹��� ũ��

	SYNTHESIZE(int, m_nFrameX, FrameX);
	SYNTHESIZE(int, m_nFrameY, FrameY);


public:
	mapObject();
	virtual ~mapObject();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void render(HDC hdc, int x, int y);

};

