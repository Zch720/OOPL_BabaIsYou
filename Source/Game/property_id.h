#pragma once

#include <string>

enum PropId: int {
	PROP_NONE,
	PROP_YOU,
	PROP_PUSH,
	PROP_STOP,
	PROP_WIN
};

int GetPropIdByName(std::string propName);
std::string GetColorDirByPropId(PropId propId);