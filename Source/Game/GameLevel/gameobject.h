#pragma once

#include "../../Library/gameutil.h"
#include "../../Expansion/point.h"
#include "property_id.h"
#include "gameobject_id.h"
#include "gameobject_type.h"

enum Direction {
	DIRECTION_RIGHT = 0,
	DIRECTION_UP = 1,
	DIRECTION_LEFT = 2,
	DIRECTION_DOWN = 3
};

class Gameobject {
public:
	const int MOVE_STEP = 4;

	game_framework::CMovingBitmap texture;
	GameobjectId gameobjectId;
	GameobjectType gameobjectType;
	Point gameBoardPosition;

	bool textureSetted = false;
	int textureSize = 0;
	double textureFatcor = 1;
	PropId textureColorPropId = PROP_NONE;
	Direction textureDirection = DIRECTION_RIGHT;

	Direction moveDirection = DIRECTION_RIGHT;
	int characterTextureStep = 0;
	int moveRemainStep = 0;

	Gameobject(const GameobjectId gameobjectId, const Point gameBoardPosition, const int textureSize);

	void setTextureWithColor(const Point textureOriginPosition, const PropId colorPropId);

	/*
		OBJECT_TYPE_CHARACTER: no otherInformation
		OBJECT_TYPE_STATIC: no otherInformation
		OBJECT_TYPE_TILED: otherInformation denote gameobject connect status
		OBJECT_TYPE_TEXT: otherInformation denote text is dark(0) or light(1)
	*/
	void show(const int textureCount, const int otherInformation = 0);

	void updatePosition();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	/*
		direction denote origion gameobject direction
	*/
	void undoUp(Direction direction);
	void undoDown(Direction direction);
	void undoLeft(Direction direction);
	void undoRight(Direction direction);
};