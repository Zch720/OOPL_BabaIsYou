#pragma once

#include "../style.h"
#include "../../Library/gameutil.h"

class CloudAnimation {
public:
	void Init();
	void StartCloudClose(Style style);
	void StopCloudClose();
	void StartCloudOpen(Style style);
	void StopCloudOpen();
	void StartCloudCloseWithCongratulation(Style style);

	bool IsShowing();
	bool IsCloudClosing();
	bool IsCloudCloseEnd();
	bool IsCloudOpening();
	bool IsCloudOpenEnd();

	void Show();

private:
	static const int CLOSE_FRAME = 23;
	static const int OPEN_FRAME = 24;
	static const int CONGRATULATION_SHOW_FRAME = 44;
	static const int CONGRATULATION_LOOP_FRAME = 9;

	static game_framework::CMovingBitmap cloudCloseNone;
	static game_framework::CMovingBitmap cloudOpenNone;
	static game_framework::CMovingBitmap congratulationShowNone;
	static game_framework::CMovingBitmap congratulationLoopNone;
	
	game_framework::CMovingBitmap cloudCloseAnimation;
	game_framework::CMovingBitmap cloudOpenAnimation;
	game_framework::CMovingBitmap congratulationShowAnimation;
	game_framework::CMovingBitmap congratulationLoopAnimation;

	int closeFrameCount = CLOSE_FRAME;
	int openFrameCount = OPEN_FRAME;
	int congratulationShowFrameCount = CONGRATULATION_SHOW_FRAME;
	int congratulationLoopFrameCount = CONGRATULATION_LOOP_FRAME;

	bool showCloudClose = false;
	bool showCloudOpen = false;
	bool showCongratulation = false;

	void loadCloseTexture(Style style);
	void loadOpenTexture(Style style);
	void loadCongratulationShowTexture(Style style);
	void loadCongratulationLoopTexture(Style style);
};