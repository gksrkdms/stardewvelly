#include "stdafx.h"
#include "shop.h"
#include "inven.h"
#include "item.h"
#include "player.h"


HRESULT shop::init()
{
	m_pWindow = IMAGEMANAGER->findImage("shop_window");
	m_pList = IMAGEMANAGER->findImage("show_list");
	m_pLeft = IMAGEMANAGER->findImage("leftarrow");
	m_pRight = IMAGEMANAGER->findImage("rightarrow");
	m_pGoldUi = IMAGEMANAGER->findImage("goldui");

	m_nWinX = 20;
	m_nWinY = 20;
	m_nListX = m_nWinX + 24;

	// ������ ������ ��ü 4�������� map�� �����
	for (int i = 0; i < 4; i++)
	{
		m_nArrayListY[i] = 43 + i * (94 + 12);
		m_pItem = new item;
		m_mapItem.insert(pair<int, item*>(i, m_pItem));
		m_pItem->init(m_nListX, m_nArrayListY[i] + 1, true);
		m_pItem->setIconX(24);
		m_pItem->setIconY(20);
		m_pItem->setrcSizeX(1032);
		m_pItem->setrcSizeY(94);
	}

	m_nLeftX = 500;
	m_nLeftY = 480;
	m_nRightX = 600;
	m_nRightY = 480;
	isMouseIn[0] = false;
	isMouseIn[1] = false;

	m_LeftRc = RectMake(m_nLeftX, m_nLeftY, m_pLeft->getWidth(), m_pLeft->getHeight());
	m_RightRc = RectMake(m_nRightX, m_nRightY, m_pRight->getWidth(), m_pRight->getHeight());


	isBuy = false;
	isSell = false;
	isOnceSetItem = true;

	m_nPage = 1;

	return S_OK;
}

void shop::release()
{
	for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
	{
		m_iterItem->second->release();
	}
	m_mapItem.clear();
}

void shop::update()
{
	for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
	{
		m_iterItem->second->update();
		if (m_iterItem->second->getToolTip() == true)
		{
			m_iterItem->second->setMouseY(g_ptMouse.y + 5);
		}
	}

	if (m_pInven->getHandItem() == false)
	{
		isHandItem = false;
	}

	checkTrade();
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (isBuy == true)
		{
			buyItem();
			SOUNDMANAGER->play("sound/effect/���Ҹ�.wav", g_soundVolume.effect);
		}
		if (isSell == true)
		{
			sellItem();
			SOUNDMANAGER->play("sound/effect/���Ҹ�.wav", g_soundVolume.effect);
		}
	}
	setItem();
}

void shop::render(HDC hdc)
{
	// ���� ���â �� ����Ʈ ui����
	m_pWindow->render(hdc, m_nWinX, m_nWinY);
	for (int i = 0; i < 4; i++)
	{
		m_pList->render(hdc, m_nListX, m_nArrayListY[i]);
	}
	// ��� ui ����
	m_pGoldUi->render(hdc, m_nWinX, m_pWindow->getHeight() + 20);
	m_pPlayer->numRender(hdc, m_nWinX + m_pGoldUi->getWidth() / 2 - 18, m_pWindow->getHeight() + 44);

	// ���� ȭ��ǥ ����
	if (isMouseIn[0] == true)
		m_pLeft->floatRender(hdc, m_nLeftX, m_nLeftY, 0, 0, m_pLeft->getWidth(), m_pLeft->getHeight(), 1.2f);
	else
		m_pLeft->floatRender(hdc, m_nLeftX, m_nLeftY, 0, 0, m_pLeft->getWidth(), m_pLeft->getHeight(), 1.0f);
	if (isMouseIn[1] == true)
		m_pRight->floatRender(hdc, m_nRightX, m_nRightY, 0, 0, m_pRight->getWidth(), m_pRight->getHeight(), 1.2f);
	else
		m_pRight->floatRender(hdc, m_nRightX, m_nRightY, 0, 0, m_pRight->getWidth(), m_pRight->getHeight(), 1.0f);
	// �κ��丮 �� ���� ����
	for (m_iterInven = m_mapInven.begin(); m_iterInven != m_mapInven.end(); m_iterInven++)
	{
		m_iterInven->second->ShopInvenRender(hdc);
	}
	for (m_iterInven = m_mapInven.begin(); m_iterInven != m_mapInven.end(); m_iterInven++)
	{
		m_iterInven->second->ShopInvenToolTip(hdc);
	}
	// ���������� ���� �� ��������
	for (int i = 0; i < 4; i++)
	{
		m_iterItem = m_mapItem.find(i);
		if (m_iterItem->second->getItemOn() == true)
		{
			// �̹�������
			m_iterItem->second->render(hdc);
			// �̸�, �� ����
			m_iterItem->second->ShopRender(hdc, m_nListX + 100, m_nArrayListY[i] + 35, m_nListX + 950, m_nArrayListY[i] + 35);
			// ���� ��������
			m_iterItem->second->ToolTiprender(hdc);
		}
	}
}

