#include "stdafx.h"
#include "item.h"
#include "progressBar.h"

HRESULT item::init(int x, int y, bool shop)
{
	//memset(this, NULL, sizeof(*this));

	m_pToolTipImg = IMAGEMANAGER->findImage("textBox");
	m_pEnergy = IMAGEMANAGER->findImage("recovery_energy");
	m_pHp = IMAGEMANAGER->findImage("recovery_hp");
	m_pShopToolTip = IMAGEMANAGER->findImage("shop_textBox");
	m_pDmg = IMAGEMANAGER->findImage("dmg");
	m_pImg = NULL;
	m_ItemName = "";
	m_ItemToolTip = "";
	m_nItemId = 0;
	m_nItemNum = 0;
	isStackItem = false;
	itemPrice = 0;
	isSell = false;
	isInvenOn = false;
	isItemOn = false;
	m_nIconX = 4;
	m_nIconY = 4;
	m_nX = x;
	m_nY = y;
	m_nPlayerX = 0;
	m_nPlayerY = 0;
	m_nRcSizeX = 58;
	m_nRcSizeY = 58;
	m_rc = RectMake(m_nX, m_nY, m_nRcSizeX, m_nRcSizeY);
	isToolTip = false;
	isShopItem = shop;
	isPlayerHead = false;
	isPlayerPlaying = true;

	m_nMouseX = 0;
	m_nMouseY = 0;

	m_itemKind = ITEM_NULL;
	m_actItemKind = ACTITEM_NULL;
	m_consumItemKind = CONITEM_NULL;
	m_nWaterDurability = 0;
	m_nMaxWaterDurability = 0;
	m_nEnergy = 0;
	m_nHp = 0;
	m_nMinDmg = 0;
	m_nMaxDmg = 0;
	waterBar = NULL;
	return S_OK;
}

void item::release()
{
}

void item::update()
{
	// ����ǥ�� �Ұ�
	if (isItemOn == true)
	{
		if (PtInRect(&m_rc, g_ptMouse))
		{
			isToolTip = true;
		}
		else
		{
			isToolTip = false;
		}
	}

	// ���콺���� x,y
	m_nMouseX = g_ptMouse.x + 5;
	m_nMouseY2 = g_ptMouse.y + 5;

	// ������ ���� �̸�,����,���� x,y������
	m_nNameX = m_nMouseX + 25;
	m_nNameY = m_nMouseY + 30;
	m_nKindX = m_nMouseX + 25;
	m_nKindY = m_nMouseY + 60;
	m_nToolTipX = m_nMouseX + 25;
	m_nToolTipY = m_nMouseY + 120;
	m_nEnergyX = m_nMouseX + 25;
	m_nEnergyY = m_nMouseY + 180;
	m_nHpX = m_nMouseX + 25;
	m_nHpY = m_nMouseY + 230;

	// ������ ��Ʈ �� �������� ��Ʈ
	m_rc = RectMake(m_nX, m_nY, m_nRcSizeX, m_nRcSizeY);
	m_NameRc = RectMake(m_nNameX, m_nNameY, 281, 200);
	m_KindRc = RectMake(m_nKindX, m_nKindY, 281, 200);
	m_ToolTipRc = RectMake(m_nToolTipX, m_nToolTipY, 281, 200);

	if (waterBar)
	{
		waterBar->setX(m_nX);
		waterBar->setY(m_nY + 40);
	}
}

void item::render(HDC hdc)
{
	//MakeRect(hdc, m_rc);

	// �������� ������
	if (isItemOn == true)
	{
		char str[128];
		// �⺻ ������ �̹��� ����
		m_pImg->render(hdc, m_nX + m_nIconX, m_nY + m_nIconY, 3);
		if (waterBar)
		{
			waterBar->render(hdc);
		}
		// �ʵ忡�� ������ ���� �������� ����������
		if (isPlayerHead == true && m_itemKind != ITEM_ACT && isPlayerPlaying == true)
		{
			// �÷��̾� �Ӹ����� ������ ����
			m_pImg->render(hdc, m_nPlayerX - CAMERA->getX() + 15, m_nPlayerY - CAMERA->getY() - 30, 4);
			// �÷��̾� Ÿ��Ÿ������ ���ķ���
			m_pImg->alphaRenderScala(hdc, m_nMouseX, m_nMouseY2, 150, 3);

		}
		// �������� 2�� �̻��̰ų� ��ø������ �������̸� ���� ���
		if (m_nItemNum > 1 && isStackItem == true)
		{
			sprintf_s(str, 128, "%d", m_nItemNum);
			TextOut(hdc, m_nX + 45, m_nY + 45, str, strlen(str));
		}
	}
}

