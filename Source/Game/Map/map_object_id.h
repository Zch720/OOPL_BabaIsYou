#pragma once
#include <string>

enum MapobjectId {
	NONE,
	LEVEL0,
	LEVEL1,
	LEVEL2,
	LEVEL3,
	LEVEL4,
	LEVEL5,
	LEVEL6,
	LEVEL7,

	JELLY,

	LINE0,
	LINE1,
	LINE2,
	LINE3,
	LINE4,
	LINE5,
	LINE6,
	LINE7,
	LINE8,
	LINE9,
	LINE10,
	LINE11,
	LINE12,
	LINE13,
	LINE14,
	LINE15,

	BOX
};

int GetMapobjectIdByName(std::string gameobjectName);
std::string GetMapobjectNameById(MapobjectId gameobjectId);