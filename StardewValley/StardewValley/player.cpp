#include "stdafx.h"
#include "player.h"
#include "animation.h"
#include "playerMenu.h"
#include "inven.h"
#include "item.h"
#include "fishing.h"
#include "progressBarHp.h"

#include "mapManager.h"

HRESULT player::init()
{
	addSound(); //@ 사운드모음 
	//m_pPlayer = IMAGEMANAGER->findImage("player_idle");
	m_pTarget = IMAGEMANAGER->findImage("focustile_001");
	m_pSeedTarget = IMAGEMANAGER->findImage("focustile_002");
	m_pNumber = IMAGEMANAGER->findImage("goldnumber");
	m_pHpEnergyUi = IMAGEMANAGER->findImage("hp_EnergyBar");
	EFFECTMANAGER->addEffect("water_drop", "image/Stardew Valley/물뿌바닥이펙트.bmp",640,64,64,64,8,5);
	EFFECTMANAGER->addEffect("water_drop2", "image/Stardew Valley/물뿌윗부분이펙트.bmp",192,64,64,64,5,5);
	EFFECTMANAGER->addEffect("recovery", "image/Stardew Valley/회복이펙트.bmp",448,64,64,64,10,5);
	EFFECTMANAGER->addEffect("need_water", "image/Stardew Valley/물부족.bmp",256,64,64,64,4,5);

	m_pAni = new animation;
	m_playerDir = PLAYER_DOWN;
	m_playerState = PLAYER_PLAY;
	m_playerMotion = MOTION_IDLE;
	m_pMenu = new playerMenu;
	m_pMenu->init();
	m_pMenu->getPlayer(this);
	m_pFishing = new fishing;
	m_pFishing->setPlayer(this);
	m_pFishing->init();

	m_pHpBar = new progressBarHp;
	m_pHpBar->init(WINSIZEX - m_pHpEnergyUi->getWidth() + 8, WINSIZEY - 216, 24, 168);
	m_pEnergyBar = new progressBarHp;
	m_pEnergyBar->init(WINSIZEX - m_pHpEnergyUi->getWidth() + 60, WINSIZEY - 216, 24, 168);

	m_nX = WINSIZEX / 2;
	m_nY = WINSIZEY / 2;
	m_nTargetX = 0;
	m_nTargetY = 0;
	m_nSyncX = 0;
	m_nSyncY = 0;
	m_fRange = 60.0f;
	m_nPlayerSizeX = 64;
	m_nPlayerSizeY = 64;
	m_nMoveSpeed = 10;
	m_nMoney = 54321;

	m_fCurrHp = m_fMaxHp = 100;			// @플레이어 체력
	m_fCurrEnergy = m_fMaxEnergy = 270;		// @플레이어 에너지 
	m_HpRc = RectMake(WINSIZEX - m_pHpEnergyUi->getWidth()+12, WINSIZEY -208, 24, 164);  //@플레이어 체력
	m_EnergyRc = RectMake(WINSIZEX - m_pHpEnergyUi->getWidth() + 64, WINSIZEY - 208, 24, 164); // @플레이어 에너지
	

	
	m_rc = RectMake(m_nX, m_nY + 32, m_nPlayerSizeX, m_nPlayerSizeY);
	m_TargetRc = RectMake(m_nX, m_nY + 32, m_nPlayerSizeX * 3, m_nPlayerSizeY * 3);
	isMove = false;
	isStop = true;
	isSeed = false;
	isProgressBar[0] = false;
	isProgressBar[1] = false;

	setMotion(m_pAni, &m_pPlayer, "player_idle", 5, 5);
	startMotion(m_pAni, 0, 1, false, false, 5);

	m_playerCollision = COLL_FALSE;

	m_nTempIndex = 0;

	return S_OK;
}

void player::release()
{
	delete m_pAni;
	m_pMenu->release();
	delete m_pMenu;
	m_pFishing->release();
	delete m_pFishing;
}

