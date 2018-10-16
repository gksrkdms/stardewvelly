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
	// ���ְų� �������� �븻Ÿ�� & �浹ü ���� �κп����� ����
	// �÷��̾ �ֺ��� �ְ� ���� �ɸ� ��ȭ ����


	m_pAniNpc->frameUpdate(TIMEMANAGER->getElapsedTime());	// ���ϸ��̼ǿ�



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