#include "stdafx.h"
#include "gameobject_id.h"
#include "../Expansion/log.h"

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
	if (gameobjectName == "gameobject_text_is") {
		return GAMEOBJECT_TEXT_IS;
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
	case GAMEOBJECT_TEXT_IS:
		return "gameobject_text_is";
	case GAMEOBJECT_TEXT_BABA:
		return "gameobject_text_baba";
	case GAMEOBJECT_TEXT_WALL:
		return "gameobject_text_wall";
	case GAMEOBJECT_TEXT_FLAG:
		return "gameobject_text_flag";
	case GAMEOBJECT_TEXT_ROCK:
		return "gameobject_text_rock";
	case GAMEOBJECT_TEXT_YOU:
		return "gameobject_text_you";
	case GAMEOBJECT_TEXT_PUSH:
		return "gameobject_text_push";
	case GAMEOBJECT_TEXT_STOP:
		return "gameobject_text_stop";
	case GAMEOBJECT_TEXT_WIN:
		return "gameobject_text_win";
	default:
		char message[125];
		sprintf_s(message, "can't get gameobject name by id %d", gameobjectId);
		logError(message);
		return "";
	}
}

bool IsTextObject(GameobjectId gameobjectId) {
	switch (gameobjectId) {
	case GAMEOBJECT_TEXT_IS:
	case GAMEOBJECT_TEXT_BABA:
	case GAMEOBJECT_TEXT_WALL:
	case GAMEOBJECT_TEXT_FLAG:
	case GAMEOBJECT_TEXT_ROCK:
	case GAMEOBJECT_TEXT_YOU:
	case GAMEOBJECT_TEXT_PUSH:
	case GAMEOBJECT_TEXT_STOP:
	case GAMEOBJECT_TEXT_WIN:
		return true;
	default:
		return false;
	}
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
	case GAMEOBJECT_TEXT_IS:
		return textureResourcesDir + "text_is/";
	case GAMEOBJECT_TEXT_BABA:
		return textureResourcesDir + "text_baba/";
	case GAMEOBJECT_TEXT_WALL:
		return textureResourcesDir + "text_wall/";
	case GAMEOBJECT_TEXT_FLAG:
		return textureResourcesDir + "text_flag/";
	case GAMEOBJECT_TEXT_ROCK:
		return textureResourcesDir + "text_rock/";
	case GAMEOBJECT_TEXT_YOU:
		return textureResourcesDir + "text_you/";
	case GAMEOBJECT_TEXT_PUSH:
		return textureResourcesDir + "text_push/";
	case GAMEOBJECT_TEXT_STOP:
		return textureResourcesDir + "text_stop/";
	case GAMEOBJECT_TEXT_WIN:
		return textureResourcesDir + "text_win/";
	default:
		char message[125];
		sprintf_s(message, "can't get %s texture directory", GetGameobjectNameById(gameobjectId).c_str());
		logError(message);
		return "";
	}
}

bool IsNounTextObject(GameobjectId gameobjectId) {
	switch (gameobjectId) {
	case GAMEOBJECT_TEXT_BABA:
	case GAMEOBJECT_TEXT_WALL:
	case GAMEOBJECT_TEXT_FLAG:
	case GAMEOBJECT_TEXT_ROCK:
		return true;
	default:
		return false;
	}
}
bool IsPropTextObject(GameobjectId gameobjectId) {
	switch (gameobjectId) {
	case GAMEOBJECT_TEXT_YOU:
	case GAMEOBJECT_TEXT_PUSH:
	case GAMEOBJECT_TEXT_STOP:
	case GAMEOBJECT_TEXT_WIN:
		return true;
	default:
		return false;
	}
}