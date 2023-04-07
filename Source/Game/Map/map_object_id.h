#pragma once
#include <string>

enum MapobjectId {
	LEVEL0,
	LEVEL1,
	LEVEL2,
	LEVEL3,
	LEVEL4,
	LEVEL5,
	LEVEL6,

	LINE,
	JELLY,
};

int GetMapobjectIdByName(std::string gameobjectName);