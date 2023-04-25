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
	
	DescriptionProc::CalculateAllDescription();
	PropertyProc::UpdatePropsManager();
	PropertyProc::UpdateAllReplaceProp();
	PropertyProc::CheckAllOverlapProp();
	GameboardProc::UpdateGameobjectTextureColor();

	if (!UndoProc::AddBufferToStack()) {
		DescriptionProc::Undo();
		PropertyProc::UpdatePropsManager();
		GameboardProc::UpdateGameobjectTextureColor();
	}
}
void LevelManager::MoveUp() {
	if (LevelData::GetTouchWin()) return;
	UndoProc::ClearBuffer();

	MoveProc::MoveUp();
	MoveProc::MoveWait();
	
	DescriptionProc::CalculateAllDescription();
	PropertyProc::UpdatePropsManager();
	PropertyProc::UpdateAllReplaceProp();
	PropertyProc::CheckAllOverlapProp();
	GameboardProc::UpdateGameobjectTextureColor();

	if (!UndoProc::AddBufferToStack()) {
		DescriptionProc::Undo();
		PropertyProc::UpdatePropsManager();
		GameboardProc::UpdateGameobjectTextureColor();
	}
}
void LevelManager::MoveDown() {
	if (LevelData::GetTouchWin()) return;
	UndoProc::ClearBuffer();

	MoveProc::MoveDown();
	MoveProc::MoveWait();
	
	DescriptionProc::CalculateAllDescription();
	PropertyProc::UpdatePropsManager();
	PropertyProc::UpdateAllReplaceProp();
	PropertyProc::CheckAllOverlapProp();
	GameboardProc::UpdateGameobjectTextureColor();

	if (!UndoProc::AddBufferToStack()) {
		DescriptionProc::Undo();
		PropertyProc::UpdatePropsManager();
		GameboardProc::UpdateGameobjectTextureColor();
	}
}
void LevelManager::MoveLeft() {
	if (LevelData::GetTouchWin()) return;
	UndoProc::ClearBuffer();

	MoveProc::MoveLeft();
	MoveProc::MoveWait();
	
	DescriptionProc::CalculateAllDescription();
	PropertyProc::UpdatePropsManager();
	PropertyProc::UpdateAllReplaceProp();
	PropertyProc::CheckAllOverlapProp();
	GameboardProc::UpdateGameobjectTextureColor();

	if (!UndoProc::AddBufferToStack()) {
		DescriptionProc::Undo();
		PropertyProc::UpdatePropsManager();
		GameboardProc::UpdateGameobjectTextureColor();
	}
}
void LevelManager::MoveRight() {
	if (LevelData::GetTouchWin()) return;
	UndoProc::ClearBuffer();

	MoveProc::MoveRight();
	MoveProc::MoveWait();
	
	DescriptionProc::CalculateAllDescription();
	PropertyProc::UpdatePropsManager();
	PropertyProc::UpdateAllReplaceProp();
	PropertyProc::CheckAllOverlapProp();
	GameboardProc::UpdateGameobjectTextureColor();

	if (!UndoProc::AddBufferToStack()) {
		DescriptionProc::Undo();
		PropertyProc::UpdatePropsManager();
		GameboardProc::UpdateGameobjectTextureColor();
	}
}
void LevelManager::Undo() {
	UndoProc::Undo();
	DescriptionProc::Undo();
	PropertyProc::UpdatePropsManager();
	GameboardProc::UpdateGameobjectTextureColor();
}

bool LevelManager::IsMoving() {
	for (auto &col : LevelData::Gameboard) {
		for (auto &block : col) {
			for (Gameobject *gameobject : block) {
				if (gameobject->IsMoving()) {
					return true;
				}
			}
		}
	}
	return false;
}
bool LevelManager::IsWin() {
	return LevelData::GetTouchWin();
}

void LevelManager::Show() {
	LevelData::ShowBackground();

	std::unordered_set<Gameobject*> connectedTextObjects = DescriptionProc::GetConnectedTextObjects();
	std::unordered_set<Gameobject*> unusableTextObjects = DescriptionProc::GetUnusableTextObjects();

	// show gameobject didn't move
	for (auto &col : LevelData::Gameboard) {
		for (Block &block : col) {
			for (Gameobject *gameobject : block) {
				if (gameobject->IsMoving()) continue;
				if (gameobject->GetInfo().type == OBJECT_TYPE_TILED) {
					gameobject->Show(GameboardProc::GetGameobjectConnectStatus(gameobject));
				}
				else if (gameobject->GetInfo().type == OBJECT_TYPE_TEXT) {
					int otherInfo = 0;
					if (connectedTextObjects.find(gameobject) != connectedTextObjects.end()) {
						otherInfo |= 0b1;
					}
					if (unusableTextObjects.find(gameobject) != unusableTextObjects.end()) {
						otherInfo |= 0b10;
					}
					gameobject->Show(otherInfo);
				}
				else {
					gameobject->Show(textureAnimationCount);
				}
			}
		}
	}

	// show gameobject is moving
	for (auto &col : LevelData::Gameboard) {
		for (Block &block : col) {
			for (Gameobject *gameobject : block) {
				if (!gameobject->IsMoving()) continue;
				if (gameobject->GetInfo().type == OBJECT_TYPE_TILED) {
					gameobject->Show(GameboardProc::GetGameobjectConnectStatus(gameobject));
				}
				else if (gameobject->GetInfo().type == OBJECT_TYPE_TEXT) {
					if (connectedTextObjects.find(gameobject) != connectedTextObjects.end()) {
						gameobject->Show(1);
					}
					else {
						gameobject->Show(0);
					}
				}
				else {
					gameobject->Show(textureAnimationCount);
				}
			}
		}
	}

	if (nextTextureWaitTime-- == 0) {
		LevelData::Gameboard.foreach([](Block &block) {
			for (Gameobject *gameobject : block) gameobject->UpdateTextureCount();
		});
		nextTextureWaitTime = 6;
	}
}