#pragma once

#include <unordered_set>
#include <stack>
#include "gameobject.h"
#include "gameobject_id.h"
#include "property_id.h"

class LevelManager {
private:
	// texture status
	int textureAnimationCount = 0;
	int nextTextureWaitTime = 0;

public:
	LevelManager();
	~LevelManager();

	void LoadLevel(int level);

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Undo();

	bool IsMoving();
	bool IsWin();

	void Show();
};