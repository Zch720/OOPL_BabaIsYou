#include "stdafx.h"
#include "gameobject_type.h"
#include "../Expansion/log.h"

int GetGameobjectTypeById(GameobjectId gameobjectId) {
	switch (gameobjectId) {
	case GAMEOBJECT_BABA:
		return OBJECT_TYPE_CHARACTER;

	case GAMEOBJECT_SKULL:
		return OBJECT_TYPE_DIRECTIONAL;

	case GAMEOBJECT_WALL:
	case GAMEOBJECT_WATER:
	case GAMEOBJECT_LAVA:
	case GAMEOBJECT_GRASS:
		return OBJECT_TYPE_TILED;

	case GAMEOBJECT_ROCK:
	case GAMEOBJECT_FLAG:
		return OBJECT_TYPE_STATIC;

	case GAMEOBJECT_TEXT_IS:

	case GAMEOBJECT_TEXT_BABA:
	case GAMEOBJECT_TEXT_WALL:
	case GAMEOBJECT_TEXT_FLAG:
	case GAMEOBJECT_TEXT_ROCK:
	case GAMEOBJECT_TEXT_WATER:
	case GAMEOBJECT_TEXT_SKULL:
	case GAMEOBJECT_TEXT_LAVA:
	case GAMEOBJECT_TEXT_GRASS:

	case GAMEOBJECT_TEXT_YOU:
	case GAMEOBJECT_TEXT_PUSH:
	case GAMEOBJECT_TEXT_STOP:
	case GAMEOBJECT_TEXT_WIN:
	case GAMEOBJECT_TEXT_SINK:
	case GAMEOBJECT_TEXT_DEFEAT:
	case GAMEOBJECT_TEXT_HOT:
	case GAMEOBJECT_TEXT_MELT:
		return OBJECT_TYPE_TEXT;

	default:
		char message[125];
		sprintf_s(message, "%s didn't has gameobject type", GetGameobjectNameById(gameobjectId).c_str());
		logError(message);
		return -1;
	}
}