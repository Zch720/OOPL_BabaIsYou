#include "stdafx.h"
#include "direction.h"

Direction GetOppositeDirection(Direction direction) {
    if (direction == DIRECTION_RIGHT) return DIRECTION_LEFT;
    if (direction == DIRECTION_UP) return DIRECTION_DOWN;
    if (direction == DIRECTION_LEFT) return DIRECTION_RIGHT;
    if (direction == DIRECTION_DOWN) return DIRECTION_UP;
	return DIRECTION_NONE;
}