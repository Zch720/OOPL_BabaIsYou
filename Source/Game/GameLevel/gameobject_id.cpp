#include "stdafx.h"
#include "gameobject_id.h"
#include "../../Expansion/log.h"

GameobjectId GAMEOBJECT_RECORD_TEXT_BEGIN = GAMEOBJECT_TEXT_IS;
GameobjectId GAMEOBJECT_RECORD_OPERATOR_TEXT_BEGIN = GAMEOBJECT_TEXT_IS;
GameobjectId GAMEOBJECT_RECORD_OPERATOR_TEXT_END = GAMEOBJECT_TEXT_AND;
GameobjectId GAMEOBJECT_RECORD_NOUN_TEXT_BEGIN = GAMEOBJECT_TEXT_BABA;
GameobjectId GAMEOBJECT_RECORD_NOUN_TEXT_END = GAMEOBJECT_TEXT_GRASS;
GameobjectId GAMEOBJECT_RECORD_PROP_TEXT_BEGIN = GAMEOBJECT_TEXT_YOU;
GameobjectId GAMEOBJECT_RECORD_PROP_TEXT_END = GAMEOBJECT_TEXT_OPEN;

int GetGameobjectIdByName(std::string gameobjectName) {
	if (gameobjectName == "baba") {
		return GAMEOBJECT_BABA;
	}
	if (gameobjectName == "wall") {
		return GAMEOBJECT_WALL;
	}
	if (gameobjectName == "flag") {
		return GAMEOBJECT_FLAG;
	}
	if (gameobjectName == "rock") {
		return GAMEOBJECT_ROCK;
	}
	if (gameobjectName == "water") {
		return GAMEOBJECT_WATER;
	}
	if (gameobjectName == "skull") {
		return GAMEOBJECT_SKULL;
	}
	if (gameobjectName == "lava") {
		return GAMEOBJECT_LAVA;
	}
	if (gameobjectName == "grass") {
		return GAMEOBJECT_GRASS;
	}

	if (gameobjectName == "text_is") {
		return GAMEOBJECT_TEXT_IS;
	}
	if (gameobjectName == "text_and") {
		return GAMEOBJECT_TEXT_AND;
	}

	if (gameobjectName == "text_baba") {
		return GAMEOBJECT_TEXT_BABA;
	}
	if (gameobjectName == "text_wall") {
		return GAMEOBJECT_TEXT_WALL;
	}
	if (gameobjectName == "text_flag") {
		return GAMEOBJECT_TEXT_FLAG;
	}
	if (gameobjectName == "text_rock") {
		return GAMEOBJECT_TEXT_ROCK;
	}
	if (gameobjectName == "text_water") {
		return GAMEOBJECT_TEXT_WATER;
	}
	if (gameobjectName == "text_skull") {
		return GAMEOBJECT_TEXT_SKULL;
	}
	if (gameobjectName == "text_lava") {
		return GAMEOBJECT_TEXT_LAVA;
	}
	if (gameobjectName == "text_grass") {
		return GAMEOBJECT_TEXT_GRASS;
	}

	if (gameobjectName == "text_you") {
		return GAMEOBJECT_TEXT_YOU;
	}
	if (gameobjectName == "text_push") {
		return GAMEOBJECT_TEXT_PUSH;
	}
	if (gameobjectName == "text_stop") {
		return GAMEOBJECT_TEXT_STOP;
	}
	if (gameobjectName == "text_win") {
		return GAMEOBJECT_TEXT_WIN;
	}
	if (gameobjectName == "text_sink") {
		return GAMEOBJECT_TEXT_SINK;
	}
	if (gameobjectName == "text_defeat") {
		return GAMEOBJECT_TEXT_DEFEAT;
	}
	if (gameobjectName == "text_hot") {
		return GAMEOBJECT_TEXT_HOT;
	}
	if (gameobjectName == "text_melt") {
		return GAMEOBJECT_TEXT_MELT;
	}
	if (gameobjectName == "text_shut") {
		return GAMEOBJECT_TEXT_SHUT;
	}
	if (gameobjectName == "text_open") {
		return GAMEOBJECT_TEXT_OPEN;
	}

	Log::LogError("Error when get gameobject id by gameobject name. Didn't has gameobject named \"%s\"", gameobjectName.c_str());
	return -1;
}

