#pragma once
#include "scene.h"
class animation;
class startScene : public scene
{
private:
	image * m_pBG;		// ��׶���
	image*	m_pImg1;	// Ÿ��Ʋ�̹���1
	image*	m_pImg2;	// Ÿ��Ʋ�̹���2
	image*	m_pImg3;	// �ڷΰ���(�̱���)
	image*	m_pCloud1;	// ����1
	image*	m_pCloud2;	// ����2

	animation * m_pAni_1;	// �޴� ���ϸ��̼�

	RECT m_rc[4];			// ���콺 üũ ��Ʈ
	bool isMouseIn[4];		// ���콺 üũ �Ұ�
	int	m_nArrayX1[5];		// ����1,2 x,y
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

