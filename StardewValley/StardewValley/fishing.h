#pragma once
class player;
class playerMenu;
class inven;
enum BARSTATE // 처음 가로바 상태
{
	BAR_NULL,
	PLUS,
	MINUS,
	STOP,
	NUM
};
enum BARRESULT // 처음 가로바 결과
{
	BAR_NULL1,
	GREEN, // 다음단계로
	YELLOW,  // 다음단계로
	RED, //다음단계X, 초기화시킴
	NUM1
};
//enum PLAYERSEE // 플레이어 보는방향
//{
//	PLAYER_NULL,
//	PLAYER_FRONT,
//	PLAYER_BACK,
//	PLAYER_LEFT,
//	PLAYER_RIGHT,
//	NUM2
//};
enum FISHGET // 세로바 물고기싸움 결과
{
	FISHGET_NULL,
	GET_FISH, // 얻는다 
	MISS_FISH, // 초기화
	NUM3
};

class fishing
{
private:
	char		m_szText[128];

	float		m_fTime;	// 맥스이미지 나올때 시간초
	float		m_fTime2;	// 가로바 선택후 대기시간
	float		m_fTime3;	// 히트이미지 나올떄시간초 , 찌던질때 찌움직임 시간초
	float		m_fTime4;	// 찌흔들림 , 찌 대기시간 
	float		m_fTime5;

	image *		m_pIgaroBar;		// 가로바 이미지	
	image *		m_pImax;			// Max 이미지
	image *		m_pIzzi;			// 찌 이미지
	image *		m_pIplayer;			// 플레이어 이미지
	image *     m_pIplayerFishing;	// 플레이어 낚시 모션
	image *		m_pIFeel;			// 느낌표 이미지
	image *		m_pIhit;			// Hit 이미지
	image *		m_pIseroBar;		// 세로바 이미지
	image *		m_pIwhiteUiLt;		// 세로흰말풍선 왼쪾위
	image *		m_pIwhiteUiRb;		// 세로흰말풍선 오른아래
	image *		m_pIgreenBar;		// 세로바 초록색 물고기맞추는 바
	image *     m_pIfish;			// 움직이는 물고기 이미지
	image *		m_pIchoo;			// 돌아가는 레버 이미지
	image *     m_pIgogi;			// 잡힌 물고기 이미지
	image *     m_pIboard;			// 잡힌 물고기 판때기
	
	RECT		m_rcGaroBar;		// 가로게이지 렉트
	RECT		m_rcSeroBar;		// 세로게이지 렉트
	RECT		m_rcFishBar;		// 물고기 게이지 렉트
	RECT		m_rcGreenBar;		// 물고기 맞추는 초록 게이지 렉트

	float		m_fGaroBarX;		// 가로바이미지 좌표
	float		m_fGaroBarY;
	float		m_fSeroBarX;		// 세로바이미지 좌표
	float		m_fSeroBarY;
	float		m_fWhiteUiX;		// 세로흰말풍선 좌표
	float		m_fWhiteUiY;
	float		m_fMaxX;			//맥스이미지 좌표
	float		m_fMaxY;

	float		m_fZziX;			//찌 이미지좌표
	float		m_fZziY;
	float       m_fZziDistance;
	int			m_iFrameZziX;
	int			m_iZziCount;


	float		m_fGreenBarX;		// 초록색 물고기맞추는바 좌표
	float		m_fGreenBarY;
	float		m_fGreenCurrY;
	float		m_fGreenMinY;
	float		m_fSpeedGreen;

	float		m_fFishX;			//움직이는물고기 좌표
	float		m_fFishY;
	int			m_iFishMove;		//움직이는 물고기 랜덤값

	float		m_fPlayerX;			//플레이어 좌표
	float		m_fPlayerY;
	int			m_iPlayerFrameX;
	int			m_iPlayerFrameY;
	int			m_iPlayerCount;

	float		m_fRcX;				//가로게이지 렉트좌표
	float		m_fRcY;
	float	    m_fRcMaxX;			// 움직이는 렉트의최대x값
	float	    m_fRcMinX;			// 움직이는 렉트의최소x값
	float	    m_fRcCurrX;			// 움직이는 렉트의 현재x값

	float		m_fSrcX;			// 세로게이지 렉트좌표
	float		m_fSrcY;
	float		m_fSrcWidth;
	float		m_fSrcHeight;
	float	    m_fSrcMaxY;
	float	    m_fSrcMinY;
	float	    m_fSrcCurrY;

	float		m_fFeelX;			//느낌표 이미지좌표
	float		m_fFeelY;
	int			m_iFeelAlpha;

	float		m_fHitX;			// 히트이미지 좌표
	float		m_fHitY;
	int			m_fHitBig;

	float		m_fchooX;				//추(낚싯대 릴감는 레버) 좌표
	float		m_fchooY;
	int			m_iChooFrame;
	int			m_iChooCount;

	float		m_fBoardX;				//잡은물고기 판때기 좌표
	float		m_fBoardY;

	

	int			m_iChance;			// 성공률
	int			m_iRandomChance;	// 랜덤값 담기는 변수
	int			m_iRandomFish;		// 랜덤값 물고기 206~209
	int			m_iLuck;			// 행운

	int			m_r;  // 가로바렉트 색깔
	int			m_g;
	int			m_b;

	bool		isOne;  //처음 낚시 시작 버튼누르면 true, 가로바 결과 나오면 false
	bool		isTwo;  //가로바 결과 나오면 true, 찌던지고 기다리며 물고기가 물거나 놓치거나 , 물고기 물었을때 누르면  false
	bool		isThree; // 물었을떄 누르면 히트뜨고 히트가끝나면서  true,  물고기 싸움끝나고 얻었을때 false

	bool		isMaxOn; //맥스일때 이미지 스위치
	bool		isThrowing; // 찌 던지고 true, true일때 찌 위아래로 흔들리게  zzimove() 
	bool		isFeelClick; // 물고기물면 느낌표 뜸 
	bool		isHitOn; // 느낌표 사라지기전에 누르면 히트뜸
	bool		isGetFish; // 물고기 낚고 결과
	bool		isMistake; //실수로 만들어진 불값
	bool		isBring; // 낚인 물고기 손위로 올라오게 하는 불값
	bool		isSetFish; // 랜덤으로 얻은 물고기
	bool		isSoundOn; // 사운드 실행
	bool        isSoundOn2; //부득이한 사용
	BARSTATE	m_BarState;		// 가로바 게이지 상태
	BARRESULT	m_BarResult;	// 가로바 게이지 결과
	//PLAYERSEE	m_PlayerSee;    // 플레이어 보는방향
	FISHGET		m_FishResult;	// 물고기 싸움결과
	player*		m_pPlayer;
	
	bool isFishing;		// 외부에서 쓰일 불값

	const char * getFishIcon(int fishNum);
	
public:

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void fishingOne(); // 가로바시작부터 결과까지 
	void ifMax();
	void zziThrow();
	void ifHit();

	void fishingTwo(); // 결과부터 물었을떄 까지
	void zziMove();

	void fishingThree(); // 물었때부터 싸우고 결과까지
	void fishMove();

	void fishingFour(); //잡은 후
	void fishBring();
	
	void setPlayer(player* play) { m_pPlayer = play; }
	//void setIsOne(bool isone) { isOne = isone; }
	//void setIsMistake(bool mistake) { isMistake = mistake; }
	void setIsFishing(bool isfishing) { isFishing = isfishing; }
	bool getIsFishing() { return isFishing; }
	fishing();
	~fishing();
};

