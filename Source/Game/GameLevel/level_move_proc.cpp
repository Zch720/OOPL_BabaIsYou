#include "stdafx.h"
#include "level_move_proc.h"
#include "level_data.h"
#include "level_gameboard_proc.h"
#include "level_property_proc.h"
#include "level_undo_proc.h"
#include "gameobject_properties_manager.h"

std::unordered_set<Gameobject*>
	MoveProc::moveObjectsInGameboard = std::unordered_set<Gameobject*>();

vector2d<int8_t>
	MoveProc::blockMoveableRecord = vector2d<int8_t>();
std::unordered_set<Gameobject*>
	MoveProc::moveableGameobjects = std::unordered_set<Gameobject*>();

void MoveProc::CreateBlockMoveableRecord() {
	if (blockMoveableRecord.size() != 0) {
		for (auto &col : blockMoveableRecord) {
			col.clear();
		}
		blockMoveableRecord.clear();
	}

	for (int i = 0; i < LevelData::gameboardWidth; i++) {
		blockMoveableRecord.push_back(std::vector<int8_t>(LevelData::gameboardHeight, 0));
	}
}

void MoveProc::MoveUp() {
	std::unordered_set<Gameobject*> hasYouPropGameobject = findAllYouObject();

	resetBlockMoveableRecord();
	moveableGameobjects.clear();

	for (Gameobject *gameobject : hasYouPropGameobject) {
		if (checkMoveUp(gameobject->gameBoardPosition.Up())) {
			moveableGameobjects.insert(gameobject);
		}
	}

	for (Gameobject *gameobject : moveableGameobjects) {
		UndoProc::AddUndo(UndoProc::UNDO_MOVE_UP, gameobject);
		GameboardProc::RemoveGameobject(gameobject);
		gameobject->moveUp();
		GameboardProc::AddGameobject(gameobject);
	}
}
void MoveProc::MoveDown() {
	std::unordered_set<Gameobject*> hasYouPropGameobject = findAllYouObject();

	resetBlockMoveableRecord();
	moveableGameobjects.clear();

	for (Gameobject *gameobject : hasYouPropGameobject) {
		if (checkMoveDown(gameobject->gameBoardPosition.Down())) {
			moveableGameobjects.insert(gameobject);
		}
	}

	for (Gameobject *gameobject : moveableGameobjects) {
		UndoProc::AddUndo(UndoProc::UNDO_MOVE_DOWN, gameobject);
		GameboardProc::RemoveGameobject(gameobject);
		gameobject->moveDown();
		GameboardProc::AddGameobject(gameobject);
	}
}
void MoveProc::MoveLeft() {
	std::unordered_set<Gameobject*> hasYouPropGameobject = findAllYouObject();

	resetBlockMoveableRecord();
	moveableGameobjects.clear();

	for (Gameobject *gameobject : hasYouPropGameobject) {
		if (checkMoveLeft(gameobject->gameBoardPosition.Left())) {
			moveableGameobjects.insert(gameobject);
		}
	}

	for (Gameobject *gameobject : moveableGameobjects) {
		UndoProc::AddUndo(UndoProc::UNDO_MOVE_LEFT, gameobject);
		GameboardProc::RemoveGameobject(gameobject);
		gameobject->moveLeft();
		GameboardProc::AddGameobject(gameobject);
	}
}
void MoveProc::MoveRight() {
	std::unordered_set<Gameobject*> hasYouPropGameobject = findAllYouObject();

	resetBlockMoveableRecord();
	moveableGameobjects.clear();

	for (Gameobject *gameobject : hasYouPropGameobject) {
		if (checkMoveRight(gameobject->gameBoardPosition.Right())) {
			moveableGameobjects.insert(gameobject);
		}
	}

	for (Gameobject *gameobject : moveableGameobjects) {
		UndoProc::AddUndo(UndoProc::UNDO_MOVE_RIGHT, gameobject);
		GameboardProc::RemoveGameobject(gameobject);
		gameobject->moveRight();
		GameboardProc::AddGameobject(gameobject);
	}
}

std::unordered_set<Gameobject*> MoveProc::findAllYouObject() {
	std::unordered_set<Gameobject*> result;
	for (auto &col : LevelData::gameboard) {
		for (Block &block : col) {
			for (Gameobject *gameobject : block) {
				if (GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, PROP_YOU)) {
					result.insert(gameobject);
				}
			}
		}
	}
	return result;
}

