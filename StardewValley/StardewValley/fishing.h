#pragma once
class player;
class playerMenu;
class inven;
enum BARSTATE // ó�� ���ι� ����
{
	BAR_NULL,
	PLUS,
	MINUS,
	STOP,
	NUM
};
enum BARRESULT // ó�� ���ι� ���
{
	BAR_NULL1,
	GREEN, // �����ܰ��
	YELLOW,  // �����ܰ��
	RED, //�����ܰ�X, �ʱ�ȭ��Ŵ
	NUM1
};
//enum PLAYERSEE // �÷��̾� ���¹���
//{
//	PLAYER_NULL,
//	PLAYER_FRONT,
//	PLAYER_BACK,
//	PLAYER_LEFT,
//	PLAYER_RIGHT,
//	NUM2
//};
enum FISHGET // ���ι� �����ο� ���
{
	FISHGET_NULL,
	GET_FISH, // ��´� 
	MISS_FISH, // �ʱ�ȭ
	NUM3
};

class fishing
{
private:
	char		m_szText[128];

	float		m_fTime;	// �ƽ��̹��� ���ö� �ð���
	float		m_fTime2;	// ���ι� ������ ���ð�
	float		m_fTime3;	// ��Ʈ�̹��� ���Ë��ð��� , ������� ������� �ð���
	float		m_fTime4;	// ����鸲 , �� ���ð� 
	float		m_fTime5;

	image *		m_pIgaroBar;		// ���ι� �̹���	
	image *		m_pImax;			// Max �̹���
	image *		m_pIzzi;			// �� �̹���
	image *		m_pIplayer;			// �÷��̾� �̹���
	image *     m_pIplayerFishing;	// �÷��̾� ���� ���
	image *		m_pIFeel;			// ����ǥ �̹���
	image *		m_pIhit;			// Hit �̹���
	image *		m_pIseroBar;		// ���ι� �̹���
	image *		m_pIwhiteUiLt;		// ������ǳ�� �ަU��
	image *		m_pIwhiteUiRb;		// ������ǳ�� �����Ʒ�
	image *		m_pIgreenBar;		// ���ι� �ʷϻ� �������ߴ� ��
	image *     m_pIfish;			// �����̴� ����� �̹���
	image *		m_pIchoo;			// ���ư��� ���� �̹���
	image *     m_pIgogi;			// ���� ����� �̹���
	image *     m_pIboard;			// ���� ����� �Ƕ���
	
	RECT		m_rcGaroBar;		// ���ΰ����� ��Ʈ
	RECT		m_rcSeroBar;		// ���ΰ����� ��Ʈ
	RECT		m_rcFishBar;		// ����� ������ ��Ʈ
	RECT		m_rcGreenBar;		// ����� ���ߴ� �ʷ� ������ ��Ʈ

	float		m_fGaroBarX;		// ���ι��̹��� ��ǥ
	float		m_fGaroBarY;
	float		m_fSeroBarX;		// ���ι��̹��� ��ǥ
	float		m_fSeroBarY;
	float		m_fWhiteUiX;		// ������ǳ�� ��ǥ
	float		m_fWhiteUiY;
	float		m_fMaxX;			//�ƽ��̹��� ��ǥ
	float		m_fMaxY;

	float		m_fZziX;			//�� �̹�����ǥ
	float		m_fZziY;
	float       m_fZziDistance;
	int			m_iFrameZziX;
	int			m_iZziCount;


	float		m_fGreenBarX;		// �ʷϻ� �������ߴ¹� ��ǥ
	float		m_fGreenBarY;
	float		m_fGreenCurrY;
	float		m_fGreenMinY;
	float		m_fSpeedGreen;

	float		m_fFishX;			//�����̴¹���� ��ǥ
	float		m_fFishY;
	int			m_iFishMove;		//�����̴� ����� ������

