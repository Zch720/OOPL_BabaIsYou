#pragma once
#include "map_object_id.h"
#include "../../Expansion/point.h"
#include "../../Library/gameutil.h"

class Mapobject {
private:
	game_framework::CMovingBitmap texture;
	MapobjectId mapobjectId = NONE;

public:
	Mapobject();
	Mapobject(MapobjectId mapobjectId, int world);

	Point mapobjectPosition;
	int levelIndex;

	void LoadTexture(int world, Point textureOrigionPosition);
	void Show();
};