#pragma once
#include "mapTool.h"
#include <vector>

class player;

enum LOADINGSTATE
{
	LOAD_FALSE,
	LOAD_START,
	LOAD_END
};

class mapObject;
class objCrop;
class objectManager;

class mapManager: public mapTool
{
private:
	std::map<std::string, mapTool*>	m_map;
	std::map<std::string, mapTool*>::iterator m_iter;

	std::vector<tagTile> m_vecTile;
	std::vector<tagTile>::iterator m_iterTile;

	list<mapObject*> m_listObj;
	list<mapObject*>::iterator m_iterObj;

	string m_mapName;

	mapObject* m_pObjectMap;
	mapObject* m_pObjectCrop;
	objectManager* m_pObjMgr;

	const char* tempCurrMapId;	// �� �ε��� ������ �����
	const char* tempLoadMapId;	// �� �ε�� ����� �� Ű��
	const char* temp;	// �� �ε�� ����� �� Ű��
	image*	m_pBlack;			// �� �̵��� ���Ǵ� ���� �̹���
	int		m_nAlpha;			// ������ �̹��� ����
	LOADINGSTATE	m_Loading;	// �ε����� ���°�

	int		m_ntempX;			// �ʱ�ü�� ����� ��ũ�� x,y
	int		m_ntempY;
	bool	isFirstMap;			// �� ó�������� ����
	void loadingProcess();		// �ε� ������ó��

	player* m_player;

public:
	mapManager();
	~mapManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void objRender(HDC hdc);
	void loadingRender(HDC hdc);

	void saveMap(const char* szfileName);
	void loadingMap(const char * szfileName, int mapSizex, int mapSizey);
	void loadMap(const char * szfileName);

	// player�� Ÿ������ �ֱ� ���ؼ� �ε����� �ּҰ� ��ȯ
	inline tagTile* getTile(int i) { return &m_pTiles[i]; }

	// player�� �ʻ����ŭ Ÿ�� �ø� ���� Ÿ�� ������ ã������ tilesize�� x,y ���� ��ȯ
	inline int getTileSize() { return TILE_SIZE_1; }
	inline int getTileX() { return TILE_X; }
	inline int getTileY() { return TILE_Y; }

	//inline map<int, mapObject*> getObject() { return m_mapObj; }

	void getPlayer(player* player) { m_player = player; }

	void SetTree();
};

