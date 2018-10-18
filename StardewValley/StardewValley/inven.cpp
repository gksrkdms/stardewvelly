#include "stdafx.h"
#include "inven.h"
#include "item.h"


HRESULT inven::init()
{
	m_pSlot1 = IMAGEMANAGER->findImage("inven_001");
	m_pSlot2 = m_pSlot3 = IMAGEMANAGER->findImage("inven_002");
	m_pInvenBG = IMAGEMANAGER->findImage("inven_004");
	m_pUiBG = IMAGEMANAGER->findImage("quickbar");
	m_pNumber = IMAGEMANAGER->findImage("barnumber");
	m_pTarget = IMAGEMANAGER->findImage("focustile_001");
	m_pSort = IMAGEMANAGER->findImage("sort");
	m_pTrashCan = IMAGEMANAGER->findImage("trash_can");
	m_pUiToolTip = IMAGEMANAGER->findImage("menu_textBox");

	m_pHand = new item;
	m_pHand->init(0, 0);
	m_pTempHand = new item;
	m_pTempHand->init(0, 0);
	m_pQuickItem = NULL;

	m_nBgX = 150;
	m_nBgY = 150;
	m_nSlotX = m_nBgX + 40;
	m_nSlot1Y = m_nBgY + 50;
	m_nSlot2Y = m_nBgY + 120;
	m_nSlot3Y = m_nBgY + 190;

	m_nUiX = 240;
	m_nUiY = WINSIZEY - 100;

	m_nQuickNum = 1;

	m_nInvenSize = 1;

	isAddSize = true;
	isHandItem = false;
	m_invenDir = INVEN_QUICKBAR;
	isUiDown = true;
	isLbutton = false;


	// �κ��丮 ������(36)��ŭ ��ü������ map�� ����ش�
	for (int i = 0; i < 36; i++)
	{
		item* newItem = new item;
		m_mapItem.insert(pair<int, item*>(i, newItem));
		switch (i / 12)
		{
		case 0:
			newItem->init(m_nSlotX + 4 + (i % 12) * 64, m_nSlot1Y + 3);
			break;
		case 1:
			newItem->init(m_nSlotX + 4 + (i % 12) * 64, m_nSlot2Y + 3);
			break;
		case 2:
			newItem->init(m_nSlotX + 4 + (i % 12) * 64, m_nSlot3Y + 3);
			break;
		}
		// �ʱ������ 7�� �־���
		if (i < 7)
		{
			newItem->getItem(i + 1, false);
		}
		if (i == 7)
		{
			newItem->getItem(201, false);
		}
	}

	//m_hBtnSave = CreateWindow("button", "sort",
	//	WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	//	WINSIZEX - 300,
	//	200, 100, 40,
	//	g_hWnd, HMENU(0), g_hInstance, NULL);

	m_sortRc = RectMake(m_pInvenBG->getWidth() + 150, 200, m_pSort->getWidth(), m_pSort->getHeight());
	m_TrashRc = RectMake(m_pInvenBG->getWidth() + 170, 400, m_pTrashCan->getWidth() * 4, m_pTrashCan->getHeight() * 4);
	isSort = false;
	isTrash = false;

	return S_OK;
}

void inven::release()
{
	// �κ��丮 ������
	m_iterItem = m_mapItem.begin();
	for (; m_iterItem != m_mapItem.end();)
	{
		if (m_iterItem->second != NULL)
		{
			m_iterItem->second->release();
			delete m_iterItem->second;
			m_iterItem = m_mapItem.erase(m_iterItem);
		}
		else
		{
			m_iterItem++;
		}
		//m_iterItem->second->release();
	}
	m_mapItem.clear();
}

