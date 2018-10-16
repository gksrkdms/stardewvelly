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
	// 툴팁표시 불값
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

	// 마우스정보 x,y
	m_nMouseX = g_ptMouse.x + 5;
	m_nMouseY2 = g_ptMouse.y + 5;

	// 툴팁에 들어가는 이름,종류,툴팁 x,y정보값
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

	// 아이템 렉트 믿 툴팁정보 렉트
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

	// 아이템이 있을떄
	if (isItemOn == true)
	{
		char str[128];
		// 기본 아이템 이미지 랜더
		m_pImg->render(hdc, m_nX + m_nIconX, m_nY + m_nIconY, 3);
		if (waterBar)
		{
			waterBar->render(hdc);
		}
		// 필드에서 도구류 외의 아이템을 선택했을때
		if (isPlayerHead == true && m_itemKind != ITEM_ACT && isPlayerPlaying == true)
		{
			// 플레이어 머리위에 아이템 랜더
			m_pImg->render(hdc, m_nPlayerX - CAMERA->getX() + 15, m_nPlayerY - CAMERA->getY() - 30, 4);
			// 플레이어 타일타겟지역 알파랜더
			m_pImg->alphaRenderScala(hdc, m_nMouseX, m_nMouseY2, 150, 3);

		}
		// 아이템이 2개 이상이거나 중첩가능한 아이템이면 갯수 출력
		if (m_nItemNum > 1 && isStackItem == true)
		{
			sprintf_s(str, 128, "%d", m_nItemNum);
			TextOut(hdc, m_nX + 45, m_nY + 45, str, strlen(str));
		}
	}
}

// 인벤토리메뉴, 상점인벤토리, 퀵바 툴팁용
void item::ToolTiprender(HDC hdc)
{
	char str[128];
	if (isItemOn == true)
	{
		if (isToolTip == true)
		{
			m_pToolTipImg->render(hdc, m_nMouseX + 10, m_nMouseY + 10);											// 툴팁 윈도우
			DrawText(hdc, m_ItemName.c_str(), strlen(m_ItemName.c_str()), &m_NameRc, DT_WORDBREAK);				// 아이템 이름
			DrawText(hdc, m_ItemKindName.c_str(), strlen(m_ItemKindName.c_str()), &m_KindRc, DT_WORDBREAK);		// 아이템 종류(도구,씨앗 등)
			DrawText(hdc, m_ItemToolTip.c_str(), strlen(m_ItemToolTip.c_str()), &m_ToolTipRc, DT_WORDBREAK);	// 아이템 상세내용
			// 아이템이 소모품이면 기력,체력 회복량 등 표시
			if (m_itemKind == ITEM_CONSUME)
			{
				m_pEnergy->render(hdc, m_nEnergyX, m_nEnergyY);
				m_pHp->render(hdc, m_nHpX, m_nHpY);
				sprintf_s(str, 128, "%d 기력", m_nEnergy);
				TextOut(hdc, m_nEnergyX + 60, m_nEnergyY + 10, str, strlen(str));
				sprintf_s(str, 128, "%d 체력", m_nHp);
				TextOut(hdc, m_nHpX + 60, m_nHpY + 10, str, strlen(str));
			}
			if (m_actItemKind == ACTITEM_SWORD)
			{
				m_pDmg->render(hdc, m_nEnergyX, m_nEnergyY);
				sprintf_s(str, 128, "%d-%d 피해", m_nMinDmg, m_nMaxDmg);
				TextOut(hdc, m_nEnergyX + 60, m_nEnergyY + 10, str, strlen(str));
			}
		}
	}
}

// 상점 리스트 랜더용 아이템이름, 가격 등
void item::ShopRender(HDC hdc, int nameX, int nameY, int moneyX, int moneyY)
{
	char str[128];
	sprintf_s(str, 128, "%s", m_ItemName.c_str());
	TextOut(hdc, nameX, nameY, str, strlen(str));
	sprintf_s(str, 128, "%d", itemPrice);
	TextOut(hdc, moneyX, moneyY, str, strlen(str));
}

// 상점용 인벤토리 랜더
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
		// 팔수없는 아이템은 알파값
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
			// 팔수 있으면 랜더, 및 상점용 툴팁 랜더(이름, 갯수, 판매가격)
			m_pImg->render(hdc, m_nX + m_nIconX, m_nY + m_nIconY, 3);
		}
	}
}

// 상점용 인벤토리 툴팁
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

// 외부에서 인벤토리에 아이템 추가할떄 쓰는 함수
// 매개변수 : 아이템번호, 같은아이템인지 확인용(겹쳐지면 중첩가능하게)
void item::getItem(int itemnum, bool sameItem)
{
	m_nItemId = itemnum;
	setItem(sameItem);	// 아이템 데이터 추가하는 함수
	isItemOn = true;
}

// 아이템 삭제용 함수
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

// 플레이어 머리위 좌표 받아오는 함수
void item::setPlayXY(int x, int y)
{
	m_nPlayerX = x;
	m_nPlayerY = y;
}

// 아이템 사용함수 (기능 미완성)
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

// 물뿌리개 내구도 깍이고 프로그래스바 함수호출하는 함수
void item::progressWaterDurability(int durability)
{
	m_nWaterDurability -= durability;
	waterBar->setGauge((float)m_nWaterDurability, (float)m_nMaxWaterDurability);
}

// 아이템 데이터 추가용 함수
void item::setItem(bool sameItem)
{
	// 같은 아이템이 있으면 수량만++
	if (sameItem == true)
	{
		m_nItemNum++;
	}
	else
	{
		// txt파일 로드하고 아이템 넘버 (item_001)등을 문서에서 찾아서 순서대로 읽는다.
		vector<string> vecData;
		vector<string>::iterator iterData;
		vector<string>::iterator iterData2;

		vecData = TXTDATA->txtLoad("image/Stardew Valley/item/itemData.txt");
		const char* itemName = "";
		// 받아온 아이템 번호로 문자열넣어줌
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
		// 문자열과 txt데이터의 데이터와 일치하면
		for (iterData = vecData.begin(); iterData != vecData.end(); iterData++)
		{
			if (*iterData == itemName)
			{
				iterData2 = iterData;
				break;
			}
		}

		// 해당백터로부터 ++로 돌면서 데이터 넣어줌
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
