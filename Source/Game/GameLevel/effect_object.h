#pragma once

#include <vector>
#include "../../Library/gameutil.h"

struct EffectInfo {
	int startDistance;
	int endDistance;
	int totalDistance;
	double degree;
	int frame;
	std::vector<int> changeFrameIndex;
};

class EffectTextures {
private:
	static game_framework::CMovingBitmap winObjectEffectTexture54;
	static game_framework::CMovingBitmap winObjectEffectTexture108;
	static game_framework::CMovingBitmap dispearTexture54;
	static game_framework::CMovingBitmap dispearTexture108;
	static game_framework::CMovingBitmap moveUp54;
	static game_framework::CMovingBitmap moveUp108;
	static game_framework::CMovingBitmap moveDown54;
	static game_framework::CMovingBitmap moveDown108;
	static game_framework::CMovingBitmap moveLeft54;
	static game_framework::CMovingBitmap moveLeft108;
	static game_framework::CMovingBitmap moveRight54;
	static game_framework::CMovingBitmap moveRight108;
	static game_framework::CMovingBitmap deadHintBubble;

	static void loadTexture(std::string path, int count, game_framework::CMovingBitmap& texture);

public:
	static void Init();
	static game_framework::CMovingBitmap GetWinObjectEffectTexture54();
	static game_framework::CMovingBitmap GetWinObjectEffectTexture108();
	static game_framework::CMovingBitmap GetDispearTexture54();
	static game_framework::CMovingBitmap GetDispearTexture108();
	static game_framework::CMovingBitmap GetMoveUpTexture54();
	static game_framework::CMovingBitmap GetMoveUpTexture108();
	static game_framework::CMovingBitmap GetMoveDownTexture54();
	static game_framework::CMovingBitmap GetMoveDownTexture108();
	static game_framework::CMovingBitmap GetMoveLeftTexture54();
	static game_framework::CMovingBitmap GetMoveLeftTexture108();
	static game_framework::CMovingBitmap GetMoveRightTexture54();
	static game_framework::CMovingBitmap GetMoveRightTexture108();
	static game_framework::CMovingBitmap GetDeadHintBubbleTexture();
};

class EffectObjectBase {
protected:
	EffectInfo info;
	int frameCount = 0;
	int textureChangeCount = 0;
	game_framework::CMovingBitmap texture;
	POINT centerPosition;

	virtual void updatePosition() = 0;
	virtual void updateTexture() = 0;

public:
	bool IsEnd();

	void Show();
};

class WinObjectEffect : public EffectObjectBase {
private:
	static const int textureCount = 5;

	void loadTexture(int size);
	void createInfo();

	void updatePosition() override;
	void updateTexture() override;

public:
	WinObjectEffect(POINT centerPosition, int size);
};

class DispearEffect : public EffectObjectBase {
private:
	static const int textureCount = 19;

	void loadTexture(int size);
	void createInfo();

	void updatePosition() override;
	void updateTexture() override;

public:
	DispearEffect(POINT centerPosition, int size);
};

class MoveUpEffect : public EffectObjectBase {
private:
	static const int textureCount = 18;

	void loadTexture(int size);
	void createInfo();

	void updatePosition() override;
	void updateTexture() override;

public:
	MoveUpEffect(POINT centerPosition, int size);
};

class MoveDownEffect : public EffectObjectBase {
private:
	static const int textureCount = 18;

	void loadTexture(int size);
	void createInfo();

	void updatePosition() override;
	void updateTexture() override;

public:
	MoveDownEffect(POINT centerPosition, int size);
};

class MoveLeftEffect : public EffectObjectBase {
private:
	static const int textureCount = 18;

	void loadTexture(int size);
	void createInfo();

	void updatePosition() override;
	void updateTexture() override;

public:
	MoveLeftEffect(POINT centerPosition, int size);
};

class MoveRightEffect : public EffectObjectBase {
private:
	static const int textureCount = 18;

	void loadTexture(int size);
	void createInfo();

	void updatePosition() override;
	void updateTexture() override;

public:
	MoveRightEffect(POINT centerPosition, int size);
};


class DeadHintBubbleEffect : public EffectObjectBase {
private:
	static const int textureCount = 4;

	void loadTexture();
	void createInfo();

	void updatePosition() override;
	void updateTexture() override;

public:
	DeadHintBubbleEffect(POINT centerPosition, int width);
};