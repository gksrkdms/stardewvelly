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

	// 상점도 아이템 객체 4개생성후 map에 담아줌
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
			SOUNDMANAGER->play("sound/effect/돈소리.wav", g_soundVolume.effect);
		}
		if (isSell == true)
		{
			sellItem();
			SOUNDMANAGER->play("sound/effect/돈소리.wav", g_soundVolume.effect);
		}
	}
	setItem();
}

void shop::render(HDC hdc)
{
	// 상점 배경창 및 리스트 ui랜더
	m_pWindow->render(hdc, m_nWinX, m_nWinY);
	for (int i = 0; i < 4; i++)
	{
		m_pList->render(hdc, m_nListX, m_nArrayListY[i]);
	}
	// 골드 ui 랜더
	m_pGoldUi->render(hdc, m_nWinX, m_pWindow->getHeight() + 20);
	m_pPlayer->numRender(hdc, m_nWinX + m_pGoldUi->getWidth() / 2 - 18, m_pWindow->getHeight() + 44);

	// 상점 화살표 랜더
	if (isMouseIn[0] == true)
		m_pLeft->floatRender(hdc, m_nLeftX, m_nLeftY, 0, 0, m_pLeft->getWidth(), m_pLeft->getHeight(), 1.2f);
	else
		m_pLeft->floatRender(hdc, m_nLeftX, m_nLeftY, 0, 0, m_pLeft->getWidth(), m_pLeft->getHeight(), 1.0f);
	if (isMouseIn[1] == true)
		m_pRight->floatRender(hdc, m_nRightX, m_nRightY, 0, 0, m_pRight->getWidth(), m_pRight->getHeight(), 1.2f);
	else
		m_pRight->floatRender(hdc, m_nRightX, m_nRightY, 0, 0, m_pRight->getWidth(), m_pRight->getHeight(), 1.0f);
	// 인벤토리 및 툴팁 랜더
	for (m_iterInven = m_mapInven.begin(); m_iterInven != m_mapInven.end(); m_iterInven++)
	{
		m_iterInven->second->ShopInvenRender(hdc);
	}
	for (m_iterInven = m_mapInven.begin(); m_iterInven != m_mapInven.end(); m_iterInven++)
	{
		m_iterInven->second->ShopInvenToolTip(hdc);
	}
	// 상점아이템 랜더 및 툴팁랜더
	for (int i = 0; i < 4; i++)
	{
		m_iterItem = m_mapItem.find(i);
		if (m_iterItem->second->getItemOn() == true)
		{
			// 이미지랜더
			m_iterItem->second->render(hdc);
			// 이름, 돈 랜더
			m_iterItem->second->ShopRender(hdc, m_nListX + 100, m_nArrayListY[i] + 35, m_nListX + 950, m_nArrayListY[i] + 35);
			// 상점 툴팁랜더
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

// 아이템 구입
void shop::buyItem()
{
	bool onItem = false;
	map<int, item*>::iterator iterItem;
	map<int, item*>::iterator iterInven;
	m_mapInven = m_pInven->getInvenMap();

	// 상점 아이템리스트 검색
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

	// 인벤토리에 똑같은 아이템이 있는지 확인
	for (m_iterInven = m_mapInven.begin(); m_iterInven != m_mapInven.end(); m_iterInven++)
	{
		if (m_iterInven->second->getInvenOn() == true &&							// 인벤토리가 남았는지
			m_iterInven->second->getItemId() == iterItem->second->getItemId() &&	// 구입할려는 아이템이 인벤토리에도 있는지
			m_iterInven->second->getStackItem() == true &&							// 해당 아이템이 중첩이 가능한지
			m_iterInven->second->getItemNum() < MAXITEM)							// 중첩이가능하면 중첩이 최대치가 아닌지
		{
			onItem = true;
			iterInven = m_iterInven;
			break;
		}
	}
	// 인벤토리에 똑같은 아이템이 있을떄
	if (onItem == true && m_pPlayer->getMoney() >= iterItem->second->getItemPrice())
	{
		m_pPlayer->setMoney(m_pPlayer->getMoney() - iterItem->second->getItemPrice());	// 플레이어 소지금액 차감
		iterInven->second->getItem(iterItem->second->getItemId(), onItem);				// 인벤토리에 아이템넣어줌(중첩가능하게)
	}
	// 인벤토리에 똑같은 아이템이 없을떄 or 수량이 꽉찼을떄
	else
	{
		for (m_iterInven = m_mapInven.begin(); m_iterInven != m_mapInven.end(); m_iterInven++)
		{
			if (m_pPlayer->getMoney() >= iterItem->second->getItemPrice() &&	// 소지금이 구입금액보다 큰지
				m_iterInven->second->getInvenOn() == true &&					// 인벤토리 추가칸 여유있는지
				m_iterInven->second->getItemOn() == false)						// 인벤토리가 여유있는지 확인
			{
				m_pPlayer->setMoney(m_pPlayer->getMoney() - iterItem->second->getItemPrice());	// 플레이어 소지금액 차감
				m_iterInven->second->getItem(iterItem->second->getItemId(), onItem);			// 인벤토리에 새로운 칸에 아이템넣어줌
				return;
			}
		}
	}
}

// 아아템 판매
void shop::sellItem()
{
	m_mapInven = m_pInven->getInvenMap();
	for (m_iterInven = m_mapInven.begin(); m_iterInven != m_mapInven.end(); m_iterInven++)
	{
		if (m_iterInven->second->getShopItem() == false &&	// 아이템이 상점용인지
			m_iterInven->second->getItemOn() == true &&		// 아이템이 있는지
			m_iterInven->second->getItemSell() == true &&	// 아이템이 판매가능한지
			m_iterInven->second->getInvenOn())				// 해당 인벤토리가 활성화됬는지
		{
			if (PtInRect(&m_iterInven->second->getrect(), g_ptMouse))
			{
				// 아이템이 1개이상일떄
				if (m_iterInven->second->getItemNum() > 1)
				{
					m_pPlayer->setMoney(m_pPlayer->getMoney() + m_iterInven->second->getItemPrice() / 2);
					m_iterInven->second->setItemNum(m_iterInven->second->getItemNum() - 1);
				}
				// 아이템이 1개일떄
				else if (m_iterInven->second->getItemNum() <= 1)
				{
					m_pPlayer->setMoney(m_pPlayer->getMoney() + m_iterInven->second->getItemPrice() / 2);
					m_iterInven->second->deleteItem();
				}

			}
		}
	}

}

// 인벤토리와 상점의 렉트 마우스체크후
// 마우스 R버튼 활성화를위해 체크해줌
void shop::checkTrade()
{
	// 상점아이템 리스트에 아이템이 존재할때 true
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
	// 인벤토리에 아이템이 있는지 검사하고 true로해줌
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

// 상점 페이지 상태에따라서 아이템 리스트변경함
void shop::setItem()
{
	// 레프트 라이트 화살표역시 마우스 L클릭 사용하기위해 체크함
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
				SOUNDMANAGER->play("sound/effect/선택음1.wav", g_soundVolume.effect);
				isOnceSetItem = true;
			}
			else
			{
				m_nPage--;
				SOUNDMANAGER->play("sound/effect/선택음1.wav", g_soundVolume.effect);
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
				SOUNDMANAGER->play("sound/effect/선택음1.wav", g_soundVolume.effect);
				isOnceSetItem = true;
			}
			else
			{
				m_nPage++;
				SOUNDMANAGER->play("sound/effect/선택음1.wav", g_soundVolume.effect);
				isOnceSetItem = true;
			}
		}
	}
	int i = 0;

	// 페이지 번호에따라서 아이템교체함
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
			m_iterItem = m_mapItem.find(2);   //@@@ 내가 추가
			m_iterItem->second->getItem(501, false);
			m_iterItem = m_mapItem.find(3);   //@@@ 내가 추가
			m_iterItem->second->getItem(502, false);
		
			isOnceSetItem = false;
			break;
		}
	}
}
