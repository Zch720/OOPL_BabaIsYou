#pragma once

#include <unordered_set>
#include "../../Expansion/point.h"
#include "../../Expansion/vector2d.hpp"

class LevelMove {
public:
	struct MoveInfo {
		static MoveInfo FromObjectInfo(ObjectInfo &info, Direction moveDirection);

		int objectGenId;
		Point position;
		Direction moveDirection;

		bool operator==(const MoveInfo &other) const;
		bool operator<(const MoveInfo &other);

		size_t GetHash() const;
	};

private:
	static std::unordered_set<ObjectInfo> hasPropertyYouObjects;
	static std::unordered_set<ObjectInfo> hasPropertyMoveObjects;
	static std::unordered_set<MoveInfo> moveObjects;
	static vector2d<int8_t> moveable;

	static void reset();

	static bool isMoveableObject(ObjectId objectId);
	static bool isMoveableObjectWithoutYou(ObjectId objectId);
	static bool isUnmoveableObject(ObjectId objectId);

	static Point getMoveOffset(Direction moveDirection);

	static void findAllYouObject();
	static void findAllMoveObject();

	static bool hasMoveableObject(POINT position);
	static bool hasMoveableObjectWithoutYou(POINT position);
	static bool checkBlockPropertiesMoveable(POINT position);
	static bool checkBlockCanSkip(POINT position);
	static bool checkBlockMoveable(POINT position, Direction moveDirection);
	static bool moveBlockPreviousMoveable(POINT position, Direction moveDirection);
	static bool moveBlockPreviousUnmoveable(POINT position, Direction moveDirection);
	static bool moveBlockPreviousUnmoveableWithMove(POINT position, Direction moveDirection);
	static bool moveBlockPreviousUnmoveableWithYouMove(POINT position, Direction moveDirection);

	static void moveAllObjects();
	static void moveObjectUp(MoveInfo &moveInfo);
	static void moveObjectDown(MoveInfo &moveInfo);
	static void moveObjectLeft(MoveInfo &moveInfo);
	static void moveObjectRight(MoveInfo &moveInfo);

public:
	static void CreateMoveableMap();
	static void MoveWait();
	static void MoveUp();
	static void MoveDown();
	static void MoveLeft();
	static void MoveRight();
};

namespace std{
	template<>
	struct hash<LevelMove::MoveInfo> {
		size_t operator()(const LevelMove::MoveInfo &info) const;
	};
}