void player::update()
{	
	
	m_pTargetItem = m_pMenu->getQuickItem();	// 퀵바 아이템 정보 받아옴
	m_pAni->frameUpdate(TIMEMANAGER->getElapsedTime());	// 에니매이션용
	
	if (m_pMenu->getMenu() == false && m_playerState == PLAYER_MENU)
	{
		// 메뉴클래스에서 false되면 플레이 상태로 전환
		m_playerState = PLAYER_PLAY;
	}
	// 플레이상태와 플레이어 모션이 idle, handup상태일떄 다음 함수 실행
	if (m_playerState == PLAYER_PLAY && (m_playerMotion == MOTION_IDLE || m_playerMotion == MOTION_HANDUP))
	{
		setKey();	// 키입력함수 wasd이동키
		useItem();	// 소모품 아이템 사용
	}
	// 플레이어 상태가 메뉴면 메뉴 true로
	if (m_playerState == PLAYER_MENU)
	{
		m_pMenu->setMenu(true);
	}
	   
	// 플레이어 렉트 셋팅
	m_rc = RectMake(m_nX + 8 - CAMERA->getX(), m_nY + 63 - CAMERA->getY(), m_nPlayerSizeX, m_nPlayerSizeY);
	// 바닥에 빨간색네모 타겟 렉트
	m_TargetRc = RectMake(m_nX + 8 - CAMERA->getX() - (m_nPlayerSizeX / 2), m_nY + 63 - CAMERA->getY() - (m_nPlayerSizeY / 2), m_nPlayerSizeX* 2, m_nPlayerSizeY * 2);
	// 메뉴클래스 업데이트
	m_pMenu->update();
	// 타일의 xy받아오는 함수
	setTargetXY();

	// 퀵바 아이템이 있을떄
	if (m_pTargetItem)
	{
		m_pTargetItem->setPlayXY(m_nX, m_nY);	// 도구아이템이 아닐때 플레이어 x,y받아오는 함수
		// L버튼 가능을하기위해 낚시상태가 아닐떄, 인벤클래스의 L버튼불값이 false일떄
		if (m_playerState != PLAYER_FISHING && m_pMenu->getInven()->getLbutton() == false)
		{
			setItemMotion();
		}						// 도구아이템 모션 상태
		setSyncMotion(m_playerMotion, &m_nSyncX, &m_nSyncY);	// 모션 랜더 x,y보정값
		// 플레이어가 플레이(필드)상태일떄 도구아이템 제외 아이템 그려줄지 여부(만세자세)
		if (m_playerState == PLAYER_PLAY)
		{
			m_pTargetItem->setPlayerPlaying(true);
		}
		else
		{
			m_pTargetItem->setPlayerPlaying(false);
		}
	}
	// 체력,에너지바 
	progressBarToolTip();

	//낚시
	m_pFishing->setPlayer(this);
	m_pFishing->update();
	

}

void player::render(HDC hdc)
{
	if (m_pTargetItem && m_pTargetItem->getActItemKind()==ACTITEM_WATER)
	{
		EFFECTMANAGER->render(hdc);
	}
	m_pHpEnergyUi->render(hdc, WINSIZEX-m_pHpEnergyUi->getWidth(),WINSIZEY-260); // @체력,에너지틀
	m_pHpBar->render(hdc);
	m_pEnergyBar->render(hdc);

	// 플레이어 랜더
	if (m_pFishing->getIsFishing() == false)
	{
		m_pPlayer->aniRender(hdc, m_nX - CAMERA->getX() - m_nSyncX, m_nY - CAMERA->getY() - m_nSyncY, m_pAni);
	}
	if (m_pTargetItem && m_pTargetItem->getActItemKind() != ACTITEM_WATER)
	{
		EFFECTMANAGER->render(hdc);
	}
    
	// 퀵바 아이템이 있을때
	if (m_pTargetItem)
	{
		if (m_playerState == PLAYER_PLAY)
		{
			if (isStop)
			{
				// 도구가 도끼,괭이,물뿌리개,곡괭이 일떄만 타겟이 보임
				if (m_pTargetItem->getActItemKind() == ACTITEM_AXE ||
					m_pTargetItem->getActItemKind() == ACTITEM_SPADE ||
					m_pTargetItem->getActItemKind() == ACTITEM_WATER ||
					m_pTargetItem->getActItemKind() == ACTITEM_PICKAX)
				{
					m_pTarget->render(hdc, m_nTargetX, m_nTargetY, TARGET_SIZE);
				}
			}
			// 아이템이 씨앗일때
			if (m_pTargetItem->getItemKind() == ITEM_SEED)
			{
				m_pSeedTarget->alphaFrameRender(hdc, m_nTargetX, m_nTargetY, isSeed, 0, 150, GAME_SCALAR);
			}
		}
	}


	//MakeRect(hdc, m_temprc);
	//MakeRect(hdc, m_rc);
	//MakeRect(hdc, m_TargetRc);

	m_pMenu->render(hdc);

	if (m_pTargetItem)
	{
		char str[128];
		sprintf_s(str, 128, "%d", m_pTargetItem->getItemId());
		TextOut(hdc, 200, 700, str, strlen(str));
	}
	m_pFishing->render(hdc);

	char str[128];
	sprintf_s(str, 128, "씨앗불값 : %d", isSeed);
	TextOut(hdc, 0, 550, str, strlen(str));
	if (isProgressBar[1] == true)
	{
		sprintf_s(str, 128, "%d / %d", m_fCurrEnergy, m_fMaxEnergy);
		TextOut(hdc, WINSIZEX - m_pHpEnergyUi->getWidth() - 100, WINSIZEY - 196, str, strlen(str));
	}
	if (isProgressBar[0] == true)
	{
		sprintf_s(str, 128, "%d / %d", m_fCurrHp, m_fMaxHp);
		TextOut(hdc, WINSIZEX - m_pHpEnergyUi->getWidth() - 100, WINSIZEY - 196, str, strlen(str));
	}
}

