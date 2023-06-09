#pragma once

#include <unordered_map>
#include "game_level_config.h"

enum PropertyId {
	PROPERTY_NONE = PROPERTY_ID_BEGIN,
	PROPERTY_YOU,
	PROPERTY_STOP,
	PROPERTY_WIN,
	PROPERTY_PUSH,
	PROPERTY_SINK,
	PROPERTY_DEFEAT,
	PROPERTY_MELT,
	PROPERTY_HOT,
	PROPERTY_MOVE,
	PROPERTY_SHUT,
	PROPERTY_OPEN,
	PROPERTY_RED,
	PROPERTY_BLUE,
	PROPERTY_FLOAT,
	PROPERTY_WEAK,
};

class PropertyIdProc {
private:
	static std::unordered_map<std::string, PropertyId> propertyNameAndId;
	static std::unordered_map<PropertyId, std::string> propertyColor;

public:
	static bool IsPropertyId(int id);
	static bool IsPropertyName(std::string name);
	static PropertyId GetIdByName(std::string propertyName);
	static std::string GetNameById(PropertyId propertyId);
	static std::string GetColorName(PropertyId propertyId);
};