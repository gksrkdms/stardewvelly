#include "stdafx.h"
#include "player.h"
#include "animation.h"
#include "playerMenu.h"
#include "inven.h"
#include "item.h"
#include "fishing.h"

#include "mapManager.h"

HRESULT player::init()
{
	//m_pPlayer = IMAGEMANAGER->findImage("player_idle");
	m_pTarget = IMAGEMANAGER->findImage("focustile_001");
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

	m_nX = WINSIZEX / 2;
	m_nY = WINSIZEY / 2;
	m_nTargetX = 0;
	m_nTargetY = 0;
	m_nSyncX = 0;
	m_nSyncY = 0;
	m_fRange = 60.0f;
	m_nPlayerSizeX = 32;
	m_nPlayerSizeY = 32;
	m_nMoveSpeed = 10;
	m_nMoney = 50000;

	m_rc = RectMake(m_nX, m_nY + 32, m_nPlayerSizeX, m_nPlayerSizeY);
	m_TargetRc = RectMake(m_nX, m_nY + 32, m_nPlayerSizeX * 3, m_nPlayerSizeY * 3);
	isMove = false;
	isTargetRc = true;

	setMotion(m_pAni, &m_pPlayer, "player_idle", 5, 5);
	startMotion(m_pAni, 0, 1, false, false, 5);

	m_playerCollision = COLL_FALSE;


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
	m_pTargetItem = m_pMenu->getQuickItem();	// ���� ������ ���� �޾ƿ�
	m_pAni->frameUpdate(TIMEMANAGER->getElapsedTime());	// ���ϸ��̼ǿ�

	if (m_pMenu->getMenu() == false && m_playerState == PLAYER_MENU)
	{
		// �޴�Ŭ�������� false�Ǹ� �÷��� ���·� ��ȯ
		m_playerState = PLAYER_PLAY;
	}
	// �÷��̻��¿� �÷��̾� ����� idle, handup�����ϋ� ���� �Լ� ����
	if (m_playerState == PLAYER_PLAY && (m_playerMotion == MOTION_IDLE || m_playerMotion == MOTION_HANDUP))
	{
		setKey();	// Ű�Է��Լ� wasd�̵�Ű
		useItem();	// �Ҹ�ǰ ������ ���
	}
	// �÷��̾� ���°� �޴��� �޴� true��
	if (m_playerState == PLAYER_MENU)
	{
		m_pMenu->setMenu(true);
	}
	   
	// �÷��̾� ��Ʈ ����
	m_rc = RectMake(m_nX + 26 - CAMERA->getX(), m_nY + 85 - CAMERA->getY(), m_nPlayerSizeX, m_nPlayerSizeY);
	// �ٴڿ� �������׸� Ÿ�� ��Ʈ
	m_TargetRc = RectMake(m_nX + 26 - CAMERA->getX() - (m_nPlayerSizeX / 2), m_nY + 85 - CAMERA->getY() - (m_nPlayerSizeY / 2), m_nPlayerSizeX * 2, m_nPlayerSizeY * 2);
	// �޴�Ŭ���� ������Ʈ
	m_pMenu->update();
	// Ÿ���� xy�޾ƿ��� �Լ�
	setTargetXY();

	// ���� �������� ������
	if (m_pTargetItem)
	{
		m_pTargetItem->setPlayXY(m_nX, m_nY);	// ������������ �ƴҶ� �÷��̾� x,y�޾ƿ��� �Լ�
		if (m_playerState != PLAYER_FISHING && m_pMenu->getInven()->getLbutton() == false)
		{
			setItemMotion();
		}						// ���������� ��� ����
		setSyncMotion(m_playerMotion, &m_nSyncX, &m_nSyncY);	// ��� ���� x,y������
		// �÷��̾ �÷���(�ʵ�)�����ϋ� ���������� ���� ������ �׷����� ����(�����ڼ�)
		if (m_playerState == PLAYER_PLAY)
		{
			m_pTargetItem->setPlayerPlaying(true);
		}
		else
		{
			m_pTargetItem->setPlayerPlaying(false);
		}
	}

	//����
	m_pFishing->setPlayer(this);
	m_pFishing->update();

}

void player::render(HDC hdc)
{
	if (m_pFishing->getIsFishing() == false)
		// �÷��̾� ����
	{
		m_pPlayer->aniRender(hdc, m_nX - CAMERA->getX() - m_nSyncX, m_nY - CAMERA->getY() - m_nSyncY, m_pAni);
	}

	// ���� �������� ������
	if (m_pTargetItem)
	{
		if (m_playerState == PLAYER_PLAY)
		{
			switch (m_pTargetItem->getItemKind())
			{
				// ������������ �����϶� + �÷��̾ �̵����� �ƴҋ�
			case ITEM_ACT:
				if (isTargetRc)
				{
					m_pTarget->render(hdc, m_nTargetX, m_nTargetY);
				}
				break;
			case ITEM_SEED:
				break;
			}
		}
	}
	//MakeRect(hdc, m_temprc);
	//MakeRect(hdc, m_rc);

	m_pMenu->render(hdc);

	if (m_pTargetItem)
	{
		char str[128];
		sprintf_s(str, 128, "%d", m_pTargetItem->getItemId());
		TextOut(hdc, 200, 700, str, strlen(str));
	}

	m_pFishing->render(hdc);
}

player::player()
{
}


player::~player()
{
}

