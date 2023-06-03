#pragma once

#include <string>
#include "../style.h"

class LevelManager {
public:
	void Init();
	void Clean();

	void LoadLevel(int level);

	bool IsWin();
	bool IsMoving();

	std::string GetWorldTitle();
	std::string GetLevelTitle();
	std::string GetFullTitle();
	Style GetWorldMainStyle();

	void Undo();

	void MoveWait();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void Show();
};