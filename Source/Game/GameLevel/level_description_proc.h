#pragma once

#include <stack>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "gameobject.h"

class DescriptionProc {
private:
	typedef std::pair<GameobjectId, GameobjectId> GameobjectIdPair;
	typedef std::unordered_set<Gameobject*> GameobjectSet;

	static std::unordered_multimap<GameobjectId, std::vector<Gameobject*>> descriptionProps;
	static std::stack<std::unordered_multimap<GameobjectId, std::vector<Gameobject*>>> descriptionStack;
	static GameobjectSet connectedTextObjects;
	static GameobjectSet cannotUseTextObjects;

	static GameobjectId getPreviousDescriptionConvertNoneGameobject(GameobjectId);
	static int getDescriptionConvertNounGameobjectCount(GameobjectId);

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
	static void Undo();
	static void GetAllDescription();
	static void UpdatePropFromDescription();
};