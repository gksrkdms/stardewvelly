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
	SYNTHESIZE(int, m_nIndex, Index);			// Ÿ�� �ε���
	SYNTHESIZE(int, m_nHarvestId, HarvestId);	// ��ȯ�ƴ� ������id
	SYNTHESIZE(bool, m_isLayerFirst, First);
	SYNTHESIZE(int, m_nFrameX, FrameX);			// ������ x
	SYNTHESIZE(int, m_nMaxGrowth, MaxGrowth);	// �ִ뼺��ġ(�ִ�������)
	SYNTHESIZE(int, m_nFrameY, FrameY);			// ������ y
	SYNTHESIZE(int, m_nNum, Num);			// �۹� ����
	SYNTHESIZE(int, m_isWaterTile, WaterTile);	// Ÿ���� �����ϋ� Ȯ�ο�
	SYNTHESIZE(bool, isHarvest, Harvest);		// �۹��� �� �ڶ����� Ȯ�ο�

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
	virtual void setXY(int x, int y);

	virtual void getPlayer(player* player) { m_player = player; }

};