std::string GetGameobjectNameById(GameobjectId gameobjectId) {
	switch (gameobjectId) {
	case GAMEOBJECT_BABA:
		return "baba";
	case GAMEOBJECT_WALL:
		return "wall";
	case GAMEOBJECT_FLAG:
		return "flag";
	case GAMEOBJECT_ROCK:
		return "rock";
	case GAMEOBJECT_WATER:
		return "water";
	case GAMEOBJECT_SKULL:
		return "skull";
	case GAMEOBJECT_LAVA:
		return "lava";
	case GAMEOBJECT_GRASS:
		return "grass";

	case GAMEOBJECT_TEXT_IS:
		return "text_is";
	case GAMEOBJECT_TEXT_AND:
		return "text_and";

	case GAMEOBJECT_TEXT_BABA:
		return "text_baba";
	case GAMEOBJECT_TEXT_WALL:
		return "text_wall";
	case GAMEOBJECT_TEXT_FLAG:
		return "text_flag";
	case GAMEOBJECT_TEXT_ROCK:
		return "text_rock";
	case GAMEOBJECT_TEXT_WATER:
		return "text_water";
	case GAMEOBJECT_TEXT_SKULL:
		return "text_skull";
	case GAMEOBJECT_TEXT_LAVA:
		return "text_lava";
	case GAMEOBJECT_TEXT_GRASS:
		return "text_grass";

	case GAMEOBJECT_TEXT_YOU:
		return "text_you";
	case GAMEOBJECT_TEXT_PUSH:
		return "text_push";
	case GAMEOBJECT_TEXT_STOP:
		return "text_stop";
	case GAMEOBJECT_TEXT_WIN:
		return "text_win";
	case GAMEOBJECT_TEXT_SINK:
		return "text_sink";
	case GAMEOBJECT_TEXT_DEFEAT:
		return "text_defeat";
	case GAMEOBJECT_TEXT_HOT:
		return "text_hot";
	case GAMEOBJECT_TEXT_MELT:
		return "text_melt";
	case GAMEOBJECT_TEXT_SHUT:
		return "text_shut";
	case GAMEOBJECT_TEXT_OPEN:
		return "text_open";

	default:
		Log::LogError("can't get gameobject name by id %d", gameobjectId);
		return "";
	}
}

bool IsTextObject(GameobjectId gameobjectId) {
	return gameobjectId >= GAMEOBJECT_RECORD_TEXT_BEGIN;
}

int GetGameobjectByTextObject(GameobjectId gameobjectId) {
	switch (gameobjectId) {
	case GAMEOBJECT_TEXT_BABA:
		return GAMEOBJECT_BABA;
	case GAMEOBJECT_TEXT_WALL:
		return GAMEOBJECT_WALL;
	case GAMEOBJECT_TEXT_FLAG:
		return GAMEOBJECT_FLAG;
	case GAMEOBJECT_TEXT_ROCK:
		return GAMEOBJECT_ROCK;
	case GAMEOBJECT_TEXT_WATER:
		return GAMEOBJECT_WATER;
	case GAMEOBJECT_TEXT_SKULL:
		return GAMEOBJECT_SKULL;
	case GAMEOBJECT_TEXT_LAVA:
		return GAMEOBJECT_LAVA;
	case GAMEOBJECT_TEXT_GRASS:
		return GAMEOBJECT_GRASS;
	default:
		Log::LogError("can't get gameobject of text %s", GetGameobjectNameById(gameobjectId).c_str());
		return -1;
	}
}

