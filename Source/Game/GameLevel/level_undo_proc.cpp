#include "stdafx.h"
#include "level_undo_proc.h"
#include "level_gameboard_proc.h"
#include "../../Expansion/log.h"

std::vector<UndoProc::UndoInfo> UndoProc::undoBuffer = std::vector<UndoProc::UndoInfo>();
std::stack<std::vector<UndoProc::UndoInfo>> UndoProc::undoStack = std::stack<std::vector<UndoProc::UndoInfo>>();

void UndoProc::ClearBuffer() {
	undoBuffer.clear();
}

void UndoProc::AddUndo(UndoType type, Gameobject *gameobject) {
	undoBuffer.push_back(UndoInfo{
		type,
		gameobject->gameobjectId,
		gameobject->textureDirection,
		gameobject->gameBoardPosition
	});
}

void UndoProc::AddBufferToStack() {
	if (undoBuffer.size() == 0) return;
	undoStack.push(undoBuffer);
}

void UndoProc::Undo() {
	if (undoStack.empty()) return;

	undoBuffer = undoStack.top();
	undoStack.pop();

	std::reverse(undoBuffer.begin(), undoBuffer.end());

	for (UndoInfo &info : undoBuffer) {
		if (info.type == UNDO_MOVE_UP) {
			Gameobject *undoObject =
				GameboardProc::FindGameobjectByIdInBlock(
					info.position.Up(),
					info.id
				);
			if (undoObject == nullptr) {
				Log::LogError("can't find undo gameobject.");
			}

			GameboardProc::RemoveGameobject(undoObject);
			undoObject->undoUp(info.direction);
			GameboardProc::AddGameobject(undoObject);
		}
		else if (info.type == UNDO_MOVE_DOWN) {
			Gameobject *undoObject =
				GameboardProc::FindGameobjectByIdInBlock(
					info.position.Down(),
					info.id
				);
			if (undoObject == nullptr) {
				Log::LogError("can't find undo gameobject.");
			}

			GameboardProc::RemoveGameobject(undoObject);
			undoObject->undoDown(info.direction);
			GameboardProc::AddGameobject(undoObject);
		}
		else if (info.type == UNDO_MOVE_LEFT) {
			Gameobject *undoObject =
				GameboardProc::FindGameobjectByIdInBlock(
					info.position.Left(),
					info.id
				);
			if (undoObject == nullptr) {
				Log::LogError("can't find undo gameobject.");
			}

			GameboardProc::RemoveGameobject(undoObject);
			undoObject->undoLeft(info.direction);
			GameboardProc::AddGameobject(undoObject);
		}
		else if (info.type == UNDO_MOVE_RIGHT) {
			Gameobject *undoObject =
				GameboardProc::FindGameobjectByIdInBlock(
					info.position.Right(),
					info.id
				);
			if (undoObject == nullptr) {
				Log::LogError("can't find undo gameobject.");
			}

			GameboardProc::RemoveGameobject(undoObject);
			undoObject->undoRight(info.direction);
			GameboardProc::AddGameobject(undoObject);
		}
		else if (info.type == UNDO_DELETE) {
			Gameobject *newGameobject = GameboardProc::GenGameobject(info.position, info.id);
			newGameobject->textureDirection = info.direction;
		}
		else if (info.type == UNDO_GEN) {
			Gameobject *undoObject =
				GameboardProc::FindGameobjectByIdInBlock(
					info.position,
					info.id
				);
			if (undoObject == nullptr) {
				Log::LogError("can't find undo gameobject.");
			}

			GameboardProc::DeleteGameobject(undoObject);
		}
	}
}