#include "stdafx.h"
#include "map_object_id.h"
#include "../../Expansion/log.h"

int GetMapobjectIdByName(std::string mapobjectName) {
	if (mapobjectName == "line_0") {
		return LINE0;
	}
	if (mapobjectName == "line_1") {
		return LINE1;
	}
	if (mapobjectName == "line_2") {
		return LINE2;
	}
	if (mapobjectName == "line_3") {
		return LINE3;
	}
	if (mapobjectName == "line_4") {
		return LINE4;
	}
	if (mapobjectName == "line_5") {
		return LINE5;
	}
	if (mapobjectName == "line_6") {
		return LINE6;
	}
	if (mapobjectName == "line_7") {
		return LINE7;
	}
	if (mapobjectName == "line_8") {
		return LINE8;
	}
	if (mapobjectName == "line_9") {
		return LINE9;
	}
	if (mapobjectName == "line_10") {
		return LINE10;
	}
	if (mapobjectName == "line_11") {
		return LINE11;
	}
	if (mapobjectName == "line_12") {
		return LINE12;
	}
	if (mapobjectName == "line_13") {
		return LINE13;
	}
	if (mapobjectName == "line_14") {
		return LINE14;
	}
	if (mapobjectName == "line_15") {
		return LINE15;
	}

	if (mapobjectName == "box") {
		return BOX;
	}

	if (mapobjectName == "level_0") {
		return LEVEL0;
	}
	if (mapobjectName == "level_1") {
		return LEVEL1;
	}
	if (mapobjectName == "level_2") {
		return LEVEL2;
	}
	if (mapobjectName == "level_3") {
		return LEVEL3;
	}
	if (mapobjectName == "level_4") {
		return LEVEL4;
	}
	if (mapobjectName == "level_5") {
		return LEVEL5;
	}
	if (mapobjectName == "level_6") {
		return LEVEL6;
	}
	if (mapobjectName == "level_7") {
		return LEVEL7;
	}
	if (mapobjectName == "level_8") {
		return LEVEL8;
	}
	if (mapobjectName == "level_9") {
		return LEVEL9;
	}
	if (mapobjectName == "level_10") {
		return LEVEL10;
	}
	if (mapobjectName == "level_11") {
		return LEVEL11;
	}
	if (mapobjectName == "level_12") {
		return LEVEL12;
	}
	if (mapobjectName == "level_13") {
		return LEVEL13;
	}
	if (mapobjectName == "level_ex1") {
		return LEVELEX1;
	}
	if (mapobjectName == "level_ex2") {
		return LEVELEX2;
	}
	if (mapobjectName == "level_ex3") {
		return LEVELEX3;
	}
	if (mapobjectName == "level_ex4") {
		return LEVELEX4;
	}
	if (mapobjectName == "level_ex5") {
		return LEVELEX5;
	}
	if (mapobjectName == "level_ex6") {
		return LEVELEX6;
	}

	if (mapobjectName == "map") {
		return MAP;
	}
	if (mapobjectName == "jelly") {
		return JELLY;
	}
	if (mapobjectName == "mountain") {
		return MOUNTAIN;
	}
	if (mapobjectName == "leaf") {
		return LEAF;
	}
	if (mapobjectName == "pillar") {
		return PILLAR;
	}
	if (mapobjectName == "flower") {
		return FLOWER;
	}
	if (mapobjectName == "tree") {
		return TREE;
	}
	if (mapobjectName == "moon") {
		return MOON;
	}

	Log::LogError("Error when get mapobject id by mapobject name. Didn't has mapobject named \"%s\"", mapobjectName.c_str());
	return -1;
}

std::string GetMapobjectNameById(MapobjectId mapobjectId) {
	switch (mapobjectId) {
	case LINE0:
		return "line_0";
	case LINE1:
		return "line_1";
	case LINE2:
		return "line_2";
	case LINE3:
		return "line_3";
	case LINE4:
		return "line_4";
	case LINE5:
		return "line_5";
	case LINE6:
		return "line_6";
	case LINE7:
		return "line_7";
	case LINE8:
		return "line_8";
	case LINE9:
		return "line_9";
	case LINE10:
		return "line_10";
	case LINE11:
		return "line_11";
	case LINE12:
		return "line_12";
	case LINE13:
		return "line_13";
	case LINE14:
		return "line_14";
	case LINE15:
		return "line_15";

	case BOX:
		return "box";

	case LEVEL0:
		return "level_0";
	case LEVEL1:
		return "level_1";
	case LEVEL2:
		return "level_2";
	case LEVEL3:
		return "level_3";
	case LEVEL4:
		return "level_4";
	case LEVEL5:
		return "level_5";
	case LEVEL6:
		return "level_6";
	case LEVEL7:
		return "level_7";
	case LEVEL8:
		return "level_8";
	case LEVEL9:
		return "level_9";
	case LEVEL10:
		return "level_10";
	case LEVEL11:
		return "level_11";
	case LEVEL12:
		return "level_12";
	case LEVEL13:
		return "level_13";
	case LEVELEX1:
		return "level_ex1";
	case LEVELEX2:
		return "level_ex2";
	case LEVELEX3:
		return "level_ex3";
	case LEVELEX4:
		return "level_ex4";
	case LEVELEX5:
		return "level_ex5";
	case LEVELEX6:
		return "level_ex6";

	case MAP:
		return "map";
	case JELLY:
		return "jelly";
	case MOUNTAIN:
		return "mountain";
	case LEAF:
		return "leaf";
	case PILLAR:
		return "pillar";
	case FLOWER:
		return "flower";
	case TREE:
		return "tree";
	case MOON:
		return "moon";

	default:
		Log::LogError("can't get mapobject name by id %d", mapobjectId);
		return "";
	}
}