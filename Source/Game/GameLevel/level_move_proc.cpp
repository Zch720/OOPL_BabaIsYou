#include "stdafx.h"
#include "level_move_proc.h"
#include "level_data.h"
#include "level_gameboard_proc.h"
#include "level_property_proc.h"
#include "level_undo_proc.h"
#include "gameobject_properties_manager.h"

MoveProc::GameobjectSet MoveProc::moveObjectsInGameboard = MoveProc::GameobjectSet();
vector2d<int8_t> MoveProc::blockMoveableRecord = vector2d<int8_t>();
MoveProc::GameobjectSet MoveProc::moveableGameobjects = MoveProc::GameobjectSet();

void MoveProc::CreateBlockMoveableRecord() {
	blockMoveableRecord.clear();
	for (int i = 0; i < LevelData::GetGameboardWidth(); i++) {
		blockMoveableRecord.push_back(std::vector<int8_t>(LevelData::GetGameboardHeight(), 0));
	}
}

void MoveProc::MoveWait() {
	GameobjectSet hasMovePropGameobject = findAllMoveObject();
	resetBuffers();
	checkMovePropGameobjectsMovable(hasMovePropGameobject);
	groupOfGameobjectMove(moveableGameobjects);
}
void MoveProc::MoveUp() {
	GameobjectSet hasYouPropGameobject = findAllYouObject();
	resetBuffers();
	addAvailableMoveUpGroupOfGameobjectToMoveable(hasYouPropGameobject);
	groupOfGameobjectMove(moveableGameobjects);
}
void MoveProc::MoveDown() {
	GameobjectSet hasYouPropGameobject = findAllYouObject();
	resetBuffers();
	addAvailableMoveDownGroupOfGameobjectToMoveable(hasYouPropGameobject);
	groupOfGameobjectMove(moveableGameobjects);
}
void MoveProc::MoveLeft() {
	GameobjectSet hasYouPropGameobject = findAllYouObject();
	resetBuffers();
	addAvailableMoveLeftGroupOfGameobjectToMoveable(hasYouPropGameobject);
	groupOfGameobjectMove(moveableGameobjects);
}
void MoveProc::MoveRight() {
	GameobjectSet hasYouPropGameobject = findAllYouObject();
	resetBuffers();
	addAvailableMoveRightGroupOfGameobjectToMoveable(hasYouPropGameobject);
	groupOfGameobjectMove(moveableGameobjects);
}

MoveProc::GameobjectSet MoveProc::findAllYouObject() {
	GameobjectSet result;
	LevelData::Gameboard.foreach([&](Block &block) {
		for (Gameobject *gameobject : block) {
			if (GameobjectPropsManager::GetGameobjectProp(gameobject->GetInfo().id, PROP_YOU)) {
				result.insert(gameobject);
			}
		}
	});
	return result;
}
MoveProc::GameobjectSet MoveProc::findAllMoveObject() {
	GameobjectSet result;
	LevelData::Gameboard.foreach([&](Block &block) {
		for (Gameobject *gameobject : block) {
			if (GameobjectPropsManager::GetGameobjectProp(gameobject->GetInfo().id, PROP_MOVE)) {
				result.insert(gameobject);
			}
		}
	});
	return result;
}

void MoveProc::resetBuffers() {
	resetBlockMoveableRecord();
	moveableGameobjects.clear();
}
void MoveProc::setGameobjectMoveableWithDirection(Gameobject *gameobject, Direction direction) {
	gameobject->SetTextureDirection(direction);
	moveableGameobjects.insert(gameobject);
}
void MoveProc::setGroupOfGameobjectMoveableWithDirection(GameobjectSet &gameobjects, Direction direction) {
	for (Gameobject *gameobject : gameobjects) {
		setGameobjectMoveableWithDirection(gameobject, direction);
	}
}

bool MoveProc::addAvailableMoveUpGameobjectToMoveable(Gameobject *gameobject) {
	bool result = checkMoveUp(gameobject->GetInfo().position.Up());
	if (result) setGameobjectMoveableWithDirection(gameobject, DIRECTION_UP);
	return result;
}
bool MoveProc::addAvailableMoveDownGameobjectToMoveable(Gameobject *gameobject) {
	bool result = checkMoveDown(gameobject->GetInfo().position.Down());
	if (result) setGameobjectMoveableWithDirection(gameobject, DIRECTION_DOWN);
	return result;
}
bool MoveProc::addAvailableMoveLeftGameobjectToMoveable(Gameobject *gameobject) {
	bool result = checkMoveLeft(gameobject->GetInfo().position.Left());
	if (result) setGameobjectMoveableWithDirection(gameobject, DIRECTION_LEFT);
	return result;
}
bool MoveProc::addAvailableMoveRightGameobjectToMoveable(Gameobject *gameobject) {
	bool result = checkMoveRight(gameobject->GetInfo().position.Right());
	if (result) setGameobjectMoveableWithDirection(gameobject, DIRECTION_RIGHT);
	return result;
}

