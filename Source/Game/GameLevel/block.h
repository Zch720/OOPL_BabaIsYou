#pragma once

#include <vector>
#include "gameobject.h"

class Block {
private:
	std::vector<Gameobject*> blockObjects;
	CPoint gameboardPosition;

	void sortBlockObjects();

public:
	std::vector<Gameobject*>::iterator begin();
	std::vector<Gameobject*>::iterator end();
	void clear();

public:
	Block(CPoint position);

	size_t GetSize();
	CPoint GetPosition();

	Gameobject* operator[](const int index);

	Gameobject* GenGameobject(GameobjectId gameobjectId);
	void DeleteGameobject(Gameobject* gameobject);
	void AddGameobject(Gameobject* gameobject);
	void RemoveGameobject(Gameobject* gameobject);

	bool HasGameobjectId(GameobjectId gameobjectId);
	Gameobject* FindGameobjectById(GameobjectId gameobjectId);
	Gameobject* FindGameobjectByProp(PropId propId);

	void UpdateGameobjectColor();
};