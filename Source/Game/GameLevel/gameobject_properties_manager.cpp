#include "stdafx.h"
#include "gameobject_properties_manager.h"
#include "../../Expansion/log.h"

int GetPropIdFromTextGameobject(GameobjectId gameobjectId) {
	switch (gameobjectId) {
	case GAMEOBJECT_TEXT_YOU:
		return PROP_YOU;
	case GAMEOBJECT_TEXT_PUSH:
		return PROP_PUSH;
	case GAMEOBJECT_TEXT_STOP:
		return PROP_STOP;
	case GAMEOBJECT_TEXT_WIN:
		return PROP_WIN;
	case GAMEOBJECT_TEXT_SINK:
		return PROP_SINK;
	case GAMEOBJECT_TEXT_DEFEAT:
		return PROP_DEFEAT;
	case GAMEOBJECT_TEXT_HOT:
		return PROP_HOT;
	case GAMEOBJECT_TEXT_MELT:
		return PROP_MELT;
	default:
		return -1;
	}
}

std::unordered_map<GameobjectId, GameobjectProps>
	GameobjectPropsManager::propsGroup =std::unordered_map<GameobjectId, GameobjectProps>();

bool GameobjectPropsManager::GetGameobjectProp(GameobjectId gameobjectId, PropId propId) {
	return propsGroup[gameobjectId].props[propId];
}

void GameobjectPropsManager::SetGameobjectProp(GameobjectId gameobjectId, PropId propId, bool value) {
	propsGroup[gameobjectId].props[propId] = value;
}

int GameobjectPropsManager::GetColorProp(GameobjectId gameobjectId) {
	return PROP_NONE;
}

void GameobjectPropsManager::SetPropWithOtherProp(PropId targetPropId, PropId newPropId, bool value) {
	for (auto &prop : propsGroup) {
		if (prop.second.props[targetPropId]) {
			prop.second.props[newPropId] = value;
		}
	}
}

void GameobjectPropsManager::ClearProperties() {
	propsGroup.clear();
}

void GameobjectPropsManager::ClearPropertiesWithoutTextPush() {
	for (auto &prop : propsGroup) {
		prop.second.props.clear();
		if (IsTextObject(prop.first)) {
			prop.second.props[PROP_PUSH] = true;
		}
	}
}