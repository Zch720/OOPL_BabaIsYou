#include "stdafx.h"
#include "level_gameboard_proc.h"
#include "level_data.h"
#include "level_undo_proc.h"

int GameboardProc::GetGameobjectConnectStatus(Gameobject *gameobject) {
	GameobjectId gameobjectId = gameobject->gameobjectId;
	CPoint position = gameobject->gameBoardPosition;
	int result = 0;

	if (position.x == LevelData::gameboardWidth - 1 || HasGameobjectIdInBlock(position + CPoint(1, 0), gameobjectId)) {
		result |= 0b1;
	}
	if (position.y == 0 || HasGameobjectIdInBlock(position - CPoint(0, 1), gameobjectId)) {
		result |= 0b10;
	}
	if (position.x == 0 || HasGameobjectIdInBlock(position - CPoint(1, 0), gameobjectId)) {
		result |= 0b100;
	}
	if (position.y == LevelData::gameboardHeight - 1 || HasGameobjectIdInBlock(position + CPoint(0, 1), gameobjectId)) {
		result |= 0b1000;
	}
	return result;
}

Gameobject* GameboardProc::GenGameobject(CPoint position, GameobjectId gameobjectId) {
	return LevelData::gameboard[position].GenGameobject(gameobjectId);
}
void GameboardProc::DeleteGameobject(Gameobject* gameobject) {
	LevelData::gameboard[gameobject->gameBoardPosition].DeleteGameobject(gameobject);
}
void GameboardProc::AddGameobject(Gameobject* gameobject) {
	LevelData::gameboard[gameobject->gameBoardPosition].AddGameobject(gameobject);
}
void GameboardProc::RemoveGameobject(Gameobject* gameobject) {
	LevelData::gameboard[gameobject->gameBoardPosition].RemoveGameobject(gameobject);
}
void GameboardProc::ReplaceGameobject(GameobjectId originGameobjectId, GameobjectId convertGameobjectId) {
	for (auto &col : LevelData::gameboard) {
		for (Block &block : col) {
			for (size_t i = 0; i < block.GetSize(); i++) {
				if (block[i]->gameobjectId == originGameobjectId) {
					Gameobject *replaceGameobject = block.GenGameobject(convertGameobjectId);
					UndoProc::AddUndo(UndoProc::UNDO_GEN, replaceGameobject);
					UndoProc::AddUndo(UndoProc::UNDO_DELETE, block[i]);
					block.DeleteGameobject(block[i]);
				}
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
bool GameboardProc::HasGameobjectIdInBlock(CPoint position, GameobjectId gameobjectId) {
	return LevelData::gameboard[position].HasGameobjectId(gameobjectId);
}
Gameobject* GameboardProc::FindGameobjectByIdInBlock(CPoint position, GameobjectId gameobjectId) {
	return LevelData::gameboard[position].FindGameobjectById(gameobjectId);
}
Gameobject* GameboardProc::FindGameobjectByPropInBlock(CPoint position, PropId propId) {
	return LevelData::gameboard[position].FindGameobjectByProp(propId);
}