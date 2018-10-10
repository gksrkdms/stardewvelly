#pragma once
class item;

#define INVENSIZE 36
#define MAXITEM 3

enum INVENDIR
{
	INVEN_QUICKBAR,
	INVEN_INVEN,
	INVEN_MAKE,
	INVEN_SHOP
};


class inven
{
private:
	HWND	m_hBtnSave;
	map<int, item*> m_mapItem;	// 인벤토리 크기 담아줄 맵
	map<int, item*>::iterator m_iterItem;

	item*	m_pHand;		// 마우스로 집은 아이템정보
	item*	m_pTempHand;	// 아이템 스왑시 담아줄 임시데이터
	item*	m_pQuickItem;	// 퀵바에 담아줄 아이템정보

	image*	m_pSlot1;	// 인벤토리 슬롯123
	image*	m_pSlot2;
	image*	m_pSlot3;
	image*	m_pInvenBG;	// 인벤토리 배경
	image*	m_pUiBG;	// ui 배경
	image*	m_pNumber;	// 퀵바 넘버
	image*	m_pTarget;	// 퀵바 타겟 이미지(빨간색 네모)

	int	m_nSlotX;	//인벤토리 슬롯x,y좌표
	int	m_nSlot1Y;
	int	m_nSlot2Y;
	int	m_nSlot3Y;

	int m_nBgX;	// 인벤토리 배경 xy좌표
	int m_nBgY;

	int m_nUiX;	// ui xy좌표
	int m_nUiY;

	int m_nQuickNum;	// 퀵바 넘버

	int		m_nInvenSize;	// 인벤토리 현재 가방칸 1당x12
	bool	isAddSize;		// 인벤토리칸 확장시 체크용
	bool	isHandItem;		// 마우스로 아이템 집었는지 유무
	PRIVATESYNTHESIZE(INVENDIR, m_invenDir, InvenDir); // 인벤토리 활성화 상태
	PRIVATESYNTHESIZE(bool, isUiDown, UiDown); // 화면 상태에따라서 ui 위아래 체크
	PRIVATESYNTHESIZE(bool, isLbutton, Lbutton); // 마우스 왼쪽클릭 우선순위 불값

	void InvenTohand();					// 좌클릭 인벤토리->손
	void handToInven();					// 좌클릭 손->인벤토리

	void InvenTohandSwap(int itemnum);	// 인벤토리->손 데이터스왑
	void handToInvenSwap(int itemnum);	// 손->인벤토리 데이터스왑
	void handToTempSwap();				// 손->템프
	void tempToInvenSwap(int itemnum);	// 템프->인벤
	void InvenToTempSwap(int itemnum);	// 인벤->템프

	void InvenToInvenSwap(int itemnum1, int itemnum2);	// 인벤->인벤

	void dataSwap(item* item1, item* item2);			// 스왑용 함수

	void setDir();		// dir값 셋팅
	void setQuickItem();
	void setClickQuickItem();
	void setClickShopItem();
	void setKey();		// 키 셋팅


public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addItem(int itemnum);			// 인벤토리에 아이템 추가
	void invenAdd();					// 인벤토리 확장 함수
	void sortInven();					// 인벤토리 정렬

	bool getHandItem() { return isHandItem; }			// 손에있는 정보 아이템 겟터셋터
	void setHandItem(bool hand) { isHandItem = hand; }

	map<int, item*> getInvenMap() { return m_mapItem; }	// 인벤토리 map 겟터
	item* getQuickItem() { return m_pQuickItem; }		// 퀵바아이템 겟터
	inven();
	~inven();
};

