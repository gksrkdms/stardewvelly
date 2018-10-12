#pragma once

class inven;
class shop;
class item;

#define ICONSCALA 4

enum MENUDIR
{
	MENU_INVEN,		// �κ�
	MENU_SKILL,		// ��ų
	MENU_RELATION,	// ����
	MENU_MAP,		// �̴ϸ�
	MENU_MAKING,	// ����
	MENU_DICTIONARY,// ����
	MENU_OPTION,	// �ɼ�
	MENU_EXIT,		// ����
	MENU_SHOP		// ����
};

class playerMenu
{
private:
	inven*	m_pInven;
	shop*	m_pShop;
	item*	m_pHand;
	PRIVATESYNTHESIZE(MENUDIR, m_menuDir, MenuDir);	// �޴� ����
	PRIVATESYNTHESIZE(bool, isMenu, Menu);			// �÷��̾ �޴� ȣ���ҋ� �Ұ�
	image* m_pIcon[8];		// �޴� ������ �̹���
	image* m_ptextBox;
	string m_Tooltip[8];	// �޴� ������ ����
	int m_nIconX[8];	// �޴� ������ x��ǥ 8��
	int m_nIconY[8];	// �޴� ������ y��ǥ 8��
	RECT m_IconRc[8];	// �޴� ������ ��Ʈ 8��
	bool isMouseIn[8];	// �޴� ������ �Ұ� 8��


	map<int, item*> m_mapItem;	// �κ��丮 ũ�� ����� ��
	map<int, item*>::iterator m_iterItem;

	void menuUpdate();

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void getPlayer(player* play);	// �������� �÷��̾� ���� �ѱ���Լ�
	item* getQuickItem();			// ���پ����� ������ �÷��̾����� ������ �ѱ�� �Լ�
	inven * getInven() { return m_pInven; }


	playerMenu();
	~playerMenu();
};

