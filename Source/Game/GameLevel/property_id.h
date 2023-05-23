#pragma once

#include <string>

enum PropId: int {
	PROP_NONE,

	PROP_YOU,
	PROP_PUSH,
	PROP_STOP,
	PROP_WIN,
	PROP_SINK,
	PROP_DEFEAT,
	PROP_HOT,
	PROP_MELT,
	PROP_SHUT,
	PROP_OPEN,
	PROP_MOVE,
	PROP_RED,
	PROP_BLUE,
	PROP_FLOAT,
};

int GetPropIdByName(std::string propName);
std::string GetColorDirByPropId(PropId propId);