// �κ��丮�޴�, �����κ��丮, ���� ������
void item::ToolTiprender(HDC hdc)
{
	char str[128];
	if (isItemOn == true)
	{
		if (isToolTip == true)
		{
			m_pToolTipImg->render(hdc, m_nMouseX + 10, m_nMouseY + 10);											// ���� ������
			DrawText(hdc, m_ItemName.c_str(), strlen(m_ItemName.c_str()), &m_NameRc, DT_WORDBREAK);				// ������ �̸�
			DrawText(hdc, m_ItemKindName.c_str(), strlen(m_ItemKindName.c_str()), &m_KindRc, DT_WORDBREAK);		// ������ ����(����,���� ��)
			DrawText(hdc, m_ItemToolTip.c_str(), strlen(m_ItemToolTip.c_str()), &m_ToolTipRc, DT_WORDBREAK);	// ������ �󼼳���
			// �������� �Ҹ�ǰ�̸� ���,ü�� ȸ���� �� ǥ��
			if (m_itemKind == ITEM_CONSUME)
			{
				m_pEnergy->render(hdc, m_nEnergyX, m_nEnergyY);
				m_pHp->render(hdc, m_nHpX, m_nHpY);
				sprintf_s(str, 128, "%d ���", m_nEnergy);
				TextOut(hdc, m_nEnergyX + 60, m_nEnergyY + 10, str, strlen(str));
				sprintf_s(str, 128, "%d ü��", m_nHp);
				TextOut(hdc, m_nHpX + 60, m_nHpY + 10, str, strlen(str));
			}
			if (m_actItemKind == ACTITEM_SWORD)
			{
				m_pDmg->render(hdc, m_nEnergyX, m_nEnergyY);
				sprintf_s(str, 128, "%d-%d ����", m_nMinDmg, m_nMaxDmg);
				TextOut(hdc, m_nEnergyX + 60, m_nEnergyY + 10, str, strlen(str));
			}
		}
	}
}

// ���� ����Ʈ ������ �������̸�, ���� ��
void item::ShopRender(HDC hdc, int nameX, int nameY, int moneyX, int moneyY)
{
	char str[128];
	sprintf_s(str, 128, "%s", m_ItemName.c_str());
	TextOut(hdc, nameX, nameY, str, strlen(str));
	sprintf_s(str, 128, "%d", itemPrice);
	TextOut(hdc, moneyX, moneyY, str, strlen(str));
}

// ������ �κ��丮 ����
void item::ShopInvenRender(HDC hdc)
{
	char str[128];
	if (isItemOn == true)
	{
		if (m_nItemNum > 1 && isStackItem == true)
		{
			sprintf_s(str, 128, "%d", m_nItemNum);
			TextOut(hdc, m_nX + 45, m_nY + 45, str, strlen(str));
		}
		// �ȼ����� �������� ���İ�
		if (isSell == false)
		{
			m_pImg->alphaRenderScala(hdc, m_nX + m_nIconX, m_nY + m_nIconY, 150, 3);
			if (waterBar)
			{
				waterBar->alphaRender(hdc);
			}
		}
		else
		{
			// �ȼ� ������ ����, �� ������ ���� ����(�̸�, ����, �ǸŰ���)
			m_pImg->render(hdc, m_nX + m_nIconX, m_nY + m_nIconY, 3);
		}
	}
}

// ������ �κ��丮 ����
void item::ShopInvenToolTip(HDC hdc)
{
	char str[128];
	if (isSell == true && isItemOn == true && isToolTip == true)
	{
		m_pShopToolTip->render(hdc, m_nMouseX + 10, m_nMouseY + 10);
		sprintf_s(str, 128, "%s", m_ItemName.c_str());
		TextOut(hdc, m_nMouseX + 30, m_nMouseY + 30, str, strlen(str));
		sprintf_s(str, 128, "%d", m_nItemNum);
		TextOut(hdc, m_nMouseX + 180, m_nMouseY + 35, str, strlen(str));
		sprintf_s(str, 128, "%d", itemPrice / 2);
		TextOut(hdc, m_nMouseX + 30, m_nMouseY + 65, str, strlen(str));
	}
}

item::item()
{
}


item::~item()
{
}

// �ܺο��� �κ��丮�� ������ �߰��ҋ� ���� �Լ�
// �Ű����� : �����۹�ȣ, �������������� Ȯ�ο�(�������� ��ø�����ϰ�)
void item::getItem(int itemnum, bool sameItem)
{
	m_nItemId = itemnum;
	setItem(sameItem);	// ������ ������ �߰��ϴ� �Լ�
	isItemOn = true;
}

