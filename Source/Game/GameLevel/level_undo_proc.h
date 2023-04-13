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
		UNDO_DELETE,
		UNDO_REPLACE
	};

private:
	struct UndoInfo {
		UndoType type;
		GameobjectId id;
		Direction direction;
		Point position;
		int otherInfo;
	};

	static std::vector<UndoInfo> undoBuffer;
	static std::stack<std::vector<UndoInfo>> undoStack;

public:
	static void ClearBuffer();
	static void AddUndo(UndoType type, Gameobject *gameobject, int otherInfo = 0);
	static bool AddBufferToStack();

	static void Undo();
};