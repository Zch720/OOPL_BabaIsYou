#pragma once

#include <stack>
#include <vector>
#include "../../Expansion/point.h"
#include "gameobject.h"

class UndoProc {
public:
	enum UndoType {
		UNDO_MOVE_UP,
		UNDO_MOVE_DOWN,
		UNDO_MOVE_LEFT,
		UNDO_MOVE_RIGHT,
		UNDO_GEN,
		UNDO_DELETE
	};

private:
	struct UndoInfo {
		UndoType type;
		GameobjectId id;
		Direction direction;
		Point position;
	};

	static std::vector<UndoInfo> undoBuffer;
	static std::stack<std::vector<UndoInfo>> undoStack;

public:
	static void ClearBuffer();
	static void AddUndo(UndoType type, Gameobject *gameobject);
	static bool AddBufferToStack();

	static void Undo();
};