#include "stdafx.h"
#include "gameobject_properties_manager.h"

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
	default:
		return -1;
	}
}

GameobjectPropsManager::GameobjectPropsManager() {}

bool GameobjectPropsManager::GetGameobjectProp(GameobjectId gameobjectId, PropId propId) {
	return propsGroup[gameobjectId].props[propId];
}

void GameobjectPropsManager::SetGameobjectProp(GameobjectId gameobjectId, PropId propId, bool value) {
	propsGroup[gameobjectId].props[propId] = value;
}

std::string GameobjectPropsManager::GetColorDirName(GameobjectId gameobjectId) {
	int colorPropId = hasColorProp(gameobjectId);

	/*
	switch (colorPropId) {
	default:
		return "default";
	}
	*/
	return "default";
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

int GameobjectPropsManager::hasColorProp(GameobjectId gameobjectId) {
	return -1;
}