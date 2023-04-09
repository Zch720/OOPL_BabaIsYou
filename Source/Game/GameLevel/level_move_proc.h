#pragma once

#include <vector>
#include <unordered_set>
#include "gameobject.h"
#include "../../Expansion/point.h"
#include "../../Expansion/vector2d.hpp"

class MoveProc {
private:
	static std::unordered_set<Gameobject*> moveObjectsInGameboard;

	static vector2d<int8_t> blockMoveableRecord;
	static std::unordered_set<Gameobject*> moveableGameobjects;

	static std::unordered_set<Gameobject*> findAllYouObject();
	static std::unordered_set<Gameobject*> findAllMoveObject();

	static void resetBlockMoveableRecord();
	static bool checkBlockMoveable(Point, std::unordered_set<PropId>, bool, Direction);
	static bool checkMoveUp(Point);
	static bool checkMoveDown(Point);
	static bool checkMoveLeft(Point);
	static bool checkMoveRight(Point);

public:
	static void CreateBlockMoveableRecord();
	static void MoveWait();
	static void MoveUp();
	static void MoveDown();
	static void MoveLeft();
	static void MoveRight();
};