// ������ ������ �Լ�
void item::deleteItem()
{
	m_pImg = NULL;
	m_ItemName = "";
	m_ItemKindName = "";
	m_ItemToolTip = "";
	m_nItemId = 0;
	isStackItem = false;
	isSell = false;
	itemPrice = 0;

	m_itemKind = ITEM_NULL;
	m_actItemKind = ACTITEM_NULL;
	m_consumItemKind = CONITEM_NULL;

	m_nWaterDurability = 0;
	m_nMaxWaterDurability = 0;
	m_nEnergy = 0;
	m_nHp = 0;
	m_nMinDmg = 0;
	m_nMaxDmg = 0;
	waterBar = NULL;

	m_nItemNum = 0;
	isItemOn = false;
}

// �÷��̾� �Ӹ��� ��ǥ �޾ƿ��� �Լ�
void item::setPlayXY(int x, int y)
{
	m_nPlayerX = x;
	m_nPlayerY = y;
}

// ������ ����Լ� (��� �̿ϼ�)
void item::useItem()
{
	if (m_nItemNum > 1)
	{
		m_nItemNum--;
	}
	else if (m_nItemNum == 1)
	{
		deleteItem();
	}
}

// ���Ѹ��� ������ ���̰� ���α׷����� �Լ�ȣ���ϴ� �Լ�
void item::progressWaterDurability(int durability)
{
	m_nWaterDurability -= durability;
	waterBar->setGauge((float)m_nWaterDurability, (float)m_nMaxWaterDurability);
}

// ������ ������ �߰��� �Լ�
void item::setItem(bool sameItem)
{
	// ���� �������� ������ ������++
	if (sameItem == true)
	{
		m_nItemNum++;
	}
	else
	{
		// txt���� �ε��ϰ� ������ �ѹ� (item_001)���� �������� ã�Ƽ� ������� �д´�.
		vector<string> vecData;
		vector<string>::iterator iterData;
		vector<string>::iterator iterData2;

		vecData = TXTDATA->txtLoad("image/Stardew Valley/item/itemData.txt");
		const char* itemName = "";
		// �޾ƿ� ������ ��ȣ�� ���ڿ��־���
		switch (m_nItemId)
		{
		case 1:
			itemName = "item_001";
			break;
		case 2:
			itemName = "item_002";
			break;
		case 3:
			itemName = "item_003";
			break;
		case 4:
			itemName = "item_004";
			break;
		case 5:
			itemName = "item_005";
			break;
		case 6:
			itemName = "item_006";
			break;
		case 7:
			itemName = "item_007";
			break;
		case 101:
			itemName = "item_101";
			break;
		case 102:
			itemName = "item_102";
			break;
		case 103:
			itemName = "item_103";
			break;
		case 104:
			itemName = "item_104";
			break;
		case 105:
			itemName = "item_105";
			break;
		case 201:
			itemName = "item_201";
			break;
		case 202:
			itemName = "item_202";
			break;
		case 203:
			itemName = "item_203";
			break;
		case 204:
			itemName = "item_204";
			break;
		case 205:
			itemName = "item_205";
			break;
		case 206:
			itemName = "item_206";
			break;
		case 207:
			itemName = "item_207";
			break;
		case 208:
			itemName = "item_208";
			break;
		case 209:
			itemName = "item_209";
			break;
		default:
			return;
			break;
		}
		// ���ڿ��� txt�������� �����Ϳ� ��ġ�ϸ�
		for (iterData = vecData.begin(); iterData != vecData.end(); iterData++)
		{
			if (*iterData == itemName)
			{
				iterData2 = iterData;
				break;
			}
		}

		// �ش���ͷκ��� ++�� ���鼭 ������ �־���
		m_pImg = IMAGEMANAGER->findImage(*iterData2++);
		m_ItemName = *iterData2++;
		m_ItemKindName = *iterData2++;
		m_ItemToolTip = *iterData2++;
		isStackItem = atoi((*iterData2++).c_str());
		isSell = atoi((*iterData2++).c_str());
		itemPrice = atoi((*iterData2++).c_str());
		m_itemKind = (ITEMKINDS)atoi((*iterData2++).c_str());
		m_actItemKind = (ACTITEMKINDS)atoi((*iterData2++).c_str());
		m_consumItemKind = (CONSUMEKINDS)atoi((*iterData2++).c_str());
		m_nWaterDurability = m_nMaxWaterDurability = atoi((*iterData2++).c_str());
		m_nEnergy = atoi((*iterData2++).c_str());
		m_nHp = atoi((*iterData2++).c_str());
		m_nMinDmg = atoi((*iterData2++).c_str());
		m_nMaxDmg = atoi((*iterData2++).c_str());
		m_nItemNum++;

		if (m_actItemKind == ACTITEM_WATER)
		{
			waterBar = new progressBar;
			waterBar->init((float)m_nX, (float)m_nY + 40, 48, 8);
		}
	}
}
