#pragma once
#include "mapObject.h"

enum State {
	IDLE, MOVE, TALK
};

struct NPCINFO
{
	float fNpcX;
	float fNpcY;
	float fNpcSpeed;
	int NpcID;

	State NpcState;
	image* NpcImg;
	RECT NpcRc;
};


class objNpc :
	public mapObject
{
private:
	NPCINFO* m_NpcInfo;

public:
	objNpc();
	~objNpc();

	virtual HRESULT init();
	virtual HRESULT init(int x, int y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void getPlayer(player* player) { m_player = player; }

};

