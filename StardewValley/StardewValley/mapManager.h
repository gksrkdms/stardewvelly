#pragma once
#include "mapTool.h"
#include <vector>

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

public:
	mapManager();
	~mapManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void loadMap(const char * szfileName);

	// player�� Ÿ������ �ֱ� ���ؼ� �ε����� �ּҰ� ��ȯ
	inline tagTile* getTile(int i) { return &m_pTiles[i]; }

	// player�� �ʻ����ŭ Ÿ�� �ø� ���� Ÿ�� ������ ã������ tilesize�� x,y ���� ��ȯ
	inline int getTileSize() { return TILE_SIZE_1; }
	inline int getTileX() { return TILE_X; }
	inline int getTileY() { return TILE_Y; }


};

