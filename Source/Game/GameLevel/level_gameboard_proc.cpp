#include "stdafx.h"
#include "gameobject_properties_manager.h"
#include "level_gameboard_proc.h"
#include "level_data.h"
//#include "level_undo_proc.h"

int GameboardProc::GetGameobjectConnectStatus(Gameobject *gameobject) {
	GameobjectId gameobjectId = gameobject->GetInfo().id;
	Point position = gameobject->GetInfo().position;
	int result = 0;

	if (position.x == LevelData::GetGameboardWidth() - 1 || HasGameobjectIdInBlock(position.Right(), gameobjectId)) {
		result |= 0b1;
	}
	if (position.y == 0 || HasGameobjectIdInBlock(position.Up(), gameobjectId)) {
		result |= 0b10;
	}
	if (position.x == 0 || HasGameobjectIdInBlock(position.Left(), gameobjectId)) {
		result |= 0b100;
	}
	if (position.y == LevelData::GetGameboardHeight() - 1 || HasGameobjectIdInBlock(position.Down(), gameobjectId)) {
		result |= 0b1000;
	}
	return result;
}

Gameobject* GameboardProc::GenGameobject(Point position, GameobjectId gameobjectId) {
	return LevelData::Gameboard[position].GenGameobject(gameobjectId);
}
void GameboardProc::DeleteGameobject(Gameobject* gameobject) {
	LevelData::Gameboard[gameobject->GetInfo().position].DeleteGameobject(gameobject);
}
void GameboardProc::AddGameobject(Gameobject* gameobject) {
	LevelData::Gameboard[gameobject->GetInfo().position].AddGameobject(gameobject);
}
void GameboardProc::RemoveGameobject(Gameobject* gameobject) {
	LevelData::Gameboard[gameobject->GetInfo().position].RemoveGameobject(gameobject);
}
void GameboardProc::ResetGameobjectsReplaceRecord() {
	for (auto &col : LevelData::Gameboard) {
		for (Block &block : col) {
			for (Gameobject *gameobject : block) {
				gameobject->SetReplace(false);
			}
		}
	}
}
void GameboardProc::UpdateGameobjectTextureColor() {
	for (auto &col : LevelData::Gameboard) {
		for (Block &block : col) {
			block.UpdateGameobjectColor();
		}
	}
}
bool GameboardProc::HasGameobjectIdInBlock(Point position, GameobjectId gameobjectId) {
	return LevelData::Gameboard[position].HasGameobjectId(gameobjectId);
}
Gameobject* GameboardProc::FindGameobjectByIdInBlock(Point position, GameobjectId gameobjectId) {
	return LevelData::Gameboard[position].FindGameobjectById(gameobjectId);
}
Gameobject* GameboardProc::FindGameobjectByPropInBlock(Point position, PropId propId) {
	return LevelData::Gameboard[position].FindGameobjectByProp(propId);
}
std::unordered_set<PropId> GameboardProc::GetAllPropsInBlock(Point position) {
	std::unordered_set<PropId> result, buffer;
	
	if (position.x < 0 || LevelData::GetGameboardWidth() <= position.x || position.y < 0 || LevelData::GetGameboardHeight() <= position.y) {
		return result;
	}

	for (Gameobject *gameobject : LevelData::Gameboard[position]) {
		buffer = GameobjectPropsManager::GetAllGameobjectProps(gameobject->GetInfo().id);
		result.insert(buffer.begin(), buffer.end());
	}
	return result;
}