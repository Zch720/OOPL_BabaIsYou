#pragma once
#include "../../Library/gameutil.h"
#include "map_object.h"
#include "map_object_id.h"
#include "../../Expansion/point.h"
#include "../../Expansion/vector2d.hpp"

using namespace game_framework;
class Map {
private:
	vector2d<Mapobject> worldVector;
	Mapobject box;
	void CreateWorldVector();
	CMovingBitmap worldBackground;

public:
	int worldVectorWidth;
	int worldVectorHeight;

	Point textureOrigionPosition;

	void LoadWorld(int world);
	void ClearWorld();
	void Show();
};