void inven::update()
{
	// �κ��丮 ���� ���� �Լ�
	invenAdd();

	// �κ��丮 (item)��ü�� ������Ʈ
	for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
	{
		m_iterItem->second->update();
	}

	// ĳ���� ��ġ�� ���� ���� ��ġ �Ұ�
	if (CAMERA->getY() >= g_mapSize.mapSizeY - WINSIZEY)
	{
		isUiDown = false;
	}
	else
	{
		isUiDown = true;
	}

	setDir(); // �÷��̾� ��Ȳ�� ���� �κ��丮�� �����Լ�
	// �տ� ���� ������ x,y���콺 ����ٴϰ�
	//if (isHandItem == true)
	//{
		m_pHand->setX(g_ptMouse.x + 5);
		m_pHand->setY(g_ptMouse.y + 5);
		m_pHand->update();
	//}

	if (m_invenDir == INVEN_INVEN)
	{
		// ui���� ������Ʈ
		setUiUpdate();
	}

	if (m_invenDir == INVEN_QUICKBAR)
	{
		setClickQuickItem(); // L��ư Ű�� ��ġ�Ƿ� ���ٿ� ���콺�� ������ L��ư �������ְ� Ȱ��ȭ

		// �ʵ�����϶� ���� y�����
		for (int i = 0; i < 12; i++)
		{
			m_iterItem = m_mapItem.find(i);
			if (isUiDown == true)
				m_iterItem->second->setMouseY(g_ptMouse.y - 250);
			else
				m_iterItem->second->setMouseY(g_ptMouse.y + 5);
		}
	}
	// �����ϋ� ���� y�����
	if (m_invenDir == INVEN_SHOP)
	{
		for (int i = 0; i < 12; i++)
		{
			m_iterItem = m_mapItem.find(i);
			m_iterItem->second->setMouseY(g_ptMouse.y + 5);
		}
	}

	// �޴��κ��丮, �����κ��丮�����ϋ� ���콺 LŬ�� �޾ƿ�
	if (m_invenDir != INVEN_QUICKBAR)
	{
		setClickShopItem();
		if (isHandItem == false)
		{
			if (isLbutton == true)
				InvenTohand();
		}
		else
		{
			if (isLbutton == true)
				handToInven();
		}
	}
	setKey(); // ����Ű �Լ� ���� 1 ~ = ���� ����
	setQuickItem();	// ���ٿ� ��ϵ� ������ �÷��̾����� ����
	if (m_pQuickItem) // m_pQuickItem �÷��̾ �̾������� ������ �޾ƿ�
		m_pQuickItem->update();
}

void inven::render(HDC hdc)
{
	// �κ��丮�޴��϶� ui�� �������� ����
	if (m_invenDir == INVEN_INVEN)
	{
		m_pInvenBG->render(hdc, m_nBgX, m_nBgY);
		m_pSlot1->render(hdc, m_nSlotX, m_nSlot1Y);
		m_pSlot2->render(hdc, m_nSlotX, m_nSlot2Y);
		m_pSlot3->render(hdc, m_nSlotX, m_nSlot3Y);
		for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
		{
			m_iterItem->second->render(hdc);
			m_iterItem->second->setMouseY(g_ptMouse.y + 5);
		}
		// ���� ������ ����
		if (isSort)
		{
			m_pSort->floatRender(hdc, m_pInvenBG->getWidth() + 150, 200, 0, 0, m_pSort->getWidth(), m_pSort->getHeight(), 1.05f);
			m_pUiToolTip->render(hdc, g_ptMouse.x + 10, g_ptMouse.y + 10);
			TextOut(hdc, g_ptMouse.x + 25, g_ptMouse.y + 28, "����", strlen("����"));
		}
		else
		m_pSort->floatRender(hdc, m_pInvenBG->getWidth() + 150, 200, 0, 0, m_pSort->getWidth(), m_pSort->getHeight(), 1.0f);
		// �������� ������ ����
		if (isTrash)
		{
			m_pTrashCan->floatRender(hdc, m_pInvenBG->getWidth() + 170, 400, 0, 0, m_pTrashCan->getWidth(), m_pTrashCan->getHeight(), 4.2f);
			m_pUiToolTip->floatRender(hdc, g_ptMouse.x + 10, g_ptMouse.y + 10, 0, 0, m_pUiToolTip->getWidth(), m_pUiToolTip->getHeight(), 1.3f);
			TextOut(hdc, g_ptMouse.x + 25, g_ptMouse.y + 35, "������", strlen("������"));
		}
		else
			m_pTrashCan->floatRender(hdc, m_pInvenBG->getWidth() + 170, 400, 0, 0, m_pTrashCan->getWidth(), m_pTrashCan->getHeight(), 4.0f);
	}
	// ���۸޴��ϋ� ui�� �κ��丮 ���� (�̱���)
	if (m_invenDir == INVEN_MAKE)
	{

	}

	// �����϶� �κ�ui�� ������ ����
	if (m_invenDir == INVEN_SHOP)
	{
		m_pInvenBG->render(hdc, m_nBgX, m_nBgY);
		m_pSlot1->render(hdc, m_nSlotX, m_nSlot1Y);
		m_pSlot2->render(hdc, m_nSlotX, m_nSlot2Y);
		m_pSlot3->render(hdc, m_nSlotX, m_nSlot3Y);
	}

	// �տ� �������� Ȱ��ȭ�ɶ� ����
	if (isHandItem == true)
	{
		m_pHand->render(hdc);
		//m_pHand->getImg()->render(hdc, m_pHand->getX(), m_pHand->getY(), 3);
		//if (m_pHand->getItemNum() > 1 && m_pHand->getStackItem() == true)
		//{
		//	// �տ�����ִ� ������ ���� ����
		//	char str[128];
		//	sprintf_s(str, 128, "%d", m_pHand->getItemNum());
		//	TextOut(hdc, m_pHand->getX() + 45, m_pHand->getY() + 45, str, strlen(str));
		//}
	}
}

