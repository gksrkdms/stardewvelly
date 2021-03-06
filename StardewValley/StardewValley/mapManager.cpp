#include "stdafx.h"
#include "mapManager.h"

#include "objTree.h"
#include "objCrop.h"
#include "objectManager.h"

mapManager::mapManager()
{
}

mapManager::~mapManager()
{
}

HRESULT mapManager::init()
{
	m_pTileSet = IMAGEMANAGER->findImage("earthAll");
	m_pObject = IMAGEMANAGER->findImage("town_Shop");
	m_pObject2 = IMAGEMANAGER->findImage("town_Nomal");
	m_pObject3 = IMAGEMANAGER->findImage("object3");
	m_pBlack = IMAGEMANAGER->findImage("black");
	m_nAlpha = 0;
	m_Loading = LOAD_FALSE;
	tempLoadMapId = "";
	tempCurrMapId = "";
	temp = "zzz";

	m_pUibgsample = IMAGEMANAGER->findImage("maptoolui");

	TILE_SIZE_1 = 64;
	TILE_X = g_mapSize.mapSizeX / TILE_SIZE_1;
	TILE_Y = g_mapSize.mapSizeY / TILE_SIZE_1;
	m_pTiles = new tagTile[TILE_X*TILE_Y];

	//	기본 타일 정보 셋팅
	for (int i = 0; i < TILE_X * TILE_Y; i++)
	{
		m_pTiles[i].rc = RectMake((i % TILE_X)*TILE_SIZE_1, (i / TILE_X)*TILE_SIZE_1, TILE_SIZE_1, TILE_SIZE_1);
		m_pTiles[i].terrainFrameX = 0;
		m_pTiles[i].terrainFrameY = 1;
		m_pTiles[i].terrain = NOMALTILE;
		m_pTiles[i].object = OBJ_NULL;
		m_pTiles[i].objectID = OBID_NULL;
		m_pTiles[i].index = i;
		m_pTiles[i].isCollide = false;
		m_pTiles[i].autoTileState = STATE_NULL;
		m_pTiles[i].autoTileStateWet = STATE_NULL;
		m_pTiles[i].m_autoWeight = { 0,0,0,0 };
		m_pTiles[i].autoWeightWet = { 0,0,0,0 };
	}
	
	//m_pObjMgr = new objectManager;
	//m_pObjMgr->setTree(m_pTiles[4].rc.left, m_pTiles[5].rc.top);
	//m_pObjMgr->setTree(m_pTiles[8].rc.left, m_pTiles[15].rc.top);
	//m_pObjMgr->setTree(m_pTiles[20].rc.left, m_pTiles[15].rc.top);
	//m_pObjMgr->getPlayer(m_player);
	   
	//m_pObjectMap = new objTree;
	//m_pObjectMap->init();
	//m_pObjectMap->getPlayer(m_player);

	//m_pObjectCrop = new objCrop;
	//m_pObjectCrop->init();
	//m_pObjectCrop->getPlayer(m_player);

	m_vecTile.resize(TILE_Y*TILE_X);
	
	return S_OK;
}

void mapManager::release()
{
	SAFE_DELETE_ARRAY(m_pTiles);
	SAFE_DELETE_ARRAY(m_pObjectMap);
	SAFE_DELETE_ARRAY(m_pObjectCrop);
	//delete m_pObjMgr;

	// 맵의 모든 원소를 돌면서 확인
	for (m_iter = m_map.begin(); m_iter != m_map.end(); )
	{
		// 원소의 value( tagTile* )가 있으면
		if (m_iter->second != NULL)
		{
			m_iter = m_map.erase(m_iter);
		}
		else
		{
			m_iter++;
		}
	}
	m_map.clear();

	m_vecTile.clear();
	//delete[] m_pTiles;
}

void mapManager::update()
{
	for (int i = 0; i < TILE_X * TILE_Y; i++)
	{
		m_pTiles[i].rc = RectMake((i % TILE_X)*TILE_SIZE_1 - CAMERA->getX(), (i / TILE_X)*TILE_SIZE_1 - CAMERA->getY(), TILE_SIZE_1, TILE_SIZE_1);
	}

	autoTile();

	m_listObj = OBJMANAGER->getObject();
	for (m_iterObj = m_listObj.begin(); m_iterObj != m_listObj.end(); m_iterObj++)
	{
		OBJMANAGER->setCropXY(m_pTiles[(*m_iterObj)->getIndex()].rc.left, m_pTiles[(*m_iterObj)->getIndex()].rc.bottom, (*m_iterObj)->getIndex());
		if (m_pTiles[(*m_iterObj)->getIndex()].object == TREE_SMALL ||
			m_pTiles[(*m_iterObj)->getIndex()].object == TREE_BIG ||
			m_pTiles[(*m_iterObj)->getIndex()].object == CROP)
		{
			OBJMANAGER->update();
		}
		if (m_pTiles[(*m_iterObj)->getIndex()].terrain == WETFARMLAND)
		OBJMANAGER->setWaterFarm((*m_iterObj)->getIndex());

		if ((*m_iterObj)->getHarvest() == true)
			m_pTiles[(*m_iterObj)->getIndex()].object = HARVEST;
		else
			m_pTiles[(*m_iterObj)->getIndex()].object = CROP;
	}

	loadingProcess();
}

