#include "stdafx.h"
#include "level_undo_proc.h"
#include "level_gameboard_proc.h"
#include "../../Expansion/log.h"

std::vector<UndoProc::UndoInfo> UndoProc::undoBuffer = std::vector<UndoProc::UndoInfo>();
std::stack<std::vector<UndoProc::UndoInfo>> UndoProc::undoStack = std::stack<std::vector<UndoProc::UndoInfo>>();


void UndoProc::Clear() {
	undoBuffer.clear();
	while (!undoStack.empty()) {
		undoStack.pop();
	}
}
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

	getUndoInfosToProcess();
	GameboardProc::ResetGameobjectsReplaceRecord();
	for (UndoInfo &info : undoBuffer) {
		if (info.type == UNDO_MOVE_UP) {
			undoMoveUp(info);
		}
		else if (info.type == UNDO_MOVE_DOWN) {
			undoMoveDown(info);
		}
		else if (info.type == UNDO_MOVE_LEFT) {
			undoMoveLeft(info);
		}
		else if (info.type == UNDO_MOVE_RIGHT) {
			undoMoveRight(info);
		}
		else if (info.type == UNDO_DELETE) {
			undoDelete(info);
		}
		else if (info.type == UNDO_GEN) {
			undoGen(info);
		}
		else if (info.type == UNDO_REPLACE) {
			undoReplace(info);
		}
	}
}

void UndoProc::getUndoInfosToProcess() {
	undoBuffer = undoStack.top();
	undoStack.pop();
	std::reverse(undoBuffer.begin(), undoBuffer.end());
}

Gameobject* UndoProc::getUndoObject(Point position, GameobjectId gameobjectId) {
	Gameobject *undoObject = GameboardProc::FindGameobjectByIdInBlock(position, gameobjectId);
	if (undoObject == nullptr) {
		Log::LogError("can't find undo gameobject.");
	}
	return undoObject;
}

void UndoProc::undoMoveUp(UndoInfo info) {
	Gameobject *undoObject = getUndoObject(info.position.Up(), info.id);
	GameboardProc::RemoveGameobject(undoObject);
	undoObject->UndoUp(info.direction);
	GameboardProc::AddGameobject(undoObject);
}
void UndoProc::undoMoveDown(UndoInfo info) {
	Gameobject *undoObject = getUndoObject(info.position.Down(), info.id);
	GameboardProc::RemoveGameobject(undoObject);
	undoObject->UndoDown(info.direction);
	GameboardProc::AddGameobject(undoObject);
}
void UndoProc::undoMoveLeft(UndoInfo info) {
	Gameobject *undoObject = getUndoObject(info.position.Left(), info.id);
	GameboardProc::RemoveGameobject(undoObject);
	undoObject->UndoLeft(info.direction);
	GameboardProc::AddGameobject(undoObject);
}
void UndoProc::undoMoveRight(UndoInfo info) {
	Gameobject *undoObject = getUndoObject(info.position.Right(), info.id);
	GameboardProc::RemoveGameobject(undoObject);
	undoObject->UndoRight(info.direction);
	GameboardProc::AddGameobject(undoObject);
}
void UndoProc::undoGen(UndoInfo info) {
	Gameobject *undoObject = getUndoObject(info.position, info.id);
	GameboardProc::DeleteGameobject(undoObject);
}
void UndoProc::undoDelete(UndoInfo info) {
	Gameobject *newGameobject = GameboardProc::GenGameobject(info.position, info.id);
	newGameobject->SetTextureDirection(info.direction);
}
void UndoProc::undoReplace(UndoInfo info) {
	Gameobject *undoObject = getUndoObject(info.position, info.id);
	undoObject->Replace(static_cast<GameobjectId>(info.otherInfo));
}