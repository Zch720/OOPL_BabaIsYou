#include "stdafx.h"
#include "property_id.h"
#include <unordered_map>
#include "../../Expansion/log.h"

std::unordered_map<std::string, PropId> propNameId = {
	{"prop_none", PROP_NONE},
	{"prop_you", PROP_YOU},
	{"prop_push", PROP_PUSH},
	{"prop_stop", PROP_STOP},
	{"prop_win", PROP_WIN},
	{"prop_sink", PROP_SINK},
	{"prop_defeat", PROP_DEFEAT},
	{"prop_melt", PROP_MELT},
	{"prop_shut", PROP_SHUT},
	{"prop_open", PROP_OPEN},
	{"prop_move", PROP_MOVE},
	{"prop_red", PROP_RED},
	{"prop_blue", PROP_BLUE},
	{"prop_float", PROP_FLOAT},
};
std::unordered_map<PropId, std::string> propColorDir = {
	{PROP_NONE, "default"},
	{PROP_RED, "red"},
	{PROP_BLUE, "blue"},
};

int GetPropIdByName(std::string propName) {
	if (propNameId.find(propName) == propNameId.end()) {
		Log::LogError("Error when get prop id by prop name. Didn't has property named \"%s\"", propName.c_str());
		return -1;
	}
	return propNameId[propName];
}
std::string GetColorDirByPropId(PropId propId) {
	if (propColorDir.find(propId) == propColorDir.end()) {
		Log::LogError("Error when get color directory by prop id. Properity id \"%d\" is not color properity.", propId);
		return "";
	}
	return propColorDir[propId];
}