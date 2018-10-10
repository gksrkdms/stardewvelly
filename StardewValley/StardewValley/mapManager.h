#pragma once
#include "mapTool.h"
#include <vector>


class mapManager: public mapTool
{
private:
	std::map<std::string, mapTool*>	m_map;
	std::map<std::string, mapTool*>::iterator m_iter;

	std::vector<tagTile> m_vecTile;
	std::vector<tagTile>::iterator m_iterTile;

	string m_mapName;

public:
	mapManager();
	~mapManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void loadMap(const char * szfileName);

	inline vector<tagTile>getTile() { return m_vecTile; }
};

