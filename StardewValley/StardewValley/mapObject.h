#pragma once
class player;

class mapObject
{
protected:
	int m_nObjX; // objx
	int m_nObjY; // objy

	int m_nStrength; // ����
	bool m_isOnce; // �ð����� �ѹ��� üũ�ϱ� ���ؼ� ���

	SYNTHESIZE(int, m_nFrameX, FrameX);
	SYNTHESIZE(int, m_nFrameY, FrameY);

	player* m_player;

public:
	mapObject();
	virtual ~mapObject();

	virtual HRESULT init();
	virtual HRESULT init(int x, int y);

	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void getPlayer(player* player) { m_player = player; }

};

