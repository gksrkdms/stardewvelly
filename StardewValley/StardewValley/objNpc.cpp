#include "stdafx.h"
#include "objNpc.h"


objNpc::objNpc()
{
}

objNpc::~objNpc()
{
}

HRESULT objNpc::init()
{
	m_NpcInfo->NpcImg = IMAGEMANAGER->findImage("npc_abigail");

	return S_OK;
}

HRESULT objNpc::init(int x, int y)
{
	return S_OK;
}

void objNpc::release()
{
}

void objNpc::update()
{
	// ���ְų� �������� �븻Ÿ�� & �浹ü ���� �κп����� ����
	// �÷��̾ �ֺ��� �ְ� ���� �ɸ� ��ȭ ����

	switch (m_NpcInfo->NpcID)
	{
	case 0:
		break;
		

	default:
		break;
	}

	switch (m_NpcInfo->NpcState)
	{
	case IDLE:
		break;
	case MOVE:
		break;
	case TALK:
		break;
	default:
		break;
	}


}

void objNpc::render(HDC hdc)
{
}