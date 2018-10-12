#include "stdafx.h"
#include "mapTool.h"

//LPTSTR	g_lpszClass2 = (LPTSTR)TEXT("MapTool");
HWND hButtonOpenFileDialog;
HWND hEditFileToBeOpened;
OPENFILENAME OFN;
const UINT nFileNameMaxLen = 512;
char szFileName[nFileNameMaxLen];
TCHAR szFileName2[256] = _T("");

RECT rc;

int SAMPLE_TILE_X;
int SAMPLE_TILE_Y;

mapTool::mapTool()
{	
}

mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{	
	m_pTileSet = IMAGEMANAGER->findImage("earthAll");
	m_pObject = IMAGEMANAGER->findImage("town_Shop");
	m_pObject2 = IMAGEMANAGER->findImage("town_Nomal");
	m_pObject3 = IMAGEMANAGER->findImage("object3");
	m_pbg = IMAGEMANAGER->findImage("whitebackground");
	m_pUibgsample = IMAGEMANAGER->findImage("maptoolui");

	g_hWndChildSample = CreateWindow(TEXT("MapSample"), NULL, WS_CHILD | WS_VISIBLE| WS_OVERLAPPEDWINDOW,
		TILE_SIZE_SAMPLE * 50, WINSIZEY - 470, WINSIZEX - TILE_SIZE_SAMPLE * 50, 450, g_hWnd, (HMENU)0, g_hInstance, NULL);
	
	TILE_SIZE_1 = 64;
	TILE_X = MAPSIZEX / TILE_SIZE_1;
	TILE_Y = MAPSIZEY / TILE_SIZE_1;

	SAMPLE_TILE_X = 20;
	SAMPLE_TILE_Y = 20;

	// 미니맵
	m_minisize = 16; // 축적도, 높을수록 작아짐
	m_minipositionX = 1000;
	m_minipositionY = 10;
	CAMERAMANAGER->cameraMiniInit(m_minipositionX + TILE_SIZE_1/ m_minisize/2* TILE_X, m_minipositionY+ TILE_SIZE_1 / m_minisize/2* TILE_Y);

	m_isObject = false;
	m_sampleObjChoice = IMGOBJ_1;
	m_rcSave = RectMakeCenter(0, 0, 0, 0);
	m_rcDragCheck = RectMakeCenter(0, 0, 0, 0);

	m_pTiles = new tagTile[TILE_X*TILE_Y];
	m_pSampleTiles = new tagSampleTile[SAMPLE_TILE_X*SAMPLE_TILE_Y];
	m_pMini = new tagTile[TILE_X*TILE_Y];

	m_ptempSampleObj1 = new tempSampleTile[SAMPLE_TILE_X*SAMPLE_TILE_Y];
	m_ptempSampleObj2 = new tempSampleTile[SAMPLE_TILE_X*SAMPLE_TILE_Y];
	m_ptempSampleObj3 = new tempSampleTile[SAMPLE_TILE_X*SAMPLE_TILE_Y];

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

	// 샘플타일 기본 위치
	m_nImageX = WINSIZEX - m_pTileSet->getWidth() - TILE_SIZE_1;

	for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++)
	{
		m_pSampleTiles[i].rc = RectMake(m_nImageX + (i % SAMPLE_TILE_X) * TILE_SIZE_SAMPLE, (i / SAMPLE_TILE_X) * TILE_SIZE_SAMPLE, TILE_SIZE_SAMPLE, TILE_SIZE_SAMPLE);
		m_pSampleTiles[i].frameX = i % (m_pTileSet->getWidth() / TILE_SIZE_SAMPLE);
		m_pSampleTiles[i].frameY = i / (m_pTileSet->getWidth() / TILE_SIZE_SAMPLE);
		m_pSampleTiles[i].object = MYHOME;
		m_pSampleTiles[i].objectID = OBID_1;
		m_pSampleTiles[i].terrain = NOMALTILE;
		m_pSampleTiles[i].isCollide = false;
		//오브젝트 충돌 임시 저장소 1
		m_ptempSampleObj1[i].isCollide = false;
		m_ptempSampleObj2[i].isCollide = false;
		m_ptempSampleObj3[i].isCollide = false;
	}

	// 상호작용가능한 땅
	m_pSampleTiles[0].terrain = EARTH;
	m_pSampleTiles[1].terrain = EARTH;
	m_pSampleTiles[2].terrain = EARTH;
	m_pSampleTiles[3].terrain = EARTH;
	m_pSampleTiles[4].terrain = EARTH;
	m_pSampleTiles[5].terrain = EARTH;

	// 경작지 구분
	for (int y = 6; y < 10; ++y)
	{
		for (int x = 9; x < 17; x++)
		{
			if(x >=13)
				m_pSampleTiles[y*20+x].terrain = WETFARMLAND;

			else
				m_pSampleTiles[y*20+x].terrain = FARMLAND;
		}
	}

	//물
	for (int y = 0; y < 4; y++)
	{
		for (int x = 12; x < 15; x++)
		{
			m_pSampleTiles[y * 20 + x].terrain = WETEREARTH;
		}
	}

	// 물
	m_pSampleTiles[11].terrain = WATER;
	m_pSampleTiles[31].terrain = WATER;
	m_pSampleTiles[92].terrain = WATER;

	for (int y = 6; y < 10; y++)
	{
		for (int x = 17; x < 20; x++)
		{
			m_pSampleTiles[y * 20 + x].terrain = WATER;
		}
	}
	
	//바다
	m_pSampleTiles[140].terrain = SEA;
	m_pSampleTiles[141].terrain = SEA;
	m_pSampleTiles[144].terrain = SEA;
	m_pSampleTiles[146].terrain = SEA;
	m_pSampleTiles[166].terrain = SEA;
		
	EnableWindow(m_hBtnSetCollision, FALSE);
	EnableWindow(m_hBtnCancelCollision, FALSE);
	
	m_vecSelectedTile.reserve(SAMPLE_TILE_X * SAMPLE_TILE_Y);
	return S_OK;
}

void mapTool::release()
{
	delete[] m_pTiles;
	delete[] m_pSampleTiles;
	delete[] m_pMini;

	delete[] m_ptempSampleObj1;
	delete[] m_ptempSampleObj2;
	delete[] m_ptempSampleObj3;
}

void mapTool::update()
{
	// 타일 옮기기
	if (m_isSampleOn)
	{
		sampleTileSave();

		if (m_isObject)
			TileObjSet();

		else
			TileSet();

		m_vecSelectedTile.clear();
	}
	
	// 샘플타일 ui 키기
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		m_isSampleOn = true;
		m_isSampleOnCount++;

		// 샘플타일 끄기
		if (m_isSampleOnCount == 2)
		{
			m_isSampleOnCount = 0;
			m_isSampleOn = false;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		m_isMiniMapOn = true;
		m_isMiniMapOnCount++;
		if (m_isMiniMapOnCount == 2)
		{
			m_isMiniMapOnCount = 0;
			m_isMiniMapOn = false;
		}
	}

	// camera 이동
	CAMERAMANAGER->update();
	for (int y = 0; y < TILE_Y; y++)
	{
		for (int x = 0; x < TILE_X; x++)
		{
			m_pTiles[y * TILE_X + x].rc = RectMake(x*TILE_SIZE_1 - CAMERAMANAGER->getCameraX(), y*TILE_SIZE_1 - CAMERAMANAGER->getCameraY(), TILE_SIZE_1, TILE_SIZE_1);
		}
	}	

	// 씬전환
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SCENEMANAGER->changeScene("startScene");
		DestroyWindow(g_hWndChildSample);
	}
}

