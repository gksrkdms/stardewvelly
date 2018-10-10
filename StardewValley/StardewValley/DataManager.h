#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>

class DataManager : public singletonBase<DataManager>
{
	public:
		//std::vector<string> txtLoad

	public:
		HRESULT init();
		void release();

		// 세이브 
		void txtSave(const char* saveFileName, std::vector<std::string> vecStr);
		char* vectorArrayCombine(std::vector<std::string> vecArray);

		// 로드
		std::vector<std::string> txtLoad(const char* loadFileName);
		std::vector<std::string> charArraySeparation(char charArray[]);



public:
	void saveMap(LPCSTR szfileName, tagTile* tile, int x, int y);
	void saveFile(tagTile tile, int x, int y);
	void loadFile(HWND hwnd, tagTile tile, int x, int y);
	void loadMap(LPCSTR szfileName, tagTile* tile, int x, int y);
	DataManager();
	~DataManager();
};

