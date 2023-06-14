#pragma once
#include <stack>
#include "../../Library/gameutil.h"
#include "map_object.h"
#include "map_object_id.h"
#include "../../Expansion/point.h"
#include "../../Expansion/vector2d.hpp"

using namespace game_framework;
class Map {
private:
	vector2d<Mapobject> worldVector;
	Mapobject box;
	CMovingBitmap worldBackground;

	std::stack<Direction> undoBuffer;

	void CreateWorldVector();
	bool checkWalkable(POINT position);

public:
	int worldVectorWidth;
	int worldVectorHeight;

	Point textureOrigionPosition;

	void LoadWorld(int world);
	void ClearWorld();
	int CheckIndex();
	Point GetBoxPosition();
	void SetBoxPosition(Point boxPosition);
	
	void Show();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Undo();
};