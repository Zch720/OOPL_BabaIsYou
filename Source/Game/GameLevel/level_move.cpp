#include "stdafx.h"
#include "property_manager.h"
#include "level_data.h"
#include "level_undo.h"
#include "level_move.h"
#include "../../Expansion/log.h"

LevelMove::MoveInfo LevelMove::MoveInfo::FromObjectInfo(ObjectInfo &info, Direction moveDirection) {
	return MoveInfo{info.genId, info.position, moveDirection};
}

bool LevelMove::MoveInfo::operator==(const LevelMove::MoveInfo &info) const {
	return objectGenId == info.objectGenId;
}

bool LevelMove::MoveInfo::operator<(const LevelMove::MoveInfo &info) {
	return objectGenId < info.objectGenId;
}

size_t LevelMove::MoveInfo::GetHash() const {
	return objectGenId;
}

size_t std::hash<LevelMove::MoveInfo>::operator()(const LevelMove::MoveInfo &info) const {
	return info.GetHash();
}


std::unordered_set<ObjectInfo> LevelMove::hasPropertyYouObjects = {};
std::unordered_set<ObjectInfo> LevelMove::hasPropertyMoveObjects = {};
std::unordered_set<LevelMove::MoveInfo> LevelMove::moveObjects = {};
vector2d<int8_t> LevelMove::moveable = {};

void LevelMove::CreateMoveableMap() {
	moveable.clear();
	for (int i = 0; i < LevelData::GetGameboardWidth(); i++){
		moveable.push_back(std::vector<int8_t>(LevelData::GetGameboardHeight(), -1));
	}
}

void LevelMove::MoveWait() {
	reset();
	findAllMoveObject();
	for (ObjectInfo objectInfo : hasPropertyMoveObjects) {
		Direction direction = objectInfo.textureDirection;
		Direction oppositeDirection = GetOppositeDirection(direction);
		if (checkBlockMoveable(objectInfo.position + getMoveOffset(direction), direction)) {
			moveObjects.insert(MoveInfo::FromObjectInfo(objectInfo, direction));
		} else if (checkBlockMoveable(objectInfo.position + getMoveOffset(oppositeDirection), oppositeDirection)) {
			moveObjects.insert(MoveInfo::FromObjectInfo(objectInfo, oppositeDirection));
		}
	}
	moveAllObjects();
}

void LevelMove::MoveUp() {
	reset();
	findAllYouObject();
	for (ObjectInfo objectInfo : hasPropertyYouObjects) {
		if (objectInfo.position.y == 0) continue;
		if (checkBlockMoveable(objectInfo.position.Up(), DIRECTION_UP)) {
			moveObjects.insert(MoveInfo::FromObjectInfo(objectInfo, DIRECTION_UP));
		} else if (moveBlockPreviousUnmoveableWithYouMove(objectInfo.position, DIRECTION_UP)) {
			moveObjects.insert(MoveInfo::FromObjectInfo(objectInfo, DIRECTION_UP));
		}
	}
	moveAllObjects();
}

void LevelMove::MoveDown() {
	reset();
	findAllYouObject();
	for (ObjectInfo objectInfo : hasPropertyYouObjects) {
		if (objectInfo.position.y == LevelData::GetGameboardHeight() - 1) continue;
		if (checkBlockMoveable(objectInfo.position.Down(), DIRECTION_DOWN)) {
			moveObjects.insert(MoveInfo::FromObjectInfo(objectInfo, DIRECTION_DOWN));
		} else if (moveBlockPreviousUnmoveableWithYouMove(objectInfo.position, DIRECTION_DOWN)) {
			moveObjects.insert(MoveInfo::FromObjectInfo(objectInfo, DIRECTION_DOWN));
		}
	}
	moveAllObjects();
}

void LevelMove::MoveLeft() {
	reset();
	findAllYouObject();
	for (ObjectInfo objectInfo : hasPropertyYouObjects) {
		if (objectInfo.position.x == 0) continue;
		if (checkBlockMoveable(objectInfo.position.Left(), DIRECTION_LEFT)) {
			moveObjects.insert(MoveInfo::FromObjectInfo(objectInfo, DIRECTION_LEFT));
		} else if (moveBlockPreviousUnmoveableWithYouMove(objectInfo.position, DIRECTION_LEFT)) {
			moveObjects.insert(MoveInfo::FromObjectInfo(objectInfo, DIRECTION_LEFT));
		}
	}
	moveAllObjects();
}

void LevelMove::MoveRight() {
	reset();
	findAllYouObject();
	for (ObjectInfo objectInfo : hasPropertyYouObjects) {
		if (objectInfo.position.x == LevelData::GetGameboardWidth() - 1) continue;
		if (checkBlockMoveable(objectInfo.position.Right(), DIRECTION_RIGHT)) {
			moveObjects.insert(MoveInfo::FromObjectInfo(objectInfo, DIRECTION_RIGHT));
		} else if (moveBlockPreviousUnmoveableWithYouMove(objectInfo.position, DIRECTION_RIGHT)) {
			moveObjects.insert(MoveInfo::FromObjectInfo(objectInfo, DIRECTION_RIGHT));
		}
	}
	moveAllObjects();
}

