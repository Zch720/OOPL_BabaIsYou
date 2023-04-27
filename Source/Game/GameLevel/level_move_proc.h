#pragma once

#include <vector>
#include <unordered_set>
#include "gameobject.h"
#include "../../Expansion/point.h"
#include "../../Expansion/vector2d.hpp"

class MoveProc {
private:
	typedef std::unordered_set<Gameobject*> GameobjectSet;

	struct MoveInfo {
		Point position;
		Direction direction;
	};
	struct AheadBlockInfo {
		bool moveable;
		std::unordered_set<PropId> properties;
	};

	static GameobjectSet moveObjectsInGameboard;

	static vector2d<int8_t> blockMoveableRecord;
	static GameobjectSet moveableGameobjects;

	static GameobjectSet findAllYouObject();
	static GameobjectSet findAllMoveObject();

	static void resetBuffers();
	static void setGameobjectMoveableWithDirection(Gameobject*, Direction);
	static void setGroupOfGameobjectMoveableWithDirection(GameobjectSet&, Direction);

	static bool addAvailableMoveUpGameobjectToMoveable(Gameobject*);
	static bool addAvailableMoveDownGameobjectToMoveable(Gameobject*);
	static bool addAvailableMoveLeftGameobjectToMoveable(Gameobject*);
	static bool addAvailableMoveRightGameobjectToMoveable(Gameobject*);

	static void addAvailableMoveUpGroupOfGameobjectToMoveable(GameobjectSet&);
	static void addAvailableMoveDownGroupOfGameobjectToMoveable(GameobjectSet&);
	static void addAvailableMoveLeftGroupOfGameobjectToMoveable(GameobjectSet&);
	static void addAvailableMoveRightGroupOfGameobjectToMoveable(GameobjectSet&);

	static void gameobjectMove(Gameobject*);
	static void gameobjectMoveUp(Gameobject*);
	static void gameobjectMoveDown(Gameobject*);
	static void gameobjectMoveLeft(Gameobject*);
	static void gameobjectMoveRight(Gameobject*);
	
	static void groupOfGameobjectMove(GameobjectSet&);

	static void checkMovePropGameobjectsMovable(GameobjectSet&);

	static void resetBlockMoveableRecord();
	static bool blockMoveable(Point);
	static bool checkBlockCanSkip(Point);
	static GameobjectSet getPushObjectInBlock(Point);
	static bool checkGameobjectsMoveable(GameobjectSet&, AheadBlockInfo);
	static bool checkBlockMoveable(MoveInfo, AheadBlockInfo);
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