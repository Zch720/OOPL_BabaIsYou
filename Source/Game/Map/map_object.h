#pragma once
#include "map_object_id.h"
#include "../../Expansion/point.h"
#include "../../Library/gameutil.h"
#include "../../Expansion/direction.h"

class Mapobject {
private:
	game_framework::CMovingBitmap texture;

	static const int MAX_MOVE_STEP = 4;
	int moveRemainStep = 0;
	Direction moveDirection;

	void clearRemainStep();
	int getTextureMoveDistance();
	void updateTexturePosition();

public:
	Mapobject();
	Mapobject(MapobjectId mapobjectId, int world);

	MapobjectId mapobjectId = NONE;
	Point mapobjectPosition;
	int levelIndex;

	bool IsMoving();

	void MoveUp(Point textureOrigionPosition);
	void MoveDown(Point textureOrigionPosition);
	void MoveLeft(Point textureOrigionPosition);
	void MoveRight(Point textureOrigionPosition);

	void LoadTexture(int world, Point textureOrigionPosition);

	void SetTexturePosition(Point textureOrigionPosition);
	void Show();
};