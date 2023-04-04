#include "stdafx.h"
#include "level_move_proc.h"
#include "level_data.h"
#include "level_gameboard_proc.h"
#include "level_property_proc.h"
#include "level_undo_proc.h"
#include "gameobject_properties_manager.h"

std::unordered_set<Gameobject*>
	MoveProc::moveObjectsInGameboard = std::unordered_set<Gameobject*>();

std::vector<std::vector<int8_t>>
	MoveProc::blockMoveableRecord = std::vector<std::vector<int8_t>>();
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
		if (checkMoveUp(gameobject->gameBoardPosition - CPoint(0, 1))) {
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
		if (checkMoveDown(gameobject->gameBoardPosition + CPoint(0, 1))) {
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
		if (checkMoveLeft(gameobject->gameBoardPosition - CPoint(1, 0))) {
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
		if (checkMoveRight(gameobject->gameBoardPosition + CPoint(1, 0))) {
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
bool MoveProc::checkBlockMoveable(CPoint position, bool aheadBlockMoveable) {
	for (Gameobject *gameobject : LevelData::gameboard[position.x][position.y]) {
		bool pushProp = GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, PROP_PUSH);

		if (pushProp) {
			if (!aheadBlockMoveable)
				return blockMoveableRecord[position.x][position.y] = 0;
			moveableGameobjects.insert(gameobject);
		}
	}
	return blockMoveableRecord[position.x][position.y] = 1;
}
bool MoveProc::checkMoveUp(CPoint position) {
	if (position.y == -1) return false;
	if (blockMoveableRecord[position.x][position.y] != -1) {
		return blockMoveableRecord[position.x][position.y];
	}

	bool stopProp = PropertyProc::CheckHasPropInBlock(position, PROP_STOP);
	if (stopProp) {
		return blockMoveableRecord[position.x][position.y] = 0;
	}

	bool youProp = PropertyProc::CheckHasPropInBlock(position, PROP_YOU);
	bool pushProp = PropertyProc::CheckHasPropInBlock(position, PROP_PUSH);
	if (!youProp && !pushProp) {
		return blockMoveableRecord[position.x][position.y] = 1;
	}
	bool aheadBlockMoveable = checkMoveUp(position - CPoint(0, 1));
	blockMoveableRecord[position.x][position.y] = checkBlockMoveable(position, aheadBlockMoveable);
	return blockMoveableRecord[position.x][position.y];
}
bool MoveProc::checkMoveDown(CPoint position) {
	if (position.y == LevelData::gameboardHeight) return false;
	if (blockMoveableRecord[position.x][position.y] != -1) {
		return blockMoveableRecord[position.x][position.y];
	}

	bool stopProp = PropertyProc::CheckHasPropInBlock(position, PROP_STOP);
	if (stopProp) {
		return blockMoveableRecord[position.x][position.y] = 0;
	}

	bool youProp = PropertyProc::CheckHasPropInBlock(position, PROP_YOU);
	bool pushProp = PropertyProc::CheckHasPropInBlock(position, PROP_PUSH);
	if (!youProp && !pushProp) {
		return blockMoveableRecord[position.x][position.y] = 1;
	}
	bool aheadBlockMoveable = checkMoveDown(position + CPoint(0, 1));
	blockMoveableRecord[position.x][position.y] = checkBlockMoveable(position, aheadBlockMoveable);
	return blockMoveableRecord[position.x][position.y];
}
bool MoveProc::checkMoveLeft(CPoint position) {
	if (position.x == -1) return false;
	if (blockMoveableRecord[position.x][position.y] != -1) {
		return blockMoveableRecord[position.x][position.y];
	}

	bool stopProp = PropertyProc::CheckHasPropInBlock(position, PROP_STOP);
	if (stopProp) {
		return blockMoveableRecord[position.x][position.y] = 0;
	}

	bool youProp = PropertyProc::CheckHasPropInBlock(position, PROP_YOU);
	bool pushProp = PropertyProc::CheckHasPropInBlock(position, PROP_PUSH);
	if (!youProp && !pushProp) {
		return blockMoveableRecord[position.x][position.y] = 1;
	}
	bool aheadBlockMoveable = checkMoveLeft(position - CPoint(1, 0));
	blockMoveableRecord[position.x][position.y] = checkBlockMoveable(position, aheadBlockMoveable);
	return blockMoveableRecord[position.x][position.y];
}
bool MoveProc::checkMoveRight(CPoint position) {
	if (position.x == LevelData::gameboardWidth) return false;
	if (blockMoveableRecord[position.x][position.y] != -1) {
		return blockMoveableRecord[position.x][position.y];
	}

	bool stopProp = PropertyProc::CheckHasPropInBlock(position, PROP_STOP);
	if (stopProp) {
		return blockMoveableRecord[position.x][position.y] = 0;
	}

	bool youProp = PropertyProc::CheckHasPropInBlock(position, PROP_YOU);
	bool pushProp = PropertyProc::CheckHasPropInBlock(position, PROP_PUSH);
	if (!youProp && !pushProp) {
		return blockMoveableRecord[position.x][position.y] = 1;
	}
	bool aheadBlockMoveable = checkMoveRight(position + CPoint(1, 0));
	blockMoveableRecord[position.x][position.y] = checkBlockMoveable(position, aheadBlockMoveable);
	return blockMoveableRecord[position.x][position.y];
}