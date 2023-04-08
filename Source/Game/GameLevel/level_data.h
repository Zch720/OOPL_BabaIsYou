#pragma once

#include "gameobject.h"
#include "block.h"
#include "../../Expansion/point.h"
#include "../../Expansion/vector2d.hpp"

class LevelData {
private:
	struct GameobjectCreateInfo {
		GameobjectId gameobjectId;
		Point position;
		Direction textureDirection;
	};
	
	static void getWorld(int level);
	static void createGameboard(std::vector<GameobjectCreateInfo>);

public:
	static int world;
	static int level;

	static game_framework::CMovingBitmap background;
	static vector2d<Block> gameboard;
	static int gameboardWidth;
	static int gameboardHeight;

	static Point textureOrigionPosition;
	static int textureSize;

	static bool touchWinObject;

	// level data functions
	static void LoadLevel(int level);
	static void Clear();
};