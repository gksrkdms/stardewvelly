#include "stdafx.h"
#include "mapCamera.h"


mapCamera::mapCamera()
	:m_ptMoveCameraX(WINSIZEX / 2)
	, m_ptMoveCameraY(WINSIZEY / 2)
	, m_ptCameraX(0)
	, m_ptCameraY(0)
{
}

mapCamera::~mapCamera()
{
}

HRESULT mapCamera::init()
{
	return S_OK;
}

void mapCamera::release()
{
}

void mapCamera::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_ptMoveCameraX -= 16;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_ptMoveCameraX += 16;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		m_ptMoveCameraY -= 16;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		m_ptMoveCameraY += 16;
	}
	camera();
}

void mapCamera::render(HDC hdc)
{
}

void mapCamera::camera()
{
	if (m_ptMoveCameraX < 0) m_ptMoveCameraX = 0;
	if (m_ptMoveCameraX > g_mapSize .mapSizeX- 50) m_ptMoveCameraX = g_mapSize.mapSizeX - 50;
	if (m_ptMoveCameraY < 0) m_ptMoveCameraY = 0;
	if (m_ptMoveCameraY > g_mapSize.mapSizeY - 50) m_ptMoveCameraY = g_mapSize.mapSizeY - 50;

	m_ptCameraX = m_ptMoveCameraX - WINSIZEX / 2;
	if (m_ptCameraX < 0) m_ptCameraX = 0;
	if (m_ptCameraX > g_mapSize.mapSizeX - WINSIZEX) m_ptCameraX = g_mapSize.mapSizeX - WINSIZEX;

	m_ptCameraY = m_ptMoveCameraY - WINSIZEY / 2;
	if (m_ptCameraY < 0) m_ptCameraY = 0;
	if (m_ptCameraY > g_mapSize.mapSizeY - WINSIZEY) m_ptCameraY = g_mapSize.mapSizeY - WINSIZEY;
}

void mapCamera::cameraMiniInit(int focusX, int focusY)
{
	m_pfocusCameraMiniX = focusX;
	m_pfocusCameraMiniY = focusY;
	m_ptCameraMiniX = focusX;
	m_ptCameraMiniY = focusY;
}