void player::numRender(HDC hdc, int x, int y)
{
	int num = 0;
	int digit = log10((double)m_nMoney);
	int digit2 = 10;
	int tempMoney = m_nMoney;

	for (int i = 0; i < digit - 1; i++)
	{
		digit2 = digit2 * 10;
	}

	for (int i = 0; i < digit + 1; i++)
	{
		if (i == digit)
		num = tempMoney % digit2;
		else
		num = tempMoney / digit2;
		tempMoney = tempMoney - num * digit2;
		if (digit2 != 10)
			digit2 = digit2 / 10;
		m_pNumber->frameRender(hdc, x + i * 24, y, num, 0);
	}
}

player::player()
{
}


player::~player()
{
}

// 타겟렉트 좌표
// 맵정보 받아와야함
void player::setTargetXY()
{
	for (int y = 0; y < WINSIZEY / m_pMap->getTileSize() + 1; y++)
	{
		for (int x = 0; x < WINSIZEX / m_pMap->getTileSize() + 1; x++)
		{
			int cullX = CAMERA->getX() / m_pMap->getTileSize();
			int cullY = CAMERA->getY() / m_pMap->getTileSize();

			int m_indexCamera;
			m_indexCamera = (y + cullY)*m_pMap->getTileX() + (x + cullX);
			if (m_indexCamera >= (m_pMap->getTileX() * m_pMap->getTileY())) continue;

			if (IntersectRect(&m_temprc, &m_pMap->getTile(m_indexCamera)->rc, &m_TargetRc))
			{
				if (isStop == true)
				{
					if (PtInRect(&m_pMap->getTile(m_indexCamera)->rc, g_ptMouse))
					{
						if (m_pMap->getTile(m_indexCamera)->terrain == FARMLAND || 
							m_pMap->getTile(m_indexCamera)->terrain == WETFARMLAND)
						{
							isSeed = true;
						}
						else
						{
							isSeed = false;
						}

						m_nTargetX = m_pMap->getTile(m_indexCamera)->rc.left;
						m_nTargetY = m_pMap->getTile(m_indexCamera)->rc.top;
						m_nTempIndex = m_indexCamera;
					}
				}
				else
				{
					m_nTargetX = m_pMap->getTile(m_indexCamera)->rc.left;
					m_nTargetY = m_pMap->getTile(m_indexCamera)->rc.top;
					break;
				}
			}
		}
	}
}

