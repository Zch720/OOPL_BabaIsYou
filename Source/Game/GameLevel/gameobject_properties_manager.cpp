#include "stdafx.h"
#include "gameobject_properties_manager.h"
#include "../../Expansion/log.h"

std::unordered_map<GameobjectId, PropId> propTextToId = {
	{GAMEOBJECT_TEXT_YOU, PROP_YOU},
	{GAMEOBJECT_TEXT_PUSH, PROP_PUSH},
	{GAMEOBJECT_TEXT_STOP, PROP_STOP},
	{GAMEOBJECT_TEXT_WIN, PROP_WIN},
	{GAMEOBJECT_TEXT_SINK, PROP_SINK},
	{GAMEOBJECT_TEXT_DEFEAT, PROP_DEFEAT},
	{GAMEOBJECT_TEXT_HOT, PROP_HOT},
	{GAMEOBJECT_TEXT_MELT, PROP_MELT},
	{GAMEOBJECT_TEXT_SHUT, PROP_SHUT},
	{GAMEOBJECT_TEXT_OPEN, PROP_OPEN},
	{GAMEOBJECT_TEXT_MOVE, PROP_MOVE},
	{GAMEOBJECT_TEXT_RED, PROP_RED},
	{GAMEOBJECT_TEXT_BLUE, PROP_BLUE},
	{GAMEOBJECT_TEXT_FLOAT, PROP_FLOAT},
};

int GetPropIdFromTextGameobject(GameobjectId gameobjectId) {
	if (propTextToId.find(gameobjectId) == propTextToId.end()) return -1;
	return propTextToId[gameobjectId];
}

std::unordered_map<GameobjectId, GameobjectProps>
	GameobjectPropsManager::propsGroup =std::unordered_map<GameobjectId, GameobjectProps>();

bool GameobjectPropsManager::GetGameobjectProp(GameobjectId gameobjectId, PropId propId) {
	return propsGroup[gameobjectId][propId];
}

void GameobjectPropsManager::SetGameobjectProp(GameobjectId gameobjectId, PropId propId, bool value) {
	propsGroup[gameobjectId][propId] = value;
}
std::unordered_set<PropId> GameobjectPropsManager::GetAllGameobjectProps(GameobjectId gameobjectId) {
	std::unordered_set<PropId> result;
	for (auto &propPair : propsGroup[gameobjectId])
		if (propPair.second) result.insert(propPair.first);
	return result;
}

int GameobjectPropsManager::GetColorProp(GameobjectId gameobjectId) {
	return PROP_NONE;
}

void GameobjectPropsManager::SetPropWithOtherProp(PropId targetPropId, PropId newPropId, bool value) {
	for (auto &prop : propsGroup) {
		if (prop.second[targetPropId]) {
			prop.second[newPropId] = value;
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

	return CheckPropCanBeOffset(gameobjectProps1, gameobjectProps2);
}
bool GameobjectPropsManager::CheckPropCanBeOffset(GameobjectId gameobjectId, std::vector<PropId> propIdArray) {
	std::unordered_set<PropId> gameobjectProps = GetAllGameobjectProps(gameobjectId);
	
	return CheckPropCanBeOffset(gameobjectProps, std::unordered_set<PropId>(propIdArray.begin(), propIdArray.end()));
}
bool GameobjectPropsManager::CheckPropCanBeOffset(GameobjectId gameobjectId, std::vector<GameobjectId> gameobjectIdArray) {
	std::unordered_set<PropId> gameobjectProps1 = GetAllGameobjectProps(gameobjectId);
	std::unordered_set<PropId> gameobjectProps2;

	for (GameobjectId gameobjectId : gameobjectIdArray) {
		std::unordered_set<PropId> props = GetAllGameobjectProps(gameobjectId);
		gameobjectProps2.insert(props.begin(), props.end());
	}
	
	return CheckPropCanBeOffset(gameobjectProps1, gameobjectProps2);
}
bool GameobjectPropsManager::CheckPropCanBeOffset(GameobjectId gameobjectId, std::unordered_set<PropId> propIdSet) {
	std::unordered_set<PropId> gameobjectProps = GetAllGameobjectProps(gameobjectId);
	
	return CheckPropCanBeOffset(gameobjectProps, propIdSet);
}
bool GameobjectPropsManager::CheckPropCanBeOffset(GameobjectId gameobjectId, std::unordered_set<GameobjectId> gameobjectIdSet) {
	std::unordered_set<PropId> gameobjectProps1 = GetAllGameobjectProps(gameobjectId);
	std::unordered_set<PropId> gameobjectProps2;

	for (GameobjectId gameobjectId : gameobjectIdSet) {
		std::unordered_set<PropId> props = GetAllGameobjectProps(gameobjectId);
		gameobjectProps2.insert(props.begin(), props.end());
	}

	return CheckPropCanBeOffset(gameobjectProps1, gameobjectProps2);
}
bool GameobjectPropsManager::CheckPropCanBeOffset(std::unordered_set<PropId> propIds1, std::unordered_set<PropId> propIds2) {
	for (PropId propId1 : propIds1) {
		for (PropId propId2 : propIds2) {
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
		prop.second.clear();
		if (IsTextObject(prop.first)) {
			prop.second[PROP_PUSH] = true;
		}
	}
}