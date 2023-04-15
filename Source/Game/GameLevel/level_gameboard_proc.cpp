#include "stdafx.h"
#include "gameobject_properties_manager.h"
#include "level_gameboard_proc.h"
#include "level_data.h"

#define RIGHT_CONNECTED		0b1
#define UP_CONNECTED		0b10
#define LEFT_CONNECTED		0b100
#define DOWN_CONNECTED		0b1000

int GameboardProc::GetGameobjectConnectStatus(Gameobject *gameobject) {
	GameobjectId gameobjectId = gameobject->GetInfo().id;
	Point position = gameobject->GetInfo().position;
	int result = 0;

	if (position.x == LevelData::GetGameboardWidth() - 1 || HasGameobjectIdInBlock(position.Right(), gameobjectId)) {
		result |= RIGHT_CONNECTED;
	}
	if (position.y == 0 || HasGameobjectIdInBlock(position.Up(), gameobjectId)) {
		result |= UP_CONNECTED;
	}
	if (position.x == 0 || HasGameobjectIdInBlock(position.Left(), gameobjectId)) {
		result |= LEFT_CONNECTED;
	}
	if (position.y == LevelData::GetGameboardHeight() - 1 || HasGameobjectIdInBlock(position.Down(), gameobjectId)) {
		result |= DOWN_CONNECTED;
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
	LevelData::Gameboard.foreach([](Block &block) {
		for (Gameobject *gameobject : block) {
			gameobject->SetReplace(false);
		}
	});
}
void GameboardProc::UpdateGameobjectTextureColor() {
	LevelData::Gameboard.foreach([](Block &block) {
		block.UpdateGameobjectColor();
	});
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
	
	if (!LevelData::IsPointInGameboard(position)) {
		return result;
	}

	for (Gameobject *gameobject : LevelData::Gameboard[position]) {
		buffer = GameobjectPropsManager::GetAllGameobjectProps(gameobject->GetInfo().id);
		result.insert(buffer.begin(), buffer.end());
	}
	return result;
}