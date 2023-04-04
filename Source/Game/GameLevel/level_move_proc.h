#pragma once

#include <vector>
#include <unordered_set>
#include "gameobject.h"

class MoveProc {
private:
	static std::unordered_set<Gameobject*> moveObjectsInGameboard;

	static std::vector<std::vector<int8_t>> blockMoveableRecord;
	static std::unordered_set<Gameobject*> moveableGameobjects;

	static std::unordered_set<Gameobject*> findAllYouObject();

	static void resetBlockMoveableRecord();
	static bool checkBlockMoveable(CPoint, bool);
	static bool checkMoveUp(CPoint);
	static bool checkMoveDown(CPoint);
	static bool checkMoveLeft(CPoint);
	static bool checkMoveRight(CPoint);

public:
	static void CreateBlockMoveableRecord();
	static void MoveUp();
	static void MoveDown();
	static void MoveLeft();
	static void MoveRight();
};