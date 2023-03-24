#pragma once

#include "gameobject_id.h"

enum GameobjectType {
	OBJECT_TYPE_CHARACTER,
	OBJECT_TYPE_STATIC,
	OBJECT_TYPE_TILED,
	OBJECT_TYPE_TEXT,
	OBJECT_TYPE_DIRECTIONAL
};

int GetGameobjectTypeById(GameobjectId gameobjectId);