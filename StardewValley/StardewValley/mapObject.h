#pragma once

class mapObject
{
protected:
	//int m_nFrameX;
	//int m_nFrameY;
	int m_nStrength; // 강도
	bool m_isOnce; // 시간마다 한번만 체크하기 위해서 사용
	int m_nScalar; //이미지 크기

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

