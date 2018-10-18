#pragma once
class player;

class mapObject
{
protected:
	image * m_pObject;

	//int m_nObjX; // objx
	//int m_nObjY; // objy

	int m_nStrength; // ����
	bool m_isOnce; // �ð����� �ѹ��� üũ�ϱ� ���ؼ� ���
	int m_nScalar; //�̹��� ũ��

	int m_nObjID;

	SYNTHESIZE(int, m_nObjX, X);
	SYNTHESIZE(int, m_nObjY, Y);
	SYNTHESIZE(int, m_nIndex, Index);
	SYNTHESIZE(bool, m_isLayerFirst, First);
	SYNTHESIZE(int, m_nFrameX, FrameX);
	SYNTHESIZE(int, m_nFrameY, FrameY);

	player* m_player;

	RECT m_rcObjet;
	RECT m_rcTemp;
	RECT m_pPlayer;

public:
	mapObject();
	virtual ~mapObject();

	virtual HRESULT init();
	virtual HRESULT init(int x, int y, int id, int index);

	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void getPlayer(player* player) { m_player = player; }

};

