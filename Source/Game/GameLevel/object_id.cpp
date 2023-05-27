#include "stdafx.h"
#include <algorithm>
#include "object_id.h"
#include "../../Expansion/log.h"

std::unordered_map<std::string, ObjectId> ObjectIdProc::objectNameAndId = {
	{"none", OBJECT_NONE},
	{"crossed", OBJECT_CROSSED},
	{"texts", GAMEOBJECT_TEXTS},
	{"baba", GAMEOBJECT_BABA},
	{"flag", GAMEOBJECT_FLAG},
	{"wall", GAMEOBJECT_WALL},
	{"rock", GAMEOBJECT_ROCK},
	{"tile", GAMEOBJECT_TILE},
	{"grass", GAMEOBJECT_GRASS},
	{"water", GAMEOBJECT_WATER},
	{"skull", GAMEOBJECT_SKULL},
	{"lava", GAMEOBJECT_LAVA},
	{"flower", GAMEOBJECT_FLOWER},
	{"brick", GAMEOBJECT_BRICK},
	{"ice", GAMEOBJECT_ICE},
	{"jelly", GAMEOBJECT_JELLY},
	{"algae", GAMEOBJECT_ALGAE},
	{"crab", GAMEOBJECT_CRAB},
	{"star", GAMEOBJECT_SATR},
	{"keke", GAMEOBJECT_KEKE},
	{"love", GAMEOBJECT_LOVE},
	{"pillar", GAMEOBJECT_PILLAR},
	{"bubble", GAMEOBJECT_BUBBLE},
	{"key", GAMEOBJECT_KEY},
	{"door", GAMEOBJECT_DOOR},
	{"hedge", GAMEOBJECT_HEDGE},
	{"rose", GAMEOBJECT_ROSE},
	{"violet", GAMEOBJECT_VIOLET},
	{"cog", GAMEOBJECT_COG},
	{"pipe", GAMEOBJECT_PIPE},
	{"robot", GAMEOBJECT_ROBOT},
	{"bolt", GAMEOBJECT_BOLT},
	{"reed", GAMEOBJECT_REED},
	{"bog", GAMEOBJECT_BOG},
	
	{"text_is", TEXTOBJECT_IS},
	{"text_and", TEXTOBJECT_AND},

	{"text_text", TEXTOBJECT_TEXT},
	{"text_baba", TEXTOBJECT_BABA},
	{"text_flag", TEXTOBJECT_FLAG},
	{"text_wall", TEXTOBJECT_WALL},
	{"text_rock", TEXTOBJECT_ROCK},
	{"text_tile", TEXTOBJECT_TILE},
	{"text_grass", TEXTOBJECT_GRASS},
	{"text_water", TEXTOBJECT_WATER},
	{"text_skull", TEXTOBJECT_SKULL},
	{"text_lava", TEXTOBJECT_LAVA},
	{"text_flower", TEXTOBJECT_FLOWER},
	{"text_brick", TEXTOBJECT_BRICK},
	{"text_ice", TEXTOBJECT_ICE},
	{"text_jelly", TEXTOBJECT_JELLY},
	{"text_algae", TEXTOBJECT_ALGAE},
	{"text_crab", TEXTOBJECT_CRAB},
	{"text_star", TEXTOBJECT_STAR},
	{"text_keke", TEXTOBJECT_KEKE},
	{"text_love", TEXTOBJECT_LOVE},
	{"text_pillar", TEXTOBJECT_PILLAR},
	{"text_bubble", TEXTOBJECT_BUBBLE},
	{"text_key", TEXTOBJECT_KEY},
	{"text_door", TEXTOBJECT_DOOR},
	{"text_hedge", TEXTOBJECT_HEDGE},
	{"text_rose", TEXTOBJECT_ROSE},
	{"text_violet", TEXTOBJECT_VIOLET},
	{"text_cog", TEXTOBJECT_COG},
	{"text_pipe", TEXTOBJECT_PIPE},
	{"text_robot", TEXTOBJECT_ROBOT},
	{"text_bolt", TEXTOBJECT_BOLT},
	{"text_reed", TEXTOBJECT_REED},
	{"text_bog", TEXTOBJECT_BOG},

	{"text_you", TEXTOBJECT_YOU},
	{"text_win", TEXTOBJECT_WIN},
	{"text_stop", TEXTOBJECT_STOP},
	{"text_push", TEXTOBJECT_PUSH},
	{"text_sink", TEXTOBJECT_SINK},
	{"text_defeat", TEXTOBJECT_DEFEAT},
	{"text_melt", TEXTOBJECT_MELT},
	{"text_hot", TEXTOBJECT_HOT},
	{"text_move", TEXTOBJECT_MOVE},
	{"text_shut", TEXTOBJECT_SHUT},
	{"text_open", TEXTOBJECT_OPEN},
	{"text_red", TEXTOBJECT_RED},
	{"text_blue", TEXTOBJECT_BLUE},
	{"text_float", TEXTOBJECT_FLOAT},
};


bool ObjectIdProc::IsGameobjectId(int id) {
	return GAMEOBJECT_ID_BEGIN <= id && id <= GAMEOBJECT_ID_END;
}

bool ObjectIdProc::IsGameobjectId(std::string name) {
	return IsGameobjectId(objectNameAndId[name]);
}

bool ObjectIdProc::IsTextobjectId(int id) {
	return TEXTOBJECT_ID_BEGIN <= id && id <= TEXTOBJECT_ID_END;
}

bool ObjectIdProc::IsTextobjectId(std::string name) {
	return IsTextobjectId(objectNameAndId[name]);
}

std::string ObjectIdProc::GetNameById(ObjectId id) {
	auto idIterator = std::find_if(objectNameAndId.begin(), objectNameAndId.end(),
		[&](auto &&pair) { return pair.second == id; }
	);

	if (idIterator == objectNameAndId.end()) {
		Log::LogError("<Object Id Proc> Can not find gameobject name with id %d", id);
	}
	return idIterator -> first;
}

ObjectId ObjectIdProc::GetIdByName(std::string name) {
	if (objectNameAndId.find(name) == objectNameAndId.end()) {
		Log::LogError("<Object Id Proc> Can not find gameobject id with name %s", name.c_str());
	}
	return objectNameAndId[name];
}