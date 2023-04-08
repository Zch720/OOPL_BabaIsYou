#pragma once

#include <string>

enum GameobjectId {
	GAMEOBJECT_NONE,

	GAMEOBJECT_BABA,
	GAMEOBJECT_FLAG,
	GAMEOBJECT_ROCK,
	GAMEOBJECT_WATER,
	GAMEOBJECT_SKULL,
	GAMEOBJECT_LAVA,
	GAMEOBJECT_GRASS,
	GAMEOBJECT_WALL,
	GAMEOBJECT_TILE,
	GAMEOBJECT_FLOWER,
	GAMEOBJECT_BRICK,

	GAMEOBJECT_TEXT_IS,
	GAMEOBJECT_TEXT_AND,

	GAMEOBJECT_TEXT_BABA,
	GAMEOBJECT_TEXT_WALL,
	GAMEOBJECT_TEXT_FLAG,
	GAMEOBJECT_TEXT_ROCK,
	GAMEOBJECT_TEXT_WATER,
	GAMEOBJECT_TEXT_SKULL,
	GAMEOBJECT_TEXT_LAVA,
	GAMEOBJECT_TEXT_GRASS,

	GAMEOBJECT_TEXT_YOU,
	GAMEOBJECT_TEXT_STOP,
	GAMEOBJECT_TEXT_WIN,
	GAMEOBJECT_TEXT_SINK,
	GAMEOBJECT_TEXT_DEFEAT,
	GAMEOBJECT_TEXT_HOT,
	GAMEOBJECT_TEXT_PUSH,
	GAMEOBJECT_TEXT_MELT,
	GAMEOBJECT_TEXT_SHUT,
	GAMEOBJECT_TEXT_OPEN
};

int GetGameobjectIdByName(std::string gameobjectName);
std::string GetGameobjectNameById(GameobjectId gameobjectId);
int GetGameobjectByTextObject(GameobjectId gameobjectId);
std::string GetTexturePathByGameobjectId(GameobjectId gameobjectId);

bool IsTextObject(GameobjectId gameobjectId);
bool IsNounTextObject(GameobjectId gameobjectId);
bool IsPropTextObject(GameobjectId gameobjectId);
bool IsOperatorTextObject(GameobjectId gameobjectId);