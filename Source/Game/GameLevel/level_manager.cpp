﻿#include "stdafx.h"
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
	LevelData::LoadLevel(level);
	MoveProc::CreateBlockMoveableRecord();
	PropertyProc::LoadTextObjectsPushProp();
	DescriptionProc::GetAllDescription();
	PropertyProc::UpdatePropsManager();
	GameboardProc::UpdateGameobjectTextureColor();
}

void LevelManager::MoveWait() {
	if (LevelData::touchWinObject) return;
	UndoProc::ClearBuffer();

	MoveProc::MoveWait();
	
	DescriptionProc::GetAllDescription();
	PropertyProc::UpdatePropsManager();
	PropertyProc::UpdateReplaceProp();
	PropertyProc::CheckAllOverlapProp();
	GameboardProc::UpdateGameobjectTextureColor();

	if (!UndoProc::AddBufferToStack()) {
		DescriptionProc::Undo();
		PropertyProc::UpdatePropsManager();
		GameboardProc::UpdateGameobjectTextureColor();
	}
}
void LevelManager::MoveUp() {
	if (LevelData::touchWinObject) return;
	UndoProc::ClearBuffer();

	MoveProc::MoveUp();
	MoveProc::MoveWait();
	
	DescriptionProc::GetAllDescription();
	PropertyProc::UpdatePropsManager();
	PropertyProc::UpdateReplaceProp();
	PropertyProc::CheckAllOverlapProp();
	GameboardProc::UpdateGameobjectTextureColor();

	if (!UndoProc::AddBufferToStack()) {
		DescriptionProc::Undo();
		PropertyProc::UpdatePropsManager();
		GameboardProc::UpdateGameobjectTextureColor();
	}
}
void LevelManager::MoveDown() {
	if (LevelData::touchWinObject) return;
	UndoProc::ClearBuffer();

	MoveProc::MoveDown();
	MoveProc::MoveWait();
	
	DescriptionProc::GetAllDescription();
	PropertyProc::UpdatePropsManager();
	PropertyProc::UpdateReplaceProp();
	PropertyProc::CheckAllOverlapProp();
	GameboardProc::UpdateGameobjectTextureColor();

	if (!UndoProc::AddBufferToStack()) {
		DescriptionProc::Undo();
		PropertyProc::UpdatePropsManager();
		GameboardProc::UpdateGameobjectTextureColor();
	}
}
void LevelManager::MoveLeft() {
	if (LevelData::touchWinObject) return;
	UndoProc::ClearBuffer();

	MoveProc::MoveLeft();
	MoveProc::MoveWait();
	
	DescriptionProc::GetAllDescription();
	PropertyProc::UpdatePropsManager();
	PropertyProc::UpdateReplaceProp();
	PropertyProc::CheckAllOverlapProp();
	GameboardProc::UpdateGameobjectTextureColor();

	if (!UndoProc::AddBufferToStack()) {
		DescriptionProc::Undo();
		PropertyProc::UpdatePropsManager();
		GameboardProc::UpdateGameobjectTextureColor();
	}
}
void LevelManager::MoveRight() {
	if (LevelData::touchWinObject) return;
	UndoProc::ClearBuffer();

	MoveProc::MoveRight();
	MoveProc::MoveWait();
	
	DescriptionProc::GetAllDescription();
	PropertyProc::UpdatePropsManager();
	PropertyProc::UpdateReplaceProp();
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
	for (auto &col : LevelData::gameboard) {
		for (auto &block : col) {
			for (Gameobject *gameobject : block) {
				if (gameobject->moveRemainStep != 0) {
					return true;
				}
			}
		}
	}
	return false;
}
bool LevelManager::IsWin() {
	return LevelData::touchWinObject;
}

void LevelManager::Show() {
	LevelData::background.ShowBitmap();

	std::unordered_set<Gameobject*> connectedTextObjects = DescriptionProc::GetConnectedTextObjects();
	std::unordered_set<Gameobject*> unusableTextObjects = DescriptionProc::GetUnusableTextObjects();

	// show gameobject didn't move
	for (auto &col : LevelData::gameboard) {
		for (Block &block : col) {
			for (Gameobject *gameobject : block) {
				if (gameobject->moveRemainStep != 0) continue;
				if (gameobject->gameobjectType == OBJECT_TYPE_TILED) {
					gameobject->show(textureAnimationCount, GameboardProc::GetGameobjectConnectStatus(gameobject));
				}
				else if (gameobject->gameobjectType == OBJECT_TYPE_TEXT) {
					int otherInfo = 0;
					if (connectedTextObjects.find(gameobject) != connectedTextObjects.end()) {
						otherInfo |= 0b1;
					}
					if (unusableTextObjects.find(gameobject) != unusableTextObjects.end()) {
						otherInfo |= 0b10;
					}
					gameobject->show(textureAnimationCount, otherInfo);
				}
				else {
					gameobject->show(textureAnimationCount);
				}
			}
		}
	}

	// show gameobject is moving
	for (auto &col : LevelData::gameboard) {
		for (Block &block : col) {
			for (Gameobject *gameobject : block) {
				if (gameobject->moveRemainStep == 0) continue;
				if (gameobject->gameobjectType == OBJECT_TYPE_TILED) {
					gameobject->show(textureAnimationCount, GameboardProc::GetGameobjectConnectStatus(gameobject));
				}
				else if (gameobject->gameobjectType == OBJECT_TYPE_TEXT) {
					if (connectedTextObjects.find(gameobject) != connectedTextObjects.end()) {
						gameobject->show(textureAnimationCount, 1);
					}
					else {
						gameobject->show(textureAnimationCount, 0);
					}
				}
				else {
					gameobject->show(textureAnimationCount);
				}
			}
		}
	}

	if (nextTextureWaitTime-- == 0) {
		textureAnimationCount = (textureAnimationCount + 1) % 3;
		nextTextureWaitTime = 6;
	}
}