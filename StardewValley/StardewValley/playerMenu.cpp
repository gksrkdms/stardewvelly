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

	m_mapItem = m_pInven->getInvenMap(); // 인벤토리 map정보 받아옴

	// 메뉴가 호출되면
	if (isMenu)
	{
		// 메뉴가 인벤토리,상점,제작,등등 체크해줌
		if (m_menuDir == MENU_INVEN)
		{
			m_pInven->setInvenDir(INVEN_INVEN);	// 메뉴가 인벤토리일떄 인벤토리 랜더를위해 상태값변경
		}
		if (m_menuDir == MENU_SHOP)
		{
			m_pInven->setInvenDir(INVEN_SHOP);	// 메뉴가 상점일떄 인벤토리 랜더를 위해 상태값변경
		}
		// 손에 아이템이 없을떄만 메뉴창을 닫을수있게함
		if (m_pInven->getHandItem() == false)
		{
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				m_pInven->setInvenDir(INVEN_QUICKBAR);	// 인벤토리 상태를 퀵바로
				m_menuDir = MENU_INVEN;					// 메뉴상태값을 인벤토리로 초기화
				isMenu = false;							// 인벤토리 false
			}
		}
	}

}

void playerMenu::render(HDC hdc)
{
	m_pInven->render(hdc);	// 인벤토리 클래스 랜더
	if (isMenu)
	{
		if (m_menuDir == MENU_SHOP)
		{
			m_pShop->render(hdc);	// 상점클래스 랜더
		}
	}
	if (m_menuDir != MENU_SHOP)
	{
		// 메뉴 상태값이 상점이 아니면
		// 인벤토리 툴팁을 랜더함(마우스 오버시)
		// 상점은 상점전용의 툴팁이따로잇음
		for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
		{
			m_iterItem->second->ToolTiprender(hdc);
		}
	}
}

// 플레이어의 소지금 상태를 알기위해서
// 이함수를 통해서 상점한테 정보를 넘김
void playerMenu::getPlayer(player * play)
{
	m_pShop->getPlayer(play);
}

// 퀵바에 선택된 아이템정보를 플레이어한테 넘김
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