void inven::quickbarRender(HDC hdc)
{
	// ����(�ʵ�)�����϶� ui�� ������ ����
	if (m_invenDir == INVEN_QUICKBAR)
	{
		m_pUiBG->render(hdc, m_nUiX, m_nUiY);
		m_pSlot1->render(hdc, m_nSlotX, m_nSlot1Y);
		m_pTarget->render(hdc, m_nUiX + 16 + (m_nQuickNum - 1) * 64, m_nUiY + 16, 2);

		for (int i = 0; i < 12; i++)
		{
			m_iterItem = m_mapItem.find(i);
			m_iterItem->second->render(hdc);
			m_pNumber->frameRender(hdc, m_nUiX + 20 + (i * 64), m_nUiY + 20, i, 0);
		}
	}
}

inven::inven()
{
}


inven::~inven()
{
}


// �κ��丮 ���� �߰�
void inven::invenAdd()
{
	if (isAddSize)
	{
		switch (m_nInvenSize)
		{
		case 1:
			m_pSlot1 = IMAGEMANAGER->findImage("inven_001");
			isAddSize = false;
			for (int i = 0; i < 12; i++)
			{
				m_iterItem = m_mapItem.find(i);
				m_iterItem->second->setInvenOn(true);
			}
			break;
		case 2:
			m_pSlot2 = IMAGEMANAGER->findImage("inven_001");
			isAddSize = false;
			for (int i = 12; i < 24; i++)
			{
				m_iterItem = m_mapItem.find(i);
				m_iterItem->second->setInvenOn(true);
			}
			break;
		case 3:
			m_pSlot3 = IMAGEMANAGER->findImage("inven_001");
			isAddSize = false;
			for (int i = 24; i < 36; i++)
			{
				m_iterItem = m_mapItem.find(i);
				m_iterItem->second->setInvenOn(true);
			}
			break;
		}
	}
}

// �κ��丮�� ������ �߰�
void inven::addItem(int itemnum)
{
	bool onItem = false;
	map<int, item*>::iterator iterItem;
	for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
	{
		if (m_iterItem->second->getInvenOn() == true &&
			m_iterItem->second->getItemId() == itemnum &&
			m_iterItem->second->getStackItem() == true &&
			m_iterItem->second->getItemNum() < MAXITEM)
		{
			onItem = true;
			iterItem = m_iterItem;
			break;
		}
	}
	// �Ȱ��� �������� ������
	if (onItem == true)
	{
		iterItem->second->getItem(itemnum, onItem);
	}
	else
	{
		for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
		{
			if (m_iterItem->second->getInvenOn() == true &&
				m_iterItem->second->getItemOn() == false)
			{
				m_iterItem->second->getItem(itemnum, onItem);
				return;
			}
		}
	}
}

// �κ��丮���� ������
void inven::InvenTohand()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
		{
			if (m_iterItem->second->getInvenOn() == true &&
				m_iterItem->second->getItemOn() == true)
			{
				if (PtInRect(&m_iterItem->second->getrect(), g_ptMouse))
				{
					SOUNDMANAGER->play("sound/effect/changeitem.wav");

					InvenTohandSwap(m_iterItem->first);
					isHandItem = true;
					m_iterItem->second->deleteItem();
				}
			}
		}
	}
}

