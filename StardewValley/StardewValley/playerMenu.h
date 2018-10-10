#pragma once

class inven;
class shop;
class item;

enum MENUDIR
{
	MENU_INVEN,		// �κ�
	MENU_SHOP,		// ����
	MENU_SKILL,		// ��ų
	MENU_RELATION,	// ����
	MENU_MAP,		// �̴ϸ�
	MENU_MAKING,	// ����
	MENU_DICTIONARY,// ����
	MENU_OPTION,	// �ɼ�
	MENU_EXIT		// ����
};

class playerMenu
{
private:
	inven*	m_pInven;
	shop*	m_pShop;
	item*	m_pHand;
	PRIVATESYNTHESIZE(MENUDIR, m_menuDir, MenuDir);	// �޴� ����
	PRIVATESYNTHESIZE(bool, isMenu, Menu);			// �÷��̾ �޴� ȣ���ҋ� �Ұ�

	map<int, item*> m_mapItem;	// �κ��丮 ũ�� ����� ��
	map<int, item*>::iterator m_iterItem;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void getPlayer(player* play);	// �������� �÷��̾� ���� �ѱ���Լ�
	item* getQuickItem();			// ���پ����� ������ �÷��̾����� ������ �ѱ�� �Լ�

	playerMenu();
	~playerMenu();
};

