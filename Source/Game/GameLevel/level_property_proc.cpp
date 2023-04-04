#include "stdafx.h"
#include "level_property_proc.h"
#include "level_data.h"
#include "level_gameboard_proc.h"
#include "level_description_proc.h"
#include "gameobject_properties_manager.h"

bool PropertyProc::CheckHasPropInBlock(CPoint position, PropId propId) {
	for (Gameobject *gameobject : LevelData::gameboard[position]) {
		if (GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, propId)) {
			return true;
		}
	}
	return false;
}
void PropertyProc::CheckAllOverlapProp() {
	checkOverlapPropFull_You_Win();

	for (int i = 0; i < LevelData::gameboardWidth; i++) {
		for (int j = 0; j < LevelData::gameboardHeight; j++) {
			CPoint position(i, j);

			checkOverlapPropBlock_Sink(position);
			deleteOverlapPropSecond(position, PROP_DEFEAT, PROP_YOU);
			deleteOverlapPropBoth(position, PROP_HOT, PROP_MELT);
		}
	}
}
void PropertyProc::LoadTextObjectsPushProp() {
	for (auto &col : LevelData::gameboard) {
		for (auto &block : col) {
			for (Gameobject *gameobject : block) {
				if (IsTextObject(gameobject->gameobjectId)) {
					GameobjectPropsManager::SetGameobjectProp(gameobject->gameobjectId, PROP_PUSH);
				}
			}
		}
	}
}
void PropertyProc::UpdatePropsManager() {
	GameobjectPropsManager::ClearPropertiesWithoutTextPush();

	std::vector<std::pair<GameobjectId, GameobjectId>> descriptionProps = DescriptionProc::GetDescriptionProps();

	for (auto &prop : descriptionProps) {
		GameobjectId gameobjectId = static_cast<GameobjectId>(GetGameobjectByTextObject(prop.first));
		int propIdNum = GetPropIdFromTextGameobject(prop.second);
		if (propIdNum == -1) {
			GameobjectId convertGameobject = static_cast<GameobjectId>(GetGameobjectByTextObject(prop.second));
			GameboardProc::ReplaceGameobject(gameobjectId, convertGameobject);
		}
		else {
			PropId propId = static_cast<PropId>(propIdNum);
			GameobjectPropsManager::SetGameobjectProp(gameobjectId, propId);
		}
	}
}

bool PropertyProc::checkPropOverlap(PropId propId1, PropId propId2) {
	for (int i = 0; i < LevelData::gameboardWidth; i++) {
		for (int j = 0; j < LevelData::gameboardHeight; j++) {
			if (checkBlockPropOverlap(CPoint(i, j), propId1, propId2)) {
				return true;
			}
		}
	}
	return false;
}
bool PropertyProc::checkBlockPropOverlap(CPoint position, PropId propId1, PropId propId2) {
	bool hasProp1 = false;
	bool hasProp2 = false;
	for (Gameobject *gameobject : LevelData::gameboard[position]) {
		hasProp1 |= GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, propId1);
		hasProp2 |= GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, propId2);
	}
	return hasProp1 && hasProp2;
}
void PropertyProc::checkOverlapPropFull_You_Win() {
	LevelData::touchWinObject = checkPropOverlap(PROP_YOU, PROP_WIN);
}
void PropertyProc::checkOverlapPropBlock_Sink(CPoint position) {
	Gameobject *sinkGameobject = GameboardProc::FindGameobjectByPropInBlock(position, PROP_SINK);
	if (!sinkGameobject) return;

	for (Gameobject *gameobject : LevelData::gameboard[position]) {
		if (!GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, PROP_SINK)) {
			GameboardProc::DeleteGameobject(gameobject);
			GameboardProc::DeleteGameobject(sinkGameobject);
			return;
		}
	}
}
void PropertyProc::deleteOverlapPropBoth(CPoint position, PropId propId1, PropId propId2) {
	Gameobject *gameobject1 = GameboardProc::FindGameobjectByPropInBlock(position, propId1);
	Gameobject *gameobject2 = GameboardProc::FindGameobjectByPropInBlock(position, propId2);
	if (gameobject1 && gameobject2) {
		GameboardProc::DeleteGameobject(gameobject2);
	}
}
void PropertyProc::deleteOverlapPropSecond(CPoint position, PropId propId1, PropId propId2) {
	Gameobject *gameobject1 = GameboardProc::FindGameobjectByPropInBlock(position, propId1);
	Gameobject *gameobject2 = GameboardProc::FindGameobjectByPropInBlock(position, propId2);
	if (gameobject1 && gameobject2) {
		GameboardProc::DeleteGameobject(gameobject1);
		GameboardProc::DeleteGameobject(gameobject2);
	}
}