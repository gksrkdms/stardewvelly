#pragma once
class animation;
//class Map;
class playerMenu;
class inven;
class item;
class fishing;

class mapManager;

#define TARGET_SIZE 2

enum PLAYERDIR
{
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_UP,
	PLAYER_DOWN
};

enum PLAYERSTATE
{
	PLAYER_PLAY,
	PLAYER_MENU,
	PLAYER_FISHING,
	PLAYER_ACTITEM
};

enum PLAYCOLLISION
{
	COLL_FALSE,
	COLL_LEFT,
	COLL_RIGHT,
	COLL_UP,
	COLL_DOWN,
};

enum PLAYERMOTION
{
	MOTION_IDLE,
	MOTION_AXE,
	MOTION_SPADE,
	MOTION_WATER,
	MOTION_PICKAX,
	MOTION_NOT,
	MOTION_FISHINGROD,
	MOTION_SWORD,
	MOTION_HANDUP

};

class player
{
private:
	image*		m_pPlayer;		// �÷��̾� �̹���
	image*		m_pTarget;		// �ٴ�Ÿ�� Ÿ�� �̹���(������ �׸�)
	image*		m_pNumber;
	image*		m_pHpEnergyUi;  // @ü��,������ �̹��� 
	

	animation *	m_pAni;			// �÷��̾� �����ӷ���
	PLAYERDIR	m_playerDir;	// �÷��̾� ���� ����
	PLAYERSTATE	m_playerState;	// �÷��̾� �ൿ ����
	PLAYERMOTION m_playerMotion;// �÷��̾� ��� ����
	playerMenu*	m_pMenu;		// �κ��丮
	item*		m_pTargetItem;	// ������ ���� ������
	fishing*	m_pFishing;

	RECT	m_HpRc;				// @ü�� ��Ʈ
	RECT	m_EnergyRc;			// @������ ��Ʈ
	RECT	m_rc;				// �÷��̾� ��Ʈ
	RECT	m_TargetRc;			// �����׸� ��Ʈ
	RECT	m_temprc;			// �����׸� ��Ʈ
	mapManager* m_pMap;			// �� ������

	PRIVATESYNTHESIZE(int, m_nMoney, Money);

	float m_fMaxHp;				// @�÷��̾� �ִ� ü��
	float m_fMaxEnergy;			// @�÷��̾� �ִ� ������
	float m_fCurrHp;			// @�÷��̾� ���� ü��
	float m_fCurrEnergy;		// @�÷��̾� ���� ������
	float m_fGaugeBar;			//@@

	int m_nX;					// �÷��̾� ��ǥx
	int m_nY;					// �÷��̾� ��ǥy
	int m_nTargetX;				// �����׸� ��ǥx
	int m_nTargetY;				// �����׸� ��ǥy
	int m_nSyncX;				// ��Ǻ� ��ũ��ǥ x
	int m_nSyncY;				// ��Ǻ� ��ũ��ǥ y
	float m_fRange;				// �÷��̾� ��Ÿ�

	int m_nPlayerSizeX;			// �÷��̾� ������x
	int m_nPlayerSizeY;			// �÷��̾� ������y
	int	m_nMoveSpeed;			// �÷��̾� �̵����ǵ�
	bool isMove;				// �����ӷ����� �Ұ�
	bool isTargetRc;			// ������Ʈ ǥ�� �Ұ�


	bool isFishingStart;
	PLAYCOLLISION m_playerCollision;	// �÷��̾� �浹 ���°�

	void setTargetXY();					// Ÿ�ٷ�Ʈ ��ǥ
	void setKey();						// Ű ����� �Լ�
	void move(PLAYERDIR playerdir);		// �÷��̾� �̵� �Լ�
	void setMotion(animation * ani, image** image, const char * szName, int framex, int framey);
	void startMotion(animation* ani, int start, int end, bool reverse, bool loop, int fps);
	void setSyncMotion(PLAYERMOTION motion, int* x, int* y);	//��� ��ũ�� ���ߴ� �Լ�
	void setItemMotion();	// ���پ����ۿ� ���� �÷��̾� ���
	void useItem();			// �Ҹ�ǰ �����ۻ��
	
	int i;
	bool m_isMove =false;

	void damaged(float c); //@@
	void addSound();
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void numRender(HDC hdc);

	int getX() { return m_nX; }					// ī�޶� �Ŵ����� ���� x,y���ͼ��͵�
	void setX(int x) { m_nX = x; }
	int getY() { return m_nY; }
	void setY(int y) { m_nY = y; }
	int getSizeX() { return m_nPlayerSizeX; }
	int getSizeY() { return m_nPlayerSizeY; }

	PLAYERDIR getPlayerDir() { return m_playerDir; }
	void setPlayerState(PLAYERSTATE state) { m_playerState  = state; }

	playerMenu* getPlayerMenu() { return m_pMenu; }
	void getMap(mapManager* map) { m_pMap = map; }

	//int getTargetX() { return m_nTargetX; }
	//int getTargetY() { return m_nTargetY; }
	
	player();
	~player();
};

