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
	map<int, item*> m_mapItem;	// �κ��丮 ũ�� ����� ��
	map<int, item*>::iterator m_iterItem;

	item*	m_pHand;		// ���콺�� ���� ����������
	item*	m_pTempHand;	// ������ ���ҽ� ����� �ӽõ�����
	item*	m_pQuickItem;	// ���ٿ� ����� ����������

	image*	m_pSlot1;	// �κ��丮 ����123
	image*	m_pSlot2;
	image*	m_pSlot3;
	image*	m_pInvenBG;	// �κ��丮 ���
	image*	m_pUiBG;	// ui ���
	image*	m_pNumber;	// ���� �ѹ�
	image*	m_pTarget;	// ���� Ÿ�� �̹���(������ �׸�)

	int	m_nSlotX;	//�κ��丮 ����x,y��ǥ
	int	m_nSlot1Y;
	int	m_nSlot2Y;
	int	m_nSlot3Y;

	int m_nBgX;	// �κ��丮 ��� xy��ǥ
	int m_nBgY;

	int m_nUiX;	// ui xy��ǥ
	int m_nUiY;

	int m_nQuickNum;	// ���� �ѹ�

	int		m_nInvenSize;	// �κ��丮 ���� ����ĭ 1��x12
	bool	isAddSize;		// �κ��丮ĭ Ȯ��� üũ��
	bool	isHandItem;		// ���콺�� ������ �������� ����
	PRIVATESYNTHESIZE(INVENDIR, m_invenDir, InvenDir); // �κ��丮 Ȱ��ȭ ����
	PRIVATESYNTHESIZE(bool, isUiDown, UiDown); // ȭ�� ���¿����� ui ���Ʒ� üũ
	PRIVATESYNTHESIZE(bool, isLbutton, Lbutton); // ���콺 ����Ŭ�� �켱���� �Ұ�

	void InvenTohand();					// ��Ŭ�� �κ��丮->��
	void handToInven();					// ��Ŭ�� ��->�κ��丮

	void InvenTohandSwap(int itemnum);	// �κ��丮->�� �����ͽ���
	void handToInvenSwap(int itemnum);	// ��->�κ��丮 �����ͽ���
	void handToTempSwap();				// ��->����
	void tempToInvenSwap(int itemnum);	// ����->�κ�
	void InvenToTempSwap(int itemnum);	// �κ�->����

	void InvenToInvenSwap(int itemnum1, int itemnum2);	// �κ�->�κ�

	void dataSwap(item* item1, item* item2);			// ���ҿ� �Լ�

	void setDir();		// dir�� ����
	void setQuickItem();
	void setClickQuickItem();
	void setClickShopItem();
	void setKey();		// Ű ����


public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addItem(int itemnum);			// �κ��丮�� ������ �߰�
	void invenAdd();					// �κ��丮 Ȯ�� �Լ�
	void sortInven();					// �κ��丮 ����

	bool getHandItem() { return isHandItem; }			// �տ��ִ� ���� ������ ���ͼ���
	void setHandItem(bool hand) { isHandItem = hand; }

	map<int, item*> getInvenMap() { return m_mapItem; }	// �κ��丮 map ����
	item* getQuickItem() { return m_pQuickItem; }		// ���پ����� ����
	inven();
	~inven();
};

