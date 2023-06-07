#include "stdafx.h"
#include <algorithm>
#include "textobject_id.h"
#include "../../Expansion/log.h"

std::unordered_map<ObjectId, ObjectId> TextobjectIdProc::textobjectToGameobject = { 
	{ TEXTOBJECT_TEXT, GAMEOBJECT_TEXTS },
	{ TEXTOBJECT_BABA, GAMEOBJECT_BABA },
	{ TEXTOBJECT_FLAG, GAMEOBJECT_FLAG },
	{ TEXTOBJECT_WALL, GAMEOBJECT_WALL },
	{ TEXTOBJECT_ROCK, GAMEOBJECT_ROCK },
	{ TEXTOBJECT_TILE, GAMEOBJECT_TILE },
	{ TEXTOBJECT_GRASS, GAMEOBJECT_GRASS },
	{ TEXTOBJECT_WATER, GAMEOBJECT_WATER },
	{ TEXTOBJECT_SKULL, GAMEOBJECT_SKULL },
	{ TEXTOBJECT_LAVA, GAMEOBJECT_LAVA },
	{ TEXTOBJECT_FLOWER, GAMEOBJECT_FLOWER },
	{ TEXTOBJECT_BRICK, GAMEOBJECT_BRICK },
	{ TEXTOBJECT_ICE, GAMEOBJECT_ICE },
	{ TEXTOBJECT_JELLY, GAMEOBJECT_JELLY },
	{ TEXTOBJECT_ALGAE, GAMEOBJECT_ALGAE },
	{ TEXTOBJECT_CRAB, GAMEOBJECT_CRAB },
	{ TEXTOBJECT_STAR, GAMEOBJECT_SATR },
	{ TEXTOBJECT_KEKE, GAMEOBJECT_KEKE },
	{ TEXTOBJECT_LOVE, GAMEOBJECT_LOVE },
	{ TEXTOBJECT_PILLAR, GAMEOBJECT_PILLAR },
	{ TEXTOBJECT_BUBBLE, GAMEOBJECT_BUBBLE },
	{ TEXTOBJECT_KEY, GAMEOBJECT_KEY },
	{ TEXTOBJECT_DOOR, GAMEOBJECT_DOOR },
	{ TEXTOBJECT_HEDGE, GAMEOBJECT_HEDGE },
	{ TEXTOBJECT_ROSE, GAMEOBJECT_ROSE },
	{ TEXTOBJECT_VIOLET, GAMEOBJECT_VIOLET },
	{ TEXTOBJECT_COG, GAMEOBJECT_COG },
	{ TEXTOBJECT_PIPE, GAMEOBJECT_PIPE },
	{ TEXTOBJECT_ROBOT, GAMEOBJECT_ROBOT },
	{ TEXTOBJECT_BOLT, GAMEOBJECT_BOLT },
	{ TEXTOBJECT_REED, GAMEOBJECT_REED },
	{ TEXTOBJECT_BOG, GAMEOBJECT_BOG },
	{ TEXTOBJECT_BOX, GAMEOBJECT_BOX },
	{ TEXTOBJECT_HUSK, GAMEOBJECT_HUSK },
	{ TEXTOBJECT_STUMP, GAMEOBJECT_STUMP },
	{ TEXTOBJECT_TREE, GAMEOBJECT_TREE },
	{ TEXTOBJECT_GHOST, GAMEOBJECT_GHOST },
	{ TEXTOBJECT_STATUE, GAMEOBJECT_STATUE },
};
std::unordered_map<ObjectId, PropertyId> TextobjectIdProc::textobjectToProperty = {
	{ TEXTOBJECT_YOU, PROPERTY_YOU },
	{ TEXTOBJECT_WIN, PROPERTY_WIN },
	{ TEXTOBJECT_STOP, PROPERTY_STOP },
	{ TEXTOBJECT_PUSH, PROPERTY_PUSH },
	{ TEXTOBJECT_SINK, PROPERTY_SINK },
	{ TEXTOBJECT_DEFEAT, PROPERTY_DEFEAT },
	{ TEXTOBJECT_MELT, PROPERTY_MELT },
	{ TEXTOBJECT_HOT, PROPERTY_HOT },
	{ TEXTOBJECT_MOVE, PROPERTY_MOVE },
	{ TEXTOBJECT_SHUT, PROPERTY_SHUT },
	{ TEXTOBJECT_OPEN, PROPERTY_OPEN },
	{ TEXTOBJECT_RED, PROPERTY_RED },
	{ TEXTOBJECT_BLUE, PROPERTY_BLUE },
	{ TEXTOBJECT_FLOAT, PROPERTY_FLOAT },
	{ TEXTOBJECT_WEAK, PROPERTY_WEAK },
};


bool TextobjectIdProc::IsOperatorTextobject(ObjectId textobjectId) {
	if (!ObjectIdProc::IsTextobjectId(textobjectId)) {
		Log::LogError("<Textobject Id Proc> object id %d is not textobject", textobjectId);
	}
	return OPERATOR_TEXTOBJECT_BEGIN <= textobjectId && textobjectId < GAMEOBJECT_TEXTOBJECT_BEGIN;
}

bool TextobjectIdProc::IsGameobjectTextobject(ObjectId textobjectId) {	
	if (!ObjectIdProc::IsTextobjectId(textobjectId)) {
		Log::LogError("<Textobject Id Proc> object id %d is not textobject", textobjectId);
	}
	return GAMEOBJECT_TEXTOBJECT_BEGIN <= textobjectId && textobjectId < PROPERTY_TEXTOBJECT_BEGIN;
}

bool TextobjectIdProc::IsPropertyTextobject(ObjectId textobjectId) {
	if (!ObjectIdProc::IsTextobjectId(textobjectId)) {
		Log::LogError("<Textobject Id Proc> object id %d is not textobject", textobjectId);
	}
	return PROPERTY_TEXTOBJECT_BEGIN <= textobjectId && textobjectId <= TEXTOBJECT_ID_END;
}

ObjectId TextobjectIdProc::GetGameobjectId(ObjectId id) {
	if (textobjectToGameobject.find(id) == textobjectToGameobject.end()) {
		Log::LogError("<Textobject Id Proc> Can not find gameobject id with textobject id %d", id);
	}
	return textobjectToGameobject[id];
}

PropertyId TextobjectIdProc::GetPropertyId(ObjectId id) {
	if (textobjectToProperty.find(id) == textobjectToProperty.end()) {
		Log::LogError("<Textobject Id Proc> Can not find property id with textobject id %d", id);
	}
	return textobjectToProperty[id];
}