// �տ��� �κ��丮 �� �տ��� ��
void inven::handToInven()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
		{
			if (m_iterItem->second->getInvenOn() == true)
			{
				if (m_iterItem->second->getItemOn() == false)
				{
					// �տ��� �κ��丮
					if (PtInRect(&m_iterItem->second->getrect(), g_ptMouse))
					{
						handToInvenSwap(m_iterItem->first);
						isHandItem = false;
						m_pHand->deleteItem();

						SOUNDMANAGER->play("sound/effect/changeitem.wav");

					}
				}
				else
				{
					// �տ��� ��
					if (PtInRect(&m_iterItem->second->getrect(), g_ptMouse))
					{
						handToTempSwap();
						InvenTohandSwap(m_iterItem->first);
						tempToInvenSwap(m_iterItem->first);
						m_pTempHand->deleteItem();

						SOUNDMANAGER->play("sound/effect/changeitem.wav");

					}
				}
			}
		}
	}
}

// �κ�����
void inven::sortInven()
{
	map<int, item*>::iterator iterItem1;
	map<int, item*>::iterator iterItem2;
	for (iterItem1 = m_mapItem.begin(); iterItem1 != m_mapItem.end(); iterItem1++)
	{
		for (iterItem2 = m_mapItem.begin(); iterItem2->first < iterItem1->first; iterItem2++)
		{
			if (iterItem1->second->getItemId() != 0)
			{
				if (iterItem2->second->getItemId() == 0)
				{
					InvenToTempSwap(iterItem2->first);
					InvenToInvenSwap(iterItem1->first, iterItem2->first);
					tempToInvenSwap(iterItem1->first);
					m_pTempHand->deleteItem();
				}
				else
				{
					if (iterItem2->second->getItemId() > iterItem1->second->getItemId())
					{
						InvenToTempSwap(iterItem2->first);
						InvenToInvenSwap(iterItem1->first, iterItem2->first);
						tempToInvenSwap(iterItem1->first);
						m_pTempHand->deleteItem();
					}
				}
			}
		}
	}
}

// �κ�->�� �����ͽ���
void inven::InvenTohandSwap(int itemnum)
{
	m_iterItem = m_mapItem.find(itemnum);
	dataSwap(m_pHand, m_iterItem->second);
}

// ��->�κ� �����ͽ���
void inven::handToInvenSwap(int itemnum)
{
	m_iterItem = m_mapItem.find(itemnum);
	dataSwap(m_iterItem->second, m_pHand);
}

// ��->���� �����ͽ���
void inven::handToTempSwap()
{
	dataSwap(m_pTempHand, m_pHand);
}

// ����->�κ� �����ͽ���
void inven::tempToInvenSwap(int itemnum)
{
	m_iterItem = m_mapItem.find(itemnum);
	dataSwap(m_iterItem->second, m_pTempHand);
}

// �κ�->���� �����ͽ���
void inven::InvenToTempSwap(int itemnum)
{
	m_iterItem = m_mapItem.find(itemnum);
	dataSwap(m_pTempHand, m_iterItem->second);
}

// �κ�->�κ� �����ͽ���
// 1�� 2�� �־���
void inven::InvenToInvenSwap(int itemnum1, int itemnum2)
{
	map<int, item*>::iterator iterItem1;
	map<int, item*>::iterator iterItem2;
	iterItem1 = m_mapItem.find(itemnum1);
	iterItem2 = m_mapItem.find(itemnum2);
	dataSwap(iterItem2->second, iterItem1->second);
}

// �����۳��� �����ͱ�ȯ
void inven::dataSwap(item * item1, item * item2)
{
	item1->setImg(item2->getImg());						// �������̹���
	item1->setName(item2->getName());					// �������̸�
	item1->setItemKindName(item2->getItemKindName());	// ����������(����,���� ��)
	item1->setItemToolTip(item2->getItemToolTip());		// ����������
	item1->setStackItem(item2->getStackItem());			// ������ ��ø����
	item1->setItemSell(item2->getItemSell());			// ������ �ǸŰ��ɿ���
	item1->setItemPrice(item2->getItemPrice());			// �����۰���
	item1->setItemKind(item2->getItemKind());			// ������ ����
	item1->setActItemKind(item2->getActItemKind());		// ���������� ����
	item1->setConsumItemKind(item2->getConsumItemKind());// �Ҹ�ǰ ����
	item1->setItemId(item2->getItemId());				// ������ ��ȣ
	item1->setWaterDurability(item2->getWaterDurability()); // ���Ѹ��� ������
	item1->setMaxWaterDurability(item2->getMaxWaterDurability()); // ���Ѹ��� �ִ볻����
	item1->setEnergy(item2->getEnergy());				// ������ ȸ����
	item1->setHp(item2->getHp());						// hp ȸ����
	item1->setMinDmg(item2->getMinDmg());				// �ּҵ�����
	item1->setMaxDmg(item2->getMaxDmg());				// �ִ뵥����
	item1->setWaterBar(item2->getWaterBar());			// ���α׷����� �ּҰ�
	item2->setWaterBar(NULL);							// ���� �ѱ�� NULL��;
	item1->setItemOn(item2->getItemOn());				// ������Ȱ��ȭ ����
	item1->setItemNum(item2->getItemNum());				// ������ ����
}

