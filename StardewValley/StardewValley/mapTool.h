#pragma once
#include "scene.h"
#include <vector>
#include <algorithm>

#include "mapObject.h"

//#define TILE_SIZE_1	16
#define TILE_SIZE_2	32

//샘플타일 사이즈 필요
#define TILE_SIZE_SAMPLE 16

//#define TILE_X	MAPSIZEX/TILE_SIZE_SAMPLE
//#define TILE_Y	MAPSIZEY/TILE_SIZE_SAMPLE

//#define SAMPLE_TILE_X	20//20
//#define SAMPLE_TILE_Y	20//20





enum BUTTONID
{
	BTN_01 = 100,
	BTN_02,
	BTN_03,
	BTN_04,
	BTN_05,
	BTN_06,
	BTN_07,
	BTN_08,
	BTN_09,
	BTN_10,
	BTN_11,
	BTN_12,
	BTN_13,
	BTN_14,
	BTN_15,
	BTN_16,
	BTN_LEFT,
	BTN_RIGHT,
	BTN_GROUP1,
	BTN_GROUP2,
	BTN_GROUP3,
	BTN_GROUP4,
	BTN_GROUP5
};

enum TERRAINIMG
{
	FARM
};

enum OBJECTIMG
{
	IMGOBJ_OBJNULL, IMGOBJ_1, IMGOBJ_2, IMGOBJ_3, IMGOBJ_OBJMAX
};

struct tagSampleTile
{
	TERRAIN terrain;
	OBJECT object;
	OBJECTIDNUM objectID;

	int frameX;
	int frameY;
	int index;

	bool isCollide;

	RECT rc;
};

struct tempSampleTile
{
	TERRAIN terrain; // 지형 타입
	OBJECT object; // 오브젝트 타입

	bool isCollide; // 충돌 가능 여부 true 일 시 충돌 가능
};

class mapTool : public scene
{
private:
	// save, load
	HWND	m_hBtnSave;
	HWND	m_hBtnLoad;

	// 이미지 선택 버튼
	HWND	m_hBtnLeft;
	HWND	m_hBtnRight;

	// 오브젝트 / 지형 선택 버튼
	HWND	m_hBtnSelectSample;
	HWND	m_hBtnSelectTerrain;
	HWND	m_hBtnSelectObject;

	// 한 타일 크기 선택버튼
	HWND	m_hBtnSelectTileSize;
	HWND	m_hBtnSelectTileSize16;
	HWND	m_hBtnSelectTileSize32;
	HWND	m_hBtnSelectTileSize64;

	// 오브젝트를 지우는 버튼
	HWND	m_hBtnEraser;

	// 맵에 드래그해서 그릴건지 확인하는 버튼
	HWND	m_hBtnSelectDraw;
	HWND	m_hBtnDragDraw;
	HWND	m_hBtnOnceDraw;

	// 충돌체 지정/해제/tile에서 충돌지우기
	HWND	m_hBtnSelectCollision;
	HWND	m_hBtnSetCollision; // 지정
	HWND	m_hBtnCancelCollision; // 해제
	HWND	m_hBtnDeleteCollision; // 지우기
	
	// 세팅 on/off
	HWND	m_hBtnSelectEnable;
	HWND	m_hBtnCollisionON;
	HWND	m_hBtnCollisionOFF;
	
	// obj 강도 지정

	// 타일
	image*	m_pTileSet;

	// 오브젝트
	image*	m_pObject;
	image*	m_pObject2;
	image*	m_pObject3;

	// 배경
	image*	m_pbg;
	image*	m_pUibgsample;
	
	//tagTile m_pTiles[TILE_X * TILE_Y];
	//tagTile m_pTiles[TILE_X * TILE_Y];
	//tagSampleTile m_pSampleTiles[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	tagTile* m_pTiles;
	tagSampleTile* m_pSampleTiles;

	// 오브젝트 샘플 이미지 선택
	OBJECTIMG m_sampleObjChoice;

	std::vector<int> m_vecSelectedTile;
	std::vector<int>::iterator m_iterSelectedTile;

	int	m_nImageX;

	bool m_isObject;

	int m_sampleTileIndex;

	int m_selectNum;
	int m_selectX;
	int m_selectY;
	int m_startX;
	int m_startY;

	bool m_isClick = false;
	bool m_isAddvec = false;
	bool m_isDrag = false;
	bool m_isDragSave = false;
	bool m_isClickSave = false;
	bool m_isMove = false;
	
	bool m_isDrawtype = false; // 타일 그릴 때 한번그릴지 쭉그릴지
	bool m_isSetCollision = false; // 충돌체 설정/ true = 충돌체 설정, false = cancel
	bool m_isSettingTile = false; // 샘플타일 설정 true = 샘플타일설정, false = 타일그리기, 설정꺼짐
	bool m_isEraserCollision = false; // 충돌값만 지우기 true = 충돌값지우기, false = 전체다 지우기
	bool m_isReverse = false; // 버튼 좌우, true 우 false 좌

	// 샘플타일 보여줌
	bool m_isSampleOn = false;
	int m_isSampleOnCount;

	// 미니맵 보여줌
	bool m_isMiniMapOn = false;
	int m_isMiniMapOnCount;

	// 오브젝트 충돌체크
	bool m_isCollide = false;

	RECT m_rcSave;
	RECT m_rcDragCheck; // 드래그 한 렉트 있는가
	int m_rcSwap;
	RECT rcTemp;

	int m_tileNum;

	//카메라
	int m_indexCamera;

	//미니맵
	int m_minisize;
	int m_minipositionX;
	int m_minipositionY;
	//tagTile m_pMini[TILE_X * TILE_Y];
	tagTile* m_pMini;

	tempSampleTile* m_ptempSampleObj1;
	tempSampleTile* m_ptempSampleObj2;
	tempSampleTile* m_ptempSampleObj3;

	int TILE_X;
	int TILE_Y;


public:
	mapTool();
	~mapTool();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	LRESULT ChildMapSampleProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	LRESULT ChildMapSampleTopProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	
	//샘플타일 저장
	void sampleTileSave();
	void objectTileSave();
	void terrainTileSave();

	//맵타일로 데이터 옮김
	void TileSet();
	void TileObjSet();
	void objectEraserAll(); //오브젝트 다 삭제
	void objectEraser(); //선택한 오브젝트 삭제 우클릭

	void objectTypeInit(); // 오브젝트 타입설정

	void changeImg(); // 이미지 바꿈
	void checkObjCollide(); // 오브젝트 충돌 검사

	void sampleTileinit(); // 타일 이미지 바뀌면 초기화

	inline tagTile* getTile() { return m_pTiles; }
	inline int getTileX() { return TILE_X; }
	inline int getTileY() { return TILE_Y; }
};

