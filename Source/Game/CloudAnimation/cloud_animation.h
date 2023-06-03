#pragma once

#include "../style.h"
#include "../../Library/gameutil.h"

class CloudAnimation {
public:
	void Init();
	void StartCloud(Style style);

	bool IsShowing();
	bool IsCloudClosing();
	bool IsCloudOpening();
	bool IsSwitch();

	void Show();

private:
	static const int CLOSE_FRAME = 23;
	static const int OPEN_FRAME = 24;

	static game_framework::CMovingBitmap cloudCloseNone;
	static game_framework::CMovingBitmap cloudOpenNone;
	
	game_framework::CMovingBitmap cloudCloseAnimation;
	game_framework::CMovingBitmap cloudOpenAnimation;

	int closeFrameCount = CLOSE_FRAME;
	int openFrameCount = OPEN_FRAME;

	void loadCloseTexture(Style style);
	void loadOpenTexture(Style style);
};