#include "stdafx.h"
#include "mapManager.h"
#include "mapTool.h"

mapManager::mapManager()
{
}

mapManager::~mapManager()
{
}
mapTool* mapManager::m_pCurrMap = NULL;
mapTool* mapManager::m_pNextMap = NULL;

HRESULT mapManager::init()
{
	return S_OK;
}

void mapManager::release()
{
	for (m_iter = m_map.begin(); m_iter != m_map.end(); )
	{
		if (m_iter->second != NULL)
		{
			if (m_iter->second == m_pCurrMap)
				m_iter->second->release();

			SAFE_DELETE(m_iter->second);
			m_iter = m_map.erase(m_iter);
		}
		else
		{
			m_iter++;
		}
	}
	m_map.clear();
}

void mapManager::update()
{
	//if (m_pCurrMap)
	//	m_pCurrMap->update();
	
	for (m_iter = m_map.begin(); m_iter != m_map.end(); m_iter++)
	{
		m_iter->second->update();
	}
}

void mapManager::render(HDC hdc)
{
	//if (m_pCurrMap)
	//	m_pCurrMap->render(hdc);

	for (m_iter = m_map.begin(); m_iter != m_map.end(); m_iter++)
	{
		m_iter->second->render(hdc);
	}
}

mapTool * mapManager::addScene(string mapName, mapTool * pMap)
{
	if (!pMap)	return NULL;

	m_map.insert(pair<string, mapTool*>(mapName, pMap));

	return pMap;
}

HRESULT mapManager::changeScene(string mapName)
{
	// �ʿ��� �ٲٰ����ϴ� ���� ã�´�
	m_iter = m_map.find(mapName);

	m_mapName = mapName;

	// �ʿ��� �ٲٰ����ϴ� ���� �� ã����
	if (m_iter == m_map.end())	return E_FAIL;

	// �ٲٰ����ϴ� ���� ������� ������
	if (m_iter->second == m_pCurrMap)	return S_OK;

	// �ٲٰ����ϴ� ���� ã������ �ʱ�ȭ
	if (SUCCEEDED(m_iter->second->init()))
	{
		// �ʱ�ȭ ���� ��, ���� ���� release
		if (m_pCurrMap)
			m_pCurrMap->release();

		// ���� ���� �ٲٰ����ϴ� ������ ��ü
		m_pCurrMap = m_iter->second;
		return S_OK;
	}

	return E_FAIL;
}

mapTool * mapManager::addMap(string mapName, mapTool * pMap)
{
	if (!pMap)	return NULL;

	return pMap;
}

HRESULT mapManager::loadFile(LPCSTR szfileName)
{
	// �ʿ��� �ٲٰ����ϴ� ���� ã�´�
	m_iter = m_map.find(szfileName);

	m_mapName = szfileName;

	// �ʿ��� �ٲٰ����ϴ� ���� �� ã����
	if (m_iter == m_map.end())	return E_FAIL;

	// �ٲٰ����ϴ� ���� ������� ������
	if (m_iter->second == m_pCurrMap)	return S_OK;

	// �ٲٰ����ϴ� ���� ã������ �ʱ�ȭ
	if (SUCCEEDED(m_iter->second->init()))
	{
		// �ʱ�ȭ ���� ��, ���� ���� release
		if (m_pCurrMap)
			m_pCurrMap->release();

		// ���� ���� �ٲٰ����ϴ� ������ ��ü
		m_pCurrMap = m_iter->second;
		return S_OK;
	}

	return E_FAIL;
}

void mapManager::loadMap(LPCSTR szfileName)
{
	char str[128];
	DWORD read;

	HANDLE hFile;
	hFile = CreateFile(szfileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(hFile, m_pCurrMap->getTile(), sizeof(tagTile) *m_pCurrMap->getTileX() *m_pCurrMap->getTileY(), &read, NULL);

	CloseHandle(hFile);
}

//vector<mapTool*> mapManager::mapLoad(const char * loadFileName)
//{
//	char str[128];
//	DWORD read;
//
//	HANDLE hFile;
//	hFile = CreateFile(loadFileName,
//		GENERIC_READ,
//		0,
//		NULL,
//		OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL,
//		NULL);
//
//	ReadFile(hFile, str, 128, &read, NULL);
//
//	CloseHandle(hFile);
//
//	return mapToolArraySeparation(str);
//}
//
//vector<mapTool*> mapManager::mapToolArraySeparation(mapTool* charArray)
//{
//	//�̼���,������,���ο�
//	vector<mapTool*> vecStr;
//	const char* separator = ",";
//	mapTool* token;
//	char* temp;
//
//	token = strtok_s(charArray, separator, &temp);
//	// token = "�̼���";
//	vecStr.push_back(token);
//
//	while ((token = strtok_s(NULL, separator, &temp)) != NULL)
//	{
//		vecStr.push_back(token);
//	}
//
//	return vecStr;
//}