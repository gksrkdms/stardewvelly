#pragma once
#include "scene.h"
#include <vector>
#include <algorithm>

//#include "mapObject.h"

//샘플타일 사이즈 필요
#define TILE_SIZE_SAMPLE 16

class mapObject;

enum TERRAIN
{
	TERRNULL, NOMALTILE, WATER, SEA, EARTH, FARMLAND, WETFARMLAND, WETEREARTH, EXIT, TR_NUM
};

enum OBJECT
{
	OBJ_NULL,
	TREE_BIG,
	TREE_SMALL,
	BUSH_BIG,
	BUSH_SMALL,
	ROCK_BIG,
	ROCK_SMALL,
	BRANCH_SMALL,
	NORMALHOUSE,
	NORMALOBJECT,
	MINE_ROCK,
	MYHOME,
	SHOP,
	FENCE,
	BED,
	TV,
	BOX,
	CROP,
	DOOR,
	OB_NUM
};

enum OBJECTIDNUM
{
	OBID_NULL,
	OBID_1,
	OBID_2,
	OBID_3,
	OBID_NUM
};

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

enum autoState
{
	STATE_NULL,LEFT, RIGHT, TOP, BOTTOM
	, LEFTCONER_T, RIGHTCONER_T, LEFTCONER_B, RIGHTCONER_B
	, SQUARE_LEFT, SQUARE_RIGHT, SQUARE_TOP, SQUARE_BOTTOM, SQUARE_MIDDLE
	, TOP_END, BOTTOM_MIDDLE, BOTTOM_END , LEFT_END, LEFT_MIDDLE, RIGHT_END
};

struct autoWeight
{
	int leftTop;
	int leftBottom;
	int rightTop;
	int rightBottom;
};

typedef struct tagTile
{
	TERRAIN terrain;
	OBJECT object;

	OBJECTIDNUM objectID;
	
	// 오토타일 상태값
	autoState autoTileState; // 안젖은땅
	autoState autoTileStateWet; // 젖은땅
	autoWeight m_autoWeight; //마른땅
	autoWeight autoWeightWet; // 젖은땅
	
	int terrainFrameX; // 타일이 가지고 있는 지형정보
	int terrainFrameY;

	int objectFrameX; // 타일이 가지고 있는 오브젝트정보
	int objectFrameY;

	int index;

	bool isCollide;

	RECT rc;
} TAGTILE;

struct tagSampleTile
{
	TERRAIN terrain;
	OBJECT object;
	OBJECTIDNUM objectID;

	int frameX;
	int frameY;

	bool isCollide;

	RECT rc;
};

// 임시저장
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

protected:
	tagTile* m_pTiles;
	tagSampleTile* m_pSampleTiles;

	int TILE_SIZE_1;

	int TILE_X;
	int TILE_Y;

	//카메라
	int m_indexCamera;

	// 타일
	image*	m_pTileSet;

	// 오브젝트
	image*	m_pObject;
	image*	m_pObject2;
	image*	m_pObject3;

	// 배경
	image*	m_pbg;
	image*	m_pUibgsample;

private:
	// 오브젝트 샘플 이미지 선택
	OBJECTIMG m_sampleObjChoice;

	std::vector<int> m_vecSelectedTile;
	std::vector<int>::iterator m_iterSelectedTile;

	image* m_pDrag;
	RECT m_Dragrc;

	int	m_nImageX;

	bool m_isObject;

	int m_sampleTileIndex;

	int m_selectNum; //전체 범위 갯수
	int m_selectX; //drag x범위
	int m_selectY; // drag y 범위
	int m_startX; //드래그 시작위치 x
	int m_startY; // 드래그 시작위치 y

	bool m_isClick = false;
	bool m_isAddvec = false;
	bool m_isDrag = false;
	bool m_isDragSave = false;
	bool m_isClickSave = false;
	bool m_isMove = false; //마우스 옆에 따라다니는 것
	
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
	   
	//미니맵
	int m_minisize;
	int m_minipositionX;
	int m_minipositionY;
	tagTile* m_pMini;

	tempSampleTile* m_ptempSampleObj1;
	tempSampleTile* m_ptempSampleObj2;
	tempSampleTile* m_ptempSampleObj3;

	//const int ways = 8;
	//					// 왼쪽 오른쪽 위 아래 왼쪽대각선위 왼쪽대각선아래 오른쪽대각선위 왼쪽대각선아래		
	//const int way[8][2] ={{-1,0},{ 1, 0 },{ 0, -1 },{ 0, 1 },{ -1, -1 },{ -1, 1 },{ 1, -1 },{ 1, 1 } };
	
	// 4방향 검사
	const int ways = 4;
	// 왼쪽 오른쪽 위 아래	
	const int way[4][2] = { {-1,0},{ 1, 0 },{ 0, -1 },{ 0, 1 } };

public:
	mapTool();
	~mapTool();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	LRESULT ChildMapSampleProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	
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
	void TerrTypeInit(); // 타일 타입설정

	void changeImg(); // 이미지 바꿈
	void checkObjCollide(); // 오브젝트 충돌 검사

	void sampleTileinit(); // 타일 이미지 바뀌면 초기화
	void reTileinit(); // 타일사이즈 바뀌면 다시 초기화

	void autoTile();
	void autoFarmRender(HDC hdc);
	
	void saveMap(const char* szfileName);
	void loadMap(const char* szfileName);
};