void MoveProc::resetBlockMoveableRecord() {
	for (auto &col : blockMoveableRecord) {
		for (int8_t &val : col) {
			val = -1;
		}
	}
}
bool MoveProc::checkBlockMoveable(Point position, std::unordered_set<PropId> aheadBlockProps, bool aheadBlockMoveable) {
	std::unordered_set<Gameobject*> blockMoveableObjects;

	for (Gameobject *gameobject : LevelData::gameboard[position]) {
		bool pushProp = GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, PROP_PUSH);

		if (pushProp) {
			if (!aheadBlockMoveable) {
				if (!GameobjectPropsManager::CheckPropCanBeOffset(gameobject->gameobjectId, aheadBlockProps)) {
					return blockMoveableRecord[position] = 0;
				}
			}
			blockMoveableObjects.insert(gameobject);
		}
	}
	moveableGameobjects.insert(blockMoveableObjects.begin(), blockMoveableObjects.end());
	return blockMoveableRecord[position] = 1;
}
bool MoveProc::checkMoveUp(Point position) {
	if (position.y == -1) return false;
	if (blockMoveableRecord[position] != -1) {
		return blockMoveableRecord[position];
	}

	for (Gameobject *gameobject : LevelData::gameboard[position]) {
		bool stopProp = GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, PROP_STOP);
		bool pushProp = GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, PROP_PUSH);
		if (stopProp && !pushProp) return blockMoveableRecord[position] = 0;
	}

	if (!LevelData::gameboard[position].HasMoveableGameobject()) {
		return blockMoveableRecord[position] = 1;
	}

	bool aheadBlockMoveable = checkMoveUp(position.Up());
	blockMoveableRecord[position] = checkBlockMoveable(position, GameboardProc::GetAllPropsInBlock(position.Up()), aheadBlockMoveable);
	return blockMoveableRecord[position];
}
bool MoveProc::checkMoveDown(Point position) {
	if (position.y == LevelData::gameboardHeight) return false;
	if (blockMoveableRecord[position] != -1) {
		return blockMoveableRecord[position];
	}

	for (Gameobject *gameobject : LevelData::gameboard[position]) {
		bool stopProp = GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, PROP_STOP);
		bool pushProp = GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, PROP_PUSH);
		if (stopProp && !pushProp) return blockMoveableRecord[position] = 0;
	}

	if (!LevelData::gameboard[position].HasMoveableGameobject()) {
		return blockMoveableRecord[position] = 1;
	}

	bool aheadBlockMoveable = checkMoveDown(position.Down());
	blockMoveableRecord[position] = checkBlockMoveable(position, GameboardProc::GetAllPropsInBlock(position.Down()), aheadBlockMoveable);
	return blockMoveableRecord[position];
}
bool MoveProc::checkMoveLeft(Point position) {
	if (position.x == -1) return false;
	if (blockMoveableRecord[position.x][position.y] != -1) {
		return blockMoveableRecord[position];
	}

	for (Gameobject *gameobject : LevelData::gameboard[position]) {
		bool stopProp = GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, PROP_STOP);
		bool pushProp = GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, PROP_PUSH);
		if (stopProp && !pushProp) return blockMoveableRecord[position] = 0;
	}

	if (!LevelData::gameboard[position].HasMoveableGameobject()) {
		return blockMoveableRecord[position] = 1;
	}

	bool aheadBlockMoveable = checkMoveLeft(position.Left());
	blockMoveableRecord[position] = checkBlockMoveable(position, GameboardProc::GetAllPropsInBlock(position.Left()), aheadBlockMoveable);
	return blockMoveableRecord[position];
}
bool MoveProc::checkMoveRight(Point position) {
	if (position.x == LevelData::gameboardWidth) return false;
	if (blockMoveableRecord[position] != -1) {
		return blockMoveableRecord[position];
	}

	for (Gameobject *gameobject : LevelData::gameboard[position]) {
		bool stopProp = GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, PROP_STOP);
		bool pushProp = GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, PROP_PUSH);
		if (stopProp && !pushProp) return blockMoveableRecord[position] = 0;
	}

	if (!LevelData::gameboard[position].HasMoveableGameobject()) {
		return blockMoveableRecord[position] = 1;
	}

	bool aheadBlockMoveable = checkMoveRight(position.Right());
	blockMoveableRecord[position] = checkBlockMoveable(position, GameboardProc::GetAllPropsInBlock(position.Right()), aheadBlockMoveable);
	return blockMoveableRecord[position];
}