void mapManager::render(HDC hdc)
{
	for (int y = 0; y < WINSIZEY / TILE_SIZE_1 + 1; y++)
	{
		for (int x = 0; x < WINSIZEX / TILE_SIZE_1 + 1; x++)
		{
			int cullX = CAMERA->getX() / TILE_SIZE_1;
			int cullY = CAMERA->getY() / TILE_SIZE_1;

			m_indexCamera = (y + cullY)*TILE_X + (x + cullX);
			if (m_indexCamera >= (TILE_X * TILE_Y)) continue;

			if (m_pTiles[m_indexCamera].terrain == WETEREARTH)
			{
				m_pTileSet->frameRenderTile(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.top
					, 19, 7, TILE_SIZE_1, TILE_SIZE_1);
			}

			else if (m_pTiles[m_indexCamera].terrain == FARMLAND || m_pTiles[m_indexCamera].terrain == WETFARMLAND)
			{
				m_pTileSet->frameRenderTile(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.top
					, 0, 0, TILE_SIZE_1, TILE_SIZE_1);
			}

			else
			{
				m_pTileSet->frameRenderTile(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.top
					, 0, 1, TILE_SIZE_1, TILE_SIZE_1);
			}

			if (m_pTiles[m_indexCamera].terrain == FARMLAND || m_pTiles[m_indexCamera].terrain == WETFARMLAND)
			{
				autoFarmRender(hdc);
			}

			else
			{
				m_pTileSet->frameRenderTile(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.top
					, m_pTiles[m_indexCamera].terrainFrameX, m_pTiles[m_indexCamera].terrainFrameY, TILE_SIZE_1, TILE_SIZE_1);
			}

			//if (m_pTiles[m_indexCamera].isCollide == true)
			//	MakeRect(hdc, m_pTiles[m_indexCamera].rc);

		}

		//TextOut(hdc, 0, 400, tempCurrMapId, strlen(tempCurrMapId));
	}
}
void mapManager::objRender(HDC hdc)
{
	for (int y = 0; y < WINSIZEY / TILE_SIZE_1 + 1; y++)
	{
		for (int x = 0; x < WINSIZEX / TILE_SIZE_1 + 1; x++)
		{
			int cullX = CAMERA->getX() / TILE_SIZE_1;
			int cullY = CAMERA->getY() / TILE_SIZE_1;

			m_indexCamera = (y + cullY)*TILE_X + (x + cullX);
			if (m_indexCamera >= (TILE_X * TILE_Y)) continue;
			
			if (m_pTiles[m_indexCamera].object == TREE_SMALL || m_pTiles[m_indexCamera].object == TREE_BIG
				|| m_pTiles[m_indexCamera].object == CROP || m_pTiles[m_indexCamera].object == HARVEST)
				OBJMANAGER->render(hdc);
			
			else if (m_pTiles[m_indexCamera].object == NPC)
				OBJMANAGER->Npcrender(hdc);

			else if (m_pTiles[m_indexCamera].object != OBJ_NULL)
			{
				if (m_pTiles[m_indexCamera].objectID != OBID_2 && m_pTiles[m_indexCamera].objectID != OBID_3)
				{
					m_pObject->frameRenderTile(hdc,
						m_pTiles[m_indexCamera].rc.left,
						m_pTiles[m_indexCamera].rc.top,
						m_pTiles[m_indexCamera].objectFrameX,
						m_pTiles[m_indexCamera].objectFrameY, TILE_SIZE_1, TILE_SIZE_1);
				}

				if (m_pTiles[m_indexCamera].objectID != OBID_1 && m_pTiles[m_indexCamera].objectID != OBID_3)
				{
					m_pObject2->frameRenderTile(hdc,
						m_pTiles[m_indexCamera].rc.left,
						m_pTiles[m_indexCamera].rc.top,
						m_pTiles[m_indexCamera].objectFrameX,
						m_pTiles[m_indexCamera].objectFrameY, TILE_SIZE_1, TILE_SIZE_1);
				}

				if (m_pTiles[m_indexCamera].objectID != OBID_1 && m_pTiles[m_indexCamera].objectID != OBID_2)
				{
					m_pObject3->frameRenderTile(hdc,
						m_pTiles[m_indexCamera].rc.left,
						m_pTiles[m_indexCamera].rc.top,
						m_pTiles[m_indexCamera].objectFrameX,
						m_pTiles[m_indexCamera].objectFrameY, TILE_SIZE_1, TILE_SIZE_1);
				}
			}

		}
	}

}

void mapManager::loadingRender(HDC hdc)
{
	if (m_Loading == LOAD_START)
	{
		m_pBlack->alphaRender(hdc, m_nAlpha);
	}

}


