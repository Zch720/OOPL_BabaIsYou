#include "stdafx.h"
#include "gameobject_type.h"
#include "gameobject_id.h"

int GetGameobjectTypeById(int gameobjectId) {
	switch (gameobjectId) {
	case GAMEOBJECT_BABA:
		return OBJECT_TYPE_CHARACTER;

	case GAMEOBJECT_WALL:
		return OBJECT_TYPE_TILED;

	case GAMEOBJECT_FLAG:
		return OBJECT_TYPE_STATIC;

	case GAMEOBJECT_TEXT_IS:
	case GAMEOBJECT_TEXT_BABA:
	case GAMEOBJECT_TEXT_WALL:
	case GAMEOBJECT_TEXT_FLAG:
	case GAMEOBJECT_TEXT_YOU:
	case GAMEOBJECT_TEXT_PUSH:
	case GAMEOBJECT_TEXT_STOP:
	case GAMEOBJECT_TEXT_WIN:
		return OBJECT_TYPE_TEXT;

	default:
		return -1;
	}
}