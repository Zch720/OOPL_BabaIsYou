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
	case GAMEOBJECT_TEXT_SHUT:
		return PROP_SHUT;
	case GAMEOBJECT_TEXT_OPEN:
		return PROP_OPEN;
	case GAMEOBJECT_TEXT_MOVE:
		return PROP_MOVE;
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
std::unordered_set<PropId> GameobjectPropsManager::GetAllGameobjectProps(GameobjectId gameobjectId) {
	std::unordered_set<PropId> result;
	for (auto &propPair : propsGroup[gameobjectId].props) {
		if (propPair.second) {
			result.insert(propPair.first);
		}
	}
	return result;
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

bool GameobjectPropsManager::CheckPropCanBeOffset(PropId propId1, PropId propId2) {
	if ((propId1 == PROP_SHUT && propId2 == PROP_OPEN) || (propId1 == PROP_OPEN && propId2 == PROP_SHUT)) {
		return true;
	}
	return false;
}
bool GameobjectPropsManager::CheckPropCanBeOffset(GameobjectId gameobjectId1, GameobjectId gameobjectId2) {
	std::unordered_set<PropId> gameobjectProps1 = GetAllGameobjectProps(gameobjectId1);
	std::unordered_set<PropId> gameobjectProps2 = GetAllGameobjectProps(gameobjectId2);

	for (PropId propId1 : gameobjectProps1) {
		for (PropId propId2 : gameobjectProps2) {
			if (CheckPropCanBeOffset(propId1, propId2)) {
				return true;
			}
		}
	}
	return false;
}
bool GameobjectPropsManager::CheckPropCanBeOffset(GameobjectId gameobjectId, std::vector<PropId> propIdArray) {
	std::unordered_set<PropId> gameobjectProps = GetAllGameobjectProps(gameobjectId);

	for (PropId propId1 : gameobjectProps) {
		for (PropId propId2 : propIdArray) {
			if (CheckPropCanBeOffset(propId1, propId2)) {
				return true;
			}
		}
	}
	return false;
}
bool GameobjectPropsManager::CheckPropCanBeOffset(GameobjectId gameobjectId, std::vector<GameobjectId> gameobjectIdArray) {
	std::unordered_set<PropId> gameobjectProps1 = GetAllGameobjectProps(gameobjectId);
	std::unordered_set<PropId> gameobjectProps2;

	for (GameobjectId gameobjectId : gameobjectIdArray) {
		std::unordered_set<PropId> props = GetAllGameobjectProps(gameobjectId);
		gameobjectProps2.insert(props.begin(), props.end());
	}

	for (PropId propId1 : gameobjectProps1) {
		for (PropId propId2 : gameobjectProps2) {
			if (CheckPropCanBeOffset(propId1, propId2)) {
				return true;
			}
		}
	}
	return false;
}
bool GameobjectPropsManager::CheckPropCanBeOffset(GameobjectId gameobjectId, std::unordered_set<PropId> propIdSet) {
	std::unordered_set<PropId> gameobjectProps = GetAllGameobjectProps(gameobjectId);

	for (PropId propId1 : gameobjectProps) {
		for (PropId propId2 : propIdSet) {
			if (CheckPropCanBeOffset(propId1, propId2)) {
				return true;
			}
		}
	}
	return false;
}
bool GameobjectPropsManager::CheckPropCanBeOffset(GameobjectId gameobjectId, std::unordered_set<GameobjectId> gameobjectIdSet) {
	std::unordered_set<PropId> gameobjectProps1 = GetAllGameobjectProps(gameobjectId);
	std::unordered_set<PropId> gameobjectProps2;

	for (GameobjectId gameobjectId : gameobjectIdSet) {
		std::unordered_set<PropId> props = GetAllGameobjectProps(gameobjectId);
		gameobjectProps2.insert(props.begin(), props.end());
	}

	for (PropId propId1 : gameobjectProps1) {
		for (PropId propId2 : gameobjectProps2) {
			if (CheckPropCanBeOffset(propId1, propId2)) {
				return true;
			}
		}
	}
	return false;
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