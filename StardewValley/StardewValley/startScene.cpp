#include "stdafx.h"
#include "startScene.h"
#include "animation.h"


HRESULT startScene::init()
{
	m_pBG = IMAGEMANAGER->findImage("title_006");
	m_pImg1 = IMAGEMANAGER->findImage("title_001");
	m_pImg2 = IMAGEMANAGER->findImage("title_002");
	m_pCloud1 = IMAGEMANAGER->findImage("title_004");
	m_pCloud2 = IMAGEMANAGER->findImage("title_005");

	SOUNDMANAGER->play("sound/StardewValleyOverture.mp3");
	
	m_pAni_1 = new animation;
	m_pAni_1->init(m_pImg2->getWidth(), m_pImg2->getHeight(), 222, 174);
	//m_pAni_1->setFPS(1);

	// Ÿ��Ʋ�� �޴� ��Ʈ, �Ұ� �ʱ�ȭ
	for (int i = 0; i < 4; i++)
	{
		m_rc[i] = RectMake((WINSIZEX / 6) + (242 * i), WINSIZEY - m_pImg2->getHeight(), m_pImg2->getFrameWidth(), m_pImg2->getFrameHeight());
		isMouseIn[i] = false;
	}

	// ū���� ���� ���� 5���� �����ʱ�ȭ
	for (int i = 0; i < 5; i++)
	{
		m_nArrayX1[i] = RANDOM->getFromIntTo(WINSIZEX / 4, WINSIZEX);
		m_nArrayY1[i] = RANDOM->getFromIntTo(0, WINSIZEY - 100);

		m_nArrayX2[i] = RANDOM->getFromIntTo(WINSIZEX / 4, WINSIZEX);
		m_nArrayY2[i] = RANDOM->getFromIntTo(0, WINSIZEY - 100);
	}

	return S_OK;
}

void startScene::release()
{
	delete m_pAni_1;
}

void startScene::update()
{
	// ���� �̵��ϴ°�
	for (int i = 0; i < 5; i++)
	{
		m_nArrayX1[i] -= (i / 2) + 1;
		m_nArrayX2[i] -= (i / 2) + 1;

		if (m_nArrayX1[i] < -120) m_nArrayX1[i] = WINSIZEX;
		if (m_nArrayX2[i] < -50) m_nArrayX2[i] = WINSIZEX;
	}

	// ���콺 ��Ʈ�� ������ ��
	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&m_rc[i], g_ptMouse))
		{
			isMouseIn[i] = true;
			SOUNDMANAGER->play("sound/effect/startbutton.wav");
		}
		else
		{
			isMouseIn[i] = false;
		}
	}

	// �ش� ��Ʈ true�� ����ȯ
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 4; i++)
		{
			if (isMouseIn[i] == true)
			{
				switch (i)
				{
				case 0:
					// ���Ӿ�
					SCENEMANAGER->changeScene("gameScene");
					break;
				case 1:
					// �̾��ϱ�
					break;
				case 2:
					// ������
					SCENEMANAGER->changeScene("maptool");
					break;
				case 3:
					// ����
					PostQuitMessage(0);
					break;
				}
			}
		}
	}
}

void startScene::render(HDC hdc)
{
	m_pBG->render(hdc, 0, 0);
	for (int i = 0; i < 5; i++)
	{
		m_pCloud1->render(hdc, m_nArrayX1[i], m_nArrayY1[i]);
		m_pCloud2->render(hdc, m_nArrayX2[i], m_nArrayY2[i]);
	}
	m_pImg1->render(hdc, WINSIZEX / 5, 50);
	for (int i = 0; i < 4; i++)
	{
		//MakeRect(hdc, m_rc[i]);
		if (isMouseIn[i] == false)
		{
			m_pAni_1->setPlayFrame(i, i + 1, false, false);
			m_pImg2->aniRender(hdc, (WINSIZEX / 6) + (242 * i), WINSIZEY - m_pImg2->getHeight(), m_pAni_1);
		}
		else
		{
			m_pAni_1->setPlayFrame(i + 4, i + 1 + 4, false, false);
			m_pImg2->floatAniRender(hdc, (WINSIZEX / 6) + (242 * i), WINSIZEY - m_pImg2->getHeight(), m_pAni_1, 1.05f);
		}
	}
}

startScene::startScene()
{
}


startScene::~startScene()
{
}
