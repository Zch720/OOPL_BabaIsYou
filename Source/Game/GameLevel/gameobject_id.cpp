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
	if (gameobjectName == "gameobject_baba") {
		return GAMEOBJECT_BABA;
	}
	if (gameobjectName == "gameobject_wall") {
		return GAMEOBJECT_WALL;
	}
	if (gameobjectName == "gameobject_flag") {
		return GAMEOBJECT_FLAG;
	}
	if (gameobjectName == "gameobject_rock") {
		return GAMEOBJECT_ROCK;
	}
	if (gameobjectName == "gameobject_water") {
		return GAMEOBJECT_WATER;
	}
	if (gameobjectName == "gameobject_skull") {
		return GAMEOBJECT_SKULL;
	}
	if (gameobjectName == "gameobject_lava") {
		return GAMEOBJECT_LAVA;
	}
	if (gameobjectName == "gameobject_grass") {
		return GAMEOBJECT_GRASS;
	}

	if (gameobjectName == "gameobject_text_is") {
		return GAMEOBJECT_TEXT_IS;
	}
	if (gameobjectName == "gameobject_text_and") {
		return GAMEOBJECT_TEXT_AND;
	}

	if (gameobjectName == "gameobject_text_baba") {
		return GAMEOBJECT_TEXT_BABA;
	}
	if (gameobjectName == "gameobject_text_wall") {
		return GAMEOBJECT_TEXT_WALL;
	}
	if (gameobjectName == "gameobject_text_flag") {
		return GAMEOBJECT_TEXT_FLAG;
	}
	if (gameobjectName == "gameobject_text_rock") {
		return GAMEOBJECT_TEXT_ROCK;
	}
	if (gameobjectName == "gameobject_text_water") {
		return GAMEOBJECT_TEXT_WATER;
	}
	if (gameobjectName == "gameobject_text_skull") {
		return GAMEOBJECT_TEXT_SKULL;
	}
	if (gameobjectName == "gameobject_text_lava") {
		return GAMEOBJECT_TEXT_LAVA;
	}
	if (gameobjectName == "gameobject_text_grass") {
		return GAMEOBJECT_TEXT_GRASS;
	}

	if (gameobjectName == "gameobject_text_you") {
		return GAMEOBJECT_TEXT_YOU;
	}
	if (gameobjectName == "gameobject_text_push") {
		return GAMEOBJECT_TEXT_PUSH;
	}
	if (gameobjectName == "gameobject_text_stop") {
		return GAMEOBJECT_TEXT_STOP;
	}
	if (gameobjectName == "gameobject_text_win") {
		return GAMEOBJECT_TEXT_WIN;
	}
	if (gameobjectName == "gameobject_text_sink") {
		return GAMEOBJECT_TEXT_SINK;
	}
	if (gameobjectName == "gameobject_text_defeat") {
		return GAMEOBJECT_TEXT_DEFEAT;
	}
	if (gameobjectName == "gameobject_text_hot") {
		return GAMEOBJECT_TEXT_HOT;
	}
	if (gameobjectName == "gameobject_text_melt") {
		return GAMEOBJECT_TEXT_MELT;
	}
	if (gameobjectName == "gameobject_text_shut") {
		return GAMEOBJECT_TEXT_SHUT;
	}
	if (gameobjectName == "gameobject_text_open") {
		return GAMEOBJECT_TEXT_OPEN;
	}

	char messageBuffer[215];
	sprintf_s(messageBuffer, "Error when get gameobject id by gameobject name. Didn't has gameobject named \"%s\"", gameobjectName.c_str());
	logError(messageBuffer);
	return -1;
}

std::string GetGameobjectNameById(GameobjectId gameobjectId) {
	switch (gameobjectId) {
	case GAMEOBJECT_BABA:
		return "gameobject_baba";
	case GAMEOBJECT_WALL:
		return "gameobject_wall";
	case GAMEOBJECT_FLAG:
		return "gameobject_flag";
	case GAMEOBJECT_ROCK:
		return "gameobject_rock";
	case GAMEOBJECT_WATER:
		return "gameobject_water";
	case GAMEOBJECT_SKULL:
		return "gameobject_skull";
	case GAMEOBJECT_LAVA:
		return "gameobject_lava";
	case GAMEOBJECT_GRASS:
		return "gameobject_grass";

	case GAMEOBJECT_TEXT_IS:
		return "gameobject_text_is";
	case GAMEOBJECT_TEXT_AND:
		return "gameobject_text_and";

	case GAMEOBJECT_TEXT_BABA:
		return "gameobject_text_baba";
	case GAMEOBJECT_TEXT_WALL:
		return "gameobject_text_wall";
	case GAMEOBJECT_TEXT_FLAG:
		return "gameobject_text_flag";
	case GAMEOBJECT_TEXT_ROCK:
		return "gameobject_text_rock";
	case GAMEOBJECT_TEXT_WATER:
		return "gameobject_text_water";
	case GAMEOBJECT_TEXT_SKULL:
		return "gameobject_text_skull";
	case GAMEOBJECT_TEXT_LAVA:
		return "gameobject_text_lava";
	case GAMEOBJECT_TEXT_GRASS:
		return "gameobject_text_grass";

	case GAMEOBJECT_TEXT_YOU:
		return "gameobject_text_you";
	case GAMEOBJECT_TEXT_PUSH:
		return "gameobject_text_push";
	case GAMEOBJECT_TEXT_STOP:
		return "gameobject_text_stop";
	case GAMEOBJECT_TEXT_WIN:
		return "gameobject_text_win";
	case GAMEOBJECT_TEXT_SINK:
		return "gameobject_text_sink";
	case GAMEOBJECT_TEXT_DEFEAT:
		return "gameobject_text_defeat";
	case GAMEOBJECT_TEXT_HOT:
		return "gameobject_text_hot";
	case GAMEOBJECT_TEXT_MELT:
		return "gameobject_text_melt";
	case GAMEOBJECT_TEXT_SHUT:
		return "gameobject_text_shut";
	case GAMEOBJECT_TEXT_OPEN:
		return "gameobject_text_open";

	default:
		char message[125];
		sprintf_s(message, "can't get gameobject name by id %d", gameobjectId);
		logError(message);
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
		char message[125];
		sprintf_s(message, "can't get gameobject of text %s", GetGameobjectNameById(gameobjectId).c_str());
		logError(message);
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
		char message[125];
		sprintf_s(message, "can't get %s texture directory", GetGameobjectNameById(gameobjectId).c_str());
		logError(message);
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