shop::shop()
{
}


shop::~shop()
{
}

// ������ ����
void shop::buyItem()
{
	bool onItem = false;
	map<int, item*>::iterator iterItem;
	map<int, item*>::iterator iterInven;
	m_mapInven = m_pInven->getInvenMap();

	// ���� �����۸���Ʈ �˻�
	for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
	{
		if (m_iterItem->second->getShopItem() == true && m_iterItem->second->getItemOn() == true)
		{
			if (PtInRect(&m_iterItem->second->getrect(), g_ptMouse))
			{
				iterItem = m_iterItem;
			}
		}
	}

	// �κ��丮�� �Ȱ��� �������� �ִ��� Ȯ��
	for (m_iterInven = m_mapInven.begin(); m_iterInven != m_mapInven.end(); m_iterInven++)
	{
		if (m_iterInven->second->getInvenOn() == true &&							// �κ��丮�� ���Ҵ���
			m_iterInven->second->getItemId() == iterItem->second->getItemId() &&	// �����ҷ��� �������� �κ��丮���� �ִ���
			m_iterInven->second->getStackItem() == true &&							// �ش� �������� ��ø�� ��������
			m_iterInven->second->getItemNum() < MAXITEM)							// ��ø�̰����ϸ� ��ø�� �ִ�ġ�� �ƴ���
		{
			onItem = true;
			iterInven = m_iterInven;
			break;
		}
	}
	// �κ��丮�� �Ȱ��� �������� ������
	if (onItem == true && m_pPlayer->getMoney() >= iterItem->second->getItemPrice())
	{
		m_pPlayer->setMoney(m_pPlayer->getMoney() - iterItem->second->getItemPrice());	// �÷��̾� �����ݾ� ����
		iterInven->second->getItem(iterItem->second->getItemId(), onItem);				// �κ��丮�� �����۳־���(��ø�����ϰ�)
	}
	// �κ��丮�� �Ȱ��� �������� ������ or ������ ��á����
	else
	{
		for (m_iterInven = m_mapInven.begin(); m_iterInven != m_mapInven.end(); m_iterInven++)
		{
			if (m_pPlayer->getMoney() >= iterItem->second->getItemPrice() &&	// �������� ���Աݾ׺��� ū��
				m_iterInven->second->getInvenOn() == true &&					// �κ��丮 �߰�ĭ �����ִ���
				m_iterInven->second->getItemOn() == false)						// �κ��丮�� �����ִ��� Ȯ��
			{
				m_pPlayer->setMoney(m_pPlayer->getMoney() - iterItem->second->getItemPrice());	// �÷��̾� �����ݾ� ����
				m_iterInven->second->getItem(iterItem->second->getItemId(), onItem);			// �κ��丮�� ���ο� ĭ�� �����۳־���
				return;
			}
		}
	}
}

// �ƾ��� �Ǹ�
void shop::sellItem()
{
	m_mapInven = m_pInven->getInvenMap();
	for (m_iterInven = m_mapInven.begin(); m_iterInven != m_mapInven.end(); m_iterInven++)
	{
		if (m_iterInven->second->getShopItem() == false &&	// �������� ����������
			m_iterInven->second->getItemOn() == true &&		// �������� �ִ���
			m_iterInven->second->getItemSell() == true &&	// �������� �ǸŰ�������
			m_iterInven->second->getInvenOn())				// �ش� �κ��丮�� Ȱ��ȭ�����
		{
			if (PtInRect(&m_iterInven->second->getrect(), g_ptMouse))
			{
				// �������� 1���̻��ϋ�
				if (m_iterInven->second->getItemNum() > 1)
				{
					m_pPlayer->setMoney(m_pPlayer->getMoney() + m_iterInven->second->getItemPrice() / 2);
					m_iterInven->second->setItemNum(m_iterInven->second->getItemNum() - 1);
				}
				// �������� 1���ϋ�
				else if (m_iterInven->second->getItemNum() <= 1)
				{
					m_pPlayer->setMoney(m_pPlayer->getMoney() + m_iterInven->second->getItemPrice() / 2);
					m_iterInven->second->deleteItem();
				}

			}
		}
	}

}