// Ÿ�ٷ�Ʈ ��ǥ
// ������ �޾ƿ;���
void player::setTargetXY()
{
	//vector<tagTile>	vecTile;
	//vector<tagTile>::iterator	iterTile;
	//vecTile = m_pMap->getTile();

	//for (iterTile = vecTile.begin(); iterTile != vecTile.end(); iterTile++)
	//{
	//	if (IntersectRect(&m_temprc, &iterTile->rc, &m_TargetRc))
	//	{
	//		if (isTargetRc == true)
	//		{
	//			if (PtInRect(&iterTile->rc, g_ptMouse))
	//			{
	//				m_nTargetX = iterTile->rc.left;
	//				m_nTargetY = iterTile->rc.top;
	//			}
	//		}
	//		else
	//		{
	//			m_nTargetX = iterTile->rc.left;
	//			m_nTargetY = iterTile->rc.top;
	//			break;
	//		}
	//	}
	//}
}

// Ű ����
void player::setKey()
{

	if (KEYMANAGER->isStayKeyDown('A'))
	{
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
		isTargetRc = false;
		move(m_playerDir);
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		isMove = false;
		isTargetRc = true;
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
		isTargetRc = false;
		m_playerDir = PLAYER_RIGHT;
		move(m_playerDir);
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		isMove = false;
		isTargetRc = true;
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
		isTargetRc = false;
		m_playerDir = PLAYER_UP;
		move(m_playerDir);
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		isMove = false;
		isTargetRc = true;
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
		isTargetRc = false;
		m_playerDir = PLAYER_DOWN;
		move(m_playerDir);
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		isMove = false;
		isTargetRc = true;
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
		m_playerState = PLAYER_MENU;
		m_pMenu->setMenuDir(MENU_INVEN);
	}
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		m_playerState = PLAYER_MENU;
		m_pMenu->setMenuDir(MENU_SHOP);
	}
}

// �̵��Լ� (�����ؾ���)
void player::move(PLAYERDIR playerdir)
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

	// ������ �޾ƿ;���

	//vector<tagTile>	vecTile;
	//vector<tagTile>::iterator	iterTile;
	//vecTile = m_pMap->getTile();
	//for (iterTile = vecTile.begin(); iterTile != vecTile.end(); iterTile++)
	//{
	//	if (iterTile->object == OBJ_BLOCK_1 && IntersectRect(&m_TargetRc, &iterTile->rc, &m_rc))
	//	{
	//		switch (playerdir)
	//		{
	//		case PLAYER_LEFT:
	//			//m_nX += m_nMoveSpeed;
	//			break;
	//		case PLAYER_RIGHT:
	//			m_nX -= m_nMoveSpeed;
	//			return;
	//			break;
	//		case PLAYER_UP:
	//			//	m_nY += m_nMoveSpeed;
	//			break;
	//		case PLAYER_DOWN:
	//			//m_playerCollision = COLL_DOWN;
	//			m_nY -= m_nMoveSpeed;
	//			return;
	//			break;
	//		}
	//	}
	//}
}

// ��ǿ����� �̹�����ü + �ִϸ��̼� ��������
void player::setMotion(animation * ani, image** image, const char * szName, int framex, int framey)
{
	*image = IMAGEMANAGER->findImage(szName);
	ani->init((*image)->getWidth(), (*image)->getHeight(), (*image)->getWidth() / framex, (*image)->getHeight() / framey);
}

// ���õ� �ִϸ��̼� �׷��� ������ ���� + �ִϸ��̼� �����Լ�
void player::startMotion(animation * ani, int start, int end, bool reverse, bool loop, int fps)
{
	ani->setPlayFrame(start, end, reverse, loop);
	ani->start();
	ani->setFPS(5);
}

// �÷��̾� ��� ����
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

// ���ٿ� ���õ� ������ ���������� ��Ǽ���
void player::setItemMotion()
{
	if (m_playerState == PLAYER_PLAY)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
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
					break;
				case ACTITEM_FISHINGROD:
					
					//m_playerMotion = MOTION_FISHINGROD;
					//setMotion(m_pAni, &m_pPlayer, "player_fishing", 4, 4);
					//switch (m_playerDir)
					//{
					//case PLAYER_LEFT:
					//	startMotion(m_pAni, 4, 8, false, false, 5);
					//	break;
					//case PLAYER_RIGHT:
					//	startMotion(m_pAni, 8, 12, false, false, 5);
					//	break;
					//case PLAYER_UP:
					//	startMotion(m_pAni, 12, 16, false, false, 5);
					//	break;
					//case PLAYER_DOWN:
					//	startMotion(m_pAni, 0, 4, false, false, 5);
					//	break;
					//}
				
					m_pFishing->init();
					//m_pFishing->setIsOne(true);
					//m_pFishing->setIsMistake(false);
	
					m_pFishing->setIsFishing(true);
					m_playerState = PLAYER_FISHING;		
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

// �����ۻ�� �Լ�
void player::useItem()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (m_pTargetItem->getItemOn() == true &&				// ���� �������� �ִ���
			(m_pTargetItem->getItemKind() == ITEM_SEED ||		// ���� �������� �����̳� �Ҹ�ǰ����
				m_pTargetItem->getItemKind() == ITEM_CONSUME))
		{
			switch (m_pTargetItem->getConsumItemKind())
			{
			case CONITEM_RECOVERY:
				switch (m_pTargetItem->getItemId())
				{
				case 201:
					m_pTargetItem->useItem();
					break;
				}
				break;
			case CONITEM_SEED:
				break;
			}
		}
	}
}
