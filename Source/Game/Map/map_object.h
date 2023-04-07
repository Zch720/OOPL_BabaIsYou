#pragma once
#include "map_object_id.h"
#include "../../Library/gameutil.h"

class Mapobject {
public:
	game_framework::CMovingBitmap texture;
	MapobjectId gameobjectId;
	int levelIndex;

	void Show();
};