// 키 세팅
void player::setKey()
{

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		
		if (SOUNDMANAGER->isPlaying("sound/effect/startbutton.wav") == false)
			SOUNDMANAGER->play("sound/effect/startbutton.wav", g_soundVolume.effect);
		if (isMove == false)
		{
			
			switch (m_playerMotion)
			{
			case MOTION_IDLE:
				startMotion(m_pAni, 20, 25, false, true, 8);
				break;
			case MOTION_HANDUP:
				startMotion(m_pAni, 15, 20, false, true, 8);
				break;
			}

			isMove = true;
		}
		m_playerDir = PLAYER_LEFT;
		isStop = false;
		move(m_playerDir);
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		isMove = false;
		isStop = true;
		m_pAni->stop();
		switch (m_playerMotion)
		{
		case MOTION_IDLE:
			m_pAni->setPlayFrame(3, 4, false, false);
			break;
		case MOTION_HANDUP:
			m_pAni->setPlayFrame(17, 18, false, false);
			break;
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (SOUNDMANAGER->isPlaying("sound/effect/startbutton.wav") == false)
			SOUNDMANAGER->play("sound/effect/startbutton.wav", g_soundVolume.effect);
		if (isMove == false)
		{
			switch (m_playerMotion)
			{
			case MOTION_IDLE:
				startMotion(m_pAni, 15, 20, false, true, 8);
				break;
			case MOTION_HANDUP:
				startMotion(m_pAni, 10, 15, false, true, 8);
				break;
			}
			isMove = true;
		}
		isStop = false;
		m_playerDir = PLAYER_RIGHT;
		move(m_playerDir);
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		isMove = false;
		isStop = true;
		m_pAni->stop();
		switch (m_playerMotion)
		{
		case MOTION_IDLE:
			m_pAni->setPlayFrame(1, 2, false, false);
			break;
		case MOTION_HANDUP:
			m_pAni->setPlayFrame(12, 13, false, false);
			break;
		}
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if(SOUNDMANAGER->isPlaying("sound/effect/startbutton.wav") ==false)
		SOUNDMANAGER->play("sound/effect/startbutton.wav", g_soundVolume.effect);
		if (isMove == false)
		{
			
			switch (m_playerMotion)
			{
			case MOTION_IDLE:
				startMotion(m_pAni, 10, 15, false, true, 5);
				break;
			case MOTION_HANDUP:
				startMotion(m_pAni, 5, 10, false, true, 8);
				break;
			}
			isMove = true;
		}
		isStop = false;
		m_playerDir = PLAYER_UP;
		move(m_playerDir);
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		isMove = false;
		isStop = true;
		m_pAni->stop();
		switch (m_playerMotion)
		{
		case MOTION_IDLE:
			m_pAni->setPlayFrame(2, 3, false, false);
			break;
		case MOTION_HANDUP:
			m_pAni->setPlayFrame(7, 8, false, false);
			break;
		}
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (SOUNDMANAGER->isPlaying("sound/effect/startbutton.wav") == false)
			SOUNDMANAGER->play("sound/effect/startbutton.wav", g_soundVolume.effect);
		if (isMove == false)
		{
			if (isMove == false)
			{
				switch (m_playerMotion)
				{
				case MOTION_IDLE:
					startMotion(m_pAni, 5, 10, false, true, 5);
					break;
				case MOTION_HANDUP:
					startMotion(m_pAni, 0, 5, false, true, 8);
					break;
				}
				isMove = true;
			}
			isMove = true;
		}
		isStop = false;
		m_playerDir = PLAYER_DOWN;
		move(m_playerDir);
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		isMove = false;
		isStop = true;
		m_pAni->stop();
		switch (m_playerMotion)
		{
		case MOTION_IDLE:
			m_pAni->setPlayFrame(0, 1, false, false);
			break;
		case MOTION_HANDUP:
			m_pAni->setPlayFrame(2, 3, false, false);
			break;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		SOUNDMANAGER->play("sound/effect/인벤토리.wav", g_soundVolume.effect);
		m_playerState = PLAYER_MENU;
		m_pMenu->setMenuDir(MENU_INVEN);
	
	}
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		SOUNDMANAGER->play("sound/effect/인벤토리.wav", g_soundVolume.effect);
		m_playerState = PLAYER_MENU;
		m_pMenu->setMenuDir(MENU_SHOP);
	}
}

// 이동함수 (수정해야함)
void player::move(PLAYERDIR playerdir)
{
	/*switch (playerdir)
	{
	case PLAYER_LEFT:
		m_nX -= m_nMoveSpeed;
		break;
	case PLAYER_RIGHT:
		m_nX += m_nMoveSpeed;
		break;
	case PLAYER_UP:
		m_nY -= m_nMoveSpeed;
		break;
	case PLAYER_DOWN:
		m_nY += m_nMoveSpeed;
		break;
	}*/



	// 맵정보 받아와야함
	for (int y = 0; y < WINSIZEY / m_pMap->getTileSize() + 1; y++)
	{
		for (int x = 0; x < WINSIZEX / m_pMap->getTileSize() + 1; x++)
		{
			int cullX = CAMERA->getX() / m_pMap->getTileSize();
			int cullY = CAMERA->getY() / m_pMap->getTileSize();

			int m_indexCamera;
			m_indexCamera = (y + cullY)*m_pMap->getTileX() + (x + cullX);
			
			if (m_indexCamera >= (m_pMap->getTileX() * m_pMap->getTileY())) continue;

			//충돌x
			if (!(m_pMap->getTile(m_indexCamera)->isCollide) && IntersectRect(&m_temprc, &m_pMap->getTile(m_indexCamera)->rc, &m_rc))
			{
				m_isMove = true;
			}

			//충돌시
			else
			{
				if ((m_pMap->getTile(m_indexCamera)->isCollide) && IntersectRect(&m_temprc, &m_pMap->getTile(m_indexCamera)->rc, &m_rc))
				{
					m_isMove = false;

					switch (playerdir)
					{
					case PLAYER_LEFT:
						m_playerCollision = COLL_LEFT;
						break;
					case PLAYER_RIGHT:
						m_playerCollision = COLL_RIGHT;
						break;
					case PLAYER_UP:
						m_playerCollision = COLL_UP;
						break;
					case PLAYER_DOWN:
						m_playerCollision = COLL_DOWN;
						break;
					}
					//m_playerCollision = COLL_LEFT;
				}
			}
		}
	}

	// 충돌x
	if (m_isMove)
	{
		switch (playerdir)
		{
		case PLAYER_LEFT:
			m_nX -= m_nMoveSpeed;
			break;
		case PLAYER_RIGHT:
			m_nX += m_nMoveSpeed;
			break;
		case PLAYER_UP:
			m_nY -= m_nMoveSpeed;
			break;
		case PLAYER_DOWN:
			m_nY += m_nMoveSpeed;
			break;
		}
	}

	// 충돌o
	else
	{
		switch (playerdir)
		{
		case PLAYER_LEFT:
			//m_nX -= m_nMoveSpeed;
			break;
		case PLAYER_RIGHT:
			//m_nX += m_nMoveSpeed;
			break;
		case PLAYER_UP:
			//m_nY -= m_nMoveSpeed;
			break;
		case PLAYER_DOWN:
			//m_nY += m_nMoveSpeed;
			break;
		}
	}
}

