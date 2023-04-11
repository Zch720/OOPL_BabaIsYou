#include "stdafx.h"
#include "gameobject_id.h"
#include <unordered_map>
#include "../../Expansion/log.h"

GameobjectId GAMEOBJECT_RECORD_TEXT_BEGIN = GAMEOBJECT_TEXT_IS;
GameobjectId GAMEOBJECT_RECORD_OPERATOR_TEXT_BEGIN = GAMEOBJECT_TEXT_IS;
GameobjectId GAMEOBJECT_RECORD_OPERATOR_TEXT_END = GAMEOBJECT_TEXT_AND;
GameobjectId GAMEOBJECT_RECORD_NOUN_TEXT_BEGIN = GAMEOBJECT_TEXT_BABA;
GameobjectId GAMEOBJECT_RECORD_NOUN_TEXT_END = GAMEOBJECT_TEXT_HEDGE;
GameobjectId GAMEOBJECT_RECORD_PROP_TEXT_BEGIN = GAMEOBJECT_TEXT_YOU;
GameobjectId GAMEOBJECT_RECORD_PROP_TEXT_END = GAMEOBJECT_TEXT_MOVE;

int GetGameobjectIdByName(std::string gameobjectName) {
	if (gameobjectName == "crossed") {
		return GAMEOBJECT_CROSSED;
	}
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
	if (gameobjectName == "tile") {
		return GAMEOBJECT_TILE;
	}
	if (gameobjectName == "flower") {
		return GAMEOBJECT_FLOWER;
	}
	if (gameobjectName == "brick") {
		return GAMEOBJECT_BRICK;
	}
	if (gameobjectName == "ice") {
		return GAMEOBJECT_ICE;
	}
	if (gameobjectName == "jelly") {
		return GAMEOBJECT_JELLY;
	}
	if (gameobjectName == "algae") {
		return GAMEOBJECT_ALGAE;
	}
	if (gameobjectName == "crab") {
		return GAMEOBJECT_CRAB;
	}
	if (gameobjectName == "star") {
		return GAMEOBJECT_STAR;
	}
	if (gameobjectName == "keke") {
		return GAMEOBJECT_KEKE;
	}
	if (gameobjectName == "love") {
		return GAMEOBJECT_LOVE;
	}
	if (gameobjectName == "pillar") {
		return GAMEOBJECT_PILLAR;
	}
	if (gameobjectName == "key") {
		return GAMEOBJECT_KEY;
	}
	if (gameobjectName == "door") {
		return GAMEOBJECT_DOOR;
	}
	if (gameobjectName == "bubble") {
		return GAMEOBJECT_BUBBLE;
	}
	if (gameobjectName == "hedge") {
		return GAMEOBJECT_HEDGE;
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
	if (gameobjectName == "text_jelly") {
		return GAMEOBJECT_TEXT_JELLY;
	}
	if (gameobjectName == "text_algae") {
		return GAMEOBJECT_TEXT_ALGAE;
	}
	if (gameobjectName == "text_crab") {
		return GAMEOBJECT_TEXT_CRAB;
	}
	if (gameobjectName == "text_star") {
		return GAMEOBJECT_TEXT_STAR;
	}
	if (gameobjectName == "text_keke") {
		return GAMEOBJECT_TEXT_KEKE;
	}
	if (gameobjectName == "text_love") {
		return GAMEOBJECT_TEXT_LOVE;
	}
	if (gameobjectName == "text_pillar") {
		return GAMEOBJECT_TEXT_PILLAR;
	}
	if (gameobjectName == "text_key") {
		return GAMEOBJECT_TEXT_KEY;
	}
	if (gameobjectName == "text_door") {
		return GAMEOBJECT_TEXT_DOOR;
	}
	if (gameobjectName == "text_hedge") {
		return GAMEOBJECT_TEXT_HEDGE;
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
	if (gameobjectName == "text_move") {
		return GAMEOBJECT_TEXT_MOVE;
	}

	Log::LogError("Error when get gameobject id by gameobject name. Didn't has gameobject named \"%s\"", gameobjectName.c_str());
	return -1;
}

std::string GetGameobjectNameById(GameobjectId gameobjectId) {
	switch (gameobjectId) {
	case GAMEOBJECT_CROSSED:
		return "crossed";
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
	case GAMEOBJECT_TILE:
		return "tile";
	case GAMEOBJECT_FLOWER:
		return "flower";
	case GAMEOBJECT_BRICK:
		return "brick";
	case GAMEOBJECT_ICE:
		return "ice";
	case GAMEOBJECT_JELLY:
		return "jelly";
	case GAMEOBJECT_ALGAE:
		return "algae";
	case GAMEOBJECT_CRAB:
		return "crab";
	case GAMEOBJECT_STAR:
		return "star";
	case GAMEOBJECT_KEKE:
		return "keke";
	case GAMEOBJECT_LOVE:
		return "love";
	case GAMEOBJECT_PILLAR:
		return "pillar";
	case GAMEOBJECT_KEY:
		return "key";
	case GAMEOBJECT_DOOR:
		return "door";
	case GAMEOBJECT_BUBBLE:
		return "bubble";
	case GAMEOBJECT_HEDGE:
		return "hedge";

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
	case GAMEOBJECT_TEXT_JELLY:
		return "text_jelly";
	case GAMEOBJECT_TEXT_ALGAE:
		return "text_algae";
	case GAMEOBJECT_TEXT_CRAB:
		return "text_crab";
	case GAMEOBJECT_TEXT_STAR:
		return "text_star";
	case GAMEOBJECT_TEXT_KEKE:
		return "text_keke";
	case GAMEOBJECT_TEXT_LOVE:
		return "text_love";
	case GAMEOBJECT_TEXT_PILLAR:
		return "text_pillar";
	case GAMEOBJECT_TEXT_KEY:
		return "text_key";
	case GAMEOBJECT_TEXT_DOOR:
		return "text_door";
	case GAMEOBJECT_TEXT_HEDGE:
		return "text_hedge";

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
	case GAMEOBJECT_TEXT_MOVE:
		return "text_move";

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
	case GAMEOBJECT_TEXT_JELLY:
		return GAMEOBJECT_JELLY;
	case GAMEOBJECT_TEXT_ALGAE:
		return GAMEOBJECT_TEXT_ALGAE;
	case GAMEOBJECT_TEXT_CRAB:
		return GAMEOBJECT_CRAB;
	case GAMEOBJECT_TEXT_STAR:
		return GAMEOBJECT_STAR;
	case GAMEOBJECT_TEXT_KEKE:
		return GAMEOBJECT_KEKE;
	case GAMEOBJECT_TEXT_LOVE:
		return GAMEOBJECT_LOVE;
	case GAMEOBJECT_TEXT_PILLAR:
		return GAMEOBJECT_PILLAR;
	case GAMEOBJECT_TEXT_KEY:
		return GAMEOBJECT_KEY;
	case GAMEOBJECT_TEXT_DOOR:
		return GAMEOBJECT_DOOR;
	case GAMEOBJECT_TEXT_HEDGE:
		return GAMEOBJECT_HEDGE;
	default:
		Log::LogError("can't get gameobject of text %s", GetGameobjectNameById(gameobjectId).c_str());
		return -1;
	}
}

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