std::string GetTexturePathByGameobjectId(GameobjectId gameobjectId) {
	std::string textureResourcesDir = "./resources/Sprites/";

	switch (gameobjectId) {
	case GAMEOBJECT_BABA:
		return textureResourcesDir + "baba/";
	case GAMEOBJECT_WALL:
		return textureResourcesDir + "wall/";
	case GAMEOBJECT_FLAG:
		return textureResourcesDir + "flag/";
	case GAMEOBJECT_ROCK:
		return textureResourcesDir + "rock/";
	case GAMEOBJECT_WATER:
		return textureResourcesDir + "water/";
	case GAMEOBJECT_SKULL:
		return textureResourcesDir + "skull/";
	case GAMEOBJECT_LAVA:
		return textureResourcesDir + "lava/";
	case GAMEOBJECT_GRASS:
		return textureResourcesDir + "grass/";

	case GAMEOBJECT_TEXT_IS:
		return textureResourcesDir + "text_is/";
	case GAMEOBJECT_TEXT_AND:
		return textureResourcesDir + "text_and/";

	case GAMEOBJECT_TEXT_BABA:
		return textureResourcesDir + "text_baba/";
	case GAMEOBJECT_TEXT_WALL:
		return textureResourcesDir + "text_wall/";
	case GAMEOBJECT_TEXT_FLAG:
		return textureResourcesDir + "text_flag/";
	case GAMEOBJECT_TEXT_ROCK:
		return textureResourcesDir + "text_rock/";
	case GAMEOBJECT_TEXT_WATER:
		return textureResourcesDir + "text_water/";
	case GAMEOBJECT_TEXT_SKULL:
		return textureResourcesDir + "text_skull/";
	case GAMEOBJECT_TEXT_LAVA:
		return textureResourcesDir + "text_lava/";
	case GAMEOBJECT_TEXT_GRASS:
		return textureResourcesDir + "text_grass/";

	case GAMEOBJECT_TEXT_YOU:
		return textureResourcesDir + "text_you/";
	case GAMEOBJECT_TEXT_PUSH:
		return textureResourcesDir + "text_push/";
	case GAMEOBJECT_TEXT_STOP:
		return textureResourcesDir + "text_stop/";
	case GAMEOBJECT_TEXT_WIN:
		return textureResourcesDir + "text_win/";
	case GAMEOBJECT_TEXT_SINK:
		return textureResourcesDir + "text_sink/";
	case GAMEOBJECT_TEXT_DEFEAT:
		return textureResourcesDir + "text_defeat/";
	case GAMEOBJECT_TEXT_HOT:
		return textureResourcesDir + "text_hot/";
	case GAMEOBJECT_TEXT_MELT:
		return textureResourcesDir + "text_melt/";
	case GAMEOBJECT_TEXT_SHUT:
		return textureResourcesDir + "text_shut/";
	case GAMEOBJECT_TEXT_OPEN:
		return textureResourcesDir + "text_open/";

	default:
		Log::LogError("can't get %s texture directory", GetGameobjectNameById(gameobjectId).c_str());
		return "";
	}
}

bool IsNounTextObject(GameobjectId gameobjectId) {
	return GAMEOBJECT_RECORD_NOUN_TEXT_BEGIN <= gameobjectId
		&& gameobjectId <= GAMEOBJECT_RECORD_NOUN_TEXT_END;
}
bool IsPropTextObject(GameobjectId gameobjectId) {
	return GAMEOBJECT_RECORD_PROP_TEXT_BEGIN <= gameobjectId
		&& gameobjectId <= GAMEOBJECT_RECORD_PROP_TEXT_END;
}
bool IsOperatorTextObject(GameobjectId gameobjectId) {
	return GAMEOBJECT_RECORD_OPERATOR_TEXT_BEGIN <= gameobjectId
		&& gameobjectId <= GAMEOBJECT_RECORD_OPERATOR_TEXT_END;
}