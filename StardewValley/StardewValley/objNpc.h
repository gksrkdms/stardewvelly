#pragma once
#include "mapObject.h"
#include <list>

class animation;
class mapManager;

enum State {
	TOP, BOTTOM, LEFT, RIGHT
};

enum NPC_NAME {
	ABIGAIL,
};

class objNpc :
	public mapObject
{
private:

	NPC_NAME m_NpcName; // 이름
	State NpcState; // 상태

	animation* m_pAniNpc;
	float m_fNpcSpeed;

	//int m_costG; // 시작점으로부터의 비용
	//int m_costH; // 도착점까지의 비용
	//objNpc* m_Parent; // 현재 노드의 부모 노드의 주소값

	//list<objNpc*> m_OpenList;
	//list<objNpc*> m_CloseList;
	//list<int> m_PathList;

	//// 4방향 검사
	//const int ways = 4;
	//// 왼쪽 오른쪽 위 아래	
	//const int way[4][2] = { { -1,0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };

public:
	objNpc();
	~objNpc();

	virtual HRESULT init();
	virtual HRESULT init(int x, int y, int id, int index);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void getPlayer(player* player) { m_player = player; }

	void abiMove();

	void startMotion(animation * ani, int start, int end, bool reverse, bool loop, int fps);

	//void findPath();
	
};

