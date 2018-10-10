#pragma once

class inven;
class item;
class player;
#define MAXPAGE 3

class shop
{
private:
	image*	m_pWindow;	// 상점 ui창
	image*	m_pList;	// 아이템 list창
	image*	m_pLeft;	// 왼쪽방향키
	image*	m_pRight;	// 오른쪽방향키
	RECT m_LeftRc;		// 체크용 레프트, 라이트rc
	RECT m_RightRc;


	item*	m_pItem;

	inven*	m_pInven;
	player* m_pPlayer;

	map<int, item*> m_mapItem;	// 상점 판매리스트 담을 맵
	map<int, item*>::iterator m_iterItem;

	map<int, item*> m_mapInven;	// 인벤토리 정보 받아올 맵
	map<int, item*>::iterator m_iterInven;

	int	m_nWinX;	// 상점 윈도우창 xy
	int	m_nWinY;
	int m_nListX;	// 리스트창 x,y
	int m_nArrayListY[4];
	int m_nLeftX;			// 레프트버튼 좌표x
	int m_nLeftY;			// 레프트버튼 좌표y
	int m_nRightX;			// 라이트버튼 좌표x
	int m_nRightY;			// 라이트버튼 좌표x
	bool isMouseIn[2];		// 화살표 커지는 불값
	int m_nPage;			// 상점 페이지 리스트

	bool isHandItem;	// 마우스 클릭유무
	bool isBuy;			// 구입 상태
	bool isSell;		// 판매 상태

	void buyItem();		// 아이템 구입 함수
	void sellItem();	// 아이템 판매 함수
	void checkTrade();	// 구입,판매 유무 체크용 함수
	void setItem();		// 페이지별 판매아이템 셋팅

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setInven(inven* inven) { m_pInven = inven; }
	void getPlayer(player* player) { m_pPlayer = player; }
	shop();
	~shop();
};