	float		m_fPlayerX;			//�÷��̾� ��ǥ
	float		m_fPlayerY;
	int			m_iPlayerFrameX;
	int			m_iPlayerFrameY;
	int			m_iPlayerCount;

	float		m_fRcX;				//���ΰ����� ��Ʈ��ǥ
	float		m_fRcY;
	float	    m_fRcMaxX;			// �����̴� ��Ʈ���ִ�x��
	float	    m_fRcMinX;			// �����̴� ��Ʈ���ּ�x��
	float	    m_fRcCurrX;			// �����̴� ��Ʈ�� ����x��

	float		m_fSrcX;			// ���ΰ����� ��Ʈ��ǥ
	float		m_fSrcY;
	float		m_fSrcWidth;
	float		m_fSrcHeight;
	float	    m_fSrcMaxY;
	float	    m_fSrcMinY;
	float	    m_fSrcCurrY;

	float		m_fFeelX;			//����ǥ �̹�����ǥ
	float		m_fFeelY;
	int			m_iFeelAlpha;

	float		m_fHitX;			// ��Ʈ�̹��� ��ǥ
	float		m_fHitY;
	int			m_fHitBig;

	float		m_fchooX;				//��(���˴� ������ ����) ��ǥ
	float		m_fchooY;
	int			m_iChooFrame;
	int			m_iChooCount;

	float		m_fBoardX;				//��������� �Ƕ��� ��ǥ
	float		m_fBoardY;

	

	int			m_iChance;			// ������
	int			m_iRandomChance;	// ������ ���� ����
	int			m_iRandomFish;		// ������ ����� 206~209
	int			m_iLuck;			// ���

	int			m_r;  // ���ιٷ�Ʈ ����
	int			m_g;
	int			m_b;

	bool		isOne;  //ó�� ���� ���� ��ư������ true, ���ι� ��� ������ false
	bool		isTwo;  //���ι� ��� ������ true, ������� ��ٸ��� ����Ⱑ ���ų� ��ġ�ų� , ����� �������� ������  false
	bool		isThree; // �������� ������ ��Ʈ�߰� ��Ʈ�������鼭  true,  ����� �ο򳡳��� ������� false

	bool		isMaxOn; //�ƽ��϶� �̹��� ����ġ
	bool		isThrowing; // �� ������ true, true�϶� �� ���Ʒ��� ��鸮��  zzimove() 
	bool		isFeelClick; // ����⹰�� ����ǥ �� 
	bool		isHitOn; // ����ǥ ����������� ������ ��Ʈ��
	bool		isGetFish; // ����� ���� ���
	bool		isMistake; //�Ǽ��� ������� �Ұ�
	bool		isBring; // ���� ����� ������ �ö���� �ϴ� �Ұ�
	bool		isSetFish; // �������� ���� �����
	bool		isSoundOn; // ���� ����
	bool        isSoundOn2; //�ε����� ���
	BARSTATE	m_BarState;		// ���ι� ������ ����
	BARRESULT	m_BarResult;	// ���ι� ������ ���
	//PLAYERSEE	m_PlayerSee;    // �÷��̾� ���¹���
	FISHGET		m_FishResult;	// ����� �ο���
	player*		m_pPlayer;
	
	bool isFishing;		// �ܺο��� ���� �Ұ�

	const char * getFishIcon(int fishNum);
	
public:

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void fishingOne(); // ���ιٽ��ۺ��� ������� 
	void ifMax();
	void zziThrow();
	void ifHit();

	void fishingTwo(); // ������� �������� ����
	void zziMove();

	void fishingThree(); // ���������� �ο�� �������
	void fishMove();

	void fishingFour(); //���� ��
	void fishBring();
	
	void setPlayer(player* play) { m_pPlayer = play; }
	//void setIsOne(bool isone) { isOne = isone; }
	//void setIsMistake(bool mistake) { isMistake = mistake; }
	void setIsFishing(bool isfishing) { isFishing = isfishing; }
	bool getIsFishing() { return isFishing; }
	fishing();
	~fishing();
};

