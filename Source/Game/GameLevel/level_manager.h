#pragma once

#include <unordered_set>
#include <stack>
#include <functional>
#include "gameobject.h"
#include "gameobject_id.h"
#include "property_id.h"

class LevelManager {
private:
	typedef std::function<bool(Gameobject*)> CheckCanShowFunc;

	// texture status
	int textureAnimationCount = 0;
	int nextTextureWaitTime = 0;

	void updateProperties();
	void addUndo();
	void showGameobjects(std::unordered_set<Gameobject*>&, CheckCanShowFunc);
	void showNotMovingGameobjects(std::unordered_set<Gameobject*>&);
	void showMovingGameobjects(std::unordered_set<Gameobject*>&);

public:
	LevelManager();
	~LevelManager();

	void LoadLevel(int level);

	void MoveWait();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Undo();

	bool IsMoving();
	bool IsWin();

	void Show();
};