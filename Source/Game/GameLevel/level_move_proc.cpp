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

void MoveProc::MoveWait() {
	std::unordered_set<Gameobject*> hasMovePropGameobject = findAllMoveObject();

	resetBlockMoveableRecord();
	moveableGameobjects.clear();

	for (Gameobject *gameobject : hasMovePropGameobject) {
		if (gameobject->textureDirection == DIRECTION_UP) {
			if (checkMoveUp(gameobject->gameBoardPosition.Up())) {
				moveableGameobjects.insert(gameobject);
			} else if (checkMoveDown(gameobject->gameBoardPosition.Down())) {
				gameobject->textureDirection = DIRECTION_DOWN;
				moveableGameobjects.insert(gameobject);
			}
		}
		else if (gameobject->textureDirection == DIRECTION_DOWN) {
			if (checkMoveDown(gameobject->gameBoardPosition.Down())) {
				moveableGameobjects.insert(gameobject);
			} else if (checkMoveUp(gameobject->gameBoardPosition.Up())) {
				gameobject->textureDirection = DIRECTION_UP;
				moveableGameobjects.insert(gameobject);
			}
		}
		else if (gameobject->textureDirection == DIRECTION_LEFT) {
			if (checkMoveLeft(gameobject->gameBoardPosition.Left())) {
				moveableGameobjects.insert(gameobject);
			} else if (checkMoveRight(gameobject->gameBoardPosition.Right())) {
				gameobject->textureDirection = DIRECTION_RIGHT;
				moveableGameobjects.insert(gameobject);
			}
		}
		else if (gameobject->textureDirection == DIRECTION_RIGHT) {
			if (checkMoveRight(gameobject->gameBoardPosition.Right())) {
				moveableGameobjects.insert(gameobject);
			} else if (checkMoveLeft(gameobject->gameBoardPosition.Left())) {
				gameobject->textureDirection = DIRECTION_LEFT;
				moveableGameobjects.insert(gameobject);
			}
		}
	}

	for (Gameobject *gameobject : moveableGameobjects) {
		if (gameobject->textureDirection == DIRECTION_UP) {
			UndoProc::AddUndo(UndoProc::UNDO_MOVE_UP, gameobject);
			GameboardProc::RemoveGameobject(gameobject);
			gameobject->moveUp();
			GameboardProc::AddGameobject(gameobject);
		}
		else if (gameobject->textureDirection == DIRECTION_DOWN) {
			UndoProc::AddUndo(UndoProc::UNDO_MOVE_DOWN, gameobject);
			GameboardProc::RemoveGameobject(gameobject);
			gameobject->moveDown();
			GameboardProc::AddGameobject(gameobject);
		}
		else if (gameobject->textureDirection == DIRECTION_LEFT) {
			UndoProc::AddUndo(UndoProc::UNDO_MOVE_LEFT, gameobject);
			GameboardProc::RemoveGameobject(gameobject);
			gameobject->moveLeft();
			GameboardProc::AddGameobject(gameobject);
		}
		else if (gameobject->textureDirection == DIRECTION_RIGHT) {
			UndoProc::AddUndo(UndoProc::UNDO_MOVE_RIGHT, gameobject);
			GameboardProc::RemoveGameobject(gameobject);
			gameobject->moveRight();
			GameboardProc::AddGameobject(gameobject);
		}
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
std::unordered_set<Gameobject*> MoveProc::findAllMoveObject() {
	std::unordered_set<Gameobject*> result;
	for (auto &col : LevelData::gameboard) {
		for (Block &block : col) {
			for (Gameobject *gameobject : block) {
				if (GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, PROP_MOVE)) {
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
bool MoveProc::checkBlockMoveable(Point position, std::unordered_set<PropId> aheadBlockProps, bool aheadBlockMoveable, Direction direction) {
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
	for (Gameobject *gameobject : blockMoveableObjects) {
		gameobject->textureDirection = direction;
	}
	moveableGameobjects.insert(blockMoveableObjects.begin(), blockMoveableObjects.end());
	return blockMoveableRecord[position] = 1;
}
bool MoveProc::checkMoveUp(Point position) {
	if (position.y < 0) return false;
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
	blockMoveableRecord[position] = checkBlockMoveable(position, GameboardProc::GetAllPropsInBlock(position.Up()), aheadBlockMoveable, DIRECTION_UP);
	return blockMoveableRecord[position];
}
bool MoveProc::checkMoveDown(Point position) {
	if (position.y >= LevelData::gameboardHeight) return false;
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
	blockMoveableRecord[position] = checkBlockMoveable(position, GameboardProc::GetAllPropsInBlock(position.Down()), aheadBlockMoveable, DIRECTION_DOWN);
	return blockMoveableRecord[position];
}
bool MoveProc::checkMoveLeft(Point position) {
	if (position.x < 0) return false;
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
	blockMoveableRecord[position] = checkBlockMoveable(position, GameboardProc::GetAllPropsInBlock(position.Left()), aheadBlockMoveable, DIRECTION_LEFT);
	return blockMoveableRecord[position];
}
bool MoveProc::checkMoveRight(Point position) {
	if (position.x >= LevelData::gameboardWidth) return false;
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
	blockMoveableRecord[position] = checkBlockMoveable(position, GameboardProc::GetAllPropsInBlock(position.Right()), aheadBlockMoveable, DIRECTION_RIGHT);
	return blockMoveableRecord[position];
}