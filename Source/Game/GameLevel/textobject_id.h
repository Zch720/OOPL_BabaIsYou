#pragma once

#include <unordered_map>
#include "game_level_config.h"
#include "object_id.h"
#include "property_id.h"

class TextobjectIdProc {
private:
	static std::unordered_map<ObjectId, ObjectId> textobjectToGameobject;
	static std::unordered_map<ObjectId, PropertyId> textobjectToProperty;

public:
	static bool IsOperatorTextobject(ObjectId textobjectId);
	static bool IsGameobjectTextobject(ObjectId textobjectId);
	static bool IsPropertyTextobject(ObjectId textobjectId);
	static ObjectId GetGameobjectId(ObjectId textobjectId);
	static PropertyId GetPropertyId(ObjectId textobjectId);
};