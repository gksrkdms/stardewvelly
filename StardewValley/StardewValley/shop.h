#pragma once

class inven;
class item;
class player;
#define MAXPAGE 3

class shop
{
private:
	image*	m_pWindow;	// ���� uiâ
	image*	m_pList;	// ������ listâ
	image*	m_pLeft;	// ���ʹ���Ű
	image*	m_pRight;	// �����ʹ���Ű
	RECT m_LeftRc;		// üũ�� ����Ʈ, ����Ʈrc
	RECT m_RightRc;


	item*	m_pItem;

	inven*	m_pInven;
	player* m_pPlayer;

	map<int, item*> m_mapItem;	// ���� �ǸŸ���Ʈ ���� ��
	map<int, item*>::iterator m_iterItem;

	map<int, item*> m_mapInven;	// �κ��丮 ���� �޾ƿ� ��
	map<int, item*>::iterator m_iterInven;

	int	m_nWinX;	// ���� ������â xy
	int	m_nWinY;
	int m_nListX;	// ����Ʈâ x,y
	int m_nArrayListY[4];
	int m_nLeftX;			// ����Ʈ��ư ��ǥx
	int m_nLeftY;			// ����Ʈ��ư ��ǥy
	int m_nRightX;			// ����Ʈ��ư ��ǥx
	int m_nRightY;			// ����Ʈ��ư ��ǥx
	bool isMouseIn[2];		// ȭ��ǥ Ŀ���� �Ұ�
	int m_nPage;			// ���� ������ ����Ʈ

	bool isHandItem;	// ���콺 Ŭ������
	bool isBuy;			// ���� ����
	bool isSell;		// �Ǹ� ����

	void buyItem();		// ������ ���� �Լ�
	void sellItem();	// ������ �Ǹ� �Լ�
	void checkTrade();	// ����,�Ǹ� ���� üũ�� �Լ�
	void setItem();		// �������� �Ǹž����� ����

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