void MoveProc::addAvailableMoveUpGroupOfGameobjectToMoveable(GameobjectSet &gameobjects) {
	for (Gameobject *gameobject : gameobjects) {
		addAvailableMoveUpGameobjectToMoveable(gameobject);
	}
}
void MoveProc::addAvailableMoveDownGroupOfGameobjectToMoveable(GameobjectSet &gameobjects) {
	for (Gameobject *gameobject : gameobjects) {
		addAvailableMoveDownGameobjectToMoveable(gameobject);
	}
}
void MoveProc::addAvailableMoveLeftGroupOfGameobjectToMoveable(GameobjectSet &gameobjects) {
	for (Gameobject *gameobject : gameobjects) {
		addAvailableMoveLeftGameobjectToMoveable(gameobject);
	}
}
void MoveProc::addAvailableMoveRightGroupOfGameobjectToMoveable(GameobjectSet &gameobjects) {
	for (Gameobject *gameobject : gameobjects) {
		addAvailableMoveRightGameobjectToMoveable(gameobject);
	}
}

void MoveProc::gameobjectMove(Gameobject *gameobject) {
	switch (gameobject->GetTextureDirection()) {
	case DIRECTION_UP:
		gameobjectMoveUp(gameobject);
		break;
	case DIRECTION_DOWN:
		gameobjectMoveDown(gameobject);
		break;
	case DIRECTION_LEFT:
		gameobjectMoveLeft(gameobject);
		break;
	case DIRECTION_RIGHT:
		gameobjectMoveRight(gameobject);
		break;
	}
}
void MoveProc::gameobjectMoveUp(Gameobject *gameobject) {
	UndoProc::AddUndo(UndoProc::UNDO_MOVE_UP, gameobject);
	GameboardProc::RemoveGameobject(gameobject);
	gameobject->MoveUp();
	GameboardProc::AddGameobject(gameobject);
}
void MoveProc::gameobjectMoveDown(Gameobject *gameobject) {
	UndoProc::AddUndo(UndoProc::UNDO_MOVE_DOWN, gameobject);
	GameboardProc::RemoveGameobject(gameobject);
	gameobject->MoveDown();
	GameboardProc::AddGameobject(gameobject);
}
void MoveProc::gameobjectMoveLeft(Gameobject *gameobject) {
	UndoProc::AddUndo(UndoProc::UNDO_MOVE_LEFT, gameobject);
	GameboardProc::RemoveGameobject(gameobject);
	gameobject->MoveLeft();
	GameboardProc::AddGameobject(gameobject);
}
void MoveProc::gameobjectMoveRight(Gameobject *gameobject) {
	UndoProc::AddUndo(UndoProc::UNDO_MOVE_RIGHT, gameobject);
	GameboardProc::RemoveGameobject(gameobject);
	gameobject->MoveRight();
	GameboardProc::AddGameobject(gameobject);
}

void MoveProc::groupOfGameobjectMove(GameobjectSet &gameobjects) {
	for (Gameobject* gameobject : gameobjects) {
		gameobjectMove(gameobject);
	}
}

void MoveProc::checkMovePropGameobjectsMovable(GameobjectSet &gameobjects) {
	for (Gameobject *gameobject : gameobjects) {
		if (gameobject->GetTextureDirection() == DIRECTION_UP) {
			if (!addAvailableMoveUpGameobjectToMoveable(gameobject))
				addAvailableMoveDownGameobjectToMoveable(gameobject);
		}
		else if (gameobject->GetTextureDirection() == DIRECTION_DOWN) {
			if (!addAvailableMoveDownGameobjectToMoveable(gameobject))
				addAvailableMoveUpGameobjectToMoveable(gameobject);
		}
		else if (gameobject->GetTextureDirection() == DIRECTION_LEFT) {
			if (!addAvailableMoveLeftGameobjectToMoveable(gameobject))
				addAvailableMoveRightGameobjectToMoveable(gameobject);
		}
		else if (gameobject->GetTextureDirection() == DIRECTION_RIGHT) {
			if (!addAvailableMoveRightGameobjectToMoveable(gameobject))
				addAvailableMoveLeftGameobjectToMoveable(gameobject);
		}
	}
}