// 모션에따라서 이미지교체 + 애니메이션 셋팅해줌
void player::setMotion(animation * ani, image** image, const char * szName, int framex, int framey)
{
	*image = IMAGEMANAGER->findImage(szName);
	ani->init((*image)->getWidth(), (*image)->getHeight(), (*image)->getWidth() / framex, (*image)->getHeight() / framey);
}

// 셋팅된 애니메이션 그려줄 프레임 셋팅 + 애니메이션 시작함수
void player::startMotion(animation * ani, int start, int end, bool reverse, bool loop, int fps)
{
	ani->setPlayFrame(start, end, reverse, loop);
	ani->start();
	ani->setFPS(5);
}

// 플레이어 모션 보정
void player::setSyncMotion(PLAYERMOTION motion, int * x, int * y)
{
	switch (motion)
	{
	case MOTION_IDLE:
		*x = 0;
		*y = 0;
		break;
	case MOTION_AXE:
		*x = 35;
		*y = 80;
		break;
	case MOTION_SPADE:
		*x = 35;
		*y = 80;
		break;
	case MOTION_WATER:
		*x = 35;
		*y = 80;
		break;
	case MOTION_PICKAX:
		*x = 35;
		*y = 80;
		break;
	case MOTION_NOT:
		switch (m_playerDir)
		{
		case PLAYER_LEFT:
			*x = 45;
			*y = 0;
			break;
		case PLAYER_RIGHT:
			*x = 35;
			*y = 0;
			break;
		case PLAYER_UP:
			*x = 35;
			*y = 80;
			break;
		case PLAYER_DOWN:
			*x = 45;
			*y = 0;
			break;
		}
		break;
	case MOTION_FISHINGROD:
		switch (m_playerDir)
		{
		case PLAYER_LEFT:
			*x = 50;
			*y = 20;
			break;
		case PLAYER_RIGHT:
			*x = 50;
			*y = 20;
			break;
		case PLAYER_UP:
			*x = 50;
			*y = 20;
			break;
		case PLAYER_DOWN:
			*x = 50;
			*y = 20;
			break;
		}
		break;
	case MOTION_SWORD:
		*x = 50;
		*y = 20;
		break;
	case MOTION_HANDUP:
		*x = 50;
		*y = 30;
		break;

	}
}

