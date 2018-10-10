#include "stdafx.h"
#include "playerMenu.h"
#include "inven.h"
#include "shop.h"
#include "item.h"


HRESULT playerMenu::init()
{
	m_pInven = new inven;
	m_pInven->init();

	m_pShop = new shop;
	m_pShop->init();

	m_pShop->setInven(m_pInven);

	isMenu = false;
	m_menuDir = MENU_INVEN;
	return S_OK;
}

void playerMenu::release()
{
	m_pInven->release();
	delete m_pInven;
	m_pShop->release();
	delete m_pShop;
}

void playerMenu::update()
{
	m_pInven->update();
	m_pShop->update();

	m_mapItem = m_pInven->getInvenMap(); // �κ��丮 map���� �޾ƿ�

	// �޴��� ȣ��Ǹ�
	if (isMenu)
	{
		// �޴��� �κ��丮,����,����,��� üũ����
		if (m_menuDir == MENU_INVEN)
		{
			m_pInven->setInvenDir(INVEN_INVEN);	// �޴��� �κ��丮�ϋ� �κ��丮 ���������� ���°�����
		}
		if (m_menuDir == MENU_SHOP)
		{
			m_pInven->setInvenDir(INVEN_SHOP);	// �޴��� �����ϋ� �κ��丮 ������ ���� ���°�����
		}
		// �տ� �������� �������� �޴�â�� �������ְ���
		if (m_pInven->getHandItem() == false)
		{
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				m_pInven->setInvenDir(INVEN_QUICKBAR);	// �κ��丮 ���¸� ���ٷ�
				m_menuDir = MENU_INVEN;					// �޴����°��� �κ��丮�� �ʱ�ȭ
				isMenu = false;							// �κ��丮 false
			}
		}
	}

}

void playerMenu::render(HDC hdc)
{
	m_pInven->render(hdc);	// �κ��丮 Ŭ���� ����
	if (isMenu)
	{
		if (m_menuDir == MENU_SHOP)
		{
			m_pShop->render(hdc);	// ����Ŭ���� ����
		}
	}
	if (m_menuDir != MENU_SHOP)
	{
		// �޴� ���°��� ������ �ƴϸ�
		// �κ��丮 ������ ������(���콺 ������)
		// ������ ���������� �����̵�������
		for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
		{
			m_iterItem->second->ToolTiprender(hdc);
		}
	}
}

// �÷��̾��� ������ ���¸� �˱����ؼ�
// ���Լ��� ���ؼ� �������� ������ �ѱ�
void playerMenu::getPlayer(player * play)
{
	m_pShop->getPlayer(play);
}

// ���ٿ� ���õ� ������������ �÷��̾����� �ѱ�
item * playerMenu::getQuickItem()
{
	return m_pInven->getQuickItem();
}


playerMenu::playerMenu()
{
}


playerMenu::~playerMenu() 
{
}
