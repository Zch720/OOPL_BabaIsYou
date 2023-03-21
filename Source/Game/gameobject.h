#pragma once

#include "../Library/gameutil.h"
#include "property_id.h"
#include "gameobject_id.h"
#include "gameobject_type.h"

class LevelManager;

class Gameobject {
private:
	game_framework::CMovingBitmap texture;
	GameobjectId gameobjectId;
	GameobjectType gameobjectType;

	int textureSize = 0;
	double textureFactor = 1;
	CPoint textureOriginPosition;
	CPoint gameBoardPosition;
	int direction = 0;
	int textureStepCount = 0;
	int remainStep = 0;
	int undoRemainStep = 0;

	void setTextureColor(PropId);

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
	Gameobject(GameobjectId gameobjectId, PropId colorPropId, CPoint gameBoardPosition, CPoint textureOriginPosition, int textureSize);

	void Show(int textureCount, int otherCount = 0);
};