void LevelMove::reset() {
	hasPropertyYouObjects.clear();
	hasPropertyMoveObjects.clear();
	moveObjects.clear();
	moveable.foreach([](int8_t &value) {
		value = -1;
	});
}

bool LevelMove::isMoveableObject(ObjectId objectId) {
	return (
		PropertyManager::ObjectHasProperty(objectId, PROPERTY_YOU) ||
		PropertyManager::ObjectHasProperty(objectId, PROPERTY_PUSH)
	);
}

bool LevelMove::isMoveableObjectWithoutYou(ObjectId objectId) {
	return (
		PropertyManager::ObjectHasProperty(objectId, PROPERTY_PUSH)
	);
}

bool LevelMove::isUnmoveableObject(ObjectId objectId) {
	return (
		PropertyManager::ObjectHasProperty(objectId, PROPERTY_STOP)
	);
}

Point LevelMove::getMoveOffset(Direction moveDirection) {
	if (moveDirection == DIRECTION_UP) return Point().Up();
	else if (moveDirection == DIRECTION_DOWN) return Point().Down();
	else if (moveDirection == DIRECTION_LEFT) return Point().Left();
	else if (moveDirection == DIRECTION_RIGHT) return Point().Right();
	return Point();
}

void LevelMove::findAllYouObject() {
	LevelData::AllObjectForeach([](ObjectBase &object) {
		if (PropertyManager::ObjectHasProperty(object.GetObjectId(), PROPERTY_YOU)) {
			hasPropertyYouObjects.insert(object.GetInfo());
		}
	});
}

void LevelMove::findAllMoveObject() {
	LevelData::AllObjectForeach([](ObjectBase &object) {
		if (PropertyManager::ObjectHasProperty(object.GetObjectId(), PROPERTY_MOVE)) {
			hasPropertyMoveObjects.insert(object.GetInfo());
		}
	});
}

bool LevelMove::hasMoveableObject(POINT position) {
	bool result = false;
	LevelData::BlockObjectForeach(position, [&result](ObjectBase &object) {
		if (result) return;
		result |= isMoveableObject(object.GetObjectId());
	});
	return result;
}

bool LevelMove::hasMoveableObjectWithoutYou(POINT position) {
	bool result = false;
	LevelData::BlockObjectForeach(position, [&result](ObjectBase &object) {
		if (result) return;
		result |= isMoveableObjectWithoutYou(object.GetObjectId());
	});
	return result;
}

bool LevelMove::checkBlockPropertiesMoveable(POINT position) {
	bool result = true;
	LevelData::BlockObjectForeach(position, [&result](ObjectBase &object) {
		if (!result) return;
		if (isUnmoveableObject(object.GetObjectId()) && !isMoveableObject(object.GetObjectId())) {
			result = false;
		}
	});
	return result;
}

bool LevelMove::checkBlockCanSkip(POINT position) {
	if (moveable[position] == -1 && !checkBlockPropertiesMoveable(position)) moveable[position] = 0;
	if (moveable[position] == -1 && !hasMoveableObjectWithoutYou(position)) moveable[position] = 1;
	return moveable[position] != -1;
}

bool LevelMove::checkBlockMoveable(POINT position, Direction moveDirection) {
	if (!LevelData::IsInsideGameboard(position)) return false;
	if (checkBlockCanSkip(position)) return moveable[position];

	if (checkBlockMoveable(getMoveOffset(moveDirection) + position, moveDirection)) {
		moveBlockPreviousMoveable(position,  moveDirection);
	} else {
		moveBlockPreviousUnmoveable(position, moveDirection);
	}
	return moveable[position];
}

bool LevelMove::moveBlockPreviousMoveable(POINT position, Direction moveDirection) {
	LevelData::BlockObjectForeach(position, [moveDirection](ObjectBase &object) {
		if (isMoveableObject(object.GetObjectId())) {
			moveObjects.insert(MoveInfo::FromObjectInfo(object.GetInfo(), moveDirection));
		}
	});
	return moveable[position] = 1;
}

bool LevelMove::moveBlockPreviousUnmoveable(POINT position, Direction moveDirection) {
	if (!LevelData::IsInsideGameboard(getMoveOffset(moveDirection) + position)) return moveable[position] = 0;
	
	std::unordered_set<MoveInfo> blockMoveObjects = {};

	std::vector<ObjectId> previousObjectIds = LevelData::GetBlockObjectIds(getMoveOffset(moveDirection) + position);
	std::vector<ObjectId> objectIds = {};
	LevelData::BlockObjectForeach(position, [&objectIds](ObjectBase &object) {
		if (isMoveableObject(object.GetObjectId())) {
			objectIds.push_back(object.GetObjectId());
		}
	});
	// LevelData::GetBlockObjectIds(position);

	PropertyManager::RemoveOffsetObjects(objectIds, previousObjectIds);

	for (ObjectId objectId : previousObjectIds) {
		if (isUnmoveableObject(objectId)) return moveable[position] = 0;
		if (isMoveableObjectWithoutYou(objectId)) return moveable[position] = 0;
	}

	LevelData::BlockObjectForeach(position, [moveDirection](ObjectBase &object) {
		if (isMoveableObject(object.GetObjectId())) {
			moveObjects.insert(MoveInfo::FromObjectInfo(object.GetInfo(), moveDirection));
		}
	});
	return moveable[position] = 1;
}

