#pragma once

enum Direction {
	DIRECTION_NONE = -1,
	DIRECTION_RIGHT = 0,
	DIRECTION_UP = 1,
	DIRECTION_LEFT = 2,
	DIRECTION_DOWN = 3
};

Direction GetOppositeDirection(Direction direction);