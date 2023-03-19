#pragma once

#include <string>

enum GameobjectId {
	GAMEOBJECT_BABA,
	GAMEOBJECT_WALL,
	GAMEOBJECT_FLAG,

	GAMEOBJECT_TEXT_IS,

	GAMEOBJECT_TEXT_BABA,
	GAMEOBJECT_TEXT_WALL,
	GAMEOBJECT_TEXT_FLAG,

	GAMEOBJECT_TEXT_YOU,
	GAMEOBJECT_TEXT_PUSH,
	GAMEOBJECT_TEXT_STOP,
	GAMEOBJECT_TEXT_WIN
};

int GetGameobjectIdByName(std::string gameobjectName);
std::string GetGameobjectNameById(GameobjectId gameobjectId);
int GetGameobjectByTextObject(GameobjectId gameobjectId);
std::string GetTexturePathByGameobjectId(GameobjectId gameobjectId);

bool IsNounTextObject(GameobjectId gameobjectId);
bool IsPropTextObject(GameobjectId gameobjectId);