void mapTool::render(HDC hdc)
{
	// 백그라운드
	for (int y = 0; y < WINSIZEY / TILE_SIZE_1+1; y++)
	{
		for (int x = 0; x < WINSIZEX / TILE_SIZE_1+1; x++)
		{
			int cullX = CAMERAMANAGER->getCameraX() / TILE_SIZE_1;
			int cullY = CAMERAMANAGER->getCameraY() / TILE_SIZE_1;
			
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
		}
	}

	for (int y = 0; y < WINSIZEY / TILE_SIZE_1+1; y++)
	{
		for (int x = 0; x < WINSIZEX / TILE_SIZE_1+1; x++)
		{
			int cullX = CAMERAMANAGER->getCameraX() / TILE_SIZE_1;
			int cullY = CAMERAMANAGER->getCameraY() / TILE_SIZE_1;

			m_indexCamera = (y + cullY)*TILE_X + (x + cullX);
			if (m_indexCamera >= (TILE_X * TILE_Y)) continue;

			m_pTileSet->frameRenderTile(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.top
				, m_pTiles[m_indexCamera].terrainFrameX, m_pTiles[m_indexCamera].terrainFrameY, TILE_SIZE_1, TILE_SIZE_1);
		
			if (m_pTiles[m_indexCamera].object != OBJ_NULL)
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

	//미니맵
	if (m_isMiniMapOn)
	{
		for (int y = 0; y < TILE_Y; y++)
		{
			for (int x = 0; x < TILE_X; x++)
			{
				m_pMini[y * TILE_X + x].rc.left = m_pTiles[y * TILE_X + x].rc.left / m_minisize;
				m_pMini[y * TILE_X + x].rc.top = m_pTiles[y * TILE_X + x].rc.top / m_minisize;
				m_pMini[y * TILE_X + x].terrainFrameX = m_pTiles[y * TILE_X + x].terrainFrameX;
				m_pMini[y * TILE_X + x].terrainFrameY = m_pTiles[y * TILE_X + x].terrainFrameY;

				// 맵 타일
				m_pTileSet->frameRenderMini(hdc,
					m_pMini[y*TILE_X + x].rc.left + m_minipositionX,
					m_pMini[y*TILE_X + x].rc.top + m_minipositionY, m_pTiles[y*TILE_X + x].terrainFrameX,
					m_pTiles[y*TILE_X + x].terrainFrameY, m_minisize, TILE_SIZE_1, TILE_SIZE_1);

				// 오브젝트
				if (m_pTiles[y*TILE_X + x].object != OBJ_NULL)
				{
					if (m_pTiles[y*TILE_X + x].objectID != OBID_2 && m_pTiles[m_indexCamera].objectID != OBID_3)
					{
						m_pObject->frameRenderMini(hdc,
							m_pMini[y*TILE_X + x].rc.left + m_minipositionX,
							m_pMini[y*TILE_X + x].rc.top + m_minipositionY,
							m_pTiles[y*TILE_X + x].objectFrameX,
							m_pTiles[y*TILE_X + x].objectFrameY, m_minisize, TILE_SIZE_1, TILE_SIZE_1);
					}

					if (m_pTiles[y*TILE_X + x].objectID != OBID_1 && m_pTiles[m_indexCamera].objectID != OBID_3)
					{
						m_pObject2->frameRenderMini(hdc,
							m_pMini[y*TILE_X + x].rc.left + m_minipositionX,
							m_pMini[y*TILE_X + x].rc.top + m_minipositionY,
							m_pTiles[y*TILE_X + x].objectFrameX,
							m_pTiles[y*TILE_X + x].objectFrameY, m_minisize, TILE_SIZE_1, TILE_SIZE_1);
					}

					if (m_pTiles[m_indexCamera].objectID != OBID_1 && m_pTiles[m_indexCamera].objectID != OBID_2)
					{
						m_pObject3->frameRenderMini(hdc,
							m_pTiles[m_indexCamera].rc.left,
							m_pTiles[m_indexCamera].rc.top,
							m_pTiles[m_indexCamera].objectFrameX,
							m_pTiles[m_indexCamera].objectFrameY, m_minisize, TILE_SIZE_1, TILE_SIZE_1);
					}
				}
			}
		}
	}	
	
	// 샘플보기
	if (m_isSampleOn)
	{
		// 툴
		m_pUibgsample->render(hdc, m_nImageX -5, 0);

		if (m_isObject)
		{
			switch (m_sampleObjChoice)
			{
			case IMGOBJ_1:
				m_pObject->render(hdc, m_nImageX,0);
				break;

			case IMGOBJ_2:
				m_pObject2->render(hdc, m_nImageX, 0);
				break;

			case IMGOBJ_3:
				m_pObject3->render(hdc, m_nImageX, 0);
				break;

			}
			
			// 확인
			if (m_isMove)
				m_pObject->frameRender(hdc, g_ptMouse.x, g_ptMouse.y, m_pSampleTiles[m_sampleTileIndex].frameX, m_pSampleTiles[m_sampleTileIndex].frameY);		
		}

		else
		{
			// 타일
			if (m_pTileSet)
				m_pTileSet->render(hdc, m_nImageX, 5);
		}
	}

	char str[128];
	SetBkMode(hdc, TRANSPARENT);

	sprintf_s(str, 128, "%d", g_ptMouse.x);
	TextOut(hdc, 800, 250, str, strlen(str));
	sprintf_s(str, 128, "%d", CAMERAMANAGER->getCameraX());
	TextOut(hdc, 0, 250, str, strlen(str));
	sprintf_s(str, 128, "%d", CAMERAMANAGER->getCameraY());
	TextOut(hdc, 0, 350, str, strlen(str));

	sprintf_s(str, 128, "left : %d", rc.left);
	TextOut(hdc, 1000, 150, str, strlen(str));
	sprintf_s(str, 128, "top : %d", rc.top);
	TextOut(hdc, 1000, 50, str, strlen(str));
	sprintf_s(str, 128, "right : %d", rc.right);
	TextOut(hdc, 850, 50, str, strlen(str));
	sprintf_s(str, 128, "bottom : %d", rc.bottom);
	TextOut(hdc, 850, 150, str, strlen(str));

	//for (int y = 0; y < WINSIZEY / TILE_SIZE_1 + 1; y++)
	//{
	//	for (int x = 0; x < WINSIZEX / TILE_SIZE_1 + 1; x++)
	//	{
	//		int cullX = CAMERAMANAGER->getCameraX() / TILE_SIZE_1;
	//		int cullY = CAMERAMANAGER->getCameraY() / TILE_SIZE_1;

	//		m_indexCamera = (y + cullY)*TILE_X + (x + cullX);
	//		if (m_indexCamera >= (TILE_X * TILE_Y)) continue;

	//		if (m_pTiles[m_indexCamera].isCollide)
	//		{
	//			sprintf_s(str, 128, "%d", 1);
	//			TextOut(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.top, str, strlen(str));
	//		}
	//		else
	//		{
	//			sprintf_s(str, 128, "%d", 0);
	//			TextOut(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.top, str, strlen(str));
	//		}
	//		sprintf_s(str, 128, "%d", m_pTiles[m_indexCamera].index);
	//		//TextOut(hdc, m_pTiles[m_indexCamera].rc.left, m_pTiles[m_indexCamera].rc.top, str, strlen(str));
	//	}
	//}

	// 충돌체 확인
	if (m_isObject)
	{
		for (int y = 0; y < SAMPLE_TILE_Y; ++y)
		{
			for (int x = 0; x < SAMPLE_TILE_X; x++)
			{
				if (m_pSampleTiles[y*SAMPLE_TILE_X + x].isCollide)
				{
					sprintf_s(str, 128, "%d", 1);
					TextOut(hdc, m_pSampleTiles[y*SAMPLE_TILE_X + x].rc.left, m_pSampleTiles[y*SAMPLE_TILE_X + x].rc.top, str, strlen(str));
				}
				else
				{
					sprintf_s(str, 128, "%d", 0);
					TextOut(hdc, m_pSampleTiles[y*SAMPLE_TILE_X + x].rc.left, m_pSampleTiles[y*SAMPLE_TILE_X + x].rc.top, str, strlen(str));
				}
			}
		}
	}

	

	//for (int y = 0; y < TILE_Y; y++)
	//{
	//	for (int x = 0; x < TILE_X; x++)
	//	{
	//		sprintf_s(str, 128, "%d", m_pTiles[y*TILE_X+x].index);
	//		TextOut(hdc, m_pTiles[y*TILE_X + x].rc.left, m_pTiles[y*TILE_X + x].rc.top, str, strlen(str));
	//	}
	//}

	//격자보기
	//for (int i = 0; i < WINSIZEX / TILE_SIZE_1; i++)
	//{
	//	MoveToEx(hdc, i * TILE_SIZE_1, 0, NULL);
	//	LineTo(hdc, i * TILE_SIZE_1, WINSIZEY);
	//}

	//for (int i = 0; i < WINSIZEY / TILE_SIZE_1; i++)
	//{
	//	MoveToEx(hdc, 0, i * TILE_SIZE_1, NULL);
	//	LineTo(hdc,WINSIZEX , i * TILE_SIZE_1);
	//}

	//드래그 보기
	if (m_isDrag)
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}


}

// 메인
LRESULT mapTool::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT crt;

	switch (iMessage)
	{
	case WM_CREATE:
		rc = RectMakeCenter(0, 0, 0, 0);
		return 0;

	case WM_LBUTTONDOWN:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		rc.left = LOWORD(lParam);
		rc.top = HIWORD(lParam);

		// 타일 0,0에서 부터 시작하기 위해 보정
		rc.left = (rc.left / TILE_SIZE_1)*TILE_SIZE_1;
		rc.top = (rc.top / TILE_SIZE_1)*TILE_SIZE_1;
		m_isClick = true;
		return 0;

	case WM_MOUSEMOVE:
		if (m_isClick)
		{
			m_isDrag = true;
			g_ptMouse.x = LOWORD(lParam);
			g_ptMouse.y = HIWORD(lParam);	
			//rc.right = LOWORD(lParam);
			//rc.bottom = HIWORD(lParam);

			// 맵타일 사이즈대로 그리기 위해 보정
			/*rc.right = rc.left+((g_ptMouse.x - rc.left) / TILE_SIZE_1)*TILE_SIZE_1;
			rc.bottom = rc.top + ((g_ptMouse.y - rc.top) / TILE_SIZE_1)*TILE_SIZE_1;*/			

			rc.right = rc.left + ((g_ptMouse.x - rc.left) / TILE_SIZE_SAMPLE)*TILE_SIZE_SAMPLE;
			rc.bottom = rc.top + ((g_ptMouse.y - rc.top) / TILE_SIZE_SAMPLE)*TILE_SIZE_SAMPLE;
		}

		else
		{
			g_ptMouse.x = LOWORD(lParam);
			g_ptMouse.y = HIWORD(lParam);
		}
		return 0;

	case WM_LBUTTONUP:
		m_isClick = false;
		m_isDrag = false;
		m_isClickSave = false;
		m_rcDragCheck = rc;
		if (rc.top > rc.bottom)
		{
			m_rcSwap = rc.top;
			rc.top = rc.bottom;
			rc.bottom = m_rcSwap;
		}
		if (rc.left > rc.right)
		{
			m_rcSwap = rc.left;
			rc.left = rc.right;
			rc.right = m_rcSwap;
		}
		m_rcSave = rc;
		m_isAddvec = true;
		rc = RectMakeCenter(0, 0, 0,0);
		m_rcSwap = -1;
		return 0;

	case WM_RBUTTONDOWN:
		objectEraser();
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			//m_moveX+= m_moveX;
			break;

		case VK_RIGHT:
			break;

		case VK_ESCAPE:
			break;
		}
		return 0;

	case WM_INITDIALOG:
		break;

	case WM_PRINT:
		//hdc = BeginPaint(hWnd, &ps);
		//EndPaint(hWnd, &ps);
		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{	
		}
		break;
	}

	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED)
		{
			GetClientRect(hWnd, &crt);
			InvalidateRect(hWnd, NULL, TRUE);
			//MoveWindow(hWnd, NULL, NULL, crt.right- crt.left, crt.bottom- crt.top, true);
		}
		return 0;

	case WM_DESTROY:
		g_wndCount--;
		if (g_wndCount == 0)
		{
			PostQuitMessage(0);
		}
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

