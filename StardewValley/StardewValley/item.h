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
	ACTITEM_AXE,		//����
	ACTITEM_SPADE,		//����
	ACTITEM_WATER,		//���Ѹ���
	ACTITEM_PICKAX,		//���
	ACTITEM_NOT,		//��
	ACTITEM_FISHINGROD,	//���˴�
	ACTITEM_SWORD		//��
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
	PRIVATESYNTHESIZE(image*, m_pImg, Img);			//������ �̹���
	PRIVATESYNTHESIZE(image*, m_pToolTipImg, ToolTipImg);			//���� �̹���
	PRIVATESYNTHESIZE(string, m_ItemName, Name);	// ������ �̸�
	PRIVATESYNTHESIZE(string, m_ItemKindName, ItemKindName);	// ������ ����
	PRIVATESYNTHESIZE(string, m_ItemToolTip, ItemToolTip);	// ������ ����
	PRIVATESYNTHESIZE(int, m_nItemId, ItemId);		// ������ id
	PRIVATESYNTHESIZE(int, m_nItemNum, ItemNum);	// ������ ����
	PRIVATESYNTHESIZE(bool, isStackItem, StackItem);// ������ ��ø ���� ����
	PRIVATESYNTHESIZE(int, itemPrice, ItemPrice);	// ������ ����
	PRIVATESYNTHESIZE(bool, isSell, ItemSell);		// ������ �Ǹ� ���� ����
	PRIVATESYNTHESIZE(bool, isInvenOn, InvenOn);	// �κ��丮 �߰�ĭ üũ
	PRIVATESYNTHESIZE(bool, isItemOn, ItemOn);		// �κ��丮�� �������� �ִ��� üũ
	PRIVATESYNTHESIZE(int, m_nIconX, IconX);		// ������ ��ǥ x
	PRIVATESYNTHESIZE(int, m_nIconY, IconY);		// ������ ��ǥ y
	PRIVATESYNTHESIZE(int, m_nX, X);				// ��Ʈ ��ǥ x
	PRIVATESYNTHESIZE(int, m_nY, Y);				// ��Ʈ ��ǥ y
	PRIVATESYNTHESIZE(int, m_nPlayerX, PlayerX);	// �޾ƿ� �÷��̾� ��ǥ x
	PRIVATESYNTHESIZE(int, m_nPlayerY, PlayerY);	// �޾ƿ� �÷��̾� ��ǥ y
	PRIVATESYNTHESIZE(RECT, m_rc, rect);			// ������ ��Ʈ
	PRIVATESYNTHESIZE(int, m_nRcSizeX, rcSizeX);		// ������ ��Ʈ������x
	PRIVATESYNTHESIZE(int, m_nRcSizeY, rcSizeY);		// ������ ��Ʈ������y
	PRIVATESYNTHESIZE(bool, isToolTip, ToolTip);		// ���� �Ұ�
	PRIVATESYNTHESIZE(bool, isShopItem, ShopItem);		// ����or�κ��丮 �Ұ�
	PRIVATESYNTHESIZE(bool, isPlayerHead, PlayerHead);	// �÷��̾� �Ӹ��� üũ�� �Ұ�
	PRIVATESYNTHESIZE(bool, isPlayerPlaying, PlayerPlaying);	// �÷��̾ �ʵ��ϋ� �׷��ִ� üũ �Ұ�
	PRIVATESYNTHESIZE(ITEMKINDS, m_itemKind, ItemKind);					// ������ ����(��Ʈ,�Һ�,���,��Ÿ ���)
	PRIVATESYNTHESIZE(ACTITEMKINDS, m_actItemKind, ActItemKind);		// ��Ʈ������ ���� (���, ���� ��, ���Ѹ��� ���)
	PRIVATESYNTHESIZE(CONSUMEKINDS, m_consumItemKind, ConsumItemKind);	// �Ҹ������ ���� (����, ȸ���� ���)
	PRIVATESYNTHESIZE(int, m_nWaterDurability, WaterDurability);		// ���Ѹ��� ������
	PRIVATESYNTHESIZE(int, m_nMaxWaterDurability, MaxWaterDurability);	// ���Ѹ��� �ִ� ������
	PRIVATESYNTHESIZE(int, m_nEnergy, Energy);		// ������ ȸ����
	PRIVATESYNTHESIZE(int, m_nHp, Hp);				// ü�� ȸ����

	int m_nMouseX;	// ���콺 �޾ƿ� xy
	PRIVATESYNTHESIZE(int, m_nMouseY, MouseY);
	int m_nMouseY2;
	int m_nNameX;	// �̸�ǥ���� ��ǥ x
	int m_nNameY;	// �̸�ǥ���� ��ǥ y
	int m_nKindX;	// ������ ���� ��ǥ x
	int m_nKindY;	// ������ ���� ��ǥ y
	int m_nToolTipX;	// ���� x
	int m_nToolTipY;	// ���� y
	int m_nEnergyX;	// ��� x
	int m_nEnergyY;	// ��� y
	int m_nHpX;	// ü�� x
	int m_nHpY;	// ü�� y
	RECT m_NameRc;		// DrawText�� ��Ʈ�� 
	RECT m_KindRc;
	RECT m_ToolTipRc;
	image* m_pEnergy;	//������ �׸�
	image* m_pHp;		// ü�� �׸�
	image* m_pShopToolTip; // ������ �κ�����

	void setItem(bool sameItem);				// ���� ���� ������ ����


public:
	HRESULT init(int x, int y, bool shop = false);
	void release();
	void update();
	void render(HDC hdc);
	void ToolTiprender(HDC hdc); // �κ��丮�޴�, �����κ��丮 ������
	void ShopRender(HDC hdc, int nameX, int nameY, int moneyX, int moneyY); // ���� ����Ʈ ������ �������̸�, ���� ��
	void ShopInvenRender(HDC hdc); // ������ �κ��丮 ����

	void getItem(int itemnum, bool sameItem);	// �־��� ������ ��ȣ ȣ��
	void deleteItem();			// ������ ����
	void setPlayXY(int x, int y); // �÷��̾� �Ӹ��� ��ǥ �޾ƿ��� �Լ�
	void useItem(); // ������ ����Լ� (��� �̿ϼ�)

	item();
	~item();
};

