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

	NPC_NAME m_NpcName; // �̸�
	State NpcState; // ����

	animation* m_pAniNpc;
	float m_fNpcSpeed;

	//int m_costG; // ���������κ����� ���
	//int m_costH; // ������������ ���
	//objNpc* m_Parent; // ���� ����� �θ� ����� �ּҰ�

	//list<objNpc*> m_OpenList;
	//list<objNpc*> m_CloseList;
	//list<int> m_PathList;

	//// 4���� �˻�
	//const int ways = 4;
	//// ���� ������ �� �Ʒ�	
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

