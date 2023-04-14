#include "stdafx.h"
#include "gameobject_id.h"
#include <unordered_map>
#include <algorithm>
#include "../../Expansion/log.h"

GameobjectId GAMEOBJECT_RECORD_TEXT_BEGIN = GAMEOBJECT_TEXT_IS;
GameobjectId GAMEOBJECT_RECORD_OPERATOR_TEXT_BEGIN = GAMEOBJECT_TEXT_IS;
GameobjectId GAMEOBJECT_RECORD_OPERATOR_TEXT_END = GAMEOBJECT_TEXT_AND;
GameobjectId GAMEOBJECT_RECORD_NOUN_TEXT_BEGIN = GAMEOBJECT_TEXT_BABA;
GameobjectId GAMEOBJECT_RECORD_NOUN_TEXT_END = GAMEOBJECT_TEXT_HEDGE;
GameobjectId GAMEOBJECT_RECORD_PROP_TEXT_BEGIN = GAMEOBJECT_TEXT_YOU;
GameobjectId GAMEOBJECT_RECORD_PROP_TEXT_END = GAMEOBJECT_TEXT_MOVE;

std::unordered_map<std::string, GameobjectId> gameobjectNameId = {
	{"crossed", GAMEOBJECT_CROSSED},
	{"baba", GAMEOBJECT_BABA},
	{"wall", GAMEOBJECT_WALL},
	{"flag", GAMEOBJECT_FLAG},
	{"rock", GAMEOBJECT_ROCK},
	{"water", GAMEOBJECT_WATER},
	{"skull", GAMEOBJECT_SKULL},
	{"lava", GAMEOBJECT_LAVA},
	{"grass", GAMEOBJECT_GRASS},
	{"tile", GAMEOBJECT_TILE},
	{"flower", GAMEOBJECT_FLOWER},
	{"brick", GAMEOBJECT_BRICK},
	{"ice", GAMEOBJECT_ICE},
	{"jelly", GAMEOBJECT_JELLY},
	{"algae", GAMEOBJECT_ALGAE},
	{"crab", GAMEOBJECT_CRAB},
	{"star", GAMEOBJECT_STAR},
	{"keke", GAMEOBJECT_KEKE},
	{"love", GAMEOBJECT_LOVE},
	{"pillar", GAMEOBJECT_PILLAR},
	{"key", GAMEOBJECT_KEY},
	{"door", GAMEOBJECT_DOOR},
	{"bubble", GAMEOBJECT_BUBBLE},
	{"hedge", GAMEOBJECT_HEDGE},

	{"text_is", GAMEOBJECT_TEXT_IS},
	{"text_and", GAMEOBJECT_TEXT_AND},

	{"text_baba", GAMEOBJECT_TEXT_BABA},
	{"text_wall", GAMEOBJECT_TEXT_WALL},
	{"text_flag", GAMEOBJECT_TEXT_FLAG},
	{"text_rock", GAMEOBJECT_TEXT_ROCK},
	{"text_water", GAMEOBJECT_TEXT_WATER},
	{"text_skull", GAMEOBJECT_TEXT_SKULL},
	{"text_lava", GAMEOBJECT_TEXT_LAVA},
	{"text_grass", GAMEOBJECT_TEXT_GRASS},
	{"text_jelly", GAMEOBJECT_TEXT_JELLY},
	{"text_algae", GAMEOBJECT_TEXT_ALGAE},
	{"text_crab", GAMEOBJECT_TEXT_CRAB},
	{"text_star", GAMEOBJECT_TEXT_STAR},
	{"text_keke", GAMEOBJECT_TEXT_KEKE},
	{"text_love", GAMEOBJECT_TEXT_LOVE},
	{"text_pillar", GAMEOBJECT_TEXT_PILLAR},
	{"text_key", GAMEOBJECT_TEXT_KEY},
	{"text_door", GAMEOBJECT_TEXT_DOOR},
	{"text_hedge", GAMEOBJECT_TEXT_HEDGE},

	{"text_you", GAMEOBJECT_TEXT_YOU},
	{"text_push", GAMEOBJECT_TEXT_PUSH},
	{"text_stop", GAMEOBJECT_TEXT_STOP},
	{"text_win", GAMEOBJECT_TEXT_WIN},
	{"text_sink", GAMEOBJECT_TEXT_SINK},
	{"text_defeat", GAMEOBJECT_TEXT_DEFEAT},
	{"text_hot", GAMEOBJECT_TEXT_HOT},
	{"text_melt", GAMEOBJECT_TEXT_MELT},
	{"text_shut", GAMEOBJECT_TEXT_SHUT},
	{"text_open", GAMEOBJECT_TEXT_OPEN},
	{"text_move", GAMEOBJECT_TEXT_MOVE}
};
std::unordered_map<GameobjectId, GameobjectId> gameobjectTextToObject = {
	{GAMEOBJECT_TEXT_BABA, GAMEOBJECT_BABA},
	{GAMEOBJECT_TEXT_WALL, GAMEOBJECT_WALL},
	{GAMEOBJECT_TEXT_FLAG, GAMEOBJECT_FLAG},
	{GAMEOBJECT_TEXT_ROCK, GAMEOBJECT_ROCK},
	{GAMEOBJECT_TEXT_WATER, GAMEOBJECT_WATER},
	{GAMEOBJECT_TEXT_SKULL, GAMEOBJECT_SKULL},
	{GAMEOBJECT_TEXT_LAVA, GAMEOBJECT_LAVA},
	{GAMEOBJECT_TEXT_GRASS, GAMEOBJECT_GRASS},
	{GAMEOBJECT_TEXT_JELLY, GAMEOBJECT_JELLY},
	{GAMEOBJECT_TEXT_ALGAE, GAMEOBJECT_ALGAE},
	{GAMEOBJECT_TEXT_CRAB, GAMEOBJECT_CRAB},
	{GAMEOBJECT_TEXT_STAR, GAMEOBJECT_STAR},
	{GAMEOBJECT_TEXT_KEKE, GAMEOBJECT_KEKE},
	{GAMEOBJECT_TEXT_LOVE, GAMEOBJECT_LOVE},
	{GAMEOBJECT_TEXT_PILLAR, GAMEOBJECT_PILLAR},
	{GAMEOBJECT_TEXT_KEY, GAMEOBJECT_KEY},
	{GAMEOBJECT_TEXT_DOOR, GAMEOBJECT_DOOR},
	{GAMEOBJECT_TEXT_HEDGE, GAMEOBJECT_HEDGE}
};
std::unordered_map<GameobjectId, int8_t> gameobjectZIndex = {
	{GAMEOBJECT_WATER, 2},
	{GAMEOBJECT_LAVA, 2},
	{GAMEOBJECT_TILE, 4},
	{GAMEOBJECT_ICE, 9},
	{GAMEOBJECT_GRASS, 10},
	{GAMEOBJECT_BRICK, 10},
	{GAMEOBJECT_FLOWER, 12},
	{GAMEOBJECT_BUBBLE, 12},
	{GAMEOBJECT_WALL, 14},
	{GAMEOBJECT_HEDGE, 14},
	{GAMEOBJECT_ALGAE, 15},
	{GAMEOBJECT_DOOR, 15},
	{GAMEOBJECT_ROCK, 16},
	{GAMEOBJECT_STAR, 16},
	{GAMEOBJECT_LOVE, 16},
	{GAMEOBJECT_PILLAR, 16},
	{GAMEOBJECT_KEY, 16},
	{GAMEOBJECT_FLAG, 17},
	{GAMEOBJECT_SKULL, 17},
	{GAMEOBJECT_JELLY, 17},
	{GAMEOBJECT_CRAB, 17},
	{GAMEOBJECT_BABA, 18},
	{GAMEOBJECT_KEKE, 18},
	{GAMEOBJECT_TEXT_IS, 20},
	{GAMEOBJECT_TEXT_AND, 20},
	{GAMEOBJECT_TEXT_BABA, 20},
	{GAMEOBJECT_TEXT_WALL, 20},
	{GAMEOBJECT_TEXT_FLAG, 20},
	{GAMEOBJECT_TEXT_ROCK, 20},
	{GAMEOBJECT_TEXT_WATER, 20},
	{GAMEOBJECT_TEXT_SKULL, 20},
	{GAMEOBJECT_TEXT_LAVA, 20},
	{GAMEOBJECT_TEXT_GRASS, 20},
	{GAMEOBJECT_TEXT_JELLY, 20},
	{GAMEOBJECT_TEXT_ALGAE, 20},
	{GAMEOBJECT_TEXT_CRAB, 20},
	{GAMEOBJECT_TEXT_STAR, 20},
	{GAMEOBJECT_TEXT_KEKE, 20},
	{GAMEOBJECT_TEXT_LOVE, 20},
	{GAMEOBJECT_TEXT_PILLAR, 20},
	{GAMEOBJECT_TEXT_KEY, 20},
	{GAMEOBJECT_TEXT_DOOR, 20},
	{GAMEOBJECT_TEXT_HEDGE, 20},
	{GAMEOBJECT_TEXT_YOU, 20},
	{GAMEOBJECT_TEXT_STOP, 20},
	{GAMEOBJECT_TEXT_WIN, 20},
	{GAMEOBJECT_TEXT_SINK, 20},
	{GAMEOBJECT_TEXT_DEFEAT, 20},
	{GAMEOBJECT_TEXT_HOT, 20},
	{GAMEOBJECT_TEXT_PUSH, 20},
	{GAMEOBJECT_TEXT_MELT, 20},
	{GAMEOBJECT_TEXT_SHUT, 20},
	{GAMEOBJECT_TEXT_SHUT, 20},
	{GAMEOBJECT_TEXT_OPEN, 20},
	{GAMEOBJECT_TEXT_MOVE, 20},
	{GAMEOBJECT_CROSSED, 21}
};

