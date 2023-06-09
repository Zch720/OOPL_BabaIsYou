#pragma once

#include <unordered_map>
#include "object_id.h"

enum ObjectType {
	TYPE_NONE,
	TYPE_TEXT,
	TYPE_TILED,
	TYPE_STATIC,
	TYPE_CHARACTER,
	TYPE_ANIMATION,
	TYPE_DIRECTION,
	TYPE_ANIMATION_DIRECTION,
};

class ObjectTypeProc {
private:
	static std::unordered_map<ObjectId, ObjectType> gameobjectIdAndType;

public:
	static ObjectType GetType(ObjectId gameobjectId);
};