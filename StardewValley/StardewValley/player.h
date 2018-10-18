#pragma once
class animation;
//class Map;
class playerMenu;
class inven;
class item;
class fishing;
class progressBarHp;
class mapManager;
class mapObject;
class objCrop;

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
	PLAYER_ACTITEM,
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
	MOTION_HANDUP,
	MOTION_RIDE 	//@@ 여기에도 라이딩 추가
};

class player
{
private:
	image*		m_pPlayer;		// 플레이어 이미지
	image*		m_pTarget;		// 바닥타일 타겟 이미지(빨간색 네모)
	image*		m_pSeedTarget;	// 바닥타일 씨앗타겟 이미지
	image*		m_pNumber;		// 상점에서 사용될 골드 ui
	image*		m_pHpEnergyUi;  // @체력,에너지 이미지 
	

	animation *	m_pAni;			// 플레이어 프래임랜더
	PLAYERDIR	m_playerDir;	// 플래이어 방향 상태
	PLAYERSTATE	m_playerState;	// 플레이어 행동 상태
	PLAYERMOTION m_playerMotion;// 플레이어 모션 상태
	playerMenu*	m_pMenu;		// 인벤토리
	item*		m_pTargetItem;	// 퀵슬롯 현재 아이템
	fishing*	m_pFishing;		// 낚시

	RECT	m_HpRc;				// @체력 렉트
	RECT	m_EnergyRc;			// @에너지 렉트
	RECT	m_rc;				// 플래이어 렉트
	RECT	m_TargetRc;			// 플레이어 주변 렉트
	RECT	m_temprc;			// 빨간네모 렉트
	mapManager* m_pMap;			// 맵 포인터
	progressBarHp*	m_pHpBar;
	progressBarHp*	m_pEnergyBar;

	PRIVATESYNTHESIZE(int, m_nMoney, Money);
	
	float m_fMaxHp;				// @플레이어 최대 체력
	float m_fMaxEnergy;			// @플레이어 최대 에너지
	float m_fCurrHp;			// @플레이어 현재 체력
	float m_fCurrEnergy;		// @플레이어 현재 에너지
	float m_fGaugeBar;			//@@

	int m_nX;					// 플레이어 좌표x
	int m_nY;					// 플레이어 좌표y
	int m_nTargetX;				// 빨간네모 좌표x
	int m_nTargetY;				// 빨간네모 좌표y
	int m_nSyncX;				// 모션별 싱크좌표 x
	int m_nSyncY;				// 모션별 싱크좌표 y
	float m_fRange;				// 플레이어 사거리

	int m_nPlayerSizeX;			// 플레이어 사이즈x
	int m_nPlayerSizeY;			// 플레이어 사이즈y
	int	m_nMoveSpeed;			// 플레이어 이동스피드
	bool isMove;				// 프레임렌더용 불값
	bool isStop;				// 멈춰있을때 타일타겟 보이게
	bool isSeed;				// 씨앗을 뿌릴수 있는지 없는지 확인용
	bool isProgressBar[2];		// 체력,기력바 출력용 불값
	bool isHarvest;

	int m_nTempIndex;			// 타일에 접근할 임시 인덱스
	POINT m_pRight;
	POINT m_pLeft;
	POINT m_pUp;
	POINT m_pDown;

	int m_nHp;	// 소모품 확인용 hp변수 (삭제해야함)

	bool isRideHorse; //@@ 말타기 불값 추가
	PLAYCOLLISION m_playerCollision;	// 플레이어 충돌 상태값

	void setTargetXY();					// 타겟렉트 좌표
	void setKey();						// 키 묶어둔 함수
	void move(PLAYERDIR playerdir);		// 플레이어 이동 함수
	void PointCollide();				// 충돌값 구하는 함수
	void Collide();						// 플레이어 충돌함수
	void setMotion(animation * ani, image** image, const char * szName, int framex, int framey);
	void startMotion(animation* ani, int start, int end, bool reverse, bool loop, int fps);
	void setSyncMotion(PLAYERMOTION motion, int* x, int* y);	//모션 싱크로 맞추는 함수
	void setItemMotion();	// 퀵바아이템에 따른 플레이어 모션
	void useItem();			// 소모품 아이템사용
	void setDir();			// 도구 사용시 플레이어 방향잡는함수
	void setSpadeTile();			// 괭이로 타일바꾸는 함수
	void setWaterTile();			// 물뿌리개로 타일바꾸는 함수
	void setAxeTile();				// 도끼 상호작용 함수
	void setPickaxTile();			// 곡괭이 상호작용 함수
	void setNotTile();				// 낫 상호작용 함수
	void setSwordTile();			// 검 상호작용 함수
	void progressBarToolTip();		// 체력,에너지 표시 처리함수
	void harvest();					// 작물 수확함수

	bool m_isMove =false;

	int m_nPlayerIndexX;
	int m_nPlayerIndexY;
	int m_nPlayerIndex;

	void addSound();
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void numRender(HDC hdc, int x, int y);

	int getX() { return m_nX; }					// 카메라 매니저에 쓰일 x,y겟터셋터들
	void setX(int x) { m_nX = x; }
	int getY() { return m_nY; }
	void setY(int y) { m_nY = y; }
	int getSizeX() { return m_nPlayerSizeX; }
	int getSizeY() { return m_nPlayerSizeY; }

	PLAYERDIR getPlayerDir() { return m_playerDir; }
	void setPlayerState(PLAYERSTATE state) { m_playerState  = state; }

	playerMenu* getPlayerMenu() { return m_pMenu; }
	void getMap(mapManager* map) { m_pMap = map; }

	inline RECT getPlayerRc() { return m_rc; }
	//int getTargetX() { return m_nTargetX; }
	//int getTargetY() { return m_nTargetY; }
	int getPlayerIndex() { return m_nPlayerIndex; }
	
	player();
	~player();
};

