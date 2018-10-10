#pragma once
#include "singletonBase.h"

class mapCamera:public singletonBase<mapCamera>
{
private:
	int m_pfocusCameraMiniX;
	int m_pfocusCameraMiniY;

	int m_ptCameraX;
	int	m_ptCameraY;
	
public:
	mapCamera();
	~mapCamera();
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	SYNTHESIZE(int, m_ptMoveCameraX, focusCameraX);
	//SYNTHESIZE(int, m_ptCameraX, CameraX);
	SYNTHESIZE(int, m_ptMoveCameraY, focusCameraY);
	//SYNTHESIZE(int, m_ptCameraY, CameraY);
	inline int getCameraX() { return m_ptCameraX; }
	inline int getCameraY() { return m_ptCameraY; }


	// 미니맵 카메라
	SYNTHESIZE(int, m_ptMiniCameraX, focusMiniCameraX);
	SYNTHESIZE(int, m_ptCameraMiniX, CameraMiniX);
	SYNTHESIZE(int, m_ptMiniCameraY, focusMiniCameraY);
	SYNTHESIZE(int, m_ptCameraMiniY, CameraMiniY);

	void camera();
	void cameraMiniInit(int focusX, int focusY);
};