LRESULT mapTool::ChildMapSampleProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT crt;

	switch (iMessage)
	{
	case WM_CREATE:
		//버튼 셋팅
		m_hBtnSelectSample = CreateWindow("button", "SampleTile", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			0, 90, 250, 70, hWnd, HMENU(BTN_GROUP1), g_hInstance, NULL);

		m_hBtnSelectTileSize = CreateWindow("button", "Tile Size", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			0, 0, 370, 70, hWnd, HMENU(BTN_GROUP2), g_hInstance, NULL);
			   
		m_hBtnSelectDraw = CreateWindow("button", "Draw Type", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			0, 180, 250, 70, hWnd, HMENU(BTN_GROUP3), g_hInstance, NULL);
			   
		m_hBtnSelectCollision = CreateWindow("button", "Collision Setting", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			0, 270, 250, 70, hWnd, HMENU(BTN_GROUP4), g_hInstance, NULL);

		m_hBtnSelectEnable = CreateWindow("button", "Setting Enable", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			260, 270, 120, 45, hWnd, HMENU(BTN_GROUP5), g_hInstance, NULL);

		// tile sample
		m_hBtnSelectTerrain = CreateWindow("button", "Terrain", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON| WS_GROUP,
			15, 120, 100, 30, hWnd, HMENU(BTN_01), g_hInstance, NULL);

		m_hBtnSelectObject = CreateWindow("button", "Object", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			130, 120, 100, 30,hWnd, HMENU(BTN_02), g_hInstance, NULL);

		m_hBtnLeft = CreateWindow("button", "Left", WS_CHILD | WS_VISIBLE | BS_BOTTOM,
			260, 140, 50, 20, hWnd, HMENU(BTN_LEFT), g_hInstance, NULL);

		m_hBtnRight = CreateWindow("button", "Right", WS_CHILD | WS_VISIBLE | BS_BOTTOM,
			320, 140, 50, 20, hWnd, HMENU(BTN_RIGHT), g_hInstance, NULL);

		m_hBtnEraser = CreateWindow("button", "Eraser", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			380, 140, 50, 20,hWnd, HMENU(BTN_03), g_hInstance, NULL);

		// tile size
		m_hBtnSelectTileSize16 = CreateWindow("button", "X 16", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON| WS_GROUP,
			15, 30, 100, 30, hWnd, HMENU(BTN_04), g_hInstance, NULL);

		m_hBtnSelectTileSize32 = CreateWindow("button", "X 32", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			130, 30, 100, 30, hWnd, HMENU(BTN_05), g_hInstance, NULL);

		m_hBtnSelectTileSize64 = CreateWindow("button", "X 64", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			245, 30, 100, 30, hWnd, HMENU(BTN_06), g_hInstance, NULL);

		// select draw type
		m_hBtnOnceDraw = CreateWindow("button", "Once", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			15, 210, 100, 30, hWnd, HMENU(BTN_07), g_hInstance, NULL);

		m_hBtnDragDraw = CreateWindow("button", "Drag", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			130, 210, 100, 30, hWnd, HMENU(BTN_08), g_hInstance, NULL);

		// save load
		m_hBtnSave = CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			240, 360, 100, 40, hWnd, HMENU(BTN_09), g_hInstance, NULL);

		m_hBtnLoad = CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			350, 360, 100, 40, hWnd, HMENU(BTN_10), g_hInstance, NULL);

		// collision
		m_hBtnSetCollision = CreateWindow("button", "Set", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			15, 300, 100, 30, hWnd, HMENU(BTN_11), g_hInstance, NULL);

		m_hBtnCancelCollision = CreateWindow("button", "Cancel", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			130, 300, 100, 30, hWnd, HMENU(BTN_12), g_hInstance, NULL);

		m_hBtnDeleteCollision = CreateWindow("button", "Eraser", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			260, 320, 70, 20, hWnd, HMENU(BTN_13), g_hInstance, NULL);

		// on/off
		m_hBtnCollisionON = CreateWindow("button", "ON", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			270, 295, 50, 10, hWnd, HMENU(BTN_14), g_hInstance, NULL);

		m_hBtnCollisionOFF = CreateWindow("button", "OFF", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			320, 295, 50, 10, hWnd, HMENU(BTN_15), g_hInstance, NULL);

		CheckRadioButton(hWnd, BTN_01, BTN_02, BTN_01);
		CheckRadioButton(hWnd, BTN_04, BTN_06, BTN_06);
		CheckRadioButton(hWnd, BTN_07, BTN_08, BTN_07);
		CheckRadioButton(hWnd, BTN_11, BTN_12, BTN_12);
		CheckRadioButton(hWnd, BTN_14, BTN_15, BTN_15);
		return 0;
		
	case WM_LBUTTONDOWN:		
		return 0;

	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);		
		return 0;

	case WM_LBUTTONUP:		
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			break;

		case VK_ESCAPE:
			break;
		}
		return 0;

	case WM_PAINT:
		//hdc = BeginPaint(hWnd, &ps);
		//TextOut(hdc, 0, 0, "dddddd", 6);
		break;

	case WM_INITDIALOG:
		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case BTN_LEFT:
			m_isReverse = false;
			changeImg();
			break;

		case BTN_RIGHT:
			m_isReverse = true;
			changeImg();
			break;

			// terrain
		case BTN_01:
			if(SendMessage(m_hBtnSelectTerrain,BM_GETCHECK,0,0)== BST_CHECKED)
				m_isObject = false;
			m_rcSave = RectMakeCenter(0, 0, 0, 0);
			m_rcDragCheck = RectMakeCenter(0, 0, 0, 0);
			sampleTileinit();
			break;

			// object
		case BTN_02:
			if (SendMessage(m_hBtnSelectObject, BM_GETCHECK, 0, 0) == BST_CHECKED)
				m_isObject = true;
			m_rcSave = RectMakeCenter(0, 0, 0, 0);
			m_rcDragCheck = RectMakeCenter(0, 0, 0, 0);
			sampleTileinit();
			break;
			
			// eraser
		case BTN_03:
			objectEraserAll();
			break;

			//tilesize
		case BTN_04:
			if (SendMessage(m_hBtnSelectTileSize16, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				TILE_SIZE_1 = 16;
				reTileinit();
			}
			break;

		case BTN_05:
			if (SendMessage(m_hBtnSelectTileSize32, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				TILE_SIZE_1 = 32;
				reTileinit();
			}
			break;

		case BTN_06:
			if (SendMessage(m_hBtnSelectTileSize64, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				TILE_SIZE_1 = 64;
				reTileinit();
			}

			break;

		case BTN_07:
			if (SendMessage(m_hBtnOnceDraw, BM_GETCHECK, 0, 0) == BST_CHECKED)
				m_isDrawtype = false;
			break;

		case BTN_08:
			if (SendMessage(m_hBtnDragDraw, BM_GETCHECK, 0, 0) == BST_CHECKED)
				m_isDrawtype = true;
			break;

		//save
		case BTN_09:
			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = g_hWnd;
			ofn.lpstrFilter = _T("MAP Files(*.map)\0*.map\0All Files (*.*)\0*.*\0");
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = nFileNameMaxLen;
			ofn.lpstrDefExt = "map";
			//ofn.nFilterIndex = 1;
			//ofn.lpstrFileTitle = szFileName;
			//ofn.nMaxFileTitle = 0;
			//ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_OVERWRITEPROMPT;
			GetSaveFileName(&ofn);

			//if (0 != GetOpenFileName(&OFN))
			//{
			//}
			saveMap(szFileName);
			//MessageBox(g_hWnd, TEXT("dd"), TEXT("ddkkk"), MB_OK);
			break;

			// load
		case BTN_10:
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFile = szFileName;
			OFN.nMaxFile = nFileNameMaxLen;

			if (0 != GetOpenFileName(&OFN))
			{
				SetWindowText(hEditFileToBeOpened, OFN.lpstrFile);
				loadMap(OFN.lpstrFile);
			}
			return TRUE;

			break;

		case BTN_11:
			if (SendMessage(m_hBtnSetCollision, BM_GETCHECK, 0, 0) == BST_CHECKED)
				m_isSetCollision = true;
			break;

		case BTN_12:
			if (SendMessage(m_hBtnCancelCollision, BM_GETCHECK, 0, 0) == BST_CHECKED)
				m_isSetCollision = false;
			break;

		case BTN_13:
			if (SendMessage(m_hBtnDeleteCollision, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			{
				SendMessage(m_hBtnDeleteCollision, BM_SETCHECK, BST_CHECKED, 0);
				m_isEraserCollision = true;
			}
			else
			{
				SendMessage(m_hBtnDeleteCollision, BM_SETCHECK, BST_UNCHECKED, 0);
				m_isEraserCollision = false;
			}
			break;

			//collision 버튼활성화
		case BTN_14:
			if (SendMessage(m_hBtnCollisionON, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				EnableWindow(m_hBtnSetCollision, true);
				EnableWindow(m_hBtnCancelCollision, true);
				EnableWindow(m_hBtnDeleteCollision, false);
				m_isSettingTile = true;
			}
			break;

			//collision 버튼 비활성화
		case BTN_15:
			if (SendMessage(m_hBtnCollisionOFF, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				EnableWindow(m_hBtnSetCollision, FALSE);
				EnableWindow(m_hBtnCancelCollision, FALSE);
				EnableWindow(m_hBtnDeleteCollision, true); // tile에 있는 collision 지우는 버튼
				m_isSettingTile = false;
			}
			break;

		}
		break;
	}

	case WM_SIZE:
		//if (wParam != SIZE_MINIMIZED)
		//{
		//	GetClientRect(g_hWnd, &crt);
		//	//MoveWindow(g_hWndChildSample, 0, 0, 500, 500, true);
		//}
		return 0;

	case WM_DESTROY:
		//g_wndCount--;
		//if (g_wndCount == 0)
		//{
		//	PostQuitMessage(0);
		//}
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

// 샘플타일 저장
void mapTool::sampleTileSave()
{
	if (m_isObject)
		objectTileSave();
	
	else
		terrainTileSave();

	m_rcSave = RectMakeCenter(0, 0, 0, 0);
	m_rcDragCheck = RectMakeCenter(0, 0, 0, 0);
}

// obj save
void mapTool::objectTileSave()
{
	for (int y = 0; y < SAMPLE_TILE_Y; ++y)
	{
		for (int x = 0; x < SAMPLE_TILE_X; x++)
		{
			// 드래그 범위가 있으면
			if (!(m_rcDragCheck.left == (g_ptMouse.x / TILE_SIZE_1)*TILE_SIZE_1 && m_rcDragCheck.top == (g_ptMouse.y / TILE_SIZE_1)*TILE_SIZE_1&& m_rcDragCheck.right == 0 && m_rcDragCheck.bottom == 0))
			{
				if (IntersectRect(&rcTemp, &m_pSampleTiles[y* (m_pObject->getWidth() / TILE_SIZE_SAMPLE) + x].rc, &m_rcSave))
				{
					int iIndex = y * (m_pObject->getWidth() / TILE_SIZE_SAMPLE) + x;
					
					if (m_isSettingTile)
					{
						// 선택범위만큼 충돌체 지정, save
						if (m_isSetCollision)
							m_pSampleTiles[iIndex].isCollide = true;

						// 충돌체 해제 설정시
						else
							m_pSampleTiles[iIndex].isCollide = false;

						switch (m_sampleObjChoice)
						{
						case IMGOBJ_OBJNULL:
							break;
						case IMGOBJ_1:
							// 임시파일에 저장
							m_ptempSampleObj1[iIndex].isCollide = m_pSampleTiles[iIndex].isCollide;
							break;
						case IMGOBJ_2:
							m_ptempSampleObj2[iIndex].isCollide = m_pSampleTiles[iIndex].isCollide;
							break;
						case IMGOBJ_OBJMAX:
							m_ptempSampleObj3[iIndex].isCollide = m_pSampleTiles[iIndex].isCollide;
							break;
						default:
							break;
						}
					}
					m_vecSelectedTile.push_back(iIndex);
					m_isDragSave = true;
					m_isMove = true;
					m_isCollide = false;
				}
			}

			else
			{
				if (PtInRect(&m_pSampleTiles[y* (m_pObject->getWidth() / TILE_SIZE_SAMPLE) + x].rc, g_ptMouse))
				{
					m_isClickSave = true;
					m_sampleTileIndex = y * (m_pObject->getWidth() / TILE_SIZE_SAMPLE) + x;
					m_isMove = true;

					if (m_isSettingTile)
					{
						// 선택범위만큼 충돌체 지정, save
						if (m_isSetCollision)
							m_pSampleTiles[m_sampleTileIndex].isCollide = true;

						// 충돌체 해제 설정시
						else
							m_pSampleTiles[m_sampleTileIndex].isCollide = false;

						switch (m_sampleObjChoice)
						{
						case IMGOBJ_OBJNULL:
							break;
						case IMGOBJ_1:
							// 임시파일에 저장
							m_ptempSampleObj1[m_sampleTileIndex].isCollide = m_pSampleTiles[m_sampleTileIndex].isCollide;
							break;
						case IMGOBJ_2:
							m_ptempSampleObj2[m_sampleTileIndex].isCollide = m_pSampleTiles[m_sampleTileIndex].isCollide;
							break;
						case IMGOBJ_OBJMAX:
							m_ptempSampleObj3[m_sampleTileIndex].isCollide = m_pSampleTiles[m_sampleTileIndex].isCollide;
							break;
						default:
							break;
						}
					}					

					//// 선택범위만큼 충돌체 지정
					//m_pSampleTiles[m_sampleTileIndex].isCollide = true;

					break;
				}
			}
		}
	}

	if (m_isAddvec && m_isDragSave)
	{
		//if(m_rcSave.left>m_rcSave.right)
		sort(m_vecSelectedTile.begin(), m_vecSelectedTile.end());
		m_selectNum = m_vecSelectedTile.back() - m_vecSelectedTile.front();
		m_selectX = m_selectNum % (m_pObject->getWidth() / TILE_SIZE_SAMPLE) + 1; //x
		m_selectY = m_selectNum / (m_pObject->getWidth() / TILE_SIZE_SAMPLE) + 1; //y		

		// 시작위치
		m_startX = m_vecSelectedTile.front() % (m_pObject->getWidth() / TILE_SIZE_SAMPLE);
		m_startY = m_vecSelectedTile.front() / (m_pObject->getWidth() / TILE_SIZE_SAMPLE);
		m_isAddvec = false;
	}
}

// terr save
void mapTool::terrainTileSave()
{
	for (int y = 0; y < SAMPLE_TILE_Y; ++y)
	{
		for (int x = 0; x < SAMPLE_TILE_X; x++)
		{
			// 드래그 범위가 있으면
			if (!(m_rcDragCheck.left == (g_ptMouse.x / TILE_SIZE_1)*TILE_SIZE_1 && m_rcDragCheck.top == (g_ptMouse.y / TILE_SIZE_1)*TILE_SIZE_1&& m_rcDragCheck.right == 0 && m_rcDragCheck.bottom == 0))
			{
				if (IntersectRect(&rcTemp, &m_pSampleTiles[y* SAMPLE_TILE_X + x].rc, &m_rcSave))
				{
					int iIndex = y * SAMPLE_TILE_X + x;
					m_pSampleTiles[iIndex].terrain = m_pSampleTiles[iIndex].terrain;
					m_vecSelectedTile.push_back(iIndex);
					m_isDragSave = true;
				}
			}

			else
			{
				if (PtInRect(&m_pSampleTiles[y* SAMPLE_TILE_X + x].rc, g_ptMouse))
				{
					m_isClickSave = true;
					m_sampleTileIndex = y * SAMPLE_TILE_X + x;

					m_pSampleTiles[m_sampleTileIndex].terrain = m_pSampleTiles[y* SAMPLE_TILE_X + x].terrain;
					break;
				}
			}
		}
	}

	if (m_isAddvec && m_isDragSave)
	{
		sort(m_vecSelectedTile.begin(), m_vecSelectedTile.end());
		m_selectNum = m_vecSelectedTile.back() - m_vecSelectedTile.front();
		m_selectX = m_selectNum % SAMPLE_TILE_X + 1; //x
		m_selectY = m_selectNum / SAMPLE_TILE_Y + 1; //y		

		// 시작위치
		m_startX = m_vecSelectedTile.front() % SAMPLE_TILE_X;
		m_startY = m_vecSelectedTile.front() / SAMPLE_TILE_Y;
		m_isAddvec = false;
	}
}

void mapTool::TileSet()
{
	// 샘플타일 정보 받아옴
	if(m_isClick)
	{	
		// 드래그 해서 저장한 것 불러오기
		if (m_isDragSave)
		{
			for (int y = 0; y < TILE_Y; ++y)
			{
				for (int x = 0; x < TILE_X; ++x)
				{
					if (PtInRect(&m_pTiles[y* TILE_X + x].rc, g_ptMouse))
					{
						for (int y2 = 0; y2 < m_selectY; y2++)
						{
							for (int x2 = 0; x2 < m_selectX; x2++)
							{
								m_pTiles[(y + y2)* TILE_X + (x + x2)].terrainFrameX = m_pSampleTiles[(m_startY + y2)* SAMPLE_TILE_X + (m_startX + x2)].frameX;
								m_pTiles[(y + y2)* TILE_X + (x + x2)].terrainFrameY = m_pSampleTiles[(m_startY + y2)* SAMPLE_TILE_X + (m_startX + x2)].frameY;
								m_pTiles[(y + y2)* TILE_X + (x + x2)].terrain = m_pSampleTiles[(m_startY + y2)* SAMPLE_TILE_X + (m_startX + x2)].terrain;
							}
						}
					}
				}
			}
			m_isDragSave = false;
		}

		// 한번 클릭 한거 불러오기
		else if(m_isClickSave)
		{
			for (int y = 0; y < TILE_Y; ++y)
			{
				for (int x = 0; x < TILE_X; ++x)
				{
					if (PtInRect(&m_pTiles[y* TILE_X + x].rc, g_ptMouse))
					{
						m_pTiles[y* TILE_X + x].terrainFrameX = m_pSampleTiles[m_sampleTileIndex].frameX;
						m_pTiles[y* TILE_X + x].terrainFrameY = m_pSampleTiles[m_sampleTileIndex].frameY;
						m_pTiles[y* TILE_X + x].terrain = m_pSampleTiles[m_sampleTileIndex].terrain;
						break;
					}
				}
			}
			//한번만 저장할 수 있게 해주는 것
			// 쭉 누르고 그릴지 선택, 대신 클릭 떼면 안됨
			if (!m_isDrawtype)
				m_isClickSave = false;
			else
				m_isClickSave = true;
		}
	}
}

void mapTool::TileObjSet()
{
	checkObjCollide();

	if(m_isClick)
	{
		if (m_isDragSave)
		{
			if (m_isCollide)
			{
				m_isDragSave = false;
			}

			else
			{
				for (int y = 0; y < TILE_Y; ++y)
				{
					for (int x = 0; x < TILE_X; ++x)
					{
						if (PtInRect(&m_pTiles[y* TILE_X + x].rc, g_ptMouse))
						{
							for (int y2 = 0; y2 < m_selectY; y2++)
							{
								for (int x2 = 0; x2 < m_selectX; x2++)
								{
									if (!m_isSettingTile) // 충돌체 세팅 off일때만 그려줌
									{
										m_pTiles[(y + y2)* TILE_X + (x + x2)].objectFrameX = m_pSampleTiles[(m_startY + y2)*  (m_pObject->getWidth() / TILE_SIZE_SAMPLE) + (m_startX + x2)].frameX;
										m_pTiles[(y + y2)* TILE_X + (x + x2)].objectFrameY = m_pSampleTiles[(m_startY + y2)* (m_pObject->getWidth() / TILE_SIZE_SAMPLE) + (m_startX + x2)].frameY;
										m_pTiles[(y + y2)* TILE_X + (x + x2)].object = m_pSampleTiles[(m_startY + y2)* (m_pObject->getWidth() / TILE_SIZE_SAMPLE) + (m_startX + x2)].object;
										m_pTiles[(y + y2)* TILE_X + (x + x2)].objectID = m_pSampleTiles[(m_startY + y2)* (m_pObject->getWidth() / TILE_SIZE_SAMPLE) + (m_startX + x2)].objectID;
										// 충돌체 정보 넘겨줌
										m_pTiles[(y + y2)* TILE_X + (x + x2)].isCollide = m_pSampleTiles[(m_startY + y2)* (m_pObject->getWidth() / TILE_SIZE_SAMPLE) + (m_startX + x2)].isCollide;
									}
									m_isMove = false;
								}
							}
						}
					}
				}
				m_isDragSave = false;
			}			
		}

		else if (m_isClickSave)
		{
			for (int y = 0; y < TILE_Y; ++y)
			{
				for (int x = 0; x < TILE_X; ++x)
				{
					if (PtInRect(&m_pTiles[y* TILE_X + x].rc, g_ptMouse))
					{
						if (m_pTiles[y* TILE_X + x].object != OBJ_NULL) break;

						if (!m_isSettingTile) // 충돌체 세팅 off일때만 그려줌
						{
							m_pTiles[y* TILE_X + x].objectFrameX = m_pSampleTiles[m_sampleTileIndex].frameX;
							m_pTiles[y* TILE_X + x].objectFrameY = m_pSampleTiles[m_sampleTileIndex].frameY;
							m_pTiles[y* TILE_X + x].object = m_pSampleTiles[m_sampleTileIndex].object;
							m_pTiles[y* TILE_X + x].objectID = m_pSampleTiles[m_sampleTileIndex].objectID;
							// 충돌체 정보 넘겨줌
							m_pTiles[y* TILE_X + x].isCollide = m_pSampleTiles[m_sampleTileIndex].isCollide;
						}
						m_isMove = false;						
						break;
					}
				}
			}
			// 쭉 누르고 그릴지 선택, 대신 클릭 떼면 안됨
			if (!m_isDrawtype)
				m_isClickSave = false;
			else
				m_isClickSave = true;
		}
	}

}

void mapTool::objectEraserAll()
{
	for (int y = 0; y < TILE_Y; ++y)
	{
		for (int x = 0; x < TILE_X; ++x)
		{
			m_pTiles[y * TILE_X + x].object = OBJ_NULL;
			m_pTiles[y * TILE_X + x].isCollide = false; //충돌 없앰
		}
	}
}

void mapTool::objectEraser()
{
	for (int y = 0; y < TILE_Y; ++y)
	{
		for (int x = 0; x < TILE_X; ++x)
		{
			if (PtInRect(&m_pTiles[y * TILE_X + x].rc, g_ptMouse))
			{
				if (m_isEraserCollision)
				{
					m_pTiles[y * TILE_X + x].isCollide = false; //충돌 없앰
				}
				else
				{
					m_pTiles[y * TILE_X + x].object = OBJ_NULL;
					m_pTiles[y * TILE_X + x].isCollide = false; //충돌 없앰
				}
			}
		}
	}
}

void mapTool::objectTypeInit()
{
	switch (m_sampleObjChoice)
	{
	case IMGOBJ_1:
		for (int i = 0; i < SAMPLE_TILE_X *SAMPLE_TILE_Y; i++)
		{
			m_pSampleTiles[i].object = SHOP;
		}
		m_pSampleTiles[181].object = OBJ_NULL;
		m_pSampleTiles[182].object = OBJ_NULL;
		m_pSampleTiles[183].object = OBJ_NULL;
		m_pSampleTiles[184].object = OBJ_NULL;
		m_pSampleTiles[185].object = OBJ_NULL;
		m_pSampleTiles[186].object = OBJ_NULL;
		m_pSampleTiles[190].object = OBJ_NULL;
		m_pSampleTiles[192].object = OBJ_NULL;
		m_pSampleTiles[193].object = OBJ_NULL;
		m_pSampleTiles[194].object = OBJ_NULL;
		m_pSampleTiles[195].object = OBJ_NULL;
		m_pSampleTiles[199].object = OBJ_NULL;

		m_pSampleTiles[200].object = OBJ_NULL;
		m_pSampleTiles[201].object = OBJ_NULL;
		m_pSampleTiles[205].object = OBJ_NULL;
		for (int i = 12; i < 20; i++)
		{
			m_pSampleTiles[10*20+i].object = OBJ_NULL;
		}

		m_pSampleTiles[220].object = OBJ_NULL;
		m_pSampleTiles[221].object = OBJ_NULL;
		for (int i = 15; i < 20; i++)
		{
			m_pSampleTiles[11 * 20 + i].object = OBJ_NULL;
		}

		m_pSampleTiles[240].object = OBJ_NULL;
		for (int y = 12; y < 20; y++)
		{
			for (int i = 16; i < 20; i++)
			{
				m_pSampleTiles[y * 20 + i].object = OBJ_NULL;
			}
		}
		//jojamart
		m_pSampleTiles[145].object = DOOR;
		m_pSampleTiles[146].object = DOOR;
		m_pSampleTiles[165].object = DOOR;
		m_pSampleTiles[166].object = DOOR;

		//house
		m_pSampleTiles[153].object = DOOR;
		m_pSampleTiles[176].object = DOOR;

		//hospital
		m_pSampleTiles[343].object = DOOR;
		m_pSampleTiles[363].object = DOOR;

		// seedshop
		m_pSampleTiles[370].object = DOOR;
		m_pSampleTiles[371].object = DOOR;
		m_pSampleTiles[390].object = DOOR;
		m_pSampleTiles[391].object = DOOR;
		break;
	case IMGOBJ_2:
		for (int i = 0; i < SAMPLE_TILE_X *SAMPLE_TILE_Y; i++)
		{
			m_pSampleTiles[i].object = NORMALHOUSE;
		}
		m_pSampleTiles[0].object = OBJ_NULL;
		m_pSampleTiles[1].object = OBJ_NULL;
		m_pSampleTiles[6].object = OBJ_NULL;
		m_pSampleTiles[7].object = OBJ_NULL;
		m_pSampleTiles[8].object = OBJ_NULL;
		m_pSampleTiles[11].object = OBJ_NULL;
		m_pSampleTiles[27].object = OBJ_NULL;
		m_pSampleTiles[28].object = OBJ_NULL;
		m_pSampleTiles[31].object = OBJ_NULL;
		m_pSampleTiles[48].object = OBJ_NULL;
		m_pSampleTiles[51].object = OBJ_NULL;
		m_pSampleTiles[70].object = OBJ_NULL;
		m_pSampleTiles[71].object = OBJ_NULL;
		for (int i = 10; i < 20; i++)
		{
			m_pSampleTiles[4*20+i].object = OBJ_NULL;
		}
		for (int y = 5; y < 10; y++)
		{
			for (int x = 10; x < 13; x++)
			{
				m_pSampleTiles[y * 20 + x].object = OBJ_NULL;
			}
		}
		m_pSampleTiles[113].object = OBJ_NULL;
		m_pSampleTiles[133].object = OBJ_NULL;
		m_pSampleTiles[193].object = OBJ_NULL;
		m_pSampleTiles[194].object = OBJ_NULL;
		m_pSampleTiles[195].object = OBJ_NULL;
		for (int i = 0; i < 16; i++)
		{
			m_pSampleTiles[10 * 20 + i].object = OBJ_NULL;
		}

		for (int i = 0; i < 9; i++)
		{
			m_pSampleTiles[11 * 20 + i].object = OBJ_NULL;
		}
		m_pSampleTiles[233].object = OBJ_NULL;
		m_pSampleTiles[234].object = OBJ_NULL;
		m_pSampleTiles[235].object = OBJ_NULL;
		for (int y = 12; y < 20; y++)
		{
			for (int x = 4; x < 7; x++)
			{
				m_pSampleTiles[y * 20 + x].object = OBJ_NULL;
			}
		}
		m_pSampleTiles[254].object = OBJ_NULL;
		m_pSampleTiles[255].object = OBJ_NULL;
		break;
	case IMGOBJ_3:
		for (int i = 0; i < SAMPLE_TILE_X *SAMPLE_TILE_Y; i++)
		{
			m_pSampleTiles[i].object = NORMALOBJECT;
		}
		m_pSampleTiles[0].object = BUSH_SMALL;
		m_pSampleTiles[1].object = BUSH_SMALL;
		m_pSampleTiles[2].object = BUSH_SMALL;
		m_pSampleTiles[3].object = BUSH_SMALL;
		m_pSampleTiles[4].object = MINE_ROCK;
		m_pSampleTiles[5].object = MINE_ROCK;
		m_pSampleTiles[6].object = ROCK_SMALL;
		m_pSampleTiles[7].object = ROCK_SMALL;
		m_pSampleTiles[8].object = BRANCH_SMALL;
		m_pSampleTiles[9].object = BRANCH_SMALL;
		for (int y = 0; y < 5; y++)
		{
			for (int x = 11; x < 13; x++)
			{
				m_pSampleTiles[y * 20 + x].object = OBJ_NULL;
			}
		}
		m_pSampleTiles[12].object = TREE_SMALL;
		m_pSampleTiles[31].object = TREE_SMALL;
		m_pSampleTiles[32].object = TREE_SMALL;

		for (int y = 0; y < 6; y++)
		{
			for (int x = 13; x < 20; x++)
			{
				m_pSampleTiles[y * 20 + x].object = TREE_BIG;
			}
		}
		m_pSampleTiles[90].object = OBJ_NULL;
		m_pSampleTiles[93].object = OBJ_NULL;
		m_pSampleTiles[95].object = OBJ_NULL;
		m_pSampleTiles[96].object = OBJ_NULL;
		m_pSampleTiles[99].object = OBJ_NULL;
		m_pSampleTiles[102].object = OBJ_NULL;
		m_pSampleTiles[113].object = OBJ_NULL;
		m_pSampleTiles[115].object = OBJ_NULL;
		m_pSampleTiles[116].object = OBJ_NULL;
		m_pSampleTiles[119].object = OBJ_NULL;
		m_pSampleTiles[136].object = OBJ_NULL;
		m_pSampleTiles[139].object = OBJ_NULL;
		m_pSampleTiles[145].object = OBJ_NULL;
		m_pSampleTiles[165].object = OBJ_NULL;

		for (int y = 9; y < 11; y++)
		{
			for (int x = 2; x < 6; x++)
			{
				m_pSampleTiles[y * 20 + x].object = FENCE;
			}
		}
		m_pSampleTiles[222].object = FENCE;
		m_pSampleTiles[242].object = FENCE;

		for (int y = 10; y < 16; y++)
		{
			for (int x = 7; x < 12; x++)
			{
				m_pSampleTiles[y * 20 + x].object = BED;
			}
		}
		for (int y = 10; y < 13; y++)
		{
			for (int x = 9; x < 11; x++)
			{
				m_pSampleTiles[y * 20 + x].object = TV;
			}
		}

		for (int y = 10; y < 17; y++)
		{
			m_pSampleTiles[y * 20 + 12].object = OBJ_NULL;
		}
		m_pSampleTiles[211].object = OBJ_NULL;
		m_pSampleTiles[231].object = OBJ_NULL;
		m_pSampleTiles[251].object = OBJ_NULL;
		for (int y = 13; y < 20; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				m_pSampleTiles[y * 20 + x].object = CROP;
			}
		}

		for (int x = 0; x < 5; x++)
		{
			m_pSampleTiles[17 * 20 + x].object = OBJ_NULL;
		}

		for (int x = 4; x < 7; x++)
		{
			m_pSampleTiles[19 * 20 + x].object = OBJ_NULL;
		}

		for (int y = 17; y < 20; y++)
		{
			m_pSampleTiles[y * 20 + 7].object = OBJ_NULL;
		}
		m_pSampleTiles[300].object = BOX;
		m_pSampleTiles[301].object = BOX;
		m_pSampleTiles[320].object = BOX;
		m_pSampleTiles[321].object = BOX;
		break;
	default:
		break;
	}

}

void mapTool::TerrTypeInit()
{
	// 상호작용가능한 땅
	m_pSampleTiles[0].terrain = EARTH;
	m_pSampleTiles[1].terrain = EARTH;
	m_pSampleTiles[2].terrain = EARTH;
	m_pSampleTiles[3].terrain = EARTH;
	m_pSampleTiles[4].terrain = EARTH;
	m_pSampleTiles[5].terrain = EARTH;

	// 경작지 구분
	for (int y = 6; y < 10; ++y)
	{
		for (int x = 9; x < 17; x++)
		{
			if (x >= 13)
				m_pSampleTiles[y * 20 + x].terrain = WETFARMLAND;

			else
				m_pSampleTiles[y * 20 + x].terrain = FARMLAND;
		}
	}

	//물
	for (int y = 0; y < 4; y++)
	{
		for (int x = 12; x < 15; x++)
		{
			m_pSampleTiles[y * 20 + x].terrain = WETEREARTH;
		}
	}

	// 물
	m_pSampleTiles[11].terrain = WATER;
	m_pSampleTiles[31].terrain = WATER;
	m_pSampleTiles[92].terrain = WATER;

	for (int y = 6; y < 10; y++)
	{
		for (int x = 17; x < 20; x++)
		{
			m_pSampleTiles[y * 20 + x].terrain = WATER;
		}
	}

	//바다
	m_pSampleTiles[140].terrain = SEA;
	m_pSampleTiles[141].terrain = SEA;
	m_pSampleTiles[144].terrain = SEA;
	m_pSampleTiles[146].terrain = SEA;
	m_pSampleTiles[166].terrain = SEA;
}

void mapTool::changeImg()
{
	if (m_isObject)
	{
		if (m_isReverse)
		{
			switch (m_sampleObjChoice)
			{
			case IMGOBJ_1:
				m_sampleObjChoice = IMGOBJ_2;
				m_pObject = IMAGEMANAGER->findImage("town_Shop");
				break;

			case IMGOBJ_2:
				m_sampleObjChoice = IMGOBJ_3;
				m_pObject2 = IMAGEMANAGER->findImage("town_Nomal");
				break;

			case IMGOBJ_3:
				m_sampleObjChoice = IMGOBJ_1;
				m_pObject3 = IMAGEMANAGER->findImage("object3");
				break;
			}
		}
		else
		{
			switch (m_sampleObjChoice)
			{
			case IMGOBJ_1:
				m_sampleObjChoice = IMGOBJ_3;
				m_pObject = IMAGEMANAGER->findImage("town_Shop");
				break;

			case IMGOBJ_2:
				m_sampleObjChoice = IMGOBJ_1;
				m_pObject2 = IMAGEMANAGER->findImage("town_Nomal");
				break;

			case IMGOBJ_3:
				m_sampleObjChoice = IMGOBJ_2;
				m_pObject3 = IMAGEMANAGER->findImage("object3");
				break;
			}
		}
		

		sampleTileinit();
		m_rcSave = RectMakeCenter(0, 0, 0, 0);
		m_rcDragCheck = RectMakeCenter(0, 0, 0, 0);
	}
}

void mapTool::checkObjCollide()
{
	if (m_isClick)
	{
		if (m_isDragSave)
		{
			for (int y = 0; y < TILE_Y; ++y)
			{
				for (int x = 0; x < TILE_X; ++x)
				{
					if (PtInRect(&m_pTiles[y* TILE_X + x].rc, g_ptMouse))
					{
						for (int y2 = 0; y2 < m_selectY; y2++)
						{
							for (int x2 = 0; x2 < m_selectX; x2++)
							{
								if (m_pTiles[(y + y2)* TILE_X + (x + x2)].object != OBJ_NULL)
									m_isCollide = true;
							}
						}
					}
				}
			}
		}
	}
}

void mapTool::sampleTileinit()
{
	if (m_isObject)
	{
		for (int i = 0; i < SAMPLE_TILE_X *SAMPLE_TILE_Y; i++)
		{
			m_pSampleTiles[i].rc = RectMake(m_nImageX + (i % SAMPLE_TILE_X) * TILE_SIZE_SAMPLE, (i / SAMPLE_TILE_X) * TILE_SIZE_SAMPLE, TILE_SIZE_SAMPLE, TILE_SIZE_SAMPLE);
			m_pSampleTiles[i].frameX = i % (m_pTileSet->getWidth() / TILE_SIZE_SAMPLE);
			m_pSampleTiles[i].frameY = i / (m_pTileSet->getWidth() / TILE_SIZE_SAMPLE);
			m_pSampleTiles[i].object = OBJ_NULL;
			m_pSampleTiles[i].terrain = NOMALTILE;
			
			//저장하고싶다....
			m_pSampleTiles[i].isCollide = false;

			switch (m_sampleObjChoice)
			{
			case IMGOBJ_1:
				m_pSampleTiles[i].objectID = OBID_1;
				// 임시파일에 저장한거 불러옴
				m_pSampleTiles[i].isCollide = m_ptempSampleObj1[i].isCollide;
				break;
			case IMGOBJ_2:
				m_pSampleTiles[i].objectID = OBID_2;
				m_pSampleTiles[i].isCollide = m_ptempSampleObj2[i].isCollide;
				break;
			case IMGOBJ_3:
				m_pSampleTiles[i].objectID = OBID_3;
				m_pSampleTiles[i].isCollide = m_ptempSampleObj3[i].isCollide;

				break;
			default:
				break;
			}

			//타일별 속성
			objectTypeInit();
		}
	}
	else
	{	
		for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++)
		{
			m_pSampleTiles[i].rc = RectMake(m_nImageX + (i % SAMPLE_TILE_X) * TILE_SIZE_SAMPLE, (i / SAMPLE_TILE_X) * TILE_SIZE_SAMPLE, TILE_SIZE_SAMPLE, TILE_SIZE_SAMPLE);
			m_pSampleTiles[i].frameX = i % (m_pTileSet->getWidth() / TILE_SIZE_SAMPLE);
			m_pSampleTiles[i].frameY = i / (m_pTileSet->getWidth() / TILE_SIZE_SAMPLE);
			m_pSampleTiles[i].terrain = NOMALTILE;
			m_pSampleTiles[i].isCollide = false;
		}
		TerrTypeInit();
	}
}

void mapTool::reTileinit()
{
	delete[] m_pTiles;
	delete[] m_pMini;
	TILE_X = MAPSIZEX / TILE_SIZE_1;
	TILE_Y = MAPSIZEY / TILE_SIZE_1;
	m_pTiles = new tagTile[TILE_X*TILE_Y];
	m_pMini = new tagTile[TILE_X*TILE_Y];

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
}


void mapTool::saveMap(const char* szfileName)
{
	//char szFilter[] = "MapSave (*.map) | All File(*.*)|*,*||";

	DWORD write;
	HANDLE hFile;
	hFile = CreateFile(szfileName,	// 세이브할 파일 경로 / 파일이름
		GENERIC_WRITE,			// 접근 방식 지정
		0,						// 파일 공유 방식 지정 (0) : 공유 안함
								// FILE_SHARE_DELETE : 삭제 접근 요청시 공유
		NULL,					// 보안 관련 옵션
		CREATE_ALWAYS,			// CREATE_ALWAYS : 새로운 파일 생성, 동일한 이름의 파일이 있으면 덮어쓴다
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

void mapTool::loadMap(const char* szfileName)
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

	ReadFile(hFile, m_pTiles, sizeof(tagTile) *TILE_X *TILE_Y, &read, NULL);

	CloseHandle(hFile);
}