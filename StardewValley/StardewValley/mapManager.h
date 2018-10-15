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
	image*	m_pBlack;			// 맵 이동시 사용되는 검은 이미지
	int		m_nAlpha;			// 검은색 이미지 알파
	LOADINGSTATE	m_Loading;	// 로딩여부 상태값

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

	// player에 타일정보 주기 위해서 인덱스의 주소값 반환
	inline tagTile* getTile(int i) { return &m_pTiles[i]; }

	// player에 맵사이즈만큼 타일 컬링 시켜 타일 정보를 찾기위해 tilesize와 x,y 갯수 반환
	inline int getTileSize() { return TILE_SIZE_1; }
	inline int getTileX() { return TILE_X; }
	inline int getTileY() { return TILE_Y; }


};

