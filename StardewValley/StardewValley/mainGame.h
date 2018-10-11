#pragma once
class loadingScene_1;
class uiTestScene;
class pixelCollision;

class startScene;
class gameScene;
class mapTool;

class mainGame
{
private:
	// DC
	HDC hdc;

	// πÈπˆ∆€
	image * m_pBackBuffer;
	void setBackBuffer();

	char m_szText[128];

	// scene
	loadingScene_1*	m_pLoadingScene;

	// ui test
	uiTestScene*	m_pUiTestScene;

	// pixel collision test
	pixelCollision*	m_pPixelCollisionScene;

	// Ω∫≈∏∆Æ æ¿
	startScene* m_pStartScene;
	// ∞‘¿”æ¿
	gameScene* m_pGameScene;

	// ∏ ≈¯
	mapTool* m_pMap;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	LRESULT ChildMapSampleProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	
	void imgload();
	void addsound();

	mainGame();
	~mainGame();
};

