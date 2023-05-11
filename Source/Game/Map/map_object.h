#pragma once
#include "map_object_id.h"
#include "../../Expansion/point.h"
#include "../../Library/gameutil.h"

class Mapobject {
private:
	game_framework::CMovingBitmap texture;
	int moveStep = 3;
	

public:
	Mapobject();
	Mapobject(MapobjectId mapobjectId, int world);

	MapobjectId mapobjectId = NONE;
	Point mapobjectPosition;
	int levelIndex;

	void UpdateBoxPosition(Point textureOrigionPosition);

	void MoveUp(Point textureOrigionPosition);
	void MoveDown(Point textureOrigionPosition);
	void MoveLeft(Point textureOrigionPosition);
	void MoveRight(Point textureOrigionPosition);

	void LoadTexture(int world, Point textureOrigionPosition);
	void Show();
};