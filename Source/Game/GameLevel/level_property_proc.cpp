#include "stdafx.h"
#include "level_property_proc.h"
#include "level_data.h"
#include "level_undo_proc.h"
#include "level_gameboard_proc.h"
#include "level_description_proc.h"
#include "gameobject_properties_manager.h"

bool PropertyProc::CheckHasPropInBlock(Point position, PropId propId) {
	for (Gameobject *gameobject : LevelData::Gameboard[position]) {
		if (GameobjectPropsManager::GetGameobjectProp(gameobject->GetInfo().id, propId)) {
			return true;
		}
	}
	return false;
}
void PropertyProc::CheckAllOverlapProp() {
	checkOverlapPropFull_You_Win();

	LevelData::Gameboard.foreach([](Block &block) {
		Point position = block.GetPosition();

		checkOverlapPropBlock_Sink(position);
		deleteOverlapPropSecond(position, PROP_DEFEAT, PROP_YOU);
		deleteOverlapPropSecond(position, PROP_HOT, PROP_MELT);
		deleteOverlapPropBoth(position, PROP_SHUT, PROP_OPEN);
	});
}
void PropertyProc::LoadTextObjectsPushProp() {
	LevelData::Gameboard.foreach([](Block &block) {
		for (Gameobject *gameobject : block) {
			if (IsTextObject(gameobject->GetInfo().id)) {
				GameobjectPropsManager::SetGameobjectProp(gameobject->GetInfo().id, PROP_PUSH);
			}
		}
	});
}
void PropertyProc::UpdatePropsManager() {
	GameobjectPropsManager::ClearPropertiesWithoutTextPush();

	std::vector<std::pair<GameobjectId, GameobjectId>> descriptionProps = DescriptionProc::GetDescriptionProps();
	
	for (auto &prop : descriptionProps) {
		GameobjectId gameobjectId = static_cast<GameobjectId>(GetGameobjectByTextObject(prop.first));
		int propIdNum = GetPropIdFromTextGameobject(prop.second);
		if (propIdNum != -1) {
			PropId propId = static_cast<PropId>(propIdNum);
			GameobjectPropsManager::SetGameobjectProp(gameobjectId, propId);
		}
	}
}
void PropertyProc::UpdateAllReplaceProp() {
	std::vector<std::pair<GameobjectId, GameobjectId>> descriptionProps = DescriptionProc::GetDescriptionProps();
	
	GameboardProc::ResetGameobjectsReplaceRecord();
	for (auto &prop : descriptionProps) {
		if (!IsNounTextObject(prop.second)) continue;
		updateReplaceProp(prop);
	}
}

bool PropertyProc::checkPropOverlap(PropId propId1, PropId propId2) {
	bool result = false;

	LevelData::Gameboard.foreach([&](Block &block) {
		if (checkBlockPropOverlap(block.GetPosition(), propId1, propId2)) {
			result = true;
		}
	});
	return result;
}
bool PropertyProc::checkBlockPropOverlap(Point position, PropId propId1, PropId propId2) {
	bool hasProp1 = false;
	bool hasProp2 = false;
	for (Gameobject *gameobject : LevelData::Gameboard[position]) {
		hasProp1 |= GameobjectPropsManager::GetGameobjectProp(gameobject->GetInfo().id, propId1);
		hasProp2 |= GameobjectPropsManager::GetGameobjectProp(gameobject->GetInfo().id, propId2);
	}
	return hasProp1 && hasProp2;
}
void PropertyProc::checkOverlapPropFull_You_Win() {
	LevelData::SetTouchWin(checkPropOverlap(PROP_YOU, PROP_WIN));
}
void PropertyProc::checkOverlapPropBlock_Sink(Point position) {
	Gameobject *sinkGameobject = GameboardProc::FindGameobjectByPropInBlock(position, PROP_SINK);
	if (!sinkGameobject) return;

	for (Gameobject *gameobject : LevelData::Gameboard[position]) {
		if (!GameobjectPropsManager::GetGameobjectProp(gameobject->GetInfo().id, PROP_SINK)) {
			UndoProc::AddUndo(UndoProc::UNDO_DELETE, gameobject);
			GameboardProc::DeleteGameobject(gameobject);
			UndoProc::AddUndo(UndoProc::UNDO_DELETE, sinkGameobject);
			GameboardProc::DeleteGameobject(sinkGameobject);
			return;
		}
	}
}
void PropertyProc::deleteOverlapPropBoth(Point position, PropId propId1, PropId propId2) {
	Gameobject *gameobject1 = GameboardProc::FindGameobjectByPropInBlock(position, propId1);
	Gameobject *gameobject2 = GameboardProc::FindGameobjectByPropInBlock(position, propId2);
	if (gameobject1 && gameobject2) {
		UndoProc::AddUndo(UndoProc::UNDO_DELETE, gameobject1);
		GameboardProc::DeleteGameobject(gameobject1);
		UndoProc::AddUndo(UndoProc::UNDO_DELETE, gameobject2);
		GameboardProc::DeleteGameobject(gameobject2);
	}
}
void PropertyProc::deleteOverlapPropSecond(Point position, PropId propId1, PropId propId2) {
	Gameobject *gameobject1 = GameboardProc::FindGameobjectByPropInBlock(position, propId1);
	Gameobject *gameobject2 = GameboardProc::FindGameobjectByPropInBlock(position, propId2);
	if (gameobject1 && gameobject2) {
		UndoProc::AddUndo(UndoProc::UNDO_DELETE, gameobject2);
		GameboardProc::DeleteGameobject(gameobject2);
	}
}

void PropertyProc::updateReplaceProp(std::pair<GameobjectId, GameobjectId> &prop) {
	if (prop.first == prop.second) return;

	GameobjectId gameobjectId = static_cast<GameobjectId>(GetGameobjectByTextObject(prop.first));
	GameobjectId replaceGameobjectId = static_cast<GameobjectId>(GetGameobjectByTextObject(prop.second));
	LevelData::Gameboard.foreach([&](Block &block) {
		for (Gameobject *gameobject : block) {
			if (gameobject->GetInfo().id == gameobjectId && gameobject->Replace(replaceGameobjectId)) {
				UndoProc::AddUndo(UndoProc::UNDO_REPLACE, gameobject, gameobjectId);
			}
		}
	});
}