bool LevelMove::moveBlockPreviousUnmoveableWithMove(POINT position, Direction moveDirection) {
	if (!LevelData::IsInsideGameboard(getMoveOffset(moveDirection) + position)) return moveable[position] = 0;

	std::unordered_set<MoveInfo> blockMoveObjects = {};
	
	std::vector<ObjectId> previousObjectIds = LevelData::GetBlockObjectIds(getMoveOffset(moveDirection) + position);
	std::vector<ObjectId> objectIds = {};
	LevelData::BlockObjectForeach(position, [&objectIds](ObjectBase &object) {
		if (object.HasProperty(PROPERTY_MOVE)) {
			objectIds.push_back(object.GetObjectId());
		}
	});

	PropertyManager::RemoveOffsetObjects(objectIds, previousObjectIds);

	for (ObjectId objectId : previousObjectIds) {
		if (isUnmoveableObject(objectId)) return moveable[position] = 0;
		if (isMoveableObjectWithoutYou(objectId)) return moveable[position] = 0;
	}

	// LevelData::BlockObjectForeach(position, [moveDirection](ObjectBase &object) {
	// 	if (isMoveableObject(object.GetObjectId())) {
	// 		moveObjects.insert(MoveInfo::FromObjectInfo(object.GetInfo(), moveDirection));
	// 	}
	// });
	return moveable[position] = 1;
}

bool LevelMove::moveBlockPreviousUnmoveableWithYouMove(POINT position, Direction moveDirection) {
	if (!LevelData::IsInsideGameboard(getMoveOffset(moveDirection) + position)) return moveable[position] = 0;

	std::unordered_set<MoveInfo> blockMoveObjects = {};
	
	std::vector<ObjectId> previousObjectIds = LevelData::GetBlockObjectIds(getMoveOffset(moveDirection) + position);
	std::vector<ObjectId> objectIds = {};
	LevelData::BlockObjectForeach(position, [&objectIds](ObjectBase &object) {
		if (object.HasProperty(PROPERTY_YOU) || object.HasProperty(PROPERTY_MOVE)) {
			objectIds.push_back(object.GetObjectId());
		}
	});

	PropertyManager::RemoveOffsetObjects(objectIds, previousObjectIds);

	for (ObjectId objectId : previousObjectIds) {
		if (isUnmoveableObject(objectId)) return moveable[position] = 0;
		if (isMoveableObjectWithoutYou(objectId)) return moveable[position] = 0;
	}

	return moveable[position] = 1;
}

void LevelMove::moveAllObjects() {
	for (MoveInfo moveInfo : moveObjects) {
		if (moveInfo.moveDirection == DIRECTION_UP) moveObjectUp(moveInfo);
		else if (moveInfo.moveDirection == DIRECTION_DOWN) moveObjectDown(moveInfo);
		else if (moveInfo.moveDirection == DIRECTION_LEFT) moveObjectLeft(moveInfo);
		else if (moveInfo.moveDirection == DIRECTION_RIGHT) moveObjectRight(moveInfo);
	}
}

void LevelMove::moveObjectUp(MoveInfo &moveInfo) {
	ObjectBase& object = LevelData::GetBlockObject(moveInfo.position, moveInfo.objectGenId);
	LevelUndo::AddObjectUndo(LevelUndo::UNDO_MOVE_UP, object.GetInfo());
	LevelData::MoveObject(object.GetInfo(), object.GetPosition().Up());
	object.MoveUp(DIRECTION_UP);
}

void LevelMove::moveObjectDown(MoveInfo &moveInfo) {
	ObjectBase& object = LevelData::GetBlockObject(moveInfo.position, moveInfo.objectGenId);
	LevelUndo::AddObjectUndo(LevelUndo::UNDO_MOVE_DOWN, object.GetInfo());
	LevelData::MoveObject(object.GetInfo(), object.GetPosition().Down());
	object.MoveDown(DIRECTION_DOWN);
}

void LevelMove::moveObjectLeft(MoveInfo &moveInfo) {
	ObjectBase& object = LevelData::GetBlockObject(moveInfo.position, moveInfo.objectGenId);
	LevelUndo::AddObjectUndo(LevelUndo::UNDO_MOVE_LEFT, object.GetInfo());
	LevelData::MoveObject(object.GetInfo(), object.GetPosition().Left());
	object.MoveLeft(DIRECTION_LEFT);
}

void LevelMove::moveObjectRight(MoveInfo &moveInfo) {
	ObjectBase& object = LevelData::GetBlockObject(moveInfo.position, moveInfo.objectGenId);
	LevelUndo::AddObjectUndo(LevelUndo::UNDO_MOVE_RIGHT, object.GetInfo());
	LevelData::MoveObject(object.GetInfo(), object.GetPosition().Right());
	object.MoveRight(DIRECTION_RIGHT);
}