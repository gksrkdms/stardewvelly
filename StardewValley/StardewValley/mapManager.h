#pragma once
#include "mapTool.h"
#include <vector>

enum LOADINGSTATE
{
	LOAD_FALSE,
	LOAD_START,
	LOAD_END
};

class mapObject;

class mapManager: public mapTool
{
private:
	std::map<std::string, mapTool*>	m_map;
	std::map<std::string, mapTool*>::iterator m_iter;

	std::vector<tagTile> m_vecTile;
	std::vector<tagTile>::iterator m_iterTile;

	string m_mapName;

	mapObject* m_pObjectMap;
	mapObject* m_pObjectCrop;

	const char* tempMapId;
	image*	m_pBlack;			// �� �̵��� ���Ǵ� ���� �̹���
	int		m_nAlpha;			// ������ �̹��� ����
	LOADINGSTATE	m_Loading;	// �ε����� ���°�

public:
	mapManager();
	~mapManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void loadingRender(HDC hdc);

	void loadingMap(const char * szfileName);
	void loadMap(const char * szfileName);

	// player�� Ÿ������ �ֱ� ���ؼ� �ε����� �ּҰ� ��ȯ
	inline tagTile* getTile(int i) { return &m_pTiles[i]; }

	// player�� �ʻ����ŭ Ÿ�� �ø� ���� Ÿ�� ������ ã������ tilesize�� x,y ���� ��ȯ
	inline int getTileSize() { return TILE_SIZE_1; }
	inline int getTileX() { return TILE_X; }
	inline int getTileY() { return TILE_Y; }


};

