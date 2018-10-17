#pragma once

class mapObject
{
protected:
	//int m_nFrameX;
	//int m_nFrameY;
	int m_nStrength; // ����
	bool m_isOnce; // �ð����� �ѹ��� üũ�ϱ� ���ؼ� ���
	SYNTHESIZE(bool, isWater, Water);
	SYNTHESIZE(bool, isHarvest, Harvest);
	SYNTHESIZE(int, m_nTileIndex, TileIndex);
	SYNTHESIZE(int, m_nCropId, CropId);
	int m_nX;
	int m_nY;
	int m_nScalar; //�̹��� ũ��

	SYNTHESIZE(int, m_nFrameX, FrameX);
	SYNTHESIZE(int, m_nFrameY, FrameY);


public:
	mapObject();
	virtual ~mapObject();

	virtual HRESULT init(int seedNum, int tileIndex, int posX, int posY);
	virtual void release();
	virtual void update(int x, int y);
	virtual void render(HDC hdc);
	virtual void render(HDC hdc, int x, int y);

};

