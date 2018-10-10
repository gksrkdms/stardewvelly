#pragma once
class titleScene;
class battleScene;
class loadingScene_1;
class uiTestScene;
class pixelCollision;
class tileMap;

class mapTool;
class sample;
class mapManager;

class startScene;
class gameScene;

class mainGame
{
private:
	// DC
	HDC hdc;

	// πÈπˆ∆€
	image * m_pBackBuffer;
	void setBackBuffer();

	char m_szText[128];

	// scene test
	titleScene*		m_pTitleScene;
	battleScene*	m_pBattleScene;

	loadingScene_1*	m_pLoadingScene;

	// ui test
	uiTestScene*	m_pUiTestScene;

	// pixel collision test
	pixelCollision*	m_pPixelCollisionScene;

	tileMap* m_pTileMap;
	
	// map tile
	mapTool* m_pMap;

	sample* m_psample;

	mapManager* m_pMapmgr;

	// Ω∫≈∏∆Æ æ¿
	startScene* m_pStartScene;
	// ∞‘¿”æ¿
	gameScene* m_pGameScene;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	LRESULT ChildMapSampleProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	LRESULT ChildMapSampleTopProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	   
	void imgload();

	mainGame();
	~mainGame();
};