// 퀵바에 선택된 도구의 종류에따라서 모션셋팅
void player::setItemMotion()
{
	if (m_playerState == PLAYER_PLAY)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && m_playerMotion == MOTION_IDLE)
		{
			setDir();	// 플레이어 방향 정하는 함수
			if (m_pTargetItem->getActItemKind() != ACTITEM_NULL)
			{
				switch (m_pTargetItem->getActItemKind())
				{
				case ACTITEM_AXE:
					m_playerMotion = MOTION_AXE;
					setMotion(m_pAni, &m_pPlayer, "player_axe", 4, 4);
					switch (m_playerDir)
					{
					case PLAYER_LEFT:
						startMotion(m_pAni, 4, 8, false, false, 5);
						break;
					case PLAYER_RIGHT:
						startMotion(m_pAni, 8, 12, false, false, 5);
						break;
					case PLAYER_UP:
						startMotion(m_pAni, 12, 16, false, false, 5);
						break;
					case PLAYER_DOWN:
						startMotion(m_pAni, 0, 4, false, false, 5);
						break;
					}
					setAxeTile();	// 상호작용 함수
					break;
				case ACTITEM_SPADE:
					m_playerMotion = MOTION_SPADE;
					setMotion(m_pAni, &m_pPlayer, "player_spade", 4, 4);
					
					switch (m_playerDir)
					{
					case PLAYER_LEFT:
						startMotion(m_pAni, 4, 8, false, false, 5);
						break;
					case PLAYER_RIGHT:
						startMotion(m_pAni, 8, 12, false, false, 5);
						break;
					case PLAYER_UP:
						startMotion(m_pAni, 12, 16, false, false, 5);
						break;
					case PLAYER_DOWN:
						startMotion(m_pAni, 0, 4, false, false, 5);
						break;
					}
					setSpadeTile();	// 상호작용 함수
					break;
				case ACTITEM_WATER:
					m_playerMotion = MOTION_WATER;
					
					setMotion(m_pAni, &m_pPlayer, "player_water", 2, 4);
					
					switch (m_playerDir)
					{
					case PLAYER_LEFT:
						startMotion(m_pAni, 2, 4, false, false, 5);
						break;
					case PLAYER_RIGHT:
						startMotion(m_pAni, 4, 6, false, false, 5);
						break;
					case PLAYER_UP:
						startMotion(m_pAni, 6, 8, false, false, 5);						
						break;
					case PLAYER_DOWN:
						startMotion(m_pAni, 0, 2, false, false, 5);
						break;
					}
					setWaterTile();	// 상호작용 함수
					break;
				case ACTITEM_PICKAX:
					m_playerMotion = MOTION_PICKAX;
					setMotion(m_pAni, &m_pPlayer, "player_mine", 3, 4);
					switch (m_playerDir)
					{
					case PLAYER_LEFT:
						startMotion(m_pAni, 3, 6, false, false, 5);
						break;
					case PLAYER_RIGHT:
						startMotion(m_pAni, 6, 9, false, false, 5);
						break;
					case PLAYER_UP:
						startMotion(m_pAni, 9, 12, false, false, 5);
						break;
					case PLAYER_DOWN:
						startMotion(m_pAni, 0, 3, false, false, 5);
						break;
					}
					setPickaxTile(); // 상호작용 함수
					break;
				case ACTITEM_NOT:
					m_playerMotion = MOTION_NOT;
					setMotion(m_pAni, &m_pPlayer, "player_not", 3, 4);
					switch (m_playerDir)
					{
					case PLAYER_LEFT:
						startMotion(m_pAni, 3, 6, false, false, 5);
						break;
					case PLAYER_RIGHT:
						startMotion(m_pAni, 6, 9, false, false, 5);
						break;
					case PLAYER_UP:
						startMotion(m_pAni, 9, 12, false, false, 5);
						break;
					case PLAYER_DOWN:
						startMotion(m_pAni, 0, 3, false, false, 5);
						break;
					}
					setNotTile();	// 상호작용 함수
					break;
				case ACTITEM_FISHINGROD:
					m_pFishing->init();
					m_pFishing->setIsFishing(true);
					m_playerState = PLAYER_FISHING;		
					m_fCurrEnergy -= 8;
					break;
				case ACTITEM_SWORD:
					m_playerMotion = MOTION_SWORD;
					setMotion(m_pAni, &m_pPlayer, "player_sword", 3, 4);
					switch (m_playerDir)
					{
					case PLAYER_LEFT:
						startMotion(m_pAni, 3, 6, false, false, 5);
						break;
					case PLAYER_RIGHT:
						startMotion(m_pAni, 6, 9, false, false, 5);
						break;
					case PLAYER_UP:
						startMotion(m_pAni, 9, 12, false, false, 5);
						break;
					case PLAYER_DOWN:
						startMotion(m_pAni, 0, 3, false, false, 5);
						break;
					}
					setSwordTile();	// 상호작용 함수
					break;
				}
			}
		}

		if (m_pTargetItem->getItemOn() == true && m_pTargetItem->getActItemKind() == ACTITEM_NULL && m_pAni->getIsPlaying() == false)
		{
			m_playerMotion = MOTION_HANDUP;
			setMotion(m_pAni, &m_pPlayer, "player_handup", 5, 4);
			switch (m_playerDir)
			{
			case PLAYER_LEFT:
				startMotion(m_pAni, 17, 18, false, false, 5);
				break;
			case PLAYER_RIGHT:
				startMotion(m_pAni, 12, 13, false, false, 5);
				break;
			case PLAYER_UP:
				startMotion(m_pAni, 7, 8, false, false, 5);
				break;
			case PLAYER_DOWN:
				startMotion(m_pAni, 2, 3, false, false, 5);
				break;
			}
		}
		if ((m_pTargetItem->getActItemKind() != ACTITEM_NULL && m_pAni->getIsPlaying() == false))
		{
			m_playerMotion = MOTION_IDLE;
			setMotion(m_pAni, &m_pPlayer, "player_idle", 5, 5);
			switch (m_playerDir)
			{
			case PLAYER_LEFT:
				startMotion(m_pAni, 3, 4, false, false, 5);
				break;
			case PLAYER_RIGHT:
				startMotion(m_pAni, 1, 2, false, false, 5);
				break;
			case PLAYER_UP:
				startMotion(m_pAni, 2, 3, false, false, 5);
				break;
			case PLAYER_DOWN:
				startMotion(m_pAni, 0, 1, false, false, 5);
				break;
			}
		}
		if ((m_pTargetItem->getItemOn() == false && m_pAni->getIsPlaying() == false))
		{
			m_playerMotion = MOTION_IDLE;
			setMotion(m_pAni, &m_pPlayer, "player_idle", 5, 5);
			switch (m_playerDir)
			{
			case PLAYER_LEFT:
				startMotion(m_pAni, 3, 4, false, false, 5);
				break;
			case PLAYER_RIGHT:
				startMotion(m_pAni, 1, 2, false, false, 5);
				break;
			case PLAYER_UP:
				startMotion(m_pAni, 2, 3, false, false, 5);
				break;
			case PLAYER_DOWN:
				startMotion(m_pAni, 0, 1, false, false, 5);
				break;
			}
		}
	}
}

