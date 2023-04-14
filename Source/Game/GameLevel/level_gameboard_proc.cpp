#include "stdafx.h"
#include "gameobject_properties_manager.h"
#include "level_gameboard_proc.h"
#include "level_data.h"
//#include "level_undo_proc.h"

int GameboardProc::GetGameobjectConnectStatus(Gameobject *gameobject) {
	GameobjectId gameobjectId = gameobject->GetInfo().id;
	Point position = gameobject->GetInfo().position;
	int result = 0;

	if (position.x == LevelData::gameboardWidth - 1 || HasGameobjectIdInBlock(position.Right(), gameobjectId)) {
		result |= 0b1;
	}
	if (position.y == 0 || HasGameobjectIdInBlock(position.Up(), gameobjectId)) {
		result |= 0b10;
	}
	if (position.x == 0 || HasGameobjectIdInBlock(position.Left(), gameobjectId)) {
		result |= 0b100;
	}
	if (position.y == LevelData::gameboardHeight - 1 || HasGameobjectIdInBlock(position.Down(), gameobjectId)) {
		result |= 0b1000;
	}
	return result;
}

Gameobject* GameboardProc::GenGameobject(Point position, GameobjectId gameobjectId) {
	return LevelData::gameboard[position].GenGameobject(gameobjectId);
}
void GameboardProc::DeleteGameobject(Gameobject* gameobject) {
	LevelData::gameboard[gameobject->GetInfo().position].DeleteGameobject(gameobject);
}
void GameboardProc::AddGameobject(Gameobject* gameobject) {
	LevelData::gameboard[gameobject->GetInfo().position].AddGameobject(gameobject);
}
void GameboardProc::RemoveGameobject(Gameobject* gameobject) {
	LevelData::gameboard[gameobject->GetInfo().position].RemoveGameobject(gameobject);
}
void GameboardProc::ResetGameobjectsReplaceRecord() {
	for (auto &col : LevelData::gameboard) {
		for (Block &block : col) {
			for (Gameobject *gameobject : block) {
				gameobject->SetReplace(false);
			}
		}
	}
}
void GameboardProc::UpdateGameobjectTextureColor() {
	for (auto &col : LevelData::gameboard) {
		for (Block &block : col) {
			block.UpdateGameobjectColor();
		}
	}
}
bool GameboardProc::HasGameobjectIdInBlock(Point position, GameobjectId gameobjectId) {
	return LevelData::gameboard[position].HasGameobjectId(gameobjectId);
}
Gameobject* GameboardProc::FindGameobjectByIdInBlock(Point position, GameobjectId gameobjectId) {
	return LevelData::gameboard[position].FindGameobjectById(gameobjectId);
}
Gameobject* GameboardProc::FindGameobjectByPropInBlock(Point position, PropId propId) {
	return LevelData::gameboard[position].FindGameobjectByProp(propId);
}
std::unordered_set<PropId> GameboardProc::GetAllPropsInBlock(Point position) {
	std::unordered_set<PropId> result, buffer;
	
	if (position.x < 0 || LevelData::gameboardWidth <= position.x || position.y < 0 || LevelData::gameboardHeight <= position.y) {
		return result;
	}

	for (Gameobject *gameobject : LevelData::gameboard[position]) {
		buffer = GameobjectPropsManager::GetAllGameobjectProps(gameobject->GetInfo().id);
		result.insert(buffer.begin(), buffer.end());
	}
	return result;
}