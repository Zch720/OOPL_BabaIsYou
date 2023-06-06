#include "stdafx.h"
#include <algorithm>
#include "property_id.h"
#include "../../Expansion/log.h"

std::unordered_map<std::string, PropertyId> PropertyIdProc::propertyNameAndId = {
	{"prop_none", PROPERTY_NONE},
	{"prop_you", PROPERTY_YOU},
	{"prop_win", PROPERTY_WIN},
	{"prop_stop", PROPERTY_STOP},
	{"prop_push", PROPERTY_PUSH},
	{"prop_sink", PROPERTY_SINK},
	{"prop_defeat", PROPERTY_DEFEAT},
	{"prop_melt", PROPERTY_MELT},
	{"prop_hot", PROPERTY_HOT},
	{"prop_move", PROPERTY_MOVE},
	{"prop_shut", PROPERTY_SHUT},
	{"prop_open", PROPERTY_OPEN},
	{"prop_red", PROPERTY_RED},
	{"prop_blue", PROPERTY_BLUE},
	{"prop_float", PROPERTY_FLOAT},
};
std::unordered_map<PropertyId, std::string> PropertyIdProc::propertyColor = {
	{PROPERTY_NONE, "default"},
	{PROPERTY_RED, "red"},
	{PROPERTY_BLUE, "blue"},
};


bool PropertyIdProc::IsPropertyId(int id) {
	return PROPERTY_ID_BEGIN <= id && id <= PROPERTY_ID_END;
}

bool PropertyIdProc::IsPropertyName(std::string name) {
	return propertyNameAndId.find(name) != propertyNameAndId.end();
}

std::string PropertyIdProc::GetNameById(PropertyId id) {
	auto idIterator = std::find_if(propertyNameAndId.begin(), propertyNameAndId.end(),
		[&](auto &&pair) { return pair.second == id; }
	);

	if (idIterator == propertyNameAndId.end()) {
		Log::LogError("<Property Id Porc> Can not find property name with id %d", id);
	}
	return idIterator -> first;
}

PropertyId PropertyIdProc::GetIdByName(std::string name) {
	if (propertyNameAndId.find(name) == propertyNameAndId.end()) {
		Log::LogError("<Property Id Proc> Can not find property id with name %s", name.c_str());
	}
	return propertyNameAndId[name];
}

std::string PropertyIdProc::GetColorName(PropertyId propertyId) {
	if (propertyColor.find(propertyId) == propertyColor.end()) {
		Log::LogError("<Property Id Proc> Property id %d did not has color name", propertyId);
	}
	return propertyColor[propertyId];
}