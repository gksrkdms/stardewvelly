#pragma once
#include "mapObject.h"

enum CROP_KIND
{
	STRAWBERRY,
	CARROT
};

class objCrop : public mapObject
{
private:
	//item* m_pitem;
	CROP_KIND m_cropKind;
public:
	objCrop();
	~objCrop();

	virtual HRESULT init();
	virtual HRESULT init(int x, int y, int id, int index);
	virtual void release();
	virtual void update();
	void setXY(int x, int y);
	virtual void render(HDC hdc);

	virtual void getPlayer(player* player) { m_player = player; }

};

