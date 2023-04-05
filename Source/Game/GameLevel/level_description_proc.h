#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "gameobject.h"

class DescriptionProc {
private:
	typedef std::pair<GameobjectId, GameobjectId> GameobjectIdPair;
	typedef std::unordered_set<Gameobject*> GameobjectSet;

	static std::vector<GameobjectIdPair> descriptionProps;
	static GameobjectSet connectedTextObjects;

	static Gameobject* getNounTextInBlock(Point);
	static Gameobject* getPropTextInBlock(Point);
	static void checkOperatorIs();
	static void checkOperatorIsHorizontal(Gameobject *gameobject);
	static void checkOperatorIsVertical(Gameobject *gameobject);
	static std::unordered_map<Gameobject*, bool> checkMainObjectHorizontal(Point position);
	static std::unordered_map<Gameobject*, bool> checkSubObjectHorizontal(Point position);
	static std::unordered_map<Gameobject*, bool> checkMainObjectVertical(Point position);
	static std::unordered_map<Gameobject*, bool> checkSubObjectVertical(Point position);

public:
	static std::vector<GameobjectIdPair> GetDescriptionProps();
	static std::unordered_set<Gameobject*> GetConnectedTextObjects();

	static void Clear();
	static void GetAllDescription();
	static void UpdatePropFromDescription();
};