// 아이템사용 함수
void player::useItem()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (m_pTargetItem->getItemOn() == true &&				// 퀵바 아이템이 있는지
			(m_pTargetItem->getItemKind() == ITEM_SEED ||		// 퀵바 아이템이 씨앗이나 소모품인지
				m_pTargetItem->getItemKind() == ITEM_CONSUME))
		{
			switch (m_pTargetItem->getConsumItemKind())
			{
			case CONITEM_RECOVERY:
				EFFECTMANAGER->play("recovery", (m_nX +5) - CAMERA->getX(), m_nY- CAMERA->getY());
				SOUNDMANAGER->play("sound/effect/아삭소리2.wav", g_soundVolume.effect);
				m_nHp += m_pTargetItem->getHp();
				m_fCurrHp += m_pTargetItem->getHp();
				if (m_fCurrHp >= m_fMaxHp)
					m_fCurrHp = m_fMaxHp;
				m_fCurrEnergy += m_pTargetItem->getEnergy();
				if (m_fCurrEnergy >= m_fMaxEnergy)
					m_fCurrEnergy = m_fMaxEnergy;
				m_pTargetItem->useItem();
			case CONITEM_SEED:
				break;
			}
		}
	}
}

// 도구사용시 방향 잡는 함수
void player::setDir()
{

	if (g_ptMouse.x > m_nX + 8 - CAMERA->getX() + m_nPlayerSizeX && 
		g_ptMouse.y > m_nY + 63 - CAMERA->getY() && 
		g_ptMouse.y < m_nY + 63 - CAMERA->getY() + m_nPlayerSizeY)
	{
		m_playerDir = PLAYER_RIGHT;
	}
	else if (g_ptMouse.x < m_nX + 8 - CAMERA->getX() &&
		g_ptMouse.y > m_nY + 63 - CAMERA->getY() &&
		g_ptMouse.y < m_nY + 63 - CAMERA->getY() + m_nPlayerSizeY)
	{
		m_playerDir = PLAYER_LEFT;
	}
	else if (g_ptMouse.y > m_nY + 63 - CAMERA->getY())
	{
		m_playerDir = PLAYER_DOWN;
	}

	else if (g_ptMouse.y <= m_nY + 63 - CAMERA->getY())
	{
		m_playerDir = PLAYER_UP;
	}
}

void player::setSpadeTile()
{
	SOUNDMANAGER->play("sound/effect/playerAct/밭갈다.wav", g_soundVolume.effect);
	if (m_pMap->getTile(m_nTempIndex)->object == BUSH_SMALL)
	{
		m_pMap->getTile(m_nTempIndex)->object = OBJ_NULL;
		// 특정확률로 풀 아이템 획득
		//if(RANDOM->getFromIntTo(0,1) > 0)
		//m_pMenu->getInven()->addItem(201);
	}
	if (m_pMap->getTile(m_nTempIndex)->terrain == EARTH)
	{ 
		m_pMap->getTile(m_nTempIndex)->terrainFrameX = 9;
		m_pMap->getTile(m_nTempIndex)->terrainFrameY = 6;
		m_pMap->getTile(m_nTempIndex)->terrain = FARMLAND;
	}
	m_fCurrEnergy -= 2;
	m_pEnergyBar->setGauge(m_fCurrEnergy, m_fMaxEnergy);
}

