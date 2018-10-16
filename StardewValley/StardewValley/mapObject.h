#pragma once
class player;

class mapObject
{
protected:
	int m_nObjX;
	int m_nObjY;
	//int m_nFrameY;

	int m_nStrength; // ����
	bool m_isOnce; // �ð����� �ѹ��� üũ�ϱ� ���ؼ� ���

	SYNTHESIZE(int, m_nFrameX, FrameX);
	SYNTHESIZE(int, m_nFrameY, FrameY);

	player* m_player;

public:
	mapObject();
	virtual ~mapObject();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void render(HDC hdc, int x, int y);

	virtual void getPlayer(player* player) { m_player = player; }
	virtual void objectPosition(int x, int y); // object position setting

};

