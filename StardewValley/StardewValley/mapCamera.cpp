#include "stdafx.h"
#include "mapCamera.h"


mapCamera::mapCamera()
	:m_ptMoveCameraX(WINSIZEX / 2)
	, m_ptMoveCameraY(WINSIZEY / 2)
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
		m_ptMoveCameraX -= 10;
		m_ptCameraMiniX -= 10;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_ptMoveCameraX += 10;
		m_ptCameraMiniX += 10;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		m_ptMoveCameraY -= 10;
		m_ptCameraMiniY -= 10;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		m_ptMoveCameraY += 10;
		m_ptCameraMiniY += 10;
	}
	camera();
}

void mapCamera::render(HDC hdc)
{
}

void mapCamera::camera()
{
	//if (m_ptMoveCamera.x < 0) m_ptMoveCamera.x = 0;
	//if (m_ptMoveCamera.x > MAPSIZEX) m_ptMoveCamera.x = MAPSIZEX;
	//if (m_ptMoveCamera.y < 0) m_ptMoveCamera.y = 0;
	//if (m_ptMoveCamera.y > MAPSIZEY) m_ptMoveCamera.y = MAPSIZEY;

	//m_ptCamera.x = m_ptMoveCamera.x - WINSIZEX / 2;
	//if (m_ptCamera.x < 0) m_ptCamera.x = 0;
	//if (m_ptCamera.x > MAPSIZEX - WINSIZEX) m_ptCamera.x = MAPSIZEX - WINSIZEX;

	//m_ptCamera.y = m_ptMoveCamera.y - WINSIZEY / 2;
	//if (m_ptCamera.y < 0) m_ptCamera.y = 0;
	//if (m_ptCamera.y > MAPSIZEY - WINSIZEY) m_ptCamera.y = MAPSIZEY - WINSIZEY;

	if (m_ptMoveCameraX < 0) m_ptMoveCameraX = 0;
	if (m_ptMoveCameraX > MAPSIZEX) m_ptMoveCameraX = MAPSIZEX;
	if (m_ptMoveCameraY < 0) m_ptMoveCameraY = 0;
	if (m_ptMoveCameraY > MAPSIZEY) m_ptMoveCameraY = MAPSIZEY;

	m_ptCameraX = m_ptMoveCameraX - WINSIZEX / 2;
	if (m_ptCameraX < 0) m_ptCameraX = 0;
	if (m_ptCameraX > MAPSIZEX - WINSIZEX) m_ptCameraX = MAPSIZEX - WINSIZEX;

	m_ptCameraY = m_ptMoveCameraY - WINSIZEY / 2;
	if (m_ptCameraY < 0) m_ptCameraY = 0;
	if (m_ptCameraY > MAPSIZEY - WINSIZEY) m_ptCameraY = MAPSIZEY - WINSIZEY;

	// ¹Ì´Ï¸Ê
	if (m_ptCameraMiniX < 0) m_ptCameraMiniX = 0;
	if (m_ptCameraMiniX > m_pfocusCameraMiniX) m_ptCameraMiniX = m_pfocusCameraMiniX;
	if (m_ptCameraMiniY < 0) m_ptCameraMiniY = 0;
	if (m_ptCameraMiniY > m_pfocusCameraMiniY) m_ptCameraMiniY = m_pfocusCameraMiniY;

	m_ptMiniCameraX = m_ptCameraMiniX - m_pfocusCameraMiniX;
	if (m_ptMiniCameraX < 0) m_ptMiniCameraX = 0;
	if (m_ptMiniCameraX > WINSIZEX - m_pfocusCameraMiniX) m_ptMiniCameraX = WINSIZEX - m_pfocusCameraMiniX;

	m_ptMiniCameraY = m_ptCameraMiniY - m_pfocusCameraMiniY;
	if (m_ptMiniCameraY < 0) m_ptMiniCameraY = 0;
	if (m_ptMiniCameraY > WINSIZEY - m_pfocusCameraMiniY) m_ptMiniCameraY = WINSIZEY - m_pfocusCameraMiniY;
}

void mapCamera::cameraMiniInit(int focusX, int focusY)
{
	m_pfocusCameraMiniX = focusX;
	m_pfocusCameraMiniY = focusY;
	m_ptCameraMiniX = focusX;
	m_ptCameraMiniY = focusY;
}
