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

	static game_framework::CMovingBitmap background;
	
	static int world;
	static int level;
	static int gameboardWidth;
	static int gameboardHeight;

	static bool touchWinObject;

	static void getWorld(int level);

	static void checkSourceFileTitle(std::vector<std::string>::iterator&, std::string);

	static void loadResourceDatas();
	static void loadBackground();
	static void loadGameboardSize(std::vector<std::string>::iterator&);
	static void loadTextureOriginPosition(std::vector<std::string>::iterator&);
	static void loadTextureSize(std::vector<std::string>::iterator&);
	static void loadNeededTextures(std::vector<std::string>::iterator&);
	static void loadObjects(std::vector<std::string>::iterator&, std::vector<std::string>::iterator&);

	static void createGameboard();
	static void createGameobjects(std::vector<GameobjectCreateInfo>);

public:
	static vector2d<Block> Gameboard;

	static void LoadLevel(int level);
	static void Clear();

	static void SetTouchWin(bool value);

	static int GetGameboardWidth();
	static int GetGameboardHeight();
	static bool GetTouchWin();

	static void ShowBackground();

	static bool IsPointInGameboard(POINT point);
};