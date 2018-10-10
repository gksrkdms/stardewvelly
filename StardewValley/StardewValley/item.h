#pragma once

enum ITEMKINDS
{
	ITEM_NULL,
	ITEM_ACT,
	ITEM_SEED,
	ITEM_CONSUME,
	ITEM_MATERIAL,
	ITEM_ETC
};

enum ACTITEMKINDS
{
	ACTITEM_NULL,
	ACTITEM_AXE,		//도끼
	ACTITEM_SPADE,		//괭이
	ACTITEM_WATER,		//물뿌리개
	ACTITEM_PICKAX,		//곡괭이
	ACTITEM_NOT,		//낫
	ACTITEM_FISHINGROD,	//낚싯대
	ACTITEM_SWORD		//검
};
enum CONSUMEKINDS
{
	CONITEM_NULL,
	CONITEM_RECOVERY,
	CONITEM_SEED
};

class item
{
private:
	PRIVATESYNTHESIZE(image*, m_pImg, Img);			//아이템 이미지
	PRIVATESYNTHESIZE(image*, m_pToolTipImg, ToolTipImg);			//툴팁 이미지
	PRIVATESYNTHESIZE(string, m_ItemName, Name);	// 아이템 이름
	PRIVATESYNTHESIZE(string, m_ItemKindName, ItemKindName);	// 아이템 종류
	PRIVATESYNTHESIZE(string, m_ItemToolTip, ItemToolTip);	// 아이템 툴팁
	PRIVATESYNTHESIZE(int, m_nItemId, ItemId);		// 아이템 id
	PRIVATESYNTHESIZE(int, m_nItemNum, ItemNum);	// 아이템 갯수
	PRIVATESYNTHESIZE(bool, isStackItem, StackItem);// 아이템 중첩 가능 유무
	PRIVATESYNTHESIZE(int, itemPrice, ItemPrice);	// 아이템 가격
	PRIVATESYNTHESIZE(bool, isSell, ItemSell);		// 아이템 판매 가능 유무
	PRIVATESYNTHESIZE(bool, isInvenOn, InvenOn);	// 인벤토리 추가칸 체크
	PRIVATESYNTHESIZE(bool, isItemOn, ItemOn);		// 인벤토리에 아이템이 있는지 체크
	PRIVATESYNTHESIZE(int, m_nIconX, IconX);		// 아이콘 좌표 x
	PRIVATESYNTHESIZE(int, m_nIconY, IconY);		// 아이콘 좌표 y
	PRIVATESYNTHESIZE(int, m_nX, X);				// 렉트 좌표 x
	PRIVATESYNTHESIZE(int, m_nY, Y);				// 렉트 좌표 y
	PRIVATESYNTHESIZE(int, m_nPlayerX, PlayerX);	// 받아올 플레이어 좌표 x
	PRIVATESYNTHESIZE(int, m_nPlayerY, PlayerY);	// 받아올 플레이어 좌표 y
	PRIVATESYNTHESIZE(RECT, m_rc, rect);			// 아이템 렉트
	PRIVATESYNTHESIZE(int, m_nRcSizeX, rcSizeX);		// 아이템 렉트사이즈x
	PRIVATESYNTHESIZE(int, m_nRcSizeY, rcSizeY);		// 아이템 렉트사이즈y
	PRIVATESYNTHESIZE(bool, isToolTip, ToolTip);		// 툴팁 불값
	PRIVATESYNTHESIZE(bool, isShopItem, ShopItem);		// 상점or인벤토리 불값
	PRIVATESYNTHESIZE(bool, isPlayerHead, PlayerHead);	// 플레이어 머리위 체크용 불값
	PRIVATESYNTHESIZE(bool, isPlayerPlaying, PlayerPlaying);	// 플레이어가 필드일떄 그려주는 체크 불값
	PRIVATESYNTHESIZE(ITEMKINDS, m_itemKind, ItemKind);					// 아이템 종류(액트,소비,재료,기타 등등)
	PRIVATESYNTHESIZE(ACTITEMKINDS, m_actItemKind, ActItemKind);		// 액트아이템 종류 (곡괭이, 괭이 삽, 물뿌리개 등등)
	PRIVATESYNTHESIZE(CONSUMEKINDS, m_consumItemKind, ConsumItemKind);	// 소모아이템 종류 (씨앗, 회복템 등등)
	PRIVATESYNTHESIZE(int, m_nWaterDurability, WaterDurability);		// 물뿌리개 내구도
	PRIVATESYNTHESIZE(int, m_nMaxWaterDurability, MaxWaterDurability);	// 물뿌리개 최대 내구도
	PRIVATESYNTHESIZE(int, m_nEnergy, Energy);		// 에너지 회복량
	PRIVATESYNTHESIZE(int, m_nHp, Hp);				// 체력 회복량

	int m_nMouseX;	// 마우스 받아올 xy
	PRIVATESYNTHESIZE(int, m_nMouseY, MouseY);
	int m_nMouseY2;
	int m_nNameX;	// 이름표시할 좌표 x
	int m_nNameY;	// 이름표시할 좌표 y
	int m_nKindX;	// 아이템 종류 좌표 x
	int m_nKindY;	// 아이템 종류 좌표 y
	int m_nToolTipX;	// 툴팁 x
	int m_nToolTipY;	// 툴팁 y
	int m_nEnergyX;	// 기력 x
	int m_nEnergyY;	// 기력 y
	int m_nHpX;	// 체력 x
	int m_nHpY;	// 체력 y
	RECT m_NameRc;		// DrawText용 렉트들 
	RECT m_KindRc;
	RECT m_ToolTipRc;
	image* m_pEnergy;	//에너지 그림
	image* m_pHp;		// 체력 그림
	image* m_pShopToolTip; // 상점용 인벤툴팁

	void setItem(bool sameItem);				// 받은 정보 아이템 세팅


public:
	HRESULT init(int x, int y, bool shop = false);
	void release();
	void update();
	void render(HDC hdc);
	void ToolTiprender(HDC hdc); // 인벤토리메뉴, 상점인벤토리 툴팁용
	void ShopRender(HDC hdc, int nameX, int nameY, int moneyX, int moneyY); // 상점 리스트 랜더용 아이템이름, 가격 등
	void ShopInvenRender(HDC hdc); // 상점용 인벤토리 랜더

	void getItem(int itemnum, bool sameItem);	// 넣어줄 아이템 번호 호출
	void deleteItem();			// 아이템 삭제
	void setPlayXY(int x, int y); // 플레이어 머리위 좌표 받아오는 함수
	void useItem(); // 아이템 사용함수 (기능 미완성)

	item();
	~item();
};

