#pragma once

#include <vector>
#include <unordered_set>
#include "gameobject.h"

class DescriptionProc {
private:
	typedef std::pair<GameobjectId, GameobjectId> GameobjectIdPair;
	typedef std::unordered_set<Gameobject*> GameobjectSet;

	static std::vector<GameobjectIdPair> descriptionProps;
	static GameobjectSet connectedTextObjects;

	static Gameobject* getNounTextInBlock(CPoint);
	static Gameobject* getPropTextInBlock(CPoint);
	static void checkOperatorIs();
	static void checkOperatorIsHorizontal(Gameobject* gameobject);
	static void checkOperatorIsVertical(Gameobject* gameobject);

public:
	static std::vector<GameobjectIdPair> GetDescriptionProps();
	static std::unordered_set<Gameobject*> GetConnectedTextObjects();

	static void Clear();
	static void GetAllDescription();
	static void UpdatePropFromDescription();
};