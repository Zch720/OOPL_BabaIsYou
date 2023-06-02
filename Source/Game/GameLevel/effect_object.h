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

public:
	static void Init();
	static game_framework::CMovingBitmap GetWinObjectEffectTexture54();
	static game_framework::CMovingBitmap GetWinObjectEffectTexture108();
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