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
	switch (m_nObjID)
	{
	case 0:
		m_pObject = IMAGEMANAGER->findImage("npc_abigail");
		m_NpcName = ABIGAIL;
		break;


	default:
		break;
	}
	m_pAniNpc = new animation;

	m_nObjX = x;
	m_nObjY = y;
	m_rcObjet = RectMake(x, y - m_pObject->getFrameHeight()*GAME_SCALAR, m_pObject->getFrameWidth()*GAME_SCALAR, m_pObject->getFrameHeight()*GAME_SCALAR);

	m_nFrameX = 0;
	m_nFrameY = 0;
	m_isOnce = false;

	return S_OK;
}

void objNpc::release()
{
}

void objNpc::update()
{
	// 서있거나 움직임은 노말타일 & 충돌체 없는 부분에서만 가능
	// 플레이어가 주변에 있고 말을 걸면 대화 가능


	m_pAniNpc->frameUpdate(TIMEMANAGER->getElapsedTime());	// 에니매이션용



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


}

void objNpc::render(HDC hdc)
{
	m_pObject->frameRender(hdc, m_nObjX - CAMERA->getX(), m_nObjY - m_pObject->getFrameHeight()*GAME_SCALAR - CAMERA->getY(), m_nFrameX, m_nFrameY, GAME_SCALAR);
}