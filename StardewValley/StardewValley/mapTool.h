#pragma once
#include "scene.h"
#include <vector>
#include <algorithm>

//#include "mapObject.h"

//����Ÿ�� ������ �ʿ�
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
	
	// ����Ÿ�� ���°�
	autoState autoTileState; // ��������
	autoState autoTileStateWet; // ������
	autoWeight m_autoWeight; //������
	autoWeight autoWeightWet; // ������
	
	int terrainFrameX; // Ÿ���� ������ �ִ� ��������
	int terrainFrameY;

	int objectFrameX; // Ÿ���� ������ �ִ� ������Ʈ����
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

// �ӽ�����
struct tempSampleTile
{
	TERRAIN terrain; // ���� Ÿ��
	OBJECT object; // ������Ʈ Ÿ��

	bool isCollide; // �浹 ���� ���� true �� �� �浹 ����
};

class mapTool : public scene
{
private:
	// save, load
	HWND	m_hBtnSave;
	HWND	m_hBtnLoad;

	// �̹��� ���� ��ư
	HWND	m_hBtnLeft;
	HWND	m_hBtnRight;

	// ������Ʈ / ���� ���� ��ư
	HWND	m_hBtnSelectSample;
	HWND	m_hBtnSelectTerrain;
	HWND	m_hBtnSelectObject;

	// �� Ÿ�� ũ�� ���ù�ư
	HWND	m_hBtnSelectTileSize;
	HWND	m_hBtnSelectTileSize16;
	HWND	m_hBtnSelectTileSize32;
	HWND	m_hBtnSelectTileSize64;

	// ������Ʈ�� ����� ��ư
	HWND	m_hBtnEraser;

	// �ʿ� �巡���ؼ� �׸����� Ȯ���ϴ� ��ư
	HWND	m_hBtnSelectDraw;
	HWND	m_hBtnDragDraw;
	HWND	m_hBtnOnceDraw;

	// �浹ü ����/����/tile���� �浹�����
	HWND	m_hBtnSelectCollision;
	HWND	m_hBtnSetCollision; // ����
	HWND	m_hBtnCancelCollision; // ����
	HWND	m_hBtnDeleteCollision; // �����
	
	// ���� on/off
	HWND	m_hBtnSelectEnable;
	HWND	m_hBtnCollisionON;
	HWND	m_hBtnCollisionOFF;
	
	// obj ���� ����

protected:
	tagTile* m_pTiles;
	tagSampleTile* m_pSampleTiles;

	int TILE_SIZE_1;

	int TILE_X;
	int TILE_Y;

	//ī�޶�
	int m_indexCamera;

	// Ÿ��
	image*	m_pTileSet;

	// ������Ʈ
	image*	m_pObject;
	image*	m_pObject2;
	image*	m_pObject3;

	// ���
	image*	m_pbg;
	image*	m_pUibgsample;

private:
	// ������Ʈ ���� �̹��� ����
	OBJECTIMG m_sampleObjChoice;

	std::vector<int> m_vecSelectedTile;
	std::vector<int>::iterator m_iterSelectedTile;

	image* m_pDrag;
	RECT m_Dragrc;

	int	m_nImageX;

	bool m_isObject;

	int m_sampleTileIndex;

	int m_selectNum; //��ü ���� ����
	int m_selectX; //drag x����
	int m_selectY; // drag y ����
	int m_startX; //�巡�� ������ġ x
	int m_startY; // �巡�� ������ġ y

	bool m_isClick = false;
	bool m_isAddvec = false;
	bool m_isDrag = false;
	bool m_isDragSave = false;
	bool m_isClickSave = false;
	bool m_isMove = false; //���콺 ���� ����ٴϴ� ��
	
	bool m_isDrawtype = false; // Ÿ�� �׸� �� �ѹ��׸��� �߱׸���
	bool m_isSetCollision = false; // �浹ü ����/ true = �浹ü ����, false = cancel
	bool m_isSettingTile = false; // ����Ÿ�� ���� true = ����Ÿ�ϼ���, false = Ÿ�ϱ׸���, ��������
	bool m_isEraserCollision = false; // �浹���� ����� true = �浹�������, false = ��ü�� �����
	bool m_isReverse = false; // ��ư �¿�, true �� false ��

	// ����Ÿ�� ������
	bool m_isSampleOn = false;
	int m_isSampleOnCount;

	// �̴ϸ� ������
	bool m_isMiniMapOn = false;
	int m_isMiniMapOnCount;

	// ������Ʈ �浹üũ
	bool m_isCollide = false;

	RECT m_rcSave;
	RECT m_rcDragCheck; // �巡�� �� ��Ʈ �ִ°�
	int m_rcSwap;
	RECT rcTemp;
	   
	//�̴ϸ�
	int m_minisize;
	int m_minipositionX;
	int m_minipositionY;
	tagTile* m_pMini;

	tempSampleTile* m_ptempSampleObj1;
	tempSampleTile* m_ptempSampleObj2;
	tempSampleTile* m_ptempSampleObj3;

	//const int ways = 8;
	//					// ���� ������ �� �Ʒ� ���ʴ밢���� ���ʴ밢���Ʒ� �����ʴ밢���� ���ʴ밢���Ʒ�		
	//const int way[8][2] ={{-1,0},{ 1, 0 },{ 0, -1 },{ 0, 1 },{ -1, -1 },{ -1, 1 },{ 1, -1 },{ 1, 1 } };
	
	// 4���� �˻�
	const int ways = 4;
	// ���� ������ �� �Ʒ�	
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
	
	//����Ÿ�� ����
	void sampleTileSave();
	void objectTileSave();
	void terrainTileSave();

	//��Ÿ�Ϸ� ������ �ű�
	void TileSet();
	void TileObjSet();
	void objectEraserAll(); //������Ʈ �� ����
	void objectEraser(); //������ ������Ʈ ���� ��Ŭ��

	void objectTypeInit(); // ������Ʈ Ÿ�Լ���
	void TerrTypeInit(); // Ÿ�� Ÿ�Լ���

	void changeImg(); // �̹��� �ٲ�
	void checkObjCollide(); // ������Ʈ �浹 �˻�

	void sampleTileinit(); // Ÿ�� �̹��� �ٲ�� �ʱ�ȭ
	void reTileinit(); // Ÿ�ϻ����� �ٲ�� �ٽ� �ʱ�ȭ

	void autoTile();
	void autoFarmRender(HDC hdc);
	
	void saveMap(const char* szfileName);
	void loadMap(const char* szfileName);
};

