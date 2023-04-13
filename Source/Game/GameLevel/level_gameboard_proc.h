#pragma once

#include <unordered_set>
#include "gameobject.h"

class GameboardProc {
public:
	static int GetGameobjectConnectStatus(Gameobject*);

	static Gameobject* GenGameobject(Point position, GameobjectId gameobjectId);
	static void DeleteGameobject(Gameobject* gameobject);
	static void AddGameobject(Gameobject* gameobject);
	static void RemoveGameobject(Gameobject* gameobject);
	static void ResetGameobjectsReplaceRecord();
	static void UpdateGameobjectTextureColor();
	static bool HasGameobjectIdInBlock(Point position, GameobjectId gameobjectId);
	static Gameobject* FindGameobjectByIdInBlock(Point position, GameobjectId gameobjectId);
	static Gameobject* FindGameobjectByPropInBlock(Point position, PropId propId);
	static std::unordered_set<PropId> GetAllPropsInBlock(Point position);
};