void MoveProc::resetBlockMoveableRecord() {
	blockMoveableRecord.foreach([](int8_t &val) {
		val = -1;
	});
}
bool MoveProc::blockMoveable(Point position) {
	for (Gameobject *gameobject : LevelData::Gameboard[position]) {
		bool stopProp = GameobjectPropsManager::GetGameobjectProp(gameobject->GetInfo().id, PROP_STOP);
		bool pushProp = GameobjectPropsManager::GetGameobjectProp(gameobject->GetInfo().id, PROP_PUSH);
		bool youProp = GameobjectPropsManager::GetGameobjectProp(gameobject->GetInfo().id, PROP_YOU);
		if (stopProp && !pushProp && !youProp) return false;
	}
	return true;
}
bool MoveProc::checkBlockCanSkip(Point position) {
	if (blockMoveableRecord[position] == -1 && !blockMoveable(position)) blockMoveableRecord[position] = 0;
	if (blockMoveableRecord[position] == -1 && !LevelData::Gameboard[position].HasMoveableGameobject()) blockMoveableRecord[position] = 1;
	if (blockMoveableRecord[position] != -1) return true;
	return false;
}

MoveProc::GameobjectSet MoveProc::getPushObjectInBlock(Point position) {
	GameobjectSet result;
	for (Gameobject *gameobject : LevelData::Gameboard[position]) {
		if (GameobjectPropsManager::GetGameobjectProp(gameobject->GetInfo().id, PROP_PUSH)) {
			result.insert(gameobject);
		}
	}
	return result;
}
bool MoveProc::checkGameobjectsMoveable(GameobjectSet &gameobjects, AheadBlockInfo aheadBlockInfo) {
	for (Gameobject *gameobject : gameobjects) {
		if (!aheadBlockInfo.moveable && !GameobjectPropsManager::CheckPropCanBeOffset(gameobject->GetInfo().id, aheadBlockInfo.properties)) {
			return false;
		}
	}
	return true;
}
bool MoveProc::checkBlockMoveable(MoveInfo moveInfo, AheadBlockInfo aheadBlockInfo) {
	GameobjectSet hasPushObjects = getPushObjectInBlock(moveInfo.position);
	blockMoveableRecord[moveInfo.position] = checkGameobjectsMoveable(hasPushObjects, aheadBlockInfo);
	if (blockMoveableRecord[moveInfo.position]) {
		setGroupOfGameobjectMoveableWithDirection(hasPushObjects, moveInfo.direction);
	}
	return blockMoveableRecord[moveInfo.position];
}
bool MoveProc::checkMoveUp(Point position) {
	if (!LevelData::IsPointInGameboard(position)) return false;
	if (checkBlockCanSkip(position)) return blockMoveableRecord[position];
	
	MoveInfo moveInfo { position,  DIRECTION_UP };
	AheadBlockInfo aheadBlockInfo { checkMoveUp(position.Up()), GameboardProc::GetAllPropsInBlock(position.Up()) };
	blockMoveableRecord[position] = checkBlockMoveable(moveInfo, aheadBlockInfo);
	return blockMoveableRecord[position];
}
bool MoveProc::checkMoveDown(Point position) {
	if (!LevelData::IsPointInGameboard(position)) return false;
	if (checkBlockCanSkip(position)) return blockMoveableRecord[position];
	
	MoveInfo moveInfo { position,  DIRECTION_DOWN };
	AheadBlockInfo aheadBlockInfo { checkMoveDown(position.Down()), GameboardProc::GetAllPropsInBlock(position.Down()) };
	blockMoveableRecord[position] = checkBlockMoveable(moveInfo, aheadBlockInfo);
	return blockMoveableRecord[position];
}
bool MoveProc::checkMoveLeft(Point position) {
	if (!LevelData::IsPointInGameboard(position)) return false;
	if (checkBlockCanSkip(position)) return blockMoveableRecord[position];
	
	MoveInfo moveInfo { position,  DIRECTION_LEFT };
	AheadBlockInfo aheadBlockInfo { checkMoveLeft(position.Left()), GameboardProc::GetAllPropsInBlock(position.Left()) };
	blockMoveableRecord[position] = checkBlockMoveable(moveInfo, aheadBlockInfo);
	return blockMoveableRecord[position];
}
bool MoveProc::checkMoveRight(Point position) {
	if (!LevelData::IsPointInGameboard(position)) return false;
	if (checkBlockCanSkip(position)) return blockMoveableRecord[position];

	MoveInfo moveInfo { position,  DIRECTION_RIGHT };
	AheadBlockInfo aheadBlockInfo { checkMoveRight(position.Right()), GameboardProc::GetAllPropsInBlock(position.Right()) };
	blockMoveableRecord[position] = checkBlockMoveable(moveInfo, aheadBlockInfo);
	return blockMoveableRecord[position];
}