// �κ��丮�� ������ ��Ʈ ���콺üũ��
// ���콺 R��ư Ȱ��ȭ������ üũ����
void shop::checkTrade()
{
	// ���������� ����Ʈ�� �������� �����Ҷ� true
	for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
	{
		if (m_iterItem->second->getShopItem() == true && m_iterItem->second->getItemOn() == true)
		{
			if (PtInRect(&m_iterItem->second->getrect(), g_ptMouse))
			{
				isBuy = true;
				break;
			}
			else
			{
				isBuy = false;
			}
		}
	}
	// �κ��丮�� �������� �ִ��� �˻��ϰ� true������
	m_mapInven = m_pInven->getInvenMap();
	for (m_iterInven = m_mapInven.begin(); m_iterInven != m_mapInven.end(); m_iterInven++)
	{
		if (m_iterInven->second->getItemOn() == true && m_iterInven->second->getShopItem() == false)
		{
			if (PtInRect(&m_iterInven->second->getrect(), g_ptMouse))
			{
				isSell = true;
				break;
			}
			else
			{
				isSell = false;
			}
		}
	}
}

// ���� ������ ���¿����� ������ ����Ʈ������
void shop::setItem()
{
	// ����Ʈ ����Ʈ ȭ��ǥ���� ���콺 LŬ�� ����ϱ����� üũ��
	if (PtInRect(&m_LeftRc, g_ptMouse))
	{
		isMouseIn[0] = true;
	}
	else
	{
		isMouseIn[0] = false;
	}
	if (PtInRect(&m_RightRc, g_ptMouse))
	{
		isMouseIn[1] = true;
	}
	else
	{
		isMouseIn[1] = false;
	}
	if (isMouseIn[0] == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (m_nPage == 1)
			{
				m_nPage = MAXPAGE;
				SOUNDMANAGER->play("sound/effect/������1.wav", g_soundVolume.effect);
				isOnceSetItem = true;
			}
			else
			{
				m_nPage--;
				SOUNDMANAGER->play("sound/effect/������1.wav", g_soundVolume.effect);
				isOnceSetItem = true;
			}
		}
	}
	if (isMouseIn[1] == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (m_nPage == MAXPAGE)
			{
				m_nPage = 1;
				SOUNDMANAGER->play("sound/effect/������1.wav", g_soundVolume.effect);
				isOnceSetItem = true;
			}
			else
			{
				m_nPage++;
				SOUNDMANAGER->play("sound/effect/������1.wav", g_soundVolume.effect);
				isOnceSetItem = true;
			}
		}
	}
	int i = 0;

	// ������ ��ȣ������ �����۱�ü��
	if (isOnceSetItem == true)
	{
		switch (m_nPage)
		{
		case 1:
			i = 101;
			for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
			{
				m_iterItem->second->deleteItem();
				m_iterItem->second->getItem(i, false);
				i++;
			}
			isOnceSetItem = false;
			break;
		case 2:
			i = 201;
			for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
			{
				m_iterItem->second->deleteItem();
				m_iterItem->second->getItem(i, false);
				i++;
			}
			isOnceSetItem = false;
			break;
		case 3:
			for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
			{
				m_iterItem->second->deleteItem();
			}
			m_iterItem = m_mapItem.find(0);
			m_iterItem->second->getItem(303, false);
			m_iterItem = m_mapItem.find(1);
			m_iterItem->second->getItem(302, false);
			m_iterItem = m_mapItem.find(2);   //@@@ ���� �߰�
			m_iterItem->second->getItem(501, false);
			m_iterItem = m_mapItem.find(3);   //@@@ ���� �߰�
			m_iterItem->second->getItem(502, false);
		
			isOnceSetItem = false;
			break;
		}
	}
}
