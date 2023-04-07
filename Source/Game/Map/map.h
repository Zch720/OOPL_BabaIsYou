#pragma once
#include "../../Library/gameutil.h"
#include "map_object.h"
#include "map_object_id.h"
#include "../../Expansion/vector2d.hpp"

using namespace game_framework;
class Map {
private:
	static CMovingBitmap world0Backgroung;
	static vector2d<Mapobject*> world;

public:
	static void LoadWorld();
	static void Show();
};