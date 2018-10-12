#pragma once
#include "scene.h"
class animation;
class startScene : public scene
{
private:
	image * m_pBG;		// 백그라운드
	image*	m_pImg1;	// 타이틀이미지1
	image*	m_pImg2;	// 타이틀이미지2
	image*	m_pImg3;	// 뒤로가기(미구현)
	image*	m_pCloud1;	// 구름1
	image*	m_pCloud2;	// 구름2

	animation * m_pAni_1;	// 메뉴 에니메이션

	RECT m_rc[4];			// 마우스 체크 렉트
	bool isMouseIn[4];		// 마우스 체크 불값
	int	m_nArrayX1[5];		// 구름1,2 x,y
	int	m_nArrayY1[5];
	int	m_nArrayX2[5];
	int	m_nArrayY2[5];

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	startScene();
	~startScene();
};

