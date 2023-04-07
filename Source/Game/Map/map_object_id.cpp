#include "stdafx.h"
#include "map_object_id.h"
#include "../../Expansion/log.h"

int GetMapobjectIdByName(std::string mapobjectName) {
	if (mapobjectName == "level0") {
		return LEVEL0;
	}
	if (mapobjectName == "level1") {
		return LEVEL1;
	}
	if (mapobjectName == "level2") {
		return LEVEL2;
	}
	if (mapobjectName == "level3") {
		return LEVEL3;
	}
	if (mapobjectName == "level4") {
		return LEVEL4;
	}
	if (mapobjectName == "level5") {
		return LEVEL5;
	}
	if (mapobjectName == "level6") {
		return LEVEL6;
	}
	if (mapobjectName == "line") {
		return LINE;
	}
	if (mapobjectName == "jelly") {
		return JELLY;
	}

	Log::LogError("Error when get mapobject id by mapobject name. Didn't has mapobject named \"%s\"", mapobjectName.c_str());
	return -1;
}