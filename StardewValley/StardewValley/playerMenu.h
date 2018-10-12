#pragma once

class inven;
class shop;
class item;

#define ICONSCALA 4

enum MENUDIR
{
	MENU_INVEN,		// 인벤
	MENU_SKILL,		// 스킬
	MENU_RELATION,	// 관계
	MENU_MAP,		// 미니맵
	MENU_MAKING,	// 제작
	MENU_DICTIONARY,// 도감
	MENU_OPTION,	// 옵션
	MENU_EXIT,		// 종료
	MENU_SHOP		// 상점
};

class playerMenu
{
private:
	inven*	m_pInven;
	shop*	m_pShop;
	item*	m_pHand;
	PRIVATESYNTHESIZE(MENUDIR, m_menuDir, MenuDir);	// 메뉴 상태
	PRIVATESYNTHESIZE(bool, isMenu, Menu);			// 플레이어가 메뉴 호출할떄 불값
	image* m_pIcon[8];		// 메뉴 아이콘 이미지
	image* m_ptextBox;
	string m_Tooltip[8];	// 메뉴 아이콘 툴팁
	int m_nIconX[8];	// 메뉴 아이콘 x좌표 8개
	int m_nIconY[8];	// 메뉴 아이콘 y좌표 8개
	RECT m_IconRc[8];	// 메뉴 아이콘 렉트 8개
	bool isMouseIn[8];	// 메뉴 아이콘 불값 8개


	map<int, item*> m_mapItem;	// 인벤토리 크기 담아줄 맵
	map<int, item*>::iterator m_iterItem;

	void menuUpdate();

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void getPlayer(player* play);	// 상점한테 플레이어 정보 넘기는함수
	item* getQuickItem();			// 퀵바아이템 정보를 플레이어한테 정보를 넘기는 함수
	inven * getInven() { return m_pInven; }


	playerMenu();
	~playerMenu();
};