// �÷��̾� ���¿� ���� �κ��丮��
void inven::setDir()
{
	// ����(�ʵ忡������)
	if (m_invenDir == INVEN_QUICKBAR)
	{
		// ���� �Ʒ��� ������
		if (isUiDown == true)
		{
			// 1������(����) ���������� ��ġ�ٲ���
			m_nUiY = WINSIZEY - 120;
			m_nSlotX = m_nUiX + 16;
			m_nSlot1Y = m_nUiY + 16;
			for (int i = 0; i < 12; i++)
			{
				m_iterItem = m_mapItem.find(i);
				m_iterItem->second->setX(m_nSlotX + 4 + (i % 12) * 64);
				m_iterItem->second->setY(m_nSlot1Y + 3);
			}
		}
		// ���� ���� ������
		else
		{
			// 1������(����) ���������� ��ġ�ٲ���
			m_nUiY = 0;
			m_nSlotX = m_nUiX + 16;
			m_nSlot1Y = m_nUiY + 16;
			for (int i = 0; i < 12; i++)
			{
				m_iterItem = m_mapItem.find(i);
				m_iterItem->second->setX(m_nSlotX + 4 + (i % 12) * 64);
				m_iterItem->second->setY(m_nSlot1Y + 3);
			}
		}
	}
	// �κ��丮 ��������
	if (m_invenDir == INVEN_INVEN)
	{
		m_pInvenBG = IMAGEMANAGER->findImage("inven_004");
		m_nBgX = 150;
		m_nBgY = 150;
		m_nSlotX = m_nBgX + 40;
		m_nSlot1Y = m_nBgY + 50;
		m_nSlot2Y = m_nBgY + 120;
		m_nSlot3Y = m_nBgY + 190;
		for (int i = 0; i < 36; i++)
		{
			m_iterItem = m_mapItem.find(i);
			switch (i / 12)
			{
			case 0:
				m_iterItem->second->setX(m_nSlotX + 4 + (i % 12) * 64);
				m_iterItem->second->setY(m_nSlot1Y + 3);
				break;
			case 1:
				m_iterItem->second->setX(m_nSlotX + 4 + (i % 12) * 64);
				m_iterItem->second->setY(m_nSlot2Y + 3);
				break;
			case 2:
				m_iterItem->second->setX(m_nSlotX + 4 + (i % 12) * 64);
				m_iterItem->second->setY(m_nSlot3Y + 3);
				break;
			}
		}
	}

	// ���� �޴� �������� �κ��丮
	if (m_invenDir == INVEN_MAKE)
	{
		m_pInvenBG = IMAGEMANAGER->findImage("shop_make");
	}

	// ���� �޴� �������� �κ��丮
	if (m_invenDir == INVEN_SHOP)
	{
		m_pInvenBG = IMAGEMANAGER->findImage("shop_make");
		m_nBgX = 276;
		m_nBgY = 540;
		m_nSlotX = m_nBgX + 40;
		m_nSlot1Y = m_nBgY + 30;
		m_nSlot2Y = m_nBgY + 100;
		m_nSlot3Y = m_nBgY + 170;

		for (int i = 0; i < 36; i++)
		{
			m_iterItem = m_mapItem.find(i);
			switch (i / 12)
			{
			case 0:
				m_iterItem->second->setX(m_nSlotX + 4 + (i % 12) * 64);
				m_iterItem->second->setY(m_nSlot1Y + 3);
				break;
			case 1:
				m_iterItem->second->setX(m_nSlotX + 4 + (i % 12) * 64);
				m_iterItem->second->setY(m_nSlot2Y + 3);
				break;
			case 2:
				m_iterItem->second->setX(m_nSlotX + 4 + (i % 12) * 64);
				m_iterItem->second->setY(m_nSlot3Y + 3);
				break;
			}
		}
	}


}

