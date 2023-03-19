#pragma once

#include "../Library/gameutil.h"
#include "gameobject_id.h"
#include "gameobject_type.h"

class LevelManager;

class Gameobject {
private:
	game_framework::CMovingBitmap texture;
	GameobjectId gameobjectId;

	int textureSize = 0;
	double textureFactor = 1;
	CPoint gameBoardPosition;
	int direction = 0;
	int remainStep = 0;
	int undoRemainStep = 0;

	bool isText = false;

	void updatePosition();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void undoUp();
	void undoDown();
	void undoLeft();
	void undoRight();

	friend LevelManager;

public:
	Gameobject(GameobjectId gameobjectId, CPoint gameBoardPosition, CPoint textureOriginPosition, int textureSize);

	void Show();
};