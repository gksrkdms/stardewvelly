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
	// 서있거나 움직임은 노말타일 & 충돌체 없는 부분에서만 가능
	// 플레이어가 주변에 있고 말을 걸면 대화 가능

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