#include "stdafx.h"
#include "mapManager.h"

#include "objTree.h"
#include "objCrop.h"

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
	tempMapId = "";

	m_pUibgsample = IMAGEMANAGER->findImage("maptoolui");

	TILE_SIZE_1 = 64;
	TILE_X = MAPSIZEX / TILE_SIZE_1;
	TILE_Y = MAPSIZEY / TILE_SIZE_1;
	m_pTiles = new tagTile[TILE_X*TILE_Y];

	//	기본 타일 정보 셋팅
	for (int y = 0; y < TILE_Y; y++)
	{
		for (int x = 0; x < TILE_X; x++)
		{
			m_pTiles[y * TILE_X + x].rc = RectMake(x*TILE_SIZE_1, y*TILE_SIZE_1, TILE_SIZE_1, TILE_SIZE_1);
			m_pTiles[y * TILE_X + x].terrainFrameX = 0;
			m_pTiles[y * TILE_X + x].terrainFrameY = 1;
			m_pTiles[y * TILE_X + x].terrain = NOMALTILE;
			m_pTiles[y * TILE_X + x].object = OBJ_NULL;
			m_pTiles[y * TILE_X + x].objectID = OBID_NULL;
			m_pTiles[y * TILE_X + x].index = y * TILE_X + x;
			m_pTiles[y * TILE_X + x].isCollide = false;
		}
	}
	
	m_pObjectMap = new objTree;
	m_pObjectMap->init();

	m_pObjectCrop = new objCrop;
	m_pObjectCrop->init();

	m_vecTile.resize(TILE_Y*TILE_X);
	
	return S_OK;
}

void mapManager::release()
{
	delete[] m_pTiles;
}

void mapManager::update()
{
	for (int y = 0; y < TILE_Y; y++)
	{
		for (int x = 0; x < TILE_X; x++)
		{
			m_pTiles[y * TILE_X + x].rc = RectMake(x*TILE_SIZE_1 - CAMERA->getX(), y*TILE_SIZE_1 - CAMERA->getY(), TILE_SIZE_1, TILE_SIZE_1);
		}
	}

	m_pObjectMap->update();
	m_pObjectCrop->update();
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
		loadMap(tempMapId);
	}
}

void mapManager::render(HDC hdc)
{
	//for (int y = 0; y < TILE_Y; y++)
	//{
	//	for (int x = 0; x < TILE_X; x++)
	//	{
	//		int cullX = CAMERA->getX() / TILE_SIZE_1;
	//		int cullY = CAMERA->getY() / TILE_SIZE_1;

	//		m_indexCamera = (y + cullY)*TILE_X + (x + cullX);
	//		if (m_indexCamera >= (TILE_X * TILE_Y)) continue;

	//		m_pTileSet->frameRenderTile(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.top
	//			, 0, 1, TILE_SIZE_1, TILE_SIZE_1);
	//	}
	//}

	for (int y = 0; y < TILE_Y; y++)
	{
		for (int x = 0; x < TILE_X; x++)
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
			else
			{
				m_pTileSet->frameRenderTile(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.top
					, 0, 1, TILE_SIZE_1, TILE_SIZE_1);
			}

			m_pTileSet->frameRenderTile(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.top
				, m_pTiles[m_indexCamera].terrainFrameX, m_pTiles[m_indexCamera].terrainFrameY, TILE_SIZE_1, TILE_SIZE_1);

			if (m_pTiles[m_indexCamera].object != OBJ_NULL)
			{
				//if (m_pTiles[m_indexCamera].objectID != OBID_2 && m_pTiles[m_indexCamera].objectID != OBID_3)
				//{
				//	m_pObject->frameRenderTile(hdc,
				//		m_pTiles[m_indexCamera].rc.left,
				//		m_pTiles[m_indexCamera].rc.top,
				//		m_pTiles[m_indexCamera].objectFrameX,
				//		m_pTiles[m_indexCamera].objectFrameY, TILE_SIZE_1, TILE_SIZE_1);
				//}

				//if (m_pTiles[m_indexCamera].objectID != OBID_1 && m_pTiles[m_indexCamera].objectID != OBID_3)
				//{
				//	m_pObject2->frameRenderTile(hdc,
				//		m_pTiles[m_indexCamera].rc.left,
				//		m_pTiles[m_indexCamera].rc.top,
				//		m_pTiles[m_indexCamera].objectFrameX,
				//		m_pTiles[m_indexCamera].objectFrameY, TILE_SIZE_1, TILE_SIZE_1);
				//}

				//if (m_pTiles[m_indexCamera].objectID != OBID_1 && m_pTiles[m_indexCamera].objectID != OBID_2)
				//{
				//	m_pObject3->frameRenderTile(hdc,
				//		m_pTiles[m_indexCamera].rc.left,
				//		m_pTiles[m_indexCamera].rc.top,
				//		m_pTiles[m_indexCamera].objectFrameX,
				//		m_pTiles[m_indexCamera].objectFrameY, TILE_SIZE_1, TILE_SIZE_1);
				//}

				//if (m_pTiles[m_indexCamera].object == TREE_BIG || m_pTiles[m_indexCamera].object == TREE_SMALL)
				if (m_pTiles[m_indexCamera].object == TREE_SMALL)
					//m_pObjectMap->render(hdc, m_pTiles[m_indexCamera].rc.left+ (m_pTiles[m_indexCamera].rc.right- m_pTiles[m_indexCamera].rc.left)/2, m_pTiles[m_indexCamera].rc.bottom);
					m_pObjectMap->render(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.bottom);

				else if(m_pTiles[m_indexCamera].object == CROP)
					m_pObjectCrop->render(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.bottom);
				
				else
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

	//char str[128];

	//for (int y = 0; y < TILE_Y; y++)
	//{	
	//for (int x = 0; x < TILE_X; x++)
	//	{
	//		int cullX = CAMERAMANAGER->getCameraX() / TILE_SIZE_1;
	//		int cullY = CAMERAMANAGER->getCameraY() / TILE_SIZE_1;

	//		m_indexCamera = (y + cullY)*TILE_X + (x + cullX);
	//		if (m_indexCamera >= (TILE_X * TILE_Y)) continue;

	//		if (m_pTiles[m_indexCamera].terrain==WATER)
	//		{
	//			sprintf_s(str, 128, "%d", 1);
	//			TextOut(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.top, str, strlen(str));
	//		}
	//		else
	//		{
	//			sprintf_s(str, 128, "%d", 0);
	//			TextOut(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.top, str, strlen(str));
	//		}
	//		//sprintf_s(str, 128, "%d", m_pTiles[m_indexCamera].index);
	//		//TextOut(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.top, str, strlen(str));
	//	}
	//}
}

void mapManager::loadingRender(HDC hdc)
{
	if (m_Loading == LOAD_START)
	{
		m_pBlack->alphaRender(hdc, m_nAlpha);
	}

}

void mapManager::loadingMap(const char * szfileName)
{
	m_Loading = LOAD_START;
	tempMapId = szfileName;
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

	ReadFile(hFile, m_pTiles, sizeof(tagTile) *TILE_X *TILE_Y, &read, NULL);

	CloseHandle(hFile);

}
