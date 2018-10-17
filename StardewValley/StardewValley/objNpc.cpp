#include "stdafx.h"
#include "objNpc.h"
#include "animation.h"


objNpc::objNpc()
{
}

objNpc::~objNpc()
{
}

HRESULT objNpc::init()
{
	m_pObject = IMAGEMANAGER->findImage("npc_abigail");

	return S_OK;
}

HRESULT objNpc::init(int x, int y, int id)
{
	m_nObjID = id;
	m_nObjX = x;
	m_nObjY = y;
	m_pAniNpc = new animation;
	
	switch (m_nObjID)
	{
	case 0:
		m_pObject = IMAGEMANAGER->findImage("npc_abigail");
		m_NpcName = ABIGAIL;
		m_pAniNpc->init(m_pObject->getWidth(), m_pObject->getHeight(), m_pObject->getFrameWidth(), m_pObject->getFrameHeight());
		break;


	default:
		break;
	}

	m_rcObjet = RectMake(x, y - m_pObject->getFrameHeight()*GAME_SCALAR, m_pObject->getFrameWidth()*GAME_SCALAR, m_pObject->getFrameHeight()*GAME_SCALAR);

	m_nFrameX = 0;
	m_nFrameY = 0;
	m_isOnce = false;
	NpcState = BOTTOM;
	startMotion(m_pAniNpc, 0, 3, false, true, 1);

	return S_OK;
}

void objNpc::release()
{
	SAFE_DELETE(m_pAniNpc);
}

void objNpc::update()
{
	// 서있거나 움직임은 노말타일 & 충돌체 없는 부분에서만 가능
	// 플레이어가 주변에 있고 말을 걸면 대화 가능

	m_rcObjet = RectMake(m_nObjX - CAMERA->getX(), m_nObjY - m_pObject->getFrameHeight()*GAME_SCALAR - CAMERA->getY(), m_pObject->getFrameWidth()*GAME_SCALAR, m_pObject->getFrameHeight()*GAME_SCALAR);


	//switch (m_NpcName)
	//{
	//case ABIGAIL:
	//	break;
	//default:
	//	break;
	//}

	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		NpcState = LEFT;
		abiMove();
	}


	if (PLAYTIMEMANAGER->getMin() % 5 == 0 && !m_isOnce)
	{
		m_isOnce = true;
		m_nFrameX++;
		m_pObject->setFrameX(m_nFrameX);
		if (m_nFrameX > 3)
		{
			m_nFrameX = 3;
		}
	}
	else if (PLAYTIMEMANAGER->getMin() % 5 != 0)
		m_isOnce = false;

	/*switch (m_NpcInfo->NpcState)
	{
	case IDLE:
		break;
	case MOVE:
		break;
	case TALK:
		break;
	default:
		break;
	}*/

	m_pAniNpc->frameUpdate(TIMEMANAGER->getElapsedTime());	// 에니매이션용

}

void objNpc::render(HDC hdc)
{
	//m_pObject->frameRender(hdc, m_nObjX - CAMERA->getX(), m_nObjY - m_pObject->getFrameHeight()*GAME_SCALAR - CAMERA->getY(), m_nFrameX, m_nFrameY, GAME_SCALAR);
	
	m_pObject->aniRender(hdc, m_nObjX - CAMERA->getX(), m_nObjY - m_pObject->getFrameHeight()*GAME_SCALAR - CAMERA->getY(), m_pAniNpc, GAME_SCALAR);
}

void objNpc::abiMove()
{
	switch (NpcState)
	{
	case BOTTOM:
		m_nObjY += 3;
		//m_pAniNpc->stop();
		//startMotion(m_pAniNpc, 0, 3, false, true, 5);
		break;
	case LEFT:
		m_nObjX += 3;
		//m_pAniNpc->stop();
		//startMotion(m_pAniNpc, 4, 7, false, true, 5);
		break;
	case TOP:
		//m_pAniNpc->stop();
		//startMotion(m_pAniNpc, 8, 11, false, true, 5);
		break;
	default:
		break;
	}
}

void objNpc::startMotion(animation * ani, int start, int end, bool reverse, bool loop, int fps)
{
	ani->setPlayFrame(start, end, reverse, loop);
	ani->start();
	ani->setFPS(fps);
}
