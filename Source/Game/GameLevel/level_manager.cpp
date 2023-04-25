#include "stdafx.h"
#include "level_manager.h"
#include "level_data.h"
#include "level_gameboard_proc.h"
#include "level_description_proc.h"
#include "level_property_proc.h"
#include "level_move_proc.h"
#include "level_undo_proc.h"
#include "texture_manager.h"
#include "gameobject_properties_manager.h"
#include "../../Expansion/dataio.h"
#include "../../Expansion/string_proc.h"
#include "../../Expansion/log.h"


LevelManager::LevelManager() {}
LevelManager::~LevelManager() {
	LevelData::Clear();
	UndoProc::Clear();
	DescriptionProc::Clear();
}

void LevelManager::LoadLevel(int level) {
	UndoProc::Clear();
	DescriptionProc::Clear();
	LevelData::LoadLevel(level);
	MoveProc::CreateBlockMoveableRecord();
	PropertyProc::LoadTextObjectsPushProp();
	DescriptionProc::CalculateAllDescription();
	PropertyProc::UpdatePropsManager();
	GameboardProc::UpdateGameobjectTextureColor();
}

void LevelManager::MoveWait() {
	if (LevelData::GetTouchWin()) return;
	UndoProc::ClearBuffer();

	MoveProc::MoveWait();
	updateProperties();
	addUndo();
}
void LevelManager::MoveUp() {
	if (LevelData::GetTouchWin()) return;
	UndoProc::ClearBuffer();

	MoveProc::MoveUp();
	MoveProc::MoveWait();
	updateProperties();
	addUndo();
}
void LevelManager::MoveDown() {
	if (LevelData::GetTouchWin()) return;
	UndoProc::ClearBuffer();

	MoveProc::MoveDown();
	MoveProc::MoveWait();
	updateProperties();
	addUndo();
}
void LevelManager::MoveLeft() {
	if (LevelData::GetTouchWin()) return;
	UndoProc::ClearBuffer();

	MoveProc::MoveLeft();
	MoveProc::MoveWait();
	updateProperties();
	addUndo();
}
void LevelManager::MoveRight() {
	if (LevelData::GetTouchWin()) return;
	UndoProc::ClearBuffer();

	MoveProc::MoveRight();
	MoveProc::MoveWait();
	updateProperties();
	addUndo();
}
void LevelManager::Undo() {
	UndoProc::Undo();
	DescriptionProc::Undo();
	PropertyProc::UpdatePropsManager();
	GameboardProc::UpdateGameobjectTextureColor();
}

bool LevelManager::IsMoving() {
	bool result = false;
	LevelData::Gameboard.foreach([&](Block &block) {
		for (Gameobject *gameobject : block) {
			if (gameobject->IsMoving()) {
				result = true;
			}
		}
	});
	return result;
}
bool LevelManager::IsWin() {
	return LevelData::GetTouchWin();
}

void LevelManager::Show() {
	LevelData::ShowBackground();

	std::unordered_set<Gameobject*> connectedTextObjects = DescriptionProc::GetConnectedTextObjects();
	
	showNotMovingGameobjects(connectedTextObjects);
	showMovingGameobjects(connectedTextObjects);

	if (nextTextureWaitTime-- == 0) {
		LevelData::Gameboard.foreach([](Block &block) {
			for (Gameobject *gameobject : block) gameobject->UpdateTextureCount();
		});
		nextTextureWaitTime = 6;
	}
}

void LevelManager::updateProperties() {
	DescriptionProc::CalculateAllDescription();
	PropertyProc::UpdatePropsManager();
	PropertyProc::UpdateAllReplaceProp();
	PropertyProc::CheckAllOverlapProp();
	GameboardProc::UpdateGameobjectTextureColor();
}

void LevelManager::addUndo() {
	if (!UndoProc::AddBufferToStack()) {
		DescriptionProc::Undo();
		PropertyProc::UpdatePropsManager();
		GameboardProc::UpdateGameobjectTextureColor();
	}
}

void LevelManager::showGameobjects(std::unordered_set<Gameobject*> &connectedTextObjects, CheckCanShowFunc checkCanShow) {
	LevelData::Gameboard.foreach([&, this] (Block &block) {
		for (Gameobject *gameobject : block) {
			if (!checkCanShow(gameobject)) continue;
			if (gameobject->GetInfo().type == OBJECT_TYPE_TILED) {
				gameobject->Show(GameboardProc::GetGameobjectConnectStatus(gameobject));
			}
			else if (gameobject->GetInfo().type == OBJECT_TYPE_TEXT) {
				gameobject->Show(connectedTextObjects.find(gameobject) != connectedTextObjects.end());
			}
			else {
				gameobject->Show(textureAnimationCount);
			}
		}
	});
}

void LevelManager::showNotMovingGameobjects(std::unordered_set<Gameobject*> &connectedTextObjects) {
	showGameobjects(connectedTextObjects, [](Gameobject* gameobject) { return !gameobject->IsMoving(); });
}
void LevelManager::showMovingGameobjects(std::unordered_set<Gameobject*> &connectedTextObjects) {
	showGameobjects(connectedTextObjects, [](Gameobject* gameobject) { return gameobject->IsMoving(); });
}