void mapManager::saveMap(const char * szfileName)
{
	DWORD write;
	HANDLE hFile;
	hFile = CreateFile(szfileName,	// 세이브할 파일 경로 / 파일이름
		GENERIC_WRITE,			// 접근 방식 지정
		0,						// 파일 공유 방식 지정 (0) : 공유 안함
								// FILE_SHARE_DELETE : 삭제 접근 요청시 공유
		NULL,					// 보안 관련 옵션
		CREATE_NEW,			// CREATE_ALWAYS : 새로운 파일 생성, 동일한 이름의 파일이 있으면 덮어쓴다
								// CREATE_NEW : 새로운 파일 생성
								// OPEN_EXISTING : 파일이 존재하면 오픈, 없으면 에러코드 리턴
		FILE_ATTRIBUTE_NORMAL,	// FILE_ATTRIBUTE_NORMAL : 다른 속성이 없다
								// FILE_ATTRIBUTE_READONLY : 읽기 전용 파일
								// FILE_ATTRIBUTE_HIDDEN : 숨김 파일 생성
		NULL);

	// 파일에 내용을 쓴다
	WriteFile(hFile, m_pTiles, sizeof(tagTile) *TILE_X *TILE_Y, &write, NULL);

	// 다 쓴 파일 핸들을 삭제
	CloseHandle(hFile);
}

void mapManager::loadingProcess()
{
	if (m_Loading == LOAD_START)
	{
		m_nAlpha += 10;
		if (m_nAlpha >= 250)
		{
			m_nAlpha = 0;
			m_Loading = LOAD_END;
		}
	}
	if (m_Loading == LOAD_END)
	{
		m_Loading = LOAD_FALSE;
		//string temp;
		//temp = "image/temp_1111.map";
		//saveMap(tempCurrMapId);
		g_mapSize.mapSizeX = m_ntempX;
		g_mapSize.mapSizeY = m_ntempY;
		loadMap(tempLoadMapId);
	}
}

void mapManager::loadingMap(const char * szfileName, int mapSizex, int mapSizey)
{
	m_Loading = LOAD_START;
	tempLoadMapId = szfileName;
	m_ntempX = mapSizex * 64;
	m_ntempY = mapSizey * 64;
}

void mapManager::loadMap(const char* szfileName)
{
	DWORD read;
	HANDLE hFile;

	hFile = CreateFile(szfileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	m_iter = m_map.find(szfileName);

	// 바꾸고자 하는 맵을 못찾으면 새로 저장
	if (m_iter == m_map.end())
	{
		m_map.insert(pair<string, tagTile*>(szfileName, m_pTiles));
		ReadFile(hFile, m_pTiles, sizeof(tagTile) *TILE_X *TILE_Y, &read, NULL);
		OBJMANAGER->release();
		SetTree();
	}
		
	// 바꿀 맵 있으면
	else
	{
		delete[] m_pTiles;
		//TILE_X = g_mapSize.mapSizeX / TILE_SIZE_1;
		//TILE_Y = g_mapSize.mapSizeY / TILE_SIZE_1;
		m_pTiles = new tagTile[TILE_X*TILE_Y];

		ReadFile(hFile, m_pTiles, sizeof(tagTile) *TILE_X *TILE_Y, &read, NULL);
	}

	//ReadFile(hFile, m_pTiles, sizeof(tagTile) *TILE_X *TILE_Y, &read, NULL);
	//SetTree();
	CloseHandle(hFile);
	tempCurrMapId = szfileName;
}

void mapManager::SetTree()
{
	for (int i = 0; i < TILE_X * TILE_Y; i++)
	{
		m_pTiles[i].rc = RectMake((i % TILE_X)*TILE_SIZE_1 - CAMERA->getX(), (i / TILE_X)*TILE_SIZE_1 - CAMERA->getY(), TILE_SIZE_1, TILE_SIZE_1);
	}

	for (int y = 0; y < TILE_Y; y++)
	{
		for (int x = 0; x < TILE_X; x++)
		{			
			if (m_pTiles[y*TILE_X + x].object == TREE_SMALL)
			{
				OBJMANAGER->setTree(m_pTiles[y*TILE_X + x].rc.left, m_pTiles[y*TILE_X + x].rc.bottom,0, y*TILE_X + x);
			}

			if (m_pTiles[y*TILE_X + x].object == TREE_BIG)
			{
				OBJMANAGER->setTree(m_pTiles[y*TILE_X + x].rc.left, m_pTiles[y*TILE_X + x].rc.bottom, 1,y*TILE_X + x);
			}

			if (m_pTiles[y*TILE_X + x].object == CROP)
			{
				OBJMANAGER->setCrop(m_pTiles[y*TILE_X + x].rc.left, m_pTiles[y*TILE_X + x].rc.bottom, 101, y*TILE_X + x);
			}

			if (m_pTiles[y*TILE_X + x].object == NPC)
			{
				OBJMANAGER->setNpc(m_pTiles[y*TILE_X + x].rc.left, m_pTiles[y*TILE_X + x].rc.bottom, 0, y*TILE_X + x);
			}
		}
	}
	OBJMANAGER->getPlayer(m_player);
}
