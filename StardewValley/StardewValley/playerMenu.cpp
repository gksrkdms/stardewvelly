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

	m_pIcon[0] = IMAGEMANAGER->findImage("icon1");
	m_pIcon[1] = IMAGEMANAGER->findImage("icon2");
	m_pIcon[2] = IMAGEMANAGER->findImage("icon3");
	m_pIcon[3] = IMAGEMANAGER->findImage("icon4");
	m_pIcon[4] = IMAGEMANAGER->findImage("icon5");
	m_pIcon[5] = IMAGEMANAGER->findImage("icon6");
	m_pIcon[6] = IMAGEMANAGER->findImage("icon7");
	m_pIcon[7] = IMAGEMANAGER->findImage("icon8");

	m_ptextBox = IMAGEMANAGER->findImage("menu_textBox");

	m_Tooltip[0] = "가방";
	m_Tooltip[1] = "기술";
	m_Tooltip[2] = "관계";
	m_Tooltip[3] = "지도";
	m_Tooltip[4] = "제작";
	m_Tooltip[5] = "도감";
	m_Tooltip[6] = "옵션";
	m_Tooltip[7] = "종료";

	for (int i = 0; i < 8; i++)
	{
		m_nIconX[i] = m_pInven->getBgX() + 50 + (i * m_pIcon[i]->getWidth() * ICONSCALA);
		m_nIconY[i] = m_pInven->getBgY() - m_pIcon[i]->getHeight() * ICONSCALA;
		m_IconRc[i] = RectMake(m_nIconX[i], m_nIconY[i], m_pIcon[i]->getWidth() * ICONSCALA, m_pIcon[i]->getHeight() * ICONSCALA);
		isMouseIn[i] = false;
	}

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

	m_mapItem = m_pInven->getInvenMap(); // 인벤토리 map정보 받아옴

	// 메뉴 업데이트
	menuUpdate();

}

void playerMenu::render(HDC hdc)
{
	if (isMenu == false)
	{
		m_pInven->quickbarRender(hdc);	// 퀵바 랜더

		// 퀵바 툴팁 랜더
		for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
		{
			m_iterItem->second->ToolTiprender(hdc);
		}
	}

	// 메뉴가 호출됬을떄( true일떄)
	if (isMenu)
	{
		m_pInven->render(hdc);
		if (m_menuDir == MENU_SHOP)
		{
			m_pShop->render(hdc);	// 상점클래스 랜더
		}
		if (m_menuDir != MENU_SHOP)
		{
			// 메뉴 상태값이 상점이 아니면
			// 인벤토리 툴팁을 랜더함(마우스 오버시)
			// 상점은 상점전용의 툴팁이따로잇음
			// 메뉴창 메뉴 아이콘 랜더
			for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
			{
				m_iterItem->second->ToolTiprender(hdc);
			}
			for (int i = 0; i < 8; i++)
			{
				//MakeRect(hdc, m_IconRc[i]);
				m_pIcon[i]->render(hdc, m_nIconX[i], m_nIconY[i], ICONSCALA);
			}
		}
		for (int i = 0; i < 8; i++)
		{
			if (isMouseIn[i] == true)
			{
				m_ptextBox->render(hdc, g_ptMouse.x + 10, g_ptMouse.y + 10);
				char str[128];
				sprintf_s(str, 128, "%s", m_Tooltip[i].c_str());
				TextOut(hdc, g_ptMouse.x + 30, g_ptMouse.y + 35, str, strlen(str));
			}
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


void playerMenu::menuUpdate()
{
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
			m_pShop->update();
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
		if (m_menuDir != MENU_SHOP)
		{
			for (int i = 0; i < 8; i++)
			{
				if (PtInRect(&m_IconRc[i], g_ptMouse))
				{
					isMouseIn[i] = true;
				}
				else
				{
					isMouseIn[i] = false;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				for (int i = 0; i < 8; i++)
				{
					if (isMouseIn[i] == true)
					{
						m_menuDir = (MENUDIR)i;
					}
				}
			}

			// 메뉴창 y축 랜더
			for (int i = 0; i < 8; i++)
			{
				if ((MENUDIR)i == m_menuDir)
				{
					m_nIconY[i] = m_pInven->getBgY() - m_pIcon[i]->getHeight() * ICONSCALA + 10;
				}
				else
				{
					m_nIconY[i] = m_pInven->getBgY() - m_pIcon[i]->getHeight() * ICONSCALA;
				}
				m_IconRc[i] = RectMake(m_nIconX[i], m_nIconY[i], m_pIcon[i]->getWidth() * ICONSCALA, m_pIcon[i]->getHeight() * ICONSCALA);
			}
		}
	}
}