void player::setWaterTile()
{
	if (m_pTargetItem->getWaterDurability() > 0)
	{
		EFFECTMANAGER->play("water_drop2", (m_nTargetX), (m_nTargetY)-30);
		EFFECTMANAGER->play("water_drop", (m_nTargetX), (m_nTargetY));
		SOUNDMANAGER->play("sound/effect/playerAct/물뿌리개2.wav", g_soundVolume.effect);
		m_pTargetItem->setWaterDurability(m_pTargetItem->getWaterDurability() - 1);
		if (m_pMap->getTile(m_nTempIndex)->terrain == FARMLAND)
		{
			SOUNDMANAGER->play("sound/effect/playerAct/물뿌리개2.wav", g_soundVolume.effect);
			m_pMap->getTile(m_nTempIndex)->terrainFrameX = 13;
			m_pMap->getTile(m_nTempIndex)->terrainFrameY = 6;
			m_pMap->getTile(m_nTempIndex)->terrain = WETFARMLAND;
		}
		m_pTargetItem->progressWaterDurability(1);
		m_fCurrEnergy -= 2;
	}
}

void player::setAxeTile()
{
	SOUNDMANAGER->play("sound/effect/playerAct/맨땅에.wav", g_soundVolume.effect);
	if (m_pMap->getTile(m_nTempIndex)->object == BUSH_SMALL)
	{
		m_pMap->getTile(m_nTempIndex)->object = OBJ_NULL;
		// 특정확률로 풀 아이템 획득
		//if(RANDOM->getFromIntTo(0,1) > 0)
		//m_pMenu->getInven()->addItem(201);
	}
	if (m_pMap->getTile(m_nTempIndex)->object == TREE_BIG)
	{
		// 특정확률로 나무 수액 아이템 획득
		//if(RANDOM->getFromIntTo(0,1) > 0)
		//m_pMenu->getInven()->addItem(203);
		//if(RANDOM->getFromIntTo(0,1) > 0)
		//m_pMenu->getInven()->addItem(204);
	}
	m_fCurrEnergy -= 2;
}

void player::setPickaxTile()
{
	SOUNDMANAGER->play("sound/effect/playerAct/맨땅에.wav", g_soundVolume.effect);
	if (m_pMap->getTile(m_nTempIndex)->object == BUSH_SMALL)
	{
		m_pMap->getTile(m_nTempIndex)->object = OBJ_NULL;
		// 특정확률로 풀 아이템 획득
		//if(RANDOM->getFromIntTo(0,1) > 0)
		//m_pMenu->getInven()->addItem(201);
	}
	if (m_pMap->getTile(m_nTempIndex)->object == MINE_ROCK)
	{
		m_pMap->getTile(m_nTempIndex)->object = OBJ_NULL;
		// 특정확률로 광석 아이템 획득
		//if(RANDOM->getFromIntTo(0,1) > 0)
		//m_pMenu->getInven()->addItem(202);
	}
	m_fCurrEnergy -= 2;
}

void player::setNotTile()
{
	SOUNDMANAGER->play("sound/effect/playerAct/낫질.wav", g_soundVolume.effect);
	if (m_pMap->getTile(m_nTempIndex)->object == BUSH_SMALL)
	{
		m_pMap->getTile(m_nTempIndex)->object = OBJ_NULL;
		// 특정확률로 풀 아이템 획득
		//if(RANDOM->getFromIntTo(0,1) > 0)
		//m_pMenu->getInven()->addItem(201);
	}
}

void player::setSwordTile()
{
	SOUNDMANAGER->play("sound/effect/playerAct/낫질.wav", g_soundVolume.effect);
	if (m_pMap->getTile(m_nTempIndex)->object == BUSH_SMALL)
	{
		m_pMap->getTile(m_nTempIndex)->object = OBJ_NULL;
		// 특정확률로 풀 아이템 획득
		//if(RANDOM->getFromIntTo(0,1) > 0)
		//m_pMenu->getInven()->addItem(201);
	}
}

void player::progressBarToolTip()
{
	if (PtInRect(&m_HpRc, g_ptMouse))
	{
		isProgressBar[0] = true;
	}
	else
	{
		isProgressBar[0] = false;
	}
	if (PtInRect(&m_EnergyRc, g_ptMouse))
	{
		isProgressBar[1] = true;
	}
	else
	{
		isProgressBar[1] = false;
	}
	else
	{
		EFFECTMANAGER->play("need_water",(m_nX+10)- CAMERA->getX(),(m_nY-80)- CAMERA->getY());
		SOUNDMANAGER->play("sound/effect/playerAct/물뿌리개물없을때.wav", g_soundVolume.effect);
	}
}

void player::addSound()
{
	//플레이어 액션
	SOUNDMANAGER->addSound("sound/effect/playerAct/곡소리.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/playerAct/낫질.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/playerAct/맨땅에.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/playerAct/도끼질.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/playerAct/물뿌리개2.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/playerAct/밭갈다.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/playerAct/물뿌리개물없을때.wav", false, false);
}
