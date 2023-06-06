#include "stdafx.h"
#include "cloud_animation.h"

game_framework::CMovingBitmap CloudAnimation::cloudCloseNone = {};
game_framework::CMovingBitmap CloudAnimation::cloudOpenNone = {};
game_framework::CMovingBitmap CloudAnimation::congratulationShowNone = {};
game_framework::CMovingBitmap CloudAnimation::congratulationLoopNone = {};

void CloudAnimation::Init() {
	std::vector<std::string> files;
	char filepath[260];

	files.clear();
	for (int i = 0; i < OPEN_FRAME; i++) {
		sprintf_s(filepath, 260, "./resources/effect/cloud_open_none/%d.bmp", i);
		files.push_back(filepath);
	}
	cloudOpenNone.LoadBitmapByString(files, 0xFFFFFF);
	
	files.clear();
	for (int i = 0; i < CLOSE_FRAME; i++) {
		sprintf_s(filepath, 260, "./resources/effect/cloud_close_none/%d.bmp", i);
		files.push_back(filepath);
	}
	cloudCloseNone.LoadBitmapByString(files, 0xFFFFFF);

	files.clear();
	for (int i = 0; i < CONGRATULATION_SHOW_FRAME; i++) {
		sprintf_s(filepath, 260, "./resources/effect/congratulation_show_none/%d.bmp", i);
		files.push_back(filepath);
	}
	congratulationShowNone.LoadBitmapByString(files, 0x000000);

	files.clear();
	for (int i = 0; i < CONGRATULATION_LOOP_FRAME; i++) {
		sprintf_s(filepath, 260, "./resources/effect/congratulation_loop_none/%d.bmp", i);
		files.push_back(filepath);
	}
	congratulationLoopNone.LoadBitmapByString(files, 0x000000);
}

void CloudAnimation::StartCloudClose(Style style) {
	loadCloseTexture(style);
	// loadOpenTexture(style);
	showCloudClose = true;
	showCongratulation = false;
	closeFrameCount = 0;
}

void CloudAnimation::StopCloudClose() {
	showCloudClose = false;
	showCongratulation = false;
}

void CloudAnimation::StartCloudOpen(Style style) {
	// loadCloseTexture(style);
	loadOpenTexture(style);
	showCloudOpen = true;
	showCongratulation = false;
	openFrameCount = 0;
}

void CloudAnimation::StopCloudOpen() {
	showCloudOpen = false;
}

void CloudAnimation::StartCloudCloseWithCongratulation(Style style) {
	loadCloseTexture(style);
	// loadOpenTexture(style);
	loadCongratulationShowTexture(style);
	loadCongratulationLoopTexture(style);
	showCloudClose = true;
	showCongratulation = true;
	closeFrameCount = 0;
	congratulationShowFrameCount = 0;
	congratulationLoopFrameCount = 0;
}

bool CloudAnimation::IsShowing() {
	return showCloudClose || showCloudOpen;
}

bool CloudAnimation::IsCloudClosing() {
	return showCloudClose;
}

bool CloudAnimation::IsCloudCloseEnd() {
	return showCloudClose && closeFrameCount == CLOSE_FRAME;
}

bool CloudAnimation::IsCloudOpening() {
	return showCloudOpen;
}

bool CloudAnimation::IsCloudOpenEnd() {
	return showCloudOpen && openFrameCount == OPEN_FRAME;
}

// bool CloudAnimation::IsSwitch() {
// 	return openFrameCount == 0;
// }

void CloudAnimation::Show() {
	if (showCongratulation) {
		if (congratulationShowFrameCount != CONGRATULATION_SHOW_FRAME) {
			congratulationShowAnimation.SetFrameIndexOfBitmap(congratulationShowFrameCount++);
			congratulationShowAnimation.ShowBitmap();
			return;
		}

		congratulationLoopAnimation.SetFrameIndexOfBitmap(congratulationLoopFrameCount++);
		congratulationLoopAnimation.ShowBitmap();
		if (congratulationLoopFrameCount == CONGRATULATION_LOOP_FRAME) {
			congratulationLoopFrameCount = 0;
		}
	}
	if (closeFrameCount != CLOSE_FRAME) {
		cloudCloseAnimation.SetFrameIndexOfBitmap(closeFrameCount++);
		cloudCloseAnimation.ShowBitmap();
		if (closeFrameCount == CLOSE_FRAME) {
			showCongratulation = false;
		}
	} else if (openFrameCount != OPEN_FRAME) {
		cloudOpenAnimation.SetFrameIndexOfBitmap(openFrameCount++);
		cloudOpenAnimation.ShowBitmap();
	}
}

void CloudAnimation::loadCloseTexture(Style style) {
	if (style == STYLE_NONE) {
		cloudCloseAnimation = cloudCloseNone;
	}
	cloudCloseAnimation.SetFrameIndexOfBitmap(0);
}

void CloudAnimation::loadOpenTexture(Style style) {
	if (style == STYLE_NONE) {
		cloudOpenAnimation = cloudOpenNone;
	}
	cloudOpenAnimation.SetFrameIndexOfBitmap(0);
}

void CloudAnimation::loadCongratulationShowTexture(Style style) {
	if (style == STYLE_NONE) {
		congratulationShowAnimation = congratulationShowNone;
	}
	congratulationShowAnimation.SetFrameIndexOfBitmap(0);
}

void CloudAnimation::loadCongratulationLoopTexture(Style style) {
	if (style == STYLE_NONE) {
		congratulationLoopAnimation = congratulationLoopNone;
	}
	congratulationLoopAnimation.SetFrameIndexOfBitmap(0);
}