#pragma once
class player;

class mapObject
{
protected:
	image * m_pObject;

	//int m_nObjX; // objx
	//int m_nObjY; // objy

	int m_nStrength; // 강도
	bool m_isOnce; // 시간마다 한번만 체크하기 위해서 사용
	int m_nScalar; //이미지 크기

	int m_nObjID;

	SYNTHESIZE(int, m_nObjX, X);
	SYNTHESIZE(int, m_nObjY, Y);
	SYNTHESIZE(int, m_nIndex, Index);			// 타일 인덱스
	SYNTHESIZE(int, m_nHarvestId, HarvestId);	// 반환아는 아이템id
	SYNTHESIZE(bool, m_isLayerFirst, First);
	SYNTHESIZE(int, m_nFrameX, FrameX);			// 프레임 x
	SYNTHESIZE(int, m_nMaxGrowth, MaxGrowth);	// 최대성장치(최대프레임)
	SYNTHESIZE(int, m_nFrameY, FrameY);			// 프레임 y
	SYNTHESIZE(int, m_nNum, Num);			// 작물 수량
	SYNTHESIZE(int, m_isWaterTile, WaterTile);	// 타일이 워터일떄 확인용
	SYNTHESIZE(bool, isHarvest, Harvest);		// 작물이 다 자랐는지 확인용

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

