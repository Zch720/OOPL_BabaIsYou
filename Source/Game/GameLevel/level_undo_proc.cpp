#include "stdafx.h"
#include "level_undo_proc.h"
#include "level_gameboard_proc.h"
#include "../../Expansion/log.h"

std::vector<UndoProc::UndoInfo> UndoProc::undoBuffer = std::vector<UndoProc::UndoInfo>();
std::stack<std::vector<UndoProc::UndoInfo>> UndoProc::undoStack = std::stack<std::vector<UndoProc::UndoInfo>>();

void UndoProc::ClearBuffer() {
	undoBuffer.clear();
}

void UndoProc::AddUndo(UndoType type, Gameobject *gameobject, int otherInfo) {
	undoBuffer.push_back(UndoInfo{
		type,
		gameobject->GetInfo().id,
		gameobject->GetTextureDirection(),
		gameobject->GetInfo().position,
		otherInfo
	});
}

bool UndoProc::AddBufferToStack() {
	if (undoBuffer.size() == 0) return false;
	undoStack.push(undoBuffer);
	return true;
}

void UndoProc::Undo() {
	if (undoStack.empty()) return;

	undoBuffer = undoStack.top();
	undoStack.pop();

	std::reverse(undoBuffer.begin(), undoBuffer.end());
	
	GameboardProc::ResetGameobjectsReplaceRecord();
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
			undoObject->UndoUp(info.direction);
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
			undoObject->UndoDown(info.direction);
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
			undoObject->UndoLeft(info.direction);
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
			undoObject->UndoRight(info.direction);
			GameboardProc::AddGameobject(undoObject);
		}
		else if (info.type == UNDO_DELETE) {
			Gameobject *newGameobject = GameboardProc::GenGameobject(info.position, info.id);
			newGameobject->SetTextureDirection(info.direction);
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
		else if (info.type == UNDO_REPLACE) {
			Gameobject *undoObject =
				GameboardProc::FindGameobjectByIdInBlock(
					info.position,
					info.id
				);
			if (undoObject == nullptr) {
				Log::LogError("can't find undo gameobject.");
			}
			undoObject->Replace(static_cast<GameobjectId>(info.otherInfo));
		}
	}
}