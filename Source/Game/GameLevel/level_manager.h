#pragma once

class LevelManager {
public:
	void Init();
	void Clean();

	void LoadLevel(int level);

	bool IsWin();
	bool IsMoving();

	void Undo();

	void MoveWait();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void Show();
};