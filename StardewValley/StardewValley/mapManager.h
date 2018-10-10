#pragma once
#include "singletonBase.h"

#include "scene.h"

class mapTool;

class mapManager: public scene // singletonBase<mapManager>,
{
private:
	std::map<std::string, mapTool*>	m_map;
	std::map<std::string, mapTool*>::iterator m_iter;

	std::vector<std::string> m_vecLoad;

	static mapTool*	m_pCurrMap;	// «ˆ¿Á ∏ 
	static mapTool*	m_pNextMap;	// ¿¸»Ø ¥Î±‚ ¡ﬂ¿Œ ∏ 
	string m_mapName;

public:
	mapManager();
	~mapManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	// ¿œπ› æ¿
	mapTool* addScene(string mapName, mapTool* pMap);
	HRESULT changeScene(string mapName);
	inline string getSceneName() { return m_mapName; };

	mapTool* addMap(string mapName, mapTool* pMap);
	HRESULT loadFile(LPCSTR szfileName);

	void loadMap(LPCSTR szfileName);
	//vector<mapTool*> mapLoad(const char * loadFileName);
	//vector<mapTool*> mapToolArraySeparation(mapTool* charArray);
};