// ���� ������ �޾Ƽ� �÷��̾����� ����
void inven::setQuickItem()
{
	for (int i = 0; i < 12; i++)
	{
		m_iterItem = m_mapItem.find(i);
		if (i == m_nQuickNum - 1)
		{
			m_iterItem->second->setPlayerHead(true);
			m_pQuickItem = m_iterItem->second;
		}
		else
		{
			m_iterItem->second->setPlayerHead(false);
		}
	}
}

// L��ư Ű�� ��ġ�Ƿ� ���ٿ� ���콺�� ������ L��ư �������ְ� Ȱ��ȭ
void inven::setClickQuickItem()
{
	for (int i = 0; i < 12; i++)
	{
		m_iterItem = m_mapItem.find(i);
		if (PtInRect(&m_iterItem->second->getrect(), g_ptMouse))
		{
			isLbutton = true;
			break;
		}
		else
		{
			isLbutton = false;
		}
	}
	if (isLbutton == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 12; i++)
			{
				m_iterItem = m_mapItem.find(i);
				if (PtInRect(&m_iterItem->second->getrect(), g_ptMouse))
				{
					m_nQuickNum = i + 1;
				}
			}
		}
	}
}

// ���콺 ��Ŭ�� Ȱ��ȭ �Լ�
void inven::setClickShopItem()
{
	for (int i = 0; i < 36; i++)
	{
		m_iterItem = m_mapItem.find(i);
		if (PtInRect(&m_iterItem->second->getrect(), g_ptMouse))
		{
			isLbutton = true;
			break;
		}
		else
		{
			isLbutton = false;
		}
	}
}

void inven::setKey()
{
	if (m_invenDir == INVEN_QUICKBAR)
	{
		if (KEYMANAGER->isOnceKeyDown(0x31))
		{
			m_nQuickNum = 1;
		}
		if (KEYMANAGER->isOnceKeyDown(0x32))
		{
			m_nQuickNum = 2;
		}
		if (KEYMANAGER->isOnceKeyDown(0x33))
		{
			m_nQuickNum = 3;
		}
		if (KEYMANAGER->isOnceKeyDown(0x34))
		{
			m_nQuickNum = 4;
		}
		if (KEYMANAGER->isOnceKeyDown(0x35))
		{
			m_nQuickNum = 5;
		}
		if (KEYMANAGER->isOnceKeyDown(0x36))
		{
			m_nQuickNum = 6;
		}
		if (KEYMANAGER->isOnceKeyDown(0x37))
		{
			m_nQuickNum = 7;
		}
		if (KEYMANAGER->isOnceKeyDown(0x38))
		{
			m_nQuickNum = 8;
		}
		if (KEYMANAGER->isOnceKeyDown(0x39))
		{
			m_nQuickNum = 9;
		}
		if (KEYMANAGER->isOnceKeyDown(0x30))
		{
			m_nQuickNum = 10;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_OEM_MINUS))
		{
			m_nQuickNum = 11;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_OEM_PLUS))
		{
			m_nQuickNum = 12;
		}
	}
	if (m_invenDir == INVEN_INVEN)
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			if (m_nInvenSize < 3)
			{
				m_nInvenSize++;
				isAddSize = true;
			}
		}
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			addItem(1);
		}
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			addItem(2);
		}
		if (KEYMANAGER->isOnceKeyDown('V'))
		{
			addItem(3);
		}
	}
}

void inven::setUiUpdate()
{
	if (PtInRect(&m_sortRc, g_ptMouse))
	{
		isSort = true;
	}
	else
	{
		isSort = false;
	}
	if (PtInRect(&m_TrashRc, g_ptMouse))
	{
		if(SOUNDMANAGER->isPlaying("sound/effect/�������뿩�¼Ҹ�.wav")==false && isTrash ==false)
		SOUNDMANAGER->play("sound/effect/�������뿩�¼Ҹ�.wav", g_soundVolume.effect);
		isTrash = true;
	}
	else
	{
		isTrash = false;
	}

	if (isSort)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SOUNDMANAGER->play("sound/effect/�κ�����.wav", g_soundVolume.effect);
			sortInven();
		}
	}

	if (isTrash)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (isHandItem && m_pHand->getItemSell() == true)
			{
				SOUNDMANAGER->play("sound/effect/�������������.wav", g_soundVolume.effect);
				
				m_pHand->deleteItem();
				isHandItem = false;
			}
			else
			{
				SOUNDMANAGER->play("sound/effect/fishing/����ä�¼Ҹ�.wav", g_soundVolume.effect);
			}
		}
	}
}
