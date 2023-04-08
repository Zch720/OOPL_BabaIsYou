#pragma once

#include <vector>
#include "../../Expansion/point.h"
#include "gameobject.h"

class Block {
private:
	std::vector<Gameobject*> blockObjects;
	Point gameboardPosition;

	void sortBlockObjects();

public:
	std::vector<Gameobject*>::iterator begin();
	std::vector<Gameobject*>::iterator end();
	void clear();

public:
	Block(Point position);

	size_t GetSize();
	Point GetPosition();

	bool IsEmpty();

	Gameobject* operator[](const int index);

	Gameobject* GenGameobject(GameobjectId gameobjectId);
	void DeleteGameobject(Gameobject* gameobject);
	void AddGameobject(Gameobject* gameobject);
	void RemoveGameobject(Gameobject* gameobject);

	bool HasGameobjectId(GameobjectId gameobjectId);
	bool HasMoveableGameobject();
	Gameobject* FindGameobjectById(GameobjectId gameobjectId);
	Gameobject* FindGameobjectByProp(PropId propId);

	void UpdateGameobjectColor();
};