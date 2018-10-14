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

	m_Tooltip[0] = "����";
	m_Tooltip[1] = "���";
	m_Tooltip[2] = "����";
	m_Tooltip[3] = "����";
	m_Tooltip[4] = "����";
	m_Tooltip[5] = "����";
	m_Tooltip[6] = "�ɼ�";
	m_Tooltip[7] = "����";

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

	m_mapItem = m_pInven->getInvenMap(); // �κ��丮 map���� �޾ƿ�

	// �޴� ������Ʈ
	menuUpdate();

}

void playerMenu::render(HDC hdc)
{
	if (isMenu == false)
	{
		m_pInven->quickbarRender(hdc);	// ���� ����

		// ���� ���� ����
		for (m_iterItem = m_mapItem.begin(); m_iterItem != m_mapItem.end(); m_iterItem++)
		{
			m_iterItem->second->ToolTiprender(hdc);
		}
	}

	// �޴��� ȣ�������( true�ϋ�)
	if (isMenu)
	{
		m_pInven->render(hdc);
		if (m_menuDir == MENU_SHOP)
		{
			m_pShop->render(hdc);	// ����Ŭ���� ����
		}
		if (m_menuDir != MENU_SHOP)
		{
			// �޴� ���°��� ������ �ƴϸ�
			// �κ��丮 ������ ������(���콺 ������)
			// ������ ���������� �����̵�������
			// �޴�â �޴� ������ ����
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


void playerMenu::menuUpdate()
{
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
			m_pShop->update();
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

			// �޴�â y�� ����
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