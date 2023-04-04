#pragma once

#include "gameobject.h"

class GameboardProc {
public:
	static int GetGameobjectConnectStatus(Gameobject*);

	static Gameobject* GenGameobject(CPoint position, GameobjectId gameobjectId);
	static void DeleteGameobject(Gameobject* gameobject);
	static void AddGameobject(Gameobject* gameobject);
	static void RemoveGameobject(Gameobject* gameobject);
	static void ReplaceGameobject(GameobjectId originGameobjectId, GameobjectId convertGameobjectId);
	static void UpdateGameobjectTextureColor();
	static bool HasGameobjectIdInBlock(CPoint position, GameobjectId gameobjectId);
	static Gameobject* FindGameobjectByIdInBlock(CPoint position, GameobjectId gameobjectId);
	static Gameobject* FindGameobjectByPropInBlock(CPoint position, PropId propId);
};