#include "stdafx.h"
#include "level_property_proc.h"
#include "level_data.h"
#include "level_undo_proc.h"
#include "level_gameboard_proc.h"
#include "level_description_proc.h"
#include "gameobject_properties_manager.h"

bool PropertyProc::CheckHasPropInBlock(Point position, PropId propId) {
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
			Point position(i, j);

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
			for (auto &col : LevelData::gameboard) {
				for (Block &block : col) {
					for (size_t i = 0; i < block.GetSize(); i++) {
						if (block[i]->gameobjectId == gameobjectId) {
							Gameobject *replaceGameobject = block.GenGameobject(convertGameobject);
							UndoProc::AddUndo(UndoProc::UNDO_GEN, replaceGameobject);
							UndoProc::AddUndo(UndoProc::UNDO_DELETE, block[i]);
							block.DeleteGameobject(block[i]);
							i--;
						}
					}
				}
			}
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
			if (checkBlockPropOverlap(Point(i, j), propId1, propId2)) {
				return true;
			}
		}
	}
	return false;
}
bool PropertyProc::checkBlockPropOverlap(Point position, PropId propId1, PropId propId2) {
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
void PropertyProc::checkOverlapPropBlock_Sink(Point position) {
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
void PropertyProc::deleteOverlapPropBoth(Point position, PropId propId1, PropId propId2) {
	Gameobject *gameobject1 = GameboardProc::FindGameobjectByPropInBlock(position, propId1);
	Gameobject *gameobject2 = GameboardProc::FindGameobjectByPropInBlock(position, propId2);
	if (gameobject1 && gameobject2) {
		GameboardProc::DeleteGameobject(gameobject2);
	}
}
void PropertyProc::deleteOverlapPropSecond(Point position, PropId propId1, PropId propId2) {
	Gameobject *gameobject1 = GameboardProc::FindGameobjectByPropInBlock(position, propId1);
	Gameobject *gameobject2 = GameboardProc::FindGameobjectByPropInBlock(position, propId2);
	if (gameobject1 && gameobject2) {
		GameboardProc::DeleteGameobject(gameobject1);
		GameboardProc::DeleteGameobject(gameobject2);
	}
}