int GetGameobjectIdByName(std::string gameobjectName) {
	if (gameobjectNameId.find(gameobjectName) == gameobjectNameId.end()) {
		Log::LogError("Error when get gameobject id by gameobject name. Didn't has gameobject named \"%s\"", gameobjectName.c_str());
		return -1;
	}
	return gameobjectNameId[gameobjectName];
}
std::string GetGameobjectNameById(GameobjectId gameobjectId) {
	auto it = std::find_if(std::begin(gameobjectNameId), std::end(gameobjectNameId),
		[&](auto &&pair) {
			return pair.second == gameobjectId;
		}
	);

	if (it == std::end(gameobjectNameId)) {
		Log::LogError("can't get gameobject name by id %d", gameobjectId);
		return "";
	}
	return it->first;
}
int GetGameobjectByTextObject(GameobjectId gameobjectId) {
	if (gameobjectTextToObject.find(gameobjectId) == gameobjectTextToObject.end()) {
		Log::LogError("can't get gameobject of text %s", GetGameobjectNameById(gameobjectId).c_str());
		return -1;
	}
	return gameobjectTextToObject[gameobjectId];
}
int GetGameobjectZIndex(GameobjectId gameobjectId) {
	if (gameobjectZIndex.find(gameobjectId) != gameobjectZIndex.end()) {
		return gameobjectZIndex[gameobjectId];
	}

	Log::LogError("can't find gameobject %s z-index", GetGameobjectNameById(gameobjectId).c_str());
	return -1;
}
std::string GetTexturePathByGameobjectId(GameobjectId gameobjectId) {
	return "./resources/Sprites/" + GetGameobjectNameById(gameobjectId) + "/";
}

bool IsTextObject(GameobjectId gameobjectId) {
	return gameobjectId >= GAMEOBJECT_